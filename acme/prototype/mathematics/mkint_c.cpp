#include "framework.h"





CLASS_DECL_ACME int mkint32(unsigned int u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (int)u;
}

CLASS_DECL_ACME  i64 mkint64(u64 ull)
{
   if (ull >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (i64)ull;
}


CLASS_DECL_ACME unsigned int natural32(int i)
{
   if (i < 0)
      return 0;
   return (unsigned int)i;
}

CLASS_DECL_ACME  u64 natural64(i64 ll)
{
   if (ll < 0)
      return 0;
   return (u64)ll;
}





