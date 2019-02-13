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
 * @file null_backend.c
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all generic backend null functions source cource
 *
 */
#include "ess_format.h"
#include "config.h"
#include "ess_backend.h"
#include "stdio.h"

int g_null_paused = 0;

ess_error_t ess_backend_null_open(const ess_format_t format) {
  printf("Possible to open backend: null (%s)\n",
  ess_format_to_string(format));
  return ESS_OK;
}
ess_error_t  ess_backend_null_close( void ){
  printf("Possible to close backend: null\n");
  return ESS_OK;
}
ess_error_t  ess_backend_null_pause( void ){
  printf("Possible to pause backend: null\n");
  return ESS_OK;
}
ess_error_t     ess_backend_null_write( void *buffer, unsigned int buf_size,  unsigned int* wrote ){
  if(wrote) *wrote = -1;
  return ESS_OK;
}
ess_error_t     ess_backend_null_read( void *buffer, unsigned int buf_size, unsigned int* readed  ){
  if(readed) *readed = -1;
  return ESS_OK;
}
ess_error_t  ess_backend_null_flush( void ){
  return ESS_OK;
}
ess_error_t  ess_backend_null_resume( void ){
  printf("Possible to resume backend: null\n");
  return ESS_OK;
}
ess_error_t  ess_backend_null_set_sample_format(const ess_format_t format) {
  return ESS_OK;
}
const char* ess_backend_null_get_name(void) {
  return ESS_BACKEND_NAME_NULL;
}
const char* ess_backend_null_get_info(void) {
  return "Null Audio";
}
ess_backend_facktory_t _null_backend_config = {
  ess_backend_null_open,
  ess_backend_null_close,
  ess_backend_null_pause,
  ess_backend_null_resume,
  ess_backend_null_write,
  ess_backend_null_read,
  ess_backend_null_flush,
  ess_backend_null_set_sample_format,
  ess_backend_null_get_name,
  ess_backend_null_get_info,
  0
};
ess_backend_facktory_t* ess_backend_null_getFactory() {
  return &_null_backend_config;
}
