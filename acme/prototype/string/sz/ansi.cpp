// Created by camilo on 2022-11-04 18:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <string.h>


CLASS_DECL_ACME huge_integer string_to_signed(const ::ansi_character * psz)
{

   return atoll(psz);

}


CLASS_DECL_ACME huge_natural as_huge_natural(const ::ansi_character * psz)
{

   return strtoull(psz, nullptr, 10);

}


CLASS_DECL_ACME double string_to_floating(const ::ansi_character * psz)
{

   return strtod(psz, nullptr);

}



