#pragma once


template < typename POINTER_TYPE >
class ptr_array :
   public pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >
{
public:


   using pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >::pointer_array_process;


   ptr_array() { }
   ptr_array(ptr_array && array) : pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >(::move(array)) { }


   POINTER_TYPE & object_at(::index i) { return *this->element_at(i); }
   const POINTER_TYPE & object_at(::index i) const { return *this->element_at(i); }


};




