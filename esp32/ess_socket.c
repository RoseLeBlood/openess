#include "ess_socket.h"


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
ess_socket_error_t ess_socket_create(ess_socket_t* socket, ess_socket_fam_t fam, ess_socket_pro_t protokoll,  const char* hostname, unsigned short port) {
  if(socket == 0) return ESS_SOCKET_ERROR_NULL;
  socket->family = fam;
  socket->protokol = protokoll;
  socket->port = port;
  socket->status = ESS_SOCKET_STATUS_CREATED;
  strcpy(socket->hostname, hostname);

  return ESS_SOCKET_ERROR_OK;
}
ess_socket_error_t ess_socket_create_server(ess_socket_t* _socket) {
  if(_socket == 0) return ESS_SOCKET_ERROR_NULL;
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

  if (  (_socket->retval = getaddrinfo(_socket->hostname,_socket->port,&hints,&result)) != 0 ) {
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




/* connec t STREAM
int sfd, return_value;
struct addrinfo hint, *result, *result_check;
memset(&hint,0,sizeof hint);

switch ( socket->protokol ) {
  case ESS_SOCKET_FAMILY_IP4: hint.ai_family = AF_INET; break;
  case ESS_SOCKET_FAMILY_IP6: hint.ai_family = AF_INET6; break;
  case ESS_SOCKET_IP_FAMILY_BOTH: hint.ai_family = AF_UNSPEC; break;
  default: return ESS_SOCKET_ERROR_UNSPEC_PROTOKOL;
};
hint.ai_socktype = SOCK_STREAM;

if (  (return_value = getaddrinfo(socket->hostname,socket->port, &hint, &result))  != 0 ) {
  return ESS_SOCKET_ERROR_GETADDR;
}
for ( result_check = result; result_check != NULL; result_check = result_check->ai_next ) {
  sfd = socket(result_check->ai_family, result_check->ai_socktype | flags, result_check->ai_protocol);
  if ( sfd < 0 )  continue;

  if ( -1 != connect(sfd,result_check->ai_addr,result_check->ai_addrlen))  break;
  close(sfd);
}
freeaddrinfo(result);


return ESS_SOCKET_ERROR_OK;*/
