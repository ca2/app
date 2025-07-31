// Created by camilo on 2023-11-25 22:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <string.h>


namespace c
{


//   CLASS_DECL_ACME char * strdup(const char * psz)
//   {
//
//      return ::strdup(scopedstr);
//
//   }


   CLASS_DECL_ACME char* strdup2(const char* psz1, const char* psz2)
   {

      auto len1 = string_safe_length(scopedstr1);

      auto len2 = string_safe_length(scopedstr2);

      auto len = len1 + len2;

      auto psz = (char*) ::malloc(len + 1);

      if (len1 > 0)
      {

         memcpy(scopedstr, psz1, len1);

      }

      if (len2 > 0)
      {

         memcpy(scopedstr + len1, psz2, len2);

      }

      psz[len] = '\0';

      return psz;

   }


   CLASS_DECL_ACME void free(void * p)
   {

      return ::free(p);

   }


} // namespace c



