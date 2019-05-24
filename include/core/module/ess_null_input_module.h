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
 * @file ess_null_input_module.h
 * @author Anna Sopdia Schröck
 * @date 22 März 2019
 * @brief OpenESS Null input stream
 *
 *
 */
 #ifndef _ESS_NULL_INPUT_STREAM_
 #define _ESS_NULL_INPUT_STREAM_
 /**
 * @addtogroup input_stream
 * @{
 */

#include "ess_input_module.h"

class ess_null_output_channel : public ess_output_channel {
public:
  ess_null_output_channel(std::string name, ess_audio_channel channel )
    : ess_output_channel(name, channel) { }

  virtual unsigned int  read(ess_audioblock_t& block, unsigned int offset)  {
      ess_automux_t lock(m_mutex);
      ess_zeromem(block.data, ESS_DEFAULT_AUDIO_PACKET_SIZE);

      return ESS_DEFAULT_AUDIO_PACKET_SIZE;
   }
};

class ess_null_input_module : public ess_input_module {
public:
  ess_null_input_module() : ess_input_module("null_input") {
    add_channel(new ess_null_output_channel("null_left", ESS_AUDIO_CHANNEL_LEFT));
    add_channel(new ess_null_output_channel("null_right", ESS_AUDIO_CHANNEL_RIGHT));
  }
};

 /**
 * @}
 */


 #endif
