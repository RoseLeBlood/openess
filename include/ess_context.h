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
 * @file context.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief Contains all ess context  functions
 *
 *
 */

#ifndef __ESS_CONTEXT_H__
#define __ESS_CONTEXT_H__

#include "ess.h"
#include "ess_format.h"
#include "ess_error.h"


class ess_backend;

/**
 * @brief Audio context stats
 */
enum  ess_context_status_t {
  ESS_CONTEXT_STATUS_CREATED, 	/**< context is created  */
  ESS_CONTEXT_STATUS_RUN, 	/**< context is running. */
  ESS_CONTEXT_STATUS_PAUSED,	/**< backend is paused */
  ESS_CONTEXT_STATUS_ERROR,	/**< error  */
  ESS_CONTEXT_STATUS_RESTART,	/**< context restart */
  ESS_CONTEXT_STATUS_CLOSE,	/**< audio backend in the context is closed */
} ;

/**
 * @brief ess context
 *
 * Embedded sound server context. Abstract managment
 */
class ess_context {
public:
  ess_error_t  create(const char* name, const ess_format_t format);
  ess_error_t  create(ess_backend* backend, const ess_format_t format);

  /**
   * @brief close the context and close the backend
   * @param context the context
    * @return when ok then ESS_OK
   */
  ess_error_t close();

  /**
   * @brief destroy and free the context
   * @param context the context
   * @return when ok then ESS_OK
   */
  ess_error_t destroy();

  /**
   * @brief set backend to standby
   * @param context the context
   * @return when ok then ESS_OK
   */
  ess_error_t paused();

  /**
   * @brief set backend to run
   * @param context the context
   * @return when ok then ESS_OK
   */
  ess_error_t resume();
  /**
   * @brief set the sample format to backend
   * @param format the new using format
   * @return when ok then ESS_OK
   */
  ess_error_t set_format(const ess_format_t format);

  /**
   * @brief write audio data to the backend
   * @param buffer the audio pcm data
   * @param buf_size the size of the buffer
   * @return the written data.
   */
  unsigned int write(void *buffer, unsigned int buf_size);
  /**
   * @brief write audio data to the backend
   * @param buffer the audio pcm data
   * @param buf_size the size of the buffer
   * @param wrote  the written data
   * @return when ok then ESS_OK
   */
  ess_error_t write(void *buffer, unsigned int buf_size,  unsigned int* wrote);
  /**
   * @brief get the usind backend name
   * @return the using backend name
   */
  const char* get_backend_name();
  /**
   * @brief get using backend informations
   * @return the using backend informations
   */
  const char* get_backend_info();

  /**
   * @brief get the last error from context
   * @return the last error
   */
  ess_error_t get_last_error();
protected:
  ess_backend* m_pBackend;
  ess_format_t m_eFormat;
  ess_context_status_t m_eStatus;
  ess_error_t last_error;
};

/**
 * @brief  initialisiert the context
 *
 * @param [out] the creating ontext
 * @param [in] name the name of the using backend
 * @param [in] format the using context format
 *
 * @reval ESS_ERROR_WRONG_FORMAT format not support
 * @retval ESS_OK context created
 */

/**
 * @brief  initialisiert the context with a user backend
  * @param [out] the creating ontext
 * @param [in] format the using context format
 * @param [in] backend the user backend factory
 *
 * @reval ESS_ERROR_WRONG_FORMAT format not support
 * @retval ESS_OK context created
 * @reval ESS_ERROR_NOBACKEND backend was NULL
 */







#endif
