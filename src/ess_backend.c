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
ess_backends_entry_t* ess_backend_get_list(unsigned int* size) {
  if(size != 0) *size = ( sizeof(backends_list) / sizeof(ess_backends_entry_t) );
  return backends_list;
}

ess_backend_facktory_t* ess_backend_get_by_index(unsigned int index)  {
  if(index > ess_backend_get_size() ) return 0;
  return backends_list[index].getFactory();
}


ess_backend_facktory_t* ess_backend_get_by_name(const char* name)  {
  ess_backend_facktory_t* factory = 0;

  for(unsigned int i = 0; i < ess_backend_get_size(); i++ ) {
    if(strcmp(backends_list[i].name, name)) {
      factory = backends_list[i].getFactory();
      break;
    }
  }
  return factory;
}

ess_backend_error_t ess_backend_probe_ex(const char* name, ess_format_t format, ess_backend_facktory_t* backend) {
  for(unsigned int i = 0; i < ess_backend_get_size(); i++ ) {
    if(strcmp(backends_list[i].name, name)) {
      if(backends_list[i].getFactory()->ess_backend_probe(format) == ESS_BACKEND_OK) {
        if(backend) backend = backends_list[i].getFactory();
        return ESS_BACKEND_OK;
      } else {
        return ESS_BACKEND_ERROR_WRONG_FORMAT;
      }
    }
  }
  return ESS_BACKEND_ERROR;
}
ess_backend_error_t ess_backend_probe(const ess_format_t format, ess_backend_facktory_t* backend) {
  if(backend == 0) return ESS_BACKEND_NULL;
  return backend->ess_backend_probe(format);
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
