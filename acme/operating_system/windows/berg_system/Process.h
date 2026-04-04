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

#include "SystemException.h"

/**
 * Enables you to start and stop local processes.
 */
class CLASS_DECL_REMOTING_COMMON Process
{
public:
  /**
   * Creates new Process class instance.
   * @param path full path to file.
   * @param args arguments for application.
   */
   Process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {});

  /**
   * Destroys Process instance.
   * Running process will not be interrupted.
   */
  virtual ~Process();

  /**
   * Sets executable filename for process.
   * @param path.
   */
  void setFilename(const ::scoped_string & scopedstrPath);

  /**
   * Sets arguments for process.
   * @param args.
   */
  void setArguments(const ::scoped_string & scopedstrArgs);

  // Sets standard in/out/error handles for the child process.
  void setStandardIoHandles(HANDLE stdIn, HANDLE stdOut, HANDLE stdErr);

  // If handlesIsInerited is true the handles of the parent process can
  // be used by the child process.
  void setHandleInheritances(bool handlesIsInerited);

  /**
   * Starts execution of process.
   * @throws SystemException on error.
   */
  virtual void start();

  /**
   * Terminates running process.
   * @throws SystemException on fail.
   */
  virtual void kill();

  /**
   * Blocks the current thread of execution until the process has exited.
   */
  void waitForExit();

  /**
   * Breaks awaiting caused by waitForExit call.
   */
  void stopWait();

  /**
   * Returns exit code of terminated process.
   * @throws SystemException on fail.
   */
  DWORD getExitCode();

  /**
   * Returns the process handle if process already run and zero otherwise.
   */
  HANDLE getProcessHandle();

protected:
  /**
   * Returns command line string for process execution.
   * Used to avoid code duplicates.
   */
  ::string getCommandLineString();

  // Fills the STARTUPINFO structure.
  // Before to use the STARTUPINFO structure in this class a function
  // must to call this function.
  void getStartupInfo(STARTUPINFO *sti);

  /**
   * Closes WinAPI handles if their are open.
   */
  void cleanup();

  ::string m_path;
  ::string m_args;

  HANDLE m_hProcess;
  HANDLE m_hThread;

  HANDLE m_hStopWait;

  // Standard in/out/error handles for the child process.
  HANDLE m_stdIn;
  HANDLE m_stdOut;
  HANDLE m_stdErr;

  bool m_handlesIsInherited;
};

//// __PROCESSMANAGER_H__
