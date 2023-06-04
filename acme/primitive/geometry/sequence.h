/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
// Merge with estamira/particle/vec4:linear_rand
#pragma once


//#include "common.h"
//#include "traits.h"
//#include <cassert>
#include <cmath>
//#include <iosfwd>
//#include <string.h> // memset


template < typename UNIT_TYPE >
inline UNIT_TYPE linear_rand(const UNIT_TYPE & t1, const UNIT_TYPE & t2)
{
   if (t2 == t1)
      return t1;
   return ((t2 - t1) * rand()/ RAND_MAX) + t1;

}



struct no_initialize_t {};

template < primitive_number COORDINATE, size_t t_iSize >
struct sequence_type
{

   using BASE_COORDINATE = COORDINATE;
   using UNIT_TYPE = COORDINATE;


   COORDINATE m_coordinatea[t_iSize];


   static constexpr bool IS_MATRIX = false;
   static constexpr size_t SIZE = t_iSize;


   sequence_type()
   {
   
      set_all(0);
      
   }

   sequence_type(no_initialize_t)
   {
      
      
   }

   sequence_type(UNIT_TYPE n)
   {

     set_all(n);

   }

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
//   sequence_type(const T & a) {
//      for (size_t i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = (COORDINATE)a[i];
//   }

   template < primitive_number NUMBER1, size_t S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   sequence_type(const sequence_type < NUMBER1, 2 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
   }

   
   template < primitive_number NUMBER1, size_t S = SIZE, std::enable_if_t<S == 3, int> = 0 >
   sequence_type(const sequence_type < NUMBER1, 3 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
   }

   
   template < primitive_number NUMBER1, size_t S = SIZE, std::enable_if_t<S == 4, int> = 0 >
   sequence_type(const sequence_type < NUMBER1, 4 > & sequence)
   {
      m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
      m_coordinatea[3] = (UNIT_TYPE) sequence.m_coordinatea[3];
   }

//   sequence_type(COORDINATE s) {
//      for (size_t i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = s;
//   }

