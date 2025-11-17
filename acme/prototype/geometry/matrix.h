// From sequence.h by camilo on 2025-07-30 20:59 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/geometry/quaternion.h"
#include "acme/prototype/geometry/sequence.h"
#include "acme/prototype/geometry2d/angle.h"

template<primitive_floating FLOATING_TYPE, int t_iDimension>
struct matrix_type;



#include <immintrin.h>
#include <xmmintrin.h>
#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
#include <emmintrin.h>
#endif

#include "acme/operating_system/cpu_features.h"


//CLASS_DECL_ACME extern int g_iCpuFeatures; // 0=scalar,1=SSE,2=AVX,3=AVX2



namespace geometry
{


   template<primitive_floating FLOATING, int t_iDimension>
   inline void _transpose(FLOATING(& A_target)[t_iDimension][t_iDimension],
                                 const FLOATING(& A_source)[t_iDimension][t_iDimension])
   {
      for (int i = 0; i < t_iDimension; i++)
         for (int j = 0; j < t_iDimension; j++)
            A_target[i][j] = A_source[j][i];
   }


} // namespace geometry





/// Simple matrix class with row-major storage
template<primitive_floating FLOATING_TYPE, int t_iDimension>
struct row_major_type
{

   using FLOATING = FLOATING_TYPE;
   static constexpr int DIMENSION = t_iDimension;


   union
   {
      FLOATING m[DIMENSION][DIMENSION];
      sequence_type<FLOATING, DIMENSION> m_sequencea[DIMENSION];
   };

   matrix_type<FLOATING, t_iDimension> transpose() const;
   
};

struct translation_t
{
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
   static constexpr int SQUARED_DIMENSION = DIMENSION * DIMENSION;

   union
   {

      
      column columna[DIMENSION];
      FLOATING m[DIMENSION][DIMENSION];
      FLOATING fa[SQUARED_DIMENSION]; // floating number array

   };


   constexpr matrix_type() {}


   constexpr matrix_type(const matrix_type<FLOATING, 4> &m)
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

  
   constexpr matrix_type(const matrix_type<FLOATING, 4> &m)
      requires(DIMENSION == 4)
   {
      
      for (int i = 0; i < SQUARED_DIMENSION; i++) this->fa[i] = m.fa[i];

   }


   /// expects p to point to an array of at least SQUARED_DIMENSION elements
   /// in column-major order
   template<primitive_floating FLOATING1>
   matrix_type(const FLOATING1 *p) 
      requires(DIMENSION == 4)
   {

      auto c = SQUARED_DIMENSION;

      for (int i = 0; i < c; ++i) this->fa[i] = (FLOATING)p[i];
      
   }


   constexpr matrix_type(const matrix_type<FLOATING, 3> & m)
      requires(DIMENSION == 4)
       : matrix_type((FLOATING)1)
   {
      //// Initialize as identity
      //*this = floating_matrix4(1.0f);

      // Copy the 3×3 into the upper-left of the 4×4
      // (column-major order)
      for (int c = 0; c < 3; ++c)
         for (int r = 0; r < 3; ++r)
            this->m[c][r] = m.m[c][r];
   }


   template < primitive_number NUMBER >
   constexpr matrix_type(NUMBER diagonal) 
   {

      for (int i = 0; i < DIMENSION; ++i)
         for (int j = 0; i < DIMENSION; ++i)
            m[i][j] = i == j ? (FLOATING) diagonal : (FLOATING) 0;

   }

