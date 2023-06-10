// Created by camilo on 2022-04-26 19:06 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"


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


template < primitive_number NUMBER >
class pole_type :
   public sequence_type < NUMBER, 3 >
{
public:


   using SIZE_TYPE = size_type < NUMBER >;
   using POINT_TYPE = size_type < NUMBER >;
   using UNIT_TYPE = NUMBER;


   pole_type(nullptr_t = nullptr) : sequence_type<NUMBER, 3>() {  }
   pole_type(enum_no_initialize) { }
   template < primitive_number X, primitive_number Y, primitive_number Z >
   pole_type(X xP, Y yP, Z zP) { this->x() = xP; this->y() = yP; this->z() = zP; }


   const UNIT_TYPE& x() const { return this->a(); }
   UNIT_TYPE& x() { return this->a(); }
   const UNIT_TYPE& y() const { return this->b(); }
   UNIT_TYPE& y() { return this->b(); }
   const UNIT_TYPE& z() const { return this->c(); }
   UNIT_TYPE& z() { return this->c(); }


   template < primitive_pole POLE >
   pole_type operator +(const POLE& pole) const
   {

      pole_type p;

      p.x() = this->x() + pole.x();
      p.y() = this->y() + pole.y();
      p.z() = this->z() + pole.z();

      return p;

   }


   template < primitive_pole POLE >
   pole_type& operator +=(const POLE& pole)
   {

      this->x() += pole.x();
      this->y() += pole.y();
      this->z() += pole.z();

      return *this;

   }


   template < primitive_pole POLE >
   pole_type& operator -=(const POLE& pole)
   {

      this->x() -= pole.x();
      this->y() -= pole.y();
      this->z() -= pole.z();

      return *this;

   }


   template < primitive_pole POLE >
   pole_type& operator = (const POLE& pole)
   {

      this->x() = pole.x();
      this->y() = pole.y();
      this->z() = pole.z();

      return *this;

   }


   template < primitive_number NUMBER_TYPE >
   pole_type& operator *= (NUMBER_TYPE n)
   {

      this->x() *= n;
      this->y() *= n;
      this->z() *= n;

      return *this;

   }


   template < primitive_number NUMBER_TYPE >
   pole_type operator * (NUMBER_TYPE n)
   {

      pole_type pole(*this);

      pole *= n;

      return pole;

   }


   SIZE_TYPE& cxy() { return (SIZE_TYPE&)*this; }
   const SIZE_TYPE& cxy()const { return (const SIZE_TYPE&)*this; }


   template < primitive_pole POLE >
   pole_type& rotate(const POLE& pole)
   {
    
      pole_type pole1;
      pole1.x() = this->x() * cos(pole.z()) - this->y() * sin(pole.z());
      pole1.y() = this->x() * sin(pole.z()) + this->y() * cos(pole.z());
      pole1.z() = this->z();

      pole_type pole2;
      pole2.y() = pole1.y() * cos(pole.x()) - pole1.z() * sin(pole.x());
      pole2.z() = pole1.y() * sin(pole.x()) + pole1.z() * cos(pole.x());
      pole2.x() = pole1.x();

      this->z() = pole2.z() * cos(pole.y()) - pole2.x() * sin(pole.y());
      this->x() = pole2.z() * sin(pole.y()) + pole2.x() * cos(pole.y());
      this->y() = pole2.y();

      return *this;

   }

   //operator POLED *() { return this; }
   //operator const POLED * () const { return this; }


};


template < primitive_pole POLE >
inline typename POLE::POINT_TYPE & __point(POLE & pole)
{

   return (typename POLE::POINT_TYPE&)(pole);

}


template < primitive_pole POLE >
inline ::point_f64 __point_f64(const POLE & pole)
{

   return { (::f64)pole.x(), (::f64)pole.y() };

}


template < primitive_pole POLE >
inline ::point_i32 u32_point_i32(const POLE & pole)
{

   return {(::i32)pole.x(), (::i32) pole.y() };

}


using pole_i32 = ::pole_type < ::i32 >;
using pole_i64 = ::pole_type < ::i64>;
using pole_f32 = ::pole_type < ::f32 >;
using pole_f64 = ::pole_type < ::f64 >;




