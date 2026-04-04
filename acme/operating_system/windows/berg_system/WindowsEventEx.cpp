// Copyright (C) 2013 GlavSoft LLC.
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
#include "framework.h"
#include "acme/_operating_system.h"
#include "WindowsEventEx.h"
#include "remoting/remoting_common/util/Exception.h"
#include <Aclapi.h>

WindowsEventEx::WindowsEventEx(const ::scoped_string & scopedstrName)
: WindowsEvent(scopedstrName)
{
  bool needToInit = GetLastError() != ERROR_ALREADY_EXISTS;
  if (needToInit) {
    setAccessToAll(getHandle());
  }
}

void WindowsEventEx::setAccessToAll(HANDLE objHandle)
{
  DWORD errorCode = SetSecurityInfo(objHandle, SE_KERNEL_OBJECT,
                                    DACL_SECURITY_INFORMATION, // Modify DACL
                                    0,
                                    0,
                                    0, // Pointer to DACL (0 = access to all)
                                    0);
  if (errorCode != ERROR_SUCCESS &&
      errorCode != ERROR_NO_SECURITY_ON_OBJECT) {
    ::string errMess;
    errMess.formatf("Cannot SetSecurityInfo with error = {}", (int)errorCode);
    throw ::remoting::Exception(errMess);
  }
}
