// Created by camilo on 2024-09-02 19:14 <3ThomasBorregaardSorensen!!
#include "framework.h"


#include <stdio.h>


void output_debug_string(const ::scoped_string & scopedstr)
{

   //printf("c.");

   auto p = ::platform::get();

   if(!p || p->m_bOutputDebugString)
   {

      //printf("2.");

//      if(strstr(scopedstr, "font_list"))
//      {
//
//         printf("a");
//
//      }

      auto pszBeg = scopedstr.begin();

      auto pszEnd = scopedstr.end();

      auto iSize = scopedstr.size();

      fwrite(pszBeg, 1, iSize, stdout);

      //fflush(stdout);

   }

}


void output_debug_string_flush()
{

   if (::platform::get()->m_bOutputDebugString)
   {

      fflush(stdout);

   }

}



