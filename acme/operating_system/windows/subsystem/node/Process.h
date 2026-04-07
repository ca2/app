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


#include "acme/subsystem/node/Process.h"
#include "acme/operating_system/windows/subsystem/node/ProcessHandle.h"


namespace  windows
{
   namespace subsystem
   {
      /**
       * Enables you to start and stop local processes.
       */
      class CLASS_DECL_ACME Process :
      virtual public ::subsystem::Process
      {
      public:
         /**
          * Creates new Process class instance.
          * @param path full path to file.
          * @param args arguments for application.
          */
         //Process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {});
         Process();
         /**
          * Destroys Process instance.
          * Running process will not be interrupted.
          */
         ~Process() override;


         void initialize_process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {}) override;
         /**
          * Sets executable filename for process.
          * @param path.
          */
         void setFilename(const ::scoped_string & scopedstrPath) override;

         /**
          * Sets arguments for process.
          * @param args.
          */
         void setArguments(const ::scoped_string & scopedstrArgs) override;

         // Sets standard in/out/error handles for the child process.
         void setStandardIoHandles(::subsystem::File * stdIn, ::subsystem::File * stdOut, ::subsystem::File * stdErr) override;

         // If handlesIsInerited is true the handles of the parent process can
         // be used by the child process.
         void setHandleInheritances(bool handlesIsInerited) override;

         /**
          * Starts execution of process.
          * @throws SystemException on error.
          */
         void start() override;

         /**
          * Terminates running process.
          * @throws SystemException on fail.
          */
         void kill() override;

         /**
          * Blocks the current thread of execution until the process has exited.
          */
         void waitForExit() override;

         /**
          * Breaks awaiting caused by waitForExit call.
          */
         void stopWait() override;

         /**
          * Returns exit code of terminated process.
          * @throws SystemException on fail.
          */
          unsigned int getExitCode() override;

         /**
          * Returns the process handle if process already run and zero otherwise.
          */
         ::subsystem::ProcessHandle * getProcessHandle() override;

      //protected:
         /**
          * Returns command line string for process execution.
          * Used to avoid code duplicates.
          */
         ::string getCommandLineString() override;

         // Fills the STARTUPINFO structure.
         // Before to use the STARTUPINFO structure in this class a function
         // must to call this function.
         virtual void getStartupInfo(STARTUPINFO *sti);

         /**
          * Closes WinAPI handles if their are open.
          */
         void cleanup() override;

         ::string m_path;
         ::string m_args;

         ::pointer < ::windows::subsystem::ProcessHandle > m_pprocesshandle;
         HANDLE m_hThread;

         HANDLE m_hStopWait;

         // Standard in/out/error handles for the child process.
         HANDLE m_stdIn;
         HANDLE m_stdOut;
         HANDLE m_stdErr;

         bool m_handlesIsInherited;

      };

      //// __PROCESSMANAGER_H__
   } // namespace  subsystem
} // namespace windows