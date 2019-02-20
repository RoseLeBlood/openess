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
 * @file esp32_platform_network.cpp
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief  platform specific socket functions for platform esp32
 *
 */
 #include "config.h"
 #ifdef ESS_CONFIG_NETWORK_ESP32

#include "ess_network.h"

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

#include "esp_log.h"

/* ******************************************************************** */
int ess_socket(ess_socket_fam fam, ess_socket_pro proto, int flags, int options) {
  if(proto == ESS_SOCKET_PROTO_DRAM_LITE ) {
    return socket(ess_socket_fam2platform(fam),
                          ess_socket_pro2platform(proto) | flags,
                          options | IPPROTO_UDPLITE);
  } else {
    return socket(ess_socket_fam2platform(fam),
                          ess_socket_pro2platform(proto) | flags,
                          options);
  }
}
/* ******************************************************************** */
ess_error_t ess_socket_server_create(ess_socket_fam fam, ess_socket_pro proto,
  const std::string& host, const std::string& port, int flags, int options, int* handle) {

  int _socket, retval;
  struct addrinfo *result, *result_check, hints;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_socktype = ess_socket_pro2platform(proto);
  hints.ai_family = ess_socket_fam2platform(fam);
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol =  (proto == ESS_SOCKET_PROTO_DRAM_LITE) ? IPPROTO_UDPLITE : 0;



  if ( getaddrinfo( host.c_str(), port.c_str(), &hints, &result )  !=0  ) {
    return ESS_ERROR_GETADDR;
  }

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next )  {
    _socket = socket( result_check->ai_family, result_check->ai_socktype | flags, result_check->ai_protocol  );
    if ( _socket < 0 )  continue;

    retval = bind(_socket, result_check->ai_addr, (socklen_t)result_check->ai_addrlen );
    if ( retval != 0 )  {
      close(_socket); continue;
    } else {
      if( proto == ESS_SOCKET_PROTO_STREAM) {
          retval = listen(_socket, 128);
          if ( retval != 0 )  { close(_socket); continue;   }
      }
      break;
    }
  }
  if ( result_check == NULL )  {
    freeaddrinfo(result);
    return ESS_ERROR;
  }

  if(handle != 0) *handle = _socket;
  freeaddrinfo(result);

  ESP_LOGI("ESSS", "server creating (%s %s on %s:%s) socket: %d",  ess_socket_pro2string(proto).c_str(),
    ess_socket_fam2string(fam).c_str(),
    host.c_str(), port.c_str(), _socket
  );

  return ESS_OK;
}
/* ******************************************************************** */
ess_error_t ess_socket_connect_dram(int socket, const std::string& dsthost, const std::string& dstport) {
  if(socket < 0) return ESS_ERROR_NOT_CREATED;

  struct addrinfo *result, *result_check, hint;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);

  if (  getsockname(socket,(struct sockaddr*)&oldsockaddr, &oldsockaddrlen) == -1 )
    return ESS_ERROR;

  if ( oldsockaddrlen > sizeof(struct sockaddr_storage) )
    return ESS_ERROR;

  memset(&hint,0,sizeof(struct addrinfo));

  hint.ai_family = ((struct sockaddr_in*)&oldsockaddr)->sin_family; // AF_INET or AF_INET6 - offset is same at sockaddr_in and sockaddr_in6
  hint.ai_socktype = SOCK_DGRAM;

  if (  getaddrinfo(dsthost.c_str(), dstport.c_str(), &hint, &result) != 0)
    return ESS_ERROR_GETADDR;

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) {
    if ( ::connect(socket, result_check->ai_addr, result_check->ai_addrlen) != -1)
        break;
  }
  if ( result_check == NULL ) {
      freeaddrinfo(result);
      return ESS_ERROR_CONNECT;
  }
  freeaddrinfo(result);
  return ESS_OK;
}
/* ******************************************************************** */
ess_error_t ess_socket_disconnect(int socket) {
  struct sockaddr deconnect;

  # ifndef __FreeBSD__
  	memset(&deconnect,0,sizeof(struct sockaddr));
  	deconnect.sa_family = AF_UNSPEC;
  	if ( ::connect(socket, &deconnect,sizeof(struct sockaddr)) )
  	    return ESS_ERROR;
  # endif
  return ESS_OK;
}
/* ******************************************************************** */
unsigned int ess_send(int socket, const void* buf, unsigned int len, int flags) {
  return send(socket, buf, len, flags);
}
/* ******************************************************************** */
unsigned int ess_recv(int socket, void* buf, unsigned int len, int flags) {
  memset(buf,0,len);
  return recv(socket,buf,len,flags);
}
/* ******************************************************************** */
unsigned int ess_write (int socket, const std::string& str) {
  return write(socket, str.c_str(), str.size() );
}
/* ******************************************************************** */
unsigned int ess_cwrite (int socket, const char* str, unsigned int lenght) {
  return write(socket, str, lenght);
}
/* ******************************************************************** */
unsigned int ess_read(int socket, std::string& dest) {
  unsigned int read_bytes;
  char* buffer = new char[dest.size()];

  memset(buffer,0,dest.size());

  read_bytes = read(socket, buffer, dest.size() );
  if ( read_bytes == -1  ) {
    delete[] buffer; return -1;
  }
  if ( read_bytes < static_cast<unsigned int>(dest.size()) )
    dest.resize(read_bytes);
  dest.assign(buffer,read_bytes);
  delete[] buffer;

  return read_bytes;
}
/* ******************************************************************** */
unsigned int ess_cread(int socket, char* str) {
  memset(str, 0, strlen(str));
  return read(socket, str, strlen(str) );
}
/* ******************************************************************** */

 #endif
