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
 * @addtogroup ess_platform_esp32
 * @{
 */

#ifndef _ESS_PLATFORM_INC_ESP32_H_
#define _ESS_PLATFORM_INC_ESP32_H_

#include "ess_platform_factory.h"

#ifdef ESS_ENABLE_BACKEND_OUT_I2S
#include "platform/esp32/i2s_generic_output_backend.h"
#endif

class ess_backend_esp32 : public ess_interface_platform {
public:
  ess_backend_esp32();

  virtual void create();

  virtual std::string get_platform_name();
  virtual std::string get_factory_creater();
private:
#ifdef ESS_ENABLE_BACKEND_OUT_I2S
  i2s_controller m_i2sController;
#endif

};
/**
* @}
*/

#endif
