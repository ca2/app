// From sequence.h by camilo on 2025-07-30 20:59 <3ThomasBorregaardSørensen!!
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

#pragma once

/// Simple matrix class with column-major storage
template <typename Value_, ::collection::count Size_> struct Matrix {
   static constexpr bool IsNanoGUI = true;
   static constexpr bool IsMatrix = true;

   using COORDINATE = Value_;
   static constexpr ::collection::count SIZE = Size_;

   Matrix() {}

   explicit Matrix(COORDINATE s) {
      ::memory_set(m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (::collection::count i = 0; i < SIZE; ++i)
         m[i][i] = s;
   }

   friend Matrix operator*(const Matrix& a, const Matrix& b) {
      Matrix c;
      for (::collection::count i = 0; i < SIZE; ++i) {
         for (::collection::count j = 0; j < SIZE; ++j) {
            COORDINATE accum = 0;
            for (::collection::count k = 0; k < SIZE; ++k)
               accum += a.m[k][i] * b.m[j][k];
            c.m[j][i] = accum;
         }
      }
      return c;
   }

   static Matrix scale(const sequence_type<COORDINATE, SIZE - 1>& m_coordinatea) {
      Matrix result;
      ::memory_set(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (::collection::count i = 0; i < SIZE; ++i)
         result.m[i][i] = i < SIZE - 1 ? m_coordinatea[i] : 1;
      return result;
   }

   static Matrix scale(const sequence_type<COORDINATE, SIZE>& m_coordinatea) {
      Matrix result;
      ::memory_set(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (::collection::count i = 0; i < SIZE; ++i)
         result.m[i][i] = m_coordinatea[i];
      return result;
   }

   static Matrix translate(const sequence_type<COORDINATE, SIZE - 1>& m_coordinatea) {
      Matrix result;
      ::memory_set(result.m, 0, sizeof(COORDINATE) * SIZE * SIZE);
      for (::collection::count i = 0; i < SIZE; ++i) {
         result.m[i][i] = 1.f;
         if (i < SIZE - 1)
            result.m[SIZE - 1][i] = m_coordinatea[i];
      }
      return result;
   }


   template <::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0>
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


   template <::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0>
   static Matrix perspective(COORDINATE fov, COORDINATE near_, COORDINATE far_, COORDINATE aspect = 1.f)
   {

      COORDINATE recip = 1 / (near_ - far_);
      COORDINATE c = 1 / ::tan(.5f * fov);

      Matrix trafo = Matrix::scale(sequence_type<COORDINATE, SIZE>(c / aspect, c, (near_ + far_) * recip, 0.f));

      trafo.m[3][2] = 2.f * near_ * far_ * recip;
      trafo.m[2][3] = -1.f;

      return trafo;
   }

   template <::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0>
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

   template <::collection::count S = SIZE, std::enable_if_t<S == 4, int> = 0>
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





