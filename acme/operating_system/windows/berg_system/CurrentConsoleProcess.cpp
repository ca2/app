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
#include "CurrentConsoleProcess.h"

#include "remoting/remoting_common/win_system/WinStaLibrary.h"
//#include "remoting/remoting_common/win_system/Environment.h"
#include "remoting/remoting_common/win_system/SystemException.h"
#include "remoting/remoting_common/win_system/Workstation.h"
#include "remoting/remoting_common/win_system/WTS.h"

CurrentConsoleProcess::CurrentConsoleProcess(LogWriter *log, bool connectRdpSession, const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrArgs)
: Process(scopedstrPath, scopedstrArgs),
  m_log(log),
  m_connectRdpSession(connectRdpSession)
{
}

CurrentConsoleProcess::~CurrentConsoleProcess()
{
}

void CurrentConsoleProcess::start()
{
  cleanup();

  m_log->information("Try to start \"{} {}\" process",
    m_path,
    m_args);

  DWORD uiAccess  = 1; // Nonzero enables UI control
  PROCESS_INFORMATION pi;
  STARTUPINFO sti;
  getStartupInfo(&sti);

  m_log->debug("sti: cb = {}, hStdError = %p, hStdInput = %p,"
             " hStdOutput = %p, dwFlags = %u",
             (unsigned int)sti.cb,
             (void *)sti.hStdError,
             (void *)sti.hStdInput,
             (void *)sti.hStdOutput,
             (unsigned int)sti.dwFlags);

  try {
    HANDLE userToken = WTS::duplicateCurrentProcessUserToken(m_connectRdpSession, m_log);

    ::string commandLine = getCommandLineString();

    m_log->debug("Try CreateProcessAsUser({} 0, {}, 0, 0, {}, NORMAL_PRIORITY_CLASS, 0, 0,"
               " sti, pi)",
               (void *)userToken, commandLine,
               (int)m_handlesIsInherited);
    if (CreateProcessAsUser(userToken, 0, (LPTSTR)::wstring(commandLine).c_str(),
      0, 0, m_handlesIsInherited, NORMAL_PRIORITY_CLASS, 0, 0, &sti,
      &pi) == 0) {
        throw SystemException();
    }
    m_log->information("Created \"{}\" process", commandLine);
    //
    // FIXME: Leak.
    //
    CloseHandle(userToken);
  } catch (SystemException &sysEx) {
    m_log->error("Failed to start process with {} error", sysEx.getErrorCode());
    throw;
  }

  m_hThread = pi.hThread;
  m_hProcess = pi.hProcess;
}
