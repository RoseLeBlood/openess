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
 * @file ess_server.h
 * @author Anna Sopdia Schröck
 * @date 12 Mai 2019
 */
#ifndef _ESS_SERVER_H_
#define _ESS_SERVER_H_

#include "ess.h"
#include "ess_stream_writer.h"
#include "ess_ip_end_point.h"

class ess_server : public ess_object {
public:
  ess_server() : ess_object("ess_server") , m_bIsListing(false) { }
  ess_server(const std::string name) : ess_object(name), m_bIsListing(false)  { }

  virtual ess_error_t listen(int port, int optons = 128) = 0;
  virtual ess_error_t stop() = 0;

  virtual size_t read(void* data, const size_t size)  = 0;
  virtual size_t write(const void* datat, const size_t size)  = 0;

  virtual bool client_available() = 0;

  bool is_listing() const { return m_bIsListing ; }

  virtual ess_ip_end_point get_end_point() = 0;
protected:
  bool m_bIsListing;
  int m_iAccetpedHandle;
};

#endif
