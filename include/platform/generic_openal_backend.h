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
 * @file generic_openal_backend.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief the basic openal backend class
 *
 * this is opanel backend
 */
#ifndef _ESS_PLATFORM_INC_GENERIC_OPENAL_H_
#define _ESS_PLATFORM_INC_GENERIC_OPENAL_H_

/**
* @addtogroup ess_platform_generic
* @{
*/

#include "ess.h"
#include "ess_backend.h"

class generic_openal_backend : public ess_backend {
public:
  generic_openal_backend() : ess_backend(ESS_BACKEND_NAME_OPENAL) { }
  ~generic_openal_backend() { }

  virtual ess_error_t probe(const ess_format_t format) { return ESS_OK; }
  virtual ess_error_t open(const ess_format_t format) { return ess_backend::open(format); }
  virtual ess_error_t close() { return ess_backend::close(); }
  virtual ess_error_t restart(const ess_format_t format) { return ESS_OK; }

  virtual ess_error_t pause() { m_bPaused = true; return ESS_OK; }
  virtual ess_error_t resume() { m_bPaused = false; return ESS_OK; }

  virtual ess_error_t write(const void *buffer, unsigned int buf_size, unsigned int* wrote) { return ESS_OK; }
  virtual ess_error_t read(void *buffer, unsigned int buf_size, unsigned int* readed) { return ESS_OK; }

  virtual const char* get_info() { return "generic_null_backend"; }
protected:
  bool m_bPaused;
};

/**
* @}
*/
#endif
