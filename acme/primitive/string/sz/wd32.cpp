// Created by camilo on 2022-11-04 18:42 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/primitive/string/string.h"


#include <wchar.h>


CLASS_DECL_ACME::i64 string_to_signed(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return _wtoll(wstr);

#else

   return wcstoll(pwsz, nullptr, 10);

#endif

}


CLASS_DECL_ACME::u64 string_to_natural(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return _wcstoui64(wstr, nullptr, 10);

#else

   return wcstoull(pwsz, nullptr, 10);

#endif

}


CLASS_DECL_ACME ::f64 string_to_floating(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return wcstod(wstr, nullptr);

#else

   return wcstod(pwsz, nullptr);

#endif

}



