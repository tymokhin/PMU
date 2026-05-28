/*
 * retarget_io.c
 *
 *  Created on: 24 квіт. 2020 р.
 *      Author: timohin
 */

#include "main.h"
#include <stdio.h>
#include <stdint.h>

volatile int32_t ITM_RxBuffer=ITM_RXBUFFER_EMPTY; // Initialize as EMPTY

int32_t __io_putchar (int32_t ch) {
    return ITM_SendChar(ch);
}

int32_t __io_getchar (void) {
  return ITM_ReceiveChar();
}
