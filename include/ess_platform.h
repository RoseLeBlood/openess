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
 * @file ess_platform.h
 * @author Anna Sopdia Schröck
 * @date 3 Februar 20119
 * @brief all platform specific functions
 *
 */
#ifndef _ESS_PLATFORM_H_
#define _ESS_PLATFORM_H_

#include "ess_error.h"

#ifdef __cplusplus
extern "C" {
#endif




typedef enum  ess_platform_ringbuffer_mode{
  ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT,
  ESS_PLATFORM_RINGBUFFER_MODE_ALLOWSPLIT,
  ESS_PLATFORM_RINGBUFFER_MODE_BYTEBUF,
}ess_platform_ringbuffer_mode_t;

typedef struct ess_platform_task {
  char name[16];
  int task_id;
  void  (*task)(void* );
  void* userdata;
  void* parem;
  unsigned int stack_size;
  void* handle;
  int priority;
}ess_platform_task_t;

typedef struct ess_platform_semaphore {
  char name[16];
  void* handle;
  int value;
}ess_platform_semaphore_t;

typedef struct ess_platform_ringbuffer {
  char name[16];
  void* handle, *qhandle;
  ess_platform_ringbuffer_mode_t type;
}ess_platform_ringbuffer_t;


/**
 * @brief get the time in milliseconds since the %FreeRTOS scheduler started.
 * @retval >0  the time in milliseconds since the %FreeRTOS scheduler started.
 *@reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR
 */
unsigned int ess_platform_get_tick_count();
/**
 * @brief Sleep for the specified number of milliseconds.
 * @param [in] ms The period in milliseconds for which to sleep.
 * @retval ESS_PLATFORM_ERROR_OK
 *@reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 */
ess_error_t ess_platform_sleep(unsigned int ms);
/**
 * @brief fill the 'esp_platform_task_t' struct
 * @param[out] task The  pointer to the 'esp_platform_task_t' struct
 * @param [in] task_func The function pointer to the function to be run in the task.
 * @param [in] taskName A string identifier for the task.
 * @param [in] param An optional parameter to be passed to the started task.
 * @param [in] stackSize An optional paremeter supplying the size of the stack in which to run the task.
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR unspec error
 * @retval ESS_PLATFORM_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_create(ess_platform_task_t* task, void task_func(void*),
    const char* taskName, void* param, unsigned int stackSize);
/**
 * @brief start the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_PLATFORM_ERROR_OK
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR
 * @retval ESS_PLATFORM_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_start(ess_platform_task_t* task);
/**
 * @brief delete the task
 * @param[int] task The  pointer to the 'esp_platform_task_t' struct
 *
 * @retval ESS_PLATFORM_ERROR_OK
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR
 * @retval ESS_PLATFORM_ERROR_NULL 'esp_platform_task_t' task is null
 */
ess_error_t ess_platform_task_delete(ess_platform_task_t* task);
/**
 * @brief create the semaphore
 * @param [in] semp the semaphore context
 * @param [in] name of the semaphore
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR unspec error
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_create(ess_platform_semaphore_t* semp, const char* name);
/**
 * @brief destroy the semaphore
 * @param [in] semp the semaphore context
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR unspec error
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_destroy(ess_platform_semaphore_t* semp);
 /**
  * @brief take a semaphore
  * @param [in] semp the semaphore context
  * @param [in] timeout_ms timeout in milliseconds.
  *
  * @retval ESS_PLATFORM_ERROR_OK no error
  * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
  * @retval ESS_PLATFORM_ERROR fail to take the semaphore
  * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
  * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
  */
ess_error_t ess_platform_semaphore_take_ex(ess_platform_semaphore_t* semp, unsigned int timeout_ms);
/**
 * @brief take a semaphore
 * @param [in] semp the semaphore context
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to take the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_take(ess_platform_semaphore_t* semp);
/**
 * @brief take a semaphore
 * @param [in] semp the semaphore context
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to give the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
 ess_error_t ess_platform_semaphore_give(ess_platform_semaphore_t* semp);
/**
 * @brief give a semaphore
 * @param [in] semp the semaphore context
 * @param [in] value the value to associate with the semaphore.
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to give the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_give_ex(ess_platform_semaphore_t* semp, int value);
/**
 * @brief give a semaphore
 * @param [in] semp the semaphore context
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to give the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_give(ess_platform_semaphore_t* semp);

/**
 * @brief give a semaphore from ISR
 * @param [in] semp the semaphore context
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP   function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to give the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_give_isr(ess_platform_semaphore_t* semp);

/**
 * @brief wait for a semaphore to be released by trying to take it and then releasing it again.
 * @param [in] semp the semaphore context
 * @param[out] value the value associated with the semaphore.
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP   function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR fail to give or take the semaphore
 * @retval ESS_PLATFORM_NOT_CREATED  semaphore is not created
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_semaphore_t' semp is null
 */
ess_error_t ess_platform_semaphore_wait(ess_platform_semaphore_t* semp, int* value);
/**
 * @brief Create a ring buffer.
 *
 * @param [in] rng the ringbuffer context
 * @param [in] length The amount of storage to allocate for the ring buffer.
 * @param [in] type the mode of the ring buffer.
 * @param [in] name the name of the ring buffer.
 *
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR unspec error
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
ess_error_t ess_platform_ringbuffer_create(ess_platform_ringbuffer_t* rng ,
  unsigned int length,  ess_platform_ringbuffer_mode_t type, const char* name);
  /**
   * @brief destroy the ring buffer.
   *
   * @param [in] rng the ringbuffer context
   *
   * @retval ESS_PLATFORM_ERROR_OK no error
   * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_PLATFORM_ERROR unspec error
   * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
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
 * @retval ESS_PLATFORM_ERROR_OK no error
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR can't write
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
ess_error_t ess_platform_ringbuffer_write(ess_platform_ringbuffer_t* rng,
    void* data, unsigned int length, unsigned int ms);
/**
 * @brief can read from the ringbuffer
 *
 * @param [in] rng the ringbuffer context
 * @param [in] ms how long to wait before giving up - in ms
 *
 * @retval ESS_PLATFORM_ERROR_OK yes
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR no
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
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
 * @reval ESS_PLATFORM_NOT_IMP  function is for using platform not implantiert
 * @retval ESS_PLATFORM_ERROR_NULL 'ess_platform_ringbuffer_t' rng is null
 */
void* ess_platform_ringbuffer_read(ess_platform_ringbuffer_t* rng, unsigned int* length, unsigned int ms);


#ifdef __cplusplus
}
#endif

#endif
