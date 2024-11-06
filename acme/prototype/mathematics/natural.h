#pragma once





CLASS_DECL_ACME void throw_cast_overflow();





#define INT_TO_NATURAL(i) (i >= 0 ? (unsigned int) i : 0)




inline unsigned int natural(int i)
{
   return i >= 0 ? (unsigned int) i : 0;
}

inline unsigned int natural(unsigned int u)
{
   return u;
}

inline u64 natural(i64 ll)
{
   return ll >= 0 ? (u64) ll: 0;
}

inline u64 natural(u64 ull)
{
   return ull;
}

#ifdef ANDROID

inline unsigned long natural(long l)
{
   return l >= 0 ? (unsigned long) l : 0;
}

#endif

// return minimum zero or positive integer
// otherwise, return third optional default -1 argument
inline int natural_min(int i1, int i2, int iEscape = -1)
{
   if(i1 >= 0)
   {
      if(i2 >= 0)
      {
         if(i2 < i1)
            return i2;
         else
            return i1;
      }
      else
      {
         return i1;
      }
   }
   else
   {
      if(i2 >= 0)
      {
         return i2;
      }
      else
      {
         return iEscape;
      }
   }
}


inline bool less_than(u64 u, int i)
{
   return i < 0 ? false : u < (u64) i;
}


inline int mkint(unsigned int u)
{
   if (u >= I32_MAXIMUM)
      throw_cast_overflow();
   return (int) u;
}

inline int mkint(int i)
{
   return i;
}

inline i64 mkint(u64 ull)
{
   if (ull >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (i64)ull;
}

inline i64 mkint(i64 ll)
{
   return ll;
}

//
////// if a == b, minimum returns first argument
//template < typename A, typename B >
//constexpr const auto minimum(const A & a, const B & b)
//{
//
//   return a < b ? a : (A) b;
//
//}

//
//template < primitive_integral) A, __typename(primitive_integral B >
//constexpr const auto maximum(const A & a, const B & b)
//{
//
//   return b < a ? a : (A)b;
//
//}
//

//// if a == b, maximum returns first argument
//template < typename A, typename B >
//constexpr const auto maximum(const A & a, const B & b)
//{
//
//   return b < a ? a : (A) b;
//
//}

//#define maximum(a, b) ((a) < (b) ? (b) : (a))
//#define minimum(a, b) ((a) < (b) ? (a) : (b))

template < typename A, typename B >
constexpr largest_type < A, B > minimum_non_negative(A a, B b)
{

   if(a < (A) 0)
   {

      if (b < (B) 0)
      {

         return (largest_type < A, B >) minimum(a, b);

      }
      else 
      {

         return (largest_type < A, B >) b;

      }

   }
   else if(b < (B) 0)
   {
      
      return (largest_type < A, B >) a;

   }
   else 
   {

      return (largest_type < A, B >) minimum(a, b);

   }

}


template < typename t >
t minimum_non_null(const t & t1, const t & t2)
{
   if (t1 == (t) 0)
   {
      return t2;
   }
   else if (t2 == (t) 0)
   {
      return t1;
   }
   else if (t1 < t2)
   {
      return t1;
   }
   else
   {
      return t2;
   }
}



template < typename T, typename L, typename H >
constexpr auto minimum_maximum(T t, L l, H h)
{

   if (t < (T)l)
   {

      return (T) l;

   }
   else if ((T)h < t)
   {

      return (T) h;

   }
   else
   {

      return t;

   }

}



//template <  >
//constexpr const auto minimum(const U & u, const I & i)
//{
//
//   return i < 0 ? 0 : (u < (unsigned int) i ? u : (unsigned int)i);
//
//}
//template <  > constexpr const auto minimum(const ::u64 & u, const ::i64 & i){  return i < 0 ? 0 : (u < (::u64)i ? u : (::u64)i); }
//template <  > constexpr const auto minimum(const ::u64 & u, const int & i) { return i < 0 ? 0 : (u < (::u64)i ? u : (::u64)i); }
//template <  > constexpr const auto minimum(const ::u64 & u, const short & i) { return i < 0 ? 0 : (u < (::u64)i ? u : (::u64)i); }
//template <  > constexpr const auto minimum(const ::u64 & u, const char & i) { return i < 0 ? 0 : (u < (::u64)i ? u : (::u64)i); }
//template <  > constexpr const auto minimum(const unsigned int & u, const ::i64 & i) { return i < 0 ? 0 : (u < (unsigned int)i ? u : (unsigned int)i); }
//template <  > constexpr const auto minimum(const unsigned int & u, const int & i) { return i < 0 ? 0 : (u < (unsigned int)i ? u : (unsigned int)i); }
//template <  > constexpr const auto minimum(const unsigned int & u, const short & i) { return i < 0 ? 0 : (u < (unsigned int)i ? u : (unsigned int)i); }
//template <  > constexpr const auto minimum(const unsigned int & u, const char & i) { return i < 0 ? 0 : (u < (unsigned int)i ? u : (unsigned int)i); }
//template <  > constexpr const auto minimum(const unsigned short & u, const ::i64 & i) { return i < 0 ? 0 : (u < (unsigned short)i ? u : (unsigned short)i); }
//template <  > constexpr const auto minimum(const unsigned short & u, const int & i) { return i < 0 ? 0 : (u < (unsigned short)i ? u : (unsigned short)i); }
//template <  > constexpr const auto minimum(const unsigned short & u, const short & i) { return i < 0 ? 0 : (u < (unsigned short)i ? u : (unsigned short)i); }
//template <  > constexpr const auto minimum(const unsigned short & u, const char & i) { return i < 0 ? 0 : (u < (unsigned short)i ? u : (unsigned short)i); }
//template <  > constexpr const auto minimum(const unsigned char & u, const ::i64 & i) { return i < 0 ? 0 : (u < (unsigned char)i ? u : (unsigned char)i); }
//template <  > constexpr const auto minimum(const unsigned char & u, const int & i) { return i < 0 ? 0 : (u < (unsigned char)i ? u : (unsigned char)i); }
//template <  > constexpr const auto minimum(const unsigned char & u, const short & i) { return i < 0 ? 0 : (u < (unsigned char)i ? u : (unsigned char)i); }
//template <  > constexpr const auto minimum(const unsigned char & u, const char & i) { return i < 0 ? 0 : (u < (unsigned char)i ? u : (unsigned char)i); }
