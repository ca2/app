//
// Created by camilo on 22/10/22 21:02 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


template <  >
CLASS_DECL_ACME iptr CompareElements<const string & >(const string &  element1, const string &  element2)
{

   return element1.compare(element2);

}







string::operator+=(const ::payload & payload)
{

   return append(payload);

}


string::operator+=(const ::property & property)
{

   return append(property);

}


string::operator+=(const ::atom & atom)
{

   return append(atom);

}


string string::operator +(const ::payload & payload) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += payload;

   return ansistr;

}



string string::operator +(const ::property & property) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += property;

   return ansistr;

}



string string::operator +(const ::atom & atom) const
{

   string_base < TYPE_CHAR > ansistr(*this);

   ansistr += atom;

   return ansistr;

}