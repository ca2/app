// Created by camilo on 2022-11-04 18:37 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include <string.h>


CLASS_DECL_ACME::i64 string_to_signed(const ::ansi_character * psz)
{

   return atoll(psz);

}


CLASS_DECL_ACME::u64 string_to_natural(const ::ansi_character * psz)
{

   return strtoull(psz, nullptr, 10);

}


CLASS_DECL_ACME ::f64 string_to_floating(const ::ansi_character * psz)
{

   return strtod(psz, nullptr);

}



