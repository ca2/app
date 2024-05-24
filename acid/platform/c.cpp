// Created by camilo on 2023-11-25 22:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <string.h>


namespace c
{


   CLASS_DECL_ACID char * strdup(const char * psz)
   {

      return ::strdup(psz);

   }


   CLASS_DECL_ACID void free(void * p)
   {

      return ::free(p);

   }


} // namespace c



