#pragma once





CLASS_DECL_ACME void throw_cast_overflow();





#define INT_TO_NATURAL(i) (i >= 0 ? (u32) i : 0)




inline u32 natural(i32 i)
{
   return i >= 0 ? (u32) i : 0;
}

inline u32 natural(u32 ui)
{
   return ui;
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
inline i32 natural_min(i32 i1, i32 i2, i32 iEscape = -1)
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


inline bool less_than(u64 ui, i32 i)
{
   return i < 0 ? false : ui < (u64) i;
}


inline i32 mkint(u32 ui)
{
   if (ui >= 0x7fffffff)
      throw_cast_overflow();
   return (i32) ui;
}

inline i32 mkint(i32 i)
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


// if a == b, min returns first argument
template < typename A, typename B >
constexpr const auto min(const A & a, const B & b)
{

   return b < a ? b : a;

}

// if a == b, max returns first argument
template < typename A, typename B >
constexpr const auto max(const A & a, const B & b)
{

   return b > a ? b : a;

}


template < typename A, typename B >
constexpr auto min_non_neg(A a, B b)
{

   if(a < (A) 0)
   {

      if (b < (B) 0)
      {

         return min(a, b);

      }
      else 
      {

         return b;

      }

   }
   else if(b < (B) 0)
   {
      
      return a;

   }
   else 
   {

      return min(a, b);

   }

}


template < typename t >
t min_non_null(const t & t1, const t & t2)
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
