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
 * @file ess_input_stream.h
 * @author Anna Sopdia Schröck
 * @date 07 März 2019
 * @brief ESS generic input stream
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
#ifndef __ESS_INPUT_STREAM_H__
#define __ESS_INPUT_STREAM_H__

#include "ess_audio_stream.h"



template <ess_audio_channel_format_t CFORMAT, unsigned int ABS = ESS_DEFAULT_AUDIO_PACKET_SIZE>
class ess_input_stream : public ess_audio_stream {
public:
  ess_input_stream() { }
  ess_input_stream(const std::string& name) :
    ess_audio_stream(0, NULL, name) {   }

  virtual ~ess_input_stream() { }

 virtual ess_audio_channel_format_t get_channel_format() { return CFORMAT; }

 virtual ess_stream_type_t get_type() { return ESS_INPUT_STREAM; }
protected:
  int32_t m_iSampleBuffer[ABS * CFORMAT];
};

/**
* @}
*/


#endif
