#include "framework.h"
//#include "uwp.h"

//DWORD ::get_tick()
//{
//
//   return (DWORD) (GetTickCount64() % 0x100000000ULL);
//
//}


//LARGE_INTEGER g_freq;
//
//extern "C"
//CLASS_DECL_ACME i64 get_nanos()
//{
//
//   LARGE_INTEGER li = {};
//
//   QueryPerformanceCounter(&li);
//
//   return muldiv64(li.QuadPart, 1'000'000'000, g_freq.QuadPart);
//
//}



CLASS_DECL_ACME void sleep(const ::duration & dur)
{

   Sleep((DWORD) dur.total_milliseconds());

}
