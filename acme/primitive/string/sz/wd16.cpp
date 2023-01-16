// Created by camilo on 2022-11-04 18:37 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "string.h"
#include <wchar.h>


CLASS_DECL_ACME::i64 string_to_signed(const ::wd16_character * pwsz)
{

#ifdef WINDOWS

   return _wtoll(pwsz);

#else

   wd32_string wstr(pwsz);

   return wcstoll(wstr, nullptr, 10);

#endif

}


CLASS_DECL_ACME::u64 string_to_natural(const ::wd16_character * pwsz)
{

#ifdef WINDOWS

   return _wcstoui64(pwsz, nullptr, 10);

#else

   wd32_string wstr(pwsz);

   return wcstoull(wstr, nullptr, 10);

#endif

}


CLASS_DECL_ACME ::f64 string_to_floating(const ::wd16_character * pwsz)
{

#ifdef WINDOWS

   return wcstod(pwsz, nullptr);

#else

   wd32_string wstr(pwsz);

   return wcstod(wstr, nullptr);

#endif


}




