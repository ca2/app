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
#include "acme/_operating_system.h"
#include "AnonymousPipe.h"
//#include "remoting/remoting_common/win_system/Environment.h"
#include "remoting/remoting_common/thread/AutoLock.h"

AnonymousPipe::AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *log)
: Pipe(maxPortionSize),
  m_hWrite(hWrite),
  m_hRead(hRead),
  m_neededToClose(true),
  m_log(log)
{
}

AnonymousPipe::~AnonymousPipe()
{
  try {
    close();
  } catch (::exception & e) {
    m_log->error("The close() function failed at AnonymousPipe destructor: {}",
               e.get_message());
  }
}

void AnonymousPipe::close()
{
  AutoLock al(&m_hPipeMutex);

  bool wrSuc = true;
  bool rdSuc = true;
  ::string wrErrText, rdErrText;
  if (m_hWrite != INVALID_HANDLE_VALUE && m_neededToClose) {
    if (CloseHandle(m_hWrite) == 0) {
      wrErrText = ::windows::last_error_message("Cannot close anonymous pipe write handle.", ::windows::last_error());
      wrSuc = false;
    }
    m_log->debug("Closed m_hWrite(%p) AnonymousPipe handle",
               m_hWrite);
  }
  m_hWrite = INVALID_HANDLE_VALUE;
  if (m_hRead != INVALID_HANDLE_VALUE && m_neededToClose) {
    if (CloseHandle(m_hRead) == 0) {
      wrErrText = ::windows::last_error_message("Cannot close anonymous pipe read handle.", ::windows::last_error());
      rdSuc = false;
    }
    m_log->debug("Closed m_hRead(%p) AnonymousPipe handle",
               m_hRead);
  }
  m_hRead = INVALID_HANDLE_VALUE;
  if (!wrSuc || !rdSuc) {
    ::string errMess;
    errMess.formatf("AnonymousPipe::close() funciton has failed ({} {})",
                   wrErrText, rdErrText);
    throw ::remoting::Exception(errMess);
  }
}

size_t AnonymousPipe::read(void *buffer, size_t len)
{
  try {
    return readByHandle(buffer, len, m_hRead);
  } catch (...) {
    m_log->error("AnonymousPipe::read() failed (m_hRead = %p)",
               m_hRead);
    throw;
  }
}

memsize AnonymousPipe::defer_write(const void *buffer, memsize len)
{
   try {
      return writeByHandle(buffer, len, m_hWrite);
   } catch (...) {
      m_log->error("AnonymousPipe::write() failed (m_hWrite = {})",
                 m_hWrite);
      throw;
   }
}

void AnonymousPipe::checkPipeHandle(HANDLE handle)
{
  if (handle == INVALID_HANDLE_VALUE) {
    throw ::io_exception(error_io, "Invalid pipe handle");
  }
}

HANDLE AnonymousPipe::getWriteHandle() const
{
  return m_hWrite;
}

HANDLE AnonymousPipe::getReadHandle() const
{
  return m_hRead;
}

void AnonymousPipe::assignHandlesFor(HANDLE hTargetProc, bool neededToClose,
                                     bool keepCloseRight)
{
  HANDLE hSrcProc = GetCurrentProcess();
  HANDLE hWrite = 0, hRead = 0;
  if (DuplicateHandle(hSrcProc, m_hWrite, hTargetProc, &hWrite, 0, FALSE,
                      DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS) == 0) {
    ::string errText;
    errText = windows::last_error_message("Cannot dupplicate write"
                           " handle for the anonymous pipe", ::windows::last_error());

    throw ::remoting::Exception(errText);
  }
  m_hWrite = hWrite;
  if (DuplicateHandle(hSrcProc, m_hRead, hTargetProc, &hRead, 0, FALSE,
                      DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS) == 0) {
    ::string errText;
    errText = windows::last_error_message("Cannot dupplicate read"
                           " handle for the anonymous pipe",
                           ::windows::last_error());
    throw ::remoting::Exception(errText);
  }
  m_hRead = hRead;
  // Try keep of the close rights.
  if (keepCloseRight) {
    if (DuplicateHandle(hTargetProc, m_hWrite, 0, 0, 0, FALSE,
                        DUPLICATE_CLOSE_SOURCE) == 0) {
      ::string errText;
      errText = ::windows::last_error_message("Cannot keep the right to close of the write"
                             " handle of the anonymous pipe",
                             ::windows::last_error());
      throw ::remoting::Exception(errText);
    }
    if (DuplicateHandle(hTargetProc, m_hRead, 0, 0, 0, FALSE,
                        DUPLICATE_CLOSE_SOURCE) == 0) {
      ::string errText;
      errText = ::windows::last_error_message("Cannot keep the right to close of the read"
                             " handle of the anonymous pipe",
                             ::windows::last_error());
      throw ::remoting::Exception(errText);
    }
    // Now the current process can close the handles.
  }
  m_neededToClose = neededToClose;
}

void AnonymousPipe::setTimeOut(unsigned int timeOut)
{
  m_timeOut = timeOut;
}
