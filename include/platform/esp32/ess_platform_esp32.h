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

#include "config.h"
#include "i2s_controller.h"
#include "ess_format.h"

class ess_platform_esp32  {
public:
  ess_platform_esp32();
  void create();

  static ess_format_t get_format() { return ESS_DEFAULT_SERVER_FORMAT; }
  static unsigned char get_bits() { return ess_format_get_bits(ESS_DEFAULT_SERVER_FORMAT); }
  static unsigned char get_samplerate() { return ess_format_get_samplerate(ESS_DEFAULT_SERVER_FORMAT); }
  static unsigned char channels() { return ess_format_get_channels(ESS_DEFAULT_SERVER_FORMAT); }
private:
  i2s_controller m_i2sController;
};
/**
* @}
*/

#endif
