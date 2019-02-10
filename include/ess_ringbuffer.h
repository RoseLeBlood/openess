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
 * @file ess_ringbuffer.h
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all platform ringbuffer specific functions
 *
 */
 #ifndef _ESS_PLATFORM_RINGBUFFER_H_
 #define _ESS_PLATFORM_RINGBUFFER_H_

 #include "ess_error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  ess_platform_ringbuffer_mode{
  ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT,
  ESS_PLATFORM_RINGBUFFER_MODE_ALLOWSPLIT,
  ESS_PLATFORM_RINGBUFFER_MODE_BYTEBUF,
}ess_platform_ringbuffer_mode_t;


typedef struct ess_platform_ringbuffer {
  char name[16];
  void* handle, *qhandle;
  ess_platform_ringbuffer_mode_t type;
}ess_platform_ringbuffer_t;

/**
 * @brief Create a ring buffer.
 *
 * @param [in] rng the ringbuffer context
 * @param [in] length The amount of storage to allocate for the ring buffer.
 * @param [in] type the mode of the ring buffer.
 * @param [in] name the name of the ring buffer.
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR unspec error
 * @retval ESS_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
ess_error_t ess_platform_ringbuffer_create(ess_platform_ringbuffer_t* rng ,
  unsigned int length,  ess_platform_ringbuffer_mode_t type, const char* name);
  /**
   * @brief destroy the ring buffer.
   *
   * @param [in] rng the ringbuffer context
   *
   * @retval ESS_OK no error
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR unspec error
   * @retval ESS_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
   */
ess_error_t ess_platform_ringbuffer_destroy(ess_platform_ringbuffer_t* rng);
/**
 * @brief write data to the ring buffer.
 *
 * @param [in] rng the ringbuffer context
 * @param [in] data the data to place into the buffer.
 * @param [in] length the length of data to place into the buffer.
 * @param [in] ms how long to wait before giving up - in ms
 *
 * @retval ESS_OK no error
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR can't write
 * @retval ESS_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
ess_error_t ess_platform_ringbuffer_write(ess_platform_ringbuffer_t* rng,
    void* data, unsigned int length, unsigned int ms);
/**
 * @brief can read from the ringbuffer
 *
 * @param [in] rng the ringbuffer context
 * @param [in] ms how long to wait before giving up - in ms
 *
 * @retval ESS_OK yes
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR no
 * @retval ESS_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
ess_error_t ess_platform_ringbuffer_can_read(ess_platform_ringbuffer_t* rng, unsigned int ms);
/**
 * @brief read data from the ring buffer.
 *
 * @param [in] rng the ringbuffer context
 * @param [out] length the length of data to place into the buffer.
 * @param [in] ms how long to wait before giving up - in ms
 *
 * @retval a pointer to the storage retrieved.
 * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
void* ess_platform_ringbuffer_read(ess_platform_ringbuffer_t* rng, unsigned int* length, unsigned int ms);



#ifdef __cplusplus
}
#endif


#endif
