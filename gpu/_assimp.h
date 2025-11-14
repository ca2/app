// Created by camilo with ChatGPT on 2025-11-14 <3ThomasBorregaardSørensen!!
#pragma once

#include <assimp/matrix4x4.h>
#include "acme/prototype/geometry/matrix.h"

#include <immintrin.h> // For SIMD intrinsics



inline float_matrix4 aiMatrix4x4ToColumnMajorSIMD(const aiMatrix4x4 &from)
{

   float_matrix4 to;

   // Load rows of the aiMatrix4x4 into __m128 registers
   __m128 row0 = _mm_set_ps(from.a4, from.a3, from.a2, from.a1); // row 0
   __m128 row1 = _mm_set_ps(from.b4, from.b3, from.b2, from.b1); // row 1
   __m128 row2 = _mm_set_ps(from.c4, from.c3, from.c2, from.c1); // row 2
   __m128 row3 = _mm_set_ps(from.d4, from.d3, from.d2, from.d1); // row 3

   // Transpose the 4x4 matrix
   __m128 tmp0 = _mm_unpacklo_ps(row0, row1); // a1 b1 a2 b2
   __m128 tmp1 = _mm_unpackhi_ps(row0, row1); // a3 b3 a4 b4
   __m128 tmp2 = _mm_unpacklo_ps(row2, row3); // c1 d1 c2 d2
   __m128 tmp3 = _mm_unpackhi_ps(row2, row3); // c3 d3 c4 d4

   __m128 col0 = _mm_movelh_ps(tmp0, tmp2); // a1 b1 c1 d1
   __m128 col1 = _mm_movehl_ps(tmp2, tmp0); // a2 b2 c2 d2
   __m128 col2 = _mm_movelh_ps(tmp1, tmp3); // a3 b3 c3 d3
   __m128 col3 = _mm_movehl_ps(tmp3, tmp1); // a4 b4 c4 d4

   // Store columns into floating_matrix4
   _mm_storeu_ps(&to.m[0], col0);
   _mm_storeu_ps(&to.m[4], col1);
   _mm_storeu_ps(&to.m[8], col2);
   _mm_storeu_ps(&to.m[12], col3);

   return to;

}


inline float_matrix4 aiMatrix4x4ToColumnMajorAVX2(const aiMatrix4x4 &from)
{
   float_matrix4 to;

   // Load 4 rows into two 256-bit registers (two rows per register)
   // Layout in memory: row0 = a1 a2 a3 a4, row1 = b1 b2 b3 b4, etc.
   __m256 row01 = _mm256_set_ps(from.b4, from.b3, from.b2, from.b1, from.a4, from.a3, from.a2, from.a1);

   __m256 row23 = _mm256_set_ps(from.d4, from.d3, from.d2, from.d1, from.c4, from.c3, from.c2, from.c1);

   // Unpack 32-bit floats to interleave
   __m256 t0 = _mm256_unpacklo_ps(row01, row23); // a1 c1 a2 c2 b1 d1 b2 d2
   __m256 t1 = _mm256_unpackhi_ps(row01, row23); // a3 c3 a4 c4 b3 d3 b4 d4

   // Shuffle to get final columns
   __m256 col01 = _mm256_permute2f128_ps(t0, t1, 0x20); // column 0 + column 1
   __m256 col23 = _mm256_permute2f128_ps(t0, t1, 0x31); // column 2 + column 3

   // Store each column (4 floats each) into floating_matrix4
   _mm_storeu_ps(&to.fa[0], _mm256_castps256_ps128(col01)); // column 0
   _mm_storeu_ps(&to.fa[4], _mm256_extractf128_ps(col01, 1)); // column 1
   _mm_storeu_ps(&to.fa[8], _mm256_castps256_ps128(col23)); // column 2
   _mm_storeu_ps(&to.fa[12], _mm256_extractf128_ps(col23, 1)); // column 3

   return to;
}



inline float_matrix4 aiMatrix4x4ToColumnMajorAVX(const aiMatrix4x4 &from)
{
   float_matrix4 to;

   // Load two rows per 128-bit lane into two 256-bit registers
   __m256 row01 = _mm256_set_ps(from.b4, from.b3, from.b2, from.b1, from.a4, from.a3, from.a2, from.a1);

   __m256 row23 = _mm256_set_ps(from.d4, from.d3, from.d2, from.d1, from.c4, from.c3, from.c2, from.c1);

   // Interleave pairs of floats
   __m256 t0 = _mm256_unpacklo_ps(row01, row23); // a1 c1 a2 c2 b1 d1 b2 d2
   __m256 t1 = _mm256_unpackhi_ps(row01, row23); // a3 c3 a4 c4 b3 d3 b4 d4

   // Permute 128-bit lanes to get final columns
   __m256 col01 = _mm256_permute2f128_ps(t0, t1, 0x20); // column 0 + column 1
   __m256 col23 = _mm256_permute2f128_ps(t0, t1, 0x31); // column 2 + column 3

   // Store each column into floating_matrix4
   _mm_storeu_ps(&to.m[0], _mm256_castps256_ps128(col01)); // column 0
   _mm_storeu_ps(&to.m[4], _mm256_extractf128_ps(col01, 1)); // column 1
   _mm_storeu_ps(&to.m[8], _mm256_castps256_ps128(col23)); // column 2
   _mm_storeu_ps(&to.m[12], _mm256_extractf128_ps(col23, 1)); // column 3

   return to;
}
