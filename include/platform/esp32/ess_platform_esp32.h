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
 * @file ess_platform_esp32.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief Contains the esp32 platform factory pool
 *
 *
 */

 /**
 * @addtogroup platform
 * @{
 */

#ifndef _ESS_PLATFORM_INC_ESP32_H_
#define _ESS_PLATFORM_INC_ESP32_H_

#include "ess.h"
#include "platform/ess_platform_interface.h"


class ess_platform_esp32 : public ess_platform_interface<ess_platform_esp32, ESS_CONFIC_MAX_CORES>  {
  friend class ess_platform_interface<ess_platform_esp32, ESS_CONFIC_MAX_CORES> ;
  friend void _esp32_platform_montoring_cpu0( void * parameter ) ;
  friend void _esp32_platform_montoring_cpu1( void * parameter ) ;
protected:
  ess_platform_esp32();
public:
  static ess_format_t get_format() { return ESS_DEFAULT_SERVER_FORMAT; }

  virtual ess_error_t create() ;

  virtual ess_output_module* create_output(ess_output_type type, std::string controller_name,
    ess_format_t format);

};
/**
* @}
*/

#endif
