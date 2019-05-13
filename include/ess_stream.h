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
 * @file ess_stream.h
 * @author Anna Sopdia Schröck
 * @date 19 Mai 2019
 *
 */
#ifndef _ESS_STREAM_H_
#define _ESS_STREAM_H_

#include "ess_object.h"

class ess_stream : public ess_object {
public:
  ess_stream() : ess_object("ess_stream") { }
  ess_stream(const std::string& name) : ess_object(name) { }


  virtual size_t read(void* data, const size_t offset, const size_t size)  = 0;
  virtual size_t write(const void* data, const size_t offset, const size_t size)  = 0;

  virtual unsigned char read() = 0;

  virtual bool can_read() = 0;
  virtual bool can_write() = 0;
  virtual bool can_seek() = 0;
};


#endif
