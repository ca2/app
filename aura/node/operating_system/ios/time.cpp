#include "framework.h"


inline ::u32 GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}



//::u32 ::get_tick()
//{
//
//   return (::u32) GetTickCount();
//
//}
//
//
//





#include "framework.h"

CLASS_DECL_AURA void sleep(unsigned int dwMillis)
{
   
   usleep(dwMillis * 1000);
   
}

