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
 * @file ess_esp32i2s_output_module.cpp
 * @author Anna Sopdia Schröck
 * @date 2 Februar 2019
 * @brief all esp32 backend generic_i2s functions source
 *
 */

#include "config.h"
#ifdef ESS_ENABLE_BACKEND_OUT_I2S
#include "platform/esp32/ess_esp32i2s_output_module.h"

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

#if  ESS_PLATFORM_ESP32 == 1
ess_esp32i2s_output_module::ess_esp32i2s_output_module()
  : ess_output_module(ESS_BACKEND_NAME_OUT_I2S_ESP32)   {

  ess_output_module::add_channel(std::string(ESS_BACKEND_NAME_OUT_I2S_ESP32) + std::string("_left"),
    ESS_AUDIO_CHANNEL_LEFT);
  ess_output_module::add_channel(std::string(ESS_BACKEND_NAME_OUT_I2S_ESP32) + std::string("_right"),
    ESS_AUDIO_CHANNEL_RIGHT);
}

ess_error_t ess_esp32i2s_output_module::add_channel(std::string name, ess_audio_channel channel) {
  return ESS_ERROR;
}

ess_error_t ess_esp32i2s_output_module::add_channel(ess_input_channel* channel) {
  return ESS_ERROR;
}
ess_esp32i2s_output_module::~ess_esp32i2s_output_module() {

}
ess_error_t ESS_IRAM_ATTR ess_esp32i2s_output_module::update(void) {
	 int32_t* buffer_r, *buffer_l;

   buffer_r = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];
   buffer_l = new int32_t[ESS_DEFAULT_AUDIO_PACKET_SIZE];

   if(buffer_r == NULL || buffer_l == NULL) return ESS_ERROR_OUTOFMEM;

   int red_l = read(ESS_AUDIO_CHANNEL_LEFT,    buffer_l, 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);
   int red_r = read(ESS_AUDIO_CHANNEL_RIGHT, buffer_r, 0, ESS_DEFAULT_AUDIO_PACKET_SIZE);

   if(red_l != -1 && red_r != -1)  {
  		switch( ess_platform_esp32::get_bits() ) {
  			case 16:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  					int16_t sample[2];
  						sample[0] = (buffer_l) ?  (int16_t)(buffer_l[i] * 32767.0f) : 0;
  						sample[1] = (buffer_r) ?  (int16_t)(buffer_r[i] * 32767.0f) : 0;

  					  m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));
  				}
  				break;
  			case 24:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  						m_iSampleBuffer[i*2 + 1] = (buffer_l) ? (-((int32_t)(buffer_l[i] * 8388608.0f))) << 8 : 0;
  						m_iSampleBuffer[i*2] = (buffer_r) ?  (-((int32_t)(buffer_r[i] * 8388608.0f))) << 8 : 0;
  				}
  				break;
  			case 32:
  				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
  						m_iSampleBuffer[i*2 + 1] = (buffer_l) ?  ((int32_t)(buffer_l[i] * 1073741823.0f)) : 0;
  						m_iSampleBuffer[i*2] = (buffer_r) ?  ((int32_t)(buffer_r[i] * 1073741823.0f)) : 0;
  				}
  				break;
  			default:
  				break;
  		}
   }

		size_t totalBytesWritten = 0;
		size_t bytesWritten = 0;
		for(;;) {
			switch(ess_platform_esp32::get_bits() ) {
				case 16:
					i2s_write(I2S_NUM_0, (const char*)&m_iSampleBuffer, (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)), &bytesWritten, portMAX_DELAY);		//Block but yield to other tasks
					break;
				case 24:
				case 32:
					i2s_write(I2S_NUM_0, (const char*)&m_iSampleBuffer, (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)) * 2, &bytesWritten, portMAX_DELAY);		//Block but yield to other tasks
					break;
				default:
					break;
			}
			totalBytesWritten += bytesWritten;
			if(totalBytesWritten >= (ESS_DEFAULT_AUDIO_PACKET_SIZE * sizeof(uint32_t)))
				break;
			vPortYield();
		}

		if (buffer_r) delete buffer_r;
    if (buffer_l) delete buffer_l;

  return ESS_OK;
}
#endif

#endif
