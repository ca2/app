//
//  process.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/05/20.
//
#include "framework.h"
#include <unistd.h>

void process_get_os_priority(::i32 * piOsPriority,  ::i32 nCa2Priority)
{

   ::i32 iOsPriority;

   ::i32 iCa2Min;

   ::i32 iCa2Max;

   ::i32 iOsMax = 20;

   ::i32 iOsMin = -20;

   if(nCa2Priority == ::e_priority_normal)
   {

      iOsPriority = 0;

   }
   else if(nCa2Priority > ::e_priority_normal)
   {

      iCa2Min = (::i32) ::e_priority_normal;

      iCa2Max = 99;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }
   else
   {

      iCa2Min = 0;

      iCa2Max = (::i32) ::e_priority_normal;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }

   *piOsPriority = iOsPriority;

}


::u32 get_current_process_id()
{

   return getpid();

}



