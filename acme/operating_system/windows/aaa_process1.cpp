// Recreated by camilo on 2021-12-16 19:41 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
////#include "acme/exception/exception.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/single_lock.h"
#include "acme/platform/node.h"
#include "acme/primitive/collection/string_array.h"
#include "acme/_operating_system.h"



CLASS_DECL_ACME::u64 translate_processor_affinity(int iOrder)
{

   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {
      return 0;
   }
   i32 j = 0;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         if (iOrder == j)
         {
            return dwMask;
         }
         j++;
      }
      dwMask = dwMask << 1;
   }

   return 0;

}



i32 get_current_process_affinity_order()
{


   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;

   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {

      return 0;

   }

   i32 iCount = 0;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }

   return iCount;


}





i32 get_current_process_maximum_affinity()
{

   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {
      return 0;
   }
   i32 iMax = -1;
   uptr dwMask = 1;
   for (i32 i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         iMax = i;
      }
      dwMask = dwMask << 1;
   }

   return iMax;

}



