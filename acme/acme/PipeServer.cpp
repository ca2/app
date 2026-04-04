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
#include "PipeServer.h"

#include "acme/platform/node.h"
#include "remoting/remoting_common/util/Exception.h"
//#include "Environment.h"

DynamicLibrary* PipeServer::m_kernel32Library = 0;
pGetNamedPipeClientProcessId PipeServer::m_GetNamedPipeClientProcessId = 0;
volatile bool PipeServer::m_initialized = false;

PipeServer::PipeServer(const ::scoped_string & scopedstrName, unsigned int bufferSize,
                       SecurityAttributes *secAttr,
                       DWORD milliseconds)
: m_milliseconds(milliseconds),
  m_secAttr(secAttr),
  m_serverPipe(INVALID_HANDLE_VALUE),
  m_bufferSize(bufferSize)
{
  if (!m_initialized) {
    initialize();
  }

  m_pipeName.format("\\\\.\\pipe\\{}", scopedstrName);

  createServerPipe();
}

void PipeServer::createServerPipe()
{
  DWORD openMode = PIPE_ACCESS_DUPLEX |         // read/write access
                   FILE_FLAG_OVERLAPPED;        // overlapped mode

  DWORD pipeMode = PIPE_TYPE_BYTE |             // scopedstrMessage type pipe
                   PIPE_READMODE_BYTE |         // scopedstrMessage-read mode
                   PIPE_WAIT;                   // blocking mode
  if (::system()->node()->_windows_isVistaOrLater()) {
    pipeMode |= PIPE_REJECT_REMOTE_CLIENTS;     // local only
  }
  m_serverPipe = CreateNamedPipe(::wstring(m_pipeName),   // pipe name
                                 openMode,
                                 pipeMode,
                                 PIPE_UNLIMITED_INSTANCES, // max. instances
                                 m_bufferSize,             // output buffer size
                                 m_bufferSize,             // input buffer size
                                 0,                        // client time-out
                                 m_secAttr != 0 ?          // security attributes
                                 m_secAttr->getSecurityAttributes() : 0
                                 );
  if (m_serverPipe == INVALID_HANDLE_VALUE) {
    ::string errMess;
    errMess.formatf("CreateNamedPipe failed, error code = {}", GetLastError());
    throw ::remoting::Exception(errMess);
  }
}

NamedPipe *PipeServer::accept()
{
  if (m_serverPipe == INVALID_HANDLE_VALUE) {
    createServerPipe();
  }

  OVERLAPPED overlapped;
  memset(&overlapped, 0, sizeof(OVERLAPPED));
  overlapped.hEvent = m_winEvent.getHandle();

  if (ConnectNamedPipe(m_serverPipe, &overlapped)) {
    // In success the overlapped ConnectNamedPipe() function must
    // return zero.
    int errCode = GetLastError();
    ::string errMess;
    errMess.formatf("ConnectNamedPipe failed, error code = {}", errCode);
    throw ::remoting::Exception(errMess);
  } else {
    int errCode = GetLastError();
    switch(errCode) {
    case ERROR_PIPE_CONNECTED:
      break;
    case ERROR_IO_PENDING:
      m_winEvent.waitForEvent(m_milliseconds);
      DWORD cbRet; // Fake
      if (!GetOverlappedResult(m_serverPipe, &overlapped, &cbRet, FALSE)) {
        int errCode = GetLastError();
        ::string errMess;
        errMess.formatf("GetOverlappedResult() failed after the "
                       "ConnectNamedPipe() call, error code = {}", errCode);
        throw ::remoting::Exception(errMess);
      }
      break;
    default:
      ::string errMess;
      errMess.formatf("ConnectNamedPipe failed, error code = {}", errCode);
      throw ::remoting::Exception(errMess);
    }
  }

  if (!checkOtherSideBinaryName(m_serverPipe)) {
    throw ::remoting::Exception("Pipe client process filename differs from current process");
  }

  // delete is inside ~NamedPipeTransport()
  NamedPipe *result = new NamedPipe(m_serverPipe, m_bufferSize, true);

  m_serverPipe = INVALID_HANDLE_VALUE;

  return result;
}

void PipeServer::close()
{
  /*if (m_isConnected) {
    if (DisconnectNamedPipe(hPipe)) {
      m_isConnected = false;
    } else {
      int errCode = GetLastError();
      ::string errMess;
      errMess.formatf("DisconnectNamedPipe failed, error code = {}", errCode);
      throw ::remoting::Exception(errMess);
    }
  }*/
  m_winEvent.notify();
}

PipeServer::~PipeServer()
{
  close();
}

void PipeServer::closeConnection()
{
}

void PipeServer::waitForConnect(DWORD milliseconds)
{
}

void PipeServer::initialize()
{
  if (!::system()->node()->_windows_isVistaOrLater()) {
    return;
  }
  try {
    m_kernel32Library = new DynamicLibrary("Kernel32.dll");
    m_GetNamedPipeClientProcessId = (pGetNamedPipeClientProcessId)m_kernel32Library->getProcAddress("GetNamedPipeClientProcessId");
  }
  catch (...) {
    return;
  }
  m_initialized = true;
}

bool PipeServer::checkOtherSideBinaryName(HANDLE hPipe)
{
  if (!m_initialized)
    return true;

  ULONG pid;

  // Vista or higher
  if (!m_GetNamedPipeClientProcessId(hPipe, &pid)) { 
    return true;
  }

  WCHAR clientName[MAX_PATH] = {};
  WCHAR serverName[MAX_PATH] = {};

  HANDLE client = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
  if (0 == client) {
    return true;
  }

  if (0 == GetProcessImageFileNameW(client, clientName, sizeof(clientName))) {
    CloseHandle(client);
    return true;
  }
  CloseHandle(client);

  HANDLE server = GetCurrentProcess();
  if (0 == server) {
    return true;
  }
  if (0 == GetProcessImageFileNameW(server, serverName, sizeof(serverName))) {
    CloseHandle(server);
    return true;
  }
  CloseHandle(server);

  if (std::equal(serverName, serverName + MAX_PATH, clientName)) {
    return true;
  }
  return false;
}
