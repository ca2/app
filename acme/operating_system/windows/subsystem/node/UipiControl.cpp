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
#include "framework.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "UipiControl.h"
//#include "Environment.h"
#include "DynamicLibrary.h"
#include "acme/subsystem/node/SystemException.h"
#include "acme/platform/node.h"

#ifndef MSGFLT_ADD
#define MSGFLT_ADD 1
#endif

namespace windows
{
   typedef BOOL (WINAPI *SetFilterEx)(HWND hWnd,
                                      UINT scopedstrMessage,
                                      DWORD action,
                                      unsigned int *reserved
   );
   typedef BOOL (WINAPI *SetFilter)(UINT scopedstrMessage,
                                    DWORD action);

   UipiControl::UipiControl(::subsystem::LogWriter *log)
   : m_plogwriter(log)
   {
   }

   UipiControl::~UipiControl()
   {
   }

   void UipiControl::allowMessage(UINT uMessage, HWND hwnd)
   {
      m_plogwriter->information("Try allow to receive the %u windows uMessage");
      if (::system()->node()->_windows_isVistaOrLater()) {
         ::subsystem::DynamicLibrary user32lib;
         user32lib.initialize_dynamic_library("user32.dll");
         m_plogwriter->information("user32.dll successfully loaded.");
         SetFilterEx setFilterEx;
         // FIXME: Test this on Windows7.
         // Try to load the ChangeWindowMessageFilterEx() function.
         setFilterEx = (SetFilterEx)user32lib.getProcAddress("ChangeWindowMessageFilterEx");
         if (setFilterEx == 0) {
            // On fail try to load the ChangeWindowMessageFilter() function.
            SetFilter setFilter;
            setFilter = (SetFilter)user32lib.getProcAddress("ChangeWindowMessageFilter");
            if (setFilter == 0) {
               throw ::subsystem::Exception("Can't load the ChangeWindowMessageFilterEx() or "
                               "ChangeWindowMessageFilter() functions.");
            }
            m_plogwriter->information("The ChangeWindowMessageFilter() function "
                      "successfully found.");
            if (setFilter(uMessage, MSGFLT_ADD) != TRUE) {
               DWORD errCode = GetLastError();
               ::string errMess;
               errMess.formatf("Can't allow to receive the {} windows uMessage by "
                              "the ChangeWindowMessageFilter() function.");
               throw ::subsystem::SystemException(errMess, errCode);
            }
            m_plogwriter->information("The ChangeWindowMessageFilter() function "
                      "successfully executed.");
         } else {
            // FIXME: Can't to check for Windows7.
            m_plogwriter->information("The ChangeWindowMessageFilterEx() function "
                      "successfully found.");
            if (setFilterEx(hwnd, uMessage, MSGFLT_ADD, 0) != TRUE) {
               DWORD errCode = GetLastError();
               ::string errMess;
               errMess.formatf("Can't allow to receive the {} windows uMessage by "
                              "the ChangeWindowMessageFilterEx() function.");
               throw ::subsystem::SystemException(errMess, errCode);
            }
            m_plogwriter->information("The ChangeWindowMessageFilterEx() function "
                      "successfully executed.");
         }
      } else {
         m_plogwriter->information("The allowMessage() function call is ignored.");
      }
   }
} // namespace windows