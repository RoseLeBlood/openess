#include "ess_format.h"
#include "config.h"
#ifdef ESS_ENABLE_BACKEND_UDP
#include "ess_backend.h"
#include "ess_socket.h"

#include "stdio.h"

typedef struct udp_backend {
  int udp_paused ;
  ess_socket_t socket;
} udp_backend_t;

ess_backend_facktory_t _udp_backend_config;


ess_backend_error_t ess_backend_udp_probe(const ess_format_t format) {
  switch (format) {
    case ESS_FORMAT_MONO_96000_8:
    case ESS_FORMAT_MONO_96000_16:
    case ESS_FORMAT_MONO_96000_24:
    case ESS_FORMAT_STEREO_96000_8:
    case ESS_FORMAT_STEREO_96000_16:
    case ESS_FORMAT_STEREO_96000_24:
      break;
    default:
      return ESS_BACKEND_OK;
  }
  printf("Format not support for backend: udp (%s)\n", ess_format_to_string(format));
  return ESS_BACKEND_ERROR_WRONG_FORMAT;
}
ess_backend_error_t ess_backend_udp_open(const ess_format_t format) {
  ess_socket_error_t error;

#if ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_BOTH
  error = ess_socket_create(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket), ESS_SOCKET_FAMILY_BOTH, ESS_SOCKET_PROTO_DRAM, "::",
                                ESS_BACKEND_UDP_PORT);
#elif ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_IP4
  error = ess_socket_create(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket), ESS_SOCKET_FAMILY_IP4, ESS_SOCKET_PROTO_DRAM, "0.0.0.0",
                              ESS_BACKEND_UDP_PORT);
#else
  error = ess_socket_create(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket), ESS_SOCKET_FAMILY_IP6, ESS_SOCKET_PROTO_DRAM, "::",
                              ESS_BACKEND_UDP_PORT);
#endif
  if(error != ESS_SOCKET_ERROR_OK) return ESS_BACKEND_ERROR;

  error = ess_socket_create_server(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket));

  return error == ESS_SOCKET_ERROR_OK ? ESS_BACKEND_OK :  ESS_BACKEND_ERROR;
}
ess_backend_error_t  ess_backend_udp_close( void ){
  return ess_socket_close(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket)) == ESS_SOCKET_ERROR_OK ?
    ESS_BACKEND_OK :  ESS_BACKEND_ERROR;
}
ess_backend_error_t  ess_backend_udp_pause( void ){
  ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused = 1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_udp_write( void *buffer, unsigned int buf_size,  unsigned int* wrote ){
  if( ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused ) return ESS_BACKEND_PAUSED;
  if(wrote) *wrote = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_udp_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if( ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused ) return ESS_BACKEND_PAUSED;
  if(readed) *readed = -1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_flush( void ){
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_resume( void ){
  ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused = 0;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_udp_set_sample_format(const ess_format_t format) {
  return ESS_BACKEND_OK;
}
const char* ess_backend_udp_get_name(void) {
  #if ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_IP6
  return "udp6-backend";
  #elif  ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_IP4
  return "udp4-backend";
  #else
  return "udp_both-backend";
  #endif
}
const char* ess_backend_udp_get_info(void) {
  return "Network audio backend over udp";
}

#include <stdlib.h>

udp_backend_t backend_data;

ess_backend_facktory_t _udp_backend_config = {
  ess_backend_udp_probe,
  ess_backend_udp_open,
  ess_backend_udp_close,
  ess_backend_udp_pause,
  ess_backend_udp_resume,
  ess_backend_udp_write,
  ess_backend_udp_read,
  ess_backend_udp_flush,
  ess_backend_udp_set_sample_format,
  ess_backend_udp_get_name,
  ess_backend_udp_get_info,
  &backend_data,
};


ess_backend_facktory_t* ess_backend_udp_getFactory() {
  return &_udp_backend_config;
}
#endif
