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

#include "ess_channel.h"
#include <sstream>

ess_channel::ess_channel() : ess_channel("ess_object", ESS_CHANNEL_INPUT) { }

ess_channel::ess_channel(std::string name, ess_channel_t type)
  : ess_channel(name, type, ESS_AUDIO_CHANNEL_LEFT ) { }

ess_channel::ess_channel(std::string name, ess_channel_t type, ess_audio_channel channel)
  : ess_object(name), m_iChannel(channel),  m_eType(type) { }


std::string ess_channel::to_string() {
  std::ostringstream ss;

  if(is_input())   ss  << "input: ";
  else if(is_output())   ss  << "output: ";
  else   ss << "invalid: ";

  ss << get_name() << "(" <<  get_channel() << ")";

  return ss.str();
}
