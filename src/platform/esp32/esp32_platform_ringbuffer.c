#include "config.h"
#ifdef ESS_CONFIG_RINGBUFFER_ESP32

#include "ess_backend.h"
#include "ess_platform.h"


#include <stdio.h>
#include <string.h>

#include  <freertos/FreeRTOS.h>   // Include the base FreeRTOS definitions
#include "freertos/queue.h"
#include "freertos/ringbuf.h"

#include "esp_log.h"
#define LOG_TAG  "OesSpR"

ess_platform_error_t ess_platform_ringbuffer_create(ess_platform_ringbuffer_t* rng,
  unsigned int length,  ess_platform_ringbuffer_mode_t type, const char* name) {
  if(rng == 0) return ESS_PLATFORM_ERROR_NULL;
  strncpy(rng->name, name, sizeof(rng->name) );

  rng->type = type;

  if(type == ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT)
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_NOSPLIT);
  else if(type == ESS_PLATFORM_RINGBUFFER_MODE_ALLOWSPLIT)
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_ALLOWSPLIT);
  else
    rng->handle = xRingbufferCreate(length, RINGBUF_TYPE_BYTEBUF);

  rng->qhandle = xQueueCreateSet(3);
  if (xRingbufferAddToQueueSetRead(rng->handle, rng->qhandle) != pdTRUE) {
      printf("Failed to add to queue set\n");
      return ESS_PLATFORM_ERROR;
  }

  return rng->handle == 0 ? ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR;
}
ess_platform_error_t ess_platform_ringbuffer_write(ess_platform_ringbuffer_t* rng,
    void* data, unsigned int length, unsigned int ms) {
      if(rng == 0) return ESS_PLATFORM_ERROR_NULL;

    return ( xRingbufferSend(rng->handle, data, length, pdMS_TO_TICKS(ms)) == pdTRUE ) ?
      ESS_PLATFORM_ERROR_OK :  ESS_PLATFORM_ERROR;
}
void* ess_platform_ringbuffer_read(ess_platform_ringbuffer_t* rng, unsigned int* length, unsigned int ms) {
    if(rng == 0) return (void*)(ESS_PLATFORM_ERROR_NULL);

    return xRingbufferReceive(rng->handle, length, pdMS_TO_TICKS(ms));
}
ess_platform_error_t ess_platform_ringbuffer_can_read(ess_platform_ringbuffer_t* rng, unsigned int ms) {
  if(rng == 0) return ESS_PLATFORM_ERROR_NULL;

  xQueueSetMemberHandle member = xQueueSelectFromSet(rng->qhandle, pdMS_TO_TICKS(ms));

  return (member != NULL && xRingbufferCanRead(rng->handle, member) == pdTRUE) ?
    ESS_PLATFORM_ERROR_OK :  ESS_PLATFORM_ERROR;
}
#endif
