//
// Created by camilo on 2022-10-24 16:10 <3ThomasBorregaardSorensen!!
//
#pragma once
#include "string.h"
//#include "acme/primitive/collection/numeric_array.h"


template < primitive_number NUMBER >
string & get_network_payload(::string & str, const NUMBER & number, bool bNewLine = true)
{

   str = as_string(number);

   return str;

}


template < primitive_array ARRAY >
string & get_network_payload(::string & str, const ARRAY & a, bool bNewLine = true)
{

   str += "[";

   if(a.has_element())
   {

      get_network_payload(str, a.first(), bNewLine);

   }

   for (::index i = 1; i < a.get_count(); i++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      get_network_payload(str, a[i], bNewLine);

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}




