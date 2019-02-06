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
 * @file backend.h
 * @author Anna Sopdia Schröck
 * @date 2 Februar 20119
 * @brief Contains all ess socket functions. source
 * It contains all functions used to work with INET and INET6 sockets, both TCP, UDP, UDP lite
 *
 *
 */
#include "ess_socket.h"
#include "esp_log.h"

#include "config.h"

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h> // read()/write()
# include <stdint.h>
# include <netdb.h> // getaddrinfo()
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <netinet/in.h> // e.g. struct sockaddr_in on create_serverBSD

ess_socket_fam_t ess_get_address_family(const char* hostname) {
  ess_socket_fam_t return_value = -1;
  struct addrinfo hint, *result;
  int af = -1;

  if ( hostname == NULL ) return -1;
  memset(&hint,0,sizeof hint);
  hint.ai_family = AF_UNSPEC;

  if ( 0 != (return_value = getaddrinfo(hostname,"0",&hint,&result)))   return -1;
  if ( result == NULL ) return -1;

  switch (result->ai_family) {
    case AF_INET:   af = ESS_SOCKET_FAMILY_IP4; break;
    case AF_INET6: af= ESS_SOCKET_FAMILY_IP6; break;
  };
  return af;
}
ess_socket_error_t ess_socket_create_server( ess_socket_fam_t fam, ess_socket_pro_t protokoll,
                                                             const char* hostname, unsigned short port, ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  _socket->family = fam;
  _socket->protokol = protokoll;
  _socket->port = port;
  _socket->status = ESS_SOCKET_STATUS_CREATED;
  strncpy(_socket->hostname, hostname, strlen(hostname));
  _socket->hostname_len = strlen(hostname);

  if(_socket->status != ESS_SOCKET_STATUS_CREATED || _socket->status == ESS_SOCKET_STATUS_STOPPED)
    return ESS_SOCKET_ERROR_UNSPEC;

  struct addrinfo *result, *result_check, hints;
  memset(&hints,0,sizeof(struct addrinfo));

  switch(_socket->protokol) {
    case ESS_SOCKET_PROTO_STREAM:  hints.ai_socktype = SOCK_STREAM;  break;
    case ESS_SOCKET_PROTO_DRAM:  hints.ai_socktype = SOCK_DGRAM; break;
    case ESS_SOCKET_PROTO_DRAM_LITE:  hints.ai_socktype = SOCK_DGRAM;  hints.ai_protocol = IPPROTO_UDPLITE; break;
    default: _socket->status = ESS_SOCKET_STATUS_ERROR; return ESS_SOCKET_ERROR_UNSPEC_PROTOKOL;
  };
  switch ( _socket->family ) {
    case ESS_SOCKET_FAMILY_IP4: hints.ai_family = AF_INET; break;
    case ESS_SOCKET_FAMILY_IP6: hints.ai_family = AF_INET6; break;
    case ESS_SOCKET_FAMILY_BOTH: hints.ai_family = AF_UNSPEC; break;
    default: _socket->status = ESS_SOCKET_STATUS_ERROR; return ESS_SOCKET_ERROR_UNSPEC_FAMILY;
  }
  hints.ai_flags = AI_PASSIVE;

  char buffer[8]; buffer[0] = '\0'; buffer[0] = '\0';
  snprintf(buffer, 8,"%d",_socket->port) ;
  if (  (_socket->retval = getaddrinfo(_socket->hostname, buffer ,&hints,&result)) != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_GETADDR;
  }

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) {
    _socket->socket = socket(result_check->ai_family, result_check->ai_socktype, result_check->ai_protocol);
    if ( _socket->socket < 0 )  continue;
    if (  (_socket->retval  = bind(_socket->socket, result_check->ai_addr,(socklen_t)result_check->ai_addrlen)) != 0 ) {
      close(_socket->socket); continue;
    }
    if (_socket->protokol == ESS_SOCKET_PROTO_STREAM) {
  	    if (  (_socket->retval  = listen(_socket->socket, 128)) == 0) {
          break;
        } else {
          close(_socket->socket);
        }
    }
  }
  if ( result_check == NULL ) {
    freeaddrinfo(result);
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_BIND;
  }
  freeaddrinfo(result);

  _socket->status = ESS_SOCKET_STATUS_LISTEN;
  return ESS_SOCKET_ERROR_OK;
}

ess_socket_error_t ess_socket_close(ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  if (  (_socket->retval  = close(_socket->socket))  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }
  return ESS_SOCKET_ERROR_OK;
}

