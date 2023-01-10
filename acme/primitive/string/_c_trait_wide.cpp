#include "framework.h"
#include "string.h"
#include "_conv.h"


::wd16_character * __u64towd16(::u64 u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character * & end)
{

   end = buf;

   __tosz(u, end, iBase, edigitcase);

   return buf;

}


::wd32_character * __u64towd32(::u64 u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character * & end)
{

   end = buf;

   __tosz(u, end, iBase, edigitcase);

   return buf;

}


::wd16_character * __i64towd16(::i64 i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end)
{

   end = buf;

   __tosz(i, end, iBase, edigitcase);

   return buf;

}


::wd32_character * __i64towd32(::i64 i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character *& end)
{

   end = buf;

   __tosz(i, end, iBase, edigitcase);

   return buf;

}




