// From string/_.h by camilo on 2022-10-11 12:21 <3ThomasBorregaardSorensen!!
#pragma once


template < typename STRING >
class string_type :
   public STRING
{
public:

   using STRING_TYPE = STRING;

   STRING * this_string() { return (STRING_TYPE *)this; }
   const STRING * this_string() const { return (const STRING_TYPE *)this; }

};



