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
#include "WinStaLibrary.h"
#include "DynamicLibrary.h"


namespace  windows
{
   WinStaLibrary::WinStaLibrary()
   : m_winStationConnectW(NULL)
   {
      // try {
      //    construct_newø(m_pdynamiclibraryWinSta);
      //
      //    m_pdynamiclibraryWinSta->initialize_dynamic_library("winsta.dll");
      //
      //    m_winStationConnectW = (pWinStationConnectW)m_pdynamiclibraryWinSta->getProcAddress("WinStationConnectW");
      // } catch (...) {
      //    m_pdynamiclibraryWinSta = nullptr;
      // }
   }

   WinStaLibrary::~WinStaLibrary()
   {
      //if (m_winStaDll != NULL) {
        // delete m_winStaDll;
      //}
   }


   void WinStaLibrary::initialize_winsta_library()
   {
   try {
      construct_newø(m_pdynamiclibraryWinSta);

      m_pdynamiclibraryWinSta->initialize_dynamic_library("winsta.dll");

      m_winStationConnectW = (pWinStationConnectW)m_pdynamiclibraryWinSta->getProcAddress("WinStationConnectW");
   } catch (...) {
      m_pdynamiclibraryWinSta = nullptr;
   }
}

   BOOL WinStaLibrary::WinStationConnectW(HANDLE server, ULONG connectSessionId,
                                          ULONG activeSessionId, PCWSTR password,
                                          ULONG unknown)
   {
      if (!m_pdynamiclibraryWinSta || !m_winStationConnectW)
         {
         return FALSE;
      }

      return m_winStationConnectW(server, connectSessionId, activeSessionId, password, unknown);
   }
} // namespace  windows


