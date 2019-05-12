#include "config.h"
#ifdef ESS_CONFIG_STREAM_WRITER_GENERIC

#include "ess_stream_writer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

size_t ess_stream_writer::write(const char * format, ...) {
  char loc_buf[64];
  char * temp = loc_buf;
  va_list arg;
  va_list copy;
  va_start(arg, format);
  va_copy(copy, arg);
  size_t len = vsnprintf(NULL, 0, format, arg);
  va_end(copy);

  if(len >= sizeof(loc_buf)){
      temp = new char[len+1];
      if(temp == NULL) {
          return 0;
      }
  }
  len = vsnprintf(temp, len+1, format, arg);
  m_refStream.write(temp, 0, len);
  va_end(arg);
  if(len >= sizeof(loc_buf)){
      delete[] temp;
  }
  return len;
}

size_t ess_stream_writer::write(const std::string &s) {
    return m_refStream.write(s.c_str(), 0, s.length());
}

size_t ess_stream_writer::write(const char *str) {
    return m_refStream.write(str, 0, strlen(str));
}

size_t ess_stream_writer::write(char c) {
    return m_refStream.write(&c, 0, 1);
}

size_t ess_stream_writer::write(unsigned char c) {
  return write_number_internal((unsigned long) c, ESS_STREAM_WRITER_FORMAT_DEC);
}

size_t ess_stream_writer::write(int value, ess_stream_format_t base){
  int t = 0;
  if(base == ESS_STREAM_WRITER_FORMAT_DEC &&  (value < 0) )
      t = write('-');
  return write_number_internal( value, ESS_STREAM_WRITER_FORMAT_DEC) + t;
}

size_t ess_stream_writer::write(unsigned int value, ess_stream_format_t base){
  return write_number_internal((unsigned long) value, base);
}

size_t ess_stream_writer::write(long value, ess_stream_format_t base){
  int t = 0;
  if(base == ESS_STREAM_WRITER_FORMAT_DEC &&  (value < 0) )
      t = write('-');
  return write_number_internal(value, ESS_STREAM_WRITER_FORMAT_DEC) + t;
}

size_t ess_stream_writer::write(unsigned long value, ess_stream_format_t base){
  return write_number_internal((unsigned long) value, base);
}

size_t ess_stream_writer::write(double value, int d) {
  return write_ieee_internal(value, d);
}

size_t ess_stream_writer::write_ln() {
  return m_refStream.write("\r\n", 0, strlen("\r\n"));
}


size_t ess_stream_writer::write_number_internal(unsigned long value, ess_stream_format_t _base){
  char buf[8 * sizeof(long) + 1];
  char *str = &buf[sizeof(buf) - 1]; *str = '\0';
  int base = 10;

  switch (_base) {
    case ESS_STREAM_WRITER_FORMAT_DEC: break;
    case ESS_STREAM_WRITER_FORMAT_BIN: base = 2; break;
    case ESS_STREAM_WRITER_FORMAT_HEX: base = 16; break;
    default: base = 10;
  }

  do {
    unsigned long m = value;
     value /= base;
     char c = m - base * value;
      *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(value);
    return m_refStream.write(str, 0, strlen(str));
}
size_t ess_stream_writer::write_ieee_internal(double value, int d) {
  size_t n = 0;

    if(isnan(value))  return m_refStream.write("NaN", 0, 3 );
    if(isinf(value))  return m_refStream.write("INF", 0, 3);
    if(value > 4294967040.0)   return m_refStream.write("OvF", 0, 3);
    if(value < -4294967040.0) return m_refStream.write("UnF", 0, 3);


    if(value < 0.0) {
        n += m_refStream.write("-", 0, 1);
        value = -value;
    }

    unsigned long first = (unsigned long) value;
    double d_n = value - (double) first;

    n += write_number_internal(first, ESS_STREAM_WRITER_FORMAT_DEC);

    if(d > 0)  n +=m_refStream.write(".", 0, 1);

    while(d-- > 0) {
        d_n *= 10.0;
        int t_p = int(d_n);
        n += write_number_internal(t_p, ESS_STREAM_WRITER_FORMAT_DEC);
        d_n -= t_p;
    }

    return n;
}

#endif
