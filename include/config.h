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
 * @file config.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief File containing configurations
 *
 */

#ifndef __ESD_CONFIG_H__
#define __ESD_CONFIG_H__


/**
 * @brief If defined compiled backend for esp32
 */
#define ESS_PLATFORM_ESP32

/**
 * @brief If defined compiled backend for Raspberry PI (linux)
 */
//#define ESS_PLATFORM_RPI
/**
 * @brief If defined compiled backend for generic linux (openal)
 */
//#define ESS_PLATFORM_LINUX
/**
 * @brief If defined compiled backend for  generic windows (openal, wasapi)
 */
//#define ESS_PLATFORM_WINDOWS


/**
 * @brief If defined then UART backend available
 * Only avaible on platform : `ESS_PLATFORM_ESP32` and `ESS_PLATFORM_RPI`
 */
#define ESS_ENABLE_BACKEND_UART
/**
 * @brief If defined then UDP backend available
 */
#define ESS_ENABLE_BACKEND_UDP
/**
 * @brief If defined then I2S backend available
 * Only avaible on platform : `ESS_PLATFORM_ESP32` and `ESS_PLATFORM_RPI`
 */
#define ESS_ENABLE_BACKEND_I2S

#ifdef ESS_ENABLE_BACKEND_UART
	#define ESS_BACKEND_UART_BAUDRAT 115200
	#define ESS_BACKEND_UART_TXD  (GPIO_NUM_4)
	#define ESS_BACKEND_UART_RXD  (GPIO_NUM_5)
	#define ESS_BACKEND_UART_RTS  (UART_PIN_NO_CHANGE)
	#define ESS_BACKEND_UART_CTS  (UART_PIN_NO_CHANGE)
#endif

#ifdef ESS_ENABLE_BACKEND_UDP
	#define ESS_BACKEND_UDP_PORT 1522
	#define ESS_BACKEND_UDP_USING_IP6 1
#endif

#ifdef ESS_ENABLE_BACKEND_I2S
	#define I2S_EXTERNAL_DAC_BCK 26
	#define I2S_EXTERNAL_DAC_LRCLK 25
	#define I2S_EXTERNAL_DAC_DOUT 22
	#define  I2S_EXTERNAL_DAC_DIN   -1                                                    //Not used

  #define ESS_BACKEND_I2S_FORMAT ESS_FORMAT_STEREO_96000_16
#endif




/* size of the audio buffer */
#define ESD_BUF_SIZE (1024)
/* maximum size we can write().  Otherwise we might overflow */
#define ESD_MAX_WRITE_SIZE (6 * 512)
#define ESD_KEY_LEN (16)
#define ESD_DEFAULT_PORT (16001)
#define ESD_DEFAULT_RATE (48000)
/* maximum length of a stream/sample name */
#define ESD_NAME_MAX (128)

/* a magic number to identify the relative endianness of a client */
#define ESD_ENDIAN_KEY \
	( (unsigned int) ( ('E' << 24) + ('N' << 16) + ('D' << 8) + ('N') ) )

#define ESD_VOLUME_BASE (256)

#endif
