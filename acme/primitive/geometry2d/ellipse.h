#pragma once


#include "contains.h"


template < primitive_number NUMBER >
class ellipse_base :
public ::rectangle_type < NUMBER >
{
public:


   ellipse_base() {}
   ellipse_base(const ellipse_base & ellipse) : ::rectangle_type < NUMBER >(ellipse) {}
   
   
   void set(const ::rectangle_type < NUMBER > & rectangle) { ::rectangle_type < NUMBER >::operator =(rectangle); }


   bool contains(const ::point_type < NUMBER > & p)
   {

      auto center = this->center();

      auto radius = this->size() / (NUMBER)2;

      return ::ellipse_contains(center, radius, p);


   }


};




