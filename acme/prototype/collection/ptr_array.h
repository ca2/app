#pragma once


#include "array.h"
#include "acme/prototype/prototype/ptr.h"
#include "comparable_eq_array.h"
#include "comparable_array.h"
#include "pointer_array_process.h"


template < class T >
class ptr_array :
   public pointer_array_process < comparable_array < ::ptr < T >, const T * >, T >
{
public:

   using BASE_ARRAY = pointer_array_process < comparable_array < ::ptr < T >, const T * > , T >;


   ptr_array() { }
   ptr_array(const ptr_array& array) : BASE_ARRAY(array) { }
   ptr_array(ptr_array && array) : BASE_ARRAY(::transfer(array)) { }


   T & object_at(::collection::index i) { return *this->element_at(i); }
   const T & object_at(::collection::index i) const { return *this->element_at(i); }


   ptr_array & operator=(const ptr_array & ptra) { BASE_ARRAY::operator=(ptra); return *this; }
   ptr_array & operator=(ptr_array && ptra) { BASE_ARRAY::operator=(::transfer(ptra)); return *this; }


};




