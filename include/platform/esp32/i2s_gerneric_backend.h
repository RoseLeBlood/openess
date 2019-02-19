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
 * @file i2s_gerneric_backend.h
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

#include "ess_backend.h"
#include "ess_backend_factory.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"

class ess_i2s_generic_backend : public ess_backend {
public:
  ess_i2s_generic_backend();
  ~ess_i2s_generic_backend();

  virtual ess_error_t probe(const ess_format_t format);
  virtual ess_error_t open(const ess_format_t format);
  virtual ess_error_t close();
  virtual ess_error_t restart(const ess_format_t format);

  virtual ess_error_t pause();
  virtual ess_error_t resume();

  virtual ess_error_t write(const void *buffer, unsigned int buf_size, unsigned int* wrote);
  virtual ess_error_t read(void *buffer, unsigned int buf_size, unsigned int* readed);

  virtual const char* get_info();
protected:
  void* m_pUserData;
  bool m_bPaused;
  i2s_config_t m_i2sConfig;
  i2s_pin_config_t m_pinConfig;
};

/**
* @}
*/
#endif
