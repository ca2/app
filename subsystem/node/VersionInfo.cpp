// Copyright (C) 2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
// #include "acme/_operating_system.h"
#include "VersionInfo.h"
// //// #include aaa_<vector>


namespace subsystem
{



   //VersionInfo::VersionInfo()
   //{


   //}
   ////
   ////
   //// VersionInfo::VersionInfo(const ::file::path & pathToFile)
   //// {
   ////   DWORD handle = 0;
   ////   DWORD verInfoSize = GetFileVersionInfoSize(pathToFile.windows_path(), &handle);
   ////
   ////   if (verInfoSize == 0) {
   ////     throw SystemException();
   ////   }
   ////
   ////   ::array_base<::i8> charBuff(verInfoSize);
   ////   char_pointer verInfo = charBuff.data();
   ////
   ////   if (GetFileVersionInfo(pathToFile.windows_path(), handle, verInfoSize, verInfo) == 0) {
   ////     throw SystemException();
   ////   }
   ////
   ////   UINT fixedInfoSize = 0;
   ////
   ////   VS_FIXEDFILEINFO *fixedInfo = 0;
   ////
   ////   if (VerQueryValue(verInfo, L"\\", (void **)&fixedInfo, &fixedInfoSize) == 0) {
   ////     throw SystemException();
   ////   }
   ////
   ////   ::u16 a = ((::u16 *)&fixedInfo->dwProductVersionMS)[1];
   ////   ::u16 b = ((::u16 *)&fixedInfo->dwProductVersionMS)[0];
   ////   ::u16 c = ((::u16 *)&fixedInfo->dwProductVersionLS)[1];
   ////   ::u16 d = ((::u16 *)&fixedInfo->dwProductVersionLS)[0];
   ////
   ////   // Convert special numbers used for beta versions (third number > 100).
   ////   // 2.0.105.0 should be considered a beta version and convert to 2.1beta5,
   ////   // 1.99.101 converts to 2.0beta1, 1.99.101.23 converts to 2.0beta1.23 etc.
   ////   TCHAR *secondDelimiter = (TCHAR *)  ".";
   ////   if (c > 100) {
   ////     secondDelimiter = (TCHAR *) "beta";
   ////     c -= 100;
   ////     if (++b >= 100) {
   ////       b = 0;
   ////       a++;
   ////     }
   ////   }
   ////
   ////   if (c == 0 && d == 0) {
   ////     m_productVersionString.formatf("{}.{}", (::i32)a, (::i32)b);
   ////   } else if (d == 0) {
   ////     m_productVersionString.formatf("{}.{}{}{}", (::i32)a, (::i32)b,
   ////                                   secondDelimiter, (::i32)c);
   ////   } else {
   ////     m_productVersionString.formatf("{}.{}{}{}.{}", (::i32)a, (::i32)b,
   ////                                   secondDelimiter, (::i32)c, (::i32)d);
   ////   }
   //// }

   //VersionInfo::~VersionInfo()
   //{


   //}

   //void VersionInfo::initialize_version_info(const ::file::path & pathToFile)
   //{

   //   m_pparticleThis->initialize_version_info(pathToFile);

   //}

   //::string VersionInfo::getProductVersionString() const
   //{
   ////  return m_productVersionString;

   //   return m_pparticleThis->getProductVersionString();
   //}




} // namespace subsystem


