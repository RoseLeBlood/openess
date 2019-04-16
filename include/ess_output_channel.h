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
 * @file ess_output_channel.h
 * @author Anna Sopdia Schröck
 * @date 08 März 2019
 * @brief channel for the output object
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
 #ifndef __ESS_OUTPUT_CHANNEL_H__
 #define __ESS_OUTPUT_CHANNEL_H__


#include "ess_channel.h"

/**
 * @brief the ess_output_channel class
 * the `ess_input_objec` has n outputs channels
 */
class ess_output_channel : public ess_channel {
public:
  ess_output_channel()  { }

  ess_output_channel(std::string name)
    : ess_channel(name, ESS_CHANNEL_OUTPUT, ESS_AUDIO_CHANNEL_LEFT)
        {  }

  ess_output_channel(std::string name, ess_audio_channel channel )
    : ess_channel(name, ESS_CHANNEL_OUTPUT, channel)
       { }

  virtual unsigned int  read(int32_t* buffer, unsigned int offset, unsigned int size)  {
    ess_automux_t lock(m_mutex);
    memset(buffer, 0, size);

    return size;
   }

   virtual unsigned int get_size() { return ESS_DEFAULT_AUDIO_PACKET_SIZE; }
   virtual int32_t* get_buffer() { return nullptr; }

};


 /**
 * @}
 */
 #endif
