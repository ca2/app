#include "framework.h"



unsigned int get_tick()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}

thread_int_ptr < unsigned int > g_dwLastError;

CLASS_DECL_ACME unsigned int get_last_error()
{

   ::time g_tickLastError;

}

CLASS_DECL_ACME unsigned int set_last_error(unsigned int dw)
{

   unsigned int dwLastError = g_dwLastError;

   g_dwLastError = dw;

   return dwLastError;

}


CLASS_DECL_ACME bool _istlead(int ch)
{

   return false;

}


void sleep(unsigned int dwMillis)
{
   timespec t;
   t.tv_sec = dwMillis / 1000;
   t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   nanosleep(&t, nullptr);
}







void informationf(const ::scoped_string & scopedstr)
{

   informationf(psz);

}
