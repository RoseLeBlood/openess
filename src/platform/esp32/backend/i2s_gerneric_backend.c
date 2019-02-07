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
 * @file i2s_gerneric_backend.c
 * @author Anna Sopdia Schröck
 * @date 2 Februar 20119
 * @brief all esp32 backend generic_i2s functions source
 *
 */
#include "ess_format.h"
#include "config.h"
#ifdef ESS_ENABLE_BACKEND_I2S
#include "ess_backend.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <math.h>
#include <errno.h>
#include <sys/select.h>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include <math.h>


static i2s_config_t std_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
    .sample_rate = 44100,                                                                                        // Default: 48kHz
    .bits_per_sample = 16,                                                                                     //16-bit per channel
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
    .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
    .dma_buf_count = ESS_BACKEND_I2S_DMA_BUF_COUNT,
    .dma_buf_len = ESS_BACKEND_I2S_DMA_BUF_SIZE,                                                      //
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
};

static i2s_pin_config_t std_pin_config = {
    .bck_io_num = I2S_EXTERNAL_DAC_BCK,
    .ws_io_num = I2S_EXTERNAL_DAC_LRCLK,
    .data_out_num = I2S_EXTERNAL_DAC_DOUT,
    .data_in_num = I2S_EXTERNAL_DAC_DIN                                                       //Not used
};

int g_i2s_generic_paused = 0;

ess_backend_error_t ess_backend_i2s_generic_probe(const ess_format_t format) {
  return ESS_BACKEND_OK;
}

ess_backend_error_t ess_backend_i2s_generic_open(const ess_format_t format ) {
  std_config.sample_rate = ess_format_get_samplerate(ESS_BACKEND_I2S_FORMAT);
  std_config.bits_per_sample = ess_format_get_bits(ESS_BACKEND_I2S_FORMAT);

  if(i2s_driver_install(0, &std_config, 0, NULL) != ESP_OK) {
    return ESS_BACKEND_ERROR;
  }
  if(i2s_set_pin(0, &std_pin_config) != ESP_OK) {
    return ESS_BACKEND_ERROR;
  }
  i2s_set_clk(0, ess_format_get_samplerate(format) ,
                         ess_format_get_bits(format),
                         (ess_format_get_channels(format) == 2) ?
                          I2S_CHANNEL_STEREO :
                          I2S_CHANNEL_MONO);


  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_i2s_generic_close(  ){
  i2s_driver_uninstall(0);
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_i2s_generic_pause(    ){
  g_i2s_generic_paused = 1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_i2s_generic_write( void *buffer, unsigned int buf_size,  unsigned int* wrote  ){
  if(g_i2s_generic_paused) return ESS_BACKEND_PAUSED;
  i2s_write(0, buffer, buf_size, wrote, 100);

  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_i2s_generic_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if(g_i2s_generic_paused) return ESS_BACKEND_PAUSED;

//  int  len = uart_read_bytes(UART_NUM_1, buffer, buf_size, 20 / portTICK_RATE_MS);
  return 0;
}
ess_backend_error_t  ess_backend_i2s_generic_flush(  ){

  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_i2s_generic_resume(  ){
  g_i2s_generic_paused = false;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_i2s_set_sample_format(const ess_format_t format) {
  i2s_set_clk(0, ess_format_get_samplerate(format) ,
                         ess_format_get_bits(format),
                         (ess_format_get_channels(format) == 2) ?
                          I2S_CHANNEL_STEREO :
                          I2S_CHANNEL_MONO);
  return ESS_BACKEND_OK;
}
const char* ess_backend_i2s_generic_get_name( ) {
  return ESS_BACKEND_NAME_I2S_ESP32;
}
const char* ess_backend_i2s_generic_get_info( ) {
  return "I2S Generic Backend";
}
ess_backend_facktory_t _i2s_generic_backend_config = {
  ess_backend_i2s_generic_probe,
  ess_backend_i2s_generic_open,
  ess_backend_i2s_generic_close,
  ess_backend_i2s_generic_pause,
  ess_backend_i2s_generic_resume,
  ess_backend_i2s_generic_write,
  ess_backend_i2s_generic_read,
  ess_backend_i2s_generic_flush,
  ess_backend_i2s_set_sample_format,
  ess_backend_i2s_generic_get_name,
  ess_backend_i2s_generic_get_info,
  0,
};
ess_backend_facktory_t* ess_backend_i2s_generic_getFactory() {
  return &_i2s_generic_backend_config;
}
#endif
