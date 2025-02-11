// Created by camilo on 2023-12-01 20:50 <3ThomasBorregaardSorensen!!
#include "framework.h"


static ::interlocked_count g_interlockedcountNewReferenceRefererSerial;


CLASS_DECL_ACME long long new_reference_referer_serial()
{

   auto i = (long long)g_interlockedcountNewReferenceRefererSerial;

   g_interlockedcountNewReferenceRefererSerial++;

   return i;

}


#if REFERENCING_DEBUGGING


void reference_referer::common_construct()
{

   auto uPointer = (::uptr) this;

   if (uPointer < 0x1000000)
   {

      //::output_debug_string("what?!?!?!?!");

   }

}


#endif



