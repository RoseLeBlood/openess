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
 * @file ess_effect.h
 * @author Anna Sopdia Schröck
 * @date 11 März 2019
 * @brief ESS  effect module
 *
 *
 */
 /**
 * @addtogroup dsp
 * @{
 */
#ifndef _ESS_EFFECT_MODULE_H_
#define _ESS_EFFECT_MODULE_H_

#include "../../channel/ess_input_channel.h"
#include  "../ess_input_module.h"

/** @brief basic input output module
*  usable for effect module
**/
// +--------------+
//  |  IN   OUT  |
//  |                   |
// +------------- +


class ess_effect  : public ess_input_module {
public:
  ess_effect();
  ess_effect(const std::string& name);

  virtual ess_error_t add_input_channel(std::string name, ess_audio_channel channel);
  virtual ess_error_t add_input_channel(ess_input_channel* channel);

  virtual ess_error_t add_output_channel(std::string name, ess_audio_channel channel);
  virtual ess_error_t add_output_channel(ess_output_channel* channel);

  virtual ess_input_channel* get_input_channel(ess_audio_channel channel);
  virtual ess_input_channel* get_input_channel(std::string name);

  virtual ess_output_channel* get_output_channel(ess_audio_channel channel);
  virtual ess_output_channel* get_output_channel(std::string name);

  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel channel);
  virtual ess_error_t connect(ess_input_module* mod, ess_audio_channel this_channel,
    ess_audio_channel mod_channel);

  virtual unsigned int read(ess_audio_channel id, ess_audioblock_t& block, unsigned int offset);

protected:
  virtual unsigned int do_effect(ess_audioblock_t& block,
    unsigned int offset, unsigned int size, ess_audio_channel id) = 0;
protected:
  std::list<ess_input_channel*> m_lstInChannels;
};

#endif
/**
* @}
*/
