/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#pragma once

//#include "common.h"
//#include "traits.h"
//#include <cassert>
//#include <cmath>
//#include <iosfwd>
//#include <string.h> // memset


template < typename COORDINATE, size_t t_iSize >
struct vector_base
{

   using BASE_COORDINATE = COORDINATE;


   COORDINATE m_coordinatea[t_iSize];


   static constexpr bool IS_MATRIX = false;
   static constexpr size_t SIZE = t_iSize;


   vector_base() { }

   vector_base(const vector_base&) = default;

   template <typename T,
      std::enable_if_t<T::SIZE == SIZE &&
      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
   vector_base(const T & a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] = (COORDINATE)a[i];
   }

   template <typename T>
   vector_base(const vector_base<T, SIZE>& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] = (COORDINATE)a.m_coordinatea[i];
   }

   vector_base(COORDINATE s) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] = s;
   }

   template <size_t S = SIZE, std::enable_if_t<S == 2, int> = 0>
   vector_base(COORDINATE v0, COORDINATE v1) {
      m_coordinatea[0] = v0; m_coordinatea[1] = v1;
   }

   template <size_t S = SIZE, std::enable_if_t<S == 3, int> = 0>
   vector_base(COORDINATE v0, COORDINATE v1, COORDINATE v2) {
      m_coordinatea[0] = v0; m_coordinatea[1] = v1; m_coordinatea[2] = v2;
   }

   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   vector_base(COORDINATE v0, COORDINATE v1, COORDINATE v2, COORDINATE v3) {
      m_coordinatea[0] = v0; m_coordinatea[1] = v1; m_coordinatea[2] = v2; m_coordinatea[3] = v3;
   }

   vector_base operator-() const {
      vector_base result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = -m_coordinatea[i];
      return result;
   }

   friend vector_base operator+(const vector_base& a, const vector_base& b) {
      vector_base result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] + b.m_coordinatea[i];
      return result;
   }

   vector_base& operator+=(const vector_base& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] += a.m_coordinatea[i];
      return *this;
   }

   friend vector_base operator-(const vector_base& a, const vector_base& b) {
      vector_base result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] - b.m_coordinatea[i];
      return result;
   }

   vector_base& operator-=(const vector_base& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] -= a.m_coordinatea[i];
      return *this;
   }

   friend vector_base operator*(const vector_base& a, const vector_base& b) {
      vector_base result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] * b.m_coordinatea[i];
      return result;
   }

   vector_base& operator*=(const vector_base& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] *= a.m_coordinatea[i];
      return *this;
   }

   friend vector_base operator/(const vector_base& a, const vector_base& b) {
      vector_base result;
      for (size_t i = 0; i < SIZE; ++i)
         result[i] = a.m_coordinatea[i] / b.m_coordinatea[i];
      return result;
   }

   vector_base& operator/=(const vector_base& a) {
      for (size_t i = 0; i < SIZE; ++i)
         m_coordinatea[i] /= a.m_coordinatea[i];
      return *this;
   }

   bool operator==(const vector_base& a) const {
      for (size_t i = 0; i < SIZE; ++i) {
         if (m_coordinatea[i] != a.m_coordinatea[i])
            return false;
      }
      return true;
   }

   constexpr bool operator!=(const vector_base& a) const { return !operator==(a); }

   constexpr const COORDINATE& operator[](size_t i) const { return m_coordinatea[i]; }

   constexpr COORDINATE& operator[](size_t i) { return m_coordinatea[i]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   const COORDINATE& x() const { return m_coordinatea[0]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 1), int> = 0>
   COORDINATE& x() { return m_coordinatea[0]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   const COORDINATE& y() const { return m_coordinatea[1]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 2), int> = 0>
   COORDINATE& y() { return m_coordinatea[1]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   const COORDINATE& z() const { return m_coordinatea[2]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 3), int> = 0>
   COORDINATE& z() { return m_coordinatea[2]; }

   template <size_t S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   const COORDINATE& w() const { return m_coordinatea[3]; }
   template <size_t S = SIZE, std::enable_if_t<(S >= 4), int> = 0>
   COORDINATE& w() { return m_coordinatea[3]; }


};


template <typename COORDINATE, size_t SIZE>
COORDINATE dot(const vector_base<COORDINATE, SIZE>& a1, const vector_base<COORDINATE, SIZE>& a2) {
   COORDINATE result = a1.m_coordinatea[0] * a2.m_coordinatea[0];
   for (size_t i = 1; i < SIZE; ++i)
      result += a1.m_coordinatea[i] * a2.m_coordinatea[i];
   return result;
}

template <typename COORDINATE, size_t SIZE>
COORDINATE squared_norm(const vector_base<COORDINATE, SIZE>& a) {
   COORDINATE result = a.m_coordinatea[0] * a.m_coordinatea[0];
   for (size_t i = 1; i < SIZE; ++i)
      result += a.m_coordinatea[i] * a.m_coordinatea[i];
   return result;
}

template <typename COORDINATE, size_t SIZE>
COORDINATE norm(const vector_base<COORDINATE, SIZE>& a)
{
   return ::sqrt(squared_norm(a));
}

template <typename COORDINATE, size_t SIZE>
vector_base<COORDINATE, SIZE> normalize(const vector_base<COORDINATE, SIZE>& a) {
   return a / norm(a);
}

template <typename COORDINATE>
vector_base<COORDINATE, 3> cross(const vector_base<COORDINATE, 3>& a, const vector_base<COORDINATE, 3>& b) {
   return vector_base<COORDINATE, 3>(
      a.y() * b.z() - a.z() * b.y(),
      a.z() * b.x() - a.x() * b.z(),
      a.x() * b.y() - a.y() * b.x()
   );
}

template <typename COORDINATE, size_t SIZE>
vector_base<COORDINATE, SIZE> max(const vector_base<COORDINATE, SIZE>& a1, const vector_base<COORDINATE, SIZE>& a2) {
   vector_base<COORDINATE, SIZE> result;
   for (size_t i = 0; i < SIZE; ++i)
      result.m_coordinatea[i] = std::max(a1.m_coordinatea[i], a2.m_coordinatea[i]);
   return result;
}

template <typename COORDINATE, size_t SIZE>
vector_base<COORDINATE, SIZE> min(const vector_base<COORDINATE, SIZE>& a1, const vector_base<COORDINATE, SIZE>& a2) {
   vector_base<COORDINATE, SIZE> result;
   for (size_t i = 0; i < SIZE; ++i)
      result.m_coordinatea[i] = std::min(a1.m_coordinatea[i], a2.m_coordinatea[i]);
   return result;
}

// Import some common Enoki types
using vector2_i32 = vector_base<::i32, 2>;
using vector3_i32 = vector_base<::i32, 3>;
using vector4_i32 = vector_base<::i32, 4>;
using vector2_i64 = vector_base<::i64, 2>;
using vector3_i64 = vector_base<::i64, 3>;
using vector4_i64 = vector_base<::i64, 4>;
using vector2_f32 = vector_base<::f32, 2>;
using vector3_f32 = vector_base<::f32, 3>;
using vector4_f32 = vector_base<::f32, 4>;
using vector2_f64 = vector_base<::f64, 2>;
using vector3_f64 = vector_base<::f64, 3>;
using vector4_f64 = vector_base<::f64, 4>;

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
// * | Channel | vector_base Index | Vector4f field | Color field |
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

   static Matrix scale(const vector_base<COORDINATE, SIZE - 1>& m_coordinatea) {
      Matrix result;
      memset(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i)
         result.m[i][i] = i < SIZE - 1 ? m_coordinatea[i] : 1;
      return result;
   }

   static Matrix scale(const vector_base<COORDINATE, SIZE>& m_coordinatea) {
      Matrix result;
      memset(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (size_t i = 0; i < SIZE; ++i)
         result.m[i][i] = m_coordinatea[i];
      return result;
   }

   static Matrix translate(const vector_base<COORDINATE, SIZE - 1>& m_coordinatea) {
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
   static Matrix rotate(const vector_base<COORDINATE, 3>& axis, COORDINATE angle)
   {

      COORDINATE s = ::sin(angle);
      COORDINATE c = ::cos(angle);
      COORDINATE t = 1 - c;

      Matrix result(0);
      result.m[3][3] = 1;
      result.m[0][0] = c + axis.x() * axis.x() * t;
      result.m[1][1] = c + axis.y() * axis.y() * t;
      result.m[2][2] = c + axis.z() * axis.z() * t;

      COORDINATE tmp1 = axis.x() * axis.y() * t;
      COORDINATE tmp2 = axis.z() * s;

      result.m[0][1] = tmp1 + tmp2;
      result.m[1][0] = tmp1 - tmp2;

      tmp1 = axis.x() * axis.z() * t;
      tmp2 = axis.y() * s;
      result.m[0][2] = tmp1 - tmp2;
      result.m[2][0] = tmp1 + tmp2;

      tmp1 = axis.y() * axis.z() * t;
      tmp2 = axis.x() * s;
      result.m[1][2] = tmp1 + tmp2;
      result.m[2][1] = tmp1 - tmp2;

      return result;

   }


   template <size_t S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix perspective(COORDINATE fov, COORDINATE near_, COORDINATE far_, COORDINATE aspect = 1.f)
   {

      COORDINATE recip = 1 / (near_ - far_);
      COORDINATE c = 1 / ::tan(.5f * fov);

      Matrix trafo = Matrix::scale(vector_base<COORDINATE, SIZE>(c / aspect, c, (near_ + far_) * recip, 0.f));

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
   static Matrix look_at(const vector_base<COORDINATE, 3>& origin,
      const vector_base<COORDINATE, 3>& target,
      const vector_base<COORDINATE, 3>& up)
   {

      auto dir = normalize(target - origin);
      auto left = normalize(cross(dir, up));
      auto new_up = cross(left, dir);
      dir = -dir;

      Matrix result(0);
      result.m[0][0] = left.x();
      result.m[0][1] = left.y();
      result.m[0][2] = left.z();
      result.m[1][0] = new_up.x();
      result.m[1][1] = new_up.y();
      result.m[1][2] = new_up.z();
      result.m[2][0] = dir.x();
      result.m[2][1] = dir.y();
      result.m[2][2] = dir.z();
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






