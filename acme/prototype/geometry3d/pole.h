// Created by camilo on 2022-04-26 19:06 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"


struct DOUBLE_POLE
{

   union
   {

      struct
      {

         ::f64 x;
         ::f64 y;
         ::f64 z;

      };

      struct
      {

         ::f64 cx;
         ::f64 cy;
         ::f64 cz;

      };

      struct
      {

         ::f64 px;
         ::f64 py;
         ::f64 pz;

      };

      ::f64 da[3];

   };


};


template < prototype_number NUMBER >
class pole_type :
   public sequence_type < NUMBER, 3 >
{
public:


   using SIZE_TYPE = size_type < NUMBER >;
   using POINT_TYPE = size_type < NUMBER >;
   using UNIT_TYPE = NUMBER;


   pole_type(nullptr_t = nullptr) : sequence_type<NUMBER, 3>() {  }
   pole_type(no_initialize_t) { }
   template < prototype_number X, prototype_number Y, prototype_number Z >
   pole_type(X xP, Y yP, Z zP) { this->x = xP; this->y = yP; this->z = zP; }


   //const UNIT_TYPE& x() const { return this->x; }
   //UNIT_TYPE& x() { return this->x; }
   //const UNIT_TYPE& y() const { return this->y; }
   //UNIT_TYPE& y() { return this->y; }
   //const UNIT_TYPE& z() const { return this->c(); }
   //UNIT_TYPE& z() { return this->c(); }


   template < prototype_pole POLE >
   pole_type operator +(const POLE& pole) const
   {

      pole_type p;

      p.x = this->x + pole.x;
      p.y = this->y + pole.y;
      p.z = this->z + pole.z;

      return p;

   }


   template < prototype_pole POLE >
   pole_type& operator +=(const POLE& pole)
   {

      this->x += pole.x;
      this->y += pole.y;
      this->z += pole.z;

      return *this;

   }


   template < prototype_pole POLE >
   pole_type& operator -=(const POLE& pole)
   {

      this->x -= pole.x;
      this->y -= pole.y;
      this->z -= pole.z;

      return *this;

   }


   template < prototype_pole POLE >
   pole_type& operator = (const POLE& pole)
   {

      this->x = pole.x;
      this->y = pole.y;
      this->z = pole.z;

      return *this;

   }


   template < prototype_number NUMBER_TYPE >
   pole_type& operator *= (NUMBER_TYPE n)
   {

      this->x *= n;
      this->y *= n;
      this->z *= n;

      return *this;

   }


   template < prototype_number NUMBER_TYPE >
   pole_type operator * (NUMBER_TYPE n)
   {

      pole_type pole(*this);

      pole *= n;

      return pole;

   }


   SIZE_TYPE& cxy() { return (SIZE_TYPE&)*this; }
   const SIZE_TYPE& cxy()const { return (const SIZE_TYPE&)*this; }


   template < prototype_pole POLE >
   pole_type& rotate(const POLE& pole)
   {
    
      pole_type pole1;
      pole1.x = this->x * cos(pole.z) - this->y * sin(pole.z);
      pole1.y = this->x * sin(pole.z) + this->y * cos(pole.z);
      pole1.z = this->z;

      pole_type pole2;
      pole2.y = pole1.y * cos(pole.x) - pole1.z * sin(pole.x);
      pole2.z = pole1.y * sin(pole.x) + pole1.z * cos(pole.x);
      pole2.x = pole1.x;

      this->z = pole2.z * cos(pole.y) - pole2.x * sin(pole.y);
      this->x = pole2.z * sin(pole.y) + pole2.x * cos(pole.y);
      this->y = pole2.y;

      return *this;

   }

   //operator POLED *() { return this; }
   //operator const POLED * () const { return this; }


};


template < prototype_pole POLE >
inline typename POLE::POINT_TYPE & __point(POLE & pole)
{

   return (typename POLE::POINT_TYPE&)(pole);

}


template < prototype_pole POLE >
inline ::f64_point as_f64_point(const POLE & pole)
{

   return { (::f64)pole.x, (::f64)pole.y };

}


template < prototype_pole POLE >
inline ::i32_point as_i32_point(const POLE & pole)
{

   return {(::i32)pole.x, (::i32) pole.y };

}


using int_pole = ::pole_type < ::i32 >;
using i64_pole = ::pole_type < ::i64>;
using f32_pole = ::pole_type < ::f32 >;
using f64_pole = ::pole_type < ::f64 >;




