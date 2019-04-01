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
 * @file ess_esp32uart_output_module.cpp
 * @author Anna Sopdia Schröck
 * @date 2 Februar 2019
 * @brief all esp32 backend generic_i2s functions source
 *
 */

#include "config.h"
#ifdef ESS_ENABLE_OUTMODULE_UART
#include "platform/esp32/ess_esp32uart_output_module.h"

#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <math.h>
#include <errno.h>
#include <sys/select.h>

#include <stdio.h>

#include <math.h>

#include "esp_log.h"
#include "platform/esp32/ess_platform_esp32.h"
#include "platform/ess_sleep.h"

#if  ESS_PLATFORM_ESP32 == 1


ess_esp32uart_output_module::ess_esp32uart_output_module()
  : ess_stereo_simple_buffer_output_module(ESS_MODULE_OUT_UART_ESP32)  {
  m_bActive = true;
}

size_t ESS_IRAM_ATTR  ess_esp32uart_output_module::send_simple_buffer_to_device(int32_t* simple_buffer, size_t offset, size_t size) {
  for(size_t i= offset; i < size; i++) {
    printf("%.2f ", (float)simple_buffer[i]);
    if(i % 16) printf("\n");
  }
  return size;
}

#endif

#endif
