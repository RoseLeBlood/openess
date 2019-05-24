#ifndef __ESP32_OPENESS_CONFIG_H__
#define __ESP32_OPENESS_CONFIG_H__

#include "ess.h"
#include "ess_platform.h"
#include "task/ess_task.h"

#include "core/module/ess_output_module.h"
#include "core/module/ess_input_module.h"
#include "core/module/ess_null_input_module.h"

#include "esp32_platform_instance.h"

#define ESS_WIFI_MODE_AP   1
#define ESS_WIFI_MODE_STA 2


#define ESP32_OPENESS_DEBUG              ESS_ON
#define ESP32_WIFI_MODE                         ESS_WIFI_MODE_AP

#define ESP32_WIFI_NAME                        "OpenESS_ESP32-Node"
#define ESP32_WIFI_AUTH_MODE          ESS_WIFI_AUTH_MODE_WPA2_PSK
#define ESP32_WIFI_PASSWORD               "Q12345678#"
#define ESP32_WIFI_CHANNEL                 8
#define ESP32_WIFI_SSID_HIDDEN          false
#define ESP32_WIFI_MAX_CONNECT      4

#endif
