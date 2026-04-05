// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


#include "remoting/remoting_common/util/winhdr.h"

#include "SystemException.h"

/**
 * Wrapper on WinAPI workstation functions.
 */
class CLASS_DECL_REMOTING_COMMON Workstation
{
public:
  /**
   * Locks workstation.
   * @throws SystemException on fail.
   */
  static void lock();
  /**
   * Logs off interactive user.
   * @throws SystemException on fail.
   * @remark caller must be run on interactive session.
   */
  static void logOff();
};


