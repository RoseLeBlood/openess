#include "config.h"
#ifdef ESS_CONFIC_TASK_ESP32

#include "ess_backend.h"
#include "ess_platform.h"


#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpT"

static int task_id = 0;

ess_platform_error_t ess_platform_sleep(unsigned int ms) {
  vTaskDelay(ms / portTICK_PERIOD_MS);
  return ESS_PLATFORM_ERROR_OK;
}
unsigned int ess_platform_get_tick_count() {
  return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS);
}


ess_platform_error_t ess_platform_task_create(ess_platform_task_t* task, void task_func(void*),
    const char* taskName, void* param, unsigned int stackSize) {
      if(task == 0) return ESS_PLATFORM_ERROR_NULL;


      strncpy(task->name, taskName, sizeof(task->name) );

      task->parem = param;
      task->stack_size = stackSize;
      task->task = task_func;
      task->userdata = param;
      task->task_id = task_id++;
      task->handle = 0;
      task->priority = 5;

      return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_task_start(ess_platform_task_t* task) {
  xTaskCreate(task->task, task->name, task->stack_size, task->userdata , task->priority,  task->handle);

  return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_task_delete(ess_platform_task_t* task) {
  if(task == 0) return ESS_PLATFORM_ERROR_NULL;

  vTaskDelete(task->handle);

  return ESS_PLATFORM_ERROR_OK;
}
#endif
