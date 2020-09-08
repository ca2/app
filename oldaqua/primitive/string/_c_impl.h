#pragma once


#include "aqua/primitive/string/_c_str_impl.h"
#include "aqua/primitive/string/_c_trait_ansi_impl.h"
#include "aqua/primitive/string/_c_trait_wd16_impl.h"
#include "aqua/primitive/string/_c_trait_wd32_impl.h"
#include "aqua/primitive/string/_c_trait_impl.h"


#include "aqua/primitive/string/_c_inline.h"






inline strsize strlen_s_dup(const char * psz, strsize nsize)
{

   if (psz == nullptr)
   {

      return 0;

   }

   strsize len = 0;

   while (*psz != '\0' && nsize > 0)
   {

      psz++;

      nsize--;

      len++;

   }

   return len;

}


#ifdef WINDOWS
inline const ansichar * eol()
{
   return "\r\n";
}
#elif defined(__APPLE__)
inline const ansichar * eol()
{
   return "\r";
}
#else
inline const ansichar * eol()
{
   return "\n";
}
#endif








