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


#include "subsystem/_common_header.h"



//#include "SystemException.h"

namespace subsystem
{



      /**
    * Enables you to start and stop local processes.
    */
   class ProcessInterface :
      virtual public ::Particle
   {
   public:


      /**
       * Creates new Process class instance.
       * @param path full path to file.
       * @param args arguments for application.
       */
      //Process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {});
// Process();
      /**
       * Destroys Process instance.
       * Running process will not be interrupted.
       */
      //virtual ~ProcessInterface() = 0;


      virtual void initialize_process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {}) = 0;
      /**
       * Sets executable filename for process.
       * @param path.
       */
      virtual void setFilename(const ::scoped_string & scopedstrPath) = 0;

      /**
       * Sets arguments for process.
       * @param args.
       */
      virtual void setArguments(const ::scoped_string & scopedstrArgs) = 0;

      // Sets standard in/out/error handles for the child process.
      virtual void setStandardIoHandles(::subsystem::FileInterface * stdIn, ::subsystem::FileInterface * stdOut, ::subsystem::FileInterface * stdErr) = 0;

      // If handlesIsInerited is true the handles of the parent process can
      // be used by the child process.
      virtual void setHandleInheritances(bool handlesIsInerited) = 0;

      /**
       * Starts execution of process.
       * @throws SystemException on error.
       */
      virtual void start() = 0;

      /**
       * Terminates running process.
       * @throws SystemException on fail.
       */
      virtual void kill() = 0;

      /**
       * Blocks the current thread of execution until the process has exited.
       */
      virtual void waitForExit() = 0;

      /**
       * Breaks awaiting caused by waitForExit call.
       */
      virtual void stopWait() = 0;

      /**
       * Returns exit code of terminated process.
       * @throws SystemException on fail.
       */
      virtual unsigned int getExitCode() = 0;

      /**
       * Returns the process handle if process already run and zero otherwise.
       */
      virtual ProcessHandleInterface * getProcessHandle() = 0;

   //protected:
      /**
       * Returns command line string for process execution.
       * Used to avoid code duplicates.
       */
      virtual ::string getCommandLineString() = 0;

      // Fills the STARTUPINFO structure.
      // Before to use the STARTUPINFO structure in this class a function
      // must to call this function.
      //void getStartupInfo(STARTUPINFO *sti);

      /**
       * Closes WinAPI handles if their are open.
       */
      virtual void cleanup() = 0;

      // ::string m_path;
      // ::string m_args;
      //
      // HANDLE m_hProcess;
      // HANDLE m_hThread;
      //
      // HANDLE m_hStopWait;
      //
      // // Standard in/out/error handles for the child process.
      // HANDLE m_stdIn;
      // HANDLE m_stdOut;
      // HANDLE m_stdErr;
      //
      // bool m_handlesIsInherited;
   };


    //using ProcessInterface = particle_interface<ProcessInterface>;

   /**
    * Enables you to start and stop local processes.
    */
   class CLASS_DECL_SUBSYSTEM ProcessComposite :
   virtual public Composite<ProcessInterface>
   {
   public:


       ImplementCompositeø(Process, process )
      /**
       * Creates new Process class instance.
       * @param path full path to file.
       * @param args arguments for application.
       */
      //Process(const ::file::path &path = {}, const ::scoped_string &scopedstrArgs = {});

      //Process();

      /**
       * Destroys Process instance.
       * Running process will not be interrupted.
       */
      //~Process() override;


          void initialize_process(const ::file::path& path = {}, const ::scoped_string& scopedstrArgs = {}) override
       {

          m_pprocess->initialize_process(path, scopedstrArgs);

       }


      /**
       * Sets executable filename for process.
       * @param path.
       */
       void setFilename(const ::scoped_string& scopedstrPath) override
       {

          m_pprocess->setFilename(scopedstrPath);

      }

      /**
       * Sets arguments for process.
       * @param args.
       */
       void setArguments(const ::scoped_string& scopedstrArgs) override
       {

          m_pprocess->setArguments(scopedstrArgs);

      }

      // Sets standard in/out/error handles for the child process.
       void setStandardIoHandles(::subsystem::FileInterface* stdIn, ::subsystem::FileInterface* stdOut, ::subsystem::FileInterface* stdErr) override
       {

          m_pprocess->setStandardIoHandles(stdIn, stdOut, stdErr);

      }

      // If handlesIsInerited is true the handles of the parent process can
      // be used by the child process.
       void setHandleInheritances(bool handlesIsInerited) override
       {

          m_pprocess->setHandleInheritances(handlesIsInerited);

      }

      /**
       * Starts execution of process.
       * @throws SystemException on error.
       */
       void start() override
       {

          m_pprocess->start();

      }

      /**
       * Terminates running process.
       * @throws SystemException on fail.
       */
       void kill() override
       {

          m_pprocess->kill();

      }

      /**
       * Blocks the current thread of execution until the process has exited.
       */
       void waitForExit() override
       {

          m_pprocess->waitForExit();

      }

      /**
       * Breaks awaiting caused by waitForExit call.
       */
      void stopWait() override
      {

         m_pprocess->stopWait();

      }

      /**
       * Returns exit code of terminated process.
       * @throws SystemException on fail.
       */
      unsigned int getExitCode() override
      {

         return m_pprocess->getExitCode();

      }

      /**
       * Returns the process handle if process already run and zero otherwise.
       */
      ProcessHandleInterface* getProcessHandle() override
      {

         return m_pprocess->getProcessHandle();

      }

   //protected:
      /**
       * Returns command line string for process execution.
       * Used to avoid code duplicates.
       */
      ::string getCommandLineString() override
      {

         return m_pprocess->getCommandLineString();

      }

      // Fills the STARTUPINFO structure.
      // Before to use the STARTUPINFO structure in this class a function
      // must to call this function.
      //void getStartupInfo(STARTUPINFO *sti);

      /**
       * Closes WinAPI handles if their are open.
       */
      void cleanup() override
      {

         return m_pprocess->cleanup();

      }

      // ::string m_path;
      // ::string m_args;
      //
      // HANDLE m_hProcess;
      // HANDLE m_hThread;
      //
      // HANDLE m_hStopWait;
      //
      // // Standard in/out/error handles for the child process.
      // HANDLE m_stdIn;
      // HANDLE m_stdOut;
      // HANDLE m_stdErr;
      //
      // bool m_handlesIsInherited;
   };


    class CLASS_DECL_SUBSYSTEM ProcessAggregate :
    virtual public Aggregate< ProcessComposite >
    {
    public:

        ImplementBaseø(Process);

    };


   class CLASS_DECL_SUBSYSTEM Process :
 virtual public Object < ProcessAggregate >
   {
   public:

   };



} // namespace subsystem


