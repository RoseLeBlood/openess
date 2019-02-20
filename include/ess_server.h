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
 * @date 19 Februar 2019
 * @brief the OpenESS generic server class
 *
 *
 */
 /**
 * @addtogroup network
 * @{
 */
#ifndef _ESS_MAIN_HEADER_H_
#error "#include <ess.h> befor this include"
#endif

#ifndef _ESS_SERVER_H__
#define _ESS_SERVER_H__

#include "ess_context.h"
#include "ess_inet_dram_server.h"


typedef enum ess_server_status {
  ESS_SERVER_STATUS_INIT,
  ESS_SERVER_STATUS_STOP,
  ESS_SERVER_STATUS_RUN,
  ESS_SERVER_STATUS_STANDBY,
  ESS_SERVER_STATUS_ERROR
}ess_server_status_t;

/*typedef struct ess_server {
  void* buffer;
  int magl, magr;
  int  speed,  length, offset ;
} ess_server_t;*/


class ess_server {
public:
  ess_server(std::string name, ess_format_t format);

  virtual ess_error_t create(std::string backend_name) = 0;

  ess_context& get_context() const{ return *m_pContext; }
  ess_format_t get_server_format() const { return m_eFormat; }

  std::string get_name() const { return m_strName; }
  ess_server_status_t get_status() const { return m_eStatus; }
protected:
  ess_context *m_pContext;
  ess_format_t m_eFormat;

  std::string m_strName;
  ess_server_status_t m_eStatus;
};


/**
* @}
*/
#endif
