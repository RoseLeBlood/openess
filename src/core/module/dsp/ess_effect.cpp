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
 * @file ess_effect.cpp
 * @author Anna Sopdia Schröck
 * @date 11 März 2019
 * @brief ESS effect module
 *
 *
 */

#include "core/module/dsp/ess_effect.h"

ess_effect::ess_effect() : ess_input_module("ess_effect") { }
ess_effect::ess_effect(const std::string& name) : ess_input_module(name)  { }

ess_error_t ess_effect::add_input_channel(std::string name, ess_audio_channel channel) {
  if(get_channel(name) != NULL) return ESS_ERROR;
  if(get_channel(channel) != NULL) return ESS_ERROR;

  m_lstInChannels.push_back(new ess_input_channel(name, channel));

  return ESS_OK;
}



ess_error_t ess_effect::add_input_channel(ess_input_channel* channel) {
  if(channel == NULL) return ESS_ERROR_NULL;

  if(get_channel(channel->get_name()) != NULL) return ESS_ERROR;
  if(get_channel(channel->get_channel()) != NULL) return ESS_ERROR;

  m_lstInChannels.push_back(channel);

  return ESS_OK;
}

ess_error_t ess_effect::add_output_channel(std::string name, ess_audio_channel channel) {
  ess_input_module::add_channel(name, channel);
  return ESS_OK;
}
ess_error_t ess_effect::add_output_channel(ess_output_channel* channel) {
  ess_input_module::add_channel(channel);
  return ESS_OK;
}

ess_input_channel* ess_effect::get_input_channel(ess_audio_channel channel) {
  std::list<ess_input_channel*>::iterator it;
  for(it = m_lstInChannels.begin(); it != m_lstInChannels.end(); it++) {
    if((*it)->get_channel() == channel ) return *it;
  }
  return nullptr;
}
ess_input_channel* ess_effect::get_input_channel(std::string name) {
  std::list<ess_input_channel*>::iterator it;
  for(it = m_lstInChannels.begin(); it != m_lstInChannels.end(); it++) {
    if( (*it)->get_name() == name ) return *it;
  }
  return nullptr;
}
ess_output_channel* ess_effect::get_output_channel(ess_audio_channel channel) {
  return ess_input_module::get_channel(channel);
}
ess_output_channel* ess_effect::get_output_channel(std::string name) {
  return ess_input_module::get_channel(name);
}

ess_error_t ess_effect::connect(ess_input_module* mod, ess_audio_channel channel) {
  return get_input_channel(channel)->connect(mod->get_channel(channel));
}
ess_error_t ess_effect::connect(ess_input_module* mod, ess_audio_channel this_channel,
  ess_audio_channel mod_channel) {
    return get_input_channel(this_channel)->connect(mod->get_channel(mod_channel));
}

unsigned int ESS_IRAM_ATTR ess_effect::read(ess_audio_channel id, ess_audioblock_t& block, unsigned int offset) {
  ess_automux_t lock(m_mutex);

  #if ESS_OUTPUT_TIME_ANALYZED == 1
    start_time_analyzed();
  #endif

  int readed = -1;
  ess_input_channel* channel = get_input_channel(id);

  if(channel) {
    readed = channel->read(block, offset);
  }

  if(m_bActive)
    do_effect(block, offset, readed, id);

  #if ESS_OUTPUT_TIME_ANALYZED == 1
     end_time_analyzed();
  #endif

  return readed;
}
