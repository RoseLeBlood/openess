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
 * @date 12 Februar 20119
 * @brief contains the OpenESS prtocol
 *
 */


#ifndef _ESS_PROTOCOL_H_
#define _ESS_PROTOCOL_H_

typedef enum  ess_client_type {
  ESS_CLIENT_TYPE_INPUT,            /**< client send data to server - normal modus*/
  ESS_CLIENT_TYPE_MONITOR,      /**< client send no audio data to server - client get only status updates*/
  ESS_CLIENT_TYPE_CONTROLL,   /**< client can controll the server*/
}ess_client_type_t;

typedef enum ess_protocol {
    OPENESS_PROTOCOL_CLIENT_CONNECT,      /**< client connect*/
    OPENESS_PROTOCOL_CLIENT_START,   /**< client send data to server */
    OPENESS_PROTOCOL_CLIENT_STOP, /**< client stop send data to server */
    OPENESS_PROTOCOL_CLIENT_SET_TYPE, /**< set the client type (`ess_client_type_t`) */
    OPENESS_PROTOCOL_CLIENT_GET_TYPE, /**< get the client type (`ess_client_type_t`) */
    OPENESS_PROTOCOL_CLIENT_GET_ID,  /**< get client id */
    OPENESS_PROTOCOL_CLIENT_GET_NAME,   /**< get client name */
    OPENESS_PROTOCOL_CLIENT_SET_NAME,   /**< set client name */
    OPENESS_PROTOCOL_CLIENT_GET_FORMAT, /**< get server format */
    OPENESS_PROTOCOL_CLIENT_DISCONNECT,  /**< client send disconnect */
    OPENESS_PROTOCOL_CLIENT_GET_SERVER_INFO,  /**<get server info (ver, sample rate, format) */

    OPENESS_PROTOCOL_GET_LATENCY,      /**<retrieve latency between write()'s and output */


    OPENESS_PROTOCAL_CONTROLL_STOP,   /**< controll client stopped the audio backend - (req: `ESS_CLIENT_TYPE_CONTROLL`)*/
    OPENESS_PROTOCAL_CONTROLL_START,   /**< controll client start the audio backend -(req: `ESS_CLIENT_TYPE_CONTROLL`)*/
    OPENESS_PROTOCAL_CONTROLL_PAUSE,   /**< controll client paused the audio backend -(req: `ESS_CLIENT_TYPE_CONTROLL`) */
    OPENESS_PROTOCAL_CONTROLL_RESTART,   /**< controll client restart the audio backend -(req: `ESS_CLIENT_TYPE_CONTROLL`)*/
    OPENESS_PROTOCAL_CONTROLL_REMOVE,   /**< controll client remove a client -(req: `ESS_CLIENT_TYPE_CONTROLL`)t*/
    OPENESS_PROTOCAL_CONTROLL_SET_FORMAT,   /**< controll client set a other server band format -(req: `ESS_CLIENT_TYPE_CONTROLL`)*/

    OPENESS_PROTOCOL_MAX           /**<for bounds checking */
}ess_protocol_t;


#endif