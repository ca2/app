#pragma once



struct CLASS_DECL_ACME LOCATIOND
{
   double x;
   double y;
   double z;
};

using LPLOCATIOND = LOCATIOND * ;
using LPCLOCATIOND = const LOCATIOND*;

class CLASS_DECL_ACME locationd:
   public LOCATIOND
{
public:

   locationd() {}
   locationd(double xP,double yP,double zP) { x = xP; y=yP; z=zP; }

   locationd  operator +(const locationd & point1) const
   {
      
      locationd locationd;

      locationd.x = x + point1.x;
      locationd.y = y + point1.y;
      locationd.z = z + point1.z;

      return locationd;

   }


   locationd & operator +=(const locationd &locationd)
   {

      x += locationd.x;
      y += locationd.y;
      z += locationd.z;

      return *this;

   }


   locationd & operator -=(const locationd & locationd)
   {

      x -= locationd.x;
      y -= locationd.y;
      z -= locationd.z;

      return *this;

   }


   locationd & operator = (const locationd & locationd)
   {

      x = locationd.x;
      y = locationd.y;
      z = locationd.z;

      return *this;

   }


   locationd rotate(locationd d);

   operator LPLOCATIOND() { return this; }
   operator LPCLOCATIOND() const { return this; }


};


inline ::point __point(LPCLOCATIOND plocation)
{
   return ::point((::i32)plocation->x, (::i32)plocation->y);
}












