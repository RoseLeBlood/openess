#include "ess.h"
#include "ess_task.h"

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
  bool m_bReady;
};

wifi_task wifi("OpenESS Daemon\0", "Qwertz1234\0" );


extern "C" void app_main() {
  ess_error_t error = wifi.start();
  ESS_ERROR(error) ; while(!wifi.is_ready()) { sleep(5); }

  printf("Wifi is ready to take off \n");

  for(;;)  { ess_platform_sleep(10); }
}



esp_err_t eventHandler(void* ctx, system_event_t* event) {
  return ESP_OK;
}
void wifi_task::onTask(ess_task* self, void* userdata) {
  wifi_task *task_self = static_cast<wifi_task*>(self);
  if(task_self == 0) return;


  esp_err_t errRc;

  errRc = esp_event_loop_init(eventHandler, 0);

  nvs_flash_init();
  tcpip_adapter_init();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  errRc = esp_wifi_init(&cfg);
  errRc = esp_wifi_set_storage(WIFI_STORAGE_RAM);

  errRc = esp_wifi_set_mode(WIFI_MODE_AP);

  wifi_config_t apConfig;
	memset(&apConfig, 0, sizeof(apConfig));
	memcpy(apConfig.ap.ssid, task_self->get_ssid(), strlen(task_self->get_ssid()) );
	apConfig.ap.ssid_len = strlen(task_self->get_ssid()) ;
	memcpy(apConfig.ap.password, task_self->get_passwd(), strlen(task_self->get_passwd()) );
	apConfig.ap.channel         = 0;
	apConfig.ap.authmode        = task_self->get_authmode(); //WIFI_AUTH_WPA2_PSK;
	apConfig.ap.ssid_hidden     = (uint8_t) 0;
	apConfig.ap.max_connection  = 4;
	apConfig.ap.beacon_interval = 100;

  errRc = esp_wifi_set_config(WIFI_IF_AP, &apConfig);
  errRc = esp_wifi_start();

  errRc = tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);

  task_self->m_bReady = true;

  for(;;) { ess_platform_sleep(1); }


}
