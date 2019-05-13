#include "net/ess_server_stream.h"

size_t ess_server_stream::read(void* data, const size_t offset, const size_t size)  {
  if (offset >= size || !can_read()) { return -1; }
  return m_sServer.read( data, size);
}
size_t ess_server_stream::write(const void* data, const size_t offset, const size_t size)  {
  if (offset >= size || !can_write()) { return -1; }
  return m_sServer.write( data , size);
}

unsigned char  ess_server_stream::read() {
  unsigned char buf;
  read(&buf, 0, 1);
  return buf;
}
