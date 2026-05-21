// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "shared_memory.h"
//#include "util/Exception.h"
#include <Aclapi.h>

namespace windows
{
   shared_memory::shared_memory()
   : m_hToMap(0),
     m_memsize(0)
   {

   }

   shared_memory::~shared_memory()
   {
      Close();
   }

   void shared_memory::Close()
   {
      if (m_begin) {
         UnmapViewOfFile(m_begin);
         m_begin = nullptr;
         m_end = nullptr;
      }
      if (m_hToMap) {
         CloseHandle(m_hToMap);
         m_hToMap = nullptr;
      }
   }


   bool shared_memory::CreateSharedMemory(const char* name, memsize size)
   {

      try {
         bool needToInit = _createFile(name, size);
         _mapViewOfFile();
         if (needToInit) {
            memset(m_begin, 0, size);
         }
      } catch (...) {
         Close();
         throw;
      }


      return true;
   }


   bool shared_memory::OpenSharedMemory(const char * name, memsize size)
   {
      try {

         m_memsize = size;

         ::wstring wstrName(name);

         m_hToMap = OpenFileMappingW(
            FILE_MAP_WRITE, // read/write access
            FALSE,          // do not inherit handle
            wstrName);

         if (m_hToMap == NULL) {
            m_memsize = 0;

            auto lasterror = ::windows::last_error();

            ::string strMessage;
            strMessage.formatf(
               "Cannot open file mapping with error = %d",
               lasterror.m_uLastError);

            throw ::exception(error_failed, strMessage);
         }

         _mapViewOfFile();

         return true;

      } catch (...) {

         Close();
         throw;

      }
   }

   bool shared_memory::_createFile(const char *name, memsize size)
   {

      m_memsize = size;

      ::wstring wstrName(name);
      DWORD lowSize = size & 0xffffffff;
      DWORD highSize = (DWORD64)size >> 32 & 0xffffffff;

      m_hToMap = CreateFileMappingW(INVALID_HANDLE_VALUE,  // use paging file
                                   0,                     // security attributes
                                   PAGE_READWRITE,        // read/write access
                                   highSize,              // size: high 32-bits
                                   lowSize,               // size: low 32-bits
                                   wstrName);                 // name of map object
      if (m_hToMap == NULL) {
         m_memsize = 0;
         auto lasterror = ::windows::last_error();
         ::string strMessage;
         strMessage.formatf("Cannot create file mapping with error = %d", lasterror.m_uLastError);
         throw ::exception(error_failed, strMessage);
      }
      // The first process to attach initializes memory
      bool needToInit = GetLastError() != ERROR_ALREADY_EXISTS;

      if (needToInit) {
         _setAllAccess(m_hToMap);
      }

      return needToInit;
   }

   void shared_memory::_mapViewOfFile()
   {
      // Get a pointer to the file-mapped shared memory
      m_begin = (::u8*) MapViewOfFile(m_hToMap,       // object to map view of
                               FILE_MAP_WRITE, // read/write access
                               0,              // high offset:  map from
                               0,              // low offset:   beginning
                               0);             // default: map entire file
      if (m_begin == NULL) {
         auto lasterror = ::windows::last_error();
         ::string strMessage;
         strMessage.formatf("Cannot map view of file with error = %d", lasterror.m_uLastError);
         throw ::exception(error_failed, strMessage);
      }
      m_end  = m_begin;
   }

   void shared_memory::_setAllAccess(HANDLE objHandle)
   {
      DWORD errorCode = SetSecurityInfo(objHandle, SE_FILE_OBJECT,
                                        DACL_SECURITY_INFORMATION, // Modify DACL
                                        0,
                                        0,
                                        0, // Pointer to DACL (0 = access to all)
                                        0);
      if (errorCode != ERROR_SUCCESS) {
         ::string strMessage;
         strMessage.formatf("Cannot SetSecurityInfo with error = %d", (int)errorCode);
         throw ::exception(error_failed, strMessage);
      }
   }
} // namespace windows