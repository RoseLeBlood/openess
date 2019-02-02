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
 * @file backend.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief ESS bnackend managment
 *
 */

#ifndef __ESS_BACKEND_H__
#define __ESS_BACKEND_H__

#include "ess.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Audio backends error
 *
 * Error codes for the backend
 */
typedef enum ess_backend_error {
  ESS_BACKEND_OK = 0, 				/**< mo error. */
  ESS_BACKEND_OUTOFMEM = -1,			/**< no more memory */
  ESS_BACKEND_NOT_FOUND,			/**< hardware for backend not avaible */
  ESS_BACKEND_ERROR_WRONG_FORMAT,		/**< The format is not supported */
  ESS_BACKEND_PAUSED,				/**< Don't read or write becourse backend is paused */
  ESS_BACKEND_ERROR,				/**< unknown error */
} ess_backend_error_t;

/**
 * @brief ess backend factory
 *
 * Embedded Sound System Backend factory. Backend vtable
 */
typedef struct ess_backend {
  ess_backend_error_t (* ess_backend_probe )(ess_format_t format);/**< probe the backend - format supported? */
  ess_backend_error_t (* ess_backend_open )(ess_format_t format); /**< open the backend */
  ess_backend_error_t (*  ess_backend_close)( void ); /**< close the backend */
  ess_backend_error_t (*  ess_backend_pause)( void ); /**< paused the backend */
  ess_backend_error_t (*  ess_backend_resum)( void ); /**< resumed the backend */
  ess_backend_error_t  (*  ess_backend_write)( void *buffer, int buf_size, unsigned int* wrote ); /**< write data to the backend */
  ess_backend_error_t  (*  ess_backend_read)( void *buffer, int buf_size, unsigned int* readed );/**< read data from the backend */
  ess_backend_error_t (*   ess_backend_flush)( void ); /**< flush backend data  */

  const char* (* get_name) (void); /**< get the name for this backend */
  const char* (* get_info)(void);  /**< get infos for this backend */
} ess_backend_facktory_t;


/**
 * @brief get the size of using backends
 * @return number of support backends 
 */
int ess_backend_get_size();
/**
 * @brief Check that all backends support the specified format and return all working backends.
 * @param format the format to probe
 * @param backend return all working backends. if not null
 * @return number of working backends or ESS_BACKEND_ERROR_WRONG_FORMAT when no  backend  supported
 */
ess_backend_error_t ess_backend_probe_all(ess_format_t format, ess_backend_facktory_t** backend);
/**
 * @brief Checked the backend with the specified name and returns it if successful.
 * @param1 Name of the backend
 * @param format the format to probe
 * @param backend return the working backend. if not null
 * @return if backend support : ESS_BACKEND_OK else ESS_BACKEND_ERROR_WRONG_FORMAT or ESS_BACKEND_ERROR
 */
ess_backend_error_t ess_backend_probe(const char* name, ess_format_t format, ess_backend_facktory_t* backend);

#ifdef __cplusplus
}
#endif

#endif
