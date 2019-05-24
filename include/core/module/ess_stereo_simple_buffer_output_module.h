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
 * @file ess_stereo_simple_buffer_output_module.h
 * @author Anna Sopdia Schröck
 * @date 01 April 2019
 * @brief mix audio data (stereo) to a single buffer integer
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
 #ifndef __ESS_OUTPUT_SIMPLE_BUFFER_MODULE_H__
 #define __ESS_OUTPUT_SIMPLE_BUFFER_MODULE_H__

#include "ess_output_module.h"
#include "../channel/ess_input_channel.h"
/**
  * @brief mix audio data (stereo) to a single buffer integer
  * +--------------+
  *  |  IN              |
  *  |  IN              |
  * +------------- +
*/
class ess_stereo_simple_buffer_output_module : public ess_output_module {
public:
  /**
  * @brief  constructor to create the module with a name
  * @param [in] name human name of the module
  **/
  ess_stereo_simple_buffer_output_module(const std::string& name);

  ~ess_stereo_simple_buffer_output_module();
  /**
  * @brief dont add a channel - overide
  * @param [in] name name of the new channel (human name)
  * @param channel which input channel ID are use the new channel
  * @return only 'ESS_ERROR'
  **/
  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel);
  /**
  * @brief dont add a channel - overide
  * @param [in] name name of the new channel (human name)
  * @param channel which input channel ID are use the new channel
  * @return only 'ESS_ERROR'
  **/
  virtual ess_error_t add_channel(ess_input_channel* channel);

  /**
  * @brief  update function  - internal use functions  `send_simple_buffer_to_device`
  **/
  virtual ess_error_t update() ;
protected:
  /**
  * @brief send the simple buffer to the using device
  * @param [in] simple_buffer the buffer to write to device
  * @param [in] offset buffer write offset
  * @param [in] size the size of the buffer
  **/
  virtual size_t send_simple_buffer_to_device(int32_t* simple_buffer, size_t offset, size_t size) = 0;
private:
  int32_t m_iSampleBuffer[ESS_DEFAULT_AUDIO_PACKET_SIZE*2];
  ess_audioblock_t  m_pBuffer_left;
  ess_audioblock_t  m_pBuffer_right;
};

 #endif
 /**
 * @}
 */
