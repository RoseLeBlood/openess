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
 * @file ess_output_stream.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ESS generic ouput stream
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
#ifndef __ESS_OUTPUT_MODULE_H__
#define __ESS_OUTPUT_MODULE_H__

#include "ess_module.h"

#include "../channel/ess_input_channel.h"
#include "ess_input_module.h"

#include <list>

/**
  * @brief basic class for output module - example `ess_null_input_module`
  * +--------------+
  *  |  IN              |
  *  |  IN              |
  * +------------- +
*/
class ess_effect;

class ess_output_module: public ess_time_analyzed_module {
public:
  ess_output_module(const std::string& name) : ess_time_analyzed_module(name) {   }

  virtual ~ess_output_module() { }

  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel);
  virtual ess_error_t add_channel(ess_input_channel* channel);

  virtual ess_input_channel* get_channel(ess_audio_channel channel);
  virtual ess_input_channel* get_channel(std::string name);

  virtual unsigned int read(ess_audio_channel id, ess_audioblock_t&   block, unsigned int offset);

  virtual ess_error_t update() = 0;

  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel channel);
  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel this_channel,
    ess_audio_channel mod_channel);

  virtual ess_error_t connect(ess_effect* mod, ess_audio_channel channel);
  virtual ess_error_t connect(ess_effect* mod, ess_audio_channel this_channel,
    ess_audio_channel mod_channel);

  virtual std::string to_string();

  virtual bool allow_multi() { return false; }
protected:
  std::list<ess_input_channel*> m_lstChannels;
};



/**
* @}
*/


#endif
