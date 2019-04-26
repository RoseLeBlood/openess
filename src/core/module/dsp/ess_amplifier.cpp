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

#include "core/module/dsp/ess_amplifier.h"
#include <math.h>


ess_amplifier::ess_amplifier()  : ess_effect("ess_amplifier")  { }
ess_amplifier::ess_amplifier(const std::string& name)
  : ess_effect(name)  { }

void ess_amplifier::set_gain(float n) {
  if (n > 100000.0f) n = 100000.0f;       //100000 = 100db [ 1000 = ~1db]
  else if (n < -100000.0f) n = -100000.0f;
  m_fMultiplier = n;
}
void ess_amplifier::set_gain_db(float db){
    if (db > 100.0f) db = 100.0f;
    else if (db < -100.0f) db = -100.0f;
    m_fMultiplier = powf(10.0f,db/20.0f);
}

float ess_amplifier::get_gain() {
  return m_fMultiplier;
}

float ess_amplifier::get_gain_db() {

  if(m_fMultiplier > 100000.0f) return 100.0f;
  else if (m_fMultiplier < -100000.0f) return -100.0f;

  return m_fMultiplier / 1000.0f; // ~
}

unsigned int ESS_IRAM_ATTR ess_amplifier::do_effect(ess_audioblock_t* block, unsigned int offset, unsigned int size,
  ess_audio_channel id) {

  for(size_t i = offset; i < size; i++) {
    block->data[i] *= m_fMultiplier;
  }
  return size;
}
