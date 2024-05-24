//
// Created by camilo on 2022-11-05 23:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"



CLASS_DECL_ACID ::string & copy(::string & str, const integral_byte & memsize)
{

   if (memsize < 1_KiB)
   {

      str.formatf("%d bytes", memsize);

   }
   else if (memsize < 1_MiB)
   {

      str.formatf("%0.2f KiB", (double)memsize / (double)(1_KiB));

   }
   else if (memsize < 1_GiB)
   {

      str.formatf("%0.2f MB", (double)memsize / (double)(1_MiB));

   }
   else
   {

      str.formatf("%0.2f GB", (double)memsize / (double)(1_GiB));

   }

   return str;

}



