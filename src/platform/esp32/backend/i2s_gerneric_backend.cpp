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
 * @file i2s_gerneric_backend.cpp
 * @author Anna Sopdia Schröck
 * @date 2 Februar 2019
 * @brief all esp32 backend generic_i2s functions source
 *
 */

#include "config.h"
#ifdef ESS_ENABLE_BACKEND_I2S
#include "platform/esp32/i2s_gerneric_backend.h"

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



ess_i2s_generic_backend::ess_i2s_generic_backend()
  : ess_backend(2, m_pInputQueueArray, ESS_BACKEND_NAME_I2S_ESP32)   {

  m_i2sConfig.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);                                // Only TX
  m_i2sConfig.sample_rate = 48000;                                                                                       // Default: 48kHz
  m_i2sConfig.bits_per_sample = (i2s_bits_per_sample_t)16;                                                                                     //16-bit per channel
  m_i2sConfig.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;                           //2-channels
  m_i2sConfig.communication_format =(i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
  m_i2sConfig.dma_buf_count = ESS_BACKEND_I2S_DMA_BUF_COUNT;
  m_i2sConfig.dma_buf_len = ESS_BACKEND_I2S_DMA_BUF_SIZE;                                                      //
  m_i2sConfig.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;                                //Interrupt level 1

  m_pinConfig.bck_io_num = I2S_EXTERNAL_DAC_BCK;
  m_pinConfig.ws_io_num = I2S_EXTERNAL_DAC_LRCLK;
  m_pinConfig.data_out_num = I2S_EXTERNAL_DAC_DOUT;
  m_pinConfig.data_in_num = I2S_EXTERNAL_DAC_DIN;                                                       //Not used

  m_bPaused = true;
}
ess_i2s_generic_backend::~ess_i2s_generic_backend() {
  close();
}
ess_error_t ess_i2s_generic_backend::probe(const ess_format_t format) {
  return ESS_OK;
}
ess_error_t ess_i2s_generic_backend::open(const ess_format_t format) {
  m_i2sConfig.sample_rate = ess_format_get_samplerate(format);
  m_i2sConfig.bits_per_sample = (i2s_bits_per_sample_t)ess_format_get_bits(format);


  if(i2s_driver_install((i2s_port_t)0, &m_i2sConfig, 0, NULL) != ESP_OK) {
    ESP_LOGE("I2S", "i2s_driver_install");
    return ESS_ERROR;
  }
  if(i2s_set_pin((i2s_port_t)0, &m_pinConfig) != ESP_OK) {
    ESP_LOGE("I2S", "i2s_set_pin");
    return ESS_ERROR;
  }
  i2s_set_clk((i2s_port_t)0, m_i2sConfig.sample_rate,
                         m_i2sConfig.bits_per_sample,
                        ( (ess_format_get_channels(format) == 2) ?
                          I2S_CHANNEL_STEREO :
                          I2S_CHANNEL_MONO) );
  m_bPaused = false;

  return ess_backend::open(format);
}


ess_error_t  ess_i2s_generic_backend::close(  ){
  i2s_driver_uninstall((i2s_port_t)0);

  return ess_backend::close();
}

const char* ess_i2s_generic_backend::get_info( ) {
  return "I2S Generic Backend";
}

#endif
