// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "remoting/remoting_common/util/Exception.h"

/**
 * Windows exception.
 *
 * Solves problem with generating formatted scopedstrMessage strings width describes
 * user code-space where error occured and windows specific information about WinAPI error.
 */
class CLASS_DECL_REMOTING_COMMON SystemException : public ::remoting::Exception
{
public:
  /**
   * Creates exception with formatted scopedstrMessage from system
   * and error code which equals to GetLastError() value.
   */
  SystemException();
  /**
   * Creates exception with formatted scopedstrMessage from system
   * and error code.
   * @param errcode windows error code.
   */
  SystemException(int errcode);
  /**
   * Creates exception with user scopedstrMessage + formatted scopedstrMessage from system
   * and error code set to GetLastError() value.
   * @param userMessage user scopedstrMessage.
   */
  SystemException(const ::scoped_string & scopedstrUserMessage);
  /**
   * Creates exception with user scopedstrMessage + formatted scopedstrMessage from system
   * and specified error code.
   * @param userMessage user scopedstrMessage.
   * @param errcode windows error code.
   */
  SystemException(const ::scoped_string & scopedstrUserMessage, int errcode);
  /**
   * Destructor, does nothing.
   */
  virtual ~SystemException();
  /**
   * Returns error code.
   * @return windows error code associated with this exception.
   */
  int getErrorCode() const;
  /**
   * Returns system error description.
   * @return system error description.
   */
  ::string getSystemErrorDescription() const;
private:
  /**
   * Creates formatted scopedstrMessage for exception.
   * @param userMessage user description about exception reason.
   * @param errcode windows error code.
   * @fixme document all special cases.
   */
  void createMessage(const ::scoped_string & scopedstrUserMessage, int errcode);
private:
  /**
   * Description of error from OS.
   */
  ::string m_systemMessage;
  /**
   * Windows error code.
   */
  int m_errcode;
};


