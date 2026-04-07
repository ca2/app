// Copyright (C) 2012 GlavSoft LLC.
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
#include "Cursor.h"



namespace windows
{
   namespace subsystem
   {

      File::File()
      {
         m_handle=nullptr;
         m_bOwned = false;
      }

      File::~File()
      {

         if (m_bOwned && m_handle != nullptr && m_handle != INVALID_HANDLE_VALUE)
         {

            auto bOk = ::CloseHandle(m_handle);

            if (!bOk)
            {

               error("windows::subsystem::File Close Handle failed");

            }



         }
      }


   } // namespace subsystem
} // namespace windows


CLASS_DECL_ACME HANDLE as_HANDLE(::subsystem::File * pfile)
{

   ::cast < ::windows::subsystem::File > pwindowssubsystemfile = pfile;

   auto handle = pwindowssubsystemfile->m_handle;

   return handle;

}

CLASS_DECL_ACME bool is_ok(const ::windows::subsystem::File * pfile)
{

   if (!::is_set(pfile))
   {

      return false;

   }

   if (pfile->m_handle == nullptr)
   {

      return false;

   }

   if (pfile->m_handle == INVALID_HANDLE_VALUE)
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME bool is_ok(const ::pointer < ::windows::subsystem::File > & pfile)
{

   return ::is_ok(pfile.m_p);

}