#include "framework.h"





CLASS_DECL_ACME int mkint32(unsigned int u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (int)u;
}

CLASS_DECL_ACME  huge_integer mkint64(huge_natural hn)
{
   if (hn >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (huge_integer)hn;
}


CLASS_DECL_ACME unsigned int natural32(int i)
{
   if (i < 0)
      return 0;
   return (unsigned int)i;
}

CLASS_DECL_ACME  huge_natural natural64(huge_integer hi)
{
   if (hi < 0)
      return 0;
   return (huge_natural)hi;
}





