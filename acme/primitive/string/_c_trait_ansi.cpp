#include "framework.h"
//#include "string.h"
//#include "_conv.h"


::ansi_character * __u64toansi(::u64 u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character *& end)
{

   end = buf;

   __tosz(u, end, iBase, edigitcase);

   return buf;

}


::ansi_character * __i64toansi(::i64 i, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character *& end)
{

   end = buf;

   __tosz(i, end, iBase, edigitcase);

   return buf;

}



