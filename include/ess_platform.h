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
 * @file ess_platform.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief platform backends combiunations with OpenESS
 *
 *
 */
 /**
 * @addtogroup platform
 * @{
 */

#ifndef __ESS_PLATFORM_IMPL_H__
#define __ESS_PLATFORM_IMPL_H__

#include "ess.h"

#if ESS_PLATFORM_ESP32 == 1
#include "platform/esp32/ess_platform_esp32.h"

#ifdef ESS_ENABLE_BACKEND_OUT_I2S
#include "platform/esp32/i2s_generic_output_backend.h"
using ess_output_i2s = i2s_generic_output_backend;
#endif

#ifdef ESS_ENABLE_BACKEND_OUT_UDP
#include "platform/generic_udp_output_backend.h"
using ess_output_udp = generic_udp_output_backend;
#endif


using ess_platform = ess_platform_esp32;

#elif  ESS_PLATFORM_LINUX == 1
#include "platform/linux/ess_platform_linux.h"
using ess_platform = ess_platform_linux;

#elif ESS_PLATFORM_RPI == 1
#include "platform/rpi/ess_platform_rpi.h"
using ess_platform = ess_platform_ rpi;

#elif ESS_PLATFORM_WINDOWS == 1
#include "platform/windows/ess_platform_windows.h"
using ess_platform = ess_platform_windows;


#elif ESS_PLATFORM_USER == 1
#include "platform/user/ess_platform_user.h"
using ess_platform = ess_platform_user;
#endif


/**
* @}
*/
#endif
