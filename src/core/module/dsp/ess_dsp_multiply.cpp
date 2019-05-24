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
#include "core/module/dsp/ess_dsp_multiply.h"

ess_error_t ess_dsp_multiply::add_channel(std::string name, ess_audio_channel channel) {
  ess_error_t tr = ESS_OK;

  tr = add_output_channel(name + std::string("_out"), channel);
  tr = add_input_channel(name + std::string("_ina"), (ess_audio_channel)  (ESS_AUDIO_EFFECT_CHANNEL * channel) ); // 1000
  tr = add_input_channel(name + std::string("_inb"), (ess_audio_channel)  ((ESS_AUDIO_EFFECT_CHANNEL *  channel) + 1) ); // 1001
  return tr;
}
unsigned int ESS_IRAM_ATTR ess_dsp_multiply::read(ess_audio_channel id, ess_audioblock_t& block, unsigned int offset) {
  ess_automux_t lock(m_mutex);

#if ESS_OUTPUT_TIME_ANALYZED == 1
  start_time_analyzed();
#endif

  uint32_t readeda = 0, readedb = 0;
  bool blocked = false;

  static ess_audioblock_t block_ina;
  static ess_audioblock_t block_inb;

  ess_input_channel* ina = get_input_channel( (ess_audio_channel) (ESS_AUDIO_EFFECT_CHANNEL *  id) );
  ess_input_channel* inb = get_input_channel( (ess_audio_channel) ((ESS_AUDIO_EFFECT_CHANNEL *  id) + 1) );

  if(ina) {
    readeda = ina->read(block_ina, offset);
  }

  if(inb) {
    readedb = inb->read(block_inb, offset);
  }

  if(readedb <= 0) blocked = true;
  if(readeda <= 0) blocked = true;

  if(!blocked) {
    for (int i = 0; i < readeda; i++) {
        block.data[i] += block_ina.data[i] * block_inb.data[i];
    }
  } else {

  }

#if ESS_OUTPUT_TIME_ANALYZED == 1
   end_time_analyzed();
#endif
  return readeda;
}
