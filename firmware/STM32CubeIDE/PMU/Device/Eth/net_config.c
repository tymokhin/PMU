#include "host_net_config.h"

#include <error.h>

#include <core/net.h>
#include <drivers/mac/stm32h7xx_eth_driver.h>
#include <drivers/phy/lan8720_driver.h>

#define ethNicDriver stm32h7xxEthDriver
#define ethPhyDriver lan8720PhyDriver

static StaticTask_t appNetTaskTcb;
static StackType_t appNetTaskStack[NET_TASK_STACK_SIZE];

static error_t ip_config_manual(const char_t *ip, const char_t *mask,
	const char_t *gateway);

static NetContext appNetContext;
static NetInterface appNetInterfaces[NET_INTERFACE_COUNT];
static bool_t appNetStackInitialized = FALSE;
static error_t net_tcp_stack_init(void)
{
	NetSettings settings;
	error_t e;

	if(appNetStackInitialized)
	{
		return NO_ERROR;
	}

	netGetDefaultSettings(&settings);
	settings.interfaces = appNetInterfaces;
	settings.numInterfaces = NET_INTERFACE_COUNT;

	settings.task.tcb = &appNetTaskTcb;
	settings.task.stack = appNetTaskStack;
	settings.task.stackSize = NET_TASK_STACK_SIZE;

	e = netInit(&appNetContext, &settings);
	if(e)
	{
		return e;
	}

	e = netStart(&appNetContext);
	if(e)
	{
		return e;
	}

	appNetStackInitialized = TRUE;
	return NO_ERROR;
}

error_t net_tcp_init(char_t *hostname)
{
	NetInterface *interface;
	MacAddr macAddr;
	error_t e = net_tcp_stack_init();

	if(e)
	{
		return e;
	}
	//Configure the first Ethernet interface
	interface = netGetDefaultInterface(&appNetContext);
	//Set interface name
	netSetInterfaceName(interface, "eth0");
	//Select the relevant network adapter
	netSetDriver(interface, &ethNicDriver);
	netSetPhyDriver(interface, &ethPhyDriver);
	//Set host name
	netSetHostname(interface, hostname);
	//Set host MAC address
	macStringToAddr(APP_MAC_ADDR, &macAddr);
	netSetMacAddr(interface, &macAddr);
	e = netConfigInterface(interface);

	if(e)
	{
		return e;
	}

	return ip_config_manual(APP_IPV4_HOST_ADDR, APP_IPV4_SUBNET_MASK,
		APP_IPV4_DEFAULT_GATEWAY);
}

static error_t ip_config_manual(const char_t *ip, const char_t *mask,
	const char_t *gateway)
{
	NetInterface *interface;
	Ipv4Addr ipv4Addr;
	
	interface = netGetDefaultInterface(&appNetContext);
	
	//Set IPv4 host address
	ipv4StringToAddr(ip, &ipv4Addr);
	ipv4SetHostAddr(interface, ipv4Addr);

	//Set subnet mask
	ipv4StringToAddr(mask, &ipv4Addr);
	ipv4SetSubnetMask(interface, ipv4Addr);

	//Set default gateway
	ipv4StringToAddr(gateway, &ipv4Addr);
	ipv4SetDefaultGateway(interface, ipv4Addr);
	
	return NO_ERROR;
}
