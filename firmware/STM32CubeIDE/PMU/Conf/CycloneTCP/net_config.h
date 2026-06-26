
#ifndef _NET_CONFIG_H
#define _NET_CONFIG_H

#include "host_net_config.h"
#include <compiler_port.h>
#include <error.h>

/* Fixed-size packet storage used by the TCP/IP stack. */
//#define NET_MEM_POOL_SUPPORT ENABLED
#define NET_MEM_POOL_SUPPORT DISABLED
#define NET_MEM_POOL_BUFFER_COUNT 64
#define NET_MEM_POOL_BUFFER_SIZE 1536

error_t net_tcp_init(char_t* hostname);

//*** <<< Use Configuration Wizard in Context Menu >>> ***

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// <o>Network Task Priority
// <i>Network Task Priority
// <i>Default: 12
// <configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY - configLIBRARY_LOWEST_INTERRUPT_PRIORITY by FreeRTOS>
#define NET_TASK_PRIORITY 8
#define NET_TASK_STACK_SIZE 2048

// <o>Number of network adapters
// <i>Number of network adapters
// <i>Default: 1
// <1-16>
#define NET_INTERFACE_COUNT 1

#define NET_LOOPBACK_IF_SUPPORT DISABLED

// <h>Trace level

// <o>Memory Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define MEM_TRACE_LEVEL 2

// <o>NIC Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define NIC_TRACE_LEVEL 3

// <o>Ethernet Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define ETH_TRACE_LEVEL 3

// <o>ARP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define ARP_TRACE_LEVEL 3

// <o>IP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define IP_TRACE_LEVEL 3

// <o>IPv4 Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define IPV4_TRACE_LEVEL 3

// <o>IPv6 Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define IPV6_TRACE_LEVEL 0

// <o>ICMP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define ICMP_TRACE_LEVEL 3

// <o>Ping Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define PING_TRACE_LEVEL 3

// <o>IGMP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define IGMP_TRACE_LEVEL 0

// <o>ICMPv6 Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define ICMPV6_TRACE_LEVEL 0

// <o>MLD Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define MLD_TRACE_LEVEL 0

// <o>NDP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define NDP_TRACE_LEVEL 0

// <o>PPP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define PPP_TRACE_LEVEL 0

// <o>UDP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define UDP_TRACE_LEVEL 3

// <o>TCP Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define TCP_TRACE_LEVEL 3

// <o>Socket Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define SOCKET_TRACE_LEVEL 3

// <o>Raw socket Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define RAW_SOCKET_TRACE_LEVEL 0

// <o>BSD socket Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define BSD_SOCKET_TRACE_LEVEL 3

// <o>Echo Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define ECHO_TRACE_LEVEL 3

// <o>WebSocket Trace level
// <i>Set the desired debugging level
// <i>Default: Error
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define WEB_SOCKET_TRACE_LEVEL 0

// <o>Auto-IP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define AUTO_IP_TRACE_LEVEL 0

// <o>SLAAC Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define SLAAC_TRACE_LEVEL 0

// <o>DHCP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define DHCP_TRACE_LEVEL 0

// <o>DHCPv6 Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define DHCPV6_TRACE_LEVEL 0

// <o>DNS Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define DNS_TRACE_LEVEL 0

// <o>mDNS Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define MDNS_TRACE_LEVEL 0

// <o>NBNS Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define NBNS_TRACE_LEVEL 0

// <o>LLMNR Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define LLMNR_TRACE_LEVEL 0

// <o>FTP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define FTP_TRACE_LEVEL 0

// <o>HTTP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define HTTP_TRACE_LEVEL 0

// <o>MQTT Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define MQTT_TRACE_LEVEL 0

// <o>SMTP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define SMTP_TRACE_LEVEL 0

// <o>SNMP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define SNMP_TRACE_LEVEL 0

// <o>SNTP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define SNTP_TRACE_LEVEL 0

// <o>TFTP Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define TFTP_TRACE_LEVEL 0

// <o>Std Services Trace level
// <i>Set the desired debugging level
// <i>Default: Info
// <0=>Off
// <1=>Fatal
// <2=>Error
// <3=>Warning
// <4=>Info
// <5=>Debug
#define STD_SERVICES_TRACE_LEVEL 0

// </h>
// <h>Ethernet

// <o>Size of the multicast MAC filter
// <i>Maximum number of entries in the multicast MAC filter
// <i>Default: 12
// <1-1024>
#define MAC_MULTICAST_FILTER_SIZE 12

