#pragma once


#include "array.h"
#include "acme/primitive/primitive/ptr.h"
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
   ptr_array(ptr_array && array) : pointer_array_process < comparable_array < TYPE * >, TYPE >(::transfer(array)) { }


   TYPE & object_at(::collection::index i) { return *this->element_at(i); }
   const TYPE & object_at(::collection::index i) const { return *this->element_at(i); }


};




