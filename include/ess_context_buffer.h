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
 * @file ess_context_buffer.h
 * @author Anna Sopdia Schröck
 * @date 23 Februar 2019
 *
 *
 */
 /**
 * @addtogroup context
 * @{
 */
#ifndef __ESS_CONTEXT_H__
#define __ESS_CONTEXT_H__
#include "ess_buffer.h"
#include "ess_context.h"

class ess_context_buffer {
public:
  virtual ess_error_t write(ess_buffer* other); // write

  virtual void update(); // write data from buffer to context
protected:
  ess_buffer m_buffer;
  ess_context *m_pContext;
};

/**
* @}
*/

#endif
