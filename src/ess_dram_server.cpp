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
 * @file ess_dram_server.cpp
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ess generic dram server
 *
 */


#include "ess.h"
#include "ess_server.h"
#include "ess_dram_server.h"

#include "esp_log.h"

#define LOG_TAG "ess_dram_server"

ess_dram_server::ess_dram_server(std::string name,  ess_format_t format)
  : ess_server(name, format) {

}
ess_error_t ess_dram_server::create(std::string backend_name, std::string host, std::string port, ess_socket_fam fam, bool lite) {
  m_pServerSocket = new ess_inet_dram_server(host, port, fam, lite);
  if(m_pServerSocket == 0) {
    ESP_LOGE(LOG_TAG, "ess_inet_dram_server - Out of Mem");
     return ESS_ERROR_OUTOFMEM;
   }
  ESP_LOGI(LOG_TAG, "OpenESS dram%d socket opened", fam == ESS_SOCKET_FAMILY_IP4 ? 4 : 6);

  m_pContext = new ess_context();
  if(m_pContext == 0) {
    ESP_LOGE(LOG_TAG, "ess_context - Out of Mem");
     return ESS_ERROR_OUTOFMEM;
   }
   ess_error_t error = m_pContext->create(backend_name.c_str(), m_eFormat);
   ESS_ERROR(error);

  return error;
}
