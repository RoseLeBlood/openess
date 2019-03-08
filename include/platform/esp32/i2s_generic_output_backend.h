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
 * @file i2s_generic_output_backend.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 20119
 * @brief the basic i2s_generic class
 *
 *
 */
#ifndef _ESS_PLATFORM_INC_ESP32_I2S_H_
#define _ESS_PLATFORM_INC_ESP32_I2S_H_

/**
* @addtogroup ess_platform_esp32
* @{
*/

#include "ess_output_stream.h"
#include "platform/esp32/i2s_controller.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"




class i2s_generic_output_backend : public ess_output_stream<ESS_CHANNEL_FORMAT_STEREO> {
public:
  i2s_generic_output_backend();
  ~i2s_generic_output_backend();

  virtual ess_error_t update(void) ;

protected:
  void* m_pUserData;
  bool m_bPaused;
};

/**
* @}
*/
#endif
