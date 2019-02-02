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
 * @file format.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief Embedded Sound Server Audio format list
 *
 */
#ifndef __ESS_FORMAT_H__
#define __ESS_FORMAT_H__

/**
 * @brief Audio Format list
 */
typedef enum ess_format {
  ESS_FORMAT_MONO_44100_8,                   /**< samplerate 44100   8 Bit Mono */
  ESS_FORMAT_MONO_44100_16,                 /**< samplerate 44100 16 Bit Mono */
  ESS_FORMAT_MONO_44100_24,                 /**< samplerate 44100 24 Bit Mono */
  ESS_FORMAT_MONO_48000_8,                   /**< samplerate 48000   8 Bit Mono */
  ESS_FORMAT_MONO_48000_16,                 /**< samplerate 48000 16 Bit Mono */
  ESS_FORMAT_MONO_48000_24,                 /**< samplerate 48000 24 Bit Mono */
  ESS_FORMAT_MONO_96000_8,                   /**< samplerate 96000   8 Bit Mono */
  ESS_FORMAT_MONO_96000_16,                 /**< samplerate 96000 16 Bit Mono */
  ESS_FORMAT_MONO_96000_24,                 /**< samplerate 96000 24 Bit Mono */
  ESS_FORMAT_STEREO_44100_8,                 /**< samplerate 44100   8 Bit Stereo */
  ESS_FORMAT_STEREO_44100_16,               /**< samplerate 44100 16 Bit Stereo */
  ESS_FORMAT_STEREO_44100_24,               /**< samplerate 44100 24 Bit Stereo */
  ESS_FORMAT_STEREO_48000_8,                 /**< samplerate 48000   8 Bit Stereo */
  ESS_FORMAT_STEREO_48000_16,               /**< samplerate 48000 16 Bit Stereo */
  ESS_FORMAT_STEREO_48000_24,               /**< samplerate 96000 24 Bit Stereo */
  ESS_FORMAT_STEREO_96000_8,                 /**< samplerate 96000   8 Bit Stereo */
  ESS_FORMAT_STEREO_96000_16,               /**< samplerate 96000 16 Bit Stereo */
  ESS_FORMAT_STEREO_96000_24                /**< samplerate 96000 24 Bit Stereo */
}ess_format_t;

/**
 * @brief Help to get the number of channels of the format.
 * @param format The format to parse
 */
int ess_format_get_channels(ess_format_t format);
/**
 * @brief Help to get the samplerate of the format.
 * @param format The format to parse
 */
int ess_format_get_samplerate(ess_format_t format);
/**
 * @brief Help to get bits of the format.
 * @param format The format to parse
 */
int ess_format_get_bits(ess_format_t format);
/**
 * @brief Help to get the string of the format.
 * @param format The format to parse
 */
const char* ess_format_to_string(ess_format_t format);


#endif
