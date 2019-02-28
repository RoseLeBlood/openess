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
 * @file ess_daemon.h
 * @author Anna Sopdia Schröck
 * @date 28 Februar 2019
 * @brief OpenESS daemon
 *
 * the main running class - I/O for openess (singleton)
 */
 #ifndef _ESS_DAEMON_MAIN_H_
 #define _ESS_DAEMON_MAIN_H_


#include "ess.h"
#include "ess_server.h"
#include "ess_protocol.h"
#include "ess_csi_server.h"
#include "ess_server.h"
#include "ess_dram_server.h"

class ess_daemon {
private:
  static ess_daemon *m_pInstance;
public:
  static ess_daemon& instance() {
    if(m_pInstance == nullptr) m_pInstance = new ess_daemon();
    return *m_pInstance;
  }
public:
  ess_error_t setup(const std::string& backend_name);

  virtual float cmd_set_volume(float vol) { return false; } // OPENESS_PROTOCAL_CONTROLL_SET_VOLUME
  virtual bool cmd_restart() { return false; } //OPENESS_PROTOCAL_CONTROLL_RESTART
  virtual bool cmd_stop() {  return false; } //OPENESS_PROTOCAL_CONTROLL_STOP
  virtual bool cmd_pause() { return false;  } //OPENESS_PROTOCAL_CONTROLL_PAUSE
  virtual bool cmd_start() { return false;  } //OPENESS_PROTOCAL_CONTROLL_START
  virtual bool cmd_set_format(ess_format_t format) { return false;  }  //OPENESS_PROTOCAL_CONTROLL_SET_FORMAT
  virtual bool cmd_rm_client(int id) { return false; } // OPENESS_PROTOCAL_CONTROLL_REMOVE
  virtual int cmd_get_version() { return OPEN_ESS_VERSION; } // OPENESS_PROTOCAL_CONTROLL_GET_VERSION
  virtual std::string cmd_get_mixer_info() { return ""; } // OPENESS_PROTOCAL_CONTROLL_GET_MIXER

  // OPENESS_PROTOCAL_CONTROLL_GET_BACKEND
  virtual std::string cmd_get_backend_info() {
     return m_pServer->get_context().get_backend_name();
   }
    // OPENESS_PROTOCAL_CONTROLL_GET_PLATFORM
  virtual std::string cmd_get_platform_info() {
    return m_pServer->get_name();
  }
protected:
  ess_daemon() ;

private:
  ess_dram_server* m_pServer;
  ess_csi_server m_CsiServer;
  //ess_mixer m_Mixer;
};


 #endif
