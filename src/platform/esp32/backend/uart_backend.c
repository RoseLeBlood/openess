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
 * @file uart_backend.c
 * @author Anna Sopdia Schröck
 * @date 2 Februar 20119
 * @brief all esp32 backend uart functions source
 *  UART 1
 */
#include "ess_format.h"
#include "config.h"
#ifdef ESS_ENABLE_BACKEND_UART
#include "ess_backend.h"


#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

int g_uart_paused = 0;

ess_backend_error_t ess_backend_uart_probe(const ess_format_t format) {
  return ESS_BACKEND_OK;
}
ess_backend_error_t ess_backend_uart_open(const ess_format_t format) {
  uart_config_t uart_config = {
        .baud_rate = ESS_BACKEND_UART_BAUDRAT,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1,
      ESS_BACKEND_UART_TXD,
      ESS_BACKEND_UART_RXD,
      ESS_BACKEND_UART_RTS,
      ESS_BACKEND_UART_CTS);
    uart_driver_install(UART_NUM_1, 512, 0, 0, NULL, 0);

    const char* buffer =  ess_format_to_string(format);
    uart_write_bytes(UART_NUM_1, (const char *) buffer, strlen(buffer));
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_uart_close( void ){
  uart_driver_delete(UART_NUM_1);
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_uart_pause( void ){
  g_uart_paused = 1;
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_uart_write( void *buffer, unsigned int buf_size,  unsigned int* wrote ){
  if(g_uart_paused) return ESS_BACKEND_PAUSED;

  *wrote = uart_write_bytes(UART_NUM_1, (const char *) buffer, buf_size);
  return ESS_BACKEND_OK;
}
ess_backend_error_t     ess_backend_uart_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if(g_uart_paused) return ESS_BACKEND_PAUSED;

  int  len = uart_read_bytes(UART_NUM_1, buffer, buf_size, 20 / portTICK_RATE_MS);
  if(readed) *readed = len;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_uart_flush( void ){
  uart_flush(UART_NUM_1);
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_uart_resume( void ){
  g_uart_paused = false;
  return ESS_BACKEND_OK;
}
ess_backend_error_t  ess_backend_uart_set_sample_format(const ess_format_t format) {
  const char* buffer =  ess_format_to_string(format);
  uart_write_bytes(UART_NUM_1, (const char *) buffer, strlen(buffer));

  return ESS_BACKEND_OK;
}
const char* ess_backend_uart_get_name(void) {
  return ESS_BACKEND_NAME_UART_ESP32;
}
const char* ess_backend_uart_get_info(void) {
  return "Uart Audio Output for debugging or other thinks";
}

ess_backend_facktory_t _uart_backend_config = {
  ess_backend_uart_probe,
  ess_backend_uart_open,
  ess_backend_uart_close,
  ess_backend_uart_pause,
  ess_backend_uart_resume,
  ess_backend_uart_write,
  ess_backend_uart_read,
  ess_backend_uart_flush,
  ess_backend_uart_set_sample_format,
  ess_backend_uart_get_name,
  ess_backend_uart_get_info,
  0,
};
ess_backend_facktory_t* ess_backend_uart_getFactory() {
  return &_uart_backend_config;
}
#endif
