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
 * @brief Contains all ess backend  functions and the backend factory struct
 *
 *
 */

#ifndef __ESS_BACKEND_H__
#define __ESS_BACKEND_H__

#include "ess.h"
#include "ess_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ess backend factory
 *
 * Embedded Sound System Backend factory. Backend vtable
 */
typedef struct ess_backend {
  ess_error_t (* ess_backend_probe )(const ess_format_t format);/**< probe the backend - format supported? */
  ess_error_t (* ess_backend_open )(const ess_format_t format); /**< open the backend */
  ess_error_t (*  ess_backend_close)( void ); /**< close the backend */
  ess_error_t (*  ess_backend_pause)( void ); /**< paused the backend */
  ess_error_t (*  ess_backend_resum)( void ); /**< resumed the backend */
  ess_error_t  (*  ess_backend_write)( void *buffer, unsigned int buf_size, unsigned int* wrote ); /**< write data to the backend */
  ess_error_t  (*  ess_backend_read)( void *buffer, unsigned int buf_size, unsigned int* readed );/**< read data from the backend */
  ess_error_t (*   ess_backend_flush)( void ); /**< flush backend data  */
  ess_error_t (* ess_backend_set_sample_format)(ess_format_t format); /**<  set new sample format */

  const char* (* get_name) (void); /**< get the name for this backend */
  const char* (* get_info)(void);  /**< get infos for this backend */

  void* user_daten;
} ess_backend_facktory_t;



/**
 * @brief get ess_error_t entry
 * @param [in] number of the entry
 * @return the backend
 * @retval NULL no backends
 */
ess_backend_facktory_t* ess_backend_get_by_index(unsigned int index);

/**
 * @brief get ess_error_t entry
 * @param [in] name of the backend
 * @return the backend
 * @retval NULL no backends
 */
ess_backend_facktory_t* ess_backend_get_by_name(const char* name) ;

/**
 * @brief get the size of backends
 * @return the  number of platform backends in the list
 */
int ess_backend_get_size();

/**
 * @brief checked the backend with the specified name and returns it if successful.
 * @param [in] Name of the backend
 * @param [in] format the format to probe
 * @param [out] backend return the working backend. if not null
 *
 * @retval  ESS_OK if backend support
 * @retval ESS_ERROR_WRONG_FORMAT
 * @retval ESS_ERROR
 */
ess_error_t ess_backend_probe_ex(const char* name, const ess_format_t format, ess_backend_facktory_t* backend);

/**
 * @brief checked the backend
 * @param [in]  format the format to probe
 * @param [in]  backend return the working backend. if not null
 * @retval  ESS_OK if backend support
 * @retval ESS_ERROR_WRONG_FORMAT
 * @retval ESS_ERROR_NULL backend is null
 */
ess_error_t ess_backend_probe(const ess_format_t format, ess_backend_facktory_t* backend);
/**
 * @brief set sample format
 * @param [in] backend the usiing backend
 * @param [in] forma sample format
 * @retval  ESS_OK if backend support
 * @retval ESS_ERROR_WRONG_FORMAT
 * @retval ESS_ERROR
 */
ess_error_t ess_backend_set_sample_format(ess_backend_facktory_t* backend,  const ess_format_t forma);

/**
 * @brief get user daten from backend (internal user)
 * @param [in] the using backend
 * @return the user daten
 */
void* ess_backend_get_user_daten(ess_backend_facktory_t* backend);
/**
 * @brief set user daten from backend (internal user)
 * @param[in] the usiing backend
 * @param [in] data the using data
 * @retval  ESS_OK
 * @retval ESS_ERROR_NULL backend null
 */
ess_error_t ess_backend_set_user_daten(ess_backend_facktory_t* backend, void* data);
#ifdef __cplusplus
}
#endif

#endif
