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
#include "PipeClient.h"
#include "remoting/remoting_common/util/Exception.h"

PipeClient::PipeClient()
{
}

NamedPipe *PipeClient::connect(const ::scoped_string & scopedstrName, unsigned int maxPortionSize)
{
  ::string pipeName;
  pipeName.formatf("\\\\.\\pipe\\{}", ::string(scopedstrName).c_str());

  HANDLE hPipe;
  hPipe = CreateFile(::wstring(pipeName),  // pipe name
                     GENERIC_READ |         // read and write access
                     GENERIC_WRITE,
                     0,                     // no sharing
                     NULL,                  // default security attributes
                     OPEN_EXISTING,         // opens existing pipe
                     FILE_FLAG_OVERLAPPED,  // asynchronous mode
                     NULL);                 // no template file

  if (hPipe == INVALID_HANDLE_VALUE) {
    int errCode = GetLastError();
    ::string errMess;
    errMess.formatf("Connect to pipe server failed, error code = {}", errCode);
    throw ::remoting::Exception(errMess);
  }

  DWORD dwMode = PIPE_READMODE_BYTE;
  if (!SetNamedPipeHandleState(hPipe,   // pipe handle
                               &dwMode,   // new pipe mode
                               NULL,      // don't set maximum bytes
                               NULL)      // don't set maximum time
                               ) {
    int errCode = GetLastError();
    ::string errMess;
    errMess.formatf("SetNamedPipeHandleState failed, error code = {}", errCode);
    throw ::remoting::Exception(errMess);
  }

  return new NamedPipe(hPipe, maxPortionSize, false);
}
