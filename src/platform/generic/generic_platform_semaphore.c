// PTHREAD
#include "config.h"
#ifdef ESS_CONFIG_SEMAPHORE_GENERIC
#include "ess_backend.h"
#include "ess_platform.h"

#include <stdio.h>
#include <string.h>

#include <pthread.h>


ess_platform_error_t ess_platform_semaphore_create(ess_platform_semaphore_t* semp, const char* name) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  strcpy(semp->name, name);

  pthread_mutex_init(&semp->handle, 0);

  return semp->handle != 0 ?  ESS_PLATFORM_ERROR_OK : ESS_PLATFORM_ERROR ;
}
ess_platform_error_t ess_platform_semaphore_destroy(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  pthread_mutex_destroy(&semp->handle);

   return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_semaphore_give_ex(ess_platform_semaphore_t* semp, int value) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;
  semp->value = value;

  pthread_mutex_unlock(&semp->handle);

  return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_semaphore_give(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  pthread_mutex_unlock(&semp->handle);

  return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_semaphore_give_isr(ess_platform_semaphore_t* semp) {
  return ESS_PLATFORM_NOT_IMP;
}
ess_platform_error_t  ess_platform_semaphore_take_ex(ess_platform_semaphore_t* semp,  unsigned int timeout_ms) {
  return ESS_PLATFORM_NOT_IMP;
}
ess_platform_error_t ess_platform_semaphore_take(ess_platform_semaphore_t* semp) {

  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  pthread_mutex_lock(&semp->handle);

  return ESS_PLATFORM_ERROR_OK;
}
ess_platform_error_t ess_platform_semaphore_wait(ess_platform_semaphore_t* semp, int* value) {
  if(semp == 0) return ESS_PLATFORM_ERROR_NULL;
  if(semp->handle == 0) return ESS_PLATFORM_NOT_CREATED;

  pthread_mutex_lock(&semp->handle);
  pthread_mutex_unlock(&semp->handle);

  if(value) *value = semp->value;
  return ESS_PLATFORM_ERROR_OK;
}
#endif
