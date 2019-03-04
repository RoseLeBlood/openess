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
 * @date 30 Januar 2019
 * @brief File containing configurations
 *
 */

#ifndef __ESS_CONFIG_H__
#define __ESS_CONFIG_H__


#define ESS_BUF_COUNT 3
#define ESS_BUF_SIZE      1024

#define ESS_PROTOCOL_UDP							1
#define ESS_PROTOCOL_TCP							2
#define ESS_PROTOCOL_UDP_LITE		3

#define ESS_FAMILY_IP4											4
#define ESS_FAMILY_IP6											6
#define ESS_FAMILY_BOTH 							46

/* Main config */

#define ESS_PLATFORM_ESP32					1/** @brief If defined compiled backend for esp32 */
#define ESS_PLATFORM_RPI 					 		 0/** @brief If defined compiled backend for Raspberry PI (linux) */
#define ESS_PLATFORM_LINUX   			0/** @brief If defined compiled backend for generic linux (openal) */
#define ESS_PLATFORM_WINDOWS  0/** @brief If defined compiled backend for  generic windows (openal, wasapi) */

#define ESS_DEFAULT_AUDIO_PACKET_SIZE 128

#define ESS_DEFAULT_SERVER_START_PORT 8686 // Clinet0: +1, Client1 +2 ...
#define ESS_DEFAULT_SERVER_FAMILY ESS_FAMILY_IP4
#define ESS_DEFAULT_SERVER_FORMAT ESS_FORMAT_STEREO_44100_16
#define ESS_DEFAULT_SERVER_PACKET_SIZE ESS_DEFAULT_AUDIO_PACKET_SIZE

#if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
#define ESS_DEFAULT_SERVER_HOST "0.0.0.0"
#else
#define ESS_DEFAULT_SERVER_HOST "::"
#endif


#if  ESS_PLATFORM_ESP32 == 1
	#define ESS_CONFIG_NETWORK_ESP32 /**< esp32 using own network functions */
	#define ESS_CONFIC_TASK_ESP32	/**< esp32 using own task functions */
	#define ESS_CONFIG_RINGBUFFER_ESP32 /**< esp32 using own ringbuffer functions */
	#define ESS_CONFIG_MUTEX_ESP32 /**< esp32 using own mutex functions */
	#define ESS_CONFIG_SPINLOCK_ESP32 /**< esp32 using own spinlock functions */

	#define ESS_ENABLE_BACKEND_OUT_I2S /**< esp32 platform I2S backend available */
	#define ESS_ENABLE_BACKEND_OUT_UDP/**< generic platform UDP backend available */

	#define ESS_DEFAULT_SERVER_NAME "OpenESS-esp32" /**< basic server name*/
#endif // ESS_PLATFORM_ESP32

#if ESS_PLATFORM_RPI == 1
	#define ESS_CONFIG_MUTEX_GENERIC
	#define ESS_CONFIC_TASK_GENERIC
	#define ESS_CONFIG_RINGBUFFER_GENERIC
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OUT_OPENAL
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_OUT_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenESS-rpi"
#endif //ESS_PLATFORM_RPI

#if ESS_PLATFORM_LINUX == 1
	#define ESS_CONFIC_TASK_GENERIC
	#define ESS_CONFIG_RINGBUFFER_GENERIC
	#define ESS_CONFIG_MUTEX_GENERIC
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OUT_OPENAL
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_OUT_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenESS-linux"
#endif //ESS_PLATFORM_LINUX

#if ESS_PLATFORM_WINDOWS == 1
	#define ESS_CONFIG_SEMAPHORE_WINDOWS
	#define ESS_CONFIC_TASK_WINDOWS
	#define ESS_CONFIG_RINGBUFFER_WINDOWS
	#define ESS_CONFIG_MUTEX_WINDOWS
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OUT_OPENAL
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_OUT_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenESS-windows"
#endif //ESS_PLATFORM_WINDOWS


//-------------------------------------------------------------------------------------------------------

#ifdef ESS_ENABLE_BACKEND_OUT_UDP
	#define ESS_BACKEND_UDP_SENDTO_PORT 17000
	#define ESS_BACKEND_UDP_PROTOCOL ESS_PROTOCOL_UDP_LITE

	#if ESS_DEFAULT_SERVER_FAMILY == ESS_FAMILY_IP4
	#define ESS_BACKEND_UDP_SENDTO_HOST "192.168.0.235"
	#else
	#define ESS_BACKEND_UDP_SENDTO_HOST "::2"
	#endif
#endif

#ifdef ESS_ENABLE_BACKEND_OUT_I2S
	#define I2S_EXTERNAL_DAC_BCK 26
	#define I2S_EXTERNAL_DAC_LRCLK 25
	#define I2S_EXTERNAL_DAC_DOUT 22
	#define  I2S_EXTERNAL_DAC_DIN   23

	#define ESS_BACKEND_I2S_DMA_BUF_SIZE	ESS_BUF_SIZE
	#define ESS_BACKEND_I2S_DMA_BUF_COUNT ESS_BUF_COUNT
#endif

#define ESS_BACKEND_NAME_OUT_I2S_ESP32 			 		"/dev/i2s0:0"
#define ESS_BACKEND_NAME_OUT_NULL									 "/dev/null0:0"
#define ESS_BACKEND_NAME_OUT_UDP								 		"/dev/udp0:0"
#define ESS_BACKEND_NAME_OUT_OPENAL	 					 "/dev/openal0:0"

#define ESS_BACKEND_NAME_IN_I2S_ESP32 			 	  "/dev/i2s0:1"
#define ESS_BACKEND_NAME_IN_OPENAL	 					  "/dev/openal0:1"

#endif
