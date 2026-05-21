// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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

#include "acme/parallelization/manual_reset_happening.h"
//#include "subsystem/_common_header.h"

//#include "DesktopSelector.h"

template<typename THREAD>
class scoped_thread
{
public:

   ::pointer<THREAD> m_ptask;

   scoped_thread() :
      scoped_thread(allocateø THREAD)
   {
   }

   scoped_thread(THREAD *ptask) : m_ptask(ptask)
   {
      if (!m_ptask->is_set())
      {

         m_ptask->branch_synchronously();
      }
      
   }

   ~scoped_thread()
   {

      m_ptask->set_finish();

      m_ptask->wait();

   }

   THREAD*operator->()
   {
      return m_ptask;
   }

};

namespace subsystem
{

class thread_implementation;

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
   class CLASS_DECL_SUBSYSTEM Thread :
      virtual public ::task
      //virtual public ::Particle,
      //virtual public ::object
   {
      
//      /**
//       * Waits until thread stops.
//       * @return false on error.
//       */
//      ::e_status wait() override;

   public:
      
      manual_reset_happening m_manualresethappeningLetRun;
      //::pointer < thread_implementation > m_pthreadimplementation;
      std::atomic<bool> m_active { false };


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
      
      
      void destroy() override;
      
      /**
       * Suspends thread execution.
       * @return false on error.
       */
      virtual bool suspendThread();
      /**
       * Resume thread execution.
       * @return false on error.
       */
      virtual bool resumeThread();
      /**
       * Terminates thread execution.
       * @remark thread-safe.
       */
      virtual void setThreadToFinish();
      
      //      /**
      //       * Waits until thread stops.
      //       * @return false on error.
      //       */
      virtual void waitThreadToFinish();

      /**
       * Checks if thread is not dead.
       * @return true if thread is not dead (still running or suspended).
       */
      virtual bool isThreadActive() const;

      /**
       * Returns thread id.
       */
      virtual ::iptr getThreadId() const;

      /**
       * Sets thread priority.
       * @param value thread priority.
       */
      virtual bool setThreadPriority(THREAD_PRIORITY value);

      /**
       * Suspends the execution of the current thread until the time-out interval elapses.
       * @param time time to sleep.
       */
      virtual void threadSleep(const class ::time & time);

      /**
       * Yield execution to the next ready thread.
       */
      virtual  void threadYield();

   //protected:
      /**
       * Returns true if terminate() method was called.
       * @remark thread-safe.
       */
      virtual bool isThreadTerminating();

      /**
       * Slot of terminate() signal.
       * Method called from terminate() method.
       * Can be overrided by subclasses to gracefully shutdown thread.
       */
      virtual void onTermThread();
      
      
      void run() override;

      /**
       * Thread's runnable body.
       */
      virtual void onThreadMain();

   //private:
      /**
       * WinApi thread func.
       */
      //static DWORD WINAPI threadProc(LPVOID pThread);

      // This function calling before call a derived onThreadMain() function to
      // perform any additional action.
      virtual void onInitThread();
      
      
      virtual void waitIfSuspended();

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

//
//      class CLASS_DECL_SUBSYSTEM ThreadCallback : virtual public Callback<ThreadInterface>
//   {
//   public:
//
//
//      ImplementCallbackø(Thread, thread)
//   };
//   //using ThreadInterface = particle_interface<ThreadInterface>;

//   /**
//    * Thread class.
//    *
//    * @fixme some of methods return bool instead of raising exceptions.
//    * @fixme some methods seems to be not thread-safe (that uses m_active member).
//    * @fixme member of HDESK type in THREAD class???
//    */
//   class CLASS_DECL_SUBSYSTEM ThreadComposite :
//      virtual public Composite < ThreadInterface >
//   {
//   public:
//
//
//      ImplementCompositeWithCallbackø(Thread, thread)
//
//
//      //::pointer < Thread > m_pthreadThis;
//
//      /**
//       * Creates new thread.
//       * @remark thread is suspended by default.
//       */
//      //Thread();
//      /**
//       * Deletes thread.
//       * @remark does not stops thread execution if it's still running.
//       */
//      //~Thread() override;
//
//      /**
//       * Waits until thread stops.
//       * @return false on error.
//       */
//      ::e_status wait() override
//      {
//
//          return m_pthread->wait();
//      }
//      /**
//       * Suspends thread execution.
//       * @return false on error.
//       */
//      bool suspendThread() override
//      {
//
//          return m_pthread->suspendThread();
//
//      }
//      /**
//       * Resume thread execution.
//       * @return false on error.
//       */
//      bool resumeThread() override
//      {
//
//          return m_pthread->resumeThread();
//
//      }
//      /**
//       * Terminates thread execution.
//       * @remark thread-safe.
//       */
//      void terminateThread() override
//      {
//
//          m_pthread->terminateThread();
//
//      }
//
//      /**
//       * Checks if thread is not dead.
//       * @return true if thread is not dead (still running or suspended).
//       */
//      bool isThreadActive() const override
//      {
//
//          return m_pthread->isThreadActive();
//
//      }
//
//      /**
//       * Returns thread id.
//       */
//      ::iptr getThreadId() const override
//      {
//
//          return m_pthread->getThreadId();
//
//      }
//
//      /**
//       * Sets thread priority.
//       * @param value thread priority.
//       */
//      bool setThreadPriority(THREAD_PRIORITY value) override
//      {
//
//          return m_pthread->setThreadPriority(value);
//
//      }
//
//      /**
//       * Suspends the execution of the current thread until the time-out interval elapses.
//       * @param time time to sleep.
//       */
//      void threadSleep(const class ::time & time) override
//      {
//
//          m_pthread->threadSleep(time);
//
//      }
//
//      /**
//       * Yield execution to the next ready thread.
//       */
//      void threadYield() override
//      {
//
//          m_pthread->threadYield();
//
//      }
//
//   //protected:
//      /**
//       * Returns true if terminate() method was called.
//       * @remark thread-safe.
//       */
//      bool isThreadTerminating() override
//      {
//
//          return m_pthread->isThreadTerminating();
//
//      }
//
//      /**
//       * Slot of terminate() signal.
//       * Method called from terminate() method.
//       * Can be overrided by subclasses to gracefully shutdown thread.
//       */
//      void onTermThread() override
//      {
//
//
//      }
//
//      /**
//       * Thread's runnable body.
//       */
//      void onThreadMain() override
//      {
//
//
//      }
//
//   //private:
//      /**
//       * WinApi thread func.
//       */
//      //static DWORD WINAPI threadProc(LPVOID pThread);
//
//      // This function calling before call a derived onThreadMain() function to
//      // perform any additional action.
//      void onInitThread() override
//      {
//
//
//      }
//
//   //private:
//      /**
//       * Win32 thread handle.
//       */
//      //HANDLE m_hThread;
//      /**
//       * Thread ID.
//       */
//      //DWORD m_threadID;
//      /**
//       * Activity flag.
//       */
//      //bool m_active;
//      /**
//       * Terminating flag.
//       */
//      //volatile bool m_terminated;
//   };


//    class CLASS_DECL_SUBSYSTEM ThreadAggregate :
//    virtual public Aggregate< ThreadComposite >
//    {
//    public:
//
//        ImplementBaseø(Thread);
//
//    };
//
//   class CLASS_DECL_SUBSYSTEM Thread :
//   virtual public Object< ThreadAggregate >
//   {
//   public:
//
//
//      ImplementObjectø(Thread)
//
//   };



} // namespace subsystem


