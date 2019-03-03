
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


void ess_audio_conections::connect(void) {
	ess_audio_conections *p;

	if (m_bIsConnected) return;
	if (m_iDestIndex > m_pDst.m_ucNumInputs) return;

	p = m_pSrc.m_pDestList;

	if (p == NULL) {
		m_pSrc.m_pDestList = this;
	} else {

		while (p->m_pNext) {
			if (&p->m_pSrc == &this->m_pSrc && &p->m_pDst == &this->m_pDst &&
              p->m_iSrcIndex == this->m_iSrcIndex && p->m_iDestIndex == this->m_iDestIndex) {
				return;
			}
			p = p->m_pNext;
		}

		p->m_pNext = this;
	}
	this->m_pNext = NULL;
	m_pSrc.m_ucNumConn++;
	m_pSrc.m_bActive = true;

	m_pDst.m_ucNumConn++;
	m_pDst.m_bActive = true;

	m_bIsConnected = true;
}

void ess_audio_conections::disconnect(void) {
	ess_audio_conections *p;

	if (!m_bIsConnected) return;
	if (m_iDestIndex > m_pDst.m_ucNumInputs) return;

	p = m_pSrc.m_pDestList;

	if (p == NULL)  return;
	else if (p == this) {

		if (p->m_pNext) {
			m_pSrc.m_pDestList = m_pNext;

		} else {
			m_pSrc.m_pDestList = NULL;
		}

	} else {

		while (p) {
			if (p == this) {
				if (p->m_pNext) {
					p = m_pNext;
					break;
				} else {
					p = NULL;
					break;
				}
			}
			p = p->m_pNext;
		}
	}

	m_pDst.m_pInputQueue[m_iDestIndex] = NULL;

	m_pSrc.m_ucNumConn--;

	if (m_pSrc.m_ucNumConn == 0) {
		m_pSrc.m_bActive = false;
	}

	m_pDst.m_ucNumConn--;

	if (m_pDst.m_ucNumConn == 0) {
		m_pDst.m_bActive = false;
	}

	m_bIsConnected = false;
}
