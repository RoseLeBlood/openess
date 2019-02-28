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
 * @file ess_daemon.cpp
 * @author Anna Sopdia Schröck
 * @date 28 Februar 2019
 * @brief OpenESS daemon
 *
 * the main running class - I/O for openess (singleton)
 */

#include "ess_daemon.h"


ess_daemon* ess_daemon::m_pInstance = 0;

ess_error_t ess_daemon::setup(const std::string& backend_name) {
  m_pServer = new ess_dram_server(ESS_DEFAULT_SERVER_NAME,
    ESS_DEFAULT_SERVER_FORMAT);

  printf("start backend and server at  .....");
  ess_error_t error = m_pServer->create(backend_name);
  ESS_ERROR(error) ;
  printf("OK\n");

  printf("start csi .....");
  error = m_CsiServer.setup(ESS_CONFIG_CSI_DEFAULT_PORT);
  ESS_ERROR(error) ;
  printf("OK\n");

  return ESS_OK;
}
