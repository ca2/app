#pragma once


namespace comparison
{



   template < typename A, typename B >
   inline bool eq(A a, B b)
   {
      return a == b;
   }

   template < >
   inline bool eq(::i32 i, ::u32 u)
   {
      return i < 0 ? false : (::u32)i == u;
   }



   template < typename A, typename B >
   inline bool lt(A a, B b)
   {

      return a < b;

   }

   template < >
   inline bool lt(long int l, unsigned long int ul)
   {

      return l < 0 ? true : (unsigned long int) l < ul;

   }

   template < >
   inline bool lt(::i32 i, unsigned long long ull)
   {
      return i < 0 ? true : (unsigned long long) i < ull;
   }

   template < >
   inline bool lt(::i32 i, unsigned long ul)
   {
      return i < 0 ? true : (unsigned long)i < ul;
   }


   template < >
   inline bool lt(::i32 i, ::u32 u)
   {
      return i < 0 ? true : (::u32)i < u;
   }


   template < >
   inline bool lt(::u32 u, ::i32 i)
   {

      return i < 0 ? false : u < (::u32)i;

   }


   template < >
   inline bool lt(::u32 u, long l)
   {

      return l < 0 ? false : u < (::u32)l;

   }


   template < >
   inline bool lt(::u32 u, char ch)
   {

      return ch < 0 ? false : u < (::u32)ch;

   }


   template < >
   inline bool lt(u64 ui64, u32 u32)
   {
      return ui64 > 0xffffffffull ? false : (u64)ui64 < u32;
   }

   template < >
   inline bool lt(u64 ui64, i64 i32)
   {
      return i32 < 0 ? false : ui64 < (u64)i32;
   }

#if defined(WINDOWS)

   template < >
   inline bool lt(i64 i, ::u64 u)
   {
      return i < 0 ? true : (::u64)i < u;
   }

   template < >
   inline bool lt(unsigned long u, long i)
   {
      return i < 0 ? false : u < (::u32) i;
   }

#endif


   template < typename A, typename B >
   inline bool le(A a, B b)
   {
      return a <= b;
   }


   template <  >
   inline bool le(i32 i, ::u32 u)
   {
      return i < 0 ? false : (::u32) i <= u;
   }

   template <  >
   inline bool le(i64 i, size_t u)
   {
      return i < 0 ? false : (::u32)i <= u;
   }

   template < typename A, typename B >
   inline bool gt(A a, B b)
   {
      return a > b;
   }


   template < >
   inline bool gt(::i32 i, ::u32 u)
   {

      return i < 0 ? false : ((::u32)i) > u;

   }


   template < >
   inline bool gt(::i32 i, unsigned long ul)
   {

      return i < 0 ? false : ((::u32)i) > ul;

   }


   template < >
   inline bool gt(::u32 u, ::i32 i)
   {

      return i < 0 ? true : u > ((::u32) i);

   }


   template < >
   inline bool gt(::u32 u, long l)
   {

      return l < 0 ? true : u >((::u32)l);

   }


   template < >
   inline bool gt(::u32 u, char ch)
   {

      return ch < 0 ? true : u >((::u32)ch);

   }


   template < >
   inline bool gt(i64 i, u64 u)
   {

      return i < 0 ? false : ((u64)i) > u;

   }

   template < >
   inline bool gt(::i32 i, long long int lli)
   {

      return i < 0 ? false : ((long long int)i) > lli;

   }


   template < >
   inline bool gt(u64 u, i64 i)
   {

      return i < 0 ? true : u > ((u64) i);

   }


#ifdef WINDOWS
   template < >
   inline bool gt(DWORD dw, ::i32 i)
   {
      return i < 0 ? true : dw >((DWORD)i);
   }

   //template < >
   //inline bool gt(count i,u64 u)
   //{

   //   return i < 0 ? false : ((u64)i) > u;

   //}

#endif

   template < typename A, typename B >
   inline bool ge(A a, B b)
   {
      return a >= b;
   }

   template < >
   inline bool ge(::i32 i, unsigned long long ul)
   {
      return i < 0 ? false : ((unsigned long)i) >= ul;
   }

   template < >
   inline bool ge(long long l, unsigned long long ul)
   {
      return l < 0 ? false : ((unsigned long long) l) >= ul;
   }

   template < >
   inline bool ge(::u32 u, unsigned long long ul)
   {
      return u >= ul;
   }

   template < >
   inline bool ge(unsigned long long ul1, unsigned long long ul2)
   {
      return ul1 >= ul2;
   }

   template < >
   inline bool ge(unsigned long long ul1, long long l2)
   {
      return l2 < 0 ? true : ul1 >= (unsigned long long) l2;
   }

   template < >
   inline bool ge(::u32 u, short sh)
   {
      return sh < 0 ? true : u >= (::u32)sh;
   }

   template < >
   inline bool ge(::i32 i, ::u32 u)
   {
      return i < 0 ? false : (::u32)i >= u;
   }

   template < >
   inline bool ge(::u32 u, ::i32 i)
   {
      return i < 0 ? true : u >= (::u32)i;
   }


   template < >
   inline bool ge(unsigned long ul, ::i32 i)
   {
      return i < 0 ? true : ul >= (unsigned long)i;
   }


   template < >
   inline bool le(::i32 i, unsigned long long ul)
   {
      return i < 0 ? true : ((unsigned long)i) <= ul;
   }



   template < typename T1, typename T2 >
   inline bool is_equal(const T1& t1, const T2& t2, double dMargin, bool bIn)
   {

      double delta = (double)(t1 - t2);

      if (bIn)
      {

         return delta >= (-dMargin / 2.0) && delta <= dMargin;

      }
      else
      {

         return delta >= (-dMargin) && delta <= dMargin * 2.0;

      }


   }


   template < typename OUTER1, typename INNER1, typename INNER2, typename OUTER2 >
   inline bool is_centered(const OUTER1& outer1, const INNER1& inner1, const INNER2& inner2, const OUTER2& outer2)
   {

      auto delta1 = abs(outer1 - inner1);

      auto delta2 = abs(inner2 - outer2);

      auto delta = (delta1 + delta2) / 3;

      return abs(delta1 - delta2) < delta;

   }

   

} // namespace comparison




