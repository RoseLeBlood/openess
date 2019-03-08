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

#include "net/ess_network.h"

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
#include <netdb.h>

# include <iostream>
# include <string>
# include <string.h>
# include <memory>
#include <sstream>

#include "esp_log.h"

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

inline const char* port_tostring(int a) {
  std::ostringstream temp;
    temp<<a;
    return temp.str().c_str();
}
int ess_socket_multicast_ip6(const std::string& group, const int port, ess_socket_pro prop, bool loop) {
  if(prop != ESS_SOCKET_PROTO_DRAM_LITE || prop != ESS_SOCKET_PROTO_DRAM ) return -1;

  int sfd;
  struct in6_addr if_inaddr;
  struct ip6_addr if_ipaddr;
  struct ip6_mreq v6imreq;

  memset(&if_inaddr,0,sizeof(if_inaddr));
  memset(&if_ipaddr,0,sizeof(if_ipaddr));
  memset(&v6imreq,0,sizeof(v6imreq));

  if(ess_socket_server_create(ESS_SOCKET_FAMILY_IP6, prop, group, port, 0, 0, &sfd ) != ESS_OK) {
    return -1;
  }

  if( tcpip_adapter_get_ip6_linklocal(TCPIP_ADAPTER_IF_STA, &if_ipaddr) != ESP_OK) {
    if( tcpip_adapter_get_ip6_linklocal(TCPIP_ADAPTER_IF_AP, &if_ipaddr) != ESP_OK)  {
      close(sfd); return -1;
    }
  }

  inet6_addr_from_ip6addr(&if_inaddr, &if_ipaddr);

  // Assign the multicast source interface, via its IP
  if(setsockopt(sfd, IPPROTO_IPV6, IPV6_MULTICAST_IF, &if_inaddr, sizeof(struct in6_addr)) < 0) {
    close(sfd); return -1;
  }
  uint8_t ttl = 255;
  if(setsockopt(sfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &ttl, sizeof(uint8_t)) == -1) {
    close(sfd); return -1;
  }


   inet6_addr_from_ip6addr(&v6imreq.ipv6mr_interface, &if_ipaddr);
   if(inet6_aton(group.c_str(), &v6imreq.ipv6mr_multiaddr) != 1) {
     ESP_LOGE("IP6UDP", "Configured IPV6 multicast address '%s' is invalid.", group.c_str());
   }
   ESP_LOGI("IP6UDP", "Configured IPV6 Multicast address %s", inet6_ntoa(v6imreq.ipv6mr_multiaddr));

  ip6_addr_t multi_addr;
  inet6_addr_to_ip6addr(&multi_addr, &v6imreq.ipv6mr_multiaddr);
  if (!ip6_addr_ismulticast(&multi_addr)) {
    ESP_LOGW("IP6UDP", "Configured IPV6 multicast address '%s' is not a valid multicast address. This will probably not work.",
    group.c_str() );
  }
  if(setsockopt(sfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
                     &v6imreq, sizeof(struct ip6_mreq)) < 0) {
    close(sfd); return -1;
 }
 int only = 1;
 setsockopt(sfd, IPPROTO_IPV6, IPV6_V6ONLY, &only, sizeof(int));

  if(loop) {
    uint8_t c = 0;
    setsockopt(sfd, IPPROTO_IPV6, IP_MULTICAST_LOOP, &c, sizeof(uint8_t) );
  }
  return sfd;
}
/* ******************************************************************** */
int ess_socket_multicast_ip4(const std::string& group, const int port, ess_socket_pro prop, bool loop) {
  if(prop != ESS_SOCKET_PROTO_DRAM_LITE || prop != ESS_SOCKET_PROTO_DRAM ) return -1;

  int sfd;
  struct sockaddr_in saddr ;

  memset(&saddr,0,sizeof(saddr));

  if(ess_socket_server_create(ESS_SOCKET_FAMILY_IP4, prop, group, port, 0, 0, &sfd ) != ESS_OK) {
    return -1;
  }
  uint8_t ttl = 255;
  if(setsockopt(sfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(uint8_t)) == -1) {
    close(sfd); return -1;
  }
  if(loop) {
    int c = 0; setsockopt(sfd,IPPROTO_IP,IP_MULTICAST_LOOP,&c,4);
  }
  return sfd;
}
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
  const std::string& host, const int port, int flags, int options, int* handle) {

  int _socket, retval;
  struct addrinfo *result, *result_check, hints;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_socktype = ess_socket_pro2platform(proto);
  hints.ai_family = ess_socket_fam2platform(fam);
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol =  (proto == ESS_SOCKET_PROTO_DRAM_LITE) ? IPPROTO_UDPLITE : 0;



  if ( getaddrinfo( host.c_str(), port_tostring(port), &hints, &result )  !=0  ) {
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

  return ESS_OK;
}
/* ******************************************************************** */

int ess_accept_stream_socket(int server_socket, char* src_host, unsigned int src_host_len, int* port, int flags) {

  if(server_socket < 0) return -1;

  struct sockaddr_storage client_info;
  int client_sfd;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);
  void* addrptr;


  socklen_t addrlen = sizeof(struct sockaddr_storage);
  client_sfd = accept(server_socket, (struct sockaddr*)&client_info,&addrlen);

  if(client_sfd == -1) return -1;

  if ( src_host_len > 0)   {
    if (  getsockname(server_socket,(struct sockaddr*)&oldsockaddr,&oldsockaddrlen) == -1) return -1;
  	if ( oldsockaddrlen > sizeof(struct sockaddr_storage) )   return -1;

    if ( oldsockaddr.ss_family == AF_INET ) {
  	    addrptr = &(((struct sockaddr_in*)&client_info)->sin_addr);
  	    if(port) *port  = ntohs(((struct sockaddr_in*)&client_info)->sin_port);

        inet_ntop(AF_INET, &((in_addr*)addrptr)->s_addr , src_host, src_host_len);

  	} else if ( oldsockaddr.ss_family == AF_INET6 ) {
  	    addrptr = &(((struct sockaddr_in6*)&client_info)->sin6_addr);
  	    if(port) *port = ntohs(((struct sockaddr_in6*)&client_info)->sin6_port);

      //inet_ntop(AF_INET6, &((in_addr6*)addrptr)->s_addr , src_host, src_host_len);
  	}
  }

  return client_sfd;
}


