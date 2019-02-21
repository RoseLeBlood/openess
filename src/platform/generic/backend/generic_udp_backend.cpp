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
 * @file generic_udp_backend.cpp
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief the basic udp backend class
 * this is a udp backend
 */

#include "config.h"
#ifdef ESS_ENABLE_BACKEND_UDP
#include "platform/generic_udp_backend.h"

generic_udp_backend::generic_udp_backend() : ess_backend(ESS_BACKEND_NAME_UDP) {
  m_bPaused = false;
}
ess_error_t generic_udp_backend::probe(const ess_format_t format) {
  switch (format) {
    case ESS_FORMAT_MONO_96000_8:
    case ESS_FORMAT_MONO_96000_16:
    case ESS_FORMAT_MONO_96000_24:
    case ESS_FORMAT_STEREO_96000_8:
    case ESS_FORMAT_STEREO_96000_16:
    case ESS_FORMAT_STEREO_96000_24:
      return ESS_ERROR_WRONG_FORMAT;
    default:
      return ESS_OK;
  }

}
ess_error_t generic_udp_backend::open(const ess_format_t format)  {
  #if ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP
    #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      m_pClient = new ess_inet_dram_client_ip4();
    #else
      m_pClient = new ess_inet_dram_client_ip6();
    #endif  // ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
  #elif ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP_LITE
    #if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
      m_pClient = new ess_inet_dramlite_client_ip4();
    #else
      m_pClient = new ess_inet_dramlite_client_ip6();
    #endif  // ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
  #endif //ESS_BACKEND_UDP_PROTOCOL == ESS_PROTOCOL_UDP

  if(m_pClient == 0) return ESS_ERROR_OUTOFMEM;


  return  m_pClient->is_socket() && ess_backend::open(format) ? ESS_OK : ESS_ERROR;

}
ess_error_t generic_udp_backend::restart(const ess_format_t format)  {
  m_eFormat = format;
  return ESS_OK;
}
ess_error_t generic_udp_backend::write(const void *buffer, unsigned int buf_size, unsigned int* wrote) {
  unsigned int  dat = send_packet(buffer, buf_size);
  if(wrote) *wrote = dat;
  return ESS_OK;
}
ess_error_t generic_udp_backend::pause() {
  if(m_pClient == 0) return ESS_ERROR;
  if(m_bPaused) return ESS_ERROR;
  m_bPaused = true;

  return ESS_OK;
}
ess_error_t generic_udp_backend::resume() {
  if(m_pClient == 0) return ESS_ERROR;
  if(!m_bPaused) return ESS_ERROR;
  m_bPaused = false;

  return ESS_OK;
}
ess_error_t generic_udp_backend::close() {
  if(m_pClient == 0) return ESS_ERROR;

  return ess_backend::close();
}


unsigned int generic_udp_backend::send_packet(const void* data, unsigned int size) {
  if(m_pClient == 0) return -1;

  m_pClient->sendto(ess_format_to_string(m_eFormat), ESS_BACKEND_UDP_SENDTO_HOST,
    ESS_BACKEND_UDP_SENDTO_PORT);
  return m_pClient->sendto(data, size,  ESS_BACKEND_UDP_SENDTO_HOST,
    ESS_BACKEND_UDP_SENDTO_PORT);

}

#endif
