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
 * @file ess_wifi_net_device.h
 * @author Anna Sopdia Schröck
 * @date 05 Mai 2019
 */
 #ifndef _ESS_WIFI_NET_INTERFACE_DEVICE_H_
 #define _ESS_WIFI_NET_INTERFACE_DEVICE_H_

#include "ess_net_device.h"

typedef enum ess_wifi_auth_mode {
  ESS_WIFI_AUTH_MODE_OPEN,
  ESS_WIFI_AUTH_MODE_WPA2_PSK,
} ess_wifi_auth_mode_t;

class ess_wifi_net_device : public ess_net_device {
public:
  ess_wifi_net_device(std::string name, std::string password, uint8_t channel = 1,
    bool ssid_hidden = 0, uint8_t max_connection = 4,
    ess_wifi_auth_mode_t authmode = ESS_WIFI_AUTH_MODE_WPA2_PSK);

  virtual std::string get_ssid() const { return m_strName; }
  virtual std::string get_passwd() const { return m_strPassword; }
  virtual ess_wifi_auth_mode_t get_authmode() const { return m_iAuthmode; }

  virtual uint8_t get_channel() const  { return m_iChannel; }
  virtual bool is_ssid_hidden() const { return m_bSsidhidden; }
  virtual uint8_t get_max_connecions() const { return m_iMaxConnections; }
protected:
  std::string m_strPassword;
  ess_wifi_auth_mode_t m_iAuthmode;
  uint8_t m_iChannel;
  bool m_bSsidhidden;
  uint8_t m_iMaxConnections;
};

#endif
