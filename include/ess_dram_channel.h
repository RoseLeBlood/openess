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
 * @file ess_channel.h
 * @author Anna Sopdia Schröck
 * @date 04 März 2019
 * @brief dram input network audio-stream
 *
 *
 */
 /**
 * @addtogroup channel
 * @{
 */
 #ifndef __ESS_DRAM_CHANNEL_H__
 #define __ESS_DRAM_CHANNEL_H__


#include "ess_channel.h"
#include "ess_inet_dram_server.h"
#include "ess_ringbuffer.h"

class ess_dram_channel : public ess_channel {
public:
  /**
   * @brief simple constructer for this dram channel without automatic soocket init
   * @param name the name of the channel
   * @param outputs number of outputs of this channel
   */
  ess_dram_channel(const std::string& name, uint8_t outputs)
    : ess_channel(name, outputs) { }
  /**
   * @brief simple constructer for this dram channel without automatic soocket init
   * @param name the name of the channel
   * @param outputs number of outputs of this channel
   */
  ess_dram_channel(const std::string& name, uint8_t outputs ,const int port)
#if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
    : ess_dram_channel(name, outputs, ESS_DEFAULT_SERVER_HOST, port, ESS_SOCKET_FAMILY_IP4) { }
#else
    : ess_dram_channel(name, outputs, ESS_DEFAULT_SERVER_HOST, port, ESS_SOCKET_FAMILY_IP6) { }
#endif
  ess_dram_channel(const std::string& name, uint8_t outputs, const std::string& host,const int port, ess_socket_fam fam)
    : ess_channel(name, outputs) { setup(host, port, fam); }

  virtual ess_error_t setup(const std::string& host,const int port, ess_socket_fam fam);

  virtual ess_error_t init() ; // ess_channel
  virtual ess_error_t destroy() ; // ess_channel
  virtual ess_error_t update(void); // ess_audio_stream

  virtual void onTask(ess_task* self, void* userdata); // ess_task - fill the ringbuffer

  ess_inet_dram_server* get_socket() { return m_pSocketServer; }
private:
  ess_inet_dram_server* m_pSocketServer;
  ess_ringbuffer m_RingBuffer;

  bool volatile m_bTaskBufferRun;
};

/**
* @}
*/


#endif
