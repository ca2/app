#include "framework.h"





CLASS_DECL_ACME int mkint32(unsigned int u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (int)u;
}

CLASS_DECL_ACME  long long mkint64(unsigned long long hn)
{
   if (hn >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (long long)hn;
}


CLASS_DECL_ACME unsigned int natural32(int i)
{
   if (i < 0)
      return 0;
   return (unsigned int)i;
}

CLASS_DECL_ACME  unsigned long long natural64(long long hi)
{
   if (hi < 0)
      return 0;
   return (unsigned long long)hi;
}





