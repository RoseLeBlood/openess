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
 * @file esp32_ess_wifi_ap_net_device.h
 * @author Anna Sopdia Schröck
 * @date 24 Mai 2019
 */
 #ifndef _ESS_ESP32_NET_INTERFACE_DEVICE_H_
 #define _ESS_ESP32_NET_INTERFACE_DEVICE_H_

#include "net/ess_wifi_net_device.h"


class esp32_ess_wifi_ap_net_device : public ess_wifi_net_device {
public:
  esp32_ess_wifi_ap_net_device(std::string name, std::string password, uint8_t channel = 1,
    bool ssid_hidden = 0, uint8_t max_connection = 4,
    ess_wifi_auth_mode_t authmode = ESS_WIFI_AUTH_MODE_WPA2_PSK);

  virtual ess_error_t initialize();
  virtual ess_error_t set_status(ess_net_device_status nstet)  { return ESS_ERROR; }
  virtual ess_error_t change_if_address(if_address if_addr);
  virtual ess_error_t discconnect();

  virtual std::string get_mac_address();
  virtual void set_mac_adress(std::string mac);

  virtual std::string get_hostname();
  virtual void set_hostname(std::string host);

  virtual std::string to_string();
};

#endif
