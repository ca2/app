#include "framework.h"
#include "acme/operating_system.h"


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


void nanosecond_timer::wait(const ::duration & duration)
{

#ifdef WINDOWS

   LARGE_INTEGER li = {};

   li.QuadPart = -duration.integral_nanosecond().m_i / 100LL;

   if (!SetWaitableTimer(m_hTimer, &li, 0, nullptr, nullptr, false))
   {

      ::preempt(duration);

   }
   else
   {

      WaitForSingleObject(m_hTimer, INFINITE);

   }

#else

   ::nanosleep((timespec *) &duration, nullptr);

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






