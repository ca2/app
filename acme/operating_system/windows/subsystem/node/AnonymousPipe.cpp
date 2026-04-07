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
#include "AnonymousPipe.h"
#include "File.h"
//#include "remoting/remoting_common/win_system/Environment.h"
//#include "remoting/remoting_common/thread/critical_section_lock.h"

namespace windows
{
   namespace  subsystem
   {
      AnonymousPipe::AnonymousPipe()  :
        m_neededToClose(true),
        m_plogwriter(nullptr)
      {
      }

      AnonymousPipe::~AnonymousPipe()
      {
         try {
            close();
         } catch (::exception & e) {
            m_plogwriter->error("The close() function failed at AnonymousPipe destructor: {}",
                       e.get_message());
         }
      }

      void AnonymousPipe::initialize_anonymous_pipe(::subsystem::FileInterface * pfileWrite, ::subsystem::FileInterface * pfileRead, unsigned int maxPortionSize, ::subsystem::LogWriter *plogwriter)
      {
         initialize_pipe(maxPortionSize);

         m_pfileWrite = pfileWrite;
         m_pfileRead = pfileRead;
         m_plogwriter = plogwriter;

      }

      void AnonymousPipe::close()
      {
         critical_section_lock al(&m_criticalsectionPipe);

         bool wrSuc = true;
         bool rdSuc = true;
         ::string wrErrText, rdErrText;
         if (::is_ok(m_pfileWrite) && m_neededToClose) {
            if (CloseHandle(m_pfileWrite->m_handle) == 0) {
               wrErrText = ::windows::last_error_message("Cannot close anonymous pipe write handle.", ::windows::last_error());
               wrSuc = false;
            }
            m_plogwriter->debug("Closed m_hWrite(%p) AnonymousPipe handle",
                       m_pfileWrite->m_handle);
         }
         ::release(m_pfileWrite);
         if (::is_ok(m_pfileRead) && m_neededToClose) {
            if (CloseHandle(m_pfileRead->m_handle) == 0) {
               wrErrText = ::windows::last_error_message("Cannot close anonymous pipe read handle.", ::windows::last_error());
               rdSuc = false;
            }
            m_plogwriter->debug("Closed m_hRead(%p) AnonymousPipe handle",
                       m_pfileRead->m_handle);
         }
         ::release(m_pfileRead);
         if (!wrSuc || !rdSuc) {
            ::string errMess;
            errMess.formatf("AnonymousPipe::close() funciton has failed ({} {})",
                           wrErrText, rdErrText);
            throw ::subsystem::Exception(errMess);
         }
      }

      size_t AnonymousPipe::read(void *buffer, size_t len)
      {
         try {
            return readByFile(buffer, len, m_pfileRead);
         } catch (...) {
            m_plogwriter->error("AnonymousPipe::read() failed (m_hRead = %p)",
                       m_pfileRead->m_handle);
            throw;
         }
      }

      memsize AnonymousPipe::defer_write(const void *buffer, memsize len)
      {
         try {
            return writeByFile(buffer, len, m_pfileWrite);
         } catch (...) {
            m_plogwriter->error("AnonymousPipe::write() failed (m_hWrite = {})",
                       m_pfileWrite->m_handle);
            throw;
         }
      }

      void AnonymousPipe::checkPipeFile(::subsystem::FileInterface * pfile)
      {
         if (::is_null(pfile) || ::as_HANDLE(pfile) == INVALID_HANDLE_VALUE || ::as_HANDLE(pfile) == nullptr) {
            throw ::io_exception(error_io, "Invalid pipe handle");
         }
      }

      ::subsystem::FileInterface* AnonymousPipe::getWriteFile() const
      {
         return m_pfileWrite;
      }

      ::subsystem::FileInterface * AnonymousPipe::getReadFile() const
      {
         return m_pfileRead;
      }

      void AnonymousPipe::assignHandlesFor(HANDLE hTargetProc, bool neededToClose,
                                           bool keepCloseRight)
      {
         HANDLE hSrcProc = GetCurrentProcess();
         HANDLE hWrite = 0, hRead = 0;
         if (DuplicateHandle(hSrcProc, m_pfileWrite->m_handle, hTargetProc, &hWrite, 0, FALSE,
                             DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS) == 0) {
            ::string errText;
            errText = windows::last_error_message("Cannot dupplicate write"
                                   " handle for the anonymous pipe", ::windows::last_error());

            throw ::subsystem::Exception(errText);
                             }
         if (DuplicateHandle(hSrcProc, m_pfileRead->m_handle, hTargetProc, &hRead, 0, FALSE,
                             DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS) == 0) {
            ::string errText;
            errText = windows::last_error_message("Cannot dupplicate read"
                                   " handle for the anonymous pipe",
                                   ::windows::last_error());
            throw ::subsystem::Exception(errText);
                             }
         // Try keep of the close rights.
         if (keepCloseRight) {
            if (DuplicateHandle(hTargetProc, m_pfileWrite, 0, 0, 0, FALSE,
                                DUPLICATE_CLOSE_SOURCE) == 0) {
               ::string errText;
               errText = ::windows::last_error_message("Cannot keep the right to close of the write"
                                      " handle of the anonymous pipe",
                                      ::windows::last_error());
               throw ::subsystem::Exception(errText);
                                }
            if (DuplicateHandle(hTargetProc, m_pfileRead->m_handle, 0, 0, 0, FALSE,
                                DUPLICATE_CLOSE_SOURCE) == 0) {
               ::string errText;
               errText = ::windows::last_error_message("Cannot keep the right to close of the read"
                                      " handle of the anonymous pipe",
                                      ::windows::last_error());
               throw ::subsystem::Exception(errText);
                                }
            // Now the current process can close the handles.
         }
         m_pfileWrite->m_handle= hWrite;
         m_pfileRead->m_handle = hRead;
         m_neededToClose = neededToClose;
      }

      void AnonymousPipe::setTimeOut(unsigned int timeOut)
      {
         m_timeOut = timeOut;
      }
   }// namespace subsystem
}// namespace windows