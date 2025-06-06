#if (defined(_WIN32) && !defined(_M_ARM)) && OSBIT == 32
#define VECTOR3_SSE 1
#else
#define VECTOR3_SSE 0
#endif


#if VECTOR3_SSE
#include <smmintrin.h>

///////////////////////////////////////////////////////////////
//
// Simple vector class
//
// http://fastcpp.blogspot.com.br/2011/12/simple-vector3-class-with-sse-support.html
// theowl64
// I'm a PhD student from Austria who is interested in photography and high performance programming.
// https://repos.ca2.network/hi5/user/europe/austria/theowl64/theowl64.jpg
// Gender: Male
// Activity: Science
// Occupation: PhD Student
// Interests: music, photography, reading, travel, computer vision
// Favorite songs: Radiohead, Gershwin
//
/////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
// Gustavo Oliveria guitarv
//	This example class shows a sketch of how many SIMD game math libraries are
//	commonly designed, i.e., encapsulating data and functions inside a class.
//	Also it encapsulates overloaded operators to make the design clean and
//	friendly to the programmers.
//
//	Nonethelss this approach causes the **INEVITABLE CODE BLOAT** when
//	performing more complex math expressions.
///////////////////////////////////////////////////////////////////////////////

__declspec(align(16)) class vector4
{
public:
   // constructors
   inline vector4() : mmvalue(_mm_setzero_ps()) {}
   inline vector4(float a) : mmvalue(_mm_set_ps(a, a, a, a)) {}
   inline vector4(float w, float x, float y, float z) : mmvalue(_mm_set_ps(z, y, x, w)) {}
   inline vector4(__m128 m) : mmvalue(m) {}

   // arithmetic operators with vector4
   inline vector4 operator +(const vector4 & b) const
   {
      return _mm_add_ps(mmvalue, b.mmvalue);
   }
   inline vector4 operator-(const vector4 & b) const
   {
      return _mm_sub_ps(mmvalue, b.mmvalue);
   }
   inline vector4 operator*(const vector4 & b) const
   {
      return _mm_mul_ps(mmvalue, b.mmvalue);
   }
   inline vector4 operator/(const vector4 & b) const
   {
      return _mm_div_ps(mmvalue, b.mmvalue);
   }

   // op= operators
   inline vector4 & operator +=(const vector4 & b)
   {
      mmvalue = _mm_add_ps(mmvalue, b.mmvalue);
      return *this;
   }
   inline vector4 & operator-=(const vector4 & b)
   {
      mmvalue = _mm_sub_ps(mmvalue, b.mmvalue);
      return *this;
   }
   inline vector4 & operator*=(const vector4 & b)
   {
      mmvalue = _mm_mul_ps(mmvalue, b.mmvalue);
      return *this;
   }
   inline vector4 & operator/=(const vector4 & b)
   {
      mmvalue = _mm_div_ps(mmvalue, b.mmvalue);
      return *this;
   }

   // arithmetic operators with float
   inline vector4 operator +(float b) const
   {
      return _mm_add_ps(mmvalue, _mm_set1_ps(b));
   }
   inline vector4 operator-(float b) const
   {
      return _mm_sub_ps(mmvalue, _mm_set1_ps(b));
   }
   inline vector4 operator*(float b) const
   {
      return _mm_mul_ps(mmvalue, _mm_set1_ps(b));
   }
   inline vector4 operator/(float b) const
   {
      return _mm_div_ps(mmvalue, _mm_set1_ps(b));
   }

   // op= operators with float
   inline vector4 & operator +=(float b)
   {
      mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(b));
      return *this;
   }
   inline vector4 & operator-=(float b)
   {
      mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(b));
      return *this;
   }
   inline vector4 & operator*=(float b)
   {
      mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(b));
      return *this;
   }
   inline vector4 & operator/=(float b)
   {
      mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(b));
      return *this;
   }

   // cross product
   inline vector4 cross(const vector4 & b) const
   {
      return _mm_sub_ps(
             _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
             _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
      );
   }

   // dot product with another vector
   inline float dot(const vector4 & b) const
   {
      return _mm_cvtss_float(_mm_dp_ps(mmvalue, b.mmvalue, 0x55));
   }
   // length of the vector
   inline float length() const
   {
      return _mm_cvtss_float(_mm_sqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x55)));
   }
   // 1/length() of the vector
   inline float rlength() const
   {
      return _mm_cvtss_float(_mm_rsqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x55)));
   }
   // returns the vector scaled to unit length
   inline vector4 normalize() const
   {
      return _mm_mul_ps(mmvalue, _mm_rsqrt_ps(_mm_dp_ps(mmvalue, mmvalue, 0x55)));
   }

   // overloaded operators that ensure alignment
   inline void * operator new[](size_t x)
   {
      return _aligned_malloc(x, 16);
   }
   inline void operator delete[](void * x)
   {
      if (x) _aligned_free(x);
   }

   // Member variables
   union
   {
      struct
      {
         float w, x, y, z;
      };
      __m128 mmvalue;
   };



};