ess_socket_error_t ess_socket_end_write(ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  if (  (_socket->retval  = shutdown(_socket->socket,  SHUT_WR) )  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }
  return ESS_SOCKET_ERROR_OK;

  if (  (_socket->retval  = shutdown(_socket->socket,  SHUT_WR) )  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }
}

ess_socket_error_t ess_socket_end_read(ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  if (  (_socket->retval  = shutdown(_socket->socket,  SHUT_RD) )  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }
  return ESS_SOCKET_ERROR_OK;
}

ess_socket_error_t ess_socket_end(ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  if (  (_socket->retval  = shutdown(_socket->socket,  SHUT_RD) )  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }
  if (  (_socket->retval  = shutdown(_socket->socket,  SHUT_WR) )  != 0 ) {
    _socket->status = ESS_SOCKET_STATUS_ERROR;
    return ESS_SOCKET_ERROR_CLOSE;
  }

  return ESS_SOCKET_ERROR_OK;
}

ess_socket_t* ess_socket_accept(ess_socket_t* server_socket, ess_socket_error_t* error_code) {
  if(server_socket == 0) { if(error_code != 0) *error_code = ESS_SOCKET_ERROR_NULL; return 0; }

  ess_socket_t *client_socket;
  int  nbl = 0;
  struct sockaddr_in incoming;
  struct sockaddr_in6 incoming6;
  unsigned int size_in6 = sizeof(struct sockaddr_in6);
  unsigned int size_in = sizeof(struct sockaddr_in);

  //socklen_t addrlen = sizeof(struct sockaddr_storage);


  client_socket = (ess_socket_t*)malloc(sizeof(ess_socket_t));
  if(client_socket == 0) return 0;

  client_socket->hostname_len = INET6_ADDRSTRLEN;

  if(server_socket->family == ESS_SOCKET_FAMILY_IP4) {

    if ( (client_socket->socket = accept(server_socket->socket, (struct sockaddr*)&incoming, (socklen_t *) &size_in)) != 0) {
      if(error_code != 0) *error_code = ESS_SOCKET_ERROR_NULL; return 0;
    }

    if(server_socket->protokol == ESS_SOCKET_PROTO_STREAM) {
      server_socket->port  = ntohs( incoming.sin_port );
		  long addr = ntohl( incoming.sin_addr.s_addr );

      snprintf(client_socket->hostname,  client_socket->hostname_len, "%03u.%03u.%03u.%03u",
        (unsigned int) addr >> 24,  (unsigned int) (addr >> 16) % 256,  (unsigned int) (addr >> 8) % 256,
        (unsigned int) addr % 256 );
      client_socket->hostname_len = strlen(client_socket->hostname);
    }

  } else {

    if ( (client_socket->socket = accept( server_socket->socket,(struct sockaddr *)&incoming6, (socklen_t *) &size_in6 )) != 0) {
      if(error_code != 0) *error_code = ESS_SOCKET_ERROR_NULL;
      return 0;
    }

    char addrbuf[INET6_ADDRSTRLEN];
    addrbuf[0] = '\0';

    client_socket->port = ntohs( incoming6.sin6_port );

    if ( inet_ntop( AF_INET6, &(incoming6.sin6_addr), addrbuf, sizeof(addrbuf) )) {
      ESP_LOGI("EssS", "client from :%s/%d", addrbuf, client_socket->port);
      strncpy(client_socket->hostname,  addrbuf,  strlen(addrbuf) );
    }
  }

  if ( ioctl( client_socket->socket , FIONBIO, &nbl ) < 0 ) {
    ESP_LOGE("EssS", "(%02d) couldn't turn on blocking for client",  client_socket->socket );
    client_socket->status = ESS_SOCKET_STATUS_ERROR;
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_NULL; return 0; }

    close(client_socket->socket);
  }
  return client_socket;
}
ess_socket_error_t ess_socket_set_buffer(ess_socket_t* _socket,  unsigned int rec_buffer_size,  unsigned int send_buffer_size) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;

  setsockopt( _socket->socket, SOL_SOCKET, SO_SNDBUF, &send_buffer_size, sizeof( send_buffer_size ) );
  setsockopt( _socket->socket, SOL_SOCKET, SO_RCVBUF, &rec_buffer_size, sizeof( rec_buffer_size ) );

  return ESS_SOCKET_ERROR_OK;
}
ess_socket_t* ess_socket_connect_stream(const char* hostname, int port, ess_socket_fam_t family, int flags, ess_socket_error_t* error_code)  {
  if(hostname == NULL) { if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_NULL; } return 0; }

  int sfd;
  struct addrinfo hint, *result, *result_check;
  ess_socket_t* new_socket;
  char buffer[8]; buffer[0] = '\0';

  memset(&hint,0,sizeof hint);

  switch ( family ) {
    case ESS_SOCKET_FAMILY_IP4: hint.ai_family = AF_INET; break;
    case ESS_SOCKET_FAMILY_IP6: hint.ai_family = AF_INET6; break;
    default: hint.ai_family = AF_UNSPEC;
  }


  hint.ai_socktype = SOCK_STREAM;


  snprintf(buffer, 8,"%d",port) ;

  if (   getaddrinfo(hostname,buffer,&hint,&result) != 0) {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_GETADDR; }
    return 0;
  }

  for ( result_check = result; result_check != 0; result_check = result_check->ai_next )  { // go through the linked list of struct addrinfo elements
      sfd = socket(result_check->ai_family, result_check->ai_socktype | flags, result_check->ai_protocol);

      if ( sfd < 0 )  continue;

      if (  connect(sfd,result_check->ai_addr,result_check->ai_addrlen)  != -1) // connected without error
        break;
        close(sfd);
  }
  freeaddrinfo(result);

  if ( result_check == 0 ) {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_GETADDR; }
    return 0;
  }
  // Yes :)
  new_socket = (ess_socket_t*)malloc(sizeof(ess_socket_t));
  if(new_socket == 0) {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_OUTOF_MEM; }
    return 0;
  }
  new_socket->socket = sfd;

  strncpy(new_socket->hostname, hostname, strlen(hostname));

  new_socket->port = port;
  new_socket->family = family;
  new_socket->protokol = ESS_SOCKET_PROTO_STREAM;

  return new_socket;
}
ess_socket_t* ess_socket_create_dram(ess_socket_fam_t  fam, ess_socket_pro_t proto, int flags, ess_socket_error_t* error_code) {
  int sfd;
  int _proto;

  if (fam != ESS_SOCKET_FAMILY_IP6 && fam != ESS_SOCKET_FAMILY_IP4)   {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_UNSPEC_FAMILY; }
    return 0;
  }
  if(proto == ESS_SOCKET_PROTO_DRAM_LITE) {
    _proto = IPPROTO_UDPLITE;
  } else if(proto == ESS_SOCKET_PROTO_DRAM) {
    _proto  = 0;
  } else {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_UNSPEC_PROTOKOL; }
    return 0;
  }

  switch ( proto )
  {
  case ESS_SOCKET_FAMILY_IP4 :
    sfd = socket(AF_INET,SOCK_DGRAM|flags,_proto);
    break;
  case ESS_SOCKET_FAMILY_IP6 :
    sfd = socket(AF_INET6,SOCK_DGRAM|flags,_proto);
    break;
  default:
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_UNSPEC_FAMILY; }
    return 0;
  }

  if ( -1 == sfd ) {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_CONNECT; }
    return 0;
  }
  ess_socket_t*  new_socket = (ess_socket_t*)malloc(sizeof(ess_socket_t));
  if(new_socket == 0) {
    if(error_code != 0) { *error_code = ESS_SOCKET_ERROR_OUTOF_MEM; }
    return 0;
  }
  new_socket->socket = sfd;
  new_socket->family = fam;
  new_socket->protokol = proto;

  return new_socket;
}

