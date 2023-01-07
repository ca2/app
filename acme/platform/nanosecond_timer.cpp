#include "framework.h"
#include "nanosecond_timer.h"
#include "acme/_operating_system.h"


#ifdef LINUX


#include <time.h>


#endif


nanosecond_timer::nanosecond_timer()
{

#ifdef WINDOWS

   m_hTimer = ::CreateWaitableTimer(nullptr, true, nullptr);

#endif

}


nanosecond_timer::~nanosecond_timer()
{

   close_timer();

}


void nanosecond_timer::wait(const class time & time)
{

#ifdef WINDOWS

   LARGE_INTEGER li = {};

   li.QuadPart = -time.integral_nanosecond() / 100LL;

   if (!SetWaitableTimer(m_hTimer, &li, 0, nullptr, nullptr, false))
   {

      ::preempt(time);

   }
   else
   {

      WaitForSingleObject(m_hTimer, INFINITE);

   }

#else

   struct timespec timespec;

   timespec.tv_sec = (time_t) time.m_iSecond;

   timespec.tv_nsec = (long) time.m_iNanosecond;

   ::nanosleep(&timespec, nullptr);

#endif


}


void nanosecond_timer::close_timer()
{

#ifdef WINDOWS
   if (m_hTimer != NULL)
   {

      ::CloseHandle(m_hTimer);

      m_hTimer = NULL;

   }

#endif


}






