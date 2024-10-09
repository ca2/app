//
// Created by camilo on 23/12/2022 16:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_impl_generic_map.h"
#include "_impl_numeric_array.h"


template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() { return ::get(this->begin()); }
template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() const { return (CONST_ITEM &) ::get(this->begin()); }






#include "acme/prototype/collection/procedure_array.h"



inline post_procedure_continuation particle::post(const ::procedure & procedure)
{
   return { this, procedure };
}
inline post_procedure_continuation particle::post()
{

   return{ this, this };
}


