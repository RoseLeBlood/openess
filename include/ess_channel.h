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
 * @date 04 März 2019
 * @brief basic mixer input  stream
 *
 *  the ess_channel is the mixer input channel
 */
 /**
 * @addtogroup channel
 * @{
 */
 #ifndef __ESS_CHANNEL_H__
 #define __ESS_CHANNEL_H__

#include "ess.h"
#include "ess_error.h"
#include "ess_format.h"
#include "ess_task.h"
#include "ess_audio_stream.h"

class ess_channel : public ess_audio_stream, public ess_task {
public:
  /**
   * @brief basic constructer
   * @param name the name of the channel
   * @param outputs number of outputs of this channel
   */
  explicit ess_channel(const std::string& name, int outputs = 2)
    : ess_audio_stream(0, NULL, name), m_bConfigured(false), m_bActive(false), m_iOutputs(outputs) {
      m_sampleBufferSize = m_iOutputs * ESS_DEFAULT_AUDIO_PACKET_SIZE;
  }

  /**
 * @brief basic destructor
 */
  virtual ~ess_channel() { }

  /**
 * @brief init the channel, must be set_active for using -  ess_mixer using this functions
 * @return ESS_OK when channel created all other are error
 */
  virtual ess_error_t init() = 0;
  /**
 * @brief destroy the channel  -  ess_mixer using this functions
 */
  virtual ess_error_t destroy() = 0;

  /**
  * @ brief is the channel active
  * @return true whenn channel active is other the channel is deactive
  * @retval true channel is active
  * @retval false channel is deactive
  **/
  virtual bool is_active() { return m_bActive; }

  /**
  * @ brief is the channel configured (init)
  * @return true whenn channel configured is other the channel is not  configured
  * @retval true channel is configured
  * @retval false channel is not configured
  **/
  virtual bool is_configured() { return m_bConfigured; }

  /**
  * @ brief set channel active
  *
  * @retval ESS_ERROR channel is not configured
  * @retval ESS_OK no error
  **/
  virtual ess_error_t set_active(bool value) { if(!is_configured()) return ESS_ERROR; m_bActive = value;  return ESS_OK; }

  /**
  * @ brief get number outputs
  *
  * @return the number of outputs
  * @retval 0 the channel is not configured
  **/
  virtual uint8_t get_outputs() { if(!is_configured()) return 0;  return m_iOutputs; }
protected:
  bool m_bConfigured;
  bool m_bActive;

  uint8_t m_iOutputs;
  float* m_pSampleData;
  unsigned int m_sampleBufferSize;
};



 /**
 * @}
 */


 #endif
