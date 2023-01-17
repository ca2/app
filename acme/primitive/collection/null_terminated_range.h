// Created by camilo on 2022-12-07 23:40 <3ThomasBorregaardSørensen!!
#pragma once


//template < typename RANGE_TYPE >
//class null_terminated_range :
//   public RANGE_TYPE
//{
//public:
//
//
//   using RANGE = RANGE_TYPE;
//   using CONST_RANGE = RANGE_TYPE::CONST_RANGE;
//
//
//   using ITERATOR = RANGE::ITERATOR;
//   using CONST_ITERATOR = ITERATOR::CONST_ITERATOR;
//
//
//   using ITEM = ITERATOR::ITEM;
//   using ITERATOR_ITEM_TYPE = ITERATOR::ITERATOR_ITEM_TYPE;
//
//
//   using RANGE_TYPE::RANGE_TYPE;
//
//
//   null_terminated_range(const ITEM * pitem) : RANGE_TYPE(pitem, find_first_null_character(pitem)) {}
//   null_terminated_range(const ITERATOR & iterator) : null_terminated_range(iterator) {}
//   null_terminated_range(const CONST_ITERATOR & iterator) : null_terminated_range(iterator) {}
//
//
//   static consteval bool is_null_terminated() { return true; }
//
//
//};
//
//
//
//
