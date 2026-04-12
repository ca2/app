// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#include "DesktopSelector.h"

namespace subsystem
{

   /**
    * Thread priority enumeration.
    */
   enum THREAD_PRIORITY
   {
      PRIORITY_IDLE,
      PRIORITY_LOWEST,
      PRIORITY_BELOW_NORMAL,
      PRIORITY_NORMAL,
      PRIORITY_ABOVE_NORMAL,
      PRIORITY_HIGHEST,
      PRIORITY_TIME_CRITICAL
   };

      /**
    * Thread class.
    *
    * @fixme some of methods return bool instead of raising exceptions.
    * @fixme some methods seems to be not thread-safe (that uses m_active member).
    * @fixme member of HDESK type in THREAD class???
    */
   class ThreadInterface :
      virtual public ::subsystem::particle_interface<ThreadInterface>
   {
   public:


      //::pointer < Thread > m_pthreadThis;

      /**
       * Creates new thread.
       * @remark thread is suspended by default.
       */
      //Thread();
      /**
       * Deletes thread.
       * @remark does not stops thread execution if it's still running.
       */
      //virtual ~ThreadInterface() = 0;
      /**
       * Waits until thread stops.
       * @return false on error.
       */
      virtual ::e_status wait() = 0;
      /**
       * Suspends thread execution.
       * @return false on error.
       */
      virtual bool suspend() = 0;
      /**
       * Resume thread execution.
       * @return false on error.
       */
      virtual bool resume() = 0;
      /**
       * Terminates thread execution.
       * @remark thread-safe.
       */
      virtual void terminate() = 0;

      /**
       * Checks if thread is not dead.
       * @return true if thread is not dead (still running or suspended).
       */
      virtual bool isActive() const = 0;

      /**
       * Returns thread id.
       */
      virtual ::itask getThreadId() const = 0;

      /**
       * Sets thread priority.
       * @param value thread priority.
       */
      virtual bool setPriority(THREAD_PRIORITY value) = 0;

      /**
       * Suspends the execution of the current thread until the time-out interval elapses.
       * @param millis time to sleep.
       */
      virtual void sleep(const class ::time & time) = 0;

      /**
       * Yield execution to the next ready thread.
       */
      virtual  void yield() = 0;

   //protected:
      /**
       * Returns true if terminate() method was called.
       * @remark thread-safe.
       */
      virtual bool isTerminating() = 0;

      /**
       * Slot of terminate() signal.
       * Method called from terminate() method.
       * Can be overrided by subclasses to gracefully shutdown thread.
       */
      virtual void onTerminate() = 0;

      /**
       * Thread's runnable body.
       */
      virtual void execute() = 0;

   //private:
      /**
       * WinApi thread func.
       */
      //static DWORD WINAPI threadProc(LPVOID pThread);

      // This function calling before call a derived execute() function to
      // perform any additional action.
      virtual void initByDerived() = 0;

   //private:
      /**
       * Win32 thread handle.
       */
      //HANDLE m_hThread;
      /**
       * Thread ID.
       */
      //DWORD m_threadID;
      /**
       * Activity flag.
       */
      //bool m_active;
      /**
       * Terminating flag.
       */
      //volatile bool m_terminated;
   };


   /**
    * Thread class.
    *
    * @fixme some of methods return bool instead of raising exceptions.
    * @fixme some methods seems to be not thread-safe (that uses m_active member).
    * @fixme member of HDESK type in THREAD class???
    */
   class CLASS_DECL_SUBSYSTEM Thread :
      virtual public ::subsystem::composite < ThreadInterface >
   {
   public:


      //::pointer < Thread > m_pthreadThis;

      /**
       * Creates new thread.
       * @remark thread is suspended by default.
       */
      Thread();
      /**
       * Deletes thread.
       * @remark does not stops thread execution if it's still running.
       */
      ~Thread() override;

      /**
       * Waits until thread stops.
       * @return false on error.
       */
      ::e_status wait() override;
      /**
       * Suspends thread execution.
       * @return false on error.
       */
      bool suspend() override;
      /**
       * Resume thread execution.
       * @return false on error.
       */
      bool resume() override;
      /**
       * Terminates thread execution.
       * @remark thread-safe.
       */
      void terminate() override;

      /**
       * Checks if thread is not dead.
       * @return true if thread is not dead (still running or suspended).
       */
      bool isActive() const override;

      /**
       * Returns thread id.
       */
      ::itask getThreadId() const override;

      /**
       * Sets thread priority.
       * @param value thread priority.
       */
      bool setPriority(THREAD_PRIORITY value) override;

      /**
       * Suspends the execution of the current thread until the time-out interval elapses.
       * @param millis time to sleep.
       */
      void sleep(const class ::time & time) override;

      /**
       * Yield execution to the next ready thread.
       */
      void yield() override;

   //protected:
      /**
       * Returns true if terminate() method was called.
       * @remark thread-safe.
       */
      bool isTerminating() override;

      /**
       * Slot of terminate() signal.
       * Method called from terminate() method.
       * Can be overrided by subclasses to gracefully shutdown thread.
       */
      void onTerminate() override;

      /**
       * Thread's runnable body.
       */
      void execute() override;

   //private:
      /**
       * WinApi thread func.
       */
      //static DWORD WINAPI threadProc(LPVOID pThread);

      // This function calling before call a derived execute() function to
      // perform any additional action.
      void initByDerived() override;

   //private:
      /**
       * Win32 thread handle.
       */
      //HANDLE m_hThread;
      /**
       * Thread ID.
       */
      //DWORD m_threadID;
      /**
       * Activity flag.
       */
      //bool m_active;
      /**
       * Terminating flag.
       */
      //volatile bool m_terminated;
   };

   //// __THREAD_H__


} // namespace subsystem


