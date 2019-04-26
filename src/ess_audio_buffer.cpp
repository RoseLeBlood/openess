#include "ess.h"
#include "ess_audio_buffer.h"

#include <sstream>

ess_audio_buffer::ess_audio_buffer(ess_audioblock_t& value)
  :  ess_object("ess_audio_buffer"), m_pMemBlock(value), m_iPosition(0)  {
}

ess_audio_buffer::ess_audio_buffer(ess_audioblock_t& value, const std::string& name)
  :  ess_object(name), m_pMemBlock(value), m_iPosition(0)  {
}
size_t ess_audio_buffer::read(float* data, const size_t offset, const size_t size) {
    if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1; }

    int n = ESS_DEFAULT_AUDIO_PACKET_SIZE - m_iPosition;

    if (n > size) n = size;
    if (n <= 0) return 0;

    memmove ((data + offset), (m_pMemBlock.data + m_iPosition), n * sizeof(float) );
    m_iPosition += n;

    return n;
}
size_t ess_audio_buffer::write(const float* data, const size_t offset, const size_t size) {
    if (ESS_DEFAULT_AUDIO_PACKET_SIZE - offset < size) { return -1; }

    int i = m_iPosition + size;
    if (i < 0) return -1;
    if (i > ESS_DEFAULT_AUDIO_PACKET_SIZE) return -1;


    memmove ((m_pMemBlock.data + m_iPosition), (data + offset), size * sizeof(float) );

    m_iPosition = i;
    return size;
}
float ess_audio_buffer::read() {
    if (m_iPosition >= ESS_DEFAULT_AUDIO_PACKET_SIZE) return 0.0f/0.0f;

    return m_pMemBlock.data[m_iPosition++];
}
void ess_audio_buffer::set_null() {
    ess_zeromem(m_pMemBlock.data, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}

void ess_audio_buffer::set_value(const uint32_t value) {
    ess_memset(m_pMemBlock.data, value, ESS_DEFAULT_AUDIO_PACKET_SIZE);
}

void ess_audio_buffer::set_value(const uint32_t value, const uint32_t position ) {
    if(position < ESS_DEFAULT_AUDIO_PACKET_SIZE) {
        m_pMemBlock.data[position] = value;
    }
}
std::string ess_audio_buffer::to_string()  {
  std::ostringstream ss;

  ss << get_name() << " ref: " << (uint32_t)(m_pMemBlock.ref_count);
  return ss.str();
}
