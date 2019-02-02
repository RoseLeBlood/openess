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
 * @file format.c
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief ESS format source
 *
 */

#include "format.h"
#include <stdio.h>

int ess_format_get_channels(ess_format_t format) {
  switch(format) {
      case ESS_FORMAT_MONO_44100_8:
      case ESS_FORMAT_MONO_44100_16:
      case ESS_FORMAT_MONO_44100_24:
      case ESS_FORMAT_MONO_48000_8:
      case ESS_FORMAT_MONO_48000_16:
      case ESS_FORMAT_MONO_48000_24:
      case ESS_FORMAT_MONO_96000_8:
      case ESS_FORMAT_MONO_96000_16:
      case ESS_FORMAT_MONO_96000_24:
        return 1;
      case ESS_FORMAT_STEREO_44100_8:
      case ESS_FORMAT_STEREO_44100_16:
      case ESS_FORMAT_STEREO_44100_24:
      case ESS_FORMAT_STEREO_48000_8:
      case ESS_FORMAT_STEREO_48000_16:
      case ESS_FORMAT_STEREO_48000_24:
      case ESS_FORMAT_STEREO_96000_8:
      case ESS_FORMAT_STEREO_96000_16:
      case ESS_FORMAT_STEREO_96000_24:
        return 2;
  };
  return -1;
}
int ess_format_get_samplerate(ess_format_t format) {
  switch(format) {
     case ESS_FORMAT_MONO_44100_8:
     case ESS_FORMAT_MONO_44100_16:
     case ESS_FORMAT_MONO_44100_24:
      return 44100;
     case ESS_FORMAT_MONO_48000_8:
     case ESS_FORMAT_MONO_48000_16:
     case ESS_FORMAT_MONO_48000_24:
      return 48000;
     case ESS_FORMAT_MONO_96000_8:
     case ESS_FORMAT_MONO_96000_16:
     case ESS_FORMAT_MONO_96000_24:
       return 96000;
     case ESS_FORMAT_STEREO_44100_8:
     case ESS_FORMAT_STEREO_44100_16:
     case ESS_FORMAT_STEREO_44100_24:
      return 44100;
     case ESS_FORMAT_STEREO_48000_8:
     case ESS_FORMAT_STEREO_48000_16:
     case ESS_FORMAT_STEREO_48000_24:
      return 48000;
     case ESS_FORMAT_STEREO_96000_8:
     case ESS_FORMAT_STEREO_96000_16:
     case ESS_FORMAT_STEREO_96000_24:
       return 96000;
  };
  return -1;
  }

int ess_format_get_bits(ess_format_t format) {
  switch(format) {
      case ESS_FORMAT_MONO_44100_8:
      case ESS_FORMAT_MONO_48000_8:
      case ESS_FORMAT_MONO_96000_8:
      case ESS_FORMAT_STEREO_44100_8:
      case ESS_FORMAT_STEREO_48000_8:
      case ESS_FORMAT_STEREO_96000_8:
        return 8;
      case ESS_FORMAT_MONO_48000_16:
      case ESS_FORMAT_MONO_44100_16:
      case ESS_FORMAT_MONO_96000_16:
      case ESS_FORMAT_STEREO_44100_16:
      case ESS_FORMAT_STEREO_48000_16:
      case ESS_FORMAT_STEREO_96000_16:
        return 16;
      case ESS_FORMAT_MONO_44100_24:
      case ESS_FORMAT_MONO_48000_24:
      case ESS_FORMAT_MONO_96000_24:
      case ESS_FORMAT_STEREO_44100_24:
      case ESS_FORMAT_STEREO_48000_24:
      case ESS_FORMAT_STEREO_96000_24:
        return 24;
  };
  return -1;
}
char __g_format_buffer[32];
const char* ess_format_to_string(ess_format_t format) {

  sprintf(__g_format_buffer, "%d:%d:%d", ess_format_get_samplerate(format),
                                                                      ess_format_get_bits(format),
                                                                      ess_format_get_channels(format) );
  return __g_format_buffer;
}
