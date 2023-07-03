//
// Created by camilo on 2022-11-05 23:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"



CLASS_DECL_ACME ::string & copy(::string & str, const integral_byte & memsize)
{

   if (memsize < 1_KiB)
   {

      str.format("%d bytes", memsize);

   }
   else if (memsize < 1_MiB)
   {

      str.format("%0.2f KiB", (double)memsize / (double)(1KiB));

   }
   else if (memsize < 1_GiB)
   {

      str.format("%0.2f MB", (double)memsize / (double)(1MiB));

   }
   else
   {

      str.format("%0.2f GB", (double)memsize / (double)(1GiB));

   }

   return str;

}



