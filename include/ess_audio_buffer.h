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

#include <cmath>

 #include "ess_audio_memory_map.h"

class ess_audio_buffer : public ess_object {
public:
    ess_audio_buffer() : ess_object("ess_audio_buffer") {
        m_pMemBlock = ess_mem_alloc();
        ess_mem_send(m_pMemBlock);
        m_iPosition = 0;
    }
    ess_audio_buffer( const std::string& name) : ess_object(name) {
        m_pMemBlock = ess_mem_alloc();
        ess_mem_send(m_pMemBlock);

        m_iPosition= 0;
    }

    ess_audio_buffer(ess_audioblock_t* value) : ess_object("ess_audio_buffer") {
        m_pMemBlock = value;
        ess_mem_send(m_pMemBlock);
        m_iPosition = 0;
    }

    ess_audio_buffer(ess_audioblock_t* value, const std::string& name) : ess_object(name) {
        m_pMemBlock = value;
        ess_mem_send(m_pMemBlock);

        m_iPosition = 0;
    }

    ess_audio_buffer(const ess_audio_buffer& other ) {
        m_pMemBlock = other.m_pMemBlock;
        ess_mem_send(m_pMemBlock);

        set_name(other.get_name());
        m_iPosition = other.m_iPosition;
    }

    ~ess_audio_buffer() {
        if(ess_mem_free(m_pMemBlock) == 0) {
            delete m_pMemBlock;
            m_pMemBlock = nullptr;
        }
    }





    void reset(ess_audioblock_t* value) {
        if(ess_mem_free(m_pMemBlock) == 0) {
            delete m_pMemBlock;
            m_pMemBlock = nullptr;
        }
        m_pMemBlock = value;
        m_iPosition = 0;
        ess_mem_send(m_pMemBlock);
    }

    ess_audioblock_t& operator *() {
        return *m_pMemBlock;
    }
    ess_audioblock_t* operator ->() {
        return m_pMemBlock;
    }
    operator bool() const   {
        return m_pMemBlock != nullptr;
    }

    ess_audio_buffer& operator = (const ess_audio_buffer& other) {
        if (this != &other) {
            if(ess_mem_free(m_pMemBlock) == 0) {
                delete m_pMemBlock;
                m_pMemBlock = nullptr;
            }
            m_pMemBlock = other.m_pMemBlock;
            m_iPosition = other.m_iPosition;
            ess_mem_send(m_pMemBlock);
            set_name(other.get_name());
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


    void set_null() {
        memset(m_pMemBlock->data, 0, ESS_DEFAULT_AUDIO_PACKET_SIZE)
    }
    void set_value(const uint32_t value) {
        memset(m_pMemBlock->data, value, ESS_DEFAULT_AUDIO_PACKET_SIZE)
    }
    void set_value(const uint32_t value, const uint32_t position ) {
        if(position < ESS_DEFAULT_AUDIO_PACKET_SIZE) {
            m_pMemBlock->data[position] = value;
        }
    }
    size_t read(const float* data, const size_t offset, const size_t size) {
        if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1 }

        int n = ESS_DEFAULT_AUDIO_PACKET_SIZE - m_iPosition;

        if (n > size) n = size;
        if (n <= 0) return 0;

        memmove ((data + offset), (m_pMemBlock->data + m_iPosition), n * sizeof(float) );
        m_iPosition += n;

        return n;
    }
    size_t write(const float* data, const size_t offset, const size_t size) {
        if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1 }

        int i = m_iPosition + size;
        if (i < 0) return -1;
        if (i > ESS_DEFAULT_AUDIO_PACKET_SIZE) return -1;


        memmove ((m_pMemBlock->data + m_iPosition), (data + offset), size * sizeof(float) );

        m_iPosition = i;
        return size;
    }
    float read() {
        if (m_iPosition >= ESS_DEFAULT_AUDIO_PACKET_SIZE) return NAN;

        return m_pMemBlock->data[m_iPosition++];
    }
protected:
    ess_audioblock_t* m_pMemBlock;
    uint32_t m_iPosition;
};


#endif