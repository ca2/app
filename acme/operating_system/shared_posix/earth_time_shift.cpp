// Created by camilo on 2023-07-04 02:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/primitive/datetime/earth_time_shift.h"
#include <time.h>


namespace earth
{


   time_shift time_shift::local()
   {

      time_t zero = 0;

      const tm * lt = localtime(&zero);

      int unaligned = lt->tm_sec + (lt->tm_min + (lt->tm_hour * 60)) * 60;

      return { (double)(lt->tm_mon ? unaligned - 24 * 60 * 60 : unaligned) };

   }



} // namespace earth



