#pragma once


#include "apex/primitive/collection/common.h"
#include "apex/primitive/collection/decl.h"
#include "apex/primitive/collection/array_decl.h"
#include "apex/primitive/collection/raw_array_decl.h"
#include "apex/primitive/collection/papaya_array_decl.h"
#include "apex/primitive/collection/smart_pointer_array.h"
#include "apex/primitive/collection/comparable_eq_array.h"
#include "apex/primitive/collection/comparable_array.h"
#include "apex/primitive/collection/comparable_raw_array.h"


#include "apex/primitive/collection/sort_array.h"


#include "apex/primitive/collection/ptr_array.h"




template < class Type, class RawType >
inline stream & operator << (stream & ostream, const string_array_base < Type, RawType > & a)
{
   ostream.write(a->get_count());
   for (i32 i = 0; i < a->get_size(); i++)
   {
      ostream << a->element_at(i);
   }
   return ostream;
}


template < class Type, class RawType >
inline stream &  operator >>(stream & istream, string_array_base < Type, RawType > & a)
{

   if (istream.fail())
   {

      return;

   }

   ::count iSize;

   istream.read(iSize);

   if (istream.fail())
   {

      return;

   }

   this->remove_all();

   this->set_size(iSize);

   for (i32 i = 0; i < iSize; i++)
   {

      istream >> this->element_at(i);

      if (istream.fail())
      {

         return;

      }

   }

   if (this->get_size() != iSize)
   {

      istream.setstate(::file::failbit);

   }

   return istream;

}
