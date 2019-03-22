#ifndef __ESS_ESP32_WIFI_TASK__
#define __ESS_ESP32_WIFI_TASK__

#include "ess.h"
#include "task/ess_task.h"

#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <lwip/dns.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>

class wifi_task : public ess_task {
public:
  wifi_task(const char* name, const char* password, wifi_auth_mode_t authmode = WIFI_AUTH_WPA2_PSK) :
    ess_task("wifi" , 0, 4096), m_strName(name), m_strPassword(password), m_iAuthmode(authmode) { }

  virtual void onTask(ess_task* self, void* userdata);

  const char* get_ssid() { return m_strName; }
  const char* get_passwd() { return m_strPassword; }
  wifi_auth_mode_t get_authmode() { return m_iAuthmode; }

  bool is_ready() { return m_bReady; }
private:
  const char* m_strName;
  const char* m_strPassword;
  wifi_auth_mode_t m_iAuthmode;
  bool volatile  m_bReady;
};

#endif
