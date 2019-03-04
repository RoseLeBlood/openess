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
 * @file ess_dram_channel.cpp
 * @author Anna Sopdia Schröck
 * @date 04 März 2019
 */
#include "ess_dram_channel.h"
#include "ess_sleep.h"

ess_error_t ess_dram_channel::setup(const std::string& host,const int port, ess_socket_fam fam) {
  if(fam == ESS_SOCKET_FAMILY_IP4)
    m_pSocketServer = new ess_inet_dramlite_server_ip4(host, port);
  else if(fam == ESS_SOCKET_FAMILY_IP6 || fam == ESS_SOCKET_FAMILY_BOTH)
    m_pSocketServer = new ess_inet_dramlite_server_ip6(host, port);

  if(!m_pSocketServer ) return ESS_ERROR_OUTOFMEM;

  m_RingBuffer.create(m_sampleBufferSize, ESS_PLATFORM_RINGBUFFER_MODE_NOSPLIT);
  m_pSampleData = (float*)malloc(m_sampleBufferSize * sizeof(float) );

  ess_task::set_user_data(this);

  if( m_pSocketServer->bind() == ESS_OK)
    return ess_task::start();
  else
    return ESS_ERROR;
}
ess_error_t ess_dram_channel::init()  {
  if(!m_bConfigured) {

    m_bConfigured = true;
    m_bActive = true;
  }
   return ESS_OK;
}
ess_error_t ess_dram_channel::destroy() {
  if(m_bConfigured) {


    m_bTaskBufferRun = false;

    while(ess_task::is_running() ) { }
    m_bConfigured = false;
    m_bActive = false;

    m_RingBuffer.destroy();
  }
   return ESS_OK;
}
void ess_dram_channel::onTask(ess_task*, void* userdata) {
  ess_dram_channel *task_self = static_cast<ess_dram_channel*>(userdata);
  if(task_self == 0) return;

  void* buffer = malloc(m_sampleBufferSize * sizeof(float) );

  int readed = 0;

  while(task_self->m_bTaskBufferRun) {
    readed =  m_pSocketServer->recvfrom(buffer, ESS_DEFAULT_AUDIO_PACKET_SIZE * m_iOutputs);
    m_RingBuffer.write(buffer, readed, 100);

    ess_platform_sleep(1);
  }
}
ess_error_t ess_dram_channel::update(void) {
  ess_audio_block_t *new_left=NULL, *new_right=NULL;
  int i;

    new_left = allocate();
    if (new_left != NULL) {
        new_right = allocate();
        if (new_right == NULL) {
            release(new_left);
            new_left = NULL;
        }
    }
    m_pSampleData = (float*)m_RingBuffer.read(&m_sampleBufferSize, 100);

    if(m_bConfigured && m_bActive) {
      if(m_iOutputs == 1) {
        for(i = 0; i < m_sampleBufferSize; i++)  {
            new_left->data[i] = new_right->data[i] = m_pSampleData[i];
        }
      } else if(m_iOutputs == 2) {
        for(i = 0; i < m_sampleBufferSize; i += 2)  {
            new_left->data[i] = m_pSampleData[i]; i++;
            new_right->data[i] = m_pSampleData[ i ];
        }
      }
      for(i = m_sampleBufferSize; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
        new_left->data[i] = new_right->data[i] = 0;
      }
  }
  transmit(new_left, 0); release(new_left);
  transmit(new_right, 1); release(new_right);

  return ESS_OK;
}
