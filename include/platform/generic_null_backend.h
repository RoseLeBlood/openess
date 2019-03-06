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
 * @file generic_null_backend.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief the basic null backend class
 *
 * this is a null backend only for testing
 */
#ifndef _ESS_PLATFORM_INC_GENERIC_NULL_H_
#define _ESS_PLATFORM_INC_GENERIC_NULL_H_

/**
* @addtogroup ess_platform_generic
* @{
*/

#include "ess.h"
#include "ess_output_stream.h"

class generic_null_backend : public ess_output_stream {
public:
  generic_null_backend() : ess_output_stream(0, 0, ESS_BACKEND_NAME_OUT_NULL) { }
  ~generic_null_backend() { close(); }

  virtual ess_error_t probe(ess_format_t format) { return ESS_OK; }
  virtual ess_error_t open() { return ess_output_stream::open (); }
  virtual ess_error_t close() { return ess_output_stream::close (); }

  virtual const char* get_info() { return "generic_null_backend"; }

  virtual ess_error_t update(void) {
    return ESS_OK;
  }
protected:
  bool m_bPaused;
};

/**
* @}
*/
#endif