// </h>
// <h>IPv4

// <o>Size of the IPv4 multicast filter
// <i>Maximum number of entries in the IPv4 multicast filter
// <i>Default: 4
// <1-1024>
#define IPV4_MULTICAST_FILTER_SIZE 4

// <q>IPv4 fragmentation support
// <i>Enable IPv4 fragmentation and reassembly support
// <i>Default: Enabled
#define IPV4_FRAG_SUPPORT 1

// <o>Maximum number of fragmented packets
// <i>Maximum number of fragmented packets the host will accept and hold in the reassembly queue simultaneously
// <i>Default: 4
// <1-1024>
#define IPV4_MAX_FRAG_DATAGRAMS 4

// <o>Maximum datagram size
// <i>Maximum datagram size the host will accept when reassembling fragments
// <i>Default: 8192
// <576-65536>
#define IPV4_MAX_FRAG_DATAGRAM_SIZE 8192

// <o>Size of ARP cache
// <i>Size of ARP cache
// <i>Default: 8
// <1-1024>
#define ARP_CACHE_SIZE 8

// <o>Maximum number of pending packets
// <i>Maximum number of packets waiting for address resolution to complete
// <i>Default: 2
// <1-1024>
#define ARP_MAX_PENDING_PACKETS 2

// </h>
// <h>IPv6

// <o>Size of the IPv6 multicast filter
// <i>Maximum number of entries in the IPv6 multicast filter
// <i>Default: 8
// <1-1024>
#define IPV6_MULTICAST_FILTER_SIZE 8

// <q>IPv6 fragmentation support
// <i>Enable IPv6 fragmentation and reassembly support
// <i>Default: Enabled
#define IPV6_FRAG_SUPPORT 1

// <o>Maximum number of fragmented packets
// <i>Maximum number of fragmented packets the host will accept and hold in the reassembly queue simultaneously
// <i>Default: 4
// <1-1024>
#define IPV6_MAX_FRAG_DATAGRAMS 4

// <o>Maximum datagram size
// <i>Maximum datagram size the host will accept when reassembling fragments
// <i>Default: 8192
// <576-65536>
#define IPV6_MAX_FRAG_DATAGRAM_SIZE 8192

// <o>Size of the Neighbor Cache size
// <i>Size of the Neighbor Cache size
// <i>Default: 8
// <1-1024>
#define NDP_NEIGHBOR_CACHE_SIZE 8

// <o>Size of the Destination Cache size
// <i>Size of the Destination Cache size
// <i>Default: 8
// <1-1024>
#define NDP_DEST_CACHE_SIZE 8

// <o>Maximum number of pending packets
// <i>Maximum number of packets waiting for address resolution to complete
// <i>Default: 2
// <1-1024>
#define NDP_MAX_PENDING_PACKETS 2

// </h>
// <h>TCP

// <o>Default buffer size for transmission
// <i>Default buffer size for transmission
// <i>Default: 2860
// <576-65536>
#define TCP_DEFAULT_TX_BUFFER_SIZE 4096

// <o>Default buffer size for reception
// <i>Default buffer size for reception
// <i>Default: 2860
// <576-65536>
#define TCP_DEFAULT_RX_BUFFER_SIZE 2860

// <o>Default SYN queue size for listening sockets
// <i>Default SYN queue size for listening sockets
// <i>Default: 4
// <1-1024>
#define TCP_DEFAULT_SYN_QUEUE_SIZE 4

// <o>Maximum number of retransmissions
// <i>Maximum number of retransmissions
// <i>Default: 5
// <1-1024>
#define TCP_MAX_RETRIES 5

// <q>SACK support
// <i>Enable selective acknowledgment support
// <i>Default: Disabled
// Enabled: without SACK a single loss forces Go-Back-N retransmission of the
// whole window, which collapses throughput (worse with larger TX buffers).
#define TCP_SACK_SUPPORT 1

// Retransmission timeouts. Defaults (tcp.h) are 1000 ms, which turns any single
// packet loss into a ~1 s stall that overflows the trace buffer. On a LAN the
// RTT is sub-millisecond, so much shorter timeouts recover far faster.
#define TCP_INITIAL_RTO 500
#define TCP_MIN_RTO 200

// </h>
// <h>UDP

// <o>Receive queue depth for connectionless sockets
// <i>Receive queue depth for connectionless sockets
// <i>Default: 4
// <1-1024>
#define UDP_RX_QUEUE_SIZE 4

