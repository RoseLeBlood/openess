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
 * @file ess_platform_esp32.cpp
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ess esp32 backend impl.
 *
 */


#include "platform/esp32/ess_platform_esp32.h"
#include "esp_log.h"



ess_backend_esp32::ess_backend_esp32() {

}
void ess_backend_esp32::create() {
  #ifdef ESS_ENABLE_BACKEND_OUT_I2S
  install_i2s_sub_system();
  add_backend(new i2s_generic_output_backend(m_i2sConfig));
  #endif
}
std::string ess_backend_esp32::get_platform_name() {
  return std::string("ESP32");
}
std::string ess_backend_esp32::get_factory_creater() {
  return std::string("Anna_Sophia Schroeck - annasophia.schroeck@gmail.com");
}
#ifdef ESS_ENABLE_BACKEND_OUT_I2S
ess_error_t ess_backend_esp32::install_i2s_sub_system() {
  m_i2sConfig.sample_rate = ess_format_get_samplerate(ESS_DEFAULT_SERVER_FORMAT);
  m_i2sConfig.bits_per_sample = (i2s_bits_per_sample_t)ess_format_get_bits(ESS_DEFAULT_SERVER_FORMAT);

  m_i2sConfig.mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);                                // Only TX
  m_i2sConfig.sample_rate = 48000;                                                                                       // Default: 48kHz
  m_i2sConfig.bits_per_sample = I2S_BITS_PER_SAMPLE_24BIT;
  m_i2sConfig.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;                           //2-channels
  m_i2sConfig.communication_format =(i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
  m_i2sConfig.dma_buf_count = ESS_BACKEND_I2S_DMA_BUF_COUNT;
  m_i2sConfig.dma_buf_len = ESS_BACKEND_I2S_DMA_BUF_SIZE;                                                      //
  m_i2sConfig.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;                                //Interrupt level 1
  m_i2sConfig.use_apll = 1;

  m_pinConfig.bck_io_num = I2S_EXTERNAL_DAC_BCK;
  m_pinConfig.ws_io_num = I2S_EXTERNAL_DAC_LRCLK;
  m_pinConfig.data_out_num = I2S_EXTERNAL_DAC_DOUT;
  m_pinConfig.data_in_num = I2S_EXTERNAL_DAC_DIN;                                                       //Not used

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
                        ( (ess_format_get_channels(ESS_DEFAULT_SERVER_FORMAT) == 2) ?
                          I2S_CHANNEL_STEREO :
                          I2S_CHANNEL_MONO) );
  return ESS_OK;
}
#endif
