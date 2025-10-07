/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
// Merge with estamira/particle/vec4:minimum_maximum_rand
#pragma once


//#include "common.h"
//#include "traits.h"
//#include <cassert>
#include <cmath>
//#include <iosfwd>
//#include <string.h> // ::memory_set



template < primitive_number COORDINATE, ::collection::count t_iSize >
struct sequence_type
{

   using sequence_tag = sequence_t;
   using sequence_size = sequence_size_t < t_iSize >;
   using BASE_COORDINATE = COORDINATE;
   using UNIT_TYPE = COORDINATE;


   COORDINATE m_coordinatea[t_iSize];


   static constexpr bool IS_MATRIX = false;
   static constexpr ::collection::count SIZE = t_iSize;


   constexpr sequence_type()
   {
   
      set_all(0);
      
   }

   sequence_type(no_initialize_t)
   {
      
      
   }


   constexpr sequence_type(UNIT_TYPE n)
   {

     set_all(n);

   }

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
//   sequence_type(const T & a) {
//      for (::collection::count i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = (COORDINATE)a[i];
//   }

   template < primitive_number NUMBER1, ::collection::count S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   constexpr sequence_type(const sequence_type < NUMBER1, 2 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
   }

   
   template < primitive_number NUMBER1, ::collection::count S = SIZE, std::enable_if_t<S == 3, int> = 0 >
   constexpr sequence_type(const sequence_type < NUMBER1, 3 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
   }

   
   template < primitive_number NUMBER1, ::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0 >
   constexpr sequence_type(const sequence_type < NUMBER1, 4 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
      m_coordinatea[3] = (UNIT_TYPE) sequence.m_coordinatea[3];
   }

//   sequence_type(COORDINATE s) {
//      for (::collection::count i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = s;
//   }

