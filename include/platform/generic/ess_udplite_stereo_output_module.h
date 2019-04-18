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
 * @file ess_udplite_output_module.h
 * @author Anna Sopdia Schröck
 * @date 15 März 2019
 * @brief the basic udplite backend class
 *
 */
#ifndef _ESS_UDPLITE_OUTPUT_MODULE_H_
#define _ESS_UDPLITE_OUTPUT_MODULE_H_
/**
* @addtogroup ess_platform_generic
* @{
*/
#include "ess_output_module.h"
#include "net/ess_inet_dram_client.h"
#include "ess_stereo_simple_buffer_output_module.h"

#define ESS_MODULE_OUT_UDPLITE 			 		"udplite0:0"


class ess_udplite_stereo_output_module  : public ess_stereo_simple_buffer_output_module {
public:
  ess_udplite_stereo_output_module();
  ~ess_udplite_stereo_output_module();

protected:
  virtual size_t send_simple_buffer_to_device(int32_t* simple_buffer, size_t offset, size_t size);
private:
#if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
  ess_inet_dramlite_client_ip4 m_iClient;
#else
  ess_inet_dramlite_client_ip6 m_iClient;
#endif
};


/**
* @}
*/
#endif
