//
//  color.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/06/23.
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
// Merge of estamira/particle/vec4 with geometry/sequence.h by
// camilo on 2023-06-03 21:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/graphics/draw2d/color.h"
#include "acme/primitive/geometry/sequence.h"


template < primitive_number NUMBER >
struct color_type :
   public sequence_type < NUMBER, 4 >
{
protected:
   
   using sequence_type < NUMBER, 4 >::a;
   using sequence_type < NUMBER, 4 >::b;
   using sequence_type < NUMBER, 4 >::c;
   using sequence_type < NUMBER, 4 >::d;

public:
   
   using UNIT_TYPE = NUMBER;
//   union
//   {
//      UNIT_TYPE m[4];
//
//      struct
//      {
//         UNIT_TYPE x, y, z, w;
//      };
//
//      struct
//      {
//         UNIT_TYPE r, g, b, a;
//      };
//   };


   color_type() {}
   color_type(no_initialize_t) : sequence_type < NUMBER, 2 >(no_initialize_t{}) {}
   //point_type(::std::nullptr_t) : sequence_type < NUMBER, 2 >(nullptr) {}

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
   color_type(UNIT_TYPE n)
   {
   
      this->set_all(n);
      
   }
//   color_type() {};
//   color_type(float f) { x = y = z = f; };
//   color_type(const color_type & v) = default;
   //color_type(color_type && v) = default;
   color_type(UNIT_TYPE r, UNIT_TYPE g, UNIT_TYPE b, UNIT_TYPE a = 0) :
   sequence_type < UNIT_TYPE, 4 >(r, g, b, a)
   {
   }
   
   template < primitive_number NUMBER1 >
   color_type(const sequence_type < NUMBER1, 4 > & sequence) :
      sequence_type < UNIT_TYPE, 4 >(sequence)
   {
      
   }
   
//   color_type(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c) { x = a; y = b; z = c; w = 0.0f; }
//   color_type(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d) { x = a; y = b; z = c; w = d; }
//   //~color_type() = default;
   
   const UNIT_TYPE & red() const {return this->a();}
   UNIT_TYPE & red() {return this->a();}
   const UNIT_TYPE & green() const {return this->b();}
   UNIT_TYPE & green() {return this->b();}
   const UNIT_TYPE & blue() const {return this->c();}
   UNIT_TYPE & blue() {return this->c();}
   const UNIT_TYPE & opacity() const {return this->d();}
   UNIT_TYPE & opacity() {return this->d();}


   color_type & operator =(const color_type & v) = default;

   //inline void setAll(UNIT_TYPE f) { x = y = z = w = f; }

   inline color_type operator *(UNIT_TYPE n) const
   {
      return color_type(this->x() * n, this->y() * n, this->z() * n, this->w() * n);
   }

   inline color_type operator /(UNIT_TYPE n) const
   {
      return color_type(this->x() / n, this->y() / n, this->z() / n, this->w() / n);
   }

   inline color_type operator +(const color_type & q) const
   {
      return color_type(this->x() + q.x(), this->y() + q.y(), this->z() + q.z(), this->w() + q.w());
   }

   inline color_type operator -(const color_type & t) const
   {
      return color_type(this->x() - t.x(), this->y() - t.y(), this->z() - t.z(), this->w() - t.w());
   }

   inline color_type & operator +=(const color_type & a)
   {
      this->add4(a);
      return *this;
   }

   inline color_type & operator -=(const color_type & a)
   {
      this->sub4(a);
      return *this;
   }

//   inline UNIT_TYPE dot(const color_type & q) const
//   {
//      return this->x() * q.x() + this->y() * q.y() + this->z() * q.z() + this->w() * q.w();
//   }
   
   ::color::color color() const
   {
      
      return ::rgba(
         this->red(),
         this->green(),
         this->blue(),
         this->opacity());
      
   }

};


using color_f32 = color_type < ::f32 >;
using color_f64 = color_type < ::f64 >;


template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline color_type < largest_number < NUMBER1, NUMBER2 > > operator * (NUMBER1 n, const color_type < NUMBER2 > & q)
{

   return color_type < largest_number < NUMBER1, NUMBER2 > >(n * q.x(), n * q.y(), n * q.z(), n * q.w());
}
