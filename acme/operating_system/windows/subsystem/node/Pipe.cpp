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
#include "Pipe.h"
#include "acme/subsystem/Exception.h"
#include "acme/operating_system/windows/subsystem/node/File.h"
#include <crtdbg.h>
//#include "remoting/remoting_common/win_system/Environment.h"
//#include "remoting/remoting_common/thread/critical_section_lock.h"

namespace windows
{
   namespace subsystem
   {
      Pipe::Pipe(unsigned int maxPortionSize)
      : m_totalRead(0),
        m_totalWrote(0),
        m_maxPortionSize(maxPortionSize)
      {
      }

      Pipe::Pipe()
: m_totalRead(0),
  m_totalWrote(0),
  m_maxPortionSize(0)
      {
      }

      Pipe::~Pipe()
      {
      }


      void Pipe::initialize_pipe(unsigned int maxPortionSize)
      {
  m_maxPortionSize = maxPortionSize;
      }

      unsigned int Pipe::getMaxPortionSize()
      {
         return m_maxPortionSize;
      }

      size_t Pipe::writeByFile(const void *buffer, size_t len, ::subsystem::File * pfilePipe)
      {

         auto handlePipe = ::as_HANDLE(pfilePipe);
         DWORD result;
         OVERLAPPED overlapped;
         memset(&overlapped, 0, sizeof(OVERLAPPED));
         overlapped.hEvent = m_writeEvent.getHandle();

         bool success;
         DWORD length = (DWORD)len;
         _ASSERT(length == len);
         if (m_maxPortionSize != 0 && length > m_maxPortionSize) {
            length = m_maxPortionSize;
         }
         {
            critical_section_lock al(&m_criticalsectionPipe);
            checkPipeFile(pfilePipe);

            success = WriteFile(handlePipe, // pipe handle
                                buffer,    // scopedstrMessage
                                length,  // scopedstrMessage length
                                &result, // bytes written
                                &overlapped)    // overlapped
                                != 0;
         }

         if (!success) {
            int errCode = GetLastError();

            if (errCode == ERROR_IO_PENDING) {
               m_writeEvent.waitForEvent();
               DWORD cbRet;
               critical_section_lock al(&m_criticalsectionPipe);
               checkPipeFile(pfilePipe);
               if (GetOverlappedResult(handlePipe, &overlapped, &cbRet, FALSE) ||
                   cbRet == 0) {
                  result = cbRet;
                   } else {
                      ::string errMess;
                      errMess = ::windows::last_error_message("The Pipe's write function failed"
                                             " after GetOverlappedResult calling",
                                             ::windows::last_error());
                      throw ::io_exception(error_io, errMess);
                   }
            } else {
               ::string errText;
               errText.format("The Pipe's write function failed after WriteFile calling"
                              "(pipe handle is {}, total write {}, try to write {})",
                              handlePipe, m_totalWrote, length);
               ::string errMess;
               errMess = ::windows::last_error_message(errText, ::windows::last_error());
               throw ::io_exception(error_io,errMess);
            }
         } // else operation already successful has been completed

         if (result == 0) {
            throw ::io_exception(error_io, "Unknown pipe error");
         }

         m_totalWrote += result;
         return result;
      }

      size_t Pipe::readByFile(void *buffer, size_t len, ::subsystem::File * pfilePipe)
      {
         auto handlePipe = ::as_HANDLE(pfilePipe);
         DWORD result = 0;
         OVERLAPPED overlapped;
         memset(&overlapped, 0, sizeof(OVERLAPPED));
         overlapped.hEvent = m_readEvent.getHandle();

         bool success;
         DWORD length = (DWORD)len;
         _ASSERT(length == len);
         if (m_maxPortionSize != 0 && length > m_maxPortionSize) {
            length = m_maxPortionSize;
         }
         {
            critical_section_lock al(&m_criticalsectionPipe);
            checkPipeFile(pfilePipe);
            success = ReadFile(handlePipe,         // pipe handle
                               buffer,            // scopedstrMessage
                               length,          // scopedstrMessage length
                               &result,         // bytes read
                               &overlapped)   // overlapped
                               != 0;
         }
         if (!success) {
            DWORD errCode = GetLastError();

            if (errCode == ERROR_IO_PENDING) {
               m_readEvent.waitForEvent();
               DWORD cbRet = 0;
               critical_section_lock al(&m_criticalsectionPipe);
               checkPipeFile(pfilePipe);
               if (GetOverlappedResult(handlePipe, &overlapped, &cbRet, FALSE) &&
                   cbRet != 0) {
                  result = cbRet;
                   } else {
                      ::string errText;
                      errText.formatf("The Pipe's read function failed after GetOverlappedResult calling (pipe handle is %p)", handlePipe);
                      ::string errMess;
                      errMess = ::windows::last_error_message(errText, ::windows::last_error());
                      throw ::io_exception(error_io,errMess);

                   }
            } else {
               ::string errText;
               errText.formatf("The Pipe's write function failed after ReadFile calling"
                              "(pipe handle is %p, total read %llu, try to read %u)",
                              handlePipe, m_totalRead, length);
               ::string errMess;
               errMess = ::windows::last_error_message(errText, ::windows::last_error());
               throw ::io_exception(error_io,errMess);
            }
         } // else operation already successful has been completed

         if (result == 0) {
            throw ::io_exception(error_io, "Unknown pipe error");
         }
         m_totalRead += result;
         return result;
      }

      void Pipe::checkPipeFile(::subsystem::File * pfilePipe)
      {
         auto handlePipe = ::as_HANDLE(pfilePipe);
         if (::is_set(pfilePipe) && handlePipe == INVALID_HANDLE_VALUE) {
            throw ::io_exception(error_io, "Invalid pipe handle");
         }
      }
   } // namespace subsystem
} // namespace windows

