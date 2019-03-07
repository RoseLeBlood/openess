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
 * @file generic_udp_output_backend.h
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
#include "ess_output_stream.h"
#include "ess_inet_dram_client.h"

/**
* @brief generic udp backend
*
* send first the format (ess_format_t) as string then the data
*/
class generic_udp_output_backend : public ess_output_stream<ESS_CHANNEL_FORMAT_STEREO> { // TODO: in the future using multicast
public:
  generic_udp_output_backend();
  ~generic_udp_output_backend() { }

  virtual ess_error_t probe(ess_format_t format); //
  virtual ess_error_t open() ; //
  virtual ess_error_t close();

  virtual ess_error_t update(void);

protected:
  unsigned int send_packet(const void* data, unsigned int size);

  ess_inet_dram_client* m_pClient;
  ess_format_t m_eFormat;
};

/**
* @}
*/
#endif
