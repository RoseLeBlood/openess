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
 * @file ess_input_module.h
 * @author Anna Sopdia Schröck
 * @date 08 März 2019
 * @brief ESS generic input module
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
#ifndef __ESS_INPUT_MODULE_H__
#define __ESS_INPUT_MODULE_H__

#include "ess_output_channel.h"
#include "ess_module.h"
#include <list>

/**
  * @brief basic class for input module - example `ess_null_input_module`
  * +--------------+
  *  |         OUT: |
  *  |         OUT: |
  * +------------- +
*/
class ess_input_module : public ess_module  {
public:
  ess_input_module(const std::string& name)  : ess_module(name) { }

  virtual ~ess_input_module() { }

  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel);
  virtual ess_error_t add_channel(ess_output_channel* channel);

  virtual ess_output_channel* get_channel(ess_audio_channel channel);
  virtual ess_output_channel* get_channel(std::string name);

  virtual unsigned int read(ess_audio_channel id, ess_audioblock_t*  block, unsigned int offset);

  virtual int32_t* get_buffer(ess_audio_channel id);
  virtual uint32_t get_size(ess_audio_channel id);

  virtual std::string to_string();
protected:
  std::list<ess_output_channel*> m_lstChannels;
};

/**
* @}
*/


#endif
