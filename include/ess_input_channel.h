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
 * @file ess_input_channel.h
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
 #ifndef __ESS_INPUT_CHANNEL_H__
 #define __ESS_INPUT_CHANNEL_H__

#include "ess_output_channel.h"

/**
 * @brief the ess_input_channel class
 * the `ess_output_objec` has n input channels
 * the input channel read from connected `ess_output_channel`
 */
class ess_input_channel : public ess_channel {
public:
  ess_input_channel()
    : ess_input_channel("ess_input_channel", ESS_AUDIO_CHANNEL_LEFT)  { }

  ess_input_channel(std::string name)
    : ess_channel(name, ESS_CHANNEL_INPUT, ESS_AUDIO_CHANNEL_LEFT),
      m_pConChannel(NULL)  { }

  ess_input_channel(std::string name, ess_audio_channel channel )
    : ess_channel(name, ESS_CHANNEL_INPUT, channel),
      m_pConChannel(NULL) { }

   bool is_connected() { return m_pConChannel != NULL; }

   virtual unsigned int read(int32_t* buffer, unsigned int offset, unsigned int size) {
     return is_connected() ? m_pConChannel->read(buffer, offset, size) : -1;
   }

   ess_error_t connect(ess_output_channel* channel) {
     if(m_pConChannel != NULL )  return ESS_ERROR_CONNECT;

     m_pConChannel = channel;
     return ESS_OK;
   }
protected:
  ess_output_channel* m_pConChannel;
};


 /**
 * @}
 */
 #endif
