// Created by camilo on 2023-12-01 20:50 <3ThomasBorregaardSorensen!!
#include "framework.h"


static ::interlocked_count g_interlockedcountNewReferenceRefererSerial;


CLASS_DECL_ACID::collection::index new_reference_referer_serial()
{

   auto i = (::i64)g_interlockedcountNewReferenceRefererSerial;

   g_interlockedcountNewReferenceRefererSerial++;

   return i;

}



