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


#include "ess_input_module.h"

ess_error_t ess_input_module::add_channel(std::string name, ess_audio_channel channel) {
  if(get_channel(name) != NULL) return ESS_ERROR;
  if(get_channel(channel) != NULL) return ESS_ERROR;

  m_lstChannels.push_back(new ess_output_channel(name, channel));

  return ESS_OK;
}

ess_error_t ess_input_module::add_channel(ess_output_channel* channel) {
  if(channel == NULL) return ESS_ERROR_NULL;

  if(get_channel(channel->get_name()) != NULL) return ESS_ERROR;
  if(get_channel(channel->get_channel()) != NULL) return ESS_ERROR;

  m_lstChannels.push_back(channel);

  return ESS_OK;
}

ess_output_channel* ess_input_module::get_channel(ess_audio_channel channel) {
  std::list<ess_output_channel*>::iterator it;
  for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
    if((*it)->get_channel() == channel ) return *it;
  }
  return nullptr;
}

ess_output_channel* ess_input_module::get_channel(std::string name) {
  std::list<ess_output_channel*>::iterator it;
  for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
    if( (*it)->get_name() == name ) return *it;
  }
  return nullptr;
}
int32_t* ess_input_module::get_buffer(ess_audio_channel id) {
  ess_output_channel* channel = get_channel(id);
  if(channel) return channel->get_buffer();

  return nullptr;
}
uint32_t ess_input_module::get_size(ess_audio_channel id) {
  ess_output_channel* channel = get_channel(id);
  if(channel) return channel->get_size();

  return -1;
}
unsigned int ess_input_module::read(ess_audio_channel id, int32_t* buffer,
  unsigned int offset, unsigned int size ) {

    ess_output_channel* channel = get_channel(id);
    if(channel) return channel->read(buffer, offset, id);
    return -1;
}
