#include "driver/esp32_ap_wifi_cpu0_task.h"
#include "sdkconfig.h"

#include "esp32_platform_instance.h"

void esp32_ap_wifi_cpu0_task::onTask(void* userdata) {

  if(m_wifiDevice.initialize() == ESS_OK)
    esp32_platform_instance::instance().set_wifi_ready();


  ess_platform_sleep(2);

  // exit task when ready
}
