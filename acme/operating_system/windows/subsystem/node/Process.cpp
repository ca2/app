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
#include "acme/subsystem/node/SystemException.h"
#include "Process.h"
//#include "port/base/iconv/lib/stringprep.h"


namespace windows
{
   namespace subsystem
   {


      Process::Process()
      : //m_hProcess(0),
        m_hThread(0),
        m_handlesIsInherited(false),
        m_hStopWait(0),
        m_stdIn(0),
        m_stdOut(0),
        m_stdErr(0)
      {
         //setFilename(path);
         //setArguments(scopedstrArgs);

         m_hStopWait = CreateEvent(0, FALSE, FALSE, 0);
      }

      Process::~Process()
      {
         cleanup();

         if (m_hStopWait) {
            CloseHandle(m_hStopWait);
         }
      }


      void Process::initialize_process(const ::file::path &path, const ::scoped_string &scopedstrArgs)
      {
         setFilename(path);
         setArguments(scopedstrArgs);

         //m_hStopWait = CreateEvent(0, FALSE, FALSE, 0);
      }


      void Process::setFilename(const ::scoped_string & scopedstrPath)
      {
         m_path= scopedstrPath;
      }

      void Process::setArguments(const ::scoped_string & scopedstrArgs)
      {
         m_args= scopedstrArgs;
      }

      void Process::setStandardIoHandles(::subsystem::File * pfileStdIn, ::subsystem::File * pfileStdOut, ::subsystem::File * pfileStdErr)
      {
         m_stdIn = pfileStdIn;
         m_stdOut = pfileStdOut;
         m_stdErr = pfileStdErr;
      }

      void Process::setHandleInheritances(bool handlesIsInerited)
      {
         m_handlesIsInherited = handlesIsInerited;
      }

      void Process::getStartupInfo(STARTUPINFO *sti)
      {
         ZeroMemory(sti, sizeof(STARTUPINFO));
         sti->cb = sizeof(STARTUPINFO);
         sti->hStdError = m_stdErr;
         sti->hStdInput = m_stdIn;
         sti->hStdOutput = m_stdOut;
         if (sti->hStdError != 0 || sti->hStdInput != 0 || sti->hStdOutput != 0) {
            sti->dwFlags |= STARTF_USESTDHANDLES;
         }
      }

      void Process::start()
      {
         cleanup();

         STARTUPINFO sti;
         getStartupInfo(&sti);
         PROCESS_INFORMATION pi;

         ::string commandLine = getCommandLineString();

         _ASSERT(!commandLine.is_empty());
         if (CreateProcess(NULL, (LPTSTR) ::wstring(commandLine).c_str(),
                           NULL, NULL, m_handlesIsInherited, NULL, NULL, NULL,
                           &sti, &pi) == 0) {
            throw ::subsystem::SystemException();
                           }

         m_hThread = pi.hThread;
         m_pprocesshandle = create_newø<ProcessHandle>();
         m_pprocesshandle->m_hProcess= pi.hProcess;
      }

      void Process::kill()
      {
         if (TerminateProcess(m_pprocesshandle->m_hProcess, 0) == 0) {
            throw ::subsystem::SystemException();
         }
      }

      void Process::waitForExit()
      {
         HANDLE handleArray[2] = { m_pprocesshandle->m_hProcess, m_hStopWait };

         WaitForMultipleObjects(2, handleArray, FALSE, INFINITE);
      }

      void Process::stopWait()
      {
         SetEvent(m_hStopWait);
      }

      unsigned int Process::getExitCode()
      {
         DWORD dwExitCode;

         if (GetExitCodeProcess(m_pprocesshandle->m_hProcess, &dwExitCode) == 0) {
            throw ::subsystem::SystemException();
         }

         return dwExitCode;
      }

      ::subsystem::ProcessHandle * Process::getProcessHandle()
      {
         return m_pprocesshandle;
      }

      ::string Process::getCommandLineString()
      {
         ::string result;

         if (m_args.is_empty()) {
            return m_path;
         }

         result.formatf("{} {}", m_path, m_args);

         return result;
      }

      void Process::cleanup()
      {
         if (m_pprocesshandle->m_hProcess) {
            CloseHandle(m_pprocesshandle->m_hProcess);
            m_pprocesshandle->m_hProcess = 0;
         }
         if (m_hThread) {
            CloseHandle(m_hThread);
            m_hThread = 0;
         }
      }

   }//namespace subsystem
} // namespace windows