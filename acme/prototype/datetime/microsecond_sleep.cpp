#include "framework.h"
#include "microsecond_sleep.h"
#include "acme/_operating_system.h"


#ifdef WINDOWS

struct MICROSECOND_SLEEP
{

   HANDLE m_hTimer;
   //socket_id m_socket;

};

#endif


#if defined(FREEBSD) || defined(__APPLE__) || defined(OPENBSD) || defined(RASPBERRYPIOS)

#include <unistd.h>

#endif


microsecond_sleep::microsecond_sleep()
{

#ifdef WINDOWS

   ::memory_set(this, 0, sizeof(microsecond_sleep));

   MICROSECOND_SLEEP * pthis = (MICROSECOND_SLEEP *)this;

   pthis->m_hTimer = ::CreateWaitableTimer(NULL, true, NULL);

#endif

}


microsecond_sleep::~microsecond_sleep()
{

#ifdef WINDOWS

   MICROSECOND_SLEEP * pthis = (MICROSECOND_SLEEP *)this;

   ::CloseHandle(pthis->m_hTimer);

#endif

}



#ifdef WINDOWS


bool microsecond_sleep::sleep(unsigned long usec)
{

   LARGE_INTEGER ft;

   ft.QuadPart = -(10 * (huge_integer)usec);

   MICROSECOND_SLEEP * pthis = (MICROSECOND_SLEEP *)this;

   ::SetWaitableTimer(pthis->m_hTimer, &ft, 0, NULL, NULL, 0);

   ::WaitForSingleObject(pthis->m_hTimer, INFINITE);

   return true;

}


#endif



