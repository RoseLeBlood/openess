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
 * @file ess_dsp_multiplexer.h
 * @author Anna Sopdia Schröck
 * @date 26 Apr 2019
 * @brief ESS simple DSP with 1 Inputs and 2 Output (OutB = In; OutA = In)
 */

 /**
 * @addtogroup dsp
 * @{
 */
 #ifndef _ESS_DSP_MULTIPLEXER_H_
 #define _ESS_DSP_MULTIPLEXER_H_

#define ESS_DSP_MULTIPLEXER_OUTA   ESS_AUDIO_CHANNEL_LEFT
#define ESS_DSP_MULTIPLEXER_OUTB   ESS_AUDIO_CHANNEL_RIGHT

 #include "ess_effect.h"

class ess_dsp_multiplexer : ess_effect {
public:
  ess_dsp_multiplexer();
  ess_dsp_multiplexer(const std::string& name);

  virtual ess_error_t add_channel(std::string name, ess_audio_channel channel);

  unsigned int read(ess_audio_channel id, ess_audioblock_t* block, unsigned int offset);
protected:
  virtual unsigned int do_effect(ess_audioblock_t* block,
    unsigned int offset, unsigned int size, ess_audio_channel id) { return 0; /* don't use */ }
private:
  bool m_outUpdate[2];
  ess_audioblock_t* block_hold;
};
#endif

/**
* @}
*/
