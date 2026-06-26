/*******************************************************************************
 * Trace Recorder Library for Tracealyzer v4.3.5
 * Percepio AB, www.percepio.com
 *
 * trcStreamingPort.c
 *
 * Supporting functions for trace streaming, used by the "stream ports" 
 * for reading and writing data to the interface.
 * Existing ports can easily be modified to fit another setup, e.g., a 
 * different TCP/IP stack, or to define your own stream port.
 *
 * Terms of Use
 * This file is part of the trace recorder library (RECORDER), which is the 
 * intellectual property of Percepio AB (PERCEPIO) and provided under a
 * license as follows.
 * The RECORDER may be used free of charge for the purpose of recording data
 * intended for analysis in PERCEPIO products. It may not be used or modified
 * for other purposes without explicit permission from PERCEPIO.
 * You may distribute the RECORDER in its original source code form, assuming
 * this text (terms of use, disclaimer, copyright notice) is unchanged. You are
 * allowed to distribute the RECORDER with minor modifications intended for
 * configuration or porting of the RECORDER, e.g., to allow using it on a 
 * specific processor, processor family or with a specific communication
 * interface. Any such modifications should be documented directly below
 * this comment block.  
 *
 * Disclaimer
 * The RECORDER is being delivered to you AS IS and PERCEPIO makes no warranty
 * as to its use or performance. PERCEPIO does not and cannot warrant the 
 * performance or results you may obtain by using the RECORDER or documentation.
 * PERCEPIO make no warranties, express or implied, as to noninfringement of
 * third party rights, merchantability, or fitness for any particular purpose.
 * In no event will PERCEPIO, its technology partners, or distributors be liable
 * to you for any consequential, incidental or special damages, including any
 * lost profits or lost savings, even if a representative of PERCEPIO has been
 * advised of the possibility of such damages, or for any claim by any third
 * party. Some jurisdictions do not allow the exclusion or limitation of
 * incidental, consequential or special damages, or the exclusion of implied
 * warranties or limitations on how long an implied warranty may last, so the
 * above limitations may not apply to you.
 *
 * Tabs are used for indent in this file (1 tab = 4 spaces)
 *
 * Copyright Percepio AB, 2018.
 * www.percepio.com
 ******************************************************************************/

/*******************************************************************************
 * PORT MODIFICATIONS (PMU project)
 *
 * This stream port is adapted to the CycloneTCP BSD socket API (instead of the
 * lwIP reference implementation shipped by Percepio). The trace is streamed to
 * the desktop Tracealyzer over TCP on port TRC_TCPIP_PORT (12000): the target
 * acts as the listening server, the desktop connects and pulls the live trace.
 *
 * The accepted client socket is configured for low-latency, bounded-blocking
 * streaming (see trcSocketAccept):
 *   - SO_SNDTIMEO is set to the trace control task delay, so trcSocketSend()
 *     blocks at most one control cycle when the TX window is full and then
 *     reports "nothing sent yet" instead of busy-spinning.
 *   - TCP_NODELAY disables Nagle. Trace pages are small (<=500 bytes) and
 *     latency-sensitive; Nagle combined with the host's delayed-ACK otherwise
 *     introduces ~40 ms stalls that overflow the recorder's page buffer and
 *     produce gaps in the timeline.
 *
 * The remaining streaming stability comes from CycloneTCP / Tracealyzer config
 * defines (SACK, RTO, TX buffer size, TzCtrl priority) - see Conf/. The root
 * cause analysis is documented in NOTES.md.
 ******************************************************************************/

#include "trcRecorder.h"

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)  
#if (TRC_USE_TRACEALYZER_RECORDER == 1)
	
/* TCP/IP includes - for lwIP in this case */
#include "core/net.h"
#include "core/bsd_socket.h"
#include "core/socket.h"
#include "cpu_endian.h"

int errno;

#define TRC_TCPIP_PORT 12000

static char is_inited = 0;

int_t sock = -1, new_sd = -1;
int remoteSize;
struct sockaddr_in address, remote;

