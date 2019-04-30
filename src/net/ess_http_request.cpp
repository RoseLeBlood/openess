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

#include "config.h"
#if ESS_CONFIG_HTTP_REQUEST_SERVER == ESS_ON

#include "net/ess_http_request.h"


uint16_t  __find_fgjdhykd_func(char* request, uint16_t pos) {
  while (request[pos] != '\0' && request[pos] != ' ' && request[pos] != '\n' && request[pos] != '\r') {
    pos++;
  }
  return pos;
}

ess_http_request_func_t ess_http_request_parse_fun(char* request, uint16_t *position)  {
  if (request[0] == 'G' && request[1] == 'E' && request[2] == 'T' && request[3] == ' ') {
      *position = 4; return ESS_HTTP_GET_REQUEST;
  } else if (request[0] == 'P' && request[1] == 'O' && request[2] == 'S' && request[3] == 'T' && request[4] == ' ') {
      *position = 5;  return ESS_HTTP_POST_REQUEST;
  } else if (request[0] == 'P' && request[1] == 'U' && request[2] == 'T' && request[3] == ' ') {
       *position = 4; return  ESS_HTTP_PUT_REQUEST;
  }
  *position = 0;
  return ESS_HTTP_ERROR_REQUEST;
}

void ess_http_request::parse(char* request) {
  uint16_t position = 0;
  // parse functions
  func = ess_http_request_parse_fun(request, &position);
  if(func == ESS_HTTP_ERROR_REQUEST) return ;
  char *uri = &request[position];
  path = uri;

  position = __find_fgjdhykd_func( &request[position],  position);
  if (request[position] == '\0') {
    func = ESS_HTTP_ERROR_REQUEST;
    return ;
  }
  request[position] = '\0';


  parse_args (uri);

  position++;

  position = __find_fgjdhykd_func( &request[position],  position);

  if (request[position] == '\0')  return ;
  request[position] = '\0';

  position++;
  if (request[position + 1] == '\r' || request[position + 1] == '\n') { position++; }
  position++;

  if (request[position] == '\0')  return ;

  parse_headers (&request[position]);
}


void ess_http_request::parse_args (char* uri) {
  uint16_t position = 0;
  // figure out where the params start
  while (uri[position] != '\0' && uri[position] != '?') {
    position++;
  }

  if (uri[position] == '?') {
    uri[position] = '\0';
    position++;
    if (uri[position] == '\0')  return;
  } else {
    return;
  }

  // assign the first parameter and move forward
  args[0] = &uri[position];

  for(int pos = position;  uri[position] != '\0' ||
                                      args_size <  ESS_CONFIG_HTTP_REQUEST_MAX_ARGS;
                                      pos++, args_size++) {
    if (uri[pos] == '&') {
        uri[pos] = '\0';
      args[args_size] = &uri[pos + 1];
      if (uri[pos + 1] == '\0') {
        break;
      }
    }
  }
}


void ess_http_request::parse_headers (char* request) {
  if (request[0] == '\0')  return;
  headers[0] = request;

  for(uint16_t position = 0; request[position] != '\0';  position++ ) {
    if (request[position] == '\n' || request[position] == '\r') {
        request[position] = '\0';
        position++;

        if (request[position] == '\r' || request[position] == '\n')  position++;

        if (request[position] != '\0') {
          headers[header_size] = &request[position];
          header_size++;
        }
    }
    if (request[position] == '\0') {
      break;
    }
  }
}

#endif
