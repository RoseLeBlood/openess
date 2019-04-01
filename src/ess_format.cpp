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
 * @file ess_format.cpp
 * @author Anna Sopdia Schröck
 * @date 30 Januar 2019
 * @brief ESS format source
 *
 */

#include "ess_format.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct _format2human {
  char string[32];
  int samplerate;
  int bits;
  int channels;
  ess_format_t format;
}format2human_t;

format2human_t format_parse[] = {
  { "ESS_FORMAT_MONO_44100_8", 44100, 8, 1, ESS_FORMAT_MONO_44100_8 },
  { "ESS_FORMAT_MONO_44100_16", 44100, 16, 1, ESS_FORMAT_MONO_44100_16 },
  { "ESS_FORMAT_MONO_44100_32", 44100, 32, 1, ESS_FORMAT_MONO_44100_32 },
  { "ESS_FORMAT_MONO_48000_8", 48000, 8, 1, ESS_FORMAT_MONO_48000_8 },
  { "ESS_FORMAT_MONO_48000_16", 48000, 16, 1, ESS_FORMAT_MONO_48000_16 },
  { "ESS_FORMAT_MONO_48000_32", 48000, 32, 1, ESS_FORMAT_MONO_48000_32 },
  { "ESS_FORMAT_MONO_96000_8", 96000, 8, 1, ESS_FORMAT_MONO_96000_8 },
  { "ESS_FORMAT_MONO_96000_16", 96000, 16, 1, ESS_FORMAT_MONO_96000_16 },
  { "ESS_FORMAT_MONO_96000_32", 96000, 32, 1, ESS_FORMAT_MONO_96000_32 },

  { "ESS_FORMAT_STEREO_44100_8", 44100, 8, 2, ESS_FORMAT_STEREO_44100_8 },
  { "ESS_FORMAT_STEREO_44100_16", 44100, 16, 2, ESS_FORMAT_STEREO_44100_16 },
  { "ESS_FORMAT_STEREO_44100_32", 44100, 32, 2, ESS_FORMAT_STEREO_44100_32 },
  { "ESS_FORMAT_STEREO_48000_8", 48000, 8, 2, ESS_FORMAT_STEREO_48000_8 },
  { "ESS_FORMAT_STEREO_48000_16", 48000, 16, 2, ESS_FORMAT_STEREO_48000_16 },
  { "ESS_FORMAT_STEREO_48000_32", 48000, 32, 2, ESS_FORMAT_STEREO_48000_32 },
  { "ESS_FORMAT_STEREO_96000_8", 96000, 8, 2, ESS_FORMAT_STEREO_96000_8 },
  { "ESS_FORMAT_STEREO_96000_16", 96000, 16, 2, ESS_FORMAT_STEREO_96000_16 },
  { "ESS_FORMAT_STEREO_96000_32", 96000, 32, 2, ESS_FORMAT_STEREO_96000_32 },

  { "ESS_FORMAT_2POINT1_44100_8", 44100, 8, 3, ESS_FORMAT_2POINT1_44100_8 },
  { "ESS_FORMAT_2POINT1_44100_16", 44100, 16, 3, ESS_FORMAT_2POINT1_44100_16 },
  { "ESS_FORMAT_2POINT1_44100_32", 44100, 32, 3, ESS_FORMAT_2POINT1_44100_32 },
  { "ESS_FORMAT_2POINT1_48000_8", 48000, 8, 3, ESS_FORMAT_2POINT1_48000_8 },
  { "ESS_FORMAT_2POINT1_48000_16", 48000, 16, 3, ESS_FORMAT_2POINT1_48000_16 },
  { "ESS_FORMAT_2POINT1_48000_32", 48000, 32, 3, ESS_FORMAT_2POINT1_48000_32 },
  { "ESS_FORMAT_2POINT1_96000_8", 96000, 8, 3, ESS_FORMAT_2POINT1_96000_8 },
  { "ESS_FORMAT_2POINT1_96000_16", 96000, 16, 3, ESS_FORMAT_2POINT1_96000_16 },
  { "ESS_FORMAT_2POINT1_96000_32", 96000, 32, 3, ESS_FORMAT_2POINT1_96000_32 },

  { "ESS_FORMAT_QUAD_44100_8", 44100, 8, 4, ESS_FORMAT_QUAD_44100_8 },
  { "ESS_FORMAT_QUAD_44100_16", 44100, 16,  4, ESS_FORMAT_QUAD_44100_16},
  { "ESS_FORMAT_QUAD_44100_32", 44100, 32, 4, ESS_FORMAT_QUAD_44100_32 },
  { "ESS_FORMAT_QUAD_48000_8", 48000, 8, 4, ESS_FORMAT_QUAD_48000_8 },
  { "ESS_FORMAT_QUAD_48000_16", 48000, 16, 4, ESS_FORMAT_QUAD_48000_16 },
  { "ESS_FORMAT_QUAD_48000_32", 48000, 32, 4, ESS_FORMAT_QUAD_48000_32 },
  { "ESS_FORMAT_QUAD_96000_8", 96000, 8, 4, ESS_FORMAT_QUAD_96000_8 },
  { "ESS_FORMAT_QUAD_96000_16", 96000, 16, 4, ESS_FORMAT_QUAD_96000_16 },
  { "ESS_FORMAT_QUAD_96000_32", 96000, 32, 4, ESS_FORMAT_QUAD_96000_32 },

  { "ESS_FORMAT_5POINT1_44100_8", 44100, 8, 6, ESS_FORMAT_5POINT1_44100_8 },
  { "ESS_FORMAT_5POINT1_44100_16", 44100, 16, 6,ESS_FORMAT_5POINT1_44100_16 },
  { "ESS_FORMAT_5POINT1_44100_32", 44100, 32, 6, ESS_FORMAT_5POINT1_44100_32 },
  { "ESS_FORMAT_5POINT1_48000_8", 48000, 8, 6, ESS_FORMAT_5POINT1_48000_8 },
  { "ESS_FORMAT_5POINT1_48000_16", 48000, 16, 6,ESS_FORMAT_5POINT1_48000_16 },
  { "ESS_FORMAT_5POINT1_48000_32", 48000, 32, 6, ESS_FORMAT_5POINT1_48000_32 },
  { "ESS_FORMAT_5POINT1_96000_8", 96000, 8, 6, ESS_FORMAT_5POINT1_96000_8 },
  { "ESS_FORMAT_5POINT1_96000_16", 96000, 16, 6, ESS_FORMAT_5POINT1_96000_16 },
  { "ESS_FORMAT_5POINT1_96000_32", 96000, 32, 6, ESS_FORMAT_5POINT1_96000_32 },

  { "ESS_FORMAT_7POINT1_44100_8", 44100, 8, 8, ESS_FORMAT_7POINT1_44100_8 },
  { "ESS_FORMAT_7POINT1_44100_16", 44100, 16, 8, ESS_FORMAT_7POINT1_44100_16 },
  { "ESS_FORMAT_7POINT1_44100_32", 44100, 32, 8, ESS_FORMAT_7POINT1_44100_32 },
  { "ESS_FORMAT_7POINT1_48000_8", 48000, 8, 8, ESS_FORMAT_7POINT1_48000_8 },
  { "ESS_FORMAT_7POINT1_48000_16", 48000, 16, 8, ESS_FORMAT_7POINT1_48000_16 },
  { "ESS_FORMAT_7POINT1_48000_32", 48000, 32, 8, ESS_FORMAT_7POINT1_48000_32 },
  { "ESS_FORMAT_7POINT1_96000_8", 96000, 8, 8, ESS_FORMAT_7POINT1_96000_8 },
  { "ESS_FORMAT_7POINT1_96000_16", 96000, 16, 8, ESS_FORMAT_7POINT1_96000_16 },
  { "ESS_FORMAT_7POINT1_96000_32", 96000, 32, 8, ESS_FORMAT_7POINT1_96000_32 },
};

