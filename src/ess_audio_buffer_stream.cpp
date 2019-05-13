#include "ess.h"
#include "ess_audio_buffer_stream.h"

#include <sstream>

ess_audio_buffer_stream::ess_audio_buffer_stream(ess_audioblock_t& value)
  :  ess_stream("ess_audio_buffer_stream"), m_pMemBlock(value), m_iPosition(0)  {
}

ess_audio_buffer_stream::ess_audio_buffer_stream(ess_audioblock_t& value, const std::string& name)
  :  ess_stream(name), m_pMemBlock(value), m_iPosition(0)  {
}
size_t ess_audio_buffer_stream::read(void* data, const size_t offset, const size_t size) {
    if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1; }

    int n = ESS_DEFAULT_AUDIO_PACKET_SIZE - m_iPosition;

    if (n > size) n = size;
    if (n <= 0) return 0;

    memmove ((data + offset), (m_pMemBlock.data + m_iPosition), n );
    m_iPosition += n;

    return n;
}
size_t ess_audio_buffer_stream::write(const void* data, const size_t offset, const size_t size) {
    if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1; }

    int i = m_iPosition + size;
    if (i < 0) return -1;
    if (i > ESS_DEFAULT_AUDIO_PACKET_SIZE) return -1;


    memmove ((m_pMemBlock.data + m_iPosition), (data + offset), size );

    m_iPosition = i;
    return size;
}
bool ess_audio_buffer_stream::can_read() {
  return ( (ESS_DEFAULT_AUDIO_PACKET_SIZE - m_iPosition)  > 0) ;
}
bool ess_audio_buffer_stream::can_write() {
  return   (m_iPosition < ESS_DEFAULT_AUDIO_PACKET_SIZE);
}
float ess_audio_buffer_stream::read_float() {
    return m_pMemBlock.data[m_iPosition++];
}
unsigned char  ess_audio_buffer_stream::read() {
    return (unsigned char)('0');
}


void ess_audio_buffer_stream::set_null() {
    ess_zeromem(m_pMemBlock.data, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}

void ess_audio_buffer_stream::set_value(const uint32_t value) {
    ess_memset(m_pMemBlock.data, value, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}

void ess_audio_buffer_stream::set_value(const uint32_t value, const uint32_t position ) {
    if(position < ESS_DEFAULT_AUDIO_PACKET_SIZE) {
        m_pMemBlock.data[position] = value;
    }
}
std::string ess_audio_buffer_stream::to_string()  {
  std::ostringstream ss;

  ss << get_name() << " ref: " << (uint32_t)(m_pMemBlock.ref_count);
  return ss.str();
}

ess_audio_buffer_stream& ess_audio_buffer_stream::operator += (const ess_audio_buffer_stream& v) {
    for (int i = 0; i < v.get_position(); i++) {
        m_pMemBlock.data[i] += v.m_pMemBlock.data[i];
    }
    return *this;
}
ess_audio_buffer_stream& ess_audio_buffer_stream::operator -= (const ess_audio_buffer_stream& v)  {
    for (int i = 0; i < v.get_position(); i++) {
        m_pMemBlock.data[i] -= v.m_pMemBlock.data[i];
    }
    return *this;
}
ess_audio_buffer_stream& ess_audio_buffer_stream::operator *= (const ess_audio_buffer_stream& v)  {
    for (int i = 0; i < v.get_position(); i++) {
        m_pMemBlock.data[i] *= v.m_pMemBlock.data[i];
    }
    return *this;
}
ess_audio_buffer_stream& ess_audio_buffer_stream::operator /= (const ess_audio_buffer_stream& v)  {
    for (int i = 0; i < v.get_position(); i++) {
        m_pMemBlock.data[i] /= v.m_pMemBlock.data[i];
    }
    return *this;
}

ess_audio_buffer_stream& ess_audio_buffer_stream::operator += (const float& f)  {
    for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
        m_pMemBlock.data[i] += f;
    }
    return *this;
}
ess_audio_buffer_stream& ess_audio_buffer_stream::operator -= (const float& f)  {
    for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
        m_pMemBlock.data[i] -= f;
    }
    return *this;
}

ess_audio_buffer_stream& ess_audio_buffer_stream::operator /= (const float& f)  {
    for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
        m_pMemBlock.data[i] /= f;
    }
    return *this;
}
ess_audio_buffer_stream& ess_audio_buffer_stream::operator *= (const float& f)  {
    for (int i = 0; i < ESS_DEFAULT_AUDIO_PACKET_SIZE; i++) {
        m_pMemBlock.data[i] *= f;
    }
    return *this;
}
