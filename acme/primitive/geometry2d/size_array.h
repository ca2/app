#pragma once


template < typename _SIZE_TYPE >
class size_array_base :
   public array < _SIZE_TYPE >
{
public:

   using SIZE_TYPE = _SIZE_TYPE;
   using SIZE_BASE_TYPE = typename SIZE_TYPE::SIZE_BASE_TYPE;
   using UNIT_TYPE = typename SIZE_TYPE::UNIT_TYPE;
   using POINT_TYPE = typename SIZE_TYPE::POINT_TYPE;


   size_array_base() { }
   virtual ~size_array_base() { }


   using array < SIZE_TYPE >::add;
   void add(UNIT_TYPE cx, UNIT_TYPE cy) { add(SIZE_TYPE(cx, cy)); }
   //void add(const POINT_TYPE & point) { add(SIZE_TYPE(point.x, point.y)); }


   void offset(const SIZE_TYPE & point) { for (auto & size : *this) size.offset(point); }
   void offset(UNIT_TYPE cx, UNIT_TYPE cy) { offset(SIZE_TYPE(cx, cy)); }


};


using size_array = size_array_base < size >;
using size64_array = size_array_base < size64 >;
using sized_array = size_array_base < sized >;