   matrix_type(const quaternion_type<FLOATING> & q)
      requires(DIMENSION == 4)
   {

      this->operator=(q);

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
   //   for (int i = 0; i < DIMENSION; ++i) {
   //      for (int j = 0; j < DIMENSION; ++j) {
   //         FLOATING accum = 0;
   //         for (int k = 0; k < DIMENSION; ++k)
   //            accum += a.m[k][i] * b.m[j][k];
   //         c.m[j][i] = accum;
   //      }
   //   }
   //   return c;
   //}



   // -------------------- Scalar fallback --------------------
   
   inline sequence_type<FLOATING, 4> mul_scalar(const sequence_type<FLOATING, 4> &s) const
      requires(DIMENSION == 4)
   {
      const auto &M = *this;
      sequence_type<FLOATING, 4> r;
      r.x = M.fa[0] * s.x + M.fa[4] * s.y + M.fa[8] * s.z + M.fa[12] * s.w;
      r.y = M.fa[1] * s.x + M.fa[5] * s.y + M.fa[9] * s.z + M.fa[13] * s.w;
      r.z = M.fa[2] * s.x + M.fa[6] * s.y + M.fa[10] * s.z + M.fa[14] * s.w;
      r.w = M.fa[3] * s.x + M.fa[7] * s.y + M.fa[11] * s.z + M.fa[15] * s.w;
      return r;
   }

   // -------------------- SSE 128-bit version --------------------
   inline float_sequence4 mul_sse(const float_sequence4 &s) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m128 vx = _mm_set_ps(s.w, s.z, s.y, s.x); // [w z y x]
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
   inline float_sequence4 mul_avx(const float_sequence4 &s) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m256 vx = _mm256_setr_m128(_mm_set1_ps(s.x), _mm_set1_ps(s.y));
      __m256 vy = _mm256_setr_m128(_mm_set1_ps(s.z), _mm_set1_ps(s.w));

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
   inline float_sequence4 mul_avx2(const float_sequence4 &s) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      const auto &M = *this;
      __m256 vx = _mm256_set1_ps(s.x);
      __m256 vy = _mm256_set1_ps(s.y);
      __m256 vz = _mm256_set1_ps(s.z);
      __m256 vw = _mm256_set1_ps(s.w);

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
   //inline float_sequence4 mul_avx2( const float_sequence4 &s)
   //   requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   //{
   //   const auto &M = *this;
   //   // Load vector s into low 128 bits: [x y z w]
   //   __m128 xv = _mm_set_ps(s.w, s.z, s.y, s.x);

   //   // Broadcast vector components into AVX registers
   //   __m256 bx = _mm256_broadcast_ss(&s.x);
   //   __m256 by = _mm256_broadcast_ss(&s.y);
   //   __m256 bz = _mm256_broadcast_ss(&s.z);
   //   __m256 bw = _mm256_broadcast_ss(&s.w);

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

   inline float_sequence4 operator *(const float_sequence4 &s) const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {
      if (g_cpufeatures.m_bAVX2)
         return mul_avx2(s);
      else if (g_cpufeatures.m_bAVX)
         return mul_avx(s);
      else if (g_cpufeatures.m_bSSE)
         return mul_sse(s);
      else
         return mul_scalar(s);
   }

   
   inline sequence_type<FLOATING, 3> operator*(const sequence_type<FLOATING, 3> &v) const
      requires(DIMENSION == 3)
   {

      const auto &M = *this;
      sequence_type<FLOATING, 3> result;

      // Column-major OpenGL multiplication: result = M * v
      result.x = M[0][0] * v.x + M[1][0] * v.y + M[2][0] * v.z;
      result.y = M[0][1] * v.x + M[1][1] * v.y + M[2][1] * v.z;
      result.z = M[0][2] * v.x + M[1][2] * v.y + M[2][2] * v.z;

      return result;
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
      if (g_cpufeatures.m_bAVX2)
         return mul_avx2(m);
      else if (g_cpufeatures.m_bAVX)
         return mul_avx(m);
      else if (g_cpufeatures.m_bSSE)
         return mul_sse(m);
      else
         return mul_scalar(m);
   }



   // ------------------------------
   // Translation
   // ------------------------------
   static matrix_type translation(const sequence_type<FLOATING, DIMENSION - 1> &t) 
   {

      matrix_type m{(FLOATING)1};

      auto c = DIMENSION - 1;

      for (int i = 0; i < c; ++i) 
         m[c][i] = t[i];

      return m;

   }


   // ------------------------------
   // Scaling
   // ------------------------------
   static matrix_type scaling(const sequence_type<FLOATING, DIMENSION - 1>& s) 
   {

      matrix_type result{1.0f};

      auto c = DIMENSION - 1;

      for (int i = 0; i < c; ++i)
         result.m[i][i] = s[i];

      return result;

   }


   // ------------------------------
   // Translation
   // ------------------------------
   static matrix_type rotation(const quaternion_type<FLOATING> &q)
   {

      matrix_type m;

      m = q;

      return m;

   }


   //static matrix_type scale(const sequence_type<FLOATING, DIMENSION>& m_coordinatea) {
   //   matrix_type result;
   //   ::memory_set(result.m, 0, sizeof(FLOATING) * SQUARED_DIMENSION);
   //   for (int i = 0; i < DIMENSION; ++i)
   //      result.m[i][i] = m_coordinatea[i];
   //   return result;
   //}

   //static matrix_type translate(const sequence_type<FLOATING, DIMENSION - 1>& m_coordinatea) {
   //   matrix_type result;
   //   ::memory_set(result.m, 0, sizeof(FLOATING) * SQUARED_DIMENSION);
   //   for (int i = 0; i < DIMENSION; ++i) {
   //      result.m[i][i] = 1.f;
   //      if (i < DIMENSION - 1)
   //         result.m[DIMENSION - 1][i] = m_coordinatea[i];
   //   }
   //   return result;
   //}

   const column & operator[](int i) const
   {

      return columna[i];
   }

   column & operator[](int i) { return columna[i]; }


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


   template <int S = DIMENSION, std::enable_if_t<S == 4, int> = 0>
   static matrix_type perspective(FLOATING fov, FLOATING near_, FLOATING far_, FLOATING aspect = 1.f)
   {

      FLOATING recip = 1 / (near_ - far_);
      FLOATING c = 1 / ::tan(.5f * fov);

      matrix_type trafo = matrix_type::scale(sequence_type<FLOATING, DIMENSION>(c / aspect, c, (near_ + far_) * recip, 0.f));

      trafo.m[3][2] = 2.f * near_ * far_ * recip;
      trafo.m[2][3] = -1.f;

      return trafo;
   }

   template <int S = DIMENSION, std::enable_if_t<S == 4, int> = 0>
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


   static matrix_type look_at(const sequence_type<FLOATING, 3>& origin,
      const sequence_type<FLOATING, 3>& target,
      const sequence_type<FLOATING, 3>& up)
      requires(DIMENSION == 4)   
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


   //inline sequence_type<FLOATING, 4> mul_scalar(const sequence_type<FLOATING, 4> &s) const
   //   requires(DIMENSION == 4)
   //{
   //   sequence_type<FLOATING, 4> r;

   //   r.x = this->m[0][0] * s.x + this->m[0][1] * s.y + this->m[0][2] * s.z + this->m[0][3] * s.w;
   //   r.y = this->m[1][0] * s.x + this->m[1][1] * s.y + this->m[1][2] * s.z + this->m[1][3] * s.w;
   //   r.z = this->m[2][0] * s.x + this->m[2][1] * s.y + this->m[2][2] * s.z + this->m[2][3] * s.w;
   //   r.w = this->m[3][0] * s.x + this->m[3][1] * s.y + this->m[3][2] * s.z + this->m[3][3] * s.w;

   //   return r;
   //}

   inline sequence_type<FLOATING, 3> operator*(const sequence_type<FLOATING, 3> &s) const
      requires(DIMENSION == 4)
   {
      auto t = this->operator *( sequence_type<FLOATING, 4>(s, (FLOATING) 1));
      return t;
   }


   matrix_type rotated(angle_type<FLOATING> angleRadians,
                                     const sequence_type<FLOATING, 3> &axis) const
      requires(DIMENSION == 4)
   {

      const auto &m = *this;
      auto a = axis.normalized();
      auto c = angleRadians.cos();
      auto s = angleRadians.sin();
      auto t = 1.0f - c;

      // Build the rotation matrix (Rodrigues' rotation formula)
      matrix_type rot(1.0f);
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


   matrix_type & rotate(angle_type<FLOATING> angleRadians, const sequence_type<FLOATING, 3> & axis)
   {

      return *this = this->rotated(angleRadians, axis);

   }

   
   //matrix_type transposed() const
   //   requires(DIMENSION == 3)
   //{
   //   auto &m = *this;
   //   matrix_type r;
   //   r[0][0] = m[0][0];
   //   r[0][1] = m[1][0];
   //   r[0][2] = m[2][0];

   //   r[1][0] = m[0][1];
   //   r[1][1] = m[1][1];
   //   r[1][2] = m[2][1];

   //   r[2][0] = m[0][2];
   //   r[2][1] = m[1][2];
   //   r[2][2] = m[2][2];
   //   return r;
   //}

      
   matrix_type transposed() const
      //requires(DIMENSION == 4)
   {
      auto &m = *this;
      matrix_type r;
      ::geometry::_transpose(r.m, m.m);
      return r;
   }


   //matrix_type & transpose()
   //   requires(DIMENSION == 3)
   //{
   //   return *this = this->transposed();
   //}


   matrix_type & translate(const sequence_type<FLOATING, 3> &s) 
      requires(DIMENSION == 4)   
   {

      this->m[3][0] += s.x;
      this->m[3][1] += s.y;
      this->m[3][2] += s.z;

      return *this;
   }

   matrix_type translated(const sequence_type<FLOATING, 3> &s) const
      requires(DIMENSION == 4)
   {

      auto m = *this;

      return m.translate(s);
   }

   
   matrix_type & scale( const sequence_type<FLOATING, 3> &s)
      requires(DIMENSION == 4)   
   {
      this->m[0][0] *= s.x;
      this->m[1][0] *= s.x;
      this->m[2][0] *= s.x;
      this->m[3][0] *= s.x;

      this->m[0][1] *= s.y;
      this->m[1][1] *= s.y;
      this->m[2][1] *= s.y;
      this->m[3][1] *= s.y;

      this->m[0][2] *= s.z;
      this->m[1][2] *= s.z;
      this->m[2][2] *= s.z;
      this->m[3][2] *= s.z;

      return *this;
   }

   
   matrix_type scaled(const sequence_type<FLOATING, 3> &s) const
      requires(DIMENSION == 4)
   {

      auto m = *this;

      return m.scale(s);
   }

   inline matrix_type inversed_scalar() const
      requires(DIMENSION == 3)
   {

      const auto &A = *this;
      // Column-major indexing:
      // A.m[0] A.m[3] A.m[6]
      // A.m[1] A.m[4] A.m[7]
      // A.m[2] A.m[5] A.m[8]

      float a00 = A.fa[0];
      float a01 = A.fa[3];
      float a02 = A.fa[6];
      float a10 = A.fa[1];
      float a11 = A.fa[4];
      float a12 = A.fa[7];
      float a20 = A.fa[2];
      float a21 = A.fa[5];
      float a22 = A.fa[8];

      // Cofactors
      float c00 = (a11 * a22 - a12 * a21);
      float c01 = -(a10 * a22 - a12 * a20);
      float c02 = (a10 * a21 - a11 * a20);

      float c10 = -(a01 * a22 - a02 * a21);
      float c11 = (a00 * a22 - a02 * a20);
      float c12 = -(a00 * a21 - a01 * a20);

      float c20 = (a01 * a12 - a02 * a11);
      float c21 = -(a00 * a12 - a02 * a10);
      float c22 = (a00 * a11 - a01 * a10);

      // Determinant
      float det = a00 * c00 + a01 * c01 + a02 * c02;

      matrix_type out;

      if (fabs(det) < 1e-12f)
      {
         // Return identity or zero? Your choice
         // Here: return identity
         out.fa[0] = 1;
         out.fa[3] = 0;
         out.fa[6] = 0;
         out.fa[1] = 0;
         out.fa[4] = 1;
         out.fa[7] = 0;
         out.fa[2] = 0;
         out.fa[5] = 0;
         out.fa[8] = 1;
         return out;
      }

      float invDet = 1.0f / det;

      // The adjugate is the transpose of the cofactor matrix
      // Write it directly in column-major:

      out.fa[0] = c00 * invDet;
      out.fa[1] = c10 * invDet;
      out.fa[2] = c20 * invDet;

      out.fa[3] = c01 * invDet;
      out.fa[4] = c11 * invDet;
      out.fa[5] = c21 * invDet;

      out.fa[6] = c02 * invDet;
      out.fa[7] = c12 * invDet;
      out.fa[8] = c22 * invDet;

      return out;
   }


   inline matrix_type inversed_sse() const
      requires(DIMENSION == 3 && std::is_same_v<FLOATING, float>)
   {

      const auto &A = *this;
      // Load columns (pad with 0 in 4th float)
      __m128 c0 = _mm_set_ps(0.0f, A.fa[2], A.fa[1], A.fa[0]);
      __m128 c1 = _mm_set_ps(0.0f, A.fa[5], A.fa[4], A.fa[3]);
      __m128 c2 = _mm_set_ps(0.0f, A.fa[8], A.fa[7], A.fa[6]);

      // Unpack to rows
      __m128 r0 = _mm_unpacklo_ps(c0, c1); // [a00 a01 a10 a11]
      __m128 r1 = _mm_unpackhi_ps(c0, c1); // [a20 a21  0    0]
      __m128 r2 = c2; // [a02 a12 a22  0]

      // Cofactor calculations:
      // c00 = a11*a22 - a12*a21
      __m128 t0 = _mm_mul_ps(_mm_shuffle_ps(r0, r0, _MM_SHUFFLE(3, 3, 1, 1)),
                             _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 3, 3, 0))); // a11 * a22

      __m128 t1 = _mm_mul_ps(_mm_shuffle_ps(r0, r0, _MM_SHUFFLE(3, 3, 1, 1)),
                             _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 3, 0, 0))); // a12 * a21

      __m128 cof0 = _mm_sub_ps(t0, t1);

      // We will extract elements later.
      float c00 = _mm_cvtss_f32(cof0);

      // Scalar fallback for the remaining cofactors (SSE only helps partially for 3×3)
      // (This keeps correctness while still accelerating the heavy parts.)

      float a00 = A.fa[0], a01 = A.fa[3], a02 = A.fa[6];
      float a10 = A.fa[1], a11 = A.fa[4], a12 = A.fa[7];
      float a20 = A.fa[2], a21 = A.fa[5], a22 = A.fa[8];

      float c01 = -(a10 * a22 - a12 * a20);
      float c02 = (a10 * a21 - a11 * a20);
      float c10 = -(a01 * a22 - a02 * a21);
      float c11 = (a00 * a22 - a02 * a20);
      float c12 = -(a00 * a21 - a01 * a20);
      float c20 = (a01 * a12 - a02 * a11);
      float c21 = -(a00 * a12 - a02 * a10);
      float c22 = (a00 * a11 - a01 * a10);

      float det = a00 * c00 + a01 * c01 + a02 * c02;

      matrix_type out;

      if (fabs(det) < 1e-12f)
      {
         // return identity
         //out = {1, 0, 0, 0, 1, 0, 0, 0, 1};
         return {1.0f};
      }

      float invDet = 1.0f / det;

      // Store adjugate * invDet (column-major)
      out.fa[0] = c00 * invDet;
      out.fa[1] = c10 * invDet;
      out.fa[2] = c20 * invDet;

      out.fa[3] = c01 * invDet;
      out.fa[4] = c11 * invDet;
      out.fa[5] = c21 * invDet;

      out.fa[6] = c02 * invDet;
      out.fa[7] = c12 * invDet;
      out.fa[8] = c22 * invDet;

      return out;
   }


   inline matrix_type inversed_avx() const
      requires(DIMENSION == 3 && std::is_same_v<FLOATING, float>)
   {

      const float *in = this->fa;
      matrix_type result;
      float *out = result.fa;
         // Load 3×3 matrix (column-major)
         float m00 = in[0], m01 = in[3], m02 = in[6];
         float m10 = in[1], m11 = in[4], m12 = in[7];
         float m20 = in[2], m21 = in[5], m22 = in[8];

         //
         // ---- Cofactor matrix (scalar – fastest for 3×3) ----
         //
         float cf00 = m11 * m22 - m12 * m21;
         float cf01 = -(m10 * m22 - m12 * m20);
         float cf02 = m10 * m21 - m11 * m20;

         float cf10 = -(m01 * m22 - m02 * m21);
         float cf11 = m00 * m22 - m02 * m20;
         float cf12 = -(m00 * m21 - m01 * m20);

         float cf20 = m01 * m12 - m02 * m11;
         float cf21 = -(m00 * m12 - m02 * m10);
         float cf22 = m00 * m11 - m01 * m10;

         // Determinant
         float det = m00 * cf00 + m01 * cf01 + m02 * cf02;
         float invdet = 1.0f / det;

         //
         // ---- Pack cofactors into column-major adjoint matrix ----
         //
         // adj = transpose(cofactor matrix)
         alignas(32) float adj[9] = {
            cf00, cf10, cf20, // column 0
            cf01, cf11, cf21, // column 1
            cf02, cf12, cf22 // column 2
         };

         //
         // ---- AVX multiply first 8 floats ----
         //
         __m256 scale = _mm256_set1_ps(invdet);
         __m256 adj_lo = _mm256_loadu_ps(&adj[0]); // adj[0..7]
         __m256 out_lo = _mm256_mul_ps(adj_lo, scale);

         //
         // ---- Last element adj[8] ----
         //
         __m128 last = _mm_mul_ss(_mm_set_ss(adj[8]), _mm256_castps256_ps128(scale));

         //
         // ---- Store result ----
         //
         _mm256_storeu_ps(&out[0], out_lo);
         _mm_store_ss(&out[8], last);
         return result;
   }


   
   
   // ---------------- Scalar inverse ----------------
   inline matrix_type inversed_scalar() const
      requires(DIMENSION == 4)
   {

      const auto &a = *this;
      matrix_type result;
      auto inv = result.fa;
      auto m = a.fa;

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


   inline matrix_type inversed_sse() const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {

      const auto &a = *this;
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

      matrix_type inv;

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

   inline matrix_type inversed_avx() const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {

      const auto &a = *this;
      // Load columns into AVX registers (2 columns per 256-bit register)
      __m256 col01 = _mm256_loadu_ps(&a.fa[0]); // columns 0 & 1
      __m256 col23 = _mm256_loadu_ps(&a.fa[8]); // columns 2 & 3

      // Unpack into scalar floats for full unrolled computation
      float m[16];
      _mm256_storeu_ps(&m[0], col01);
      _mm256_storeu_ps(&m[8], col23);

      matrix_type inv;

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


   inline matrix_type inversed_avx2() const
      requires(DIMENSION == 4 && std::is_same_v<FLOATING, float>)
   {

      const auto &a = *this;
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

      matrix_type inv;

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


   inline matrix_type inversed() const
   {

      if constexpr ( std::is_same_v<FLOATING, float>)
      {
         if constexpr (DIMENSION == 4)
         {
            if (g_cpufeatures.m_bAVX2)
               return inversed_avx2();
            else if (g_cpufeatures.m_bAVX)
               return inversed_avx();
            else if (g_cpufeatures.m_bSSE)
               return inversed_sse();
            else
               return inversed_scalar();
         }
         else if constexpr (DIMENSION == 3)
         {
            if (g_cpufeatures.m_bAVX)
               return inversed_avx();
            if (g_cpufeatures.m_bSSE) 
               return inversed_sse();
            else
               return inversed_scalar();
         }
         else
         {
            return inversed_scalar();
         }

      }
      else
      {
         return inversed_scalar();
      }

   }


   inline matrix_type & operator =(const quaternion_type<FLOATING> &q)
      requires (DIMENSION == 4)
   {
      auto & M = *this;

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

      return *this;
   }


   static inline matrix_type from(const quaternion_type<FLOATING> &q)
      requires(DIMENSION == 4)
   {

      return q;

   }


   
   inline row_major_type<FLOATING, t_iDimension> transpose() const
   {
      row_major_type<FLOATING, 4> r;
      _transpose(4, this->m);
      return r;
   }
};


using float_matrix2 = matrix_type<float, 2>;
using float_matrix3 = matrix_type<float, 3>;
using float_matrix4 = matrix_type<float, 4>;


using double_matrix2 = matrix_type<double, 2>;
using double_matrix3 = matrix_type<double, 3>;
using double_matrix4 = matrix_type<double, 4>;

//
//namespace geometry
//{
//
//
//   //   static inline void _transpose(FLOATING A_target[t_iDimension][t_iDimension],
//   //                              const FLOATING A_source[t_iDimension][t_iDimension])
//   //{
//   //   for (int i = 0; i < t_iDimension; i++)
//   //      for (int j = 0; j < t_iDimension; j++)
//   //         A_target[i][j] = A_source[j][i];
//   //}
//   //
//
//   ////template<primitive_floating FLOATING>
//   ////row_major_type<FLOATING, 4> transpose(const matrix_type<FLOATING, 4> &m)
//   ////{
//   ////   row_major_type<FLOATING, 4> r;
//   ////   _transpose(4, m.m);
//   ////   return r;
//   ////}
//
//
//   ////template<primitive_floating FLOATING>
//   //////matrix_type<FLOATING, 3> inverse(const matrix_type<FLOATING, 3> &m)
//   //////{
//
//   //////   float det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
//   //////               m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
//
//   //////   if (std::fabs(det) < 1e-8f)
//   //////      return matrix_type<FLOATING, 3>(1.0f); // fallback to identity (non-invertible)
//
//   //////   float invDet = 1.0f / det;
//
//   //////   matrix_type<FLOATING, 3> r;
//   //////   r[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet;
//   //////   r[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet;
//   //////   r[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;
//
//   //////   r[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet;
//   //////   r[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet;
//   //////   r[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet;
//
//   //////   r[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet;
//   //////   r[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet;
//   //////   r[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;
//
//   //////   return r;
//   //////}
//
//   //
//
//
//   //template<primitive_floating FLOATING>
//   //quaternion_type < FLOATING > quaternion(const ::sequence_type<FLOATING, 3> & euler)
//   //{
//
//   //   return euler;
//
//   //}
//
//   //template<primitive_floating FLOATING>
//   //inline matrix_type<FLOATING, 4> inverse(const matrix_type<FLOATING, 4> &A)
//   //{
//   //   matrix_type<FLOATING, 4> inv{};
//   //   const FLOATING *m = &A.fa[0][0]; // treat as flat array
//
//   //   FLOATING invOut[16];
//
//   //   invOut[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
//   //               m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
//
//   //   invOut[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
//   //               m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
//
//   //   invOut[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
//   //               m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
//
//   //   invOut[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
//   //                m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
//
//   //   invOut[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
//   //               m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
//
//   //   invOut[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
//   //               m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
//
//   //   invOut[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
//   //               m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
//
//   //   invOut[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
//   //                m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
//
//   //   invOut[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
//   //               m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
//
//   //   invOut[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
//   //               m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
//
//   //   invOut[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
//   //                m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
//
//   //   invOut[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
//   //                m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
//
//   //   invOut[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
//   //               m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
//
//   //   invOut[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
//   //               m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
//
//   //   invOut[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
//   //                m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
//
//   //   invOut[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
//   //                m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
//
//   //   float det = m[0] * invOut[0] + m[1] * invOut[4] + m[2] * invOut[8] + m[3] * invOut[12];
//
//   //   // Determinant zero → not invertible
//   //   if (det == 0.0f)
//   //      return {}; // or assert / return identity
//
//   //   float invDet = 1.0f / det;
//
//   //   matrix_type<FLOATING, 4> R{};
//   //   for (int i = 0; i < 16; i++)
//   //      ((float *)R.m)[i] = invOut[i] * invDet;
//
//   //   return R;
//   //}
//
//
//   //template<primitive_floating FLOATING_TYPE>
//   //inline row_major_type<FLOATING_TYPE, 4> inverse(const row_major_type<FLOATING_TYPE, 4> &M)
//   //{
//   //   auto T = transpose(M);
//   //   auto C = inverse(T);
//   //   return transpose(C);
//   //}
//   //// --- Fast affine inverse (rotation + translation only) --------------------
//   //template<primitive_floating FLOATING>
//   //inline matrix_type<FLOATING, 4> inverse_affine(const matrix_type<FLOATING, 4> &A)
//   //{
//   //   // assumes bottom row is [0 0 0 1] (i.e. affine matrix)
//   //   // and upper-left 3x3 is orthonormal (rotation + uniform scale = 1)
//   //   matrix_type<FLOATING, 4> R;
//   //   // transpose the 3x3 rotation
//   //   for (int c = 0; c < 3; ++c)
//   //      for (int r = 0; r < 3; ++r)
//   //         R.m[c][r] = A.m[r][c];
//
//   //   // compute -R^T * translation
//   //   float tx = A.m[3][0], ty = A.m[3][1], tz = A.m[3][2];
//   //   R.m[3][0] = -(R.m[0][0] * tx + R.m[1][0] * ty + R.m[2][0] * tz);
//   //   R.m[3][1] = -(R.m[0][1] * tx + R.m[1][1] * ty + R.m[2][1] * tz);
//   //   R.m[3][2] = -(R.m[0][2] * tx + R.m[1][2] * ty + R.m[2][2] * tz);
//
//   //   // last column/row
//   //   R.m[0][3] = R.m[1][3] = R.m[2][3] = 0.0f;
//   //   R.m[3][3] = 1.0f;
//
//   //   return R;
//   //}
//
//
//   //inline float_matrix4 inverse_col_major_simd(const float_matrix4 &A)
//   //{
//   //   const __m128 row0 = _mm_loadu_ps(&A.m[0][0]);
//   //   const __m128 row1 = _mm_loadu_ps(&A.m[1][0]);
//   //   const __m128 row2 = _mm_loadu_ps(&A.m[2][0]);
//   //   const __m128 row3 = _mm_loadu_ps(&A.m[3][0]);
//
//   //   // Compute cofactors
//   //   __m128 tmp1, tmp2, tmp3, minor0, minor1, minor2, minor3;
//
//   //   tmp1 = _mm_mul_ps(row2, row3);
//   //   tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(1, 0, 3, 2));
//
//   //   tmp2 = _mm_mul_ps(row1, tmp1);
//   //   tmp3 = _mm_mul_ps(row0, tmp1);
//
//   //   tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1));
//
//   //   tmp2 = _mm_sub_ps(tmp2, _mm_mul_ps(row1, tmp1));
//   //   tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(row0, tmp1));
//
//   //   minor0 = tmp2;
//   //   minor1 = tmp3;
//
//   //   // Continue building cofactor matrix
//   //   tmp1 = _mm_mul_ps(row1, row2);
//   //   tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(1, 0, 3, 2));
//
//   //   tmp2 = _mm_mul_ps(row3, tmp1);
//   //   tmp3 = _mm_mul_ps(row0, tmp1);
//
//   //   tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1));
//
//   //   tmp2 = _mm_sub_ps(tmp2, _mm_mul_ps(row3, tmp1));
//   //   tmp3 = _mm_sub_ps(tmp3, _mm_mul_ps(row0, tmp1));
//
//   //   minor2 = tmp2;
//   //   minor3 = tmp3;
//
//   //   // Compute determinant
//   //   __m128 det = _mm_mul_ps(row0, minor0);
//   //   det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 3, 0, 1)));
//   //   det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(1, 0, 3, 2)));
//
//   //   __m128 invDet = _mm_div_ps(_mm_set1_ps(1.0f), det);
//
//   //   // Multiply cofactors by reciprocal determinant
//   //   minor0 = _mm_mul_ps(minor0, invDet);
//   //   minor1 = _mm_mul_ps(minor1, invDet);
//   //   minor2 = _mm_mul_ps(minor2, invDet);
//   //   minor3 = _mm_mul_ps(minor3, invDet);
//
//   //   float_matrix4 R;
//
//   //   _mm_storeu_ps(&R.m[0][0], minor0);
//   //   _mm_storeu_ps(&R.m[1][0], minor1);
//   //   _mm_storeu_ps(&R.m[2][0], minor2);
//   //   _mm_storeu_ps(&R.m[3][0], minor3);
//
//   //   return R;
//   //}
////
////// --- SIMD optimized multiplication (SSE) ----------------------------------
////// Only enabled if SSE is available. Operates on column-major storage where
////// each column is contiguous in memory: &M.m[col][0]
////#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
////
////   // float_matrix4 * vec4  (column-major) using SSE: result = col0 * vx + col1 * vy + ...
////   inline float_sequence4 mat4_mul_vec4_sse(const float_matrix4 &M, const float_sequence4 &s)
////   {
////      __m128 col0 = _mm_loadu_ps(&M.m[0][0]); // m00,m01,m02,m03
////      __m128 col1 = _mm_loadu_ps(&M.m[1][0]);
////      __m128 col2 = _mm_loadu_ps(&M.m[2][0]);
////      __m128 col3 = _mm_loadu_ps(&M.m[3][0]);
////
////      __m128 vx = _mm_set1_ps(s.x);
////      __m128 vy = _mm_set1_ps(s.y);
////      __m128 vz = _mm_set1_ps(s.z);
////      __m128 vw = _mm_set1_ps(s.w);
////
////      __m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(col0, vx), _mm_mul_ps(col1, vy)),
////                            _mm_add_ps(_mm_mul_ps(col2, vz), _mm_mul_ps(col3, vw)));
////
////      float_sequence4 out;
////      _mm_storeu_ps(&out.x, r);
////      return out;
////   }
////
////   // float_matrix4 * float_matrix4 (column-major): compute A * B by multiplying A by each column of B
////   inline float_matrix4 mat4_mul_mat4_sse(const float_matrix4 &A, const float_matrix4 &B)
////   {
////      float_matrix4 R;
////      // for each column j of B, compute R.col[j] = A * B.col[j]
////      for (int j = 0; j < 4; ++j)
////      {
////         __m128 colB = _mm_loadu_ps(&B.m[j][0]); // B column j
////         // extract components of B.col[j]
////         float bj0 = ((float *)&B.m[j][0])[0];
////         float bj1 = ((float *)&B.m[j][0])[1];
////         float bj2 = ((float *)&B.m[j][0])[2];
////         float bj3 = ((float *)&B.m[j][0])[3];
////
////         __m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(&A.m[0][0]), _mm_set1_ps(bj0)),
////                                          _mm_mul_ps(_mm_loadu_ps(&A.m[1][0]), _mm_set1_ps(bj1))),
////                               _mm_add_ps(_mm_mul_ps(_mm_loadu_ps(&A.m[2][0]), _mm_set1_ps(bj2)),
////                                          _mm_mul_ps(_mm_loadu_ps(&A.m[3][0]), _mm_set1_ps(bj3))));
////         _mm_storeu_ps(&R.m[j][0], r);
////      }
////      return R;
////   }
////
////#endif // __SSE__
//
////   // Fallback wrappers that choose SSE version if available
////   inline vec4 mul(const float_matrix4 &M, const vec4 &s)
////   {
////#if defined(__SSE__)
////      return mat4_mul_vec4_sse(M, s);
////#else
////      return M * s;
////#endif
////   }
////
////   inline float_matrix4 mul(const float_matrix4 &A, const float_matrix4 &B)
////   {
////#if defined(__SSE__)
////      return mat4_mul_mat4_sse(A, B);
////#else
////      return A * B;
////#endif
////   }
////
////#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
////
////   inline float_matrix4 mat4_inverse_sse(const float_matrix4 &A)
////   {
////      // Build rows from column-major storage:
////      // row0 = [ m00 m01 m02 m03 ] where mXY is row X column Y
////      // Note: our storage is m[col][row], so m00 = A.m[0][0], m01 = A.m[1][0], ...
////      __m128 row0 = _mm_setr_ps(A.m[0][0], A.m[1][0], A.m[2][0], A.m[3][0]);
////      __m128 row1 = _mm_setr_ps(A.m[0][1], A.m[1][1], A.m[2][1], A.m[3][1]);
////      __m128 row2 = _mm_setr_ps(A.m[0][2], A.m[1][2], A.m[2][2], A.m[3][2]);
////      __m128 row3 = _mm_setr_ps(A.m[0][3], A.m[1][3], A.m[2][3], A.m[3][3]);
////
////      __m128 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
////      __m128 minor0, minor1, minor2, minor3;
////      __m128 det, det_shuf, inv_det;
////
////      // compute pairs for first 8 cofactors (cofactor matrix)
////      tmp1 = _mm_mul_ps(row2, row3);
////      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1)); // swap pairs
////
////      tmp2 = _mm_mul_ps(row1, tmp1);
////      tmp3 = _mm_mul_ps(row0, tmp1);
////
////      tmp1 = _mm_shuffle_ps(tmp1, tmp1, _MM_SHUFFLE(2, 3, 0, 1)); // undo shuffle for other part
////
////      tmp2 = _mm_sub_ps(_mm_mul_ps(row1, _mm_shuffle_ps(row2, row3, _MM_SHUFFLE(1, 0, 3, 2))), tmp2);
////      tmp3 = _mm_sub_ps(_mm_mul_ps(row0, _mm_shuffle_ps(row2, row3, _MM_SHUFFLE(1, 0, 3, 2))), tmp3);
////
////      minor0 = tmp2;
////      minor1 = tmp3;
////
////      // compute pairs for the next 8 cofactors
////      tmp4 = _mm_mul_ps(row1, row2);
////      tmp4 = _mm_shuffle_ps(tmp4, tmp4, _MM_SHUFFLE(2, 3, 0, 1));
////
////      tmp5 = _mm_mul_ps(row3, tmp4);
////      tmp6 = _mm_mul_ps(row0, tmp4);
////
////      tmp4 = _mm_shuffle_ps(tmp4, tmp4, _MM_SHUFFLE(2, 3, 0, 1));
////
////      tmp5 = _mm_sub_ps(_mm_mul_ps(row3, _mm_shuffle_ps(row1, row2, _MM_SHUFFLE(1, 0, 3, 2))), tmp5);
////      tmp6 = _mm_sub_ps(_mm_mul_ps(row0, _mm_shuffle_ps(row1, row2, _MM_SHUFFLE(1, 0, 3, 2))), tmp6);
////
////      minor2 = tmp5;
////      minor3 = tmp6;
////
////      // assemble the cofactor matrix (rows of cofactors)
////      // Note: This sequence produces cofactors in row-major order (as __m128 rows).
////      // Now compute determinant = dot(row0, minor0)
////      det = _mm_mul_ps(row0, minor0);
////      det_shuf = _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 3, 0, 1));
////      det = _mm_add_ps(det, det_shuf);
////      det_shuf = _mm_shuffle_ps(det, det, _MM_SHUFFLE(1, 0, 3, 2));
////      det = _mm_add_ps(det, det_shuf);
////
////      // reciprocal determinant
////      inv_det = _mm_div_ps(_mm_set1_ps(1.0f), det);
////
////      // Multiply cofactors by reciprocal determinant and transpose to column-major
////      minor0 = _mm_mul_ps(minor0, inv_det);
////      minor1 = _mm_mul_ps(minor1, inv_det);
////      minor2 = _mm_mul_ps(minor2, inv_det);
////      minor3 = _mm_mul_ps(minor3, inv_det);
////
////      // The minors we have are the rows of the adjugate (cofactor) matrix. We must transpose them
////      // to get the column-major result matrix. Perform a 4x4 transpose on [minor0..minor3].
////      __m128 t0 = _mm_unpacklo_ps(minor0, minor1); // m00 m10 m01 m11
////      __m128 t1 = _mm_unpackhi_ps(minor0, minor1); // m02 m12 m03 m13
////      __m128 t2 = _mm_unpacklo_ps(minor2, minor3); // m20 m30 m21 m31
////      __m128 t3 = _mm_unpackhi_ps(minor2, minor3); // m22 m32 m23 m33
////
////      __m128 col0 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(1, 0, 1, 0)); // m00 m10 m20 m30
////      __m128 col1 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(3, 2, 3, 2)); // m01 m11 m21 m31
////      __m128 col2 = _mm_shuffle_ps(t1, t3, _MM_SHUFFLE(1, 0, 1, 0)); // m02 m12 m22 m32
////      __m128 col3 = _mm_shuffle_ps(t1, t3, _MM_SHUFFLE(3, 2, 3, 2)); // m03 m13 m23 m33
////
////      float_matrix4 R;
////      _mm_storeu_ps(&R.m[0][0], col0); // store column 0
////      _mm_storeu_ps(&R.m[1][0], col1); // store column 1
////      _mm_storeu_ps(&R.m[2][0], col2); // store column 2
////      _mm_storeu_ps(&R.m[3][0], col3); // store column 3
////
////      return R;
////   }
////#endif // SSE
//
////   // Wrapper: use SIMD inverse when available, else fallback
////   inline float_matrix4 inverse_simd(const float_matrix4 &A)
////   {
////#if defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
////      return mat4_inverse_sse(A);
////#else
////      return inverse(A);
////#endif
////   }
//   //   // Multiply 4x4 matrix `a` by 4x4 matrix `b` (a*b) using AVX2 fully unrolled
//   //inline float_matrix4 mul_avx2(const float_matrix4 &a, const float_matrix4 &b)
//   //{
//   //   float_matrix4 result;
//
//   //   // Load columns of B
//   //   __m128 b0 = _mm_loadu_ps(&b.fa[0]);
//   //   __m128 b1 = _mm_loadu_ps(&b.fa[4]);
//   //   __m128 b2 = _mm_loadu_ps(&b.fa[8]);
//   //   __m128 b3 = _mm_loadu_ps(&b.fa[12]);
//
//   //   // For each column of B, broadcast each element and multiply-add with columns of A
//   //   for (int col = 0; col < 4; ++col)
//   //   {
//   //      __m128 bc; // broadcast column element
//   //      __m256 sum01, sum23;
//
//   //      switch (col)
//   //      {
//   //         case 0:
//   //            bc = b0;
//   //            break;
//   //         case 1:
//   //            bc = b1;
//   //            break;
//   //         case 2:
//   //            bc = b2;
//   //            break;
//   //         case 3:
//   //            bc = b3;
//   //            break;
//   //      }
//
//   //      // Broadcast each element of the column
//   //      __m256 b0_256 = _mm256_broadcast_ps((__m128 *)&bc); // replicate column
//   //      // Load A columns
//   //      __m256 a01 = _mm256_loadu_ps(&a.fa[0]); // columns 0 & 1
//   //      __m256 a23 = _mm256_loadu_ps(&a.fa[8]); // columns 2 & 3
//
//   //      // Multiply and sum
//   //      sum01 = _mm256_mul_ps(a01, b0_256); // element-wise multiply
//   //      sum23 = _mm256_mul_ps(a23, b0_256);
//
//   //      // Add results
//   //      __m256 result256_0 = _mm256_add_ps(sum01, sum23);
//
//   //      // Store back
//   //      _mm256_storeu_ps(&result.fa[0], result256_0); // fully unrolled: can expand by column
//   //   }
//
//   //   return result;
//   //}
//
//
//} // namespace geometry
//
//






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


template<primitive_floating FLOATING, int t_iDimension>  
inline matrix_type<FLOATING, t_iDimension> row_major_type< FLOATING, t_iDimension >::transpose() const
{
   matrix_type<FLOATING, 4> r;
   _transpose(4, this->m);
   return r;
}


template<primitive_number NUMBER, int t_iSize>
template<primitive_floating FLOATING1>
inline sequence_type<NUMBER, t_iSize>
sequence_type<NUMBER, t_iSize>::operator*(const matrix_type<FLOATING1, 3> &M) const
   requires(t_iSize == 3 && std::is_same_v < FLOATING1, NUMBER >)
{
   const auto &v = *this;
   sequence_type result;
   result.x = v.x * M[0][0] + v.y * M[0][1] + v.z * M[0][2];
   result.y = v.x * M[1][0] + v.y * M[1][1] + v.z * M[1][2];
   result.z = v.x * M[2][0] + v.y * M[2][1] + v.z * M[2][2];
   return result;
}


template<primitive_number NUMBER, int t_iSize>
   template<primitive_floating FLOATING1>
inline sequence_type<NUMBER, t_iSize>
sequence_type<NUMBER, t_iSize>::operator*(const matrix_type<FLOATING1, 4> &M) const
   requires(t_iSize == 4 && ::std::is_same_v<FLOATING1, NUMBER>)
{

   const auto &v = *this;
   sequence_type result;

   result.x = v.x * M[0][0] + v.y * M[0][1] + v.z * M[0][2] + v.w * M[0][3];
   result.y = v.x * M[1][0] + v.y * M[1][1] + v.z * M[1][2] + v.w * M[1][3];
   result.z = v.x * M[2][0] + v.y * M[2][1] + v.z * M[2][2] + v.w * M[2][3];
   result.w = v.x * M[3][0] + v.y * M[3][1] + v.z * M[3][2] + v.w * M[3][3];

   return result;
}



