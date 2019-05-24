#ifndef __ESS_ESP32_WIFI_TASK__
#define __ESS_ESP32_WIFI_TASK__

#include "esp32_ess.h"
#include "esp32_wifi_ap_device.h"

class esp32_ap_wifi_cpu0_task : public ess_task {
public:
  esp32_ap_wifi_cpu0_task() :
    ess_task("wifi" , 0, 4096) { }

  virtual void onTask(void* userdata);
private:
  esp32_wifi_ap_device m_wifiDevice;
};

#endif
