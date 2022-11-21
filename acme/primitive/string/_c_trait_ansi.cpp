#include "framework.h"
#include "string.h"
#include "_conv.h"


ansichar * __u64toansi(::u64 u, ansichar * buf, int iBase, ansichar ansichTen)
{

   if (u == 0)
   {

      buf[0] = (ansichar)'0';

      buf[1] = (ansichar)'\0';

      return buf;

   }

   i32 iIndex = 0;

   __natural_to_string_internal(u, buf, iBase, iIndex, ansichTen);

   buf[iIndex] = '\0';

   ansi_reverse(buf);

   return buf;

}




ansichar * __i64toansi(::i64 i, ansichar * buf, int iBase, ansichar ansichTen)
{


   if (i == 0)
   {

      buf[0] = (ansichar)'0';

      buf[1] = (ansichar)'\0';

      return buf;

   }

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

   i32 iIndex = 0;

   __natural_to_string_internal(i, buf, iBase, iIndex, ansichTen);

   if (bNegative)
   {

      buf[iIndex] = '-';

      iIndex++;

   }

   buf[iIndex] = '\0';

   ansi_reverse(buf);

   return buf;

}






