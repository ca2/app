// from subsystem/thread/Thread.h on 2026-05-17 03:40 by camilo <3ThomasBorregaardSørensen!!
#pragma once


//#include "subsystem/_common_header.h"

//#include "DesktopSelector.h"

//namespace subsystem
//{

class thread_implementation;

//   /**
//    * Thread priority enumeration.
//    */
//   enum THREAD_PRIORITY
//   {
//      PRIORITY_IDLE,
//      PRIORITY_LOWEST,
//      PRIORITY_BELOW_NORMAL,
//      PRIORITY_NORMAL,
//      PRIORITY_ABOVE_NORMAL,
//      PRIORITY_HIGHEST,
//      PRIORITY_TIME_CRITICAL
//   };

      /**
    * Thread class.
    *
    * @fixme some of methods return bool instead of raising exceptions.
    * @fixme some methods seems to be not thread-safe (that uses m_active member).
    * @fixme member of HDESK type in THREAD class???
    */
   class CLASS_DECL_ACME filament :
      virtual public ::object
{
public:
   
   
};
      
//      
//      ::pointer < thread_implementation > m_pthreadimplementation;
//
//
//      //::pointer < Thread > m_pthreadThis;
//
//      /**
//       * Creates new thread.
//       * @remark thread is suspended by default.
//       */
//      Thread();
//      /**
//       * Deletes thread.
//       * @remark does not stops thread execution if it's still running.
//       */
//      ~Thread() override;
//      /**
//       * Suspends thread execution.
//       * @return false on error.
//       */
//      virtual bool suspendThread();
//      /**
//       * Resume thread execution.
//       * @return false on error.
//       */
//      virtual bool resumeThread();
//      /**
//       * Terminates thread execution.
//       * @remark thread-safe.
//       */
//      virtual void setThreadToFinish();
//      
//      
//      
//
//      /**
//       * Checks if thread is not dead.
//       * @return true if thread is not dead (still running or suspended).
//       */
//      virtual bool isThreadActive() const;
//
//      /**
//       * Returns thread id.
//       */
//      virtual ::iptr getThreadId() const;
//
//      /**
//       * Sets thread priority.
//       * @param value thread priority.
//       */
//      virtual bool setThreadPriority(THREAD_PRIORITY value);
//
//      /**
//       * Suspends the execution of the current thread until the time-out interval elapses.
//       * @param time time to sleep.
//       */
//      virtual void threadSleep(const class ::time & time);
//
//      /**
//       * Yield execution to the next ready thread.
//       */
//      virtual  void threadYield();
//
//   //protected:
//      /**
//       * Returns true if terminate() method was called.
//       * @remark thread-safe.
//       */
//      virtual bool isThreadTerminating();
//
//      /**
//       * Slot of terminate() signal.
//       * Method called from terminate() method.
//       * Can be overrided by subclasses to gracefully shutdown thread.
//       */
//      virtual void onTerminateThread();
//
//      /**
//       * Thread's runnable body.
//       */
//      virtual void onRunThread();
//
//   //private:
//      /**
//       * WinApi thread func.
//       */
//      //static DWORD WINAPI threadProc(LPVOID pThread);
//
//      // This function calling before call a derived onRunThread() function to
//      // perform any additional action.
//      virtual void onInitThread();
//      
//      
//      virtual void waitIfSuspended();
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
//
////
////      class CLASS_DECL_SUBSYSTEM ThreadCallback : virtual public Callback<ThreadInterface>
////   {
////   public:
////
////
////      ImplementCallbackø(Thread, thread)
////   };
////   //using ThreadInterface = particle_interface<ThreadInterface>;
//
////   /**
////    * Thread class.
////    *
////    * @fixme some of methods return bool instead of raising exceptions.
////    * @fixme some methods seems to be not thread-safe (that uses m_active member).
////    * @fixme member of HDESK type in THREAD class???
////    */
////   class CLASS_DECL_SUBSYSTEM ThreadComposite :
////      virtual public Composite < ThreadInterface >
////   {
////   public:
////
////
////      ImplementCompositeWithCallbackø(Thread, thread)
////
////
////      //::pointer < Thread > m_pthreadThis;
////
////      /**
////       * Creates new thread.
////       * @remark thread is suspended by default.
////       */
////      //Thread();
////      /**
////       * Deletes thread.
////       * @remark does not stops thread execution if it's still running.
////       */
////      //~Thread() override;
////
////      /**
////       * Waits until thread stops.
////       * @return false on error.
////       */
////      ::e_status wait() override
////      {
////
////          return m_pthread->wait();
////      }
////      /**
////       * Suspends thread execution.
////       * @return false on error.
////       */
////      bool suspendThread() override
////      {
////
////          return m_pthread->suspendThread();
////
////      }
////      /**
////       * Resume thread execution.
////       * @return false on error.
////       */
////      bool resumeThread() override
////      {
////
////          return m_pthread->resumeThread();
////
////      }
////      /**
////       * Terminates thread execution.
////       * @remark thread-safe.
////       */
////      void terminateThread() override
////      {
////
////          m_pthread->terminateThread();
////
////      }
////
////      /**
////       * Checks if thread is not dead.
////       * @return true if thread is not dead (still running or suspended).
////       */
////      bool isThreadActive() const override
////      {
////
////          return m_pthread->isThreadActive();
////
////      }
////
////      /**
////       * Returns thread id.
////       */
////      ::iptr getThreadId() const override
////      {
////
////          return m_pthread->getThreadId();
////
////      }
////
////      /**
////       * Sets thread priority.
////       * @param value thread priority.
////       */
////      bool setThreadPriority(THREAD_PRIORITY value) override
////      {
////
////          return m_pthread->setThreadPriority(value);
////
////      }
////
////      /**
////       * Suspends the execution of the current thread until the time-out interval elapses.
////       * @param time time to sleep.
////       */
////      void threadSleep(const class ::time & time) override
////      {
////
////          m_pthread->threadSleep(time);
////
////      }
////
////      /**
////       * Yield execution to the next ready thread.
////       */
////      void threadYield() override
////      {
////
////          m_pthread->threadYield();
////
////      }
////
////   //protected:
////      /**
////       * Returns true if terminate() method was called.
////       * @remark thread-safe.
////       */
////      bool isThreadTerminating() override
////      {
////
////          return m_pthread->isThreadTerminating();
////
////      }
////
////      /**
////       * Slot of terminate() signal.
////       * Method called from terminate() method.
////       * Can be overrided by subclasses to gracefully shutdown thread.
////       */
////      void onTerminateThread() override
////      {
////
////
////      }
////
////      /**
////       * Thread's runnable body.
////       */
////      void onRunThread() override
////      {
////
////
////      }
////
////   //private:
////      /**
////       * WinApi thread func.
////       */
////      //static DWORD WINAPI threadProc(LPVOID pThread);
////
////      // This function calling before call a derived onRunThread() function to
////      // perform any additional action.
////      void onInitThread() override
////      {
////
////
////      }
////
////   //private:
////      /**
////       * Win32 thread handle.
////       */
////      //HANDLE m_hThread;
////      /**
////       * Thread ID.
////       */
////      //DWORD m_threadID;
////      /**
////       * Activity flag.
////       */
////      //bool m_active;
////      /**
////       * Terminating flag.
////       */
////      //volatile bool m_terminated;
////   };
//
//
////    class CLASS_DECL_SUBSYSTEM ThreadAggregate :
////    virtual public Aggregate< ThreadComposite >
////    {
////    public:
////
////        ImplementBaseø(Thread);
////
////    };
////
////   class CLASS_DECL_SUBSYSTEM Thread :
////   virtual public Object< ThreadAggregate >
////   {
////   public:
////
////
////      ImplementObjectø(Thread)
////
////   };
//


} // namespace subsystem


