#include "framework.h"


#ifndef PREFER_MALLOC
#define PREFER_MALLOC 0
#endif


#if defined(WINDOWS) && !defined(__VLD) && !defined(__MCRTDBG)
#include "acme/operating_system.h"

HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}


#endif


critical_section * g_pmutexSystemHeap = nullptr;


#if defined(WINDOWS) && !PREFER_MALLOC  && !(defined(__VLD) || defined(__MCRTDBG))


#include "os_alloc/WindowsHeapAlloc.cpp"


#else


#include "os_alloc/malloc.cpp"


#endif


#ifndef BOUNDS_CHECK
#define BOUNDS_CHECK 0
#endif


#if BOUNDS_CHECK


#include "os_alloc/bounds_check.cpp"


#else


#include "os_alloc/no_bounds_check.cpp"


#endif


