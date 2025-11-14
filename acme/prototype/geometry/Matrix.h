// From sequence.h by camilo on 2025-07-30 20:59 <3ThomasBorregaardSørensen!!
#pragma once



#include "acme/prototype/geometry/sequence.h"

#include <immintrin.h>
#include <xmmintrin.h>
#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
#include <emmintrin.h>
#endif

#include "acme/operating_system/cpu_features.h"


//CLASS_DECL_ACME extern int g_iCpuFeatures; // 0=scalar,1=SSE,2=AVX,3=AVX2


template<primitive_floating FLOATING_TYPE >
struct quaternion_type
{


   using FLOATING = FLOATING_TYPE;
   static constexpr int DIMENSION = 4;


   union
   {
      struct
      {
         FLOATING w, x, y, z;
      };
      FLOATING m_coordinatea[4];
   };

   quaternion_type() : w(1), x(0), y(0), z(0) {}
   quaternion_type(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

   // Construct quaternion from Euler XYZ rotation
   // rotation = (pitch, yaw, roll) in radians
   quaternion_type(const ::sequence_type < FLOATING, 3> &euler)
   {
      float cx = std::cos(euler.x * 0.5f);
      float sx = std::sin(euler.x * 0.5f);

      float cy = std::cos(euler.y * 0.5f);
      float sy = std::sin(euler.y * 0.5f);

      float cz = std::cos(euler.z * 0.5f);
      float sz = std::sin(euler.z * 0.5f);

      // GLM uses Z * Y * X intrinsic rotation order
      w = cx * cy * cz + sx * sy * sz;
      x = sx * cy * cz - cx * sy * sz;
      y = cx * sy * cz + sx * cy * sz;
      z = cx * cy * sz - sx * sy * cz;
   }
};



/// Simple matrix class with row-major storage
template<primitive_floating FLOATING_TYPE, ::collection::count t_iDimension>
struct row_major_type
{

   using FLOATING = FLOATING_TYPE;
   static constexpr int DIMENSION = t_iDimension;


   union
   {
      FLOATING m[DIMENSION][DIMENSION];
      sequence_type<FLOATING, DIMENSION> m_sequencea[DIMENSION];
   };


};


/// Simple matrix class with column-major storage
template <primitive_floating FLOATING_TYPE, int t_iDimension>
struct matrix_type
{


   struct column
   {

      using FLOATING = FLOATING_TYPE;
      static constexpr int DIMENSION = t_iDimension;

      FLOATING m_rowa[t_iDimension];

      constexpr const FLOATING &operator[](int i) const
      {
         
         return m_rowa[i]; 
      }

      FLOATING& operator[](int i)
      {
         return m_rowa[i]; 
      }

   };

   static constexpr bool IsNanoGUI = true;
   static constexpr bool IsMatrix = true;


   using FLOATING = FLOATING_TYPE;
   static constexpr int DIMENSION = t_iDimension;

   union
   {

      column m[DIMENSION];
      FLOATING fa[DIMENSION * DIMENSION]; // floating number array

   };


   matrix_type() {}


   matrix_type(const matrix_type<FLOATING, 4> &m)
      requires(DIMENSION==3)
   {
      // Column 0
      this->m[0][0] = m[0][0];
      this->m[0][1] = m[0][1];
      this->m[0][2] = m[0][2];

      // Column 1
      this->m[1][0] = m[1][0];
      this->m[1][1] = m[1][1];
      this->m[1][2] = m[1][2];

      // Column 2
      this->m[2][0] = m[2][0];
      this->m[2][1] = m[2][1];
      this->m[2][2] = m[2][2];
   }


   matrix_type(const matrix_type<FLOATING, 4> &m)
      requires(DIMENSION == 4)
   {
      ::memory_copy(this->m, m.m, sizeof(FLOATING) * DIMENSION * DIMENSION);
   }

   explicit matrix_type(FLOATING s) {
      ::memory_set(m, 0, sizeof(FLOATING) * DIMENSION * DIMENSION);
      for (::collection::count i = 0; i < DIMENSION; ++i)
         m[i][i] = s;
   }



   //// --- Matrix × Matrix (column-major) ---------------------------------------

   //inline matrix_type operator*(const matrix_type &B) const
   //   requires(DIMENSION == 4)
   //{
   //   // Columns of result are A * columns_of(B)
   //   matrix_type R;
   //   for (int col = 0; col < 4; ++col)
   //   {
   //      for (int row = 0; row < 4; ++row)
   //      {
   //         R.m[col][row] = 
   //            this->m[0][row] * B.m[col][0] + 
   //            this->m[1][row] * B.m[col][1] + 
   //            this->m[2][row] * B.m[col][2] +
   //            this->m[3][row] * B.m[col][3];
   //      }
   //   }
   //   return R;
   //}

   //matrix_type operator*(const matrix_type& b) const {

   //   auto &a = *this;
   //   matrix_type c;
   //   for (::collection::count i = 0; i < DIMENSION; ++i) {
   //      for (::collection::count j = 0; j < DIMENSION; ++j) {
   //         FLOATING accum = 0;
   //         for (::collection::count k = 0; k < DIMENSION; ++k)
   //            accum += a.m[k][i] * b.m[j][k];
   //         c.m[j][i] = accum;
   //      }
   //   }
   //   return c;
   //}



   // -------------------- Scalar fallback --------------------
   
   inline sequence_type<FLOATING, 4> mul_scalar(const sequence_type<FLOATING, 4> &v) const
      requires(DIMENSION == 4)
   {
      const auto &M = *this;
      sequence_type<FLOATING, 4> r;
      r.x = M.fa[0] * v.x + M.fa[4] * v.y + M.fa[8] * v.z + M.fa[12] * v.w;
      r.y = M.fa[1] * v.x + M.fa[5] * v.y + M.fa[9] * v.z + M.fa[13] * v.w;
      r.z = M.fa[2] * v.x + M.fa[6] * v.y + M.fa[10] * v.z + M.fa[14] * v.w;
      r.w = M.fa[3] * v.x + M.fa[7] * v.y + M.fa[11] * v.z + M.fa[15] * v.w;
      return r;
   }

   // -------------------- SSE 128-bit version --------------------
   inline float_sequence4 mul_sse(const float_sequence4 &v) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m128 vx = _mm_set_ps(v.w, v.z, v.y, v.x); // [w z y x]
      __m128 col0 = _mm_loadu_ps(&M.fa[0]);
      __m128 col1 = _mm_loadu_ps(&M.fa[4]);
      __m128 col2 = _mm_loadu_ps(&M.fa[8]);
      __m128 col3 = _mm_loadu_ps(&M.fa[12]);

