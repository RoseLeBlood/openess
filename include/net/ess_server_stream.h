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
 * @file ess_server_stream.h
 * @author Anna Sopdia Schröck
 * @date 13 Mai 2019
 *
 */
#ifndef _ESS_SERVER_STREAM_H_
#define _ESS_SERVER_STREAM_H_

#include "ess_stream.h"
#include "ess_server.h"
#include "ess_stream_writer.h"

class ess_server_stream : public ess_stream {
public:
  ess_server_stream(ess_server& server)
    : ess_stream("ess_server_stream"), m_sServer(server) { }
  ess_server_stream(ess_server& server, const std::string& name)
    : ess_stream(name), m_sServer(server)  { }

  virtual size_t read(void* data, const size_t offset, const size_t size) ;
  virtual size_t write(const void* data, const size_t offset, const size_t size) ;

  virtual unsigned char  read() ;

  virtual bool can_read() { return m_sServer.is_listing(); }
  virtual bool can_write() { return m_sServer.is_listing(); }
  virtual bool can_seek() { return false; }
protected:
  ess_server& m_sServer;
};

class ess_server_stream_writer : public ess_stream_writer {
public:
  ess_server_stream_writer(ess_server_stream& stream)
    : ess_stream_writer(stream , "ess_server_stream_writer") { }
  ess_server_stream_writer(ess_server_stream& stream, std::string name)
    : ess_stream_writer(stream , name) { }
};

#endif