   template < ::collection::count S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   constexpr sequence_type(COORDINATE coordinate0, COORDINATE coordinate1)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
   }

   
   template <::collection::count S = SIZE, std::enable_if_t<S == 3, int> = 0>
   constexpr sequence_type(COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
      m_coordinatea[2] = coordinate2;
   }

   
   template <::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0>
   constexpr sequence_type(
                 COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2, COORDINATE coordinate3)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
      m_coordinatea[2] = coordinate2;
      m_coordinatea[3] = coordinate3;
   }


   constexpr ::collection::count get_size() const { return SIZE; }
   constexpr ::collection::count get_count() const { return this->get_size(); }
   
   
   constexpr COORDINATE & set_coordinate(::collection::index i, COORDINATE coordinate)
   {

      return m_coordinatea[i] = coordinate;

   }


   constexpr COORDINATE coordinate(::collection::index i) const
   {

      return m_coordinatea[i];

   }

   
   constexpr COORDINATE & coordinate(::collection::index i)
   {

      return m_coordinatea[i];

   }


   void set_all(COORDINATE coordinate)
   {
      
      for (::collection::count i = 0; i < SIZE; ++i)
      {
         
         m_coordinatea[i] = coordinate;
         
      }
      
   }
   
   bool is_all(COORDINATE coordinate) const
   {
      
      for (::collection::count i = 0; i < SIZE; ++i)
      {
         
         if(m_coordinatea[i] != coordinate)
         {
          
            return false;
            
         }
         
      }
      
      return true;
      
   }



   // simple menthods: operates on x, y
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void add2(const sequence_type & a)
   {
      this->a() += a.a();
      this->b() += a.b();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void sub2(const sequence_type & a)
   {
      this->a() -= a.a();
      this->b() -= a.b();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void mul2(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void set2(UNIT_TYPE a, UNIT_TYPE b)
   {
      this->a() = a;
      this->b() = b;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   static inline void mix2(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
   }

   // simple menthods: operates on x, y, z
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void add3(const sequence_type & a)
   {
      this->a() += a.a();
      this->b() += a.b();
      this->c() += a.c();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void sub3(const sequence_type & a)
   {
      this->a() -= a.a();
      this->b() -= a.b();
      this->c() -= a.c();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void mul3(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
      this->c() *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void set3(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c)
   {
      this->a() = a;
      this->b() = b;
      this->c() = c;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   static inline void mix3(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
      c.c() = a.c()*((UNIT_TYPE)1.0 - t) + b.c()*t;
   }

   // simple menthods: operates on x, y, z, w
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void add4(const sequence_type & q)
   {
      this->a() += q.a();
      this->b() += q.b();
      this->c() += q.c();
      this->d() += q.d();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void sub4(const sequence_type & q)
   {
      this->a() -= q.a();
      this->b() -= q.b();
      this->c() -= q.c();
      this->d() -= q.d();
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void mul4(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
      this->c() *= n;
      this->d() *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void set4(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d)
   {
      this->a() = a;
      this->b() = b;
      this->c() = c;
      this->d() = d;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   static inline void mix4(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
      c.c() = a.c()*((UNIT_TYPE)1.0 - t) + b.c()*t;
      c.d() = a.d()*((UNIT_TYPE)1.0 - t) + b.d()*t;
   }


   sequence_type operator-() const
   {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = -m_coordinatea[i];
      return result;
   }

   
   friend sequence_type operator +(const sequence_type& a, const sequence_type& b)
   {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] + b.m_coordinatea[i];
      return result;
   }

   sequence_type& operator +=(const sequence_type& a) {
      for (::collection::count i = 0; i < SIZE; ++i)
         m_coordinatea[i] += a.m_coordinatea[i];
      return *this;
   }

   friend sequence_type operator-(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] - b.m_coordinatea[i];
      return result;
   }

   sequence_type& operator-=(const sequence_type& a) {
      for (::collection::count i = 0; i < SIZE; ++i)
         m_coordinatea[i] -= a.m_coordinatea[i];
      return *this;
   }

   friend sequence_type operator *(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] * b.m_coordinatea[i];
      return result;
   }
   
   template < primitive_number NUMBER1 >
   sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > operator *(NUMBER1 n) const
   {
      sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[i] * n);
      return result;
   }


   sequence_type& operator*=(const sequence_type& a) {
      for (::collection::count i = 0; i < SIZE; ++i)
         m_coordinatea[i] *= a.m_coordinatea[i];
      return *this;
   }

   
   friend sequence_type operator/(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] / b.m_coordinatea[i];
      return result;
   }
   
   
   template < primitive_number NUMBER1 >
   sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > operator /(NUMBER1 n) const
   {
      sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[i] / n);
      return result;
   }


   sequence_type& operator/=(const sequence_type& a) {
      for (::collection::count i = 0; i < SIZE; ++i)
         m_coordinatea[i] /= a.m_coordinatea[i];
      return *this;
   }

   bool operator==(const sequence_type& a) const {
      for (::collection::count i = 0; i < SIZE; ++i) {
         if (m_coordinatea[i] != a.m_coordinatea[i])
            return false;
      }
      return true;
   }


   template < typename PREDICATE >
   bool is_every(PREDICATE predicate) const
   {

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         if (!predicate(m_coordinatea[i]))
         {

            return false;

         }

      }

      return true;

   }

   
   bool is_empty() const
   {

      return is_every([](auto coordinate) {return coordinate == COORDINATE{}; });

   }


   bool is_set() const
   {

      return !is_empty();

   }


   bool is_all_set() const
   {

      return is_every([](auto coordinate) {return coordinate != COORDINATE{}; });

   }


   bool is_all_positive() const
   {

      return is_every([](auto coordinate) {return coordinate > COORDINATE{}; });

   }


   template < typename PREDICATE >
   sequence_type prefer_self_coordinate_if(const sequence_type &vectorOther, PREDICATE predicate) const
   {

      sequence_type vector;

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         if (predicate(m_coordinatea[i]))
         {

            vector[i] = m_coordinatea[i];

         }
         else
         {

            vector[i] = vectorOther.m_coordinatea[i];

         }

      }

      return vector;

   }


   sequence_type prefer_self_coordinate_if_set(const sequence_type& vectorOther) const
   {

      return prefer_self_coordinate_if(vectorOther, [](auto coordinate) {return coordinate != 0; });

   }


   sequence_type prefer_self_coordinate_if_positive(const sequence_type& vectorOther) const
   {

      return prefer_self_coordinate_if(vectorOther, [](auto coordinate) {return coordinate > COORDINATE{}; });

   }


   template < typename PREDICATE, typename SOURCE_PREDICATE >
   sequence_type pred_prefer_self_coordinate_if(PREDICATE predicate, SOURCE_PREDICATE sourcepredicate) const
   {

      if (is_every(predicate))
      {

         return *this;

      }

      auto vectorOther = sourcepredicate();

      return prefer_self_coordinate_if(vectorOther, predicate);

   }


   template < typename SOURCE_PREDICATE >
   sequence_type pred_prefer_self_coordinate_if_set(SOURCE_PREDICATE sourcepredicate) const
   {

      return pred_prefer_self_coordinate_if([](auto coordinate) {return coordinate != COORDINATE{}; }, sourcepredicate);

   }


   template < typename SOURCE_PREDICATE >
   sequence_type pred_prefer_self_coordinate_if_positive(SOURCE_PREDICATE sourcepredicate) const
   {

      return pred_prefer_self_coordinate_if([](auto coordinate) {return coordinate > COORDINATE{}; }, sourcepredicate);

   }



   constexpr bool operator!=(const sequence_type& a) const { return !operator==(a); }

   constexpr const COORDINATE& operator[](::collection::count i) const { return m_coordinatea[i]; }

   constexpr COORDINATE& operator[](::collection::count i) { return m_coordinatea[i]; }

   template <::collection::count S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   constexpr const COORDINATE& a() const { return m_coordinatea[0]; }
   template <::collection::count S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   COORDINATE& a() { return m_coordinatea[0]; }

   template <::collection::count S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   constexpr const COORDINATE& b() const { return m_coordinatea[1]; }
   template <::collection::count S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   COORDINATE& b() { return m_coordinatea[1]; }

   template <::collection::count S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   constexpr const COORDINATE& c() const { return m_coordinatea[2]; }
   template <::collection::count S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   COORDINATE& c() { return m_coordinatea[2]; }

   template <::collection::count S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   constexpr const COORDINATE& d() const { return m_coordinatea[3]; }
   template <::collection::count S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   COORDINATE& d() { return m_coordinatea[3]; }
   
   
   template <::collection::count S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE dot_with_left_perpendicular_of(const sequence_type & b)
   {

      return (this->b() * b.a()) - (this->a() * b.b());

   }

   
   template <::collection::count S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE angle(const sequence_type & b)
   {

      return ::std::atan2(this->dot_with_left_perpendicular_of(b), this->dot(b));

   }


   sequence_type maximum(const sequence_type & vector) const
   {

      sequence_type result;

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::maximum(m_coordinatea[i], vector.m_coordinatea[i]);

      }

      return result;

   }

   sequence_type minimum(const sequence_type& vector) const
   {

      sequence_type result;

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::minimum(m_coordinatea[i], vector.m_coordinatea[i]);

      }

      return result;

   }

   
   UNIT_TYPE minimum() const
   {

      UNIT_TYPE nMinimum = this->m_coordinatea[0];

      for (::collection::count i = 1; i < SIZE; ++i)
      {

         nMinimum = ::minimum(nMinimum, this->m_coordinatea[i]);

      }

      return nMinimum;

   }


   UNIT_TYPE maximum() const
   {

      UNIT_TYPE nMaximum = this->m_coordinatea[0];

      for (::collection::count i = 1; i < SIZE; ++i)
      {

         nMaximum = ::maximum(nMaximum, this->m_coordinatea[i]);

      }

      return nMaximum;

   }
   
   
   COORDINATE dot(const sequence_type & vector) const
   {

      COORDINATE result = m_coordinatea[0] * vector.m_coordinatea[0];

      for (::collection::count i = 1; i < SIZE; ++i)
      {

         result += m_coordinatea[i] * vector.m_coordinatea[i];

      }

      return result;

   }


   COORDINATE squared_modulus()  const
   {

      return dot(*this);

   }


   COORDINATE modulus() const
   {
      
      return ::sqrt(squared_modulus());

   }


   sequence_type make_unitary() const
   {

      return *this / modulus();

   }


   const UNIT_TYPE & get_dimension(enum_orientation eorientation) const
   {
      
      return this->m_coordinatea[eorientation];
      
   }

   UNIT_TYPE & get_dimension(enum_orientation eorientation)
   {
      
      return this->m_coordinatea[eorientation];
      
   }

   
   template < ::collection::count S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   const UNIT_TYPE & get_normal_dimension(enum_orientation eorientation) const
   {
      
      return this->m_coordinatea[orthogonal2_index_of(eorientation)];
   
   }

   
   template < ::collection::count S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   UNIT_TYPE & get_normal_dimension(enum_orientation eorientation)
   {
      
      return this->m_coordinatea[orthogonal2_index_of(eorientation)];
   
   }
   
   
   inline UNIT_TYPE & set_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept
   {
      
      return this->m_coordinatea[eorientation] = l;
      
   }
   
   
   inline UNIT_TYPE & set_orthogonal_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept
   {
      
      return this->m_coordinatea[orthogonal2_index_of(eorientation)] = l;
      
   }

   

};



template <typename COORDINATE>
sequence_type<COORDINATE, 3> cross(const sequence_type<COORDINATE, 3>& a, const sequence_type<COORDINATE, 3>& b) {
   return sequence_type<COORDINATE, 3>(
      a.b() * b.c() - a.c() * b.b(),
      a.c() * b.a() - a.a() * b.c(),
      a.a() * b.b() - a.b() * b.a()
   );
}



//template <typename COORDINATE, ::collection::count SIZE>
//sequence_type<COORDINATE, SIZE> min(const sequence_type<COORDINATE, SIZE>& a1, const sequence_type<COORDINATE, SIZE>& a2) {
//   sequence_type<COORDINATE, SIZE> result;
//   for (::collection::count i = 0; i < SIZE; ++i)
//      result.m_coordinatea[i] = std::min(a1.m_coordinatea[i], a2.m_coordinatea[i]);
//   return result;
//}
//
//template < primitive_number NUMBER >
//class sequence2_type :
//   public sequence_type < NUMBER, 2 >
//{
//public:
//
//
//   using sequence_type < NUMBER, 2 >::sequence_type;
//
//
//   NUMBER dot_with_left_perpendicular_of(const sequence2_type & b)
//   {
//
//      return (this->b() * b.a()) - (this->a() * b.b());
//
//   }
//
//
//   NUMBER angle(const sequence2_type & b)
//   {
//
//      return atan2f(this->dot_with_left_perpendicular_of(b), this->dot(b));
//
//   }
//
//
//
//};

// Import some common Enoki types
using sequence2_int = sequence_type<int, 2>;
using sequence3_int = sequence_type<int, 3>;
using sequence4_int = sequence_type<int, 4>;

using sequence2_long_long = sequence_type<long long, 2>;
using sequence3_long_long = sequence_type<long long, 3>;
using sequence4_long_long = sequence_type<long long, 4>;

using sequence2_float = sequence_type<float, 2>;
using sequence3_float = sequence_type<float, 3>;
using sequence4_float = sequence_type<float, 4>;

using sequence2_double = sequence_type<double, 2>;
using sequence3_double = sequence_type<double, 3>;
using sequence4_double = sequence_type<double, 4>;




///// Allows for conversion between ::color::color and the NanoVG ::color::color class.
//inline Color::operator const ::color::color & () const {
//   return reinterpret_cast<const ::color::color &>(*(this->m_coordinatea));
//}

template < primitive_sequence SEQUENCE, typename COORDINATE_TRANSFORM >
auto transform(const SEQUENCE& sequence, COORDINATE_TRANSFORM coordinatetransform)
{

   SEQUENCE sequenceResult(no_initialize_t{});

   for (::collection::count i = 0; i < sequence.get_size(); ++i)
   {

      sequenceResult.set_coordinate(i, coordinatetransform(sequence.coordinate(i)));

   }

   return sequenceResult;

}


template < primitive_sequence SEQUENCE >
auto floor(const SEQUENCE& sequence)
{

   return transform(sequence, [](auto a) {return floor(a); });

}


template < primitive_sequence SEQUENCE >
auto ceil(const SEQUENCE& sequence)
{

   return transform(sequence, [](auto a) {return ceil(a); });

}



