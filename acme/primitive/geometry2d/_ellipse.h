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




