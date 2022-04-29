// Created by camilo on 2022-04-24 04:50 <3ThomasBorregaardSørensen!!
#include "framework.h"


#if defined(__GNUC__) && __GNUC__ < 11

CLASS_DECL_ACME void to_string(string & str, const unsigned long & ul)
{

   str = ui64toa_dup(ul, 10);

}


CLASS_DECL_ACME void to_string(string & str, const long int & i)
{

   str = i64toa_dup(i);

}


#endif



