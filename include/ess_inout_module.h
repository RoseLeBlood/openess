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
 * @file ess_inout_module.h
 * @author Anna Sopdia Schröck
 * @date 11 März 2019
 * @brief ESS input output effect module
 *
 *
 */
 /**
 * @addtogroup ess_effect
 * @{
 */
#ifndef _ESS_INPUT_OUTPUT_MODULE_H_
#define _ESS_INPUT_OUTPUT_MODULE_H_

#include "ess_output_module.h"

/** @brief basic input output module
*  usable for effect module
**/
// +--------------+
//  |  IN   OUT  |
//  |                   |
// +------------- +
class ess_inout_module  : public ess_module {
public:
  struct entry {
    ess_input_channel* input;
    ess_output_channel* output;
    std::string name;
    ess_audio_channel channel;
  };
  ess_inout_module() : ess_module("ess_inout_module") { }
  ess_inout_module(const std::string& name)
    : ess_module(name)  { }

  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel) {
    entry new_entry;

    new_entry.input = new ess_input_channel(name + std::string("_in")  );
    new_entry.output = new ess_output_channel(name + std::string("_out")  );
    new_entry.name = name;
    new_entry.channel = channel;

    m_lstChannels.push_back(new_entry);

    return ESS_OK;
  }

  virtual ess_input_channel* get_channel(ess_audio_channel channel) {
    std::list<entry>::iterator it;
    for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
      if( (*it).channel == channel ) return (*it).input;
    }
    return nullptr;
  }
  virtual ess_input_channel* get_channel(std::string name) {
    std::list<entry>::iterator it;
    for(it = m_lstChannels.begin(); it != m_lstChannels.end(); it++) {
      if( (*it).name == name ) return (*it).input;
    }
    return nullptr;
  }

  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel channel) {
    return get_channel(channel)->connect(mod->get_channel(channel));
  }
  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel this_channel,
    ess_audio_channel mod_channel) {
      return get_channel(this_channel)->connect(mod->get_channel(mod_channel));
    }
protected:
  std::list<entry> m_lstChannels;
};

#endif
/**
* @}
*/
