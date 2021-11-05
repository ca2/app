#pragma once


#include "acme/primitive/collection/common.h"
#include "acme/primitive/collection/decl.h"
#include "acme/primitive/collection/array_decl.h"
#include "acme/primitive/collection/raw_array_decl.h"
#include "acme/primitive/collection/papaya_array_decl.h"
#include "acme/primitive/collection/smart_pointer_array.h"
#include "acme/primitive/collection/comparable_eq_array.h"
#include "acme/primitive/collection/comparable_array.h"
#include "acme/primitive/collection/comparable_raw_array.h"


#include "acme/primitive/collection/sort_array.h"


#include "acme/primitive/collection/ptr_array.h"




template < typename Type, typename RawType, enum_type t_etypePayload >
inline stream & operator << (stream & ostream, const string_array_base < Type, RawType, t_etypePayload > & a)
{
   ostream.write(a->get_count());
   for (i32 i = 0; i < a->get_size(); i++)
   {
      ostream << a->element_at(i);
   }
   return ostream;
}


template < typename Type, typename RawType, enum_type t_etypePayload >
inline stream &  operator >>(stream & istream, string_array_base < Type, RawType, t_etypePayload > & a)
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

   this->erase_all();

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
