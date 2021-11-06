#pragma once


template < typename POINT_TYPE >
class lines_base :
   virtual public point_array_base < POINT_TYPE >
{
public:

   using POLYGON_BASE_TYPE = point_array_base < POINT_TYPE >;
   using POINT_BASE_TYPE = typename POINT_TYPE::POINT_BASE_TYPE;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;
   using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE::RECTANGLE_BASE_TYPE;


   lines_base();
   lines_base(const lines_base& lines);
   lines_base(lines_base&& lines);
   ~lines_base();



};




template < typename POINT_TYPE >
lines_base < POINT_TYPE >::lines_base()
{

}




template < typename POINT_TYPE >
inline lines_base < POINT_TYPE >::lines_base(const lines_base& lines) :
   point_array_base < POINT_TYPE >(lines)
{

}


template < typename POINT_TYPE >
inline lines_base < POINT_TYPE >::lines_base(lines_base&& lines) :
   point_array_base < POINT_TYPE >(::move(lines))
{


}



template < typename POINT_TYPE >
lines_base < POINT_TYPE >::~lines_base()

{

}


using lines_i32 = lines_base < point_i32 >;
using lines_i64 = lines_base < point_i64 >;
using lines_f32 = lines_base < point_f32 >;
using lines_f64 = lines_base < point_f64 >;



