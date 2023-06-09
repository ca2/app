//
// Created by camilo on 22/10/22 21:02 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
//#include "string.h"
//#include "acme/primitive/comparison/compare_elements.hh"



//template <  >
//CLASS_DECL_ACME iptr CompareElements<const string & >(const string * pelement1, const string *pelement2)
//{
//
//   return pelement1->compare(*pelement2);
//
//}
//
//
//string::operator+=(const ::payload & payload)
//{
//
//   return append(payload);
//
//}
//
//
//string::operator+=(const ::property & property)
//{
//
//   return append(property);
//
//}
//
//
//string::operator+=(const ::atom & atom)
//{
//
//   return append(atom);
//
//}
//
//
//string string::operator +(const ::payload & payload) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += payload;
//
//   return ansistr;
//
//}
//
//
//
//string string::operator +(const ::property & property) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += property;
//
//   return ansistr;
//
//}
//
//
//
//string string::operator +(const ::atom & atom) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += atom;
//
//   return ansistr;
//
//}


CLASS_DECL_ACME string string_from_strdup(const ::ansi_character* psz)
{

   if (psz == nullptr)
   {

      return "";

   }

   string str;

   try
   {

      str = psz;

   }
   catch (...)
   {

   }

   try
   {

      ::free((void*)psz);

   }
   catch (...)
   {

   }

   return str;

}


CLASS_DECL_ACME ::string localization_get(const ::string & str)
{

   return str;

}


CLASS_DECL_ACME ::string _(const ::string & str)
{

   return localization_get(str);

}


CLASS_DECL_ACME void foo123()
{

   ::output_debug_string("foo123");

}

