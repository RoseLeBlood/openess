
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
