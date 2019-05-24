
#ifndef _ESP32_ESS_DRIVER_TASK_GROUP_H_
#define _ESP32_ESS_DRIVER_TASK_GROUP_H_

#include "esp32_ap_wifi_cpu0_task.h"
#include "task/ess_task_group.h"
#include "esp_log.h"

class esp32_driver_task_group : public ess_task_group {
public:
  esp32_driver_task_group() : ess_task_group("esp32_driver_task_group") {
    add(new esp32_ap_wifi_cpu0_task());
  }
};
#endif
