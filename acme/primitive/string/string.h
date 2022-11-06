// Recreated by camilo on 2022-10-22 20:39 <3ThomasBorregaardSorensen!!
#pragma once


#include "__begin.h"


#include "string_base.h"


#include "__end.h"


CLASS_DECL_ACME string demangle(const char * psz);


CLASS_DECL_ACME void copy(::string & str, const particle & particle);


template < typename TYPE >
inline ::string __string(const TYPE & t)
{

   ::string str;

   ::copy(str, t);

   return ::move(str);

}


//template < has_copy_to_string HAS_COPY_TO_STRING >
//inline ::string __string(const HAS_COPY_TO_STRING & hascopytostring)
//{
//
//   ::string str;
//
//   ::copy(str, hascopytostring);
//
//   return ::move(str);
//
//}


CLASS_DECL_ACME string string_from_strdup(const ansichar* psz);