int ess_format_get_channels(const ess_format_t format) {
  if(format >= ESS_FORMAT_INVALID) return -1;
    return format_parse[format].channels;
}
int ess_format_get_samplerate(const ess_format_t format) {
  if(format >= ESS_FORMAT_INVALID) return -1;
  return format_parse[format].samplerate;
}

int ess_format_get_bits(const ess_format_t format) {
  if(format >= ESS_FORMAT_INVALID) return -1;
  return format_parse[format].bits;
}

const char* ess_format_to_string(ess_format_t format) {
  if(format >= ESS_FORMAT_INVALID) return "ESS_FORMAT_INVALID";
  return format_parse[format].string;
}
ess_format_t ess_format_from_string(const char* format) {
  for(int8_t i = 0; i < ESS_FORMAT_INVALID; i++) {
    if( strcmp(format_parse[i].string, format) == 0 )
      return format_parse[i].format;
  }
  return ESS_FORMAT_INVALID;
}
ess_format_t ess_format_parse(const unsigned char bits,
                                                   const unsigned int samplerate,
                                                   const unsigned char channels) {
  ess_format_t ret = ESS_FORMAT_INVALID;

  switch(channels) {
    case 1:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_MONO_44100_8; break;
            case 48000: ret = ESS_FORMAT_MONO_48000_8; break;
            case 96000: ret = ESS_FORMAT_MONO_96000_8; break;
          }; //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_MONO_44100_16; break;
            case 48000: ret = ESS_FORMAT_MONO_48000_16; break;
            case 96000: ret = ESS_FORMAT_MONO_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_MONO_44100_32; break;
          case 48000: ret = ESS_FORMAT_MONO_48000_32; break;
          case 96000: ret = ESS_FORMAT_MONO_96000_32; break;
        };  //switch(samplerate)
        break;
      };  // switch(bits)
      break;

    case 2:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_STEREO_44100_8; break;
            case 48000: ret = ESS_FORMAT_STEREO_48000_8; break;
            case 96000: ret = ESS_FORMAT_STEREO_96000_8; break;
          };  //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_STEREO_44100_16; break;
            case 48000: ret = ESS_FORMAT_STEREO_48000_16; break;
            case 96000: ret = ESS_FORMAT_STEREO_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_STEREO_44100_32; break;
          case 48000: ret = ESS_FORMAT_STEREO_48000_32; break;
          case 96000: ret = ESS_FORMAT_STEREO_96000_32; break;
        };  //switch(samplerate)
        break;
      };  // switch(bits)
      break;

    case 3:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_2POINT1_44100_8; break;
            case 48000: ret = ESS_FORMAT_2POINT1_48000_8; break;
            case 96000: ret = ESS_FORMAT_2POINT1_96000_8; break;
          };  //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_2POINT1_44100_16; break;
            case 48000: ret = ESS_FORMAT_2POINT1_48000_16; break;
            case 96000: ret = ESS_FORMAT_2POINT1_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_2POINT1_44100_32; break;
          case 48000: ret = ESS_FORMAT_2POINT1_48000_32; break;
          case 96000: ret = ESS_FORMAT_2POINT1_96000_32; break;
        };  //switch(samplerate)
        break;
      };  // switch(bits)
      break;

    case 4:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_QUAD_44100_8; break;
            case 48000: ret = ESS_FORMAT_QUAD_48000_8; break;
            case 96000: ret = ESS_FORMAT_QUAD_96000_8; break;
          };  //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_QUAD_44100_16; break;
            case 48000: ret = ESS_FORMAT_QUAD_48000_16; break;
            case 96000: ret = ESS_FORMAT_QUAD_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_QUAD_44100_32; break;
          case 48000: ret = ESS_FORMAT_QUAD_48000_32; break;
          case 96000: ret = ESS_FORMAT_QUAD_96000_32; break;
        };  //switch(samplerate)
        break;
      };  // switch(bits)
      break;

    case 6:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_5POINT1_44100_8; break;
            case 48000: ret = ESS_FORMAT_5POINT1_48000_8; break;
            case 96000: ret = ESS_FORMAT_5POINT1_96000_8; break;
          };  //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_5POINT1_44100_16; break;
            case 48000: ret = ESS_FORMAT_5POINT1_48000_16; break;
            case 96000: ret = ESS_FORMAT_5POINT1_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_5POINT1_44100_32; break;
          case 48000: ret = ESS_FORMAT_5POINT1_48000_32; break;
          case 96000: ret = ESS_FORMAT_5POINT1_96000_32; break;
        };  //switch(samplerate)
        break;
      };  // switch(bits)
      break;

    case 8:
      switch(bits) {
        case 8:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_7POINT1_44100_8; break;
            case 48000: ret = ESS_FORMAT_7POINT1_48000_8; break;
            case 96000: ret = ESS_FORMAT_7POINT1_96000_8; break;
          };  //switch(samplerate)
          break;
        case 16:
          switch(samplerate) {
            case 44100: ret = ESS_FORMAT_7POINT1_44100_16; break;
            case 48000: ret = ESS_FORMAT_7POINT1_48000_16; break;
            case 96000: ret = ESS_FORMAT_7POINT1_96000_16; break;
          };  //switch(samplerate)
          break;
        case 32:
        switch(samplerate) {
          case 44100: ret = ESS_FORMAT_7POINT1_44100_32; break;
          case 48000: ret = ESS_FORMAT_7POINT1_48000_32; break;
          case 96000: ret = ESS_FORMAT_7POINT1_96000_32; break;
        };  //switch(samplerate)
        break;
      }; // switch(bits)
      break;
  }; //switch(channels)

  return ret;
}
