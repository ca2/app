// Created by camilo on 2023-12-01 20:50 <3ThomasBorregaardSorensen!!
#include "framework.h"


static ::interlocked_count g_interlockedcountNewReferenceRefererSerial;


CLASS_DECL_ACME huge_integer new_reference_referer_serial()
{

   auto i = (huge_integer)g_interlockedcountNewReferenceRefererSerial;

   g_interlockedcountNewReferenceRefererSerial++;

   return i;

}



