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
//   Sleep((::u32)dur.total_milliseconds());
//
//}
