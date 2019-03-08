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
 * @date 18 Februar 2019
 * @brief basic class for `ess_input_channel` and ''ess_output_channel
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
 #ifndef __ESS_CHANNEL_H__
 #define __ESS_CHANNEL_H__

 #include "ess.h"



class ess_channel {
public:
  ess_object() : ess_object("ess_object", ESS_CHANNEL_INPUT) { }

  ess_object(std::string name, ess_channel_t type) :
    ess_object(name, type, ESS_AUDIO_CHANNEL_LEFT ) { }

  ess_object(std::string name, ess_channel_t type, ess_audio_channel channel)
    : m_strHumanChannelName(name) { }

  std::string& get_name() { return m_strHumanChannelName; }
  void set_name(const std::string& name) { m_strHumanChannelName = name; }

  ess_audio_channel get_channel() { return m_iChannel; }
  ess_channel_t get_type() { return m_eType; }

  bool is_input() { return m_eType == ESS_CHANNEL_INPUT; }
  bool is_output() { return m_eType == ESS_CHANNEL_OUTPUT; }
  bool is_invalid() { return m_eType >= ESS_CHANNEL_MAX; }
  
protected:
  void set_channel(const ess_audio_channel channel) { return m_iChannel = channel; }
  void set_type(const ess_channel_t type) { return m_eType = type; }
protected:
  std::string m_strHumanChannelName;
  ess_audio_channel m_iChannel;
  ess_channel_t m_eType;
};

/**
* @}
*/
#endif