// </h>
// <h>Socket

// <o>Maximum number of sockets
// <i>Maximum number of sockets
// <i>Default: 16
// <1-1024>
//Number of sockets that can be opened simultaneously
#define SOCKET_MAX_COUNT 16

// <q>Raw socket support
// <i>Enable raw socket support
// <i>Default: Disabled
#define RAW_SOCKET_SUPPORT 0

// </h>
// <h>HTTP Server

// <q>File system support
// <i>Enable file system support
// <i>Default: Disabled
#define HTTP_SERVER_FS_SUPPORT 0

// <q>SSI support
// <i>Enable Server Side Includes support
// <i>Default: Disabled
#define HTTP_SERVER_SSI_SUPPORT 0

// <q>Basic access authentication support
// <i>Enable basic access authentication support
// <i>Default: Disabled
#define HTTP_SERVER_BASIC_AUTH_SUPPORT 0

// <q>Digest access authentication support
// <i>Enable digest access authentication support
// <i>Default: Disabled
#define HTTP_SERVER_DIGEST_AUTH_SUPPORT 0

// <q>WebSocket support
// <i>Enable WebSocket support
// <i>Default: Disabled
#define HTTP_SERVER_WEB_SOCKET_SUPPORT 0

// <o>HTTP connection timeout
// <i>HTTP connection timeout (in seconds)
// <i>Default: 10
// <1-600>
// <#*1000>
#define HTTP_SERVER_TIMEOUT 10000

// <o>HTTP idle timeout
// <i>Maximum time the server will wait for a subsequent request before closing the connection (in seconds)
// <i>Default: 5
// <1-600>
// <#*1000>
#define HTTP_SERVER_IDLE_TIMEOUT 5000

// </h>
// <h>SNMP Agent

// <q>SNMPv1 support
// <i>Enable SNMPv1 support
// <i>Default: Enabled
#define SNMP_V1_SUPPORT 1

// <q>SNMPv2 support
// <i>Enable SNMPv2 support
// <i>Default: Enabled
#define SNMP_V2_SUPPORT 1

// <q>SNMPv3 support
// <i>Enable SNMPv3 support
// <i>Default: Disabled
#define SNMP_V3_SUPPORT 0

// <o>Maximum size of SNMP messages
// <i>Maximum size of SNMP messages
// <i>Default: 1452
// <484-65535>
#define SNMP_MAX_MSG_SIZE 1452

// <o>Maximum number of MIBs
// <i>Maximum number of MIBs that can be loaded at a time
// <i>Default: 8
// <1-100>
#define SNMP_AGENT_MAX_MIBS 8

// <o>Maximum number of community strings
// <i>Maximum number of community strings
// <i>Default: 3
// <1-100>
#define SNMP_AGENT_MAX_COMMUNITIES 3

// <o>Maximum number of users
// <i>Maximum number of users
// <i>Default: 8
// <1-100>
#define SNMP_AGENT_MAX_USERS 8

// <q>VACM support
// <i>Enable VACM support
// <i>Default: Disabled
#define SNMP_AGENT_VACM_SUPPORT 0

// <o>Size of the group table
// <i>Size of the group table
// <i>Default: 8
// <1-100>
#define SNMP_AGENT_GROUP_TABLE_SIZE 8

// <o>Size of the access table
// <i>Size of the access table
// <i>Default: 8
// <1-100>
#define SNMP_AGENT_ACCESS_TABLE_SIZE 8

// <o>Size of the view table
// <i>Size of the view table
// <i>Default: 8
// <1-100>
#define SNMP_AGENT_VIEW_TABLE_SIZE 8

// </h>

//------------- <<< end of configuration section >>> -----------------------

//TCP support
#define TCP_SUPPORT ENABLED
//UDP support
#define UDP_SUPPORT ENABLED
//IPv4 support
#define IPV4_SUPPORT ENABLED
//IGMP support
#define IGMP_SUPPORT DISABLED
//DHCP client support
#define DHCP_CLIENT_SUPPORT DISABLED
//DNS client support
#define DNS_CLIENT_SUPPORT DISABLED
//SNTP client support
#define SNTP_CLIENT_SUPPORT DISABLED

//NBNS client support
#define NBNS_CLIENT_SUPPORT DISABLED
//NBNS responder support
#define NBNS_RESPONDER_SUPPORT DISABLED

#endif
