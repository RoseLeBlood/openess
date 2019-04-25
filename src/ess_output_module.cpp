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


#include "ess_output_module.h"
#include "ess_audioblock.h"

#include <sstream>

ess_error_t ess_output_module::add_channel(std::string name, ess_audio_channel channel) {
  if(get_channel(name) != NULL) return ESS_ERROR;
  if(get_channel(channel) != NULL) return ESS_ERROR;

  m_lstChannels.push_back(new ess_input_channel(name, channel));

  return ESS_OK;
}

ess_error_t ess_output_module::add_channel(ess_input_channel* channel) {
  if(channel == NULL) return ESS_ERROR_NULL;

  if(get_channel(channel->get_name()) != NULL) return ESS_ERROR;
  if(get_channel(channel->get_channel()) != NULL) return ESS_ERROR;

  m_lstChannels.push_back(channel);

  return ESS_OK;
}

ess_input_channel* ess_output_module::get_channel(ess_audio_channel channel) {
  std::list<ess_input_channel*>::iterator it;
  for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
    if((*it)->get_channel() == channel ) return *it;
  }
  return nullptr;
}

ess_input_channel* ess_output_module::get_channel(std::string name) {
  std::list<ess_input_channel*>::iterator it;
  for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
    if( (*it)->get_name() == name ) return *it;
  }
  return nullptr;
}

unsigned int ESS_IRAM_ATTR ess_output_module::read(ess_audio_channel id, ess_audioblock_t*  block,
   unsigned int offset ) {

    int readed = -1;
    ess_input_channel* channel = get_channel(id);
    if(channel) {
      ess_audioblock_take(block);
      readed = channel->read(block, offset);
      ess_audioblock_relese(block);
    }

    return readed;
}
ess_error_t ess_output_module::connect( ess_input_module* input, ess_audio_channel channel) {
 return get_channel(channel)->connect(input->get_channel(channel));
}
ess_error_t ess_output_module::connect( ess_input_module* input, ess_audio_channel this_channel,
  ess_audio_channel mod_channel) {
  return get_channel(this_channel)->connect(input->get_channel(mod_channel));
}
std::string ess_output_module::to_string() {
  std::ostringstream ss;

  ss << get_name() << " inputs: " << std::endl;
  ss << "-------------------------" << std::endl;
  std::list<ess_input_channel*>::iterator it;
  for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
     ss << "\t" << (*it)->to_string() << std::endl;
  }
  ss << "-------------------------";

  return ss.str();
}
