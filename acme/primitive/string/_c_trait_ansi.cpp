#include "framework.h"
#include "string.h"
#include "_conv.h"


ansichar * __u64toansi(::u64 u, ansichar * buf, int iBase, enum_digit_case edigitcase, ::i32 & len)
{

   if (u == 0)
   {

      buf[0] = (ansichar)'0';

      buf[1] = (ansichar)'\0';

      len = 1;

      return buf;

   }

   len = 0;

   __natural_to_string_internal(u, buf, iBase, len, edigitcase);

   buf[len] = '\0';

   ansi_reverse(buf, len);

   return buf;

}


ansichar * __i64toansi(::i64 i, ansichar * buf, int iBase, enum_digit_case edigitcase, ::i32 & len)
{

   if (i == 0)
   {

      buf[0] = (ansichar)'0';

      buf[1] = (ansichar)'\0';

      len = 1;

      return buf;

   }

   len = 0;

   bool bNegative;

   if (i < 0)
   {

      i = -i;

      bNegative = true;

   }
   else
   {

      bNegative = false;

   }

   __natural_to_string_internal(i, buf, iBase, len, edigitcase);

   if (bNegative)
   {

      buf[len] = '-';

      len++;

   }

   buf[len] = '\0';

   ansi_reverse(buf, len);

   return buf;

}



