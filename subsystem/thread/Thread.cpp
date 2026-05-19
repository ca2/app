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
#include "framework.h"
#include "Thread.h"
//#include "critical_section_lock.h"
#include "subsystem/platform/Exception.h"

//#ifdef PARALLELIZATION_PTHREAD
//#include "Thread_pthread.h"
//#endif

namespace subsystem
{

   Thread::Thread()
   {

      //::get_task()->add_task(this);

      m_manualresethappeningLetRun.clear();
      
      auto ptaskParent = ::get_task();

      if (::is_null(ptaskParent))
      {

         throw ::exception(error_wrong_state);

      }
      
      initialize(ptaskParent);
      
      branch();

      //m_pthreadimplementation = allocateø thread_implementation(this);
      
      
   //
   //    pthread_mutex_init(
   //        &m_pthreadimplementation->m_suspendMutex,
   //        nullptr);
   //
   //    pthread_cond_init(
   //        &m_pthreadimplementation->m_suspendCond,
   //        nullptr);
   //
   //    pthread_create(
   //        &m_pthreadimplementation->m_thread,
   //        nullptr,
   //        &Thread::threadProc,
   //        this);
   //
   //   m_pthreadimplementation->m_threadID =
   //        (::iptr)m_thread;
   }


Thread::~Thread()
{
//    pthread_mutex_destroy(
//        &m_pthreadimplementation->m_suspendMutex);
//
//    pthread_cond_destroy(
//        &m_pthreadimplementation->m_suspendCond);
}


void Thread::destroy()
{
   
   ::task::destroy();
   
//   if (isThreadActive()) {
//      setThreadToFinish();
//      waitThreadToFinish()
//   }

   
}


void Thread::run()
{
   
   m_active = true;
   
   waitIfSuspended();

   try
   {
      
      onInitThread();
      
      onThreadMain();
      
   }
   catch (...)
   {
      
   }
   
   try
   {
      
      onTermThread();
      
   }
   catch(...)
   {
      
      
   }
   
   m_active = false;
   
   //        _this->onThreadMain();
   //    }
   //    catch (...)
   //    {
   //    }
}

//void* Thread::threadProc(void* pThread)
//{
//    Thread* _this =
//        (Thread*)pThread;
//
//
//
//
//    _this->m_pthreadimplementation->m_active = true;
//
//    // start suspended
//    _this->waitIfSuspended();
//
//    try
//    {
//        _this->onInitThread();
//        _this->onThreadMain();
//    }
//    catch (...)
//    {
//    }
//
//    _this->m_pthreadimplementation->m_active = false;
//   _this->m_pobjectParentTask->erase_task_and_set_task_new_parent(_this, nullptr);
//
//
//    return nullptr;
//}


void Thread::waitIfSuspended()
{
   
   m_manualresethappeningLetRun.wait();
   //m_pthreadimplementation->waitIfSuspended();
//    pthread_mutex_lock(
//        &m_pthreadimplementation->m_suspendMutex);
//
//    while (m_suspended &&
//           !m_pthreadimplementation->m_terminated)
//    {
//        pthread_cond_wait(
//            &m_pthreadimplementation->m_suspendCond,
//            &m_pthreadimplementation->m_suspendMutex);
//    }
//
//    pthread_mutex_unlock(
//        &m_pthreadimplementation->m_suspendMutex);
}


void Thread::onInitThread()
{
   
}


void Thread::waitThreadToFinish()
{
//   return m_pthreadimplementation->wait();
//    if (m_pthreadimplementation->m_active)
//    {
//        return pthread_join(
//                            m_pthreadimplementation->m_thread,
//            nullptr) == 0
//                ? ::success
//                : error_failed;
//    }
//
    //return ::success;
}


bool Thread::suspendThread()
{
   m_manualresethappeningLetRun.clear();
//return   m_pthreadimplementation->suspendThread();
   //m_pthreadimplementation->m_suspended = true;
    return true;
}


bool Thread::resumeThread()
{
   
   m_manualresethappeningLetRun.set_happening();
   //return m_pthreadimplementation->resumeThread();
//    pthread_mutex_lock(
//        &m_pthreadimplementation->m_suspendMutex);
//
//   m_pthreadimplementation->m_suspended = false;
//
//    pthread_cond_signal(
//        &m_pthreadimplementation->m_suspendCond);
//
//    pthread_mutex_unlock(
//        &m_pthreadimplementation->m_suspendMutex);
//
    return true;
}


void Thread::setThreadToFinish()
{
   set_finish();
   //m_pthreadimplementation->terminateThread();
//   m_pthreadimplementation->m_terminated = true;
//
//    resumeThread();
//
//    onTermThread();
}


bool Thread::isThreadActive() const
{
   return ::task::is_task_set2();
   //return m_pthreadimplementation->isThreadActive();
    //return m_pthreadimplementation->m_active;
}


::iptr Thread::getThreadId() const
{
    //return m_pthreadimplementation->m_threadID;
   return ::task::m_itask;
}


bool Thread::setThreadPriority(
    ::subsystem::THREAD_PRIORITY value)
{
   throw "todo";
   return false;
   //return m_pthreadimplementation->setThreadPriority(value);
//    int policy;
//    sched_param param;
//
//    pthread_getschedparam(
//                          m_pthreadimplementation->m_thread,
//        &policy,
//        &param);
//
//    int minPriority =
//        sched_get_priority_min(policy);
//
//    int maxPriority =
//        sched_get_priority_max(policy);
//
//    int priority =
//        (minPriority + maxPriority) / 2;
//
//    switch (value)
//    {
//    case ::subsystem::PRIORITY_IDLE:
//        priority = minPriority;
//        break;
//
//    case ::subsystem::PRIORITY_TIME_CRITICAL:
//        priority = maxPriority;
//        break;
//
//    default:
//        break;
//    }
//
//    param.sched_priority = priority;
//
//    return pthread_setschedparam(
//                                 m_pthreadimplementation->m_thread,
//        policy,
//        &param) == 0;
}


void Thread::threadSleep(
    const class ::time& time)
{
   preempt(time);
//   m_pthreadimplementation->threadSleep(time);
//    usleep(
//        (useconds_t)
//        time.integral_microsecond());
}


void Thread::threadYield()
{
#ifdef PARALLELIZATION_PTHREAD
    sched_yield();
#endif
   //m_pthreadimplementation->threadYield();
}


bool Thread::isThreadTerminating()
{
    //return m_pthreadimplementation->isThreadTerminating();
   return !should_run();
}


void Thread::onTermThread()
{
   
}


void Thread::onThreadMain()
{
   //m_pthreadCallback->onThreadMain();
//   ::subsystem::Thread::onThreadMain();
//    if(m_procedureCallback)
//    {
//
//       m_procedureCallback();
//
//    }
}

} // namespace subsystem

