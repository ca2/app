#pragma once


#include "size.h"


template < primitive_number NUMBER >
class size_array_base :
public ::array_base < ::size_type < NUMBER > >
{
public:

   using BASE_ARRAY = ::array_base < ::size_type < NUMBER > >;
   //using SIZE_TYPE = _SIZE_TYPE;
   //using SIZE_BASE_TYPE = SIZE_TYPE;
   using UNIT_TYPE = NUMBER;
   //using POINT_TYPE = typename SIZE_TYPE::POINT_TYPE;

   using BASE_ARRAY::BASE_ARRAY;
   using BASE_ARRAY::operator =;

   //size_array_base() { }
   ///~size_array_base() override { }


   using array_base < ::size_type < NUMBER > >::add;
   void add(UNIT_TYPE cx, UNIT_TYPE cy) { add(SIZE_TYPE(cx, cy)); }
   //void add(const POINT_TYPE & point) { add(SIZE_TYPE(point.x(), point.y())); }


   void offset(const ::size_type < NUMBER > & size) { for (auto & sizeItem : *this) sizeItem.offset(size); }
   void offset(UNIT_TYPE cx, UNIT_TYPE cy) { offset(::size_type < NUMBER >(cx, cy)); }


};


//using int_size_array = size_array_base < int >;
//using long_long_size_array = size_array_base < long long >;
//using float_size_array = size_array_base < float >;
//using double_size_array = size_array_base < double >;



