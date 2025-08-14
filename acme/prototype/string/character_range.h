// Created by camilo on 2025-04-17 09:37 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/range.h"


template < typename ITERATOR_TYPE >
class character_range :
   public ::range < ITERATOR_TYPE >
{
public:

   using BASE_RANGE = ::range < ITERATOR_TYPE >;

   using BASE_RANGE::BASE_RANGE;


};



