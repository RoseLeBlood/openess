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

#include "ess_format.h"
#include <stdio.h>

typedef struct _format2human {
  char string[32];
  int samplerate;
  int bits;
  int channels;
}format2human_t;

format2human_t format_parse[] = {
  {  "ESS_FORMAT_MONO_44100_8", 44100, 8, 1 },
  {  "ESS_FORMAT_MONO_48000_8", 48000, 8, 1 },
  {  "ESS_FORMAT_MONO_96000_8", 96000, 8, 1 },
  {  "ESS_FORMAT_STEREO_44100_8", 44100, 8, 2 },
  {  "ESS_FORMAT_STEREO_48000_8", 48000, 8, 2 },
  {  "ESS_FORMAT_STEREO_96000_8", 96000, 8, 2 },
  {  "ESS_FORMAT_MONO_48000_16", 48000, 16, 1 },
  {  "ESS_FORMAT_MONO_44100_16", 44100, 16, 1 },
  {  "ESS_FORMAT_MONO_96000_16", 96000, 16, 1 },
  {   "ESS_FORMAT_STEREO_44100_16", 44100, 16, 2 },
  {  "ESS_FORMAT_STEREO_48000_16", 48000, 16, 2 },
  {  "ESS_FORMAT_STEREO_96000_16", 96000, 16, 2 },
  {   "ESS_FORMAT_MONO_44100_24", 44100, 24, 1 },
  {   "ESS_FORMAT_MONO_48000_24", 48000, 24, 1 },
  {   "ESS_FORMAT_MONO_96000_24", 96000, 24, 1 },
  {    "ESS_FORMAT_STEREO_44100_24", 44100, 24, 2 },
  {   "ESS_FORMAT_STEREO_48000_24", 48000, 24, 2 },
  {    "ESS_FORMAT_STEREO_96000_24", 96000, 24, 2 },
};

int ess_format_get_channels(const ess_format_t format) {
  if(format >= ESS_FORMAT_MAX) return -1;
    return format_parse[format].channels;
}
int ess_format_get_samplerate(const ess_format_t format) {
  if(format >= ESS_FORMAT_MAX) return -1;
  return format_parse[format].samplerate;
}

int ess_format_get_bits(const ess_format_t format) {
  if(format >= ESS_FORMAT_MAX) return -1;
  return format_parse[format].bits;
}




const char* ess_format_to_string(ess_format_t format) {
  if(format >= ESS_FORMAT_MAX) return "NO_FORMAT";
  return format_parse[format].string;
}
