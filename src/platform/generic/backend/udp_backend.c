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
 * @file generic_platform_semaphore.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all generic backend udp functions source
 *
 */
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


ess_error_t ess_backend_udp_open(const ess_format_t format) {
  ess_error_t error;

  switch (format) {
    case ESS_FORMAT_MONO_96000_8:
    case ESS_FORMAT_MONO_96000_16:
    case ESS_FORMAT_MONO_96000_24:
    case ESS_FORMAT_STEREO_96000_8:
    case ESS_FORMAT_STEREO_96000_16:
    case ESS_FORMAT_STEREO_96000_24:
      return ESS_ERROR_WRONG_FORMAT;
    default:
      break;
  };

#if ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_BOTH
  error =  ess_socket_create_server(  ESS_SOCKET_FAMILY_BOTH, ESS_SOCKET_PROTO_DRAM, "::",
    ESS_BACKEND_UDP_PORT, &(((udp_backend_t*)_udp_backend_config.user_daten)->socket));
#elif ESS_BACKEND_UDP_FAMILY == ESS_FAMILY_IP4
  error =  ess_socket_create_server(  ESS_SOCKET_FAMILY_IP4, ESS_SOCKET_PROTO_DRAM, "0.0.0.0",
    ESS_BACKEND_UDP_PORT, &(((udp_backend_t*)_udp_backend_config.user_daten)->socket));
#else
  error =  ess_socket_create_server(  ESS_SOCKET_FAMILY_IP6, ESS_SOCKET_PROTO_DRAM, "::",
    ESS_BACKEND_UDP_PORT, &(((udp_backend_t*)_udp_backend_config.user_daten)->socket));
#endif
  return error;
}
ess_error_t  ess_backend_udp_close( void ){
  return ess_socket_close(&(((udp_backend_t*)_udp_backend_config.user_daten)->socket)) ;
}
ess_error_t  ess_backend_udp_pause( void ){
  ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused = 1;
  return ESS_OK;
}
ess_error_t     ess_backend_udp_write( void *buffer, unsigned int buf_size,  unsigned int* wrote ){
  if( ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused ) return ESS_ERROR_PAUSED;
  if(wrote) *wrote = -1;
  return ESS_OK;
}
ess_error_t     ess_backend_udp_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if( ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused ) return ESS_ERROR_PAUSED;
  if(readed) *readed = -1;
  return ESS_OK;
}
ess_error_t  ess_backend_udp_flush( void ){
  return ESS_OK;
}
ess_error_t  ess_backend_udp_resume( void ){
  ((udp_backend_t*)_udp_backend_config.user_daten)->udp_paused = 0;
  return ESS_OK;
}
ess_error_t  ess_backend_udp_set_sample_format(const ess_format_t format) {
  return ESS_OK;
}
const char* ess_backend_udp_get_name(void) {
  return ESS_BACKEND_NAME_UDP;
}
const char* ess_backend_udp_get_info(void) {
  return "Network audio backend over udp";
}

#include <stdlib.h>

udp_backend_t backend_data;

ess_backend_facktory_t _udp_backend_config = {
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