ess_socket_error_t ess_socket_connect_dram(ess_socket_t* _socket, const char* host, int port)  {

  struct addrinfo *result, *result_check, hint;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);
  char buffer[8]; buffer[0] = '\0';


  snprintf(buffer, 8,"%d",port) ;

  if ( host == NULL ) {
    return 0;
  }

  //TODO: Create new ERROR Codes

  if ( -1 == getsockname(_socket->socket,(struct sockaddr*)&oldsockaddr,&oldsockaddrlen) ){
    return ESS_SOCKET_ERROR_UNSPEC;
  }

  if ( oldsockaddrlen > sizeof(struct sockaddr_storage) ) {
    return ESS_SOCKET_ERROR_UNSPEC;
  }

  memset(&hint,0,sizeof(struct addrinfo));

  hint.ai_family = ((struct sockaddr_in*)&oldsockaddr)->sin_family; // AF_INET or AF_INET6 - offset is same at sockaddr_in and sockaddr_in6

  hint.ai_socktype =  SOCK_DGRAM;

  if (  getaddrinfo(host,buffer,&hint,&result) != 0) {
    return ESS_SOCKET_ERROR_GETADDR;
  }

  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) { // go through the linked list of struct addrinfo elements
    if (  connect(_socket->socket,result_check->ai_addr,result_check->ai_addrlen) != -1) // connected without error
        break;

    if ( result_check == 0 ) {
      return ESS_SOCKET_ERROR_CONNECT;
    }
  }
  freeaddrinfo(result);

  _socket->hostname_len = strlen(host);
  strncpy(_socket->hostname, host, _socket->hostname_len);
  _socket->port = port;

  return ESS_SOCKET_ERROR_OK;
}
int ess_socket_write_dram(ess_socket_t* _socket, const void* buf, unsigned int size,
  const char* host, int port, int sendto_flags) {

  struct sockaddr_storage oldsock;
  struct addrinfo *result, *result_check, hint;
  socklen_t oldsocklen = sizeof(struct sockaddr_storage);
  int return_value;
  char buffer[8]; buffer[0] = '\0';
  snprintf(buffer, 8, "%d", port);

  if(buf == 0) return 0;

  if (_socket == 0  || port == 0  || host == NULL)   {
    return ESS_SOCKET_ERROR_NULL;
  }
  if (  getsockname(_socket->socket, (struct sockaddr*)&oldsock,(socklen_t*)&oldsocklen) == -1 ){
    return ESS_SOCKET_ERROR_UNSPEC;
  }
  hint.ai_family = oldsock.ss_family;
  hint.ai_socktype = SOCK_DGRAM;

  if ( getaddrinfo(host,buffer,&hint,&result) != 0){
    return ESS_SOCKET_ERROR_UNSPEC;
  }
  for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) { // go through the linked list of struct addrinfo elements
    if (  (return_value = sendto(_socket->socket,buf,size,sendto_flags,result_check->ai_addr,result_check->ai_addrlen)) != -1) // connected without error
      break;
  }
  freeaddrinfo(result);

  return return_value;
}
ess_socket_error_t ess_socket_read_dram(ess_socket_t* socket, void* buf, unsigned int size, char* src_host,
  unsigned int src_host_len,  int src_port, unsigned int src_service_len, int recvfrom_flags, int numeric) {

  struct sockaddr_storage client;
  ssize_t bytes;
  int retval;

  char buffer[8]; buffer[0] = '\0';
  snprintf(buffer, 8, "%d", src_port);

  if(buf == 0 || size == 0) return 0;

  if (_socket == 0 )   {
    return ESS_SOCKET_ERROR_NULL;
  }
  memset(buffer,0,size);
  if ( src_host ) memset(src_host,0,src_host_len);

  socklen_t stor_addrlen = sizeof(struct sockaddr_storage);

  if ( bytes = recvfrom(socket->socket, buffer,size,recvfrom_flags,(struct sockaddr*)&client,&stor_addrlen) == -1)
    return ESS_SOCKET_ERROR_UNSPEC;

  return bytes;
}

