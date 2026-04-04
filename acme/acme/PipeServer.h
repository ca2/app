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

#pragma once


#include "remoting/remoting_common/util/CommonHeader.h"

#include "NamedPipe.h"
#include "remoting/remoting_common/thread/LocalMutex.h"
#include "SecurityAttributes.h"
#include "DynamicLibrary.h"

typedef BOOL(WINAPI* pGetNamedPipeClientProcessId)(HANDLE Pipe, PULONG ClientProcessId);

/**
 * Server fabric of pipes.
 *
 * @author yuri, enikey.
 * @fixme not thread-safe, undone, strange code inside.
 */
class CLASS_DECL_REMOTING_COMMON PipeServer
{
public:
  /**
   * Creates new pipe server ready to accept connections.
   *
   * @param pipeName name of pipe to bind.
   * @throws PipeException on fail.
   *
   * @fixme stub.
   */
  PipeServer(const ::scoped_string & scopedstrName, unsigned int bufferSize,
             SecurityAttributes *secAttr = 0,
             DWORD milliseconds = INFINITE);
  /**
   * Destroys pipe server.
   */
  virtual ~PipeServer();

  /**
   * Waits until pipe client connects.
   * @return connected pipe.
   * @throws PipeException on fail.
   * @note accept() method can be breaked by call of close() method.
   *
   * @fixme stub.
   */
  NamedPipe *accept();

  /**
   * Closes pipe server.
   * @throws PipeException on fail.
   */
  void close();

  /**
   * @deprecated.
   */
  void waitForConnect(DWORD milliseconds = INFINITE);
  /**
   * @deprecated.
   */
  virtual void closeConnection();

private:
  void createServerPipe();

  // returns True on every error 
  bool checkOtherSideBinaryName(HANDLE hPipe);

  // loads GetNamedPipeClientProcessId (Vista or later) from kernel32
  static void initialize();
  static volatile bool m_initialized;

private:
  static DynamicLibrary* m_kernel32Library;
  static pGetNamedPipeClientProcessId m_GetNamedPipeClientProcessId;

private:
  ::string m_pipeName;
  WindowsEvent m_winEvent;
  DWORD m_milliseconds;
  SecurityAttributes *m_secAttr;
  HANDLE m_serverPipe;
  unsigned int m_bufferSize;
};

//// __PIPESERVER_H__
