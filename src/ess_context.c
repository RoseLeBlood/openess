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

ess_context_error_t ess_context_create(ess_context_t* context, ess_format_t format) {
  context = (ess_context_t*)malloc(sizeof(ess_context_t));
  if(context == 0) { context->last_error = ESS_CONTEXT_ERROR_OUTOFMEM;
    return ESS_CONTEXT_ERROR_OUTOFMEM; }

  context->format = format;
  context->status = ESS_CONTEXT_STATUS_CREATED;
  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;
}
ess_context_error_t ess_context_init(ess_context_t* context, const char* name) {
  if(context == 0) return ESS_CONTEXT_ERROR;

  ess_backend_facktory_t* backend = 0;

  if(ess_backend_probe(name, context->format, backend) == ESS_BACKEND_OK)
    return ess_context_init_ex(context, backend);
  context->status = ESS_CONTEXT_STATUS_ERROR;

  return ESS_CONTEXT_ERROR;
}
ess_context_error_t ess_context_init_ex(ess_context_t* context, ess_backend_facktory_t* backend) {
  if(backend == 0 && backend == 0) {
    context->last_error = ESS_CONTEXT_ERRORNOBACKEND;
    return ESS_CONTEXT_ERRORNOBACKEND;
  }

  if(backend->ess_backend_open(context->format) != 0) {
    ESP_LOGE(LOG_TAG,"Error to open backend");
    return -1;
  } else {
    context->backend = backend;
    context->status = ESS_CONTEXT_STATUS_RUN;
    ESP_LOGI(LOG_TAG,"Possible to open backend");
  }
  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;
}
ess_context_error_t ess_context_close(ess_context_t* context) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  if(context->backend == 0)  return context->last_error =  ESS_CONTEXT_ERRORNOBACKEND;

  context->backend->ess_backend_close();
  context->status = ESS_CONTEXT_STATUS_CLOSE;

  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;

}

ess_context_error_t ess_context_destroy(ess_context_t* context) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  ess_context_close(context);
  if(context->backend != 0) free(context->backend );
  if(context != 0) free(context );

  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;
}

ess_context_error_t ess_context_paused(ess_context_t* context) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  if(context->backend == 0)  return context->last_error =  ESS_CONTEXT_ERRORNOBACKEND;

  context->status = ESS_CONTEXT_STATUS_PAUSED;
  context->backend->ess_backend_pause();

  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;
}
ess_context_error_t ess_context_resume(ess_context_t* context) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  if(context->backend == 0)  return context->last_error =  ESS_CONTEXT_ERRORNOBACKEND;

  context->status = ESS_CONTEXT_STATUS_RUN;
  context->backend->ess_backend_resum();

  context->last_error = ESS_CONTEXT_ERROR_OK;
  return ESS_CONTEXT_ERROR_OK;
}

ess_context_error_t ess_context_set_format(ess_context_t* context, ess_format_t format) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  if(context->backend == 0)  return context->last_error =  ESS_CONTEXT_ERRORNOBACKEND;

  return (ess_backend_set_sample_format(context->backend, format) != 0) ? ESS_CONTEXT_WRONGFORMAT : ESS_CONTEXT_ERROR_OK;
}

unsigned int ess_context_write(ess_context_t* context, void *buffer, int buf_size) {
  unsigned int wrote;
  ess_context_write_ex(context, buffer, buf_size, &wrote);
  return wrote;
}
ess_context_error_t ess_context_write_ex(ess_context_t* context, void *buffer, int buf_size,  unsigned int* wrote) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  if(context->status == ESS_CONTEXT_STATUS_PAUSED) return context->last_error = ESS_CONTEX_ISPAUSED;
  if(context->backend == 0)  return context->last_error =  ESS_CONTEXT_ERRORNOBACKEND;

  context->backend->ess_backend_write(buffer, buf_size, wrote);

  return  ESS_CONTEXT_ERROR_OK;
}

const char* ess_context_get_backend_name(ess_context_t* context) {
  if(context == 0) return 0;
  return context->backend->get_name();
}
const char* ess_context_get_backend_info(ess_context_t* context) {
  if(context == 0) return 0;
  return context->backend->get_info();
}
ess_context_error_t ess_context_get_last_error(ess_context_t* context) {
  if(context == 0) return ESS_CONTEXT_ERROR;
  return context->last_error;
}
