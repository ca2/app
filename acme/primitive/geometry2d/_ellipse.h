#pragma once


template < typename RECTANGLE_TYPE >
class ellipse_base :
   public RECTANGLE_TYPE
{
public:

   
   using RECTANGLE_BASE_TYPE = RECTANGLE_TYPE;


   ellipse_base() {}
   ellipse_base(const ellipse_base & ellipse) : RECTANGLE_TYPE(ellipse) {}
   
   
   template < primitive_rectangle RECTANGLE >
   void set(const RECTANGLE & rectangle) { RECTANGLE_TYPE::operator =(rectangle); }


};




