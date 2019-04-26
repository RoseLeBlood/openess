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
 * @file ess_esp32uart_output_module.h
 * @author Anna Sopdia Schröck
 * @date 22 März 20119
 * @brief generic uart output module
 *
 *
 */
#ifndef _ESS_PLATFORM_INC_ESP32_UART_H_
#define _ESS_PLATFORM_INC_ESP32_UART_H_

/**
* @addtogroup ess_platform_esp32
* @{
*/

#include "../../core/module/ess_stereo_simple_buffer_output_module.h"
#include "esp_system.h"


#define ESS_MODULE_OUT_UART_ESP32 			 		"uart0:0"

/**
* @brief esp32 uart stereo output module
**/
class ess_esp32uart_output_module : public ess_stereo_simple_buffer_output_module {
public:
  /**
  * @brief basic constructer
  **/
  ess_esp32uart_output_module(void);
protected:
  /**
  * @brief send buffer to the uart0 device
  * @param [in] simple_buffer the simple buffer to send to the uart0 device
  * @param [in] offset offset to send
  * @param [in] size size of the simple buffer to send
  *
  * @return the size to write to the uart0 device
  * @retval <0 error on send
  **/
  virtual size_t send_simple_buffer_to_device(int32_t* simple_buffer, size_t offset, size_t size);
};

/**
* @}
*/
#endif
