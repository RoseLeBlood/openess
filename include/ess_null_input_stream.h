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
 * @file ess_null_input_stream.h
 * @author Anna Sopdia Schröck
 * @date 07 März 2019
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

#include "ess_input_stream.h"

 class ess_null_input_stream : public ess_input_stream<ESS_CHANNEL_FORMAT_STEREO> {
public:
  ess_null_input_stream() : ess_input_stream<ESS_CHANNEL_FORMAT_STEREO>(ESS_INPUT_STREAM_NULL) {
    m_bBlockingObjectRun = true;
    m_bBlocking = true;
    m_bInit = true;
  }

  ess_error_t update(void)  {
    ess_audio_block_t *new_left, *new_right;

    new_left = allocate();
		new_right = allocate();

		if (new_right != NULL && new_left != NULL) {

      memset(new_left->data, 0, sizeof(new_left));
      memset(new_right->data, 0, sizeof(new_right));

      transmit(new_left, 0);
  		release(new_left);
  		transmit(new_right, 1);
  		release(new_right);
    }
    return ESS_OK;
  }

 };


 /**
 * @}
 */


 #endif