   template < size_t S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   sequence_type(COORDINATE coordinate0, COORDINATE coordinate1)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
   }

   
   template <size_t S = SIZE, std::enable_if_t<S == 3, int> = 0>
   sequence_type(COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
      m_coordinatea[2] = coordinate2;
   }

   
   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   sequence_type(
                 COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2, COORDINATE coordinate3)
   {
      m_coordinatea[0] = coordinate0;
      m_coordinatea[1] = coordinate1;
      m_coordinatea[2] = coordinate2;
      m_coordinatea[3] = coordinate3;
   }

   
   void set_all(COORDINATE coordinate)
   {
      
      for (size_t i = 0; i < SIZE; ++i)
      {
         
         m_coordinatea[i] = coordinate;
         
      }
      
   }
   
   // simple menthods: operates on x, y
   template < size_t S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void add2(const sequence_type & a)
   {
      this->a() += a.a();
      this->b() += a.b();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void sub2(const sequence_type & a)
   {
      this->a() -= a.a();
      this->b() -= a.b();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void mul2(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void set2(UNIT_TYPE a, UNIT_TYPE b)
   {
      this->a() = a;
      this->b() = b;
   }

   template < size_t S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   static inline void mix2(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
   }

   // simple menthods: operates on x, y, z
   template < size_t S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void add3(const sequence_type & a)
   {
      this->a() += a.a();
      this->b() += a.b();
      this->c() += a.c();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void sub3(const sequence_type & a)
   {
      this->a() -= a.a();
      this->b() -= a.b();
      this->c() -= a.c();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void mul3(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
      this->c() *= n;
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void set3(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c)
   {
      this->a() = a;
      this->b() = b;
      this->c() = c;
   }

   template < size_t S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   static inline void mix3(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
      c.c() = a.c()*((UNIT_TYPE)1.0 - t) + b.c()*t;
   }

   // simple menthods: operates on x, y, z, w
   template < size_t S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void add4(const sequence_type & q)
   {
      this->a() += q.a();
      this->b() += q.b();
      this->c() += q.c();
      this->d() += q.d();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void sub4(const sequence_type & q)
   {
      this->a() -= q.a();
      this->b() -= q.b();
      this->c() -= q.c();
      this->d() -= q.d();
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void mul4(UNIT_TYPE n)
   {
      this->a() *= n;
      this->b() *= n;
      this->c() *= n;
      this->d() *= n;
   }
   template < size_t S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void set4(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d)
   {
      this->a() = a;
      this->b() = b;
      this->c() = c;
      this->d() = d;
   }

   template < size_t S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   static inline void mix4(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a() = a.a()*((UNIT_TYPE)1.0 - t) + b.a()*t;
      c.b() = a.b()*((UNIT_TYPE)1.0 - t) + b.b()*t;
      c.c() = a.c()*((UNIT_TYPE)1.0 - t) + b.c()*t;
      c.d() = a.d()*((UNIT_TYPE)1.0 - t) + b.d()*t;
   }



   inline sequence_type linear_rand(const sequence_type &sequence) const
   {

      return sequence_type(
             linear_rand(this->a(), sequence.a()),
             linear_rand(this->b(), sequence.b()),
             linear_rand(this->c(), sequence.c()),
             linear_rand(this->d(), sequence.d()));

   }

   sequence_type operator-() const
   {
      sequence_type result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = -m_coordinatea[i];
      return result;
   }

   
   friend sequence_type operator+(const sequence_type& a, const sequence_type& b)
   {
      sequence_type result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] + b.m_coordinatea[i];
      return result;
   }

   sequence_type& operator+=(const sequence_type& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] += a.m_coordinatea[i];
      return *this;
   }

   friend sequence_type operator-(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] - b.m_coordinatea[i];
      return result;
   }

   sequence_type& operator-=(const sequence_type& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] -= a.m_coordinatea[i];
      return *this;
   }

   friend sequence_type operator *(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] * b.m_coordinatea[i];
      return result;
   }
   
   template < primitive_number NUMBER1 >
   sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > operator *(NUMBER1 n) const
   {
      sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[i] * n);
      return result;
   }


   sequence_type& operator*=(const sequence_type& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] *= a.m_coordinatea[i];
      return *this;
   }

   
   friend sequence_type operator/(const sequence_type& a, const sequence_type& b) {
      sequence_type result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] / b.m_coordinatea[i];
      return result;
   }
   
   
   template < primitive_number NUMBER1 >
   sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > operator /(NUMBER1 n) const
   {
      sequence_type < largest_number < UNIT_TYPE, NUMBER1 >, SIZE > result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[i] / n);
      return result;
   }


   sequence_type& operator/=(const sequence_type& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] /= a.m_coordinatea[i];
      return *this;
   }

   bool operator==(const sequence_type& a) const {
      for (size_t i = 0; i < SIZE; ++i) {
         if (m_coordinatea[i] != a.m_coordinatea[i])
            return false;
      }
      return true;
   }


   template < typename PREDICATE >
   bool is_every(PREDICATE predicate) const
   {

      for (size_t i = 0; i < SIZE; ++i)
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

      for (size_t i = 0; i < SIZE; ++i)
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

   constexpr const COORDINATE& operator[](size_t i) const { return m_coordinatea[i]; }

   constexpr COORDINATE& operator[](size_t i) { return m_coordinatea[i]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   constexpr const COORDINATE& a() const { return m_coordinatea[0]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   COORDINATE& a() { return m_coordinatea[0]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   constexpr const COORDINATE& b() const { return m_coordinatea[1]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   COORDINATE& b() { return m_coordinatea[1]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   constexpr const COORDINATE& c() const { return m_coordinatea[2]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   COORDINATE& c() { return m_coordinatea[2]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   constexpr const COORDINATE& d() const { return m_coordinatea[3]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   COORDINATE& d() { return m_coordinatea[3]; }
   
   
   template <size_t S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE dot_with_left_perpendicular_of(const sequence_type & b)
   {

      return (this->b() * b.a()) - (this->a() * b.b());

   }

   
   template <size_t S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE angle(const sequence_type & b)
   {

      return ::std::atan2(this->dot_with_left_perpendicular_of(b), this->dot(b));

   }


   sequence_type maximum(const sequence_type & vector) const
   {

      sequence_type result;

      for (size_t i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::maximum(m_coordinatea[i], vector.m_coordinatea[i]);

      }

      return result;

   }

   sequence_type minimum(const sequence_type& vector) const
   {

      sequence_type result;

      for (size_t i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::minimum(m_coordinatea[i], vector.m_coordinatea[i]);

      }

      return result;

   }

   
   UNIT_TYPE minimum() const
   {

      UNIT_TYPE nMinimum = this->m_coordinatea[0];

      for (size_t i = 1; i < SIZE; ++i)
      {

         nMinimum = ::minimum(nMinimum, this->m_coordinatea[i]);

      }

      return nMinimum;

   }


   UNIT_TYPE maximum() const
   {

      UNIT_TYPE nMaximum = this->m_coordinatea[0];

      for (size_t i = 1; i < SIZE; ++i)
      {

         nMaximum = ::maximum(nMaximum, this->m_coordinatea[i]);

      }

      return nMaximum;

   }
   
   
   COORDINATE dot(const sequence_type & vector) const
   {

      COORDINATE result = m_coordinatea[0] * vector.m_coordinatea[0];

      for (size_t i = 1; i < SIZE; ++i)
      {

         result += m_coordinatea[i] * vector.m_coordinatea[i];

      }

      return result;

   }


   COORDINATE squared_normal()  const
   {

      return dot(*this);

   }


   COORDINATE normal() const
   {
      
      return ::sqrt(squared_normal());

   }

   sequence_type normalize() const
   {

      return *this / norm(*this);

   }


   const UNIT_TYPE & get_dimension(enum_orientation eorientation) const
   {
      
      return this->m_coordinatea[eorientation];
      
   }

   UNIT_TYPE & get_dimension(enum_orientation eorientation)
   {
      
      return this->m_coordinatea[eorientation];
      
   }

   
   template < size_t S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   const UNIT_TYPE & get_normal_dimension(enum_orientation eorientation) const
   {
      
      return this->m_coordinatea[orthogonal2_index_of(eorientation)];
   
   }

   
   template < size_t S = SIZE, std::enable_if_t<S == 2, int> = 0 >
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



//template <typename COORDINATE, size_t SIZE>
//sequence_type<COORDINATE, SIZE> min(const sequence_type<COORDINATE, SIZE>& a1, const sequence_type<COORDINATE, SIZE>& a2) {
//   sequence_type<COORDINATE, SIZE> result;
//   for (size_t i = 0; i < SIZE; ++i)
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
using sequence2_i32 = sequence_type<::i32, 2>;
using sequence3_i32 = sequence_type<::i32, 3>;
using sequence4_i32 = sequence_type<::i32, 4>;

using sequence2_i64 = sequence_type<::i64, 2>;
using sequence3_i64 = sequence_type<::i64, 3>;
using sequence4_i64 = sequence_type<::i64, 4>;

using sequence2_f32 = sequence_type<::f32, 2>;
using sequence3_f32 = sequence_type<::f32, 3>;
using sequence4_f32 = sequence_type<::f32, 4>;

using sequence2_f64 = sequence_type<::f64, 2>;
using sequence3_f64 = sequence_type<::f64, 3>;
using sequence4_f64 = sequence_type<::f64, 4>;

///**
// * \class Color common.h nanoui/common.h
// *
// * \brief Stores an RGBA floating point color value.
// *
// * This class simply wraps around an ``Vector4f``, providing some convenient
// * methods and terminology for thinking of it as a color.  The data operates in the
// * same way as ``Vector4f``, and the following values are identical:
// *
// * \rst
// * +---------+-------------+----------------+-------------+
// * | Channel | sequence_type Index | Vector4f field | Color field |
// * +=========+=============+================+=============+
// * | Red     | ``0``       | x()            | r()         |
// * +---------+-------------+----------------+-------------+
// * | Green   | ``1``       | y()            | g()         |
// * +---------+-------------+----------------+-------------+
// * | Blue    | ``2``       | z()            | b()         |
// * +---------+-------------+----------------+-------------+
// * | Alpha   | ``3``       | w()            | a()         |
// * +---------+-------------+----------------+-------------+
// * \endrst
// */
//class Color : public Vector4f {
//public:
//   using Vector4f::Vector4f;
//   using Vector4f::operator=;
//
//   /// Default constructor: represents black (``r, g, b, a = 0``)
//   Color() : Color(0, 0, 0, 0) { }
//
//   /// Initialize from a 4D vector
//   Color(const Vector4f & color) : Vector4f(color) { }
//   
//   Color(const color::color & color) : Color(color.r, color.g, color.b, color.a) { }
//
//   /**
//    * Copies (x, y, z) from the input vector, and uses the value specified by
//    * the ``alpha`` parameter for this Color object's alpha component.
//    *
//    * \param color
//    * The three dimensional float vector being copied.
//    *
//    * \param alpha
//    * The value to set this object's alpha component to.
//    */
//   Color(const Vector3f & color, float alpha)
//      : Color(color[0], color[1], color[2], alpha) { }
//
//   /**
//    * Copies (x, y, z) from the input vector, casted as floats first and then
//    * divided by ``255.0``, and uses the value specified by the ``alpha``
//    * parameter, casted to a float and divided by ``255.0`` as well, for this
//    * Color object's alpha component.
//    *
//    * \param color
//    * The three dimensional integer vector being copied, will be divided by ``255.0``.
//    *
//    * \param alpha
//    * The value to set this object's alpha component to, will be divided by ``255.0``.
//    */
//   Color(const Vector3i & color, int alpha)
//      : Color(Vector3f(color) / 255.f, alpha / 255.f) { }
//
//   /**
//    * Copies (x, y, z) from the input vector, and sets the alpha of this color
//    * to be ``1.0``.
//    *
//    * \param color
//    * The three dimensional float vector being copied.
//    */
//   Color(const Vector3f & color) : Color(color, 1.0f) {}
//
//   /**
//    * Copies (x, y, z) from the input vector, casting to floats and dividing by
//    * ``255.0``.  The alpha of this color will be set to ``1.0``.
//    *
//    * \param color
//    * The three dimensional integer vector being copied, will be divided by ``255.0``.
//    */
//   Color(const Vector3i & color)
//      : Color(Vector3f(color) / 255.f, 1.f) { }
//
//   /**
//    * Copies (x, y, z, w) from the input vector, casting to floats and dividing
//    * by ``255.0``.
//    *
//    * \param color
//    * The three dimensional integer vector being copied, will be divided by ``255.0``.
//    */
//   Color(const Vector4i & color)
//      : Color(Vector4f(color) / 255.f) { }
//
//   /**
//    * Creates the Color ``(intensity, intensity, intensity, alpha)``.
//    *
//    * \param intensity
//    * The value to be used for red, green, and blue.
//    *
//    * \param alpha
//    * The alpha component of the color.
//    */
//   Color(float intensity, float alpha)
//      : Color(Vector3f(intensity), alpha) { }
//
//   /**
//    * Creates the Color ``(intensity, intensity, intensity, alpha) / 255.0``.
//    * Values are casted to floats before division.
//    *
//    * \param intensity
//    * The value to be used for red, green, and blue, will be divided by ``255.0``.
//    *
//    * \param alpha
//    * The alpha component of the color, will be divided by ``255.0``.
//    */
//   Color(int intensity, int alpha)
//      : Color(Vector3i(intensity), alpha) { }
//
//   /**
//    * Explicit constructor: creates the Color ``(r, g, b, a)``.
//    *
//    * \param r
//    * The red component of the color.
//    *
//    * \param g
//    * The green component of the color.
//    *
//    * \param b
//    * The blue component of the color.
//    *
//    * \param a
//    * The alpha component of the color.
//    */
//   Color(float r, float g, float b, float a) : Color(Vector4f(r, g, b, a)) { }
//
//   /**
//    * Explicit constructor: creates the Color ``(r, g, b, a) / 255.0``.
//    * Values are casted to floats before division.
//    *
//    * \param r
//    * The red component of the color, will be divided by ``255.0``.
//    *
//    * \param g
//    * The green component of the color, will be divided by ``255.0``.
//    *
//    * \param b
//    * The blue component of the color, will be divided by ``255.0``.
//    *
//    * \param a
//    * The alpha component of the color, will be divided by ``255.0``.
//    */
//   Color(int r, int g, int b, int a) : Color(Vector4f((float)r, (float)g, (float)b, (float)a) / 255.f) { }
//
//   /// Return a reference to the red channel
//   float & r() { return x(); }
//   /// Return a reference to the red channel (const version)
//   const float & r() const { return x(); }
//   /// Return a reference to the green channel
//   float & g() { return y(); }
//   /// Return a reference to the green channel (const version)
//   const float & g() const { return y(); }
//   /// Return a reference to the blue channel
//   float & b() { return z(); }
//   /// Return a reference to the blue channel (const version)
//   const float & b() const { return z(); }
//   /// Return a reference to the alpha channel
//   float & a() { return w(); }
//   /// Return a reference to the alpha channel (const version)
//   const float & a() const { return w(); }
//
//   /**
//    * Computes the luminance as ``l = 0.299r + 0.587g + 0.144b + 0.0a``.  If
//    * the luminance is less than 0.5, white is returned.  If the luminance is
//    * greater than or equal to 0.5, black is returned.  Both returns will have
//    * an alpha component of 1.0.
//    */
//   Color contrasting_color() const {
//      float luminance = dot(*this, Color(0.299f, 0.587f, 0.144f, 0.f));
//      return Color(luminance < 0.5f ? 1.f : 0.f, 1.f);
//   }
//
//   /// Allows for conversion between this Color and NanoVG's representation.
//   inline operator const ::color::color & () const;
//};

/// Simple matrix class with column-major storage
template <typename Value_, size_t Size_> struct Matrix {
   static constexpr bool IsNanoGUI = true;
   static constexpr bool IsMatrix = true;

   using COORDINATE = Value_;
   static constexpr size_t SIZE = Size_;

   Matrix() { }

   explicit Matrix(COORDINATE s) {
      memset(m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i)
         m[i][i] = s;
   }

   friend Matrix operator*(const Matrix& a, const Matrix& b) {
      Matrix c;
      for (size_t i = 0; i < SIZE; ++i) {
         for (size_t j = 0; j < SIZE; ++j) {
            COORDINATE accum = 0;
            for (size_t k = 0; k < SIZE; ++k)
               accum += a.m[k][i] * b.m[j][k];
            c.m[j][i] = accum;
         }
      }
      return c;
   }

   static Matrix scale(const sequence_type<COORDINATE, SIZE - 1>& m_coordinatea) {
      Matrix result;
      memset(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i)
         result.m[i][i] = i < SIZE - 1 ? m_coordinatea[i] : 1;
      return result;
   }

   static Matrix scale(const sequence_type<COORDINATE, SIZE>& m_coordinatea) {
      Matrix result;
      memset(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i)
         result.m[i][i] = m_coordinatea[i];
      return result;
   }

   static Matrix translate(const sequence_type<COORDINATE, SIZE - 1>& m_coordinatea) {
      Matrix result;
      memset(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i) {
         result.m[i][i] = 1.f;
         if (i < SIZE - 1)
            result.m[SIZE - 1][i] = m_coordinatea[i];
      }
      return result;
   }


   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix rotate(const sequence_type<COORDINATE, 3>& axis, COORDINATE angle)
   {

      COORDINATE s = ::sin(angle);
      COORDINATE c = ::cos(angle);
      COORDINATE t = 1 - c;

      Matrix result(0);
      result.m[3][3] = 1;
      result.m[0][0] = c + axis.a() * axis.a() * t;
      result.m[1][1] = c + axis.b() * axis.b() * t;
      result.m[2][2] = c + axis.c() * axis.c() * t;

      COORDINATE tmp1 = axis.a() * axis.b() * t;
      COORDINATE tmp2 = axis.c() * s;

      result.m[0][1] = tmp1 + tmp2;
      result.m[1][0] = tmp1 - tmp2;

      tmp1 = axis.a() * axis.c() * t;
      tmp2 = axis.b() * s;
      result.m[0][2] = tmp1 - tmp2;
      result.m[2][0] = tmp1 + tmp2;

      tmp1 = axis.b() * axis.c() * t;
      tmp2 = axis.a() * s;
      result.m[1][2] = tmp1 + tmp2;
      result.m[2][1] = tmp1 - tmp2;

      return result;

   }


   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix perspective(COORDINATE fov, COORDINATE near_, COORDINATE far_, COORDINATE aspect = 1.f)
   {

      COORDINATE recip = 1 / (near_ - far_);
      COORDINATE c = 1 / ::tan(.5f * fov);

      Matrix trafo = Matrix::scale(sequence_type<COORDINATE, SIZE>(c / aspect, c, (near_ + far_) * recip, 0.f));

      trafo.m[3][2] = 2.f * near_ * far_ * recip;
      trafo.m[2][3] = -1.f;

      return trafo;
   }

   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix ortho(COORDINATE left, COORDINATE right,
      COORDINATE bottom, COORDINATE top,
      COORDINATE near_, COORDINATE far_)
   {

      COORDINATE rl = 1 / (right - left);
      COORDINATE tb = 1 / (top - bottom);
      COORDINATE fn = 1 / (far_ - near_);

      Matrix result(0);

      result.m[0][0] = 2 * rl;
      result.m[1][1] = 2 * tb;
      result.m[2][2] = -2 * fn;
      result.m[3][3] = 1;
      result.m[3][0] = -(right + left) * rl;
      result.m[3][1] = -(top + bottom) * tb;
      result.m[3][2] = -(far_ + near_) * fn;

      return result;
   }

   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix look_at(const sequence_type<COORDINATE, 3>& origin,
      const sequence_type<COORDINATE, 3>& target,
      const sequence_type<COORDINATE, 3>& up)
   {

      auto dir = normalize(target - origin);
      auto left = normalize(cross(dir, up));
      auto new_up = cross(left, dir);
      dir = -dir;

      Matrix result(0);
      result.m[0][0] = left.a();
      result.m[0][1] = left.b();
      result.m[0][2] = left.c();
      result.m[1][0] = new_up.a();
      result.m[1][1] = new_up.b();
      result.m[1][2] = new_up.c();
      result.m[2][0] = dir.a();
      result.m[2][1] = dir.b();
      result.m[2][2] = dir.c();
      result.m[3][0] = -dot(left, origin);
      result.m[3][1] = -dot(new_up, origin);
      result.m[3][2] = -dot(dir, origin);
      result.m[3][3] = 1.f;
      return result;
   }

   COORDINATE m[SIZE][SIZE];
};

using Matrix2f = Matrix<float, 2>;
using Matrix3f = Matrix<float, 3>;
using Matrix4f = Matrix<float, 4>;


///// Allows for conversion between ::color::color and the NanoVG ::color::color class.
//inline Color::operator const ::color::color & () const {
//   return reinterpret_cast<const ::color::color &>(*(this->m_coordinatea));
//}






