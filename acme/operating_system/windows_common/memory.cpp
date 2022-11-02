#include "framework.h"
#include "acme/_operating_system.h"


HANDLE g_handleSystemHeap = nullptr;


void defer_initialize_system_heap()
{

   if (!g_handleSystemHeap)
   {

      g_handleSystemHeap = HeapCreate(0, 0, 0);

   }

}



