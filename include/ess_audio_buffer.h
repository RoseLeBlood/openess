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
 * @file ess_audio_buffer.h
 * @author Anna Sopdia Schröck
 * @date 18 April 2019
 * @brief OpenESS audio buffer with auto debugging
 *
 */
#ifndef _OPENESS_AUDIO_AUDIO_BUFFER_MAP_
#define _OPENESS_AUDIO_AUDIO_BUFFER_MAP_

#include "ess_object.h"
#include "ess_audioblock.h"

/*
class ess_audio_buffer : public ess_object {
public:
    ess_audio_buffer();

    ess_audio_buffer(ess_audioblock_t* value);
    ess_audio_buffer( const std::string& name);
    ess_audio_buffer(ess_audioblock_t* value, const std::string& name);

    ess_audio_buffer(const ess_audio_buffer& other );
    ~ess_audio_buffer();

    ess_audioblock_t& operator *() {
        return *m_pMemBlock;
    }
    ess_audioblock_t* operator ->() {
        return m_pMemBlock;
    }
    operator bool() const   {
        return m_pMemBlock != nullptr;
    }

    void set_null() ;
    void set_value(const uint32_t value) ;
    void set_value(const uint32_t value, const uint32_t position ) ;

    size_t read(float* data, const size_t offset, const size_t size);
    size_t write(const float* data, const size_t offset, const size_t size);

    float get_float();

    void reset(ess_audioblock_t* value);

    virtual std::string to_string() ;

    ess_audio_buffer& operator = (const ess_audio_buffer& other) {
        if (this != &other) {
            if(ess_memory_map::Instance().release_block(m_pMemBlock) == 0) {
                m_pMemBlock = nullptr;
            }
            m_pMemBlock = other.m_pMemBlock;
            m_iPosition = other.m_iPosition;
            if(m_pMemBlock) m_pMemBlock->ref_count++;

            m_strName = other.m_strName;
        }
        return *this;
    }

    ess_audio_buffer& operator += (const ess_audio_buffer& v) {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] += v.m_pMemBlock->data[i];
        }
        return *this;
    }
    ess_audio_buffer& operator -= (const ess_audio_buffer& v)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] -= v.m_pMemBlock->data[i];
        }
        return *this;
    }
    ess_audio_buffer& operator *= (const ess_audio_buffer& v)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] *= v.m_pMemBlock->data[i];
        }
        return *this;
    }
    ess_audio_buffer& operator /= (const ess_audio_buffer& v)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] /= v.m_pMemBlock->data[i];
        }
        return *this;
    }

    ess_audio_buffer& operator += (const float& f)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] += f;
        }
        return *this;
    }
    ess_audio_buffer& operator -= (const float& f)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] -= f;
        }
        return *this;
    }

    ess_audio_buffer& operator /= (const float& f)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] /= f;
        }
        return *this;
    }
    ess_audio_buffer& operator *= (const float& f)  {
        for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
            m_pMemBlock->data[i] *= f;
        }
        return *this;
    }
protected:
    ess_audioblock_t* m_pMemBlock;
    uint32_t m_iPosition;
};
*/

#endif
