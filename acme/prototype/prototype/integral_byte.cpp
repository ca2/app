//
// Created by camilo on 2022-11-05 23:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"



CLASS_DECL_ACME ::string & copy(::string & str, const integral_byte & memsize)
{

   if (memsize < 1_KiB)
   {

      str.formatf("%d bytes", memsize);

   }
   else if (memsize < 1_MiB)
   {

      str.formatf("%0.2f KiB", (::f64)memsize / (::f64)(1_KiB));

   }
   else if (memsize < 1_GiB)
   {

      str.formatf("%0.2f MB", (::f64)memsize / (::f64)(1_MiB));

   }
   else
   {

      str.formatf("%0.2f GB", (::f64)memsize / (::f64)(1_GiB));

   }

   return str;

}



