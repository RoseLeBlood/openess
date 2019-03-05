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
 * @file ess_error.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ess error list (ess_error_t)
 *
 */


#ifndef _ESS_ERROR_H_
#define _ESS_ERROR_H_


/**
 * @brief OpenESS error codes
 */
typedef enum ess_error {
    ESS_OK = 0, 				/**< mo error. */
    ESS_ERROR_OUTOFMEM = 3,			/**< no more memory */
    ESS_ERROR_NOT_FOUND = 4,			/**< hardware for backend not avaible */
    ESS_ERROR_WRONG_FORMAT = 5,		/**< The format is not supported */
    ESS_ERROR_PAUSED,				/**< Don't read or write becourse backend is paused */
    ESS_ERROR_NULL, /**< backend is null */
    ESS_ERROR,				/**< unknown error */
    ESS_ERROR_NOT_IMP,    /** function no implantiert */
    ESS_ERROR_NOT_CREATED, /** <not created */
    ESS_ERROR_UNSPEC_PROTOKOL,      /**< unknown protokol */
    ESS_ERROR_WRONG_PROTOKOL,  /**< wrong protokol */
    ESS_ERROR_UNSPEC_FAMILY,              /**< unknown family */
    ESS_ERROR_GETADDR,                            /**<  getaddrinfo error see  ess_socket_t::retval */
    ESS_ERROR_BIND,                                     /**<  bind error see  ess_socket_t::retval  */
    ESS_ERROR_CONNECT,                            /** <  connect error */
    ESS_ERROR_CLOSE,                                     /**<  close error see  ess_socket_t::retval  */

    ESS_ERROR_NOBACKEND, /**< context has no backend */
    ESS_ERROR_ISPAUSED,  /**< can write while context is paused  */

    ESS_ERROR_TASK_CREAT, /**< can't create task mutex */
    ESS_ERROR_TASK_RUNNING, /**< task already running */
    ESS_ERROR_ALREADY_CREATED, /**< task or socet are already created*/

    
    ESS_ERROR_MAX,
}ess_error_t;


#define ESS_ERROR(error)   if(error != ESS_OK) \
  printf("%s: %d %s\n", ess_error_to_string(error), __LINE__, __FILE__);

#define ESS_ERROR_RET(error, ret)  if(error != ESS_OK)  { \
  printf("%s: %d %s\n", ess_error_to_string(error), __LINE__, __FILE__); \
  return ret; }

const char* ess_error_to_string(const ess_error_t error);


#endif
