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
 * @file ess_mixer.h
 * @author Anna Sopdia Schröck
 * @date 28 Februar 2019
 * @brief OpenESS simple mixer
 *
 * the generic mixer
 */
 #ifndef _ESS_GENERIC_MIXER_H_
 #define _ESS_GENERIC_MIXER_H_

#include "ess_ringbuffer.h"

class ess_mixer_source : public ess_inet_dramlite_server_ip4 {
public:
  ess_mixer_source(const std::string& host,const int port)
    : ess_inet_dramlite_server_ip4(host, port) {  m_pRingBuffer.create(ESS_DEFAULT_SERVER_PACKET_SIZE); }

 // TODO:Add event - auto update

  int update() {
    static char buffer[ESS_DEFAULT_SERVER_PACKET_SIZE];

    m_iReaded = recvfrom(buffer, ESS_DEFAULT_SERVER_PACKET_SIZE);
    m_pRingBuffer.write(buffer, m_iReaded)
    return m_iReaded;
  }
private:
  ess_ringbuffer m_pRingBuffer;

  int m_iReaded;
}

class ess_mixer {
public:
  ess_mixer() : m_iMinVolume(0), m_iMaxVolume(100), m_iVolume(50) { }

  virtual int get_min_volume() { return m_iMinVolume; }
  virtual int get_max_volume() { return m_iMaxVolume; }
  virtual int get_volume() {return m_iVolume; }

  virtual int get_channels() { return ESS_DEFAULT_MIXER_MAX_INPUTS; }

  virtual int read(void* buffer, int offset, unsigned int size) {
    for(int i=0; i < ESS_DEFAULT_MIXER_MAX_INPUTS; i++) {

    }
  }
protected:
  ess_mixer_source* m_pServer[ESS_DEFAULT_MIXER_MAX_INPUTS];
  char m_pBuffer[];
  int m_iMinVolume, m_iMaxVolume, m_iVolume;

};

 #endif
