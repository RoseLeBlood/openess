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
 * @file ess_stream_writer.h
 * @author Anna Sopdia Schröck
 * @date 19 Mai 2019
 *
 */
#ifndef _ESS_STREAM_WRITER_H_
#define _ESS_STREAM_WRITER_H_

#include "ess_stream.h"

typedef enum ess_stream_format {
  ESS_STREAM_WRITER_FORMAT_DEC,
  ESS_STREAM_WRITER_FORMAT_BIN,
  ESS_STREAM_WRITER_FORMAT_HEX,
}ess_stream_format_t;

class ess_stream_writer : public ess_object {
protected:
  ess_stream_writer(ess_stream& stream)
    : ess_object("ess_stream_writer"),  m_refStream(stream) { }
  ess_stream_writer(ess_stream& stream, std::string name)
    : ess_object(name),  m_refStream(stream) { }
public:
    virtual size_t write(const char * format, ...)  __attribute__ ((format (printf, 2, 3)));
    virtual size_t write(const std::string & str);
    virtual size_t write(const char* str);
    virtual size_t write(char c);

    virtual size_t write(unsigned char);
    virtual size_t write(int value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC);
    virtual size_t write(unsigned int value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC);
    virtual size_t write(long value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC);
    virtual size_t write(unsigned long value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC);
    virtual size_t write(double value, int d = 2);

    virtual size_t write_ln(const std::string & str) {
        return write(str) + write_ln();
    }
    virtual size_t write_ln(const char* str){
        return write(std::string(str) ) + write_ln();
    }
    virtual size_t write_ln(char c) {
        return write(c) + write_ln();
    }

    virtual size_t write_ln(unsigned char c) {
      return write(c) + write_ln();
    }
    virtual size_t write_ln(int value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC) {
      return write(value, base) + write_ln();
    }
    virtual size_t write_ln(unsigned int value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC) {
      return write(value, base) + write_ln();
    }
    virtual size_t write_ln(long value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC) {
      return write(value, base) + write_ln();
    }
    virtual size_t write_ln(unsigned long value, ess_stream_format_t base = ESS_STREAM_WRITER_FORMAT_DEC) {
      return write(value, base) + write_ln();
    }
    virtual size_t write_ln(double value, int d = 2) {
      return write(value, d) + write_ln();
    }
    virtual size_t write_ln();
protected:
  virtual size_t write_number_internal(unsigned long value, ess_stream_format_t base);
  virtual size_t write_ieee_internal(double value, int d = 2);
protected:
  ess_stream& m_refStream;
};

#endif
