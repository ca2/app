#pragma once


#include "array.h"
#include "comparable_eq_array.h"
#include "comparable_array.h"
#include "pointer_array_process.h"


template < typename TYPE >
class raw_pointer_array :
   public pointer_array_process < comparable_array < TYPE * >, TYPE >
{
public:


   using pointer_array_process < comparable_array < TYPE * >, TYPE >::pointer_array_process;


   raw_pointer_array() { }
   raw_pointer_array(raw_pointer_array && array) : pointer_array_process < comparable_array < TYPE * >, TYPE >(::transfer(array)) { }


   TYPE & object_at(::collection::index i) { return *this->element_at(i); }
   const TYPE & object_at(::collection::index i) const { return *this->element_at(i); }


};




