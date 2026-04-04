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
#include "acme/_operating_system.h"
#include "NamedPipe.h"
#include "remoting/remoting_common/util/Exception.h"
#include <crtdbg.h>
//#include "remoting/remoting_common/win_system/Environment.h"
#include "remoting/remoting_common/thread/AutoLock.h"

#define MAX_PORTION_SIZE 512 * 1024

NamedPipe::NamedPipe(HANDLE hPipe, unsigned int maxPortionSize, bool asServer)
: Pipe(maxPortionSize),
  m_hPipe(hPipe),
  m_asServer(asServer)
{
}

NamedPipe::~NamedPipe(void)
{
  try {
    close();
  } catch (...) {
  }
}

void NamedPipe::close()
{
  AutoLock al(&m_hPipeMutex);
  if (m_asServer) {
    if (DisconnectNamedPipe(m_hPipe) == 0) {
      DWORD errCode = GetLastError();
      ::string errMess;
      errMess.formatf("DisconnectNamedPipe failed, error code = %u", errCode);
      throw ::remoting::Exception(errMess);
    }
  }

  if (m_hPipe != INVALID_HANDLE_VALUE) {
    CloseHandle(m_hPipe);
    m_hPipe = INVALID_HANDLE_VALUE;
  }
  // Unblock a blocked operation
  m_readEvent.notify();
  m_writeEvent.notify();
}

memsize NamedPipe::defer_write(const void *buffer, memsize len)
{
   return writeByHandle(buffer, len, m_hPipe);
}

size_t NamedPipe::read(void *buffer, size_t len)
{
  return readByHandle(buffer, len, m_hPipe);
}

HANDLE NamedPipe::getHandle() const
{
  return m_hPipe;
}

void NamedPipe::checkPipeHandle()
{
  if (m_hPipe == INVALID_HANDLE_VALUE) {
    throw ::io_exception(error_io, "Invalid pipe handle");
  }
}
