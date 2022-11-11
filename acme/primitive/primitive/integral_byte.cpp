//
// Created by camilo on 2022-11-05 23:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/primitive/string/string.h"


CLASS_DECL_ACME ::string & copy(::string & str, const integral_byte & memsize)
{

   if (memsize < 1_kb)
   {

      str.format("%d bytes", memsize);

   }
   else if (memsize < 1_mb)
   {

      str.format("%0.2f kb", (double)memsize / (double)(1_kb));

   }
   else if (memsize < 1_gb)
   {

      str.format("%0.2f MB", (double)memsize / (double)(1_mb));

   }
   else
   {

      str.format("%0.2f GB", (double)memsize / (double)(1_gb));

   }

   return str;

}



