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
#include "ess_backend.h"

#include "ess_context.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <esp_log.h>


#define LOG_TAG "EssB"

#include "ess_platform.h"


int ess_backend_get_size() {
  return sizeof(backends_list) / sizeof(ess_backends_entry_t);
}
ess_backend_facktory_t* ess_backend_create_factory_list() {
  return (ess_backend_facktory_t*)malloc(sizeof(ess_backend_facktory_t) * ess_backend_get_size());
}
ess_backend_error_t ess_backend_destroy_factory_list(ess_backend_facktory_t* list) {
  if(list == 0)  return ESS_BACKEND_ERROR_NULL;
  //free(list);
  return ESS_BACKEND_OK;
}
ess_backend_error_t ess_backend_probe_all(ess_format_t format, ess_backend_facktory_t** backend, int* size) {
  ess_backend_facktory_t *factory = 0;

  unsigned int i,n = 0;

  for( i = 0; i < ess_backend_get_size(); i++ ) {
    factory = backends_list[i].getFactory();

    if(factory->ess_backend_probe(format) == ESS_BACKEND_OK) {
      if(*backend) { backend[n] = factory; } n++;
    }
  }
  ESP_LOGI(LOG_TAG,"%d/%d backends probe possible\n", n, ess_backend_get_size());

  if(size) *size = n;
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
ess_backend_error_t ess_backend_set_sample_format(ess_backend_facktory_t* backend,  ess_format_t forma) {
  if(backend == 0) return ESS_BACKEND_ERROR_NULL;
  return backend->ess_backend_set_sample_format(forma);
}
void* ess_backend_get_user_daten(ess_backend_facktory_t* backend) {
  if(backend == 0)  return 0;
  return  backend->user_daten;
}
ess_backend_error_t ess_backend_set_user_daten(ess_backend_facktory_t* backend, void* data) {
  if(backend == 0)  return ESS_BACKEND_ERROR_NULL;
  backend->user_daten = data;
  return ESS_BACKEND_OK;
}
