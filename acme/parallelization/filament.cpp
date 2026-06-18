// from subsystem/thread/Thread.cpp on 2026-05-17 03:40 by camilo <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "filament.h"
//#include "Thread.h"
////#include "critical_section_lock.h"
//#include "subsystem/platform/Exception.h"
//
//#ifdef PARALLELIZATION_PTHREAD
//#include "Thread_pthread.h"
//#endif

//namespace subsystem
//{

Thread::Thread()
{

   ::get_task()->add_task(this);

   m_pthreadimplementation = allocateø thread_implementation(this);
   
   
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


void Thread::waitIfSuspended()
{
   
   m_pthreadimplementation->waitIfSuspended();
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


::e_status Thread::wait()
{
   return m_pthreadimplementation->wait();
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
}


bool Thread::suspendThread()
{
return   m_pthreadimplementation->suspendThread();
   //m_pthreadimplementation->m_suspended = true;
    //return true;
}


bool Thread::resumeThread()
{
   return m_pthreadimplementation->resumeThread();
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
}


void Thread::terminateThread()
{
   m_pthreadimplementation->terminateThread();
//   m_pthreadimplementation->m_terminated = true;
//
//    resumeThread();
//
//    onTerminateThread();
}


bool Thread::isThreadActive() const
{
   return m_pthreadimplementation->isThreadActive();
    return m_pthreadimplementation->m_active;
}


::iptr Thread::getThreadId() const
{
    return m_pthreadimplementation->m_threadID;
}


bool Thread::setThreadPriority(
    ::subsystem::THREAD_PRIORITY value)
{
   return m_pthreadimplementation->setThreadPriority(value);
//    ::i32 policy;
//    sched_param param;
//
//    pthread_getschedparam(
//                          m_pthreadimplementation->m_thread,
//        &policy,
//        &param);
//
//    ::i32 minPriority =
//        sched_get_priority_min(policy);
//
//    ::i32 maxPriority =
//        sched_get_priority_max(policy);
//
//    ::i32 priority =
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
   m_pthreadimplementation->threadSleep(time);
//    usleep(
//        (useconds_t)
//        time.integral_microsecond());
}


void Thread::threadYield()
{
    //sched_yield();
   m_pthreadimplementation->threadYield();
}


bool Thread::isThreadTerminating()
{
    return m_pthreadimplementation->isThreadTerminating();
}


void Thread::onTerminateThread()
{
}


void Thread::onRunThread()
{
   //m_pthreadCallback->onRunThread();
//   ::subsystem::Thread::onRunThread();
//    if(m_procedureCallback)
//    {
//
//       m_procedureCallback();
//
//    }
}

} // namespace subsystem

