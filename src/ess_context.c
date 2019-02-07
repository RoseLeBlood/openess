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
 * @file context.c
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief ESS context source
 *
 */

#include "ess_context.h"
#include "ess_backend.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <esp_log.h>
#include "config.h"

#define LOG_TAG "EssC"


ess_error_t ess_context_create(ess_context_t* context, const char* name, const ess_format_t format) {
  if(context == 0) { return ESS_ERROR_NULL; }

  ess_backend_facktory_t* backend = ess_backend_get_by_name(name);
  if(backend == 0) {
    ESP_LOGE(LOG_TAG,"Backend with name: %s not found", name);
    return ESS_ERROR_NOBACKEND;
  }

 if(backend->ess_backend_probe(format) == ESS_OK) {
   if(backend->ess_backend_open(format) != ESS_OK) {
     ESP_LOGE(LOG_TAG,"Backend with name: %s error open", name);
     return ESS_ERROR_WRONG_FORMAT;
   }
 }
  context->format = format;
  context->status = ESS_CONTEXT_STATUS_RUN;
  context->backend = backend;

  ESP_LOGI(LOG_TAG,"Backend with name: %s found and open", name);
  return ESS_OK;
}
ess_error_t  ess_context_create_ex(ess_context_t* context, ess_backend_facktory_t* backend, const ess_format_t format) {
  if(context == 0) { return ESS_ERROR_NULL; }
  if(backend == 0) return ESS_ERROR_NOBACKEND;

  if(backend->ess_backend_probe(format) == ESS_OK) {
    if(backend->ess_backend_open(format) != ESS_OK) {
      ESP_LOGE(LOG_TAG,"Backend with name: %s error open", backend->get_name());
      return ESS_ERROR_WRONG_FORMAT;
    }
  }
   context->format = format;
   context->status = ESS_CONTEXT_STATUS_RUN;
   context->backend = backend;

   ESP_LOGI(LOG_TAG,"Backend with name: %s found and open",  backend->get_name());
   return ESS_OK;
}
ess_error_t ess_context_close(ess_context_t* context) {
  if(context == 0) return ESS_ERROR_NULL;
  if(context->backend == 0)  return context->last_error =  ESS_ERROR_NOBACKEND;

  context->backend->ess_backend_close();
  context->status = ESS_CONTEXT_STATUS_CLOSE;

  context->last_error = ESS_OK;
  return ESS_OK;

}

ess_error_t ess_context_destroy(ess_context_t* context) {
  if(context == 0) return ESS_ERROR_NULL;
  ess_context_close(context);

  context->last_error = ESS_OK;
  return ESS_OK;
}

ess_error_t ess_context_paused(ess_context_t* context) {
  if(context == 0) return ESS_ERROR_NULL;
  if(context->backend == 0)  return context->last_error =  ESS_ERROR_NOBACKEND;

  context->status = ESS_CONTEXT_STATUS_PAUSED;
  context->backend->ess_backend_pause();

  context->last_error = ESS_OK;
  return ESS_OK;
}
ess_error_t ess_context_resume(ess_context_t* context) {
  if(context == 0) return ESS_ERROR_NULL;
  if(context->backend == 0)  return context->last_error =  ESS_ERROR_NOBACKEND;

  context->status = ESS_CONTEXT_STATUS_RUN;
  context->backend->ess_backend_resum();

  context->last_error = ESS_OK;
  return ESS_OK;
}

ess_error_t ess_context_set_format(ess_context_t* context, const ess_format_t format) {
  if(context == 0) return ESS_ERROR_NULL;
  if(context->backend == 0)  return context->last_error =  ESS_ERROR_NOBACKEND;

  return (ess_backend_set_sample_format(context->backend, format) != 0) ? ESS_ERROR_WRONG_FORMAT : ESS_ERROR_NULL;
}

unsigned int ess_context_write(ess_context_t* context, void *buffer, unsigned int buf_size) {
  unsigned int wrote;
  ess_context_write_ex(context, buffer, buf_size, &wrote);
  return wrote;
}
ess_error_t ess_context_write_ex(ess_context_t* context, void *buffer, unsigned int buf_size,  unsigned int* wrote) {
  if(context == 0) return ESS_ERROR_NULL;
  if(context->status == ESS_CONTEXT_STATUS_PAUSED) return context->last_error = ESS_ERROR_PAUSED;
  if(context->backend == 0)  return context->last_error =  ESS_ERROR_NOBACKEND;

  context->backend->ess_backend_write(buffer, buf_size, wrote);

  return  ESS_OK;
}

const char* ess_context_get_backend_name(ess_context_t* context) {
  if(context == 0) return 0;
  return context->backend->get_name();
}
const char* ess_context_get_backend_info(ess_context_t* context) {
  if(context == 0) return 0;
  return context->backend->get_info();
}
ess_error_t ess_context_get_last_error(ess_context_t* context) {
  if(context == 0) return ESS_ERROR_NULL;
  return context->last_error;
}
