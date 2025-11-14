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

template<primitive_floating FLOATING_TYPE, int t_iDimension>
struct matrix_type;

template<primitive_number NUMBER, int t_iSize >
struct sequence_t_type
{


   using sequence_tag = sequence_t;
   using sequence_size = sequence_size_t<t_iSize>;
   using COORDINATE = NUMBER;
   using UNIT_TYPE = NUMBER;
   static const int SIZE = t_iSize;


};


template<primitive_number NUMBER>
struct sequence_t_type<NUMBER, 1>
{


   using COORDINATE = NUMBER;
   using UNIT_TYPE = NUMBER;
   static const int SIZE = 1;


   union
   {
      struct
      {
         union
         {
            COORDINATE x, r, s;
         };
      };
      COORDINATE m_coordinatea[SIZE];
   };


};


template<primitive_number NUMBER>
struct std::hash<::sequence_t_type<NUMBER, 1>>
{
   std::size_t operator()(const ::sequence_t_type<NUMBER, 1> &s) const noexcept
   {
      std::size_t h1 = std::hash<NUMBER>{}(s.x);
      return h1;
   }
};
 


template < primitive_number NUMBER >
struct sequence_t_type<NUMBER, 2>
{


   using COORDINATE = NUMBER;
   using UNIT_TYPE = NUMBER;
   static const int SIZE = 2;

   union
   {
      struct
      {
         union
         {
            COORDINATE x, r, s;
         };
         union
         {
            COORDINATE y, g, t;
         };
      };
      COORDINATE m_coordinatea[SIZE];
   };


};


template<primitive_number NUMBER>
struct std::hash<::sequence_t_type<NUMBER, 2>>
{
   std::size_t operator()(const ::sequence_t_type<NUMBER, 2> &s) const noexcept
   {
      std::size_t h1 = std::hash<NUMBER>{}(s.x);
      std::size_t h2 = std::hash<NUMBER>{}(s.y);
      return h1 ^ (h2 << 1);
   }
};



template<primitive_number NUMBER>
struct sequence_t_type<NUMBER, 3>
{


   using COORDINATE = NUMBER;
   using UNIT_TYPE = NUMBER;
   static const int SIZE = 3;


   union
   {
      struct
      {
         union
         {
            COORDINATE x, r, s;
         };
         union
         {
            COORDINATE y, g, t;
         };
         union
         {
            COORDINATE z, b, p;
         };
      };
      COORDINATE m_coordinatea[SIZE];
   };
   

};


template<primitive_number NUMBER>
struct std::hash<::sequence_t_type<NUMBER, 3>>
{
   std::size_t operator()(const ::sequence_t_type<NUMBER, 3> &s) const noexcept
   {
      std::size_t h1 = std::hash<NUMBER>{}(s.x);
      std::size_t h2 = std::hash<NUMBER>{}(s.y);
      std::size_t h3 = std::hash<NUMBER>{}(s.z);
      return h1 ^ (h2 << 1) ^ (h3 << 2);
   }
};


template<primitive_number NUMBER>
struct sequence_t_type<NUMBER, 4>
{


   using COORDINATE = NUMBER;
   using UNIT_TYPE = NUMBER;
   static const int SIZE = 4;


   union
   {
      struct
      {
         union
         {
            COORDINATE x, r, s;
         };
         union
         {
            COORDINATE y, g, t;
         };
         union
         {
            COORDINATE z, b, p;
         };
         union
         {
            COORDINATE w, a, q;
         };
      };
      COORDINATE m_coordinatea[SIZE];
   };
   

};

template<primitive_number NUMBER>
struct std::hash<::sequence_t_type<NUMBER, 4>>
{
   std::size_t operator()(const ::sequence_t_type<NUMBER, 4> &s) const noexcept
   {
      std::size_t h1 = std::hash<NUMBER>{}(s.x);
      std::size_t h2 = std::hash<NUMBER>{}(s.y);
      std::size_t h3 = std::hash<NUMBER>{}(s.z);
      std::size_t h4 = std::hash<NUMBER>{}(s.w);
      return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 2);
   }
};

