#pragma once


#include "contains.h"
#include "rectangle.h"


template < prototype_number NUMBER >
class ellipse_type :
   public ::rectangle_type < NUMBER >
{
public:


   ellipse_type() {}
   template < prototype_number NUMBER2 >
   ellipse_type(const ellipse_type < NUMBER2 > & ellipse)
   {
   
   
   
   }
   
   
   void set(const ::rectangle_type < NUMBER > & rectangle) { ::rectangle_type < NUMBER >::operator =(rectangle); }
   
   auto radius() const { return this->size() / (NUMBER) 2; }

   static bool contains(const ::point_type < NUMBER > & center, const ::size_type < NUMBER > & radius,
                        const ::point_type < NUMBER > & point)

   {
      
      if (radius.is_empty())
      {

         return false;

      }

      ::f64 x = point.x;

      ::f64 y = point.y;

      ::f64 Δx = x - center.x;

      ::f64 Δy = y - center.y;

      if (radius.cx == radius.cy)
      {

         ::f64 r = radius.cx;

         ::f64 square_distance = (Δx * Δx) + (Δy * Δy);

         ::f64 square_boundary = (r * r);

         return square_distance <= square_boundary;

      }
      else
      {

         ::f64 normal_distance = ((Δx * Δx) / (radius.cx * radius.cx) + (Δy * Δy) / (radius.cx * radius.cy));

         return normal_distance <= 1.0;

      }

   }
   
   
   bool contains(const ::point_type < NUMBER > & point)
   {
      
      if(!::rectangle_type < NUMBER >::contains(point))
      {
         
         return false;
         
      }
      
      auto center = this->center();

      auto radius = this->radius();

      if (!contains(center, radius, point))
      {

         return false;

      }

      return true;

   }


};




