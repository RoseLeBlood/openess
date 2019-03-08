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
#include "ess_input_channel.h"
#include <list>

/**
  * @brief basic class for input module - example `ess_null_input_module`
  * +--------------+
  *  |  IN              |
  *  |  IN              |
  * +------------- +
*/
class ess_output_module: public ess_module {
public:
  ess_output_module(const std::string& name) : ess_module(name) {   }

  virtual ~ess_output_module() { }

  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel);
  virtual ess_error_t add_channel(ess_input_channel* channel);

  virtual ess_input_channel* get_channel(ess_audio_channel channel);
  virtual ess_input_channel* get_channel(std::string name);

  virtual unsigned int read(ess_audio_channel id, int32_t* buffer,
    unsigned int offset, unsigned int size);

  virtual ess_error_t update() = 0;
protected:
  std::list<ess_input_channel*> m_lstChannels;
};

/**
* @}
*/


#endif
