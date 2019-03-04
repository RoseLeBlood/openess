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
 * @file i2s_generic_output_backend.cpp
 * @author Anna Sopdia Schröck
 * @date 2 Februar 2019
 * @brief all esp32 backend generic_i2s functions source
 *
 */

#include "config.h"
#ifdef ESS_ENABLE_BACKEND_OUT_I2S
#include "platform/esp32/i2s_generic_output_backend.h"

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



i2s_generic_output_backend::i2s_generic_output_backend(i2s_controller i2sconfig)
  : ess_backend(2, m_pInputQueueArray, ESS_BACKEND_NAME_OUT_I2S_ESP32)   {
    m_i2sConfig = i2sconfig;
}
i2s_generic_output_backend::~i2s_generic_output_backend() {

}
ess_error_t i2s_generic_output_backend::probe(ess_format_t format) {
  return ESS_OK;
}
ess_error_t i2s_generic_output_backend::open() {
  m_bBlockingObjectRun = true;
  m_bBlocking = true;
  m_bInit = true;

  return ess_backend::open();
}


ess_error_t  i2s_generic_output_backend::close(  ){
  return ess_backend::close();
}

const char* i2s_generic_output_backend::get_info( ) {
  return "I2S Generic Backend";
}



ess_error_t IRAM_ATTR i2s_generic_output_backend::update(void) {
	ess_audio_block_t *block_left, *block_right;

	if(m_isUsed) {
		block_left = receive_read_only(0);  // input 0
		block_right = receive_read_only(1); // input 1

		switch(m_i2sConfig.get_bits()) {
			case 16:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
					int16_t sample[2];
						sample[0] = (block_left) ?  (int16_t)(block_left->data[i] * 32767.0f) : 0;
						sample[1] = (block_right) ?  (int16_t)(block_right->data[i] * 32767.0f) : 0;

					  m_iSampleBuffer[i] = (((sample[1]+ 0x8000)<<16) | ((sample[0]+ 0x8000) & 0xffff));
				}
				break;
			case 24:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
						m_iSampleBuffer[i*2 + 1] = (block_left) ? (-((int32_t)(block_left->data[i] * 8388608.0f))) << 8 : 0;
						m_iSampleBuffer[i*2] = (block_right) ?  (-((int32_t)(block_right->data[i] * 8388608.0f))) << 8 : 0;
				}
				break;
			case 32:
				for(int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
						m_iSampleBuffer[i*2 + 1] = (block_left) ?  ((int32_t)(block_left->data[i] * 1073741823.0f)) : 0;
						m_iSampleBuffer[i*2] = (block_right) ?  ((int32_t)(block_right->data[i] * 1073741823.0f)) : 0;
				}
				break;
			default:
				break;
		}

		size_t totalBytesWritten = 0;
		size_t bytesWritten = 0;
		for(;;) {
			switch(m_i2sConfig.get_bits()) {
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

		if (block_left) release(block_left);
		if (block_right) release(block_right);
	}
  return ESS_OK;
}

#endif
