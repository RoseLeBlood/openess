
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

#include "ess_audio_conections.h"
#include <stdio.h>

ess_audio_conections::ess_audio_conections(ess_audio_stream &source, unsigned char sourceOutput,
  ess_audio_stream &destination, unsigned char destinationInput) : m_pSrc(source), m_pDst(destination) {

  m_iSrcIndex = sourceOutput;
  m_iDestIndex = destinationInput;
  m_pNext = NULL;

  m_bIsConnected = false;
  connect();
}
ess_audio_conections::~ess_audio_conections() {
  disconnect();
}
