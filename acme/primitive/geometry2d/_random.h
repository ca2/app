// Created by camilo on 2022-11-11 11:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/mathematics/_random.h"


template < primitive_rectangle RECTANGLE >
inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r)
{ 
   
   return { __random(r.left, r.right), __random(r.top, r.bottom) };

}


template < primitive_rectangle RECTANGLE >
inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r, double dRate)
{ 
   
   auto rectangle = r; 
   
   rectangle.rate(dRate); 
   
   return random_point(rectangle); 

}