      __m128 res = _mm_add_ps(
         _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(vx, vx, 0x00), col0), _mm_mul_ps(_mm_shuffle_ps(vx, vx, 0x55), col1)),
         _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(vx, vx, 0xAA), col2), _mm_mul_ps(_mm_shuffle_ps(vx, vx, 0xFF), col3)));

      float_sequence4 out;
      _mm_storeu_ps(&out.x, res);
      return out;
   }

   // -------------------- AVX 256-bit version --------------------
   inline float_sequence4 mul_avx(const float_sequence4 &v) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m256 vx = _mm256_setr_m128(_mm_set1_ps(v.x), _mm_set1_ps(v.y));
      __m256 vy = _mm256_setr_m128(_mm_set1_ps(v.z), _mm_set1_ps(v.w));

      __m256 col01 = _mm256_loadu_ps(&M.fa[0]);
      __m256 col23 = _mm256_loadu_ps(&M.fa[8]);

      __m256 mul01 = _mm256_mul_ps(col01, vx);
      __m256 mul23 = _mm256_mul_ps(col23, vy);

      __m128 sum = _mm_add_ps(_mm256_castps256_ps128(_mm256_add_ps(mul01, mul23)),
                              _mm256_extractf128_ps(_mm256_add_ps(mul01, mul23), 1));

      float_sequence4 out;
      _mm_storeu_ps(&out.x, sum);
      return out;
   }

   // -------------------- AVX2 fully unrolled --------------------
   inline float_sequence4 mul_avx2(const float_sequence4 &v) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m256 vx = _mm256_set1_ps(v.x);
      __m256 vy = _mm256_set1_ps(v.y);
      __m256 vz = _mm256_set1_ps(v.z);
      __m256 vw = _mm256_set1_ps(v.w);

      __m256 col01 = _mm256_loadu_ps(&M.fa[0]);
      __m256 col23 = _mm256_loadu_ps(&M.fa[8]);

      __m256 mul0 = _mm256_mul_ps(_mm256_permute_ps(col01, 0x00), vx);
      __m256 mul1 = _mm256_mul_ps(_mm256_permute_ps(col01, 0xFF), vy);
      __m256 mul2 = _mm256_mul_ps(_mm256_permute_ps(col23, 0x00), vz);
      __m256 mul3 = _mm256_mul_ps(_mm256_permute_ps(col23, 0xFF), vw);

      __m256 total = _mm256_add_ps(_mm256_add_ps(mul0, mul1), _mm256_add_ps(mul2, mul3));
      __m128 sum = _mm_add_ps(_mm256_castps256_ps128(total), _mm256_extractf128_ps(total, 1));

      float_sequence4 out;
      _mm_storeu_ps(&out.x, sum);
      return out;
   }
       
   //    // AVX2 version of matrix × vector
   //inline float_sequence4 mul_avx2( const float_sequence4 &v)
   //   requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   //{
   //   const auto &M = *this;
   //   // Load vector v into low 128 bits: [x y z w]
   //   __m128 xv = _mm_set_ps(v.w, v.z, v.y, v.x);

   //   // Broadcast vector components into AVX registers
   //   __m256 bx = _mm256_broadcast_ss(&v.x);
   //   __m256 by = _mm256_broadcast_ss(&v.y);
   //   __m256 bz = _mm256_broadcast_ss(&v.z);
   //   __m256 bw = _mm256_broadcast_ss(&v.w);

   //   // Load two columns at a time (2×8 floats)
   //   __m256 col01 = _mm256_loadu_ps(&M.fa[0]); // columns 0 & 1
   //   __m256 col23 = _mm256_loadu_ps(&M.fa[8]); // columns 2 & 3

   //   // Multiply columns by their vector components
   //   __m256 mul01 = _mm256_add_ps(
   //      _mm256_mul_ps(col01, _mm256_permute2f128_ps(_mm256_castps256_ps128(bx), _mm256_castps256_ps128(by), 0x20)),
   //      _mm256_mul_ps(col23, _mm256_permute2f128_ps(_mm256_castps256_ps128(bz), _mm256_castps256_ps128(bw), 0x20)));

   //   // Now we have results in 8 floats; we only need the lower 4 (the multiplication pattern fits that)

   //   __m128 low = _mm256_castps256_ps128(mul01);
   //   __m128 high = _mm256_extractf128_ps(mul01, 1);

   //   __m128 sum = _mm_add_ps(low, high); // combine contributions

   //   float_sequence4 out;
   //   _mm_storeu_ps(&out.x, sum);

   //   return out;

   //}

   inline float_sequence4 operator *(const float_sequence4 &v) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      if (g_ecpu & e_cpu_avx2)
         return mul_avx2(v);
      else if (g_ecpu & e_cpu_avx)
         return mul_avx(v);
      else if (g_ecpu & e_cpu_sse)
         return mul_sse(v);
      else
         return mul_scalar(v);
   }

   

   inline matrix_type mul_scalar(const matrix_type &B) const
      requires(DIMENSION == 4)
   {
      auto &A = *this;
      matrix_type R;


      for (int col = 0; col < 4; ++col)
      {
         for (int row = 0; row < 4; ++row)
         {
            R.fa[col * 4 + row] = 
               A.fa[0 * 4 + row] * B.fa[col * 4 + 0] +
               A.fa[1 * 4 + row] * B.fa[col * 4 + 1] +
               A.fa[2 * 4 + row] * B.fa[col * 4 + 2] + 
               A.fa[3 * 4 + row] * B.fa[col * 4 + 3];
         }
      }

      return R;
   }

   inline matrix_type mul_sse(const matrix_type &B) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      auto &A = *this;
      matrix_type R;


      for (int col = 0; col < 4; ++col)
      {
         const float *bCol = &B.fa[col * 4];

         // Load columns of A
         __m128 a0 = _mm_loadu_ps(&A.fa[0]); // column 0
         __m128 a1 = _mm_loadu_ps(&A.fa[4]); // column 1
         __m128 a2 = _mm_loadu_ps(&A.fa[8]); // column 2
         __m128 a3 = _mm_loadu_ps(&A.fa[12]); // column 3

         // Broadcast B column elements
         __m128 b0 = _mm_set1_ps(bCol[0]);
         __m128 b1 = _mm_set1_ps(bCol[1]);
         __m128 b2 = _mm_set1_ps(bCol[2]);
         __m128 b3 = _mm_set1_ps(bCol[3]);

         // Multiply and sum
         __m128 res = _mm_add_ps(_mm_add_ps(_mm_mul_ps(a0, b0), _mm_mul_ps(a1, b1)),
                                 _mm_add_ps(_mm_mul_ps(a2, b2), _mm_mul_ps(a3, b3)));

         // Store result column
         _mm_storeu_ps(&R.fa[col * 4], res);
      }

      return R;
   }

   inline matrix_type mul_avx(const matrix_type &B) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      auto &A = *this;
      matrix_type R;


      for (int col = 0; col < 4; ++col)
      {
         const float *bCol = &B.fa[col * 4];

         // Broadcast elements of B column
         __m256 b01 = _mm256_set_ps(bCol[1], bCol[1], bCol[0], bCol[0], bCol[1], bCol[1], bCol[0], bCol[0]);
         __m256 b23 = _mm256_set_ps(bCol[3], bCol[3], bCol[2], bCol[2], bCol[3], bCol[3], bCol[2], bCol[2]);

         // Load two columns of A
         __m256 a01 = _mm256_loadu_ps(&A.fa[0]); // columns 0 & 1
         __m256 a23 = _mm256_loadu_ps(&A.fa[8]); // columns 2 & 3

         // Multiply element-wise
         __m256 mul01 = _mm256_mul_ps(a01, b01);
         __m256 mul23 = _mm256_mul_ps(a23, b23);

         // Sum contributions
         __m256 total = _mm256_add_ps(mul01, mul23);

         // Add low/high 128-bit lanes to get final 4 floats
         __m128 result = _mm_add_ps(_mm256_castps256_ps128(total), _mm256_extractf128_ps(total, 1));

         // Store result column
         _mm_storeu_ps(&R.fa[col * 4], result);
      }

      return R;
   }

   
