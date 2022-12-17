// Created by camilo on 2022-12-07 23:44 <3ThomasBorregaardSorensen!!
#pragma once



template < typename ITERATOR_TYPE >
class null_terminated_iterator :
   public ITERATOR_TYPE
{
public:


   using ITERATOR = ITERATOR_TYPE;

   using ITEM = typename ITERATOR::ITEM;
   using ITERATOR_ITEM_TYPE = typename ITERATOR::ITERATOR_ITEM_TYPE;


   using ITERATOR_TYPE::ITERATOR_TYPE;


   consteval bool is_null_terminated() const { return true; }


};