int32_t trcSocketSend( void* data, int32_t size, int32_t* bytesWritten )
{
  if (new_sd < 0)
    return -1;
  
  if (bytesWritten == NULL)
	return -1;

  Socket* sock = &socketTable[new_sd];

  /* Blocking send, bounded by the SO_SNDTIMEO set in trcSocketAccept(). When
     the TX window is momentarily full the call blocks for up to one control
     task cycle, then returns SOCKET_ERROR with EWOULDBLOCK. */
  *bytesWritten = send( new_sd, data, size, 0 );

  if (*bytesWritten > 0)
    return 0;

  if (*bytesWritten == SOCKET_ERROR) {
    if (sock->errnoCode == EWOULDBLOCK) {
      /* Timed out with the peer still alive but slow: report zero bytes so the
         recorder retries the same page on the next cycle. Not a fatal error. */
      *bytesWritten = 0;
      return 0;
    }
  }

  /* Any other error means the connection is broken: drop the client socket so
     trcSocketAccept() can take a fresh connection. */
  closesocket(new_sd);
  new_sd = -1;
  errno = -1;
  *bytesWritten = 0;
  return -1;
}

int32_t trcSocketReceive( void* data, int32_t size, int32_t* bytesRead )
{
  if (new_sd < 0)
    return -1;

  Socket* sock = &socketTable[new_sd];

  *bytesRead = recv(new_sd, data, size, MSG_DONTWAIT);

  if (*bytesRead>0)
	  return 0;

  if (*bytesRead==SOCKET_ERROR){
	  if (sock->errnoCode==0 || sock->errnoCode == EWOULDBLOCK) {
		  *bytesRead = 0;
		  return 0;
	  }
  }

  closesocket(new_sd);
  new_sd = -1;
  errno = -1;
  *bytesRead = 0;
  return -1;
}

int32_t trcSocketInitializeListener()
{
  if (sock >= 0)
	return 0;
  
  errno = 0;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0)
    return -1;

  address.sin_family = AF_INET;
  address.sin_port = htons( TRC_TCPIP_PORT );
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
  {
    closesocket(sock);
    sock = -1;
    return -1;
  }

  if (listen(sock, 5) < 0)
  {
    closesocket(sock);
    sock = -1;
    return -1;
  }

  return 0;
}

int32_t trcSocketAccept()
{
  struct timeval sendTimeout;
  uint32_t sendTimeoutMs;
  if (sock < 0)
      return -1;
  
  if (new_sd >= 0)
      return 0;
  
  remoteSize = sizeof( remote );
  new_sd = accept( sock, (struct sockaddr *)&remote, (socklen_t*)&remoteSize );

  if( new_sd < 0 )
  {
   	closesocket(new_sd);
    new_sd = -1;
    return -1;
  }

  sendTimeoutMs = (TRC_CFG_CTRL_TASK_DELAY > 0) ? TRC_CFG_CTRL_TASK_DELAY : 1;
  sendTimeout.tv_sec = sendTimeoutMs / 1000;
  sendTimeout.tv_usec = (sendTimeoutMs % 1000) * 1000;

  if (setsockopt(new_sd, SOL_SOCKET, SO_SNDTIMEO, &sendTimeout,
      sizeof(sendTimeout)) == SOCKET_ERROR)
  {
    closesocket(new_sd);
    new_sd = -1;
    return -1;
  }

  /* Disable Nagle on the trace socket. Trace pages are small (<=500 bytes) and
     latency-sensitive; Nagle + the host's delayed-ACK introduce ~40 ms stalls
     that overflow the recorder's page buffer and cause gaps in the timeline. */
  {
    int tcpNoDelay = 1;
    if (setsockopt(new_sd, IPPROTO_TCP, TCP_NODELAY, &tcpNoDelay,
        sizeof(tcpNoDelay)) == SOCKET_ERROR)
    {
      closesocket(new_sd);
      new_sd = -1;
      return -1;
    }
  }

  if (is_inited == 1) {
	  TRC_STREAM_PORT_INIT();
  }
  else {
	  is_inited = 1;
  }

  return 0;
}
/************** MODIFY THE ABOVE PART TO USE YOUR TPC/IP STACK ****************/

int32_t trcTcpWrite(void* data, uint32_t size, int32_t *ptrBytesWritten)
{
    return trcSocketSend(data, size, ptrBytesWritten);
}

int32_t trcTcpRead(void* data, uint32_t size, int32_t *ptrBytesRead)
{
    trcSocketInitializeListener();
        
    trcSocketAccept();
      
    return trcSocketReceive(data, size, ptrBytesRead);
}

#endif /*(TRC_USE_TRACEALYZER_RECORDER == 1)*/
#endif /*(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)*/
