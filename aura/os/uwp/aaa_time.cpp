#include "framework.h"
//#include "uwp.h"

//::u32 ::get_tick()
//{
//
//   return (::u32) (GetTickCount64() % 0x100000000ULL);
//
//}


//LARGE_INTEGER g_freq;
//
//extern "C"
//CLASS_DECL_AURA i64 get_nanos()
//{
//
//   LARGE_INTEGER li = {};
//
//   QueryPerformanceCounter(&li);
//
//   return muldiv64(li.QuadPart, 1'000'000'000, g_freq.QuadPart);
//
//}



CLASS_DECL_AURA void sleep(const ::duration & dur)
{

   Sleep((::u32) dur.total_milliseconds());

}
