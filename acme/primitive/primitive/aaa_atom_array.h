#pragma once


#include "array.h"
#include "comparable_eq_array.h"
#include "comparable_array.h"


using atom_array = ::comparable_array < ::atom >;


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
atom_array __atom_array(const string_array_base < Type, RawType, m_etypeContainer > & a)
{

   atom_array atoma;

   for (::index i = 0; i < a.get_count(); i++)
   {

      atoma.add(a.element_at(i));

   }

   return atoma;

}





