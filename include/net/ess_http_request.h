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
 * @file ess_http_request.h
 * @author Anna Sopdia Schröck
 * @date 28 April 2019
 */
 #ifndef __ESS_HTTP_REQUEST_H__
 #define __ESS_HTTP_REQUEST_H__

#include "ess.h"


typedef enum ess_http_request_func {
  ESS_HTTP_ERROR_REQUEST = 0x00,
  ESS_HTTP_GET_REQUEST = 0x01,
  ESS_HTTP_POST_REQUEST = 0x10,
  ESS_HTTP_PUT_REQUEST = 0x11,
} ess_http_request_func_t;

class ess_http_request {
public:
  ess_http_request( char* request) {
    parse(request); }

  std::string get_path() {
    return path; }

  std::string get_arg(uint8_t i)  {
    return i < ESS_CONFIG_HTTP_REQUEST_MAX_ARGS ? args[i]  : ""; }

  std::string get_header(uint8_t i) {
    return i < ESS_CONFIG_HTTP_REQUEST_MAX_HEADERS ? args[i]  : ""; }

  uint8_t get_arg_size() const {
    return args_size; }
  uint8_t get_header_size() const {
    return header_size; }

  ess_http_request_func_t get_function() const {
    return func;
  }
private:
  void parse( char* request);
  void parse_args ( char* uri);
  void parse_headers ( char* request);
protected:
  ess_http_request_func_t func;
  std::string path;
  std::string args[ESS_CONFIG_HTTP_REQUEST_MAX_ARGS];
  uint8_t args_size;
  std::string headers[ESS_CONFIG_HTTP_REQUEST_MAX_HEADERS];
  uint8_t header_size;
};



#endif
