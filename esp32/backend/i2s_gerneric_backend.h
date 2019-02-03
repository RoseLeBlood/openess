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
 * @file i2s_gerneric_backend.h
 * @author Anna Sopdia Schröck
 * @date 30 Januar 20119
 * @brief ESS i2s generic backend
 *
 */
#ifndef __ESS_BACKEND_I2S_GENERIC_H__
#define __ESS_BACKEND_I2S_GENERIC_H__




#ifdef __cplusplus
extern "C" {
#endif

/**
 * get the i2s_generic_backend factory
 */
ess_backend_facktory_t* ess_backend_i2s_generic_getFactory();


#ifdef __cplusplus
}
#endif

#endif
