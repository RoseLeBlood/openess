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
#include "ess_format.h"

#include <map>


class ess_backend {
public:
  ess_backend() { }
  ess_backend(const char* name) { m_strName = name; }
  virtual ~ess_backend() { }

  virtual ess_error_t open(const ess_format_t format) = 0;
  virtual ess_error_t close() = 0;
  virtual ess_error_t restart(const ess_format_t format) = 0;

  virtual ess_error_t pause() = 0;
  virtual ess_error_t resume() = 0;

  virtual ess_error_t write(const void *buffer, unsigned int buf_size, unsigned int* wrote) = 0;
  virtual ess_error_t read(void *buffer, unsigned int buf_size, unsigned int* readed) = 0;

  virtual const char* get_name() { return m_strName; }
  virtual const char* get_info() = 0;
protected:
  void* m_pUserData;
  const char* m_strName;
};

/**
 * @brief ess backend interface
 *
 * Embedded Sound System Backend factory. Backend vtable
 */
class ess_backend_factory {
public:
  bool add_backend(const char* name, ess_backend* backend);

  ess_backend& get_backend(const char* name);
private:
  std::map<const char*, ess_backend*> m_lBackends;
};


#endif
