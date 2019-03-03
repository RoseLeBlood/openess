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
 * @file ess_protocol.h
 * @author Anna Sopdia Schröck
 * @date 12 Februar 2019
 * @brief contains the OpenESS protocol
 *
 */


#ifndef _ESS_PROTOCOL_H_
#define _ESS_PROTOCOL_H_

// used  in ess_daemon
typedef enum ess_protocol {
    OPENESS_PROTOCAL_CONTROLL_STOP,   /**< controll client stopped the audio backend */
    OPENESS_PROTOCAL_CONTROLL_START,   /**< controll client start the audio backend */
    OPENESS_PROTOCAL_CONTROLL_PAUSE,   /**< controll client paused the audio backend  */
    OPENESS_PROTOCAL_CONTROLL_RESTART,   /**< controll client restart the audio backend */
    OPENESS_PROTOCAL_CONTROLL_REMOVE,   /**< controll client remove a client t*/
    OPENESS_PROTOCAL_CONTROLL_SET_FORMAT,   /**< controll client set a other server band format */
    OPENESS_PROTOCAL_CONTROLL_SET_VOLUME,   /**< controll client set the mixer volume */

    OPENESS_PROTOCAL_CONTROLL_GET_VERSION,/** < csi client get OpenESS versioen*/
    OPENESS_PROTOCAL_CONTROLL_GET_MIXER,/** < csi client get Mixer info*/
    OPENESS_PROTOCAL_CONTROLL_GET_BACKEND,/** < csi client get backend info*/
    OPENESS_PROTOCAL_CONTROLL_GET_PLATFORM,/** < csi client get platform info*/


//------------------------------------------------------------------------------- NOT INC
    OPENESS_PROTOCAL_CONTROLL_GET_FORMAT,
    OPENESS_PROTOCOL_CONTROLL_GET_ID,  /**< get client id */
    OPENESS_PROTOCOL_CONTROLL_GET_NAME,   /**< get client name */
    OPENESS_PROTOCOL_CONTROLL_SET_NAME,   /**< set client name */
    OPENESS_PROTOCOL_GET_LATENCY,      /**<retrieve latency between write()'s and output */

    OPENESS_PROTOCOL_MAX           /**<for bounds checking */
}ess_protocol_t;


#endif
