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
#include "framework.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "ProcessHandle.h"
#include "acme/subsystem/node/SystemException.h"

namespace windows
{
   namespace subsystem
   {
      ProcessHandle::ProcessHandle()
      : m_hProcess(0)
      {
      }

      ProcessHandle::ProcessHandle(HANDLE handle, bool bOwn)
      : m_hProcess(0), m_bOwned(bOwn)
      {


      }

      ProcessHandle::~ProcessHandle()
      {
         if (m_hProcess != 0 && m_bOwned) {
            CloseHandle(m_hProcess);
         }
      }

      void ProcessHandle::openProcess(unsigned int dwDesiredAccess,
                          bool bInheritHandle,
                          ::process_identifier processidentifier)
      {
         m_hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, processidentifier);
         if (m_hProcess == 0) {
            ::string errMess;
            errMess.formatf("Can't open the {} process", processidentifier);
            throw ::subsystem::SystemException(errMess);
         }
         m_bOwned = true;
      }
      //
      // ::subsystem::ProcessHandle * ProcessHandle::getHandle() const
      // {
      //    return m_pprocessHandle;
      // }

      ::string ProcessHandle::getProcessModulePath()
      {
         // FIXME: Test under Windows7
         TCHAR path[MAX_PATH];
         DWORD result = GetModuleFileNameEx(m_hProcess, 0, path,
                                            sizeof(path) / sizeof(TCHAR));
         if (result == 0) {
            throw ::subsystem::SystemException("Can't get process module path");
         }
         return path;
      }
   } // namespace subsystem
}// namespace windows