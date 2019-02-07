/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file generic_platform_semaphore.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all generic platform semaphore functions source
 *
 *  using pthread
 */
#include "config.h"
#ifdef ESS_CONFIG_SEMAPHORE_GENERIC
#include "ess_backend.h"
#include "ess_platform.h"

#include <stdio.h>
#include <string.h>

#include <pthread.h>


ess_error_t ess_platform_semaphore_create(ess_platform_semaphore_t* semp, const char* name) {
  if(semp == 0) return ESS_ERROR_NULL;
  strcpy(semp->name, name);

  pthread_mutex_init(&semp->handle, 0);

  return semp->handle != 0 ?  ESS_OK : ESS_ERROR ;
}
ess_error_t ess_platform_semaphore_destroy(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_ERROR_NULL;
  if(semp->handle == 0) return ESS_ERROR_NOT_CREATED;

  pthread_mutex_destroy(&semp->handle);

   return ESS_OK;
}
ess_error_t ess_platform_semaphore_give_ex(ess_platform_semaphore_t* semp, int value) {
  if(semp == 0) return ESS_ERROR_NULL;
  if(semp->handle == 0) return ESS_ERROR_NOT_CREATED;
  semp->value = value;

  pthread_mutex_unlock(&semp->handle);

  return ESS_OK;
}
ess_error_t ess_platform_semaphore_give(ess_platform_semaphore_t* semp) {
  if(semp == 0) return ESS_ERROR_NULL;
  if(semp->handle == 0) return ESS_ERROR_NOT_CREATED;

  pthread_mutex_unlock(&semp->handle);

  return ESS_OK;
}
ess_error_t ess_platform_semaphore_give_isr(ess_platform_semaphore_t* semp) {
  return ESS_ERROR_NOT_IMP;
}
ess_error_t  ess_platform_semaphore_take_ex(ess_platform_semaphore_t* semp,  unsigned int timeout_ms) {
  return ESS_ERROR_NOT_IMP;
}
ess_error_t ess_platform_semaphore_take(ess_platform_semaphore_t* semp) {

  if(semp == 0) return ESS_ERROR_NULL;
  if(semp->handle == 0) return ESS_ERROR_NOT_CREATED;

  pthread_mutex_lock(&semp->handle);

  return ESS_OK;
}
ess_error_t ess_platform_semaphore_wait(ess_platform_semaphore_t* semp, int* value) {
  if(semp == 0) return ESS_ERROR_NULL;
  if(semp->handle == 0) return ESS_ERROR_NOT_CREATED;

  pthread_mutex_lock(&semp->handle);
  pthread_mutex_unlock(&semp->handle);

  if(value) *value = semp->value;
  return ESS_OK;
}
#endif
