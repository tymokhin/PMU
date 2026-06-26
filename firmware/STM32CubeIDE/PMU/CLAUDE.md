# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Firmware for a **PMU (Phasor Measurement Unit)** built on an **STM32H725AGIx** (Cortex-M7) using STM32CubeIDE (GCC / `arm-none-eabi`). The project is a STM32CubeMX-generated CubeIDE project: `PMU.ioc` is the source of truth for pin/peripheral/clock config — regenerating it overwrites code outside `/* USER CODE BEGIN ... END */` guards in `Core/`.

Integrates several large middlewares: **FreeRTOS**, **CycloneTCP** (TCP/IP), **Percepio Tracealyzer 4** (streaming trace), and **libiec61850** (IEC 61850 protocol stack). External **SDRAM** (MT48LC32M16, FMC), **SD card** with an **Ext4** driver, and a **LAN8720** Ethernet PHY are attached.

## Build & flash

This is a CubeIDE-managed build; the GCC makefile is generated under `Debug/`.

- Build: `make -C Debug` (or Project → Build in STM32CubeIDE). Output: `Debug/PMU.elf`.
- Clean: `make -C Debug clean`.
- Flash/debug: use the `PMU Debug.launch` configuration in CubeIDE (ST-LINK). `STM32H725AGIX_FLASH.ld` is the production linker script; `STM32H725AGIX_RAM.ld` exists for RAM-only runs.
- There is **no host unit-test harness** in this repo — "tests" means on-target verification via the debugger and the ITM/Tracealyzer logs.

Editing peripheral config: change it in `PMU.ioc` and regenerate, or hand-edit inside the USER CODE guards. Do not put hand-written code outside those guards in CubeMX-owned files.

## Diagnostics channels

- **Debug logging** is over **ITM/SWO** (`Helper/debug_log.{c,h}`, `DEBUG_LOG_BACKEND_ITM`). Use the `DBG_INFO` / `DBG_ERROR` macros. Logs only appear with an SWO viewer attached.
- **Tracealyzer** runs in **streaming mode over TCP** (`Tracealyzer4/streamports/trcStreamingPort.c`), listening on **port 12000**. The desktop Tracealyzer connects to the board's IP and pulls the live trace. Trace is enabled in `main()` only under `#if defined(DEBUG)`.
- Static network config (`Conf/CycloneTCP/host_net_config.h`): IP `192.168.1.44`, gateway `192.168.1.1`, MAC `00-AB-CD-EF-00-A2`.

## Boot / init order (`Core/Src/main.c`)

`MPU_Config()` → enable I/D-cache → `HAL_Init` → clocks → peripheral `MX_*_Init()` → `MT48LC32M16_Init()` (SDRAM) → **`vPortDefineHeapRegions(xHeapRegions)`** → `net_tcp_init("PMU")` → enable Tracealyzer → `vTaskStartScheduler()`. SDRAM must be initialized *before* the heap is defined because the heap lives in SDRAM (see below).

The CycloneTCP stack is wired up in `Device/Eth/net_config.c`: `stm32h7xxEthDriver` MAC + `lan8720PhyDriver` PHY, static IPv4. The stack uses CubeIDE-static FreeRTOS task storage (`appNetTaskStack`).

## Memory architecture (the critical big picture)

Getting placement right across the MPU, linker, and the three allocators is the central source of subtle, hard-to-debug behavior. Read these together, not in isolation:

- **MPU** (`MPU_Config()` in `main.c`): background region = no-access; `0x24000000` (RAM_D1/AXI SRAM) = cacheable write-back; `0x30000000` (RAM_D2) = **non-cacheable** (Device/normal-noncache, TEX1/shareable); `0xC0000000` (SDRAM, 64 MB) = cacheable write-back, bufferable.
- **FreeRTOS uses `heap_5`** with a single region placed in **external SDRAM at `0xC0000000`** (`xHeapRegions` in `main.c`). So `pvPortMalloc`/`vPortFree` — and therefore CycloneTCP's `osAllocMem`/`osFreeMem` (`os_port_freertos.c`) — operate on **slow 16-bit SDRAM** under scheduler suspension.
- **CycloneTCP packet buffers**: `Conf/CycloneTCP/net_config.h` selects the allocator via `NET_MEM_POOL_SUPPORT`.
  - `ENABLED` → fixed-size static pool `memPool[64][1536]` (`CycloneTCP/cyclone_tcp/core/net_mem.c`) → lands in `.bss` → **fast internal AXI SRAM**; O(1)-ish allocation under a short mutex.
  - `DISABLED` → every `NetBuffer` comes from `pvPortMalloc` → **SDRAM heap**; slower, fragmenting, jittery. This degrades TCP throughput and increases scheduler-suspend jitter, which can starve the small Tracealyzer page buffer and cause dropped trace events ("gaps") on the desktop. Prefer the pool, or give the net stack a dedicated SRAM heap region, when streaming traces.
- **Ethernet DMA**: descriptors (`.RxDescripSection`/`.TxDescripSection`) and the driver's own `txBuffer`/`rxBuffer` (`STM32H7XX_ETH_RAM_SECTION` → `.ram_no_cache`) all live in **non-cacheable RAM_D2**. The MAC driver memcpy's between `NetBuffer`s and these DMA buffers (`stm32h7xx_eth_driver.c`), so D-cache coherency for DMA is handled by placement, not by manual cache maintenance — packet payloads in cacheable SDRAM/SRAM do not corrupt over DMA.

When changing where any networking or trace data lives, verify all three layers agree (MPU attributes ↔ linker section ↔ allocator), and re-check the SDRAM-vs-internal-RAM tradeoff against trace-streaming stability.

## Layout

- `Core/` — CubeMX-generated app entry, IRQ handlers, HAL MSP, clock/MPU/peripheral init.
- `Conf/` — per-middleware config headers (`CycloneTCP/`, `FreeRTOS/`, `Tracealyzer4/`, `Ext4/`, `IEC61850/`). **Tune middleware here**, not in the library sources.
- `Device/` — board/peripheral glue: `Eth/` (CycloneTCP wiring), `SDRAM/`, `MEM/`, `SD/Ext4/`.
- `Helper/` — `debug_log`, `debug_system_info`, `Hook/` (fault hooks), `cache.h`.
- `CycloneTCP/`, `FreeRTOS/`, `Tracealyzer4/`, `Drivers/` — vendored library sources; avoid editing, change behavior via `Conf/` instead.
