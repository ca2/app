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


#include <unistd.h>
#include <sched.h>

#ifdef PARALLELIZATION_PTHREAD
#include "Thread_pthread.h"
#endif

namespace subsystem
{

thread_implementation::thread_implementation(::subsystem::Thread * psubsystemthread):
m_psubsystemthread(psubsystemthread)
{

   
   
   
    pthread_mutex_init(
        &m_suspendMutex,
        nullptr);

    pthread_cond_init(
        &m_suspendCond,
        nullptr);

    pthread_create(
        &m_thread,
        nullptr,
        &thread_implementation::threadProc,
        this);

   m_threadID =
        (::iptr)m_thread;
}


thread_implementation::~thread_implementation()
{
    pthread_mutex_destroy(
        &m_suspendMutex);

    pthread_cond_destroy(
        &m_suspendCond);
}


void* thread_implementation::threadProc(void* pThread)
{
   thread_implementation* _this =
        (thread_implementation*)pThread;
   
   
   

    _this->m_active = true;

    // start suspended
    _this->waitIfSuspended();

    try
    {
        _this->onInitThread();
        _this->onRunThread();
    }
    catch (...)
    {
    }

    _this->m_active = false;
   //_this->m_psubsystemthread->m_pobjectParentTask->erase_task_and_set_task_new_parent//(_this->m_psubsystemthread, nullptr);
   
   _this->m_psubsystemthread.defer_destroy_and_release();
   

    return nullptr;
}


void thread_implementation::waitIfSuspended()
{
   
   //m_pthreadimplementation->waitIfSuspended();
    pthread_mutex_lock(
        &m_suspendMutex);

    while (m_suspended &&
           !has_finishing_flag())
    {
        pthread_cond_wait(
            &m_suspendCond,
            &m_suspendMutex);
    }

    pthread_mutex_unlock(
        &m_suspendMutex);
}


void thread_implementation::onInitThread()
{
   m_psubsystemthread->onInitThread();
}


::e_status thread_implementation::wait()
{
 //  return m_pthreadimplementation->wait();
    if (m_active)
    {
        return pthread_join(
                            m_thread,
            nullptr) == 0
                ? ::success
                : error_failed;
    }

    return ::success;
}


bool thread_implementation::suspendThread()
{
//return   m_pthreadimplementation->suspendThread();
   m_suspended = true;
    return true;
}


bool thread_implementation::resumeThread()
{
   //return m_pthreadimplementation->resumeThread();
    pthread_mutex_lock(
        &m_suspendMutex);

   m_suspended = false;

    pthread_cond_signal(
        &m_suspendCond);

    pthread_mutex_unlock(
        &m_suspendMutex);

    return true;
}


void thread_implementation::terminateThread()
{
   //m_pthreadimplementation->terminateThread();
   set_finish();

    resumeThread();

    onTerminateThread();
}


bool thread_implementation::isThreadActive() const
{
   //return m_pthreadimplementation->isThreadActive();
    return m_active;
}


::iptr thread_implementation::getThreadId() const
{
    return m_threadID;
}


bool thread_implementation::setThreadPriority(
    ::subsystem::THREAD_PRIORITY value)
{
    int policy;
    sched_param param;

    pthread_getschedparam(
                          m_thread,
        &policy,
        &param);

    int minPriority =
        sched_get_priority_min(policy);

    int maxPriority =
        sched_get_priority_max(policy);

    int priority =
        (minPriority + maxPriority) / 2;

    switch (value)
    {
    case ::subsystem::PRIORITY_IDLE:
        priority = minPriority;
        break;

    case ::subsystem::PRIORITY_TIME_CRITICAL:
        priority = maxPriority;
        break;

    default:
        break;
    }

    param.sched_priority = priority;

    return pthread_setschedparam(
                                 m_thread,
        policy,
        &param) == 0;
}


void thread_implementation::threadSleep(
    const class ::time& time)
{
    usleep(
        (useconds_t)
        time.integral_microsecond());
}


void thread_implementation::threadYield()
{
    sched_yield();
}


bool thread_implementation::isThreadTerminating()
{
    return has_finishing_flag();
}


void thread_implementation::onTerminateThread()
{
   m_psubsystemthread->onTerminateThread();
}


void thread_implementation::onRunThread()
{
   m_psubsystemthread->onRunThread();
//   ::subsystem::thread_implementation::onRunThread();
//    if(m_procedureCallback)
//    {
//     
//       m_procedureCallback();
//       
//    }
}

} // namespace subsystem



//namespace subsystem
//{
//
//thread_implementation::Thread()
//{
//   
//   m_pthreadimplementation = allocateø thread_implementation;
//   
//   ::get_task()->add_task(this);
//   
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
//        &thread_implementation::threadProc,
//        this);
//
//   m_pthreadimplementation->m_threadID =
//        (::iptr)m_thread;
//}
//
//
//thread_implementation::~Thread()
//{
//    pthread_mutex_destroy(
//        &m_pthreadimplementation->m_suspendMutex);
//
//    pthread_cond_destroy(
//        &m_pthreadimplementation->m_suspendCond);
//}
//
//
//void* thread_implementation::threadProc(void* pThread)
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
//        _this->onRunThread();
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
//
//
//void thread_implementation::waitIfSuspended()
//{
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
//}
//
//
//void thread_implementation::onInitThread()
//{
//}
//
//
//::e_status thread_implementation::wait()
//{
//    if (m_pthreadimplementation->m_active)
//    {
//        return pthread_join(
//                            m_pthreadimplementation->m_thread,
//            nullptr) == 0
//                ? ::success
//                : error_failed;
//    }
//
//    return ::success;
//}
//
//
//bool thread_implementation::suspendThread()
//{
//   m_pthreadimplementation->m_suspended = true;
//    return true;
//}
//
//
//bool thread_implementation::resumeThread()
//{
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
//    return true;
//}
//
//
//void thread_implementation::terminateThread()
//{
//   m_pthreadimplementation->m_terminated = true;
//
//    resumeThread();
//
//    onTerminateThread();
//}
//
//
//bool thread_implementation::isThreadActive() const
//{
//    return m_pthreadimplementation->m_active;
//}
//
//
//::iptr thread_implementation::getThreadId() const
//{
//    return m_pthreadimplementation->m_threadID;
//}
//
//
//bool thread_implementation::setThreadPriority(
//    ::subsystem::THREAD_PRIORITY value)
//{
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
//}
//
//
//void thread_implementation::threadSleep(
//    const class ::time& time)
//{
//    usleep(
//        (useconds_t)
//        time.integral_microsecond());
//}
//
//
//void thread_implementation::threadYield()
//{
//    sched_yield();
//}
//
//
//bool thread_implementation::isThreadTerminating()
//{
//    return m_pthreadimplementation->m_terminated;
//}
//
//
//void thread_implementation::onTerminateThread()
//{
//}
//
//
//void thread_implementation::onRunThread()
//{
//   //m_pthreadCallback->onRunThread();
////   ::subsystem::thread_implementation::onRunThread();
////    if(m_procedureCallback)
////    {
////
////       m_procedureCallback();
////
////    }
//}
//
//} // namespace subsystem
