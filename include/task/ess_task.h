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
 * @file ess_task.h
 * @author Anna Sopdia Schröck
 * @date 3 Februar 2019
 * @brief  platform specific task class
 *
 */
#ifndef _ESS_TASK_H_
#define _ESS_TASK_H_

#include "ess.h"
#include "task/ess_mutex.h"

class ess_task : public ess_object  {
public:
  /**
   * @brief simple constructer
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_task()  : ess_task("ess_task", NULL, 4096){ }

  /**
   * @brief constructer for the task
   *
   * param [in] taskName the name of the task
   * param[in] param the user daten of this task
   * param [in] stackSize the n bytes for the task
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_task(const std::string taskName, void* param = NULL, unsigned int stackSize = 4096);
  virtual ~ess_task() { destroy(); }

  /**
   * @brief start the task
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_error_t start();

  /**
   * @brief start the task and pinned it to a core
   * @param [in] core pinned to core
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_error_t start(uint32_t core);
  /**
   * @brief delete the task
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_error_t destroy();


  /**
   * @brief suspend the task
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_error_t suspend();
  /**
   * @brief resume the task
   *
   * @retval ESS_OK
   * @reval ESS_ERROR_NOT_IMP  function is for using platform not implantiert
   * @retval ESS_ERROR
   */
  ess_error_t resume();

  /**
   * @brief the virtual task functions
   * @param[int] it self  of the task class
   * @param[in] userdata the task userdaten
   */
  virtual void onTask(ess_task* self, void* userdata) { }

  /**
   * @brief get the stack size
   * @return the stack size
   */
  virtual unsigned int get_stack_size() { return m_uiStackSize; }
  /**
   * @brief get the platform handle
   * @return the platform handle
   */
  virtual void* get_handle() { return m_pHandle; }
  /**
   * @brief get the task priority
   * @return the task priority
   */
  virtual int get_priority() { return m_iPriority; }

  /**
   * @brief is the task running ?
   * @return true when the task run
   */
  virtual bool is_running() { runningMutex.lock(); return m_bRunning; runningMutex.unlock();  }

  /**
   * @brief set the task priority
   * @param [in] value the new task priority
   */
  virtual void set_prority(int value) { runningMutex.lock(); m_iPriority =  value; runningMutex.unlock();  }
  /**
   * @brief set the stack size
   * @param [in] value the new stack size
   */
  virtual void set_stack_size(unsigned int value) { runningMutex.lock(); m_uiStackSize =  value; runningMutex.unlock();  }
protected:
  /**
   * @brief set the user data
   * @param [in] value the new user data
   */
  virtual void set_user_data(void* value) { m_pUserdata = value; }
private:
  static void int_task_stub(void* data);
protected:
  int m_iTaskId;

  void* m_pUserdata;
  void* parem;
  unsigned int m_uiStackSize;
  void* m_pHandle;
  int m_iPriority;
  bool m_bRunning;

  ess_mutex runningMutex;
  ess_mutex contextMutext;
  ess_mutex continuemutex;
  ess_mutex continuemutex2;
};

using ess_task_wrapper_func = void (*)(void* userdata);

/**
  * simple c wrapper for c++ ess_task class
**/
class ess_task_wrapper : public ess_task {
public:
  ess_task_wrapper(ess_task_wrapper_func func, std::string name )
    :  ess_task(name), m_pFunc(func) { }

  virtual void onTask(ess_task* self, void* userdata) { if(m_pFunc) m_pFunc(userdata); }
private:
  ess_task_wrapper_func m_pFunc;
};

#endif