inline vector4 operator +(float a, const vector4 & b)
{
   return b + a;
}
inline vector4 operator-(float a, const vector4 & b)
{
   return vector4(_mm_set1_ps(a)) - b;
}
inline vector4 operator*(float a, const vector4 & b)
{
   return b * a;
}
inline vector4 operator/(float a, const vector4 & b)
{
   return vector4(_mm_set1_ps(a)) / b;
}
//inline vector4 operator +(const vector4& a,const vector4& b) { return _mm_add_ps(a.mmvalue,b.mmvalue); }
//inline vector4 operator-(const vector4& a,const vector4& b) { return _mm_sub_ps(a.mmvalue,b.mmvalue); }
//inline vector4 operator*(const vector4& a,const vector4& b) { return _mm_mul_ps(a.mmvalue,b.mmvalue); }
//inline vector4 operator/(const vector4& a,const vector4& b) { return _mm_div_ps(a.mmvalue,b.mmvalue); }
//inline vector4& operator +=(vector4& a,const vector4& b) { a.mmvalue = _mm_add_ps(a.mmvalue,b.mmvalue); return a; }
//inline vector4& operator-=(vector4& a,const vector4& b) { a.mmvalue = _mm_sub_ps(a.mmvalue,b.mmvalue); return a; }
//inline vector4& operator*=(vector4& a,const vector4& b) { a.mmvalue = _mm_mul_ps(a.mmvalue,b.mmvalue); return a; }
//inline vector4& operator/=(vector4& a,const vector4& b) { a.mmvalue = _mm_div_ps(a.mmvalue,b.mmvalue); return a; }

//////////////////////////////////////////////////////////////////////////////
// Fast SSE2 4-dimensional dot product by Gustavo M. Oliveira.
// Feel free to use for commercial or non-commercial applications,
// as long as this header is mantained.
//
// For more information on how to write and use high-performance
// SIMD Libraties, visit:
// http://www.guitarv.com/ComputerScience.aspx?page=articles
//
// The author assumes NO RESPONSIBILITY and/or LIABILITY  for any problems
// caused by the use of this software. Use it at your own risk.
//////////////////////////////////////////////////////////////////////////////
inline vector4 Dot(const vector4 & va, const vector4 & vb)
{
   vector4 t0 = _mm_mul_ps(va.mmvalue, vb.mmvalue);
   vector4 t1 = _mm_shuffle_ps(t0.mmvalue, t0.mmvalue, _MM_SHUFFLE(1, 0, 3, 2));
   vector4 t2 = _mm_add_ps(t0.mmvalue, t1.mmvalue);
   vector4 t3 = _mm_shuffle_ps(t2.mmvalue, t2.mmvalue, _MM_SHUFFLE(2, 3, 0, 1));
   vector4 dot = _mm_add_ps(t3.mmvalue, t2.mmvalue);
   return (dot);
}

inline vector4 Reflect(const vector4 & Incident, const vector4 & Normal)
{
   // Result = Incident - (2 * dot(Incident, Normal)) * Normal
   vector4 Result = Dot(Incident, Normal);
   Result = _mm_add_ps(Result.mmvalue, Result.mmvalue);
   Result = _mm_mul_ps(Result.mmvalue, Normal.mmvalue);
   Result = _mm_sub_ps(Incident.mmvalue, Result.mmvalue);

   return Result;

}


#endif // VECTOR3_SSE
