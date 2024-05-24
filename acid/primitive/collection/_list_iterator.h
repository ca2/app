//
// Created by camilo on 23/12/2022 01:57 <3ThomasBorregaardSorensen!!
//
#pragma once


template < typename BASE_ITERATOR_TYPE >
constexpr ::collection::count make_list_iterator < BASE_ITERATOR_TYPE >::operator - (const_iterator iterator) const
{

   ::collection::count c;

   if (difference(c, *this, iterator))
   {

      return c;

   }

   if (difference(c, iterator, *this))
   {

      return -c;

   }

   throw_exception(error_failed, "iterators aren't from same list");

   return -1;

}



