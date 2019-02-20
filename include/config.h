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

#define ESS_DEFAULT_SERVER_PORT "8686"
#define ESS_DEFAULT_SERVER_PROTOCOL ESS_PROTOCOL_UDP_LITE
#define ESS_DEFAULT_SERVER_FAMILY ESS_FAMILY_IP4
#define ESS_DEFAULT_SERVER_FORMAT ESS_FORMAT_STEREO_44100_16


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

	#define ESS_ENABLE_BACKEND_UART /**< esp32 platform UART backend available */
	#define ESS_ENABLE_BACKEND_I2S /**< esp32 platform I2S backend available */
	#define ESS_ENABLE_BACKEND_UDP/**< generic platform UDP backend available */

	#define ESS_DEFAULT_SERVER_NAME "OpenEssD-esp32" /**< basic server name*/
#endif // ESS_PLATFORM_ESP32

#if ESS_PLATFORM_RPI == 1
	#define ESS_CONFIG_MUTEX_GENERIC
	#define ESS_CONFIC_TASK_GENERIC
	#define ESS_CONFIG_RINGBUFFER_GENERIC
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OPENAL
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenEssD-rpi"
#endif //ESS_PLATFORM_RPI

#if ESS_PLATFORM_LINUX == 1
	#define ESS_CONFIC_TASK_GENERIC
	#define ESS_CONFIG_RINGBUFFER_GENERIC
	#define ESS_CONFIG_MUTEX_GENERIC
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OPENAL
	/** @brief If defined then Pulseaudio backend available */
	#define ESS_ENABLE_BACKEND_PULSEAUDIO
	/** @brief If defined then ALSA backend available */
	#define ESS_ENABLE_BACKEND_ALSA
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenEssD-linux"
#endif //ESS_PLATFORM_LINUX

#if ESS_PLATFORM_WINDOWS == 1
	#define ESS_CONFIG_SEMAPHORE_WINDOWS
	#define ESS_CONFIC_TASK_WINDOWS
	#define ESS_CONFIG_RINGBUFFER_WINDOWS
	#define ESS_CONFIG_MUTEX_WINDOWS
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_OPENAL
	/** @brief If defined then OpenAL backend available */
	#define ESS_ENABLE_BACKEND_WASAPI
	/** @brief If defined then UDP backend available */
	#define ESS_ENABLE_BACKEND_UDP
	#define ESS_DEFAULT_SERVER_NAME "OpenEssD-windows"
#endif //ESS_PLATFORM_WINDOWS


//-------------------------------------------------------------------------------------------------------

#ifdef ESS_ENABLE_BACKEND_UART
	#define ESS_BACKEND_UART_BAUDRAT 115200
	#define ESS_BACKEND_UART_TXD  (GPIO_NUM_4)
	#define ESS_BACKEND_UART_RXD  (GPIO_NUM_5)
	#define ESS_BACKEND_UART_RTS  (UART_PIN_NO_CHANGE)
	#define ESS_BACKEND_UART_CTS  (UART_PIN_NO_CHANGE)
#endif

#ifdef ESS_ENABLE_BACKEND_UDP
	#define ESS_BACKEND_UDP_PORT 17000
	#define ESS_BACKEND_UDP_HOST 192.168.0.235
	#define ESS_BACKEND_UDP_FAMILY ESS_FAMILY_BOTH
#endif

#ifdef ESS_ENABLE_BACKEND_I2S
	#define I2S_EXTERNAL_DAC_BCK 26
	#define I2S_EXTERNAL_DAC_LRCLK 25
	#define I2S_EXTERNAL_DAC_DOUT 22
	#define  I2S_EXTERNAL_DAC_DIN   -1                                                    //Not used

  #define ESS_BACKEND_I2S_FORMAT ESS_FORMAT_STEREO_96000_16
	#define ESS_BACKEND_I2S_DMA_BUF_SIZE	512
	#define ESS_BACKEND_I2S_DMA_BUF_COUNT 6
#endif

#define ESS_BACKEND_NAME_I2S_ESP32 			 "i2s_esp32"
#define ESS_BACKEND_NAME_NULL								"null"
#define ESS_BACKEND_NAME_UDP								 "udp"
#define ESS_BACKEND_NAME_OPENAL	 				"openal"

#endif
