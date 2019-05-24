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
#include "net/ess_wifi_net_device.h"

ess_wifi_net_device::ess_wifi_net_device(std::string name, std::string password, uint8_t channel,
  bool ssid_hidden, uint8_t max_connection,
  ess_wifi_auth_mode_t authmode) : ess_net_device(ESS_NET_DEVICE_WIFI, name) {

  m_strPassword = password;
  m_iAuthmode = authmode;
  m_iChannel = channel;
  m_bSsidhidden = ssid_hidden;
   m_iMaxConnections =max_connection ;
}
