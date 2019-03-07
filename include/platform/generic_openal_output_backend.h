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
#include "ess_output_stream.h"

class generic_openal_output_backend : public ess_output_stream<ESS_CHANNEL_FORMAT_MON0> {
public:
  generic_openal_output_backend() : ess_output_stream(ESS_BACKEND_NAME_OUT_OPENAL) { }
  ~generic_openal_output_backend() { }

  virtual ess_error_t probe(ess_format_t format) { return ESS_OK; }
  virtual ess_error_t open() { return ess_output_stream::open(); }
  virtual ess_error_t close() { return ess_output_stream::close(); }


  virtual ess_error_t update(void) {
    return ESS_OK;
  }
};

/**
* @}
*/
#endif
