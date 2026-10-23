// Created by camilo on 2022-11-04 18:42 <3ThomasBorregaardSorensen!!
#include "platform.h"



#include <wchar.h>


CLASS_DECL_ACME ::i64 string_to_signed(const ::wd32_character * pwsz)
{

   return wd32_to_i64(pwsz, nullptr, 10);

}


CLASS_DECL_ACME ::u64 as_u64(const ::wd32_character * pwsz)
{

   return wd32_to_u64(pwsz, nullptr, 10);

}


CLASS_DECL_ACME ::f64 string_to_floating(const ::wd32_character * pwsz)
{

   ::string str(pwsz);

   return strtod(str, nullptr);

}



