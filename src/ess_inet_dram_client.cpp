/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file ess_inet_dram_client.cpp
 * @author Anna Sopdia Schröck
 * @date 19 Februar 2019
 * @brief Contains the inet dram client (UDP Server) socket
 */
#include "ess_inet_dram_client.h"

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <stdint.h>
# include <netdb.h> // getaddrinfo()
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <netinet/in.h>

ess_inet_dram_client::ess_inet_dram_client(ess_socket_fam fam, int flags, bool lite)
  : ess_insocket_dram(fam), m_isConnected(false) {

  int proto = lite ? IPPROTO_UDPLITE : 0;
  switch ( fam ) {
    case ESS_SOCKET_FAMILY_IP4 : m_iSocket = socket(AF_INET,SOCK_DGRAM|flags, proto); break;
    case ESS_SOCKET_FAMILY_IP6 : m_iSocket = socket(AF_INET6,SOCK_DGRAM|flags,proto); break;
    case ESS_SOCKET_FAMILY_BOTH:  m_iSocket = socket(AF_UNSPEC,SOCK_DGRAM|flags,proto); break;
    default: m_iSocket = -1;
  }
}
/**
 * @brief Connect datagram socket.
 *
 * Connect a datagram socket to a remote peer so only its packets are received
 * and all data written is sent to it.
 *
 * @param dsthost destination host
 * @param dstport destination port
 */
ess_error_t ess_inet_dram_client::connect(const std::string& dsthost, const std::string& dstport) {
  if(m_iSocket < 0) return ESS_ERROR_NOT_CREATED;

  struct addrinfo *result, *result_check, hint;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);

  if (  getsockname(m_iSocket,(struct sockaddr*)&oldsockaddr, &oldsockaddrlen) == -1 )
    return ESS_ERROR;

  if ( oldsockaddrlen > sizeof(struct sockaddr_storage) )
    return ESS_ERROR;

  memset(&hint,0,sizeof(struct addrinfo));

  hint.ai_family = ((struct sockaddr_in*)&oldsockaddr)->sin_family; // AF_INET or AF_INET6 - offset is same at sockaddr_in and sockaddr_in6
  hint.ai_socktype = SOCK_DGRAM;

  if (  getaddrinfo(dsthost.c_str(), dstport.c_str(), &hint, &result) != 0)
    return ESS_ERROR_GETADDR;

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) {
    if ( ::connect(m_iSocket, result_check->ai_addr, result_check->ai_addrlen) != -1)
        break;
  }
  if ( result_check == NULL ) {
      freeaddrinfo(result);
      return ESS_ERROR_CONNECT;
  }

  m_strHost = dsthost;
  m_strPort = dstport;
  m_isConnected = true;

  return ESS_OK;
}

/*
 * @brief Break association to host. Does not close the socket.
 *
 */
ess_error_t ess_inet_dram_client::disconnect(void) {
  struct sockaddr deconnect;

  # ifndef __FreeBSD__
  	memset(&deconnect,0,sizeof(struct sockaddr));
  	deconnect.sa_family = AF_UNSPEC;
  	if ( ::connect(m_iSocket, &deconnect,sizeof(struct sockaddr)) )
  	    return ESS_ERROR;
  # endif

  m_strHost.clear();
  m_strPort.clear();
  m_isConnected = false;

  return ESS_OK;
}

/**
 * @brief Send data to connected socket
 *
 * @param buf pointer to the data
 * @param len the length of the buffer
 * @param flags flags for `send(2)`
 *
 * @retval n *n* bytes were sent
 * @retval <0 Something went wrong.
 */
unsigned int ess_inet_dram_client::write(const void* buf, unsigned int len, int flags) {
  if ( m_isConnected != true ) return -1;
  return send(m_iSocket,buf,len,flags);
}
/**
 * @brief Receive data from a connected DGRAM socket
 *
 * If a datagram socket is connected, this function may be called to receive data sent from
 * the host connected to.
 *
 * @param buf Area to write the data to
 * @param len How many data we want to receive
 * @param flags Flags to be passed to `recv(2)`
 *
 * @retval >0 n bytes were received.
 * @retval 0 no data were received.
 * @retval -1 Something went wrong.
 */
unsigned int ess_inet_dram_client::read(void* buf, unsigned int len, int flags) {
  if ( m_isConnected != true ) return -1;
  memset(buf,0,len);
  return recv(m_iSocket,buf,len,flags);
}


/**
 * @brief send data to connected peer
 * @code
 * socket << "Hallo Welt";
 * @endcode
 */
ess_inet_dram_client& operator<< (ess_inet_dram_client& sock, const std::string& str) {
  if ( sock.m_isConnected != true ) return sock;
  write(sock.m_iSocket, str.c_str(), str.size() );
  return sock;
}
/**
 * @brief send data to connected peer
 * @code
 * socket << "Hallo Welt";
 * @endcode
 */
ess_inet_dram_client& operator<<(ess_inet_dram_client& sock, const char* str) {
  if ( sock.m_isConnected != true ) return sock;
  write(sock.m_iSocket, str, strlen(str) );
  return sock;
}

/**
 * @brief Receive data from connected datagram socket
 *
 * If a datagram socket is connected, you may receive data from it using stream-like functions.
 *
 * @param sock The socket to receive data from
 * @param dest The string to write data to. This string has to be resized to the number of bytes you wish to receive.
 */
ess_inet_dram_client& operator>>(ess_inet_dram_client& sock, std::string& dest) {
  unsigned int read_bytes;
  char* buffer = new char[dest.size()];

  memset(buffer,0,dest.size());

  read_bytes = read(sock.m_iSocket, buffer, dest.size() );
  if ( read_bytes == -1  ) {
    delete[] buffer; return sock;
  }
  if ( read_bytes < static_cast<unsigned int>(dest.size()) )
    dest.resize(read_bytes);
  dest.assign(buffer,read_bytes);
  delete[] buffer;

  return sock;
}
ess_inet_dram_client& operator>>(ess_inet_dram_client& sock, char* dest) {
  memset(dest, 0, strlen(dest));
  read(sock.m_iSocket, dest, strlen(dest) );
  return sock;
}
