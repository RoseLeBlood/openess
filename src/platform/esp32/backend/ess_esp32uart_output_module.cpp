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
  : ess_output_module(ESS_MODULE_OUT_UART_ESP32)  {

  ess_output_module::add_channel(std::string(ESS_MODULE_OUT_UART_ESP32) + std::string("_left"),
    ESS_AUDIO_CHANNEL_LEFT);
  ess_output_module::add_channel(std::string(ESS_MODULE_OUT_UART_ESP32) + std::string("_right"),
    ESS_AUDIO_CHANNEL_RIGHT);

  m_iBuffer[1] = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];
  m_iBuffer[0] = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];

  memset(m_iBuffer[1], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
  memset(m_iBuffer[0], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);

  m_bActive = true;
}

ess_error_t ess_esp32uart_output_module::add_channel(std::string name, ess_audio_channel channel) {
  return ESS_ERROR;
}

ess_error_t ess_esp32uart_output_module::add_channel(ess_input_channel* channel) {
  return ESS_ERROR;
}
ess_esp32uart_output_module::~ess_esp32uart_output_module() {
  if (m_iBuffer[1]) delete m_iBuffer[1];
  if (m_iBuffer[0]) delete m_iBuffer[0];
}

ess_error_t ESS_IRAM_ATTR ess_esp32uart_output_module::update(void) {
  ess_automux_t lock(m_mutex);

  if(!m_bActive) { ess_platform_sleep(1); return ESS_ERROR; }
  if(m_iBuffer[1] == NULL || m_iBuffer[0] == NULL) {   ess_platform_sleep(1);  return ESS_ERROR_OUTOFMEM;}

  bool blocked = false;

   int red_l = read(ESS_AUDIO_CHANNEL_LEFT,    m_iBuffer[0], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
   int red_r = read(ESS_AUDIO_CHANNEL_RIGHT, m_iBuffer[1], 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);


   if(red_l != -1 && red_r != -1)  {
  		switch( ess_platform_esp32::get_bits() ) {
  			case 16:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  					int16_t sample[2];
  						sample[0] = (m_iBuffer[0]) ?  (int16_t)(m_iBuffer[0][i] * 32767.0f) : 0;
  						sample[1] = (m_iBuffer[1]) ?  (int16_t)(m_iBuffer[1][i] * 32767.0f) : 0;

  					  m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));

  				}
  				break;
  			case 24:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  						m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ? (-((int32_t)(m_iBuffer[0][i] * 8388608.0f))) << 8 : 0;
  						m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  (-((int32_t)(m_iBuffer[1][i] * 8388608.0f))) << 8 : 0;
  				}
  				break;
  			case 32:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  						m_iSampleBuffer[i*2 + 1] = (m_iBuffer[0]) ?  ((int32_t)(m_iBuffer[0][i] * 1073741823.0f)) : 0;
  						m_iSampleBuffer[i*2] = (m_iBuffer[1]) ?  ((int32_t)(m_iBuffer[1][i] * 1073741823.0f)) : 0;
  				}
  				break;
  			default:
  				break;
  		}
   } else {
     printf("blocked\n");
     blocked = true;
   }


   if(!blocked) {

    for(int i=0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
      printf("%.2f ", (float)m_iSampleBuffer[i]);
      if(i % 8) printf("\n");

    	vPortYield();
    }
  } else {
    ess_platform_sleep(1);
  }


    return ESS_OK;
}
#endif

#endif
