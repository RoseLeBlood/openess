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
 * @file ess_channel.h
 * @author Anna Sopdia Schröck
 * @date 08 März 2019
 * @brief basic class for `ess_input_channel` and ''ess_output_channel
 *
 *
 */
 /**
 * @addtogroup ess
 * @{
 */
 #ifndef __ESS_CHANNEL_H__
 #define __ESS_CHANNEL_H__

 #include "ess.h"


 /**
  * @brief generic channel class - basic class for `ess_input_channel` and `ess_output_channel`
  *
  * all openess modules have n inputs channels or / and n outputs channels
  */
class ess_channel : public ess_object {
public:
  /**
   * @brief basic constructer
   */
  ess_channel() : ess_channel("ess_object", ESS_CHANNEL_INPUT) { }

  /**
   * @brief second constructer
   * @param [in] name human readelble name for the channel
   * @param [in] type type of the channel
   */
  ess_channel(std::string name, ess_channel_t type) :
    ess_channel(name, type, ESS_AUDIO_CHANNEL_LEFT ) { }

  /**
   * @brief third constructer
   * @param [in] name human readelble name for the channel
   * @param [in] type type of the channel
   * @param [in] channel which channel
   */
  ess_channel(std::string name, ess_channel_t type, ess_audio_channel channel)
    : ess_object(name), m_iChannel(channel),  m_eType(type) { }

  /**
   * @brief get the using channel (id)
   * @return tthe using channel
   */
  ess_audio_channel get_channel() { return m_iChannel; }
  /**
   * @brief get the type of the channel
   * @return the type of the channel
   */
  ess_channel_t get_type() { return m_eType; }

  /**
   * @brief is the channel a input channel
   * @retval true the channel is a input channel
   * @retval false the channel is not a input channel
   */
  bool is_input() { return m_eType == ESS_CHANNEL_INPUT; }
  /**
   * @brief is the channel a output channel
   * @retval true the channel is a output channel
   * @retval false the channel is not a output channel
   */
  bool is_output() { return m_eType == ESS_CHANNEL_OUTPUT; }
  /**
   * @brief is the channel valid
   * @retval true the channel is not a input or output channel
   * @retval false the channel is valid
   */
  bool is_invalid() { return m_eType >= ESS_CHANNEL_MAX; }

  /**
   * @brief read interface
   *
   *  the output object read from input
   * @param [out] buffer the pointer to write the data to
   * @param [in] offset the readed offset
   * @param [in] size length of the buffer
   *
   * @return  the readed bytes
   * @retval -1 somthings are wrong : error
   */
  virtual unsigned int read(int32_t* buffer, unsigned int offset, unsigned int size) = 0;
protected:
  /**
   * @brief set the channel
   * @param [in]  name  the new channel
   */
  void set_channel(const ess_audio_channel channel) { m_iChannel = channel; }
  /**
   * @brief set the type of this channel
   * @param [in]  name  the new type of this channel
   */
  void set_type(const ess_channel_t type) { m_eType = type; }
protected:
  ess_audio_channel m_iChannel;
  ess_channel_t m_eType;
};

/**
* @}
*/
#endif
