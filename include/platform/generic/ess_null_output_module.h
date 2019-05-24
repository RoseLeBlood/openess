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
 * @file ess_null_output_module.h
 * @author Anna Sopdia Schröck
 * @date 18 Februar 2019
 * @brief the basic null backend class
 *
 * this is a null backend only for testing
 */
#ifndef _ESS_PLATFORM_INC_GENERIC_NULL_H_
#define _ESS_PLATFORM_INC_GENERIC_NULL_H_

/**
* @addtogroup ess_platform_generic
* @{
*/

#include "../../core/module/ess_output_module.h"

#define ESS_NULL_OUTPUT_NAME									   "ess_outnull"

class ess_null_output_module  : public ess_output_module {
public:
  ess_null_output_module();
  ~ess_null_output_module();

  virtual ess_error_t update(void) ;
private:
  ess_audioblock_t m_pBuffer;
};

/**
* @}
*/
#endif
