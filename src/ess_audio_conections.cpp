
 /* Teensyduino Core Library
  * http://www.pjrc.com/teensy/
  * Copyright (c) 2017 PJRC.COM, LLC.
  *
  * Permission is hereby granted, free of charge, to any person obtaining
  * a copy of this software and associated documentation files (the
  * "Software"), to deal in the Software without restriction, including
  * without limitation the rights to use, copy, modify, merge, publish,
  * distribute, sublicense, and/or sell copies of the Software, and to
  * permit persons to whom the Software is furnished to do so, subject to
  * the following conditions:
  *
  * 1. The above copyright notice and this permission notice shall be
  * included in all copies or substantial portions of the Software.
  *
  * 2. If the Software is incorporated into a build system that allows
  * selection among a list of target devices, then similar target
  * devices manufactured by PJRC.COM must be included in the list of
  * target devices and selectable in the same manner.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */
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
