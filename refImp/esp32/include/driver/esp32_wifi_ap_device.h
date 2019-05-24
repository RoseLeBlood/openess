#ifndef __ESS_ESP32_WIFI_AP_DEVICE__
#define __ESS_ESP32_WIFI_AP_DEVICE__

#include "esp32_ess.h"
#include "platform/esp32/esp32_ess_wifi_ap_net_device.h"



class esp32_wifi_ap_device : public esp32_ess_wifi_ap_net_device {
public:
  esp32_wifi_ap_device() :
      esp32_ess_wifi_ap_net_device(ESP32_WIFI_NAME, ESP32_WIFI_PASSWORD,
        ESP32_WIFI_CHANNEL, ESP32_WIFI_SSID_HIDDEN,
        ESP32_WIFI_MAX_CONNECT, ESP32_WIFI_AUTH_MODE) { }
};

#endif
