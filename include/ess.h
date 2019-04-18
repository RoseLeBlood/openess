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
 * @file ess.h
 * @author Anna Sopdia Schröck
 * @date 2 Februar 2019
 * @brief the basic OpenESS header file
 */
#ifndef _ESS_MAIN_HEADER_H_
#define _ESS_MAIN_HEADER_H_

#define OPEN_ESS_VERSION_0_5  5 // backends, platform
#define OPEN_ESS_VERSION_1_0 10 // TODO: Future Plan - server, backends, platforms referen imp ready
#define OPEN_ESS_VERSION_1_1 11  // TODO: Future Plan 11 - all platforms ready  -- MT Safe
#define OPEN_ESS_VERSION_2_0  20 // TODO: Future Future Plan 2 - ??

#define OPEN_ESS_VERSION OPEN_ESS_VERSION_0_5

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/signal.h>

#include <iostream>

#include "ess_object.h"
#include "ess_format.h"
#include "ess_error.h"
#include "ess_protocol.h"
#include "platform/ess_sleep.h"
#include "platform/ess_memory.h"

/**
* @brief which output module to create the platform factory
**/
typedef enum  ess_output_type {
  ESS_OUTPUT_NULL, /**< platform factory create  `ess_null_output_module` (platform; all)*/
  ESS_OUTPUT_UART, /**< platform factory create  a uart output (platform: esp32, rapi) */
  ESS_OUTPUT_I2S, /**< platform factory create  a i2s output (platform: esp32, rapi) */
  ESS_OUTPUT_UDP, /**< platform factory create  a UDPLite output (platform: all) */
  ESS_OUTPUT_TCP, /**< platform factory create  a TCP output (platform: all) */
  ESS_OUTPUT_OPENAL, /**< platform factory create  a OPENAL output (platform: Linux, raPI) */
  ESS_OUTPUT_WASAPI,  /**< platform factory create  a WASAPI output (platform: windows) */
  ESS_OUTPUT_ASIO, /**< platform factory create  a ASIO output (platform: windows) */
  ESS_OUTPUT_JACKD, /**< platform factory create  a jackD2 output (platform: jackd platforms) */
  ESS_OUTPUT_WAV_WRITTER, /**< platform factory create  a WAV writter output (platform: all) */
  ESS_OUTPUT_USER, /**< user platform implatations (ESS_OUTPUT_USER+1 ..)    (platform: all) */
}ess_output_t;

/**
* @brief the channel system id using in `ess_channel` `ess_module`
**/
typedef enum ess_audio_channel {
  ESS_AUDIO_CHANNEL_LEFT = 0,  /**< channel id for left*/
  ESS_AUDIO_CHANNEL_RIGHT, /**< channel id for right*/
  ESS_AUDIO_CHANNEL_REAR_LEFT, /**< channel id for rear left*/
  ESS_AUDIO_CHANNEL_REAR_RIGHT, /**< channel id for rear right*/
  ESS_AUDIO_CHANNEL_BACK_LEFT, /**< channel id for back left*/
  ESS_AUDIO_CHANNEL_BACK_RIGTH, /**< channel id for back right*/
  ESS_AUDIO_CHANNEL_CENTER, /**< channel id for center*/
  ESS_AUDIO_CHANNEL_LFE, /**< channel id for LFE*/
  ESS_AUDIO_CHANNEL_MAX,
}ess_audio_channel_t;

typedef enum  ess_audio_channel_format {
  ESS_CHANNEL_FORMAT_MON0 = 1,
  ESS_CHANNEL_FORMAT_STEREO = 2,
  ESS_CHANNEL_FORMAT_2POINT1 = 3,
  ESS_CHANNEL_FORMAT_QUAD = 4,
  ESS_CHANNEL_FORMAT_5POINT1 = 6,
  ESS_CHANNEL_FORMAT_7POINT1 = 8,
}ess_audio_channel_format_t;

/**
* @brief type of the `ess_channel`
**/
typedef enum ess_channel_type {
  ESS_CHANNEL_INPUT,
  ESS_CHANNEL_OUTPUT,
  ESS_CHANNEL_MAX
}ess_channel_t;

typedef struct ess_audioblock {
  uint8_t  ref_count;
  uint16_t memory_pool_index;
  float    data[ESS_DEFAULT_AUDIO_PACKET_SIZE];
  ess_format_t format;
} ess_audioblock_t;


/**
* @brief system format helper
**/
class ess_system_format {
public:
  /**
  * @brief get the system format bits
  **/
  static unsigned char get_bits() { return ess_format_get_bits(ESS_DEFAULT_SERVER_FORMAT); }
  /**
  * @brief get the system format samplerate
  **/
  static unsigned char get_samplerate() { return ess_format_get_samplerate(ESS_DEFAULT_SERVER_FORMAT); }
  /**
  * @brief get the system format channels
  **/
  static unsigned char channels() { return ess_format_get_channels(ESS_DEFAULT_SERVER_FORMAT); }
};



#if  ESS_PLATFORM_ESP32 == 1
extern "C" void app_main()  ;
#endif

#endif
