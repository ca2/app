#include "framework.h"
#include "string.h"
#include "_conv.h"


wd16char * __u64towd16(::u64 u, wd16char * buf, int iBase)
{

   if (u == 0)
   {

      buf[0] = (wd16char)'0';

      buf[1] = (wd16char)'\0';

      return buf;

   }

   i32 iIndex = 0;

   __natural_to_string_internal(u, buf, iBase, iIndex);

   buf[iIndex] = '\0';

   wd16_reverse(buf);

   return buf;

}


wd32char * __u64towd32(::u64 u, wd32char * buf, int iBase)
{

   if (u == 0)
   {

      buf[0] = (wd32char)'0';

      buf[1] = (wd32char)'\0';

      return buf;

   }

   i32 iIndex = 0;

   __natural_to_string_internal(u, buf, iBase, iIndex);

   buf[iIndex] = '\0';

   wd32_reverse(buf);

   return buf;

}


wd16char * __i64towd16(::i64 i, wd16char * buf, int iBase)
{


   if (i == 0)
   {

      buf[0] = (wd16char)'0';

      buf[1] = (wd16char)'\0';

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

   __natural_to_string_internal(i, buf, iBase, iIndex);

   if (bNegative)
   {

      buf[iIndex] = '-';

      iIndex++;

   }

   buf[iIndex] = '\0';

   wd16_reverse(buf);

   return buf;

}


wd32char * __i64towd32(::i64 i, wd32char * buf, int iBase)
{

   if (i == 0)
   {

      buf[0] = (wd32char)'0';

      buf[1] = (wd32char)'\0';

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

   __natural_to_string_internal(i, buf, iBase, iIndex);

   if (bNegative)
   {

      buf[iIndex] = '-';

      iIndex++;

   }

   buf[iIndex] = '\0';

   wd32_reverse(buf);

   return buf;

}




