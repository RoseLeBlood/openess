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


#include "ess_audio_stream.h"

ess_audio_stream::ess_audio_stream(unsigned char ninput, ess_audio_block_t **iqueue,
  const std::string defaultName) : name(defaultName), num_inputs(ninput), inputQueue(iqueue) {
    active = false;
    blocking = false;
    destination_list = NULL;
    for (int i=0; i < num_inputs; i++) {
      inputQueue[i] = NULL;
    }

    if (first_update == NULL) {
      first_update = this;
    } else {
      ess_audio_stream *p;
      for (p=first_update; p->next_update; p = p->next_update) ;
      p->next_update = this;
    }
    next_update = NULL;
    numConnections = 0;
  }
