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
 * @file ess_audio_buffer_stream.h
 * @author Anna Sopdia Schröck
 * @date 18 April 2019
 * @brief OpenESS helper class for ess_effects
 *
 */
#ifndef _OPENESS_AUDIO_BUFFER_HELPER_
#define _OPENESS_AUDIO_BUFFER_HELPER_

#include "ess_stream.h"
#include "ess_audioblock.h"


class ess_audio_buffer_stream : public ess_stream {
public:
    ess_audio_buffer_stream(ess_audioblock_t& value);
    ess_audio_buffer_stream(ess_audioblock_t& value, const std::string& name);

    ess_audio_buffer_stream(const ess_audio_buffer_stream& other ) = delete;

    void set_null() ;
    void set_value(const uint32_t value) ;
    void set_value(const uint32_t value, const uint32_t position ) ;

    virtual size_t read(void* data, const size_t offset, const size_t size);
    virtual size_t write(const void* data, const size_t offset, const size_t size);

    virtual unsigned char read();
    virtual float read_float();

    virtual std::string to_string() ;

    virtual bool can_read();
    virtual bool can_write();
    virtual bool can_seek() { return false; }
    virtual uint32_t get_position() const { return m_iPosition; }


    ess_audio_buffer_stream& operator += (const ess_audio_buffer_stream& v);
    ess_audio_buffer_stream& operator -= (const ess_audio_buffer_stream& v);
    ess_audio_buffer_stream& operator *= (const ess_audio_buffer_stream& v);
    ess_audio_buffer_stream& operator /= (const ess_audio_buffer_stream& v);

    ess_audio_buffer_stream& operator += (const float& f);
    ess_audio_buffer_stream& operator -= (const float& f);
    ess_audio_buffer_stream& operator /= (const float& f);
    ess_audio_buffer_stream& operator *= (const float& f);
protected:
    ess_audioblock_t& m_pMemBlock;
    uint32_t m_iPosition;
};


#endif
