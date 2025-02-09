// Created by camilo on 2023-07-04 02:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/prototype/datetime/earth_time_shift.h"
#include <time.h>

//
//namespace earth
//{
//

   class ::time time::local()
   {

      time_t zero = 0;

      const tm * lt = localtime(&zero);

      int unaligned = lt->tm_sec + (lt->tm_min + (lt->tm_hour * 60)) * 60;

      return { (long long) (lt->tm_mon ? unaligned - 24 * 60 * 60 : unaligned), 0 };

   }


//
//} // namespace earth
//
//

