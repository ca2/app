#include "framework.h"
#include "acme/operating_system.h"


#ifdef LINUX


#include <time.h>


#endif


nano_timer::nano_timer()
{

#ifdef WINDOWS

   m_hTimer = ::CreateWaitableTimer(nullptr, true, nullptr);

#endif

}


void nano_timer::wait(const ::nanos & nanosWait)
{

#ifdef WINDOWS

      LARGE_INTEGER li = {};

      li.QuadPart = -((::i64)nanosWait.m_i / 100LL);

      if (!SetWaitableTimer(m_hTimer, &li, 0, nullptr, nullptr, false))
      {

         sleep(::millis(nanosWait.m_i / 1'000'000LL));

      }
      else
      {

         WaitForSingleObject(m_hTimer, U32_INFINITE_TIMEOUT);

      }

#else

      struct timespec req;

      //struct timespec rem;

      req.tv_sec = nanosWait.m_i / 1'000'000'000ULL;

      req.tv_nsec = nanosWait.m_i % 1'000'000'000ULL;

      //rem.tv_sec = 0;

      //rem.tv_nsec = 0;

      //::nanosleep(&req, &rem);

      ::nanosleep(&req, nullptr);

#endif

   }


void nano_timer::close_timer()
{

#ifdef WINDOWS
   if (m_hTimer != NULL)
   {

      ::CloseHandle(m_hTimer);

      m_hTimer = NULL;

   }

#endif


}


nano_timer::~nano_timer()
{

   close_timer();

}



