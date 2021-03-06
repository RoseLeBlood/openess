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
 * @file ess_i2s_controller.h
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

/**
* @brief the basic i2s esp32 controller
**/
class ess_i2s_controller : public ess_controler {
public:
  /**
  * @brief basic constructor - set name to "ess_i2s_controller"
  **/
  ess_i2s_controller() : ess_controler("ess_i2s_controller") { }

  /**
  * @brief setup the controller using in `ess_platform_interface`
  **/
  virtual ess_error_t setup(int flags = 0);
  /**
  * @brief destroy the controller using in `ess_platform_interface`
  **/
  virtual ess_error_t destroy(int flags = 0) ;

  /**
  * @brief get the controller format bits
  **/
  virtual int get_bits();
  /**
  * @brief get the controller format samplerate
  **/
  virtual int get_samplerate();

  /**
  * @brief get the controller format
  **/
  virtual ess_format_t get_format();

  /**
  * @brief write audio buffer to the using device
  * @param [in] buffer rhe audio buffer
  * @param [in] the write offset
  * @param [in] size the size of the buffer
  *
  * @return the size to write to the device
  * @retval <0 error
  **/
  virtual unsigned int write(void* buffer, unsigned int offset, unsigned  int size) ;
private:
  i2s_config_t m_i2sConfig;
  i2s_pin_config_t m_pinConfig;
};

#endif
