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
 * @file generic_udp_backend.h
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief the basic udp backend class
 *
 * this is a udp backend
 */
#ifndef _ESS_PLATFORM_INC_GENERIC_UDP_BACKEND_H_
#define _ESS_PLATFORM_INC_GENERIC_UDP_BACKEND_H_

/**
* @addtogroup ess_platform_generic
* @{
*/

#include "ess.h"
#include "ess_backend.h"
#include "ess_inet_dram_client.h"

/**
* @brief generic udp backend
*
* send first the format (ess_format_t) as string then the data
*/
class generic_udp_backend : public ess_backend { // TODO: in the future using multicast
public:
  generic_udp_backend();
  ~generic_udp_backend() { close(); }

  virtual ess_error_t probe(const ess_format_t format); //
  virtual ess_error_t open(const ess_format_t format) ; //
  virtual ess_error_t close();
  virtual ess_error_t restart(const ess_format_t format) ; //

  virtual ess_error_t pause() ;
  virtual ess_error_t resume() ;

  virtual ess_error_t write(const void *buffer, unsigned int buf_size, unsigned int* wrote) ;
  virtual ess_error_t read(void *buffer, unsigned int buf_size, unsigned int* readed) { return ESS_ERROR; }

  virtual const char* get_info() { return "generic_udp_backend"; }
protected:
  unsigned int send_packet(const void* data, unsigned int size);
protected:
  bool m_bPaused;
  ess_inet_dram_client* m_pClient;
  ess_format_t m_eFormat;
};

/**
* @}
*/
#endif
