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

#include "core/module/dsp/ess_dsp_multiplexer.h"

ess_dsp_multiplexer::ess_dsp_multiplexer() : ess_dsp_multiplexer("ess_dsp_multiplexer") { }

ess_dsp_multiplexer::ess_dsp_multiplexer(const std::string& name) : ess_effect(name)  {
  add_output_channel("dsp_multi_outa", ESS_DSP_MULTIPLEXER_OUTA );
  add_output_channel("dsp_multi_outb", ESS_DSP_MULTIPLEXER_OUTB ); // 1001

  add_input_channel("dsp_multi_inb", ESS_DSP_MULTIPLEXER_OUTA );

  m_outUpdate[0]  = true;
  m_outUpdate[1]  = true;
}

ess_error_t ess_dsp_multiplexer::add_channel(std::string name, ess_audio_channel channel) {
  return ESS_OK;
}

unsigned int ESS_IRAM_ATTR ess_dsp_multiplexer::read(ess_audio_channel id,
  ess_audioblock_t& block, unsigned int offset) {
  ess_automux_t lock(m_mutex);

   #if ESS_OUTPUT_TIME_ANALYZED == 1
     start_time_analyzed();
   #endif

   if(id == ESS_DSP_MULTIPLEXER_OUTA || ESS_DSP_MULTIPLEXER_OUTB) {

     if(m_outUpdate[0]  && m_outUpdate[1] ) {
       ess_input_channel* in = get_input_channel( id );
       if(in) {

         in->read(block_hold, offset);

         m_outUpdate[0]  = false;
         m_outUpdate[1]  = false;
       }
     }

    memmove(block.data, block_hold.data, sizeof(block.data));
    m_outUpdate[id] = true;

   }

#if ESS_OUTPUT_TIME_ANALYZED == 1
  end_time_analyzed();
#endif

   return 0;
 }
