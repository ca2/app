// Created by camilo on 2022-11-04 18:37 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "string.h"
#include <wchar.h>


CLASS_DECL_ACME ::i64 string_to_signed(const ::wd16_character * pwsz)
{

   return wd16_to_i64(pwsz, nullptr, 10);

}


CLASS_DECL_ACME ::u64 as_u64(const ::wd16_character * pwsz)
{

   return wd16_to_u64(pwsz, nullptr, 10);

}


CLASS_DECL_ACME ::f64 string_to_floating(const ::wd16_character * pwsz)
{

   ::string str(pwsz);

   return strtod(str, nullptr);


}




