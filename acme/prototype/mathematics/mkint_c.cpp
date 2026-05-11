#include "framework.h"





CLASS_DECL_ACME int mkint32(::u32 u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (int)u;
}

CLASS_DECL_ACME  ::i64 mkint64(::u64 hn)
{
   if (hn >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (::i64)hn;
}


CLASS_DECL_ACME ::u32 natural32(int i)
{
   if (i < 0)
      return 0;
   return (::u32)i;
}

CLASS_DECL_ACME  ::u64 natural64(::i64 hi)
{
   if (hi < 0)
      return 0;
   return (::u64)hi;
}





