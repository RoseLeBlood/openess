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


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ess_backend ess_backend_facktory_t;
/**
 * @brief Audio context stats
 */
typedef enum ess_context_status {
  ESS_CONTEXT_STATUS_CREATED, 	/**< context is created  */
  ESS_CONTEXT_STATUS_RUN, 	/**< context is running. */
  ESS_CONTEXT_STATUS_PAUSED,	/**< backend is paused */
  ESS_CONTEXT_STATUS_ERROR,	/**< error  */
  ESS_CONTEXT_STATUS_RESTART,	/**< context restart */
  ESS_CONTEXT_STATUS_CLOSE,	/**< audio backend in the context is closed */
} ess_context_status_t;

/**
 * @brief ess context error codes
 */
typedef enum ess_context_error {
  ESS_CONTEXT_ERROR_OK = 0,     /**< no error  */
  ESS_CONTEXT_ERROR_OUTOFMEM = -1, /**< out of memory */
  ESS_CONTEXT_ERRORNOBACKEND, /**< context has no backend */
  ESS_CONTEXT_WRONGFORMAT, /**< context format is not supported from backend  */
  ESS_CONTEXT_ERROR, /**< context unknown error  */
  ESS_CONTEX_ISPAUSED = -42,  /**< can write while context is paused  */
}ess_context_error_t;
/**
 * @brief ess context
 *
 * Embedded sound server context. Abstract managment
 */
typedef struct ess_context {
  ess_backend_facktory_t* backend; /**< using backend */
  ess_format_t format;		   /**< backend format */
  ess_context_status_t status;	   /**< context status */
  ess_context_error_t last_error; /**< the last error */
}ess_context_t;


/**
 * @brief  initialisiert the context
 * @code
 * ess_context_t *context;
 *
 * context = ess_context_init ("uart", ESS_FORMAT_STEREO_96000_24);
 *
 * @endcode
 *
 * @param [in] name the name of the using backend
 * @param [in] format the using context format
 * @retval NULL error with creating context
 * @return the new context
 */
ess_context_t* ess_context_create( const char* name, const ess_format_t format);
/**
 * @brief  initialisiert the context with a user backend
 * @code
 * ess_context_t *context;
 * ess_backend_facktory_t* user_backend = { ,,, };
 *
 * context = ess_context_create_ex( user_backend, ESS_FORMAT_STEREO_96000_24);
 * @endcode
 * @param [in] format the using context format
 * @param [in] backend the user backend factory
 *
 * @retval NULL error with creating context
 * @return the new context
 */
ess_context_t* ess_context_create_ex(ess_backend_facktory_t* backend, const ess_format_t format);
/**
 * @brief close the context and close the backend
 * @param context the context
  * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_close(ess_context_t* context);
/**
 * @brief destroy and free the context
 * @param context the context
 * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_destroy(ess_context_t* context);
/**
 * @brief set backend to standby
 * @param context the context
 * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_paused(ess_context_t* context);
/**
 * @brief set backend to run
 * @param context the context
 * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_resume(ess_context_t* context);
/**
 * @brief set the sample format to backend
 * @param context the context
 * @code
 * ess_context_t context;
 *
 * ess_context_create(&context, ESS_FORMAT_STEREO_92000_24); // Backend Format
 * ess_context_init_ex(&context, "uart"); // open uart backend
 *
 * ess_context_set_format(&context, LOADED_WAV_FORMAT);
 * @endcode
 * @param format the new using format
 * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_set_format(ess_context_t* context, const ess_format_t format);

/**
 * @brief write audio data to the backend
 * @param context the context
 * @param buffer the audio pcm data
 * @param buf_size the size of the buffer
 * @return the written data.
 */
unsigned int ess_context_write(ess_context_t* context, void *buffer, unsigned int buf_size);
/**
 * @brief write audio data to the backend
 * @param context the context
 * @param buffer the audio pcm data
 * @param buf_size the size of the buffer
 * @param wrote  the written data
 * @return when ok then ESS_CONTEXT_ERROR_OK
 */
ess_context_error_t ess_context_write_ex(ess_context_t* context, void *buffer, unsigned int buf_size,  unsigned int* wrote);
/**
 * @brief get the usind backend name
 * @param context the context
 * @return the using backend name
 */
const char* ess_context_get_backend_name(ess_context_t* context);
/**
 * @brief get using backend informations
 * @param context the context
 * @return the using backend informations
 */
const char* ess_context_get_backend_info(ess_context_t* context);

/**
 * @brief get the last error from context
 * @param context the context
 * @return the last error
 */
ess_context_error_t ess_context_get_last_error(ess_context_t* context);

#ifdef __cplusplus
}
#endif

#endif