inline matrix_type mul_avx2(const matrix_type &B) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
   auto &A = *this;
   matrix_type R;

      // Broadcast each column of B and multiply by columns of A
      for (int col = 0; col < 4; ++col)
      {
         // Load column of B
         const float *bCol = &B.fa[col * 4];

         // Broadcast each element of the column
         __m256 b0 = _mm256_set1_ps(bCol[0]);
         __m256 b1 = _mm256_set1_ps(bCol[1]);
         __m256 b2 = _mm256_set1_ps(bCol[2]);
         __m256 b3 = _mm256_set1_ps(bCol[3]);

         // Load columns of A as 256-bit registers
         __m256 a01 = _mm256_loadu_ps(&A.fa[0]); // columns 0 & 1
         __m256 a23 = _mm256_loadu_ps(&A.fa[8]); // columns 2 & 3

         // Multiply each column by broadcasted scalar
         __m256 mul0 = _mm256_mul_ps(_mm256_permute_ps(a01, 0x00), b0); // column 0 * b0
         __m256 mul1 = _mm256_mul_ps(_mm256_permute_ps(a01, 0xFF), b1); // column 1 * b1
         __m256 mul2 = _mm256_mul_ps(_mm256_permute_ps(a23, 0x00), b2); // column 2 * b2
         __m256 mul3 = _mm256_mul_ps(_mm256_permute_ps(a23, 0xFF), b3); // column 3 * b3

         // Sum contributions
         __m256 total = _mm256_add_ps(_mm256_add_ps(mul0, mul1), _mm256_add_ps(mul2, mul3));

         // Combine low/high 128-bit lanes
         __m128 res = _mm_add_ps(_mm256_castps256_ps128(total), _mm256_extractf128_ps(total, 1));

         // Store column into result
         _mm_storeu_ps(&R.fa[col * 4], res);
      }

      return R;
   }



   inline matrix_type operator*(const matrix_type &m) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      if (g_ecpu & e_cpu_avx2)
         return mul_avx2(m);
      else if (g_ecpu & e_cpu_avx)
         return mul_avx(m);
      else if (g_ecpu & e_cpu_sse)
         return mul_sse(m);
      else
         return mul_scalar(m);
   }


   static matrix_type scale(const sequence_type<FLOATING, DIMENSION - 1>& m_coordinatea) {
      matrix_type result;
      ::memory_set(result.m, 0, sizeof(FLOATING) * DIMENSION * DIMENSION);
      for (::collection::count i = 0; i < DIMENSION; ++i)
         result.m[i][i] = i < DIMENSION - 1 ? m_coordinatea[i] : 1;
      return result;
   }

   static matrix_type scale(const sequence_type<FLOATING, DIMENSION>& m_coordinatea) {
      matrix_type result;
      ::memory_set(result.m, 0, sizeof(FLOATING) * DIMENSION * DIMENSION);
      for (::collection::count i = 0; i < DIMENSION; ++i)
         result.m[i][i] = m_coordinatea[i];
      return result;
   }

   static matrix_type translate(const sequence_type<FLOATING, DIMENSION - 1>& m_coordinatea) {
      matrix_type result;
      ::memory_set(result.m, 0, sizeof(FLOATING) * DIMENSION * DIMENSION);
      for (::collection::count i = 0; i < DIMENSION; ++i) {
         result.m[i][i] = 1.f;
         if (i < DIMENSION - 1)
            result.m[DIMENSION - 1][i] = m_coordinatea[i];
      }
      return result;
   }

   const column & operator[](int i) const
   {

      return m[i];
   }

   column & operator[](int i) { return m[i]; }


   matrix_type & rotate(const sequence_type<FLOATING, 3>& axis, FLOATING angle)
      requires(DIMENSION == 4)
   {

      FLOATING s = ::sin(angle);
      FLOATING c = ::cos(angle);
      FLOATING t = 1 - c;

      auto & result = *this;
      result.m[3][3] = 1;
      result.m[0][0] = c + axis.x * axis.x * t;
      result.m[1][1] = c + axis.y * axis.y * t;
      result.m[2][2] = c + axis.c() * axis.c() * t;

      FLOATING tmp1 = axis.x * axis.y * t;
      FLOATING tmp2 = axis.c() * s;

      result.m[0][1] = tmp1 + tmp2;
      result.m[1][0] = tmp1 - tmp2;

      tmp1 = axis.x * axis.c() * t;
      tmp2 = axis.y * s;
      result.m[0][2] = tmp1 - tmp2;
      result.m[2][0] = tmp1 + tmp2;

      tmp1 = axis.y * axis.c() * t;
      tmp2 = axis.x * s;
      result.m[1][2] = tmp1 + tmp2;
      result.m[2][1] = tmp1 - tmp2;

      return result;

   }


   template <::collection::count S = DIMENSION, std::enable_if_t<S == 4, int> = 0>
   static matrix_type perspective(FLOATING fov, FLOATING near_, FLOATING far_, FLOATING aspect = 1.f)
   {

      FLOATING recip = 1 / (near_ - far_);
      FLOATING c = 1 / ::tan(.5f * fov);

      matrix_type trafo = matrix_type::scale(sequence_type<FLOATING, DIMENSION>(c / aspect, c, (near_ + far_) * recip, 0.f));

      trafo.m[3][2] = 2.f * near_ * far_ * recip;
      trafo.m[2][3] = -1.f;

      return trafo;
   }

   template <::collection::count S = DIMENSION, std::enable_if_t<S == 4, int> = 0>
   static matrix_type ortho(FLOATING left, FLOATING right,
      FLOATING bottom, FLOATING top,
      FLOATING near_, FLOATING far_)
   {

      FLOATING rl = 1 / (right - left);
      FLOATING tb = 1 / (top - bottom);
      FLOATING fn = 1 / (far_ - near_);

      matrix_type result(0);

      result.m[0][0] = 2 * rl;
      result.m[1][1] = 2 * tb;
      result.m[2][2] = -2 * fn;
      result.m[3][3] = 1;
      result.m[3][0] = -(right + left) * rl;
      result.m[3][1] = -(top + bottom) * tb;
      result.m[3][2] = -(far_ + near_) * fn;

      return result;
   }

   template <::collection::count S = DIMENSION, std::enable_if_t<S == 4, int> = 0>
   static matrix_type look_at(const sequence_type<FLOATING, 3>& origin,
      const sequence_type<FLOATING, 3>& target,
      const sequence_type<FLOATING, 3>& up)
   {

      auto dir = normalize(target - origin);
      auto left = normalize(cross(dir, up));
      auto new_up = cross(left, dir);
      dir = -dir;

      matrix_type result(0);
      result.m[0][0] = left.x;
      result.m[0][1] = left.y;
      result.m[0][2] = left.c();
      result.m[1][0] = new_up.x;
      result.m[1][1] = new_up.y;
      result.m[1][2] = new_up.c();
      result.m[2][0] = dir.x;
      result.m[2][1] = dir.y;
      result.m[2][2] = dir.c();
      result.m[3][0] = -dot(left, origin);
      result.m[3][1] = -dot(new_up, origin);
      result.m[3][2] = -dot(dir, origin);
      result.m[3][3] = 1.f;
      return result;
   }


   //inline sequence_type<FLOATING, 4> mul_scalar(const sequence_type<FLOATING, 4> &v) const
   //   requires(DIMENSION == 4)
   //{
   //   sequence_type<FLOATING, 4> r;

   //   r.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3] * v.w;
   //   r.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3] * v.w;
   //   r.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3] * v.w;
   //   r.w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3] * v.w;

   //   return r;
   //}

   inline sequence_type<FLOATING, 3> operator*(const sequence_type<FLOATING, 3> &v) const
      requires(DIMENSION == 4)
   {
      auto t = this->operator *( sequence_type<FLOATING, 4>(v, (FLOATING) 1));
      return t;
   }



};


