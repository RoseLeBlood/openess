
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
/**
 * @file ess_audio_conections.h
 * @author Anna Sopdia Schröck
 * @date 03 März 2019
 *
 *
 */
 /**
 * @addtogroup stream
 * @{
 */
#ifndef __ESS_AUDIO_CONNECTIONS_H__
#define __ESS_AUDIO_CONNECTIONS_H__

class ess_audio_stream;

class ess_audio_conections {
  friend class ess_audio_stream;
public:
	ess_audio_conections(ess_audio_stream &source, ess_audio_stream &destination)
    : ess_audio_conections(source, 0, destination, 0) { }

	ess_audio_conections(ess_audio_stream &source, unsigned char sourceOutput,
		ess_audio_stream &destination, unsigned char destinationInput);

	~ess_audio_conections();

	void disconnect(void);
	void connect(void);
protected:
	ess_audio_stream &m_pSrc;
	ess_audio_stream &m_pDst;

	unsigned char m_iSrcIndex;
	unsigned char m_iDestIndex;
	ess_audio_conections *m_pNext;
	bool m_bIsConnected;
};

/**
* @}
*/

#endif
