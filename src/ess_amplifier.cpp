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

#include "ess_amplifier.h"
#include <math.h>

ess_amplifier::ess_amplifier() { }
ess_amplifier::ess_amplifier(const std::string& name)
  : ess_inout_module(name)  { }

unsigned int ess_amplifier::read(ess_audio_channel id, int32_t* buffer, unsigned int offset, unsigned int size) {
  if(buffer == NULL || size == 0) return 0;

  ess_input_channel* channel = get_channel(id);

  if(channel == NULL) return 0;

  unsigned int readed = channel->read(buffer, offset, size);

  for(int i=0; i < readed; i++) {
    buffer[readed] = buffer[readed] * m_fMultiplier;
  }
  return readed;
}
void ess_amplifier::set_gain(float n) {
  if (n > 100000.0f) n = 100000.0f;       //100000 = 100db
  else if (n < -100000.0f) n = -100000.0f;
  m_fMultiplier = n;
}
void ess_amplifier::set_gain_db(float db){
    if (db > 100.0f) db = 100.0f;
    else if (db < -100.0f) db = -100.0f;
    m_fMultiplier = powf(10.0f,db/20.0f);
}