/* ******************************************************************** */

ess_error_t ess_socket_connect_dram(int socket, const std::string& dsthost, const int dstport) {
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

  if (  getaddrinfo(dsthost.c_str(), port_tostring(dstport), &hint, &result) != 0)
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
unsigned int ess_vrecvfrom(int socket, void *buf, size_t len, int flags) {
  if ( socket == -1 ) { return -1; }
  if ( buf == NULL || len == 0) return -1;

  struct sockaddr_storage client;

  memset(buf,0,len);
  socklen_t stor_addrlen = sizeof(struct sockaddr_storage);

  return recvfrom(socket,buf,len,flags,(struct sockaddr*)&client,&stor_addrlen);
}
/* ******************************************************************** */
unsigned int ess_recvfrom(int socket, std::string& dest, int flags) {
  if ( socket == -1 ) { return -1; }

  unsigned int bytes;

  using std::unique_ptr;
  std::unique_ptr<char[]> cbuf(new char[dest.size()]);

  memset(cbuf.get(),0,dest.size());

  bytes = ess_vrecvfrom(socket, cbuf.get(),static_cast<size_t>(dest.size()), flags);

  dest.resize(bytes);
  dest.assign(cbuf.get(), bytes);

  return bytes;
}
/* ******************************************************************** */
unsigned int ess_vsendto(int socket, const void* buf, size_t len, const char* dsthost, const int dstport) {
  struct sockaddr_storage oldsock;
  struct addrinfo *result, *result_check, hint;
  socklen_t oldsocklen = sizeof(struct sockaddr_storage);
  int return_value;

  if ( socket == -1 ) { return -1; }

  if (  getsockname(socket,(struct sockaddr*)&oldsock,(socklen_t*)&oldsocklen) == -1)  return -1;
  memset(&hint,0,sizeof(struct addrinfo));

  hint.ai_family = oldsock.ss_family;
  hint.ai_socktype = SOCK_DGRAM;

  if (  getaddrinfo(dsthost, port_tostring(dstport), &hint, &result) != 0 ) return -1;

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next )  {

    return_value =  sendto(socket, buf, len, 0, result_check->ai_addr, result_check->ai_addrlen);

    if(return_value != -1) break;
  }
  freeaddrinfo(result);
  return return_value;
}
/* ******************************************************************** */
int ess_setsockopt(int socket, int level, int optname, const char* optval, unsigned int optlen) {
  return setsockopt(socket, level, optname, optval, optlen);
}

 #endif