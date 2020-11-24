#include "framework.h"


nano_timer::nano_timer()
{

#ifdef WINDOWS

   m_hTimer = ::CreateWaitableTimer(nullptr, TRUE, nullptr);

#endif

}


void nano_timer::wait(u64 uWait)
{

#ifdef WINDOWS

      LARGE_INTEGER li = {};

      li.QuadPart = -((::i64)uWait / 100LL);

      if (!SetWaitableTimer(m_hTimer, &li, 0, nullptr, nullptr, FALSE))
      {

         millis_sleep(::u32(uWait / 1000000LL));

      }
      else
      {

         WaitForSingleObject(m_hTimer, U32_INFINITE_TIMEOUT);

      }

#else

      struct timespec req;

      //struct timespec rem;

      req.tv_sec = uWait / 1'000'000'000ULL;

      req.tv_nsec = uWait % 1'000'000'000ULL;

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