ess_socket_error_t ess_socket_read(ess_socket_t* socket, void* buffer, unsigned int size, int* readed) {
  int readed_g = 0;
  
  if(buffer == 0) { if(readed) *readed = 0; return ESS_SOCKET_ERROR_NULL; }

  if (_socket == 0)   {
    return ESS_SOCKET_ERROR_NULL; if(readed) *readed = 0;
  }
  readed_g = read(socket->socket, buffer, size);
  if(readed_g > 0) {
  	return ESS_SOCKET_ERROR_UNSPEC; if(readed) *readed = 0;
  }
  if(readed) {
    *readed = readed_g;
  return ESS_SOCKET_ERROR_OK;
}
ess_socket_error_t ess_socket_write(ess_socket_t* socket, const void* buffer, unsigned int size, unsigned int* wrote) {
  int wrote_g = 0;
  
  if(buffer == 0) { if(wrote) *wrote = 0; return ESS_SOCKET_ERROR_NULL; }

  if (_socket == 0)   {
    return ESS_SOCKET_ERROR_NULL; if(wrote) *wrote = 0;
  }
  wrote_g = write(socket->socket, buffer, size);
  if(readed_g > 0) {
  	return ESS_SOCKET_ERROR_UNSPEC; if(wrote) *wrote = 0;
  }
  if(wrote) {
    *wrote = wrote_g;
  return ESS_SOCKET_ERROR_OK;
}
