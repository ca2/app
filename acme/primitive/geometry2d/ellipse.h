#pragma once


template < primitive_number NUMBER >
class ellipse_base :
public ::rectangle_type < NUMBER >
{
public:


   ellipse_base() {}
   ellipse_base(const ellipse_base & ellipse) : ::rectangle_type < NUMBER >(ellipse) {}
   
   
   void set(const ::rectangle_type < NUMBER > & rectangle) { ::rectangle_type < NUMBER >::operator =(rectangle); }


};




