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
 * @file backend.c
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief ESS backend factory  source
 *
 */
#include "backend.h"

#include "context.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <esp_log.h>

#ifdef ESS_ENABLE_BACKEND_UART
  #include "backend/uart_backend.h"
#endif

#ifdef ESS_ENABLE_BACKEND_I2S
  #include "backend/i2s_gerneric_backend.h"
#endif

#ifdef ESS_ENABLE_BACKEND_UART
  #include "backend/uart_backend.h"
#endif

#ifdef ESS_ENABLE_BACKEND_UDP
  #include "backend/udp_backend.h"
#endif

#include "backend/null_backend.h"

#define LOG_TAG "EssB"


typedef struct ess_backends_entry {
    const char* name;
    ess_backend_facktory_t* (* getFactory)(void);
}ess_backends_entry_t;

ess_backends_entry_t backends_list[] = {
#ifdef ESS_ENABLE_BACKEND_UART
  { "uart", ess_backend_uart_getFactory},
#endif
#ifdef ESS_ENABLE_BACKEND_I2S
  { "i2s_generic", ess_backend_i2s_generic_getFactory},
#endif
#ifdef ESS_ENABLE_BACKEND_UDP
  { "udp", ess_backend_udp_getFactory},
#endif
  { "null", ess_backend_null_getFactory},
};

int ess_backend_get_size() {
  return sizeof(backends_list) / sizeof(ess_backends_entry_t);
}


ess_backend_error_t ess_backend_probe_all(ess_format_t format, ess_backend_facktory_t** backend) {
  ess_backend_facktory_t *factory;

  unsigned int i,n = 0;

  for( i = 0; i < ess_backend_get_size(); i++ ) {
    factory = backends_list[i].getFactory();

    if(factory->ess_backend_probe(format) != ESS_BACKEND_OK) {
      ESP_LOGE(LOG_TAG, "Failed to probe backend \"%s\"", backends_list[n].name);
      continue;
    } else {
      ESP_LOGI(LOG_TAG,"Possible format for backend: \"%s\" ", backends_list[n].name);
      if(backend) { backend[n] = factory; }
      n++;
    }

  }
  ESP_LOGI(LOG_TAG,"%d/%d backends probe possible\n", n, ess_backend_get_size());

  if(n == 0) return ESS_BACKEND_ERROR_WRONG_FORMAT;
  return n;
}

ess_backend_error_t ess_backend_probe(const char* name, ess_format_t format, ess_backend_facktory_t* backend) {
  for(unsigned int i = 0; i < ess_backend_get_size(); i++ ) {
    if(strcmp(backends_list[i].name, name)) {
      if(backends_list[i].getFactory()->ess_backend_probe(format)) {
        if(backend) backend = backends_list[i].getFactory();
        return ESS_BACKEND_OK;
      } else {
        return ESS_BACKEND_ERROR_WRONG_FORMAT;
      }
    }
  }
  return ESS_BACKEND_ERROR;
}