using float_matrix2 = matrix_type<float, 2>;
using float_matrix3 = matrix_type<float, 3>;
using float_matrix4 = matrix_type<float, 4>;


using double_matrix2 = matrix_type<double, 2>;
using double_matrix3 = matrix_type<double, 3>;
using double_matrix4 = matrix_type<double, 4>;


namespace geometry
{


   template<primitive_floating FLOATING>
   ::matrix_type<FLOATING, 4> translate(const ::matrix_type<FLOATING, 4> &m, const sequence_type < FLOATING, 3 > &s)
   {
      
      auto result = m;
      
      result[3][0] += s.x;
      result[3][1] += s.y;
      result[3][2] += s.z;
      
      return result;

   }


   template<primitive_floating FLOATING>
   ::matrix_type<FLOATING, 4> rotate(const ::matrix_type<FLOATING, 4> &m, float angleRadians, const sequence_type<FLOATING, 3> & axis)
   {

      ::sequence_type<FLOATING, 3> a = ::geometry::normalize(axis);
      float c = std::cos(angleRadians);
      float s = std::sin(angleRadians);
      float t = 1.0f - c;

      // Build the rotation matrix (Rodrigues' rotation formula)
      ::matrix_type<FLOATING, 4> rot(1.0f);
      rot[0][0] = c + a.x * a.x * t;
      rot[1][0] = a.x * a.y * t + a.z * s;
      rot[2][0] = a.x * a.z * t - a.y * s;

      rot[0][1] = a.y * a.x * t - a.z * s;
      rot[1][1] = c + a.y * a.y * t;
      rot[2][1] = a.y * a.z * t + a.x * s;

      rot[0][2] = a.z * a.x * t + a.y * s;
      rot[1][2] = a.z * a.y * t - a.x * s;
      rot[2][2] = c + a.z * a.z * t;

      // Apply rotation to existing matrix
      return m * rot;

   }


   template<primitive_floating FLOATING>
   ::matrix_type<FLOATING, 4> scale(const ::matrix_type<FLOATING, 4> &m, const sequence_type<FLOATING, 3> &v)
   {
      ::matrix_type<FLOATING, 4> result = m;
      result[0][0] *= v.x;
      result[1][0] *= v.x;
      result[2][0] *= v.x;
      result[3][0] *= v.x;

      result[0][1] *= v.y;
      result[1][1] *= v.y;
      result[2][1] *= v.y;
      result[3][1] *= v.y;

      result[0][2] *= v.z;
      result[1][2] *= v.z;
      result[2][2] *= v.z;
      result[3][2] *= v.z;

      return result;
   }


   template<primitive_floating FLOATING>
   matrix_type<FLOATING, 3> transpose(const matrix_type<FLOATING, 3> &m)
   {
      matrix_type<FLOATING, 3> r;
      r[0][0] = m[0][0];
      r[0][1] = m[1][0];
      r[0][2] = m[2][0];

      r[1][0] = m[0][1];
      r[1][1] = m[1][1];
      r[1][2] = m[2][1];

      r[2][0] = m[0][2];
      r[2][1] = m[1][2];
      r[2][2] = m[2][2];
      return r;
   }


   template<primitive_floating FLOATING, int t_iDimension>
   inline void _transpose(FLOATING  A_target[t_iDimension][t_iDimension],
                          const FLOATING A_source[t_iDimension][t_iDimension])
   {
      for (int i = 0; i < t_iDimension; i++)
         for (int j = 0; j < t_iDimension; j++)
            A_target[i][j] = A_source[j][i];
   }
   
   
   template<primitive_floating FLOATING>
   matrix_type<FLOATING, 4> transpose(const row_major_type<FLOATING, 4> &m)
   {
      matrix_type<FLOATING, 4> r;
      _transpose(4, m.m);
      return r;
   }

