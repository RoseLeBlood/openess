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

#include "config.h"
#ifdef  ESS_CONFIG_MEMORY_ESP32

#include "platform/ess_memory.h"

#include <stdlib.h>
#include "string.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_heap_caps.h"



void* ess_malloc(unsigned int size) {
  #if CONFIG_SPIRAM_BOOT_INIT
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  #else
    return malloc(size);
  #endif
}

void* ess_calloc(size_t nmemb, size_t size) {
  void *data =  NULL;
#if CONFIG_SPIRAM_BOOT_INIT
  data = heap_caps_malloc(nmemb * size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  if (data) {
      ess_zeromem(data, nmemb * size);
  }
#else
  data = calloc(nmemb, size);
#endif
  return data;
}

void* ess_realloc(void *ptr, size_t size) {
  if(!ptr) return NULL;

  void *newdata = ess_malloc(size);
  ess_memcpy(newdata, ptr, size);
  ess_free(ptr);

  return (ptr =newdata);
}

void ess_free(void* buffer) {
  free(buffer);
}

void ess_zeromem(void* buffer, unsigned int size) {
  ess_memset(buffer, 0, size);
}

void ess_memset(void* buffer, int data, unsigned int size) {
  memset(buffer, data, size);
}

void ess_memcpy(void* dest, const void* src, unsigned int size) {
  memcpy(dest, src, size);
}

#endif
