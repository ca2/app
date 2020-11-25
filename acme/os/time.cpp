#include "framework.h"
#include <time.h>
#if defined(LINUX) || defined(APPLEOS)
#include <unistd.h>
#endif


CLASS_DECL_ACME void __seed_srand()
{

   srand((unsigned int)(time(nullptr)));

}



bool os_usleep::sleep(unsigned long usec)
{

#ifdef WINDOWS
   LARGE_INTEGER ft;

   ft.QuadPart = -(10 * (::i64)usec);
   SetWaitableTimer(m_hTimer, &ft, 0, NULL, NULL, 0);
   WaitForSingleObject(m_hTimer, U32_INFINITE_TIMEOUT);

   return true;

#else

   usleep((::u32) usec);

   return true;

#endif

}





//CLASS_DECL_ACME void sleep(const ::duration& dur)
//{
//
//   millis_sleep((::u32)dur.total_milliseconds());
//
//}


CLASS_DECL_ACME void secs_sleep(const ::secs & secs)
{

   ::Sleep((DWORD) (secs.m_iSeconds * 1'000));

}


CLASS_DECL_ACME void millis_sleep(const millis & millis)
{

   ::Sleep((DWORD) millis.m_iMilliseconds);

}


CLASS_DECL_ACME void micros_sleep(const micros & micros)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void nanos_sleep(const nanos & nanos)
{

   ::Sleep(1);

}



