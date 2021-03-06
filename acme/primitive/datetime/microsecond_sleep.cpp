#include "framework.h"
#include "acme/operating_system.h"


#ifdef WINDOWS

struct MICROSECOND_SLEEP
{

   HANDLE m_hTimer;
   //SOCKET m_socket;

};

#endif


microsecond_sleep::microsecond_sleep()
{

#ifdef WINDOWS

   memset(this, 0, sizeof(microsecond_sleep));

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


bool microsecond_sleep::sleep(unsigned long usec)
{

#ifdef WINDOWS

   LARGE_INTEGER ft;

   ft.QuadPart = -(10 * (::i64)usec);

   MICROSECOND_SLEEP * pthis = (MICROSECOND_SLEEP *)this;

   ::SetWaitableTimer(pthis->m_hTimer, &ft, 0, NULL, NULL, 0);

   ::WaitForSingleObject(pthis->m_hTimer, U32_INFINITE_TIMEOUT);

   return true;

#else

   usleep((::u32)usec);

   return true;

#endif

}



