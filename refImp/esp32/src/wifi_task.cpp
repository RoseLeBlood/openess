#include "wifi_task.h"
#include "sdkconfig.h"


esp_err_t eventHandler(void* ctx, system_event_t* event) ;

void wifi_task::onTask(ess_task* self, void* userdata) {
  wifi_task *task_self = static_cast<wifi_task*>(self);
  if(task_self == 0) return;


  esp_event_loop_init(eventHandler, 0);

  nvs_flash_init();
  tcpip_adapter_init();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
   esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);

  esp_wifi_set_mode(WIFI_MODE_AP);

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

  esp_wifi_set_config(WIFI_IF_AP, &apConfig);
  esp_wifi_start();

   tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);

  ess_platform_sleep(4);
  task_self->m_bReady = true;

  for(;;) { ess_platform_sleep(1); }


}



esp_err_t eventHandler(void* ctx, system_event_t* event) {
  return ESP_OK;
}
