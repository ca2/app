#pragma once


#include <math.h>

struct Q4
{

   double w;
   double x;
   double y;
   double z;

};


template < primitive_number NUMBER >
class q4 :
   public sequence_type < NUMBER, 4 >
{
public:


   using UNIT_TYPE = NUMBER;


   q4()
   {

      // randomly filled

   }

   q4(const q4 & q)
   {

      operator = (q);

   }

   template < primitive_number W, primitive_number X, primitive_number Y, primitive_number Z >
   q4(W w, X x, Y y, Z z)
   {

      this->w() = (UNIT_TYPE) w;
      this->x() = (UNIT_TYPE) x;
      this->y() = (UNIT_TYPE) y;
      this->z() = (UNIT_TYPE) z;

   }


   double sqsize()
   {
      
      return this->w() * this->w() + this->x() * this->x() + this->y() * this->y() + this->z() * this->z();

   }


   double size()
   {

      return sqrt(sqsize());

   }


   q4 operator * (const q4 & q2)
   {
      if(this == &q2)
      {
         return operator *(q4(q2));
      }

      q4 q;

      q.w() = this->w() * q2.w() - this->x() * q2.x() - this->y * q2.y() - this->z() * q2.z();
      q.x() = this->w() * q2.x() + this->x() * q2.w() + this->y * q2.z() - this->z() * q2.y();
      q.y() = this->w() * q2.y() - this->x() * q2.z() + this->y * q2.w() + this->z() * q2.x();
      q.z() = this->w() * q2.z() + this->x() * q2.y() - this->y * q2.x() + this->z() * q2.w();

      return q;

   }

   q4 & operator *= (const q4 & q2)
   {

      q4 q1(*this);

      return operator = (q1 * q2);

   }


   q4 & operator = (const q4 & q2)
   {

      this->w() = q2.w();
      this->x() = q2.x();
      this->y() = q2.y();
      this->z() = q2.z();

      return *this;

   }

};
