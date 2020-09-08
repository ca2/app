#pragma once


#include <math.h>


class CLASS_DECL_ACME q4 :
   public Q4
{
public:


   q4()
   {

      // randomly filled

   }

   q4(const q4 & q)
   {

      operator = (q);

   }


   q4(double w1,double x1,double y1,double z1)
   {

      w = w1;
      x = x1;
      y = y1;
      z = z1;

   }


   double sqsize()
   {
      
      return w * w + x * x + y * y + z * z;

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

      q.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
      q.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
      q.y = w * q2.y - x * q2.z + y * q2.w + z * q2.x;
      q.z = w * q2.z + x * q2.y - y * q2.x + z * q2.w;

      return q;

   }

   q4 & operator *= (const q4 & q2)
   {

      q4 q1(*this);

      return operator = (q1 * q2);

   }


   q4 & operator = (const q4 & q2)
   {

      w = q2.w;
      x = q2.x;
      y = q2.y;
      z = q2.z;

      return *this;

   }

};
