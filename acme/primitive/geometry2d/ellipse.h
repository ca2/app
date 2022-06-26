#pragma once


template < typename RECTANGLE_TYPE >
class ellipse_base :
   public RECTANGLE_TYPE
{
public:

   
   using RECTANGLE_BASE_TYPE = RECTANGLE_TYPE;


   ellipse_base() {}
   ellipse_base(const RECTANGLE_TYPE & ellipse) : RECTANGLE_TYPE(ellipse) { }


};


using ellipse_i32 = ellipse_base < rectangle_i32 >;
using ellipse_i64 = ellipse_base < rectangle_i64 >;
using ellipse_f32 = ellipse_base < rectangle_f32 >;
using ellipse_f64 = ellipse_base < rectangle_f64 >;


using ellipse = ::ellipse_f64;


