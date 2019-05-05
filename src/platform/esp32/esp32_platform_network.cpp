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
 * @file esp32_platform_network.cpp
 * @author Anna Sopdia Schröck
 * @date 20 Februar 2019
 * @brief  platform specific socket functions for platform esp32
 *
 */
 #include "config.h"
 #ifdef ESS_CONFIG_NETWORK_ESP32

#include "net/ess_network.h"

# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <stdint.h>
# include <netdb.h> // getaddrinfo()
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <netinet/in.h>
#include <netdb.h>

# include <iostream>
# include <string>
# include <string.h>
# include <memory>
#include <sstream>

#include "esp_log.h"

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#define ESP_NET_TAG "esp32_socket"

int ess_socket(ess_socket_fam fam, ess_socket_type type, ess_socket_proto options) {
    return socket(ess_socket_fam2platform(fam),
                          ess_socket_type2platform(type),
                          options);
}
ess_error_t ess_socket_close(int socket) {
  if ( 0 > close(socket)) return ESS_ERROR_CLOSE;
  return ESS_OK;
}
int ess_setsockopt(int socket, int level, ess_socket_option_name_t optname, const char* optval, unsigned int optlen) {
  return setsockopt(socket, level, (int)optname, optval, optlen);
}

int ess_getsockopt(int socket, int level, ess_socket_option_name_t optname,
  char* optval, unsigned int* optlen) {
    return getsockopt(socket, level, optname, optval, optlen);
}

ess_error_t ess_socket_bind(int socket,  int port) {
  struct sockaddr_in serverAddress;
  memset(&serverAddress,0,sizeof(serverAddress));

	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr= INADDR_ANY;
	serverAddress.sin_port=htons(port);

	if(bind(socket,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
    ESP_LOGE(ESP_NET_TAG, "error to bind socket");
    return ESS_ERROR;
  }
  ESP_LOGI(ESP_NET_TAG, "ok to bind socket");
  return ESS_OK;
}

ess_error_t ess_socket_listen(int socket, int options) {
  if(listen(socket,options) < 0) {
    ESP_LOGE(ESP_NET_TAG, "error to listen");
    return ESS_ERROR;
  }
  ESP_LOGI(ESP_NET_TAG, "ok to listen");
  return ESS_OK;
}
ess_error_t ess_socket_accept(int socket, int* client) {
  struct sockaddr_in cli_addr;
  unsigned int clilen;

  memset(&cli_addr,0,sizeof(cli_addr));
  clilen = sizeof(cli_addr);

  *client = accept(socket, (struct sockaddr *) &cli_addr, &clilen);
  return ( (*client) < 0) ? ESS_ERROR : ESS_OK;
}
 #endif
