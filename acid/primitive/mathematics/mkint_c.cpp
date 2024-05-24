#include "framework.h"





CLASS_DECL_ACID i32 mkint32(u32 u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (i32)u;
}

CLASS_DECL_ACID  i64 mkint64(u64 ull)
{
   if (ull >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (i64)ull;
}


CLASS_DECL_ACID u32 natural32(i32 i)
{
   if (i < 0)
      return 0;
   return (u32)i;
}

CLASS_DECL_ACID  u64 natural64(i64 ll)
{
   if (ll < 0)
      return 0;
   return (u64)ll;
}





