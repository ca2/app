// Created by camilo on 2022-04-26 19:06 <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"


struct POLED
{

   union
   {

      struct
      {

         double x;
         double y;
         double z;

      };

      struct
      {

         double cx;
         double cy;
         double cz;

      };

      struct
      {

         double px;
         double py;
         double pz;

      };

      double da[3];

   };


};


class CLASS_DECL_ACME poled :
   public POLED
{
public:

   poled(nullptr_t = nullptr) { x = 0.; y = 0.; z = 0.; }
   poled(enum_no_initialize) { }
   poled(double xP, double yP, double zP) { x = xP; y = yP; z = zP; }

   poled operator +(const poled & point1) const
   {

      poled poled;

      poled.x = x + point1.x;
      poled.y = y + point1.y;
      poled.z = z + point1.z;

      return poled;

   }


   poled & operator +=(const poled & poled)
   {

      x += poled.x;
      y += poled.y;
      z += poled.z;

      return *this;

   }


   poled & operator -=(const poled & poled)
   {

      x -= poled.x;
      y -= poled.y;
      z -= poled.z;

      return *this;

   }


   poled & operator = (const poled & poled)
   {

      x = poled.x;
      y = poled.y;
      z = poled.z;

      return *this;

   }

   poled & operator *= (double d)
   {

      x *= d;
      y *= d;
      z *= z;

      return *this;

   }

   poled operator * (double d)
   {

      poled pole(*this);

      pole *= d;

      return pole;

   }


   ::size_f64 & cxy() { return (::size_f64 &)*this; }
   const ::size_f64 & cxy()const { return (::size_f64 &)*this; }


   poled & rotate(const poled & d);

   operator POLED *() { return this; }
   operator const POLED * () const { return this; }


};


inline ::point_f64 __point_f64(POLED & pole)
{

   return (::point_f64 &)(pole);

}


inline ::point_i32 __point_i32(POLED & pole)
{

   return {(::i32)pole.x, (::i32) pole.y };

}




