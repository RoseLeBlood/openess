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



#include "platform/esp32/esp32_ess_wifi_ap_net_device.h"

#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <lwip/dns.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>


#include <esp_err.h>
#include <lwip/ip_addr.h>
#include "dhcpserver/dhcpserver_options.h"

esp_err_t eventHandler(void* ctx, system_event_t* event) {
  return ESP_OK;
}

esp32_ess_wifi_ap_net_device::esp32_ess_wifi_ap_net_device(std::string name,
  std::string password, uint8_t channel,
  bool ssid_hidden, uint8_t max_connection,
  ess_wifi_auth_mode_t authmode)
  : ess_wifi_net_device(name, password, channel, ssid_hidden, max_connection, authmode) {

}

ess_error_t esp32_ess_wifi_ap_net_device::initialize() {
  tcpip_adapter_ip_info_t ip;
  ip6_addr_t addr;

  esp_event_loop_init(eventHandler, 0);

  nvs_flash_init();
  tcpip_adapter_init();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);

  esp_wifi_set_mode(WIFI_MODE_AP);

  wifi_config_t apConfig;
  memset(&apConfig, 0, sizeof(apConfig));

  strlcpy(reinterpret_cast<char*>(apConfig.ap.ssid), m_strName.c_str(), sizeof(apConfig.ap.ssid));
  apConfig.ap.ssid_len = strlen(reinterpret_cast<char *>(apConfig.ap.ssid));
  apConfig.ap.channel         = m_iChannel;
  apConfig.ap.ssid_hidden     = (uint8_t) m_bSsidhidden ? 1 : 0;
  apConfig.ap.max_connection  = m_iMaxConnections;
  apConfig.ap.beacon_interval = 100;

  if(m_iAuthmode == ESS_WIFI_AUTH_MODE_WPA2_PSK) {
      apConfig.ap.authmode        = WIFI_AUTH_WPA2_PSK;
      strlcpy(reinterpret_cast<char*>(apConfig.ap.password), m_strPassword.c_str() , sizeof(apConfig.ap.password));
  } else {
      apConfig.ap.authmode        = WIFI_AUTH_OPEN;
      *apConfig.ap.password = 0;
  }

  esp_wifi_set_config(WIFI_IF_AP, &apConfig);
  esp_wifi_start();

  tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);



  ess_platform_sleep(1);
  m_fStatus = ESS_NET_DEVICE_STATUS_UP;

  tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_AP);
  tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ip);
  tcpip_adapter_get_ip6_linklocal(TCPIP_ADAPTER_IF_AP, &addr);

  m_if_address.local_address4 = ess_ip4address(ip.ip.addr);
  m_if_address.local_address6 = ess_ip6address(addr.addr);

  return ESS_OK;
}

ess_error_t esp32_ess_wifi_ap_net_device::discconnect() {
    wifi_config_t conf;

    *conf.ap.ssid     = 0;
    *conf.ap.password = 0;
    conf.ap.authmode  = WIFI_AUTH_OPEN;
    if( esp_wifi_set_config(WIFI_IF_AP, &conf) == ESP_OK )
      return ESS_OK;

    return ESS_ERROR;
}

ess_error_t esp32_ess_wifi_ap_net_device::change_if_address(if_address if_addr) {
  tcpip_adapter_ip_info_t ip;
  ip6_addr_t addr;

  ess_error_t error = ESS_ERROR;

  esp_wifi_start();

  tcpip_adapter_ip_info_t info;
  info.ip.addr = static_cast<uint32_t>(if_addr.local_address4);
  info.gw.addr = static_cast<uint32_t>(if_addr.dns_address4);
  info.netmask.addr = static_cast<uint32_t>(if_addr.sub_net_mask);

  tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);

  if(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info) == ESP_OK) {
      dhcps_lease_t lease;
      lease.enable = true;
      lease.start_ip.addr = static_cast<uint32_t>(if_addr.local_address4) + (1 << 24);
      lease.end_ip.addr = static_cast<uint32_t>(if_addr.local_address4) + (11 << 24);

      tcpip_adapter_dhcps_option(
        (tcpip_adapter_option_mode_t)TCPIP_ADAPTER_OP_SET,
        (tcpip_adapter_option_id_t)REQUESTED_IP_ADDRESS,
        (void*)&lease, sizeof(dhcps_lease_t)
    );

    error =  (tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP) == ESP_OK) ?
      ESS_OK : ESS_ERROR;

    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ip);
    tcpip_adapter_get_ip6_linklocal(TCPIP_ADAPTER_IF_AP, &addr);

    m_if_address.local_address4 = ess_ip4address(ip.ip.addr);
    m_if_address.local_address6 = ess_ip6address(addr.addr);
  }
  return error;
}

std::string esp32_ess_wifi_ap_net_device::get_mac_address() {
  uint8_t mac[6];
  char macStr[18] = { 0 };

  esp_wifi_get_mac(WIFI_IF_AP, mac);

  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  return std::string(macStr);
}
void esp32_ess_wifi_ap_net_device::set_mac_adress(std::string mac) {

}

std::string esp32_ess_wifi_ap_net_device::get_hostname() {
  const char * hostname = NULL;

  if(tcpip_adapter_get_hostname(TCPIP_ADAPTER_IF_AP, &hostname)) {
      return "";
  }
  return hostname;
}
void esp32_ess_wifi_ap_net_device::set_hostname(std::string host) {
  tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_AP, host.c_str());
}

std::string esp32_ess_wifi_ap_net_device::to_string() {
  uint8_t primaryChan;
  wifi_second_chan_t secondChan;
  wifi_config_t conf;


  esp_wifi_get_channel(&primaryChan, &secondChan);
  esp_wifi_get_config(WIFI_IF_STA, &conf);

  const char* ssid = reinterpret_cast<const char*>(conf.sta.ssid);
  const char* passphrase = reinterpret_cast<const char*>(conf.sta.password);


  std::ostringstream ss;
  ss << "WiFi Access Point Channel: " ;
  ss  << primaryChan << "SSID: " << ssid << " Passphrase: " <<  passphrase << "BSSID set: "
       << conf.sta.bssid_set;

  return  ss.str();
}
