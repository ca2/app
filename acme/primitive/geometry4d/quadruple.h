// Merge of estamira/particle/vec4 with geometry/sequence.h by
// camilo on 2023-06-03 21:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/geometry/sequence.h"


template < primitive_number NUMBER >
struct quadruple_type :
   public sequence_type < NUMBER, 4 >
{

   
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


   quadruple_type() {}
   quadruple_type(no_initialize_t) : sequence_type < NUMBER, 2 >(no_initialize_t{}) {}
   //point_type(::std::nullptr_t) : sequence_type < NUMBER, 2 >(nullptr) {}

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
   quadruple_type(UNIT_TYPE n)
   {
   
      this->set_all(n);
      
   }
//   quadruple_type() {};
//   quadruple_type(float f) { x = y = z = f; };
//   quadruple_type(const quadruple_type & v) = default;
   //quadruple_type(quadruple_type && v) = default;
   quadruple_type(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c = 0, UNITYPE_ d = 0) { x = a; y = b; z = c; w = d; }
   
   template < primitive_number NUMBER1 >
   point_type(const sequence_type < NUMBER1, 4 > & sequence) :
      sequence_type < UNIT_TYPE, 4 >(sequence)
   {
      
   }
   
//   quadruple_type(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c) { x = a; y = b; z = c; w = 0.0f; }
//   quadruple_type(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d) { x = a; y = b; z = c; w = d; }
//   //~quadruple_type() = default;
   
   const UNIT_TYPE & x() const {return this->a();}
   UNIT_TYPE & x() {return this->a();}
   const UNIT_TYPE & y() const {return this->b();}
   UNIT_TYPE & y() {return this->b();}
   const UNIT_TYPE & z() const {return this->c();}
   UNIT_TYPE & z() {return this->c();}
   const UNIT_TYPE & w() const {return this->d();}
   UNIT_TYPE & w() {return this->d();}


   quadruple_type & operator =(const quadruple_type & v) = default;

   //inline void setAll(UNIT_TYPE f) { x = y = z = w = f; }

   // simple menthods: operates on x, y
   inline void add2(const quadruple_type & a) 
   {
      this->x() += a.x();
      this->y() += a.y();
   }
   inline void sub2(const quadruple_type & a)
   {
      this->x() -= a.x();
      this->y() -= a.y(); 
   }
   inline void mul2(UNIT n) 
   {
      this->x() *= n; 
      this->y() *= n;
   }
   inline void set2(UNIT_TYPE a, UNIT_TYPE b) 
   {
      this->x() = a; 
      this->y() = b; 
   }

   static inline void mix2(const quadruple_type &a, const quadruple_type &b, UNIT_TYPE t, quadruple_type &c)
   {
      c.x() = a.x()*((UNIT_TYPE)1.0 - t) + b.x()*t;
      c.y() = a.y()*((UNIT_TYPE)1.0 - t) + b.y()*t;
   }

   // simple menthods: operates on x, y, z
   inline void add3(const quadruple_type & a) 
   {
      this->x() += a.x(); 
      this->y() += a.y();
      this->z() += a.z();
   }
   inline void sub3(const quadruple_type & a)
   {
      this->x() -= a.x();
      this->y() -= a.y();
      this->z() -= a.z(); 
   }
   inline void mul3(UNIT_TYPE n) 
   { 
      this->x() *= n; 
      this->y() *= n;
      this->z() *= n;
   }
   inline void set3(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c)
   {
      this->x() = a;
      this->y() = b;
      this->z() = c; 
   }

   static inline void mix3(const quadruple_type &a, const quadruple_type &b, UNIT_TYPE t, quadruple_type &c)
   {
      c.x() = a.x()*((UNIT_TYPE)1.0 - t) + b.x()*t;
      c.y() = a.y()*((UNIT_TYPE)1.0 - t) + b.y()*t;
      c.z() = a.z()*((UNIT_TYPE)1.0 - t) + b.z()*t;
   }

   // simple menthods: operates on x, y, z, w
   inline void add4(const quadruple_type & q)
   {
      this->x() += q.x();
      this->y() += q.y();
      this->z() += q.z();
      this->w() += q.w();
   }
   inline void sub4(const quadruple_type & q)
   {
      this->x() -= q.x();
      this->y() -= q.y();
      this->z() -= q.z();
      this->w() -= q.w();
   }
   inline void mul4(UNIT_TYPE n)
   {
      this->x() *= n;
      this->y() *= n;
      this->z() *= n;
      this->w() *= n;
   }
   inline void set4(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d)
   {
      this->x() = a;
      this->y() = b;
      this->z() = c;
      this->w() = d;
   }

   static inline void mix4(const quadruple_type &a, const quadruple_type &b, UNIT_TYPE t, quadruple_type &c)
   {
      c.x() = a.x()*((UNIT_TYPE)1.0 - t) + b.x()*t;
      c.y() = a.y()*((UNIT_TYPE)1.0 - t) + b.y()*t;
      c.z() = a.z()*((UNIT_TYPE)1.0 - t) + b.z()*t;
      c.w() = a.w()*((UNIT_TYPE)1.0 - t) + b.w()*t;
   }

   inline quadruple_type operator *(UNIT_TYPE n) const
   {
      return quadruple_type(this->x() * n, this->y() * n, this->z() * n, this->w() * n);
   }

   inline quadruple_type operator /(UNIT_TYPE n) const
   {
      return quadruple_type(this->x() / n, this->y() / n, this->z() / n, this->w() / n);
   }

   inline quadruple_type operator +(const quadruple_type & q) const
   {
      return quadruple_type(this->x() + q.x(), this->y() + q.y(), this->z() + q.z(), this->w() + q.w());
   }

   inline quadruple_type operator -(const quadruple_type & t) const
   {
      return quadruple_type(this->x() - t.x(), this->y() - t.y(), this->z() - t.z(), this->w() - t.w());
   }

   inline quadruple_type & operator +=(const quadruple_type & a)
   {
      this->add4(a);
      return *this;
   }

   inline quadruple_type & operator -=(const quadruple_type & a)
   {
      this->sub4(a);
      return *this;
   }

   inline UNIT_TYPE dot(const quadruple_type & q) const
   {
      return this->x() * q.x() + this->y() * q.y() + this->z() * q.z() + this->w() * q.w();
   }

};


using quadruple_f32 = quadruple_type < ::f32 >;
using quadruple_f64 = quadruple_type < ::f64 >;


template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline quadruple < largest_number < NUMBER1, NUMBER2 > > operator * (NUMBER1 n, const quadruple < NUMBER2 > & q)
{

   return quadruple < largest_number < NUMBER1, NUMBER2 > >(n * q.x(), n * q.y(), n * q.z(), n * q.w());
}


template < typename UNIT_TYPE >
inline UNIT_TYPE linear_rand(const UNIT_TYPE & t1, const UNIT_TYPE & t2)
{
   if (t2 == t1)
      return t1;
   return ((t2 - t1) * rand()/ RAND_MAX) + t1;

}

template < primitive_number NUMBER >
inline quadruple < NUMBER > linear_rand(const quadruple < NUMBER > & t1, const quadruple < NUMBER > & t2)
{

   return quadruple < NUMBER >(
          linear_rand(t1.x(), t2.x()),
          linear_rand(t1.y(), t2.y()),
          linear_rand(t1.z(), t2.z()),
          linear_rand(t1.w(), t2.w()));

}
