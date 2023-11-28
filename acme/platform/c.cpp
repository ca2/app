// Created by camilo on 2023-11-25 22:02 <3ThomasBorregaardSorensen!!
#include "framework.h"


namespace c
{


   CLASS_DECL_ACME char * strdup(const char * psz)
   {

      return ::strdup(psz);

   }


   CLASS_DECL_ACME void free(void * p)
   {

      return ::free(p);

   }


} // namespace c