using int_sequence2_t = sequence_t_type<int, 2>;
using int_sequence3_t = sequence_t_type<int, 3>;
using int_sequence4_t = sequence_t_type<int, 4>;


using long_long_sequence2_t = sequence_t_type<long long, 2>;
using long_long_sequence3_t = sequence_t_type<long long, 3>;
using long_long_sequence4_t = sequence_t_type<long long, 4>;


using float_sequence2_t = sequence_t_type<float, 2>;
using float_sequence3_t = sequence_t_type<float, 3>;
using float_sequence4_t = sequence_t_type<float, 4>;


using double_sequence2_t = sequence_t_type<double, 2>;
using double_sequence3_t = sequence_t_type<double, 3>;
using double_sequence4_t = sequence_t_type<double, 4>;



template < primitive_number NUMBER, int t_iSize >
struct sequence_type :
   public sequence_t_type<NUMBER, t_iSize>
{

   using sequence_tag = sequence_t;
   using sequence_size = sequence_size_t < t_iSize >;
   using SEQUENCE_T = sequence_t_type< NUMBER, t_iSize >;
   using COORDINATE = typename SEQUENCE_T::COORDINATE;
   using UNIT_TYPE = typename SEQUENCE_T::COORDINATE;
   static const int SIZE = t_iSize;


   static constexpr bool IS_MATRIX = false;


   constexpr sequence_type()
   {
   
      set_null();
      
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
//         this->m_coordinatea[i] = (COORDINATE)a[i];
//   }

   template < primitive_number NUMBER1 >
   constexpr sequence_type(const sequence_t_type < NUMBER1, 2 > & sequence)
      requires(SIZE >= 2)
   {
      this->m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      this->m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
   }

   
   template < primitive_number NUMBER1, int iSize >
   constexpr sequence_type(const sequence_t_type < NUMBER1, iSize > & sequence)
      requires(SIZE >= 3 && iSize >= 3)
   {
      this->m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      this->m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      this->m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
   }


   template<primitive_number NUMBER1>
   constexpr sequence_type(const NUMBER1 *p) // expects p to point to an array of at least SIZE elements
   {
      for (::collection::count i = 0; i < SIZE; ++i)
         this->m_coordinatea[i] = (UNIT_TYPE)p[i];
   }




   void set_null() 
   {
      set_all(0); 
   }


   sequence_type & null()
   {

      set_null();

      return *this;

   }

   static sequence_type Null()
   {

      return {};
   }

   template < primitive_number NUMBER1 >
   constexpr sequence_type(const sequence_t_type < NUMBER1, 4 > & sequence)
      requires(SIZE >= 4)
   {
      this->m_coordinatea[0] = (UNIT_TYPE) sequence.m_coordinatea[0];
      this->m_coordinatea[1] = (UNIT_TYPE) sequence.m_coordinatea[1];
      this->m_coordinatea[2] = (UNIT_TYPE) sequence.m_coordinatea[2];
      this->m_coordinatea[3] = (UNIT_TYPE) sequence.m_coordinatea[3];
   }

//   sequence_type(COORDINATE s) {
//      for (::collection::count i = 0; i < SIZE; ++i)
//         this->m_coordinatea[i] = s;
//   }

   template < ::collection::count S = SIZE, std::enable_if_t<S == 2, int> = 0 >
   constexpr sequence_type(COORDINATE coordinate0, COORDINATE coordinate1)
   {
      this->m_coordinatea[0] = coordinate0;
      this->m_coordinatea[1] = coordinate1;
   }

   
   template <::collection::count S = SIZE, std::enable_if_t<S == 3, int> = 0>
   constexpr sequence_type(COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2)
   {
      this->m_coordinatea[0] = coordinate0;
      this->m_coordinatea[1] = coordinate1;
      this->m_coordinatea[2] = coordinate2;
   }

   
   constexpr sequence_type(
                 COORDINATE coordinate0, COORDINATE coordinate1,
                 COORDINATE coordinate2, COORDINATE coordinate3)
      requires(SIZE == 4)
   {
      this->m_coordinatea[0] = coordinate0;
      this->m_coordinatea[1] = coordinate1;
      this->m_coordinatea[2] = coordinate2;
      this->m_coordinatea[3] = coordinate3;
   }

   constexpr sequence_type(const sequence_type < COORDINATE, 3 > &  seq3,
                           COORDINATE coordinate3)
      requires(SIZE == 4)
   {
      this->m_coordinatea[0] = seq3[0];
      this->m_coordinatea[1] = seq3[1];
      this->m_coordinatea[2] = seq3[2];
      this->m_coordinatea[3] = coordinate3;
   }

   constexpr sequence_type(COORDINATE coordinate0, const sequence_type<COORDINATE, 3> &seq3)
      requires(SIZE == 4)
   {
      this->m_coordinatea[0] = coordinate0;
      this->m_coordinatea[1] = seq3[0];
      this->m_coordinatea[2] = seq3[1];
      this->m_coordinatea[3] = seq3[2];
   }

   constexpr ::collection::count get_size() const { return SIZE; }
   constexpr ::collection::count get_count() const { return this->get_size(); }
   
   
   constexpr COORDINATE & set_coordinate(::collection::index i, COORDINATE coordinate)
   {

      return this->m_coordinatea[i] = coordinate;

   }


   constexpr COORDINATE coordinate(::collection::index i) const
   {

      return this->m_coordinatea[i];

   }

   
   constexpr COORDINATE & coordinate(::collection::index i)
   {

      return this->m_coordinatea[i];

   }


   void set_all(COORDINATE coordinate)
   {
      
      for (::collection::count i = 0; i < SIZE; ++i)
      {
         
         this->m_coordinatea[i] = coordinate;
         
      }
      
   }
   
   bool is_all(COORDINATE coordinate) const
   {
      
      for (::collection::count i = 0; i < SIZE; ++i)
      {
         
         if(this->m_coordinatea[i] != coordinate)
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
      this->x += a.a;
      this->y += a.b;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void sub2(const sequence_type & a)
   {
      this->x -= a.a;
      this->y -= a.b;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void mul2(UNIT_TYPE n)
   {
      this->x *= n;
      this->y *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   inline void set2(UNIT_TYPE a, UNIT_TYPE b)
   {
      this->x = a;
      this->y = b;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 2, int> = 0 >
   static inline void mix2(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a = a.a*((UNIT_TYPE)1.0 - t) + b.a*t;
      c.b = a.b*((UNIT_TYPE)1.0 - t) + b.b*t;
   }

   // simple menthods: operates on x, y, z
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void add3(const sequence_type & a)
   {
      this->x += a.a;
      this->y += a.b;
      this->c += a.c;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void sub3(const sequence_type & a)
   {
      this->x -= a.a;
      this->y -= a.b;
      this->c -= a.c;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void mul3(UNIT_TYPE n)
   {
      this->x *= n;
      this->y *= n;
      this->c *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   inline void set3(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c)
   {
      this->x = a;
      this->y = b;
      this->c = c;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 3, int> = 0 >
   static inline void mix3(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a = a.a*((UNIT_TYPE)1.0 - t) + b.a*t;
      c.b = a.b*((UNIT_TYPE)1.0 - t) + b.b*t;
      c.c = a.c*((UNIT_TYPE)1.0 - t) + b.c*t;
   }

   // simple menthods: operates on x, y, z, w
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void add4(const sequence_type & q)
   {
      this->x += q.a;
      this->y += q.b;
      this->c += q.c;
      this->d += q.d;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void sub4(const sequence_type & q)
   {
      this->x -= q.a;
      this->y -= q.b;
      this->c -= q.c;
      this->d -= q.d;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void mul4(UNIT_TYPE n)
   {
      this->x *= n;
      this->y *= n;
      this->c *= n;
      this->d *= n;
   }
   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   inline void set4(UNIT_TYPE a, UNIT_TYPE b, UNIT_TYPE c, UNIT_TYPE d)
   {
      this->x = a;
      this->y = b;
      this->c = c;
      this->d = d;
   }

   template < ::collection::count S = SIZE, std::enable_if_t<S <= 4, int> = 0 >
   static inline void mix4(const sequence_type &a, const sequence_type &b, UNIT_TYPE t, sequence_type &c)
   {
      c.a = a.a*((UNIT_TYPE)1.0 - t) + b.a*t;
      c.b = a.b*((UNIT_TYPE)1.0 - t) + b.b*t;
      c.c = a.c*((UNIT_TYPE)1.0 - t) + b.c*t;
      c.d = a.d*((UNIT_TYPE)1.0 - t) + b.d*t;
   }


   sequence_type operator-() const
   {
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = -this->m_coordinatea[i];
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
         this->m_coordinatea[i] += a.m_coordinatea[i];
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
         this->m_coordinatea[i] -= a.m_coordinatea[i];
      return *this;
   }

   sequence_type operator *(const sequence_type& b) const {
      const sequence_type &a = *this;
      sequence_type result;
      for (::collection::count i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] * b.m_coordinatea[i];
      return result;
   }

   template<primitive_floating FLOATING1>
   inline sequence_type operator*(const matrix_type<FLOATING1, 3> &M) const
      requires(t_iSize == 3 && ::std::is_same_v<FLOATING1, NUMBER>);

   template<primitive_floating FLOATING1>
   inline sequence_type operator*(const matrix_type<FLOATING1, 4> &M) const
      requires(t_iSize == 4 && ::std::is_same_v<FLOATING1, NUMBER>);

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
         this->m_coordinatea[i] *= a.m_coordinatea[i];
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
         this->m_coordinatea[i] /= a.m_coordinatea[i];
      return *this;
   }

   sequence_type &operator/=(const NUMBER &n)
   {
      for (::collection::count i = 0; i < SIZE; ++i)
         this->m_coordinatea[i] /= n;
      return *this;
   }

   bool operator==(const sequence_type& a) const {
      for (::collection::count i = 0; i < SIZE; ++i) {
         if (this->m_coordinatea[i] != a.m_coordinatea[i])
            return false;
      }
      return true;
   }


   template < typename PREDICATE >
   bool is_every(PREDICATE predicate) const
   {

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         if (!predicate(this->m_coordinatea[i]))
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

         if (predicate(this->m_coordinatea[i]))
         {

            vector[i] = this->m_coordinatea[i];

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

   constexpr const COORDINATE& operator[](::collection::count i) const { return this->m_coordinatea[i]; }

   constexpr COORDINATE& operator[](::collection::count i) { return this->m_coordinatea[i]; }

   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   //constexpr const COORDINATE& a const { return this->m_coordinatea[0]; }
   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   //COORDINATE& a { return this->m_coordinatea[0]; }

   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   //constexpr const COORDINATE& b const { return this->m_coordinatea[1]; }
   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   //COORDINATE& b { return this->m_coordinatea[1]; }

   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   //constexpr const COORDINATE& c const { return this->m_coordinatea[2]; }
   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   //COORDINATE& c { return this->m_coordinatea[2]; }

   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   //constexpr const COORDINATE& d const { return this->m_coordinatea[3]; }
   //template <::collection::count S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   //COORDINATE& d { return this->m_coordinatea[3]; }
   
   
   template <::collection::count S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE dot_with_left_perpendicular_of(const sequence_type & b)
   {

      return (this->y * b.x) - (this->x * b.y);

   }

   
   template <::collection::count S = SIZE, std::enable_if_t<(S == 2), int> = 0>
   COORDINATE angle(const sequence_type & b)
   {

      return ::std::atan2(this->dot_with_left_perpendicular_of(b), this->dotted(b));

   }


   sequence_type maximum(const sequence_type & vector) const
   {

      sequence_type result;

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::maximum(this->m_coordinatea[i], vector.m_coordinatea[i]);

      }

      return result;

   }

   sequence_type minimum(const sequence_type& vector) const
   {

      sequence_type result;

      for (::collection::count i = 0; i < SIZE; ++i)
      {

         result.m_coordinatea[i] = ::minimum(this->m_coordinatea[i], vector.m_coordinatea[i]);

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
   
   
   COORDINATE dotted(const sequence_type & vector) const
   {

      COORDINATE result = this->m_coordinatea[0] * vector.m_coordinatea[0];

      for (::collection::count i = 1; i < SIZE; ++i)
      {

         result += this->m_coordinatea[i] * vector.m_coordinatea[i];

      }

      return result;

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

   sequence_type<COORDINATE, 3> crossed(const sequence_type<COORDINATE, 3> &b) const
      requires(SIZE == 3)
   {
      const auto &a = *this;
      return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
   }

   inline NUMBER squared_modulus() const
      requires(SIZE == 2)
   {
      return 
         this->x * this->x +
         this->y * this->y;
   }

   inline NUMBER squared_modulus() const
      requires(SIZE == 3)
   {
      return 
         this->x * this->x +
         this->y * this->y + 
         this->z * this->z;
   }

   inline NUMBER squared_modulus() const
      requires(SIZE == 4)
   {
      return 
         this->x * this->x + 
         this->y * this->y + 
         this->z * this->z + 
         this->w * this->w; 
   }

   inline NUMBER modulus() const
   { 
      return ::std::sqrt(squared_modulus()); 
   }


   inline NUMBER length() const
   {
      
      return modulus(); 

   }  


   inline NUMBER distance(const sequence_type & b) const 
   {
      
      return (b - *this).modulus(); 
   
   }  


   sequence_type &normalize()
   {

      auto modulus = this->modulus();

      if (modulus > 0.0f)
      {

         return *this /= modulus;

      }
      else
      {

         return null();

      }

   }


   sequence_type normalized() const
   {

      sequence_type sequence = *this;

      return sequence.normalize();

   }


   template<primitive_floating FLOATING>
   inline sequence_type mix(const sequence_type &b, FLOATING t) const
   {
      
      return *this * ((FLOATING)1 - t) + b * t;

   }


};





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
//      return (this->y * b.a) - (this->x * b.b);
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
using int_sequence2 = sequence_type<int, 2>;
using int_sequence3 = sequence_type<int, 3>;
using int_sequence4 = sequence_type<int, 4>;

using long_long_sequence2 = sequence_type<long long, 2>;
using long_long_sequence3 = sequence_type<long long, 3>;
using long_long_sequence4 = sequence_type<long long, 4>;

using float_sequence2 = sequence_type<float, 2>;
using float_sequence3 = sequence_type<float, 3>;
using float_sequence4 = sequence_type<float, 4>;

using double_sequence2 = sequence_type<double, 2>;
using double_sequence3 = sequence_type<double, 3>;
using double_sequence4 = sequence_type<double, 4>;




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



//
//template<primitive_number COORDINATE, ::collection::count t_iDimension>
//struct matrix_type
//{
//
//   using matrix_tag = matrix_t;
//   using BASE_COORDINATE = COORDINATE;
//   using UNIT_TYPE = COORDINATE;
//
//
//   COORDINATE this->m_coordinatea[t_iDimension * t_iDimension];
//
//
//};
//



template<primitive_number NUMBER, int t_iSize>
struct std::hash<::sequence_type<NUMBER, t_iSize>>
{
   std::size_t operator()(const ::sequence_type<NUMBER, t_iSize> &s) const noexcept
   {
      return std::hash<::sequence_t_type<NUMBER, t_iSize>>{}(
         (const ::sequence_t_type<NUMBER, t_iSize> & )(s));
   }
};

//
//namespace geometry
//{
//
//
//   template<primitive_number NUMBER>
//   sequence_type<NUMBER, 3> normalize(const sequence_type<NUMBER, 3> &v)
//   {
//      
//      float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
//      
//      if (length > 0.0f)
//      {
//
//         return v / length;
//
//      }
//      else
//      {
//
//         return sequence_type<NUMBER, 3>(0.0f); // or return v (undefined direction)
//
//      }
//
//
//   }
//
//
//} // namespace geometry
//


template < primitive_number NUMBER, primitive_number NUMBER1, int t_iSize >
inline sequence_type<largest_number<NUMBER, NUMBER1>, t_iSize>
operator*(NUMBER n, const sequence_type< NUMBER, t_iSize> & s)
{
   sequence_type<largest_number<NUMBER, NUMBER1>, t_iSize> result;
   for (::collection::count i = 0; i < t_iSize; ++i)
      result[i] = (largest_number<NUMBER, NUMBER1>)(n * this->m_coordinatea[i]);
   return result;
}
