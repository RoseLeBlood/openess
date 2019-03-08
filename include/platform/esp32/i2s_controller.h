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
 * @file ess_ontroler.h
 * @author Anna Sopdia Schröck
 * @date 04 März 20119
 * @brief generic platform hardware controller
 *
 *
 */
#ifndef _ESS_PLATFORM_I2S_CONTROLER_H_
#define _ESS_PLATFORM_I2S_CONTROLER_H_

#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

#include "ess_format.h"
#include "platform/ess_controler.h"

class i2s_controller : public ess_controler {
public:
  virtual ess_error_t setup(int flags = 0);
  virtual ess_error_t destroy(int flags) ;

  virtual void* get_value(int flags) { return NULL; }


  ess_format_t get_format() ;
  int get_bits();
  int get_samplerate() ;
  int get_channels();
private:
  i2s_config_t m_i2sConfig;
  i2s_pin_config_t m_pinConfig;
};

#endif
