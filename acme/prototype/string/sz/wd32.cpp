// Created by camilo on 2022-11-04 18:42 <3ThomasBorregaardSorensen!!
#include "framework.h"



#include <wchar.h>


CLASS_DECL_ACME long long string_to_signed(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return _wtoll(wstr);

#else

   return wcstoll(pwsz, nullptr, 10);

#endif

}


CLASS_DECL_ACME unsigned long long as_unsigned_long_long(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return _wcstoui64(wstr, nullptr, 10);

#else

   return wcstoull(pwsz, nullptr, 10);

#endif

}


CLASS_DECL_ACME double string_to_floating(const ::wd32_character * pwsz)
{

#ifdef WINDOWS

   wd16_string wstr(pwsz);

   return wcstod(wstr, nullptr);

#else

   return wcstod(pwsz, nullptr);

#endif

}



