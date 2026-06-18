// Created by camilo on 2022-11-04 18:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <string.h>


CLASS_DECL_ACME ::i64 string_to_signed(const_char_pointer psz)
{

   return atoll(psz);

}


CLASS_DECL_ACME ::u64 as_u64(const_char_pointer psz)
{

   return strtoull(psz, nullptr, 10);

}


CLASS_DECL_ACME ::f64 string_to_floating(const_char_pointer psz)
{

   return strtod(psz, nullptr);

}