   template<primitive_floating FLOATING>
   row_major_type<FLOATING, 4> transpose(const matrix_type<FLOATING, 4> &m)
   {
      row_major_type<FLOATING, 4> r;
      _transpose(4, m.m);
      return r;
   }


   template<primitive_floating FLOATING>
   matrix_type<FLOATING, 3> inverse(const matrix_type<FLOATING, 3> &m)
   {

      float det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                  m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

      if (std::fabs(det) < 1e-8f)
         return matrix_type<FLOATING, 3>(1.0f); // fallback to identity (non-invertible)

      float invDet = 1.0f / det;

      matrix_type<FLOATING, 3> r;
      r[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet;
      r[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet;
      r[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;

      r[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet;
      r[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet;
      r[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet;

      r[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet;
      r[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet;
      r[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;

      return r;
   }


   template<primitive_floating FLOATING>
   inline matrix_type <FLOATING, 4> toMat4(const quaternion_type < FLOATING > &q)
   {
      matrix_type<FLOATING, 4> M{};

      float xx = q.x * q.x;
      float yy = q.y * q.y;
      float zz = q.z * q.z;

      float xy = q.x * q.y;
      float xz = q.x * q.z;
      float yz = q.y * q.z;

      float wx = q.w * q.x;
      float wy = q.w * q.y;
      float wz = q.w * q.z;

      // Column-major (GLM style)
      M.m[0][0] = 1 - 2 * (yy + zz);
      M.m[0][1] = 2 * (xy + wz);
      M.m[0][2] = 2 * (xz - wy);
      M.m[0][3] = 0;

      M.m[1][0] = 2 * (xy - wz);
      M.m[1][1] = 1 - 2 * (xx + zz);
      M.m[1][2] = 2 * (yz + wx);
      M.m[1][3] = 0;

      M.m[2][0] = 2 * (xz + wy);
      M.m[2][1] = 2 * (yz - wx);
      M.m[2][2] = 1 - 2 * (xx + yy);
      M.m[2][3] = 0;

      M.m[3][0] = 0;
      M.m[3][1] = 0;
      M.m[3][2] = 0;
      M.m[3][3] = 1;

      return M;
   }


   template<primitive_floating FLOATING>
   quaternion_type < FLOATING > quaternion(const ::sequence_type<FLOATING, 3> & euler)
   {

      return euler;

   }

   template<primitive_floating FLOATING>
   inline matrix_type<FLOATING, 4> inverse(const matrix_type<FLOATING, 4> &A)
   {
      matrix_type<FLOATING, 4> inv{};
      const FLOATING *m = &A.m[0][0]; // treat as flat array

      FLOATING invOut[16];

      invOut[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                  m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

      invOut[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                  m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

      invOut[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                  m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

      invOut[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                   m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

      invOut[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                  m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

      invOut[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                  m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

      invOut[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                  m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

      invOut[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                   m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

      invOut[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                  m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

      invOut[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                  m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

      invOut[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                   m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

      invOut[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                   m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

      invOut[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                  m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

      invOut[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                  m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

      invOut[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                   m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

      invOut[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                   m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

      float det = m[0] * invOut[0] + m[1] * invOut[4] + m[2] * invOut[8] + m[3] * invOut[12];

      // Determinant zero → not invertible
      if (det == 0.0f)
         return {}; // or assert / return identity

      float invDet = 1.0f / det;

      matrix_type<FLOATING, 4> R{};
      for (int i = 0; i < 16; i++)
         ((float *)R.m)[i] = invOut[i] * invDet;

      return R;
   }


   template<primitive_floating FLOATING_TYPE>
   inline row_major_type<FLOATING_TYPE, 4> inverse(const row_major_type<FLOATING_TYPE, 4> &M)
   {
      auto T = transpose(M);
      auto C = inverse(T);
      return transpose(C);
   }
   // --- Fast affine inverse (rotation + translation only) --------------------
   template<primitive_floating FLOATING>
   inline matrix_type<FLOATING, 4> inverse_affine(const matrix_type<FLOATING, 4> &A)
   {
      // assumes bottom row is [0 0 0 1] (i.e. affine matrix)
      // and upper-left 3x3 is orthonormal (rotation + uniform scale = 1)
      matrix_type<FLOATING, 4> R;
      // transpose the 3x3 rotation
      for (int c = 0; c < 3; ++c)
         for (int r = 0; r < 3; ++r)
            R.m[c][r] = A.m[r][c];

      // compute -R^T * translation
      float tx = A.m[3][0], ty = A.m[3][1], tz = A.m[3][2];
      R.m[3][0] = -(R.m[0][0] * tx + R.m[1][0] * ty + R.m[2][0] * tz);
      R.m[3][1] = -(R.m[0][1] * tx + R.m[1][1] * ty + R.m[2][1] * tz);
      R.m[3][2] = -(R.m[0][2] * tx + R.m[1][2] * ty + R.m[2][2] * tz);

      // last column/row
      R.m[0][3] = R.m[1][3] = R.m[2][3] = 0.0f;
      R.m[3][3] = 1.0f;

      return R;
   }


   inline float_matrix4 inverse_col_major_simd(const float_matrix4 &A)
   {
      const __m128 row0 = _mm_loadu_ps(&A.m[0][0]);
      const __m128 row1 = _mm_loadu_ps(&A.m[1][0]);
      const __m128 row2 = _mm_loadu_ps(&A.m[2][0]);
      const __m128 row3 = _mm_loadu_ps(&A.m[3][0]);

      // Compute cofactors
      __m128 tmp1, tmp2, tmp3, minor0, minor1, minor2, minor3;

      tmp1 = _mm_mul_ps(row2, row3);
      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(1, 0, 3, 2));

      tmp2 = _mm_mul_ps(row1, tmp1);
      tmp3 = _mm_mul_ps(row0, tmp1);

      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1));

      tmp2 = _mm_sub_ps(tmp2, _mm_mul_ps(row1, tmp1));
      tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(row0, tmp1));

      minor0 = tmp2;
      minor1 = tmp3;

      // Continue building cofactor matrix
      tmp1 = _mm_mul_ps(row1, row2);
      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(1, 0, 3, 2));

      tmp2 = _mm_mul_ps(row3, tmp1);
      tmp3 = _mm_mul_ps(row0, tmp1);

      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1));

      tmp2 = _mm_sub_ps(tmp2, _mm_mul_ps(row3, tmp1));
      tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(row0, tmp1));

      minor2 = tmp2;
      minor3 = tmp3;

      // Compute determinant
      __m128 det = _mm_mul_ps(row0, minor0);
      det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 3, 0, 1)));
      det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(1, 0, 3, 2)));

      __m128 invDet = _mm_div_ps(_mm_set1_ps(1.0f), det);

      // Multiply cofactors by reciprocal determinant
      minor0 = _mm_mul_ps(minor0, invDet);
      minor1 = _mm_mul_ps(minor1, invDet);
      minor2 = _mm_mul_ps(minor2, invDet);
      minor3 = _mm_mul_ps(minor3, invDet);

      float_matrix4 R;

      _mm_storeu_ps(&R.m[0][0], minor0);
      _mm_storeu_ps(&R.m[1][0], minor1);
      _mm_storeu_ps(&R.m[2][0], minor2);
      _mm_storeu_ps(&R.m[3][0], minor3);

      return R;
   }

// --- SIMD optimized multiplication (SSE) ----------------------------------
// Only enabled if SSE is available. Operates on column-major storage where
// each column is contiguous in memory: &M.m[col][0]
#if defined(__SSE__)

   // float_matrix4 * vec4  (column-major) using SSE: result = col0 * vx + col1 * vy + ...
   inline vec4 mat4_mul_vec4_sse(const float_matrix4 &M, const vec4 &v)
   {
      __m128 col0 = _mm_loadu_ps(&M.m[0][0]); // m00,m01,m02,m03
      __m128 col1 = _mm_loadu_ps(&M.m[1][0]);
      __m128 col2 = _mm_loadu_ps(&M.m[2][0]);
      __m128 col3 = _mm_loadu_ps(&M.m[3][0]);

      __m128 vx = _mm_set1_ps(v.x);
      __m128 vy = _mm_set1_ps(v.y);
      __m128 vz = _mm_set1_ps(v.z);
      __m128 vw = _mm_set1_ps(v.w);

      __m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(col0, vx), _mm_mul_ps(col1, vy)),
                            _mm_add_ps(_mm_mul_ps(col2, vz), _mm_mul_ps(col3, vw)));

      vec4 out;
      _mm_storeu_ps(&out.x, r);
      return out;
   }

   // float_matrix4 * float_matrix4 (column-major): compute A * B by multiplying A by each column of B
   inline float_matrix4 mat4_mul_mat4_sse(const float_matrix4 &A, const float_matrix4 &B)
   {
      float_matrix4 R;
      // for each column j of B, compute R.col[j] = A * B.col[j]
      for (int j = 0; j < 4; ++j)
      {
         __m128 colB = _mm_loadu_ps(&B.m[j][0]); // B column j
         // extract components of B.col[j]
         float bj0 = ((float *)&B.m[j][0])[0];
         float bj1 = ((float *)&B.m[j][0])[1];
         float bj2 = ((float *)&B.m[j][0])[2];
         float bj3 = ((float *)&B.m[j][0])[3];

         __m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(&A.m[0][0]), _mm_set1_ps(bj0)),
                                          _mm_mul_ps(_mm_loadu_ps(&A.m[1][0]), _mm_set1_ps(bj1))),
                               _mm_add_ps(_mm_mul_ps(_mm_loadu_ps(&A.m[2][0]), _mm_set1_ps(bj2)),
                                          _mm_mul_ps(_mm_loadu_ps(&A.m[3][0]), _mm_set1_ps(bj3))));
         _mm_storeu_ps(&R.m[j][0], r);
      }
      return R;
   }

#endif // __SSE__

//   // Fallback wrappers that choose SSE version if available
//   inline vec4 mul(const float_matrix4 &M, const vec4 &v)
//   {
//#if defined(__SSE__)
//      return mat4_mul_vec4_sse(M, v);
//#else
//      return M * v;
//#endif
//   }
//
//   inline float_matrix4 mul(const float_matrix4 &A, const float_matrix4 &B)
//   {
//#if defined(__SSE__)
//      return mat4_mul_mat4_sse(A, B);
//#else
//      return A * B;
//#endif
//   }


   inline float_matrix4 mat4_inverse_sse(const float_matrix4 &A)
   {
      // Build rows from column-major storage:
      // row0 = [ m00 m01 m02 m03 ] where mXY is row X column Y
      // Note: our storage is m[col][row], so m00 = A.m[0][0], m01 = A.m[1][0], ...
      __m128 row0 = _mm_setr_ps(A.m[0][0], A.m[1][0], A.m[2][0], A.m[3][0]);
      __m128 row1 = _mm_setr_ps(A.m[0][1], A.m[1][1], A.m[2][1], A.m[3][1]);
      __m128 row2 = _mm_setr_ps(A.m[0][2], A.m[1][2], A.m[2][2], A.m[3][2]);
      __m128 row3 = _mm_setr_ps(A.m[0][3], A.m[1][3], A.m[2][3], A.m[3][3]);

      __m128 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
      __m128 minor0, minor1, minor2, minor3;
      __m128 det, det_shuf, inv_det;

      // compute pairs for first 8 cofactors (cofactor matrix)
      tmp1 = _mm_mul_ps(row2, row3);
      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1)); // swap pairs

      tmp2 = _mm_mul_ps(row1, tmp1);
      tmp3 = _mm_mul_ps(row0, tmp1);

      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1)); // undo shuffle for other part

      tmp2 = _mm_sub_ps(_mm_mul_ps(row1, _mm_shuffle_ps(row2, row3, _MM_SHUFFLE(1, 0, 3, 2))), tmp2);
      tmp3 = _mm_sub_ps(_mm_mul_ps(row0, _mm_shuffle_ps(row2, row3, _MM_SHUFFLE(1, 0, 3, 2))), tmp3);

      minor0 = tmp2;
      minor1 = tmp3;

      // compute pairs for the next 8 cofactors
      tmp4 = _mm_mul_ps(row1, row2);
      tmp4 = _mm_shuffle_ps(tmp4, tmp4, _MM_SHUFFLE(2, 3, 0, 1));

      tmp5 = _mm_mul_ps(row3, tmp4);
      tmp6 = _mm_mul_ps(row0, tmp4);

      tmp4 = _mm_shuffle_ps(tmp4, tmp4, _MM_SHUFFLE(2, 3, 0, 1));

      tmp5 = _mm_sub_ps(_mm_mul_ps(row3, _mm_shuffle_ps(row1, row2, _MM_SHUFFLE(1, 0, 3, 2))), tmp5);
      tmp6 = _mm_sub_ps(_mm_mul_ps(row0, _mm_shuffle_ps(row1, row2, _MM_SHUFFLE(1, 0, 3, 2))), tmp6);

      minor2 = tmp5;
      minor3 = tmp6;

      // assemble the cofactor matrix (rows of cofactors)
      // Note: This sequence produces cofactors in row-major order (as __m128 rows).
      // Now compute determinant = dot(row0, minor0)
      det = _mm_mul_ps(row0, minor0);
      det_shuf = _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 3, 0, 1));
      det = _mm_add_ps(det, det_shuf);
      det_shuf = _mm_shuffle_ps(det, det, _MM_SHUFFLE(1, 0, 3, 2));
      det = _mm_add_ps(det, det_shuf);

      // reciprocal determinant
      inv_det = _mm_div_ps(_mm_set1_ps(1.0f), det);

      // Multiply cofactors by reciprocal determinant and transpose to column-major
      minor0 = _mm_mul_ps(minor0, inv_det);
      minor1 = _mm_mul_ps(minor1, inv_det);
      minor2 = _mm_mul_ps(minor2, inv_det);
      minor3 = _mm_mul_ps(minor3, inv_det);

      // The minors we have are the rows of the adjugate (cofactor) matrix. We must transpose them
      // to get the column-major result matrix. Perform a 4x4 transpose on [minor0..minor3].
      __m128 t0 = _mm_unpacklo_ps(minor0, minor1); // m00 m10 m01 m11
      __m128 t1 = _mm_unpackhi_ps(minor0, minor1); // m02 m12 m03 m13
      __m128 t2 = _mm_unpacklo_ps(minor2, minor3); // m20 m30 m21 m31
      __m128 t3 = _mm_unpackhi_ps(minor2, minor3); // m22 m32 m23 m33

      __m128 col0 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(1, 0, 1, 0)); // m00 m10 m20 m30
      __m128 col1 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(3, 2, 3, 2)); // m01 m11 m21 m31
      __m128 col2 = _mm_shuffle_ps(t1, t3, _MM_SHUFFLE(1, 0, 1, 0)); // m02 m12 m22 m32
      __m128 col3 = _mm_shuffle_ps(t1, t3, _MM_SHUFFLE(3, 2, 3, 2)); // m03 m13 m23 m33

