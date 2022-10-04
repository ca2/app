//
//  macos_file_raw.cpp
//  ace
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/09/17.
//  Copyright © 2017 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "macos.h"
#include <sys/sysctl.h>


int get_processor_count()
{

   int nm[2];

   size_t len = 4;

   u32 count;

   nm[0] = CTL_HW;

   nm[1] = HW_AVAILCPU;

   sysctl(nm, 2, &count, &len, nullptr, 0);

   if(count < 1)
   {

      nm[1] = HW_NCPU;

      sysctl(nm, 2, &count, &len, nullptr, 0);

      if(count < 1)
      {
         count = 1;

      }

   }

   return count;

}



