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
  ess_input_channel();
  ess_input_channel(std::string name);
  ess_input_channel(std::string name, ess_audio_channel channel );

  ess_error_t connect(ess_output_channel* channel) ;
  ess_error_t disconnect();


   virtual unsigned int read(ess_audioblock_t*  block, unsigned int offset) ;

   virtual bool is_connected();

   virtual std::string to_string();
protected:
  ess_output_channel* m_pConChannel;
};


 /**
 * @}
 */
 #endif
