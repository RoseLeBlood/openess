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
 * @file ess_context.cpp
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
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



ess_error_t  ess_context::create(const char* name, const ess_format_t format) {
 ess_backend_t& ins = ess_backend_t::Instance();
 ess_backend* backend = ins.get_backend(name) ;

 if(backend == 0) {
   ESP_LOGE(LOG_TAG,"Backend with name: %s not found", name);
   return ESS_ERROR_NOBACKEND;
 }
if(backend->open(format) != ESS_OK) {
  ESP_LOGE(LOG_TAG,"Backend with name: %s error open", name);
  return ESS_ERROR_WRONG_FORMAT;
}

 m_eFormat= format;
 m_eStatus = ESS_CONTEXT_STATUS_RUN;
 m_pBackend = backend;

 return ESS_OK;
}
ess_error_t  ess_context::create(ess_backend* backend, const ess_format_t format) {
  if(backend == 0) return ESS_ERROR_NOBACKEND;

  if(backend->open(format) != ESS_OK) {
    ESP_LOGE(LOG_TAG,"Backend with name: %s error open", backend->get_name());
    return ESS_ERROR_WRONG_FORMAT;
  }

   m_eFormat= format;
   m_eStatus = ESS_CONTEXT_STATUS_RUN;
   m_pBackend = backend;

   return ESS_OK;
}
ess_error_t ess_context::close() {

  if(m_pBackend == 0)  return last_error =  ESS_ERROR_NOBACKEND;

  m_pBackend->close();
  m_eStatus = ESS_CONTEXT_STATUS_CLOSE;

  last_error = ESS_OK;
  return ESS_OK;

}

ess_error_t ess_context::destroy() {

  close();
  return ESS_OK;
}

ess_error_t ess_context::paused() {

  if(m_pBackend == 0)  return last_error =  ESS_ERROR_NOBACKEND;

  m_eStatus = ESS_CONTEXT_STATUS_PAUSED;
  m_pBackend->pause();

  last_error = ESS_OK;
  return ESS_OK;
}
ess_error_t ess_context::resume() {

  if(m_pBackend == 0)  return last_error =  ESS_ERROR_NOBACKEND;

  m_eStatus = ESS_CONTEXT_STATUS_RUN;
  m_pBackend->resume();

  last_error = ESS_OK;
  return ESS_OK;
}

ess_error_t ess_context::set_format(const ess_format_t format) {

  if(m_pBackend == 0)  return last_error =  ESS_ERROR_NOBACKEND;

  return (m_pBackend->restart(format) != 0) ? ESS_ERROR_WRONG_FORMAT : ESS_ERROR_NULL;
}

unsigned int ess_context::write(void *buffer, unsigned int buf_size) {
  unsigned int wrote;
  write(buffer, buf_size, &wrote);
  return wrote;
}
ess_error_t ess_context::write(void *buffer, unsigned int buf_size,  unsigned int* wrote) {

  if(m_eStatus == ESS_CONTEXT_STATUS_PAUSED) return last_error = ESS_ERROR_PAUSED;
  if(m_pBackend == 0)  return last_error =  ESS_ERROR_NOBACKEND;

  m_pBackend->write(buffer, buf_size, wrote);

  return  ESS_OK;
}

const char* ess_context::get_backend_name() {
  if(m_pBackend == 0) return 0;
  return m_pBackend->get_name();
}
const char* ess_context::get_backend_info() {
  if(m_pBackend == 0) return 0;
  return m_pBackend->get_info();
}
ess_error_t ess_context::get_last_error() {

  return last_error;
}
