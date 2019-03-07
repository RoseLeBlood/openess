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
#ifndef __ESS_OUTPUT_STREAM_H__
#define __ESS_OUTPUT_STREAM_H__

#include "ess_audio_stream.h"


template <ess_audio_channel_format_t CFORMAT, unsigned int ABS = ESS_DEFAULT_AUDIO_PACKET_SIZE>
class ess_output_stream: public ess_audio_stream {
public:
  ess_output_stream() { }
  ess_output_stream(const std::string& name) :
    ess_audio_stream((unsigned char)CFORMAT, m_pInputQueueArray, name) {   }

  virtual ~ess_output_stream() { }

  virtual ess_audio_channel_format_t get_channel_format() { return CFORMAT; }
protected:
  ess_audio_block_t *m_pInputQueueArray[CFORMAT];
	int32_t m_iSampleBuffer[ABS * CFORMAT];
};

/**
* @}
*/


#endif
