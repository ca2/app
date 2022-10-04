//
//  process.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/05/20.
//
#include "framework.h"


void process_get_os_priority(i32 * piOsPriority,  i32 nCa2Priority)
{

   int iOsPriority;

   int iCa2Min;

   int iCa2Max;

   int iOsMax = 20;

   int iOsMin = -20;

   if(nCa2Priority == ::e_priority_normal)
   {

      iOsPriority = 0;

   }
   else if(nCa2Priority > ::e_priority_normal)
   {

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = 99;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }
   else
   {

      iCa2Min = 0;

      iCa2Max = (int) ::e_priority_normal;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }

   *piOsPriority = iOsPriority;

}


::u32 get_current_process_id()
{

    return getpid();

}



