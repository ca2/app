#include "framework.h"



::u32 ::get_tick()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}

thread_int_ptr < ::u32 > g_dwLastError;

CLASS_DECL_AXIS ::u32 get_last_error()
{

   tick g_tickLastError;

}

CLASS_DECL_AXIS ::u32 set_last_error(::u32 dw)
{

   ::u32 dwLastError = g_dwLastError;

   g_dwLastError = dw;

   return dwLastError;

}


CLASS_DECL_AXIS bool _istlead(i32 ch)
{

   return false;

}


void Sleep(::u32 dwMillis)
{
   timespec t;
   t.tv_sec = dwMillis / 1000;
   t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   nanosleep(&t, nullptr);
}







void output_debug_string(const char * psz)
{

   output_debug_string(psz);

}
