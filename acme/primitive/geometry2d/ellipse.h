#pragma once


#include "contains.h"
#include "rectangle.h"


template < primitive_number NUMBER >
class ellipse_type :
   public ::rectangle_type < NUMBER >
{
public:


   ellipse_type() {}
   template < primitive_number NUMBER2 >
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

      double x = point.x();

      double y = point.y();

      double greekdeltax = x - center.x();

      double greekdeltay = y - center.y();

      if (radius.cx() == radius.cy())
      {

         double r = radius.cx();

         double square_distance = (greekdeltax * greekdeltax) + (greekdeltay * greekdeltay);

         double square_boundary = (r * r);

         return square_distance <= square_boundary;

      }
      else
      {

         double normal_distance = ((greekdeltax * greekdeltax) / (radius.cx() * radius.cx()) + (greekdeltay * greekdeltay) / (radius.cx() * radius.cy()));

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




