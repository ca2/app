#include "framework.h"
#include "string.h"
#include "_conv.h"


::wd16_character * __u64towd16(huge_natural u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character * & end)
{

   end = buf;

   __tosz(u, end, iBase, edigitcase);

   return buf;

}


::wd32_character * __u64towd32(huge_natural u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character * & end)
{

   end = buf;

   __tosz(u, end, iBase, edigitcase);

   return buf;

}


::wd16_character * __huge_integertowd16(huge_integer i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end)
{

   end = buf;

   __tosz(i, end, iBase, edigitcase);

   return buf;

}


::wd32_character * __huge_integertowd32(huge_integer i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character *& end)
{

   end = buf;

   __tosz(i, end, iBase, edigitcase);

   return buf;

}




