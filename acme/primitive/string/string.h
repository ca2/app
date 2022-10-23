// Recreated by camilo on 2022-10-22 20:39 <3ThomasBorregaardSorensen!!
#pragma once


#include "__begin.h"


#include "string_base.h"


class CLASS_DECL_ACME string :
   public ansistring
{
public:


   using ansistring::ansistring;

   string(const ::string & str) : ansistring(str) {}
   string(const ::ansistring & ansistr) : ansistring(ansistr) {}
   string(const ::atom & atom);
   string(const ::payload & payload);
   string(const ::property & property);


   using ansistring::operator +=;

   string & operator += (const ::payload & payload);
   string & operator += (const ::property & property);
   string & operator += (const ::atom & atom);


   using ansistring::operator +;


   string operator + (const ::payload & payload) const;
   string operator + (const ::property & property) const;
   string operator + (const ::atom & atom) const;


};


#include "__wstring.h"



template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::operator + (const string & str) const
{


   ::string strConcatenated(*this);

   strConcatenated += str;

   return strConcatenated;


}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR >  string_base < TYPE_CHAR > ::operator + (const wstring & wstr) const
{


   ::string strConcatenated(*this);

   strConcatenated += wstr;

   return strConcatenated;


}


#include "__end.h"