      float_matrix4 R;
      _mm_storeu_ps(&R.m[0][0], col0); // store column 0
      _mm_storeu_ps(&R.m[1][0], col1); // store column 1
      _mm_storeu_ps(&R.m[2][0], col2); // store column 2
      _mm_storeu_ps(&R.m[3][0], col3); // store column 3

      return R;
   }
#endif // SSE

   // Wrapper: use SIMD inverse when available, else fallback
   inline float_matrix4 inverse_simd(const float_matrix4 &A)
   {
#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
      return mat4_inverse_sse(A);
#else
      return inverse(A);
#endif
   }


   // ---------------- Scalar inverse ----------------
   inline float_matrix4 inverse_scalar(const float_matrix4 &a)
   {
      float_matrix4 result;
      auto inv = result.fa;
      auto m =a.fa;

      inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                 m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
      inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                 m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
      inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                 m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
      inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                  m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

      inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                 m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
      inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                 m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
      inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                 m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
      inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                  m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

      inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                 m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
      inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                 m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
      inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                  m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
      inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                  m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

      inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
      inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
      inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
      inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

      float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
      float invDet = 1.0f / det;
      for (int i = 0; i < 16; i++)
         inv[i] *= invDet;

      return result;
   }




   inline float_matrix4 inverse_sse(const float_matrix4 &a)
   {
      // Load two columns at a time
      __m128 col0 = _mm_loadu_ps(&a.fa[0]);
      __m128 col1 = _mm_loadu_ps(&a.fa[4]);
      __m128 col2 = _mm_loadu_ps(&a.fa[8]);
      __m128 col3 = _mm_loadu_ps(&a.fa[12]);

      // Unpack into scalar floats for fully unrolled computation
      float m[16];
      _mm_storeu_ps(&m[0], col0);
      _mm_storeu_ps(&m[4], col1);
      _mm_storeu_ps(&m[8], col2);
      _mm_storeu_ps(&m[12], col3);

      float_matrix4 inv;

      // Fully unrolled cofactor computation (column-major)
      inv.fa[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                 m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
      inv.fa[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                 m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
      inv.fa[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                 m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
      inv.fa[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

      inv.fa[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                 m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
      inv.fa[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                 m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
      inv.fa[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                 m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
      inv.fa[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

      inv.fa[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                 m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
      inv.fa[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                 m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
      inv.fa[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                  m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
      inv.fa[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

      inv.fa[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                  m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
      inv.fa[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                  m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
      inv.fa[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                  m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
      inv.fa[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

      // Compute determinant
      float det = m[0] * inv.fa[0] + m[1] * inv.fa[4] + m[2] * inv.fa[8] + m[3] * inv.fa[12];
      float invDet = 1.0f / det;

      // Multiply all elements by 1/det using SSE
      __m128 v0 = _mm_loadu_ps(&inv.fa[0]);
      __m128 v1 = _mm_loadu_ps(&inv.fa[4]);
      __m128 v2 = _mm_loadu_ps(&inv.fa[8]);
      __m128 v3 = _mm_loadu_ps(&inv.fa[12]);
      __m128 det128 = _mm_set1_ps(invDet);

      _mm_storeu_ps(&inv.fa[0], _mm_mul_ps(v0, det128));
      _mm_storeu_ps(&inv.fa[4], _mm_mul_ps(v1, det128));
      _mm_storeu_ps(&inv.fa[8], _mm_mul_ps(v2, det128));
      _mm_storeu_ps(&inv.fa[12], _mm_mul_ps(v3, det128));

      return inv;
   }

   inline float_matrix4 inverse_avx(const float_matrix4 &a)
   {
      // Load columns into AVX registers (2 columns per 256-bit register)
      __m256 col01 = _mm256_loadu_ps(&a.fa[0]); // columns 0 & 1
      __m256 col23 = _mm256_loadu_ps(&a.fa[8]); // columns 2 & 3

      // Unpack into scalar floats for full unrolled computation
      float m[16];
      _mm256_storeu_ps(&m[0], col01);
      _mm256_storeu_ps(&m[8], col23);

      float_matrix4 inv;

      // Fully unrolled cofactor computation (column-major)
      inv.fa[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                 m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
      inv.fa[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                 m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
      inv.fa[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                 m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
      inv.fa[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

      inv.fa[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                 m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
      inv.fa[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                 m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
      inv.fa[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                 m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
      inv.fa[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

      inv.fa[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                 m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
      inv.fa[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                 m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
      inv.fa[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                  m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
      inv.fa[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

      inv.fa[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                  m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
      inv.fa[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                  m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
      inv.fa[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                  m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
      inv.fa[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

      // Determinant
      float det = m[0] * inv.fa[0] + m[1] * inv.fa[4] + m[2] * inv.fa[8] + m[3] * inv.fa[12];
      float invDet = 1.0f / det;

      // Multiply all 16 elements by 1/det using AVX
      __m256 v0 = _mm256_loadu_ps(&inv.fa[0]);
      __m256 v1 = _mm256_loadu_ps(&inv.fa[8]);
      __m256 invDet256 = _mm256_set1_ps(invDet);
      _mm256_storeu_ps(&inv.fa[0], _mm256_mul_ps(v0, invDet256));
      _mm256_storeu_ps(&inv.fa[8], _mm256_mul_ps(v1, invDet256));

      return inv;
   }


   inline float_matrix4 inverse_avx2(const float_matrix4 &a)
   {
      // Load all 16 elements
      __m256 col01 = _mm256_loadu_ps(&a.fa[0]); // columns 0 & 1
      __m256 col23 = _mm256_loadu_ps(&a.fa[8]); // columns 2 & 3

      // Unpack columns into rows for computation
      __m128 r0 = _mm256_castps256_ps128(col01); // col0 low
      __m128 r1 = _mm256_extractf128_ps(col01, 1); // col1 low
      __m128 r2 = _mm256_castps256_ps128(col23); // col2 low
      __m128 r3 = _mm256_extractf128_ps(col23, 1); // col3 low

      // Compute pairs for cofactors (fully unrolled)
      float m[16];
      _mm_storeu_ps(&m[0], r0);
      _mm_storeu_ps(&m[4], r1);
      _mm_storeu_ps(&m[8], r2);
      _mm_storeu_ps(&m[12], r3);

      float_matrix4 inv;

      // Fully unrolled cofactor computation (column-major)
      inv.fa[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                 m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
      inv.fa[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                 m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
      inv.fa[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                 m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
      inv.fa[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

      inv.fa[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                 m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
      inv.fa[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                 m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
      inv.fa[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                 m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
      inv.fa[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

      inv.fa[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                 m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
      inv.fa[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                 m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
      inv.fa[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                  m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
      inv.fa[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

      inv.fa[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                  m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
      inv.fa[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                  m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
      inv.fa[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                  m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
      inv.fa[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

      // Compute determinant
      float det = m[0] * inv.fa[0] + m[1] * inv.fa[4] + m[2] * inv.fa[8] + m[3] * inv.fa[12];
      float invDet = 1.0f / det;

      // Scale all elements by 1/det using AVX2
      __m256 v0 = _mm256_loadu_ps(&inv.fa[0]);
      __m256 v1 = _mm256_loadu_ps(&inv.fa[8]);
      __m256 invDet256 = _mm256_set1_ps(invDet);
      _mm256_storeu_ps(&inv.fa[0], _mm256_mul_ps(v0, invDet256));
      _mm256_storeu_ps(&inv.fa[8], _mm256_mul_ps(v1, invDet256));

      return inv;
   }


   inline float_matrix4 inverse(const float_matrix4 &m)
   {
      
      if (g_ecpu & e_cpu_avx2)
            return inverse_avx2(m);
      else if (g_ecpu &  e_cpu_avx)
            return inverse_avx(m);
      else if (g_ecpu &  e_cpu_sse)
            return inverse_sse(m);
      else
         return inverse_scalar(m);

   }


      // Multiply 4x4 matrix `a` by 4x4 matrix `b` (a*b) using AVX2 fully unrolled
   inline float_matrix4 mul_avx2(const float_matrix4 &a, const float_matrix4 &b)
   {
      float_matrix4 result;

      // Load columns of B
      __m128 b0 = _mm_loadu_ps(&b.fa[0]);
      __m128 b1 = _mm_loadu_ps(&b.fa[4]);
      __m128 b2 = _mm_loadu_ps(&b.fa[8]);
      __m128 b3 = _mm_loadu_ps(&b.fa[12]);

      // For each column of B, broadcast each element and multiply-add with columns of A
      for (int col = 0; col < 4; ++col)
      {
         __m128 bc; // broadcast column element
         __m256 sum01, sum23;

         switch (col)
         {
            case 0:
               bc = b0;
               break;
            case 1:
               bc = b1;
               break;
            case 2:
               bc = b2;
               break;
            case 3:
               bc = b3;
               break;
         }

         // Broadcast each element of the column
         __m256 b0_256 = _mm256_broadcast_ps((__m128 *)&bc); // replicate column
         // Load A columns
         __m256 a01 = _mm256_loadu_ps(&a.fa[0]); // columns 0 & 1
         __m256 a23 = _mm256_loadu_ps(&a.fa[8]); // columns 2 & 3

         // Multiply and sum
         sum01 = _mm256_mul_ps(a01, b0_256); // element-wise multiply
         sum23 = _mm256_mul_ps(a23, b0_256);

         // Add results
         __m256 result256_0 = _mm256_add_ps(sum01, sum23);

         // Store back
         _mm256_storeu_ps(&result.fa[0], result256_0); // fully unrolled: can expand by column
      }

      return result;
   }


} // namespace geometry








//
//
//    // Load all elements into scalar array for cofactor calculation
//float m[16];
//_mm256_storeu_ps(&m[0], _mm256_loadu_ps(&a.fa[0])); // first 8 elements
//_mm256_storeu_ps(&m[8], _mm256_loadu_ps(&a.fa[8])); // last 8 elements
//
//// Fully unrolled cofactor computation
//inv.fa[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
//           m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
//inv.fa[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
//           m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
//inv.fa[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] -
//           m[13] * m[3] * m[6];
//inv.fa[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] +
//           m[9] * m[3] * m[6];
//
//inv.fa[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
//           m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
//inv.fa[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
//           m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
//inv.fa[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
//           m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
//inv.fa[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] -
//           m[8] * m[3] * m[6];
//
//inv.fa[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
//           m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
//inv.fa[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
//           m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
//inv.fa[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
//            m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
//inv.fa[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] +
//            m[8] * m[3] * m[5];
//
//inv.fa[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
//            m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
//inv.fa[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
//            m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
//inv.fa[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
//            m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
//inv.fa[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] -
//            m[8] * m[2] * m[5];
//
//// Compute determinant scalar
//float det = m[0] * inv.fa[0] + m[1] * inv.fa[4] + m[2] * inv.fa[8] + m[3] * inv.fa[12];
//float invDet = 1.0f / det;
//
//// Scale all elements using AVX2
//__m256 v0 = _mm256_loadu_ps(&inv.fa[0]);
//__m256 v1 = _mm256_loadu_ps(&inv.fa[8]);
//__m256 det256 = _mm256_set1_ps(invDet);
//
//_mm256_storeu_ps(&inv.fa[0], _mm256_mul_ps(v0, det256));
//_mm256_storeu_ps(&inv.fa[8], _mm256_mul_ps(v1, det256));
