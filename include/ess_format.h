/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation either version 3 of the License or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
/**
 * @file ess_format.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief Contains all ess format  functions and all formats
 * It contains all functions used to work with formats
 *
 *
 */
#ifndef __ESS_FORMAT_H__
#define __ESS_FORMAT_H__


/**
 * @brief Audio Format list
 */
typedef enum ess_format {
   ESS_FORMAT_MONO_44100_8 =                             0 , /**< samplerate 44100   8 Bit Mono */
   ESS_FORMAT_MONO_44100_16 =                            1 , /**< samplerate 44100 16 Bit Mono */
   ESS_FORMAT_MONO_44100_32 =                          2 , /**< samplerate 44100 32 Bit Mono */
   ESS_FORMAT_MONO_48000_8   =                          3 , /**< samplerate 48000   8 Bit Mono */
   ESS_FORMAT_MONO_48000_16 =                          4 , /**< samplerate 48000 16 Bit Mono */
   ESS_FORMAT_MONO_48000_32 =                          5 , /**< samplerate 48000 32 Bit Mono */
   ESS_FORMAT_MONO_96000_8  =                           6 , /**< samplerate 96000   8 Bit Mono */
   ESS_FORMAT_MONO_96000_16 =                          7, /**< samplerate 96000 16 Bit Mono */
   ESS_FORMAT_MONO_96000_32 =                          8, /**< samplerate 96000 32 Bit Mono */
   ESS_FORMAT_STEREO_44100_8 =                          9 , /**< samplerate 44100   8 Bit Stereo */
   ESS_FORMAT_STEREO_44100_16 =                      10 , /**< samplerate 44100 16 Bit Stereo */
   ESS_FORMAT_STEREO_44100_32 =                      11 , /**< samplerate 44100 32 Bit Stereo */
   ESS_FORMAT_STEREO_48000_8 =                        12 , /**< samplerate 48000   8 Bit Stereo */
   ESS_FORMAT_STEREO_48000_16 =                      13 , /**< samplerate 48000 16 Bit Stereo */
   ESS_FORMAT_STEREO_48000_32 =              14, /**< samplerate 96000 32 Bit Stereo */
   ESS_FORMAT_STEREO_96000_8  =               15, /**< samplerate 96000   8 Bit Stereo */
   ESS_FORMAT_STEREO_96000_16 =              16, /**< samplerate 96000 16 Bit Stereo */
   ESS_FORMAT_STEREO_96000_32 =              17, /**< samplerate 96000 32 Bit Stereo */

   ESS_FORMAT_MAX  = 18,
} ess_format_t;

/**
 * @brief Help to get the number of channels of the format.
 * @param [in] format The format to parse
 * @return channels of the format
 */
int ess_format_get_channels(const ess_format_t format);
/**
 * @brief Help to get the samplerate of the format.
 * @param [in] format The format to parse
 * @return samplerate of the format
 */
int ess_format_get_samplerate(const ess_format_t format);
/**
 * @brief Help to get bits of the format.
 * @param [in] format The format to parse
 * @return bits of the format
 */
int ess_format_get_bits(const ess_format_t format) ;
/**
 * @brief Help to get the string of the format.
 * @param [in] format The format to parse
 * @return string  of the format
 */
const char* ess_format_to_string(const ess_format_t format);

/**
 * @brief Help to get the sample size of the format.
 * @param format The format to parse
 * @return samplesize of the format
 */
int ess_format_get_sample_size(const ess_format_t format);

ess_format_t ess_format_parse(const unsigned char bits,
                                                   const unsigned char samplerate,
                                                   const unsigned char channels);
#endif
