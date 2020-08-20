#pragma once


namespace comparison
{



   template < typename A, typename B >
   inline bool eq(A a, B b)
   {
      return a == b;
   }

   template < >
   inline bool eq(int i, unsigned int ui)
   {
      return i < 0 ? false : (unsigned int)i == ui;
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
   inline bool lt(int i, unsigned long long ull)
   {
      return i < 0 ? true : (unsigned long long) i < ull;
   }

   template < >
   inline bool lt(int i, unsigned long ul)
   {
      return i < 0 ? true : (unsigned long)i < ul;
   }


   template < >
   inline bool lt(int i, unsigned int ui)
   {
      return i < 0 ? true : (unsigned int)i < ui;
   }


   template < >
   inline bool lt(unsigned int ui, int i)
   {

      return i < 0 ? false : ui < (unsigned int)i;

   }


   template < >
   inline bool lt(unsigned int ui, long l)
   {

      return l < 0 ? false : ui < (unsigned int)l;

   }


   template < >
   inline bool lt(unsigned int ui, char ch)
   {

      return ch < 0 ? false : ui < (unsigned int)ch;

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
   inline bool lt(i64 i, unsigned __int64 ui)
   {
      return i < 0 ? true : (unsigned __int64)i < ui;
   }

   template < >
   inline bool lt(DWORD dw, int i)
   {
      return i < 0 ? false : dw < (DWORD)i;
   }

#endif


   template < typename A, typename B >
   inline bool le(A a, B b)
   {
      return a <= b;
   }


   template <  >
   inline bool le(i32 i, unsigned int ui)
   {
      return i < 0 ? false : (unsigned int) i <= ui;
   }

   template <  >
   inline bool le(i64 i, size_t ui)
   {
      return i < 0 ? false : (unsigned int)i <= ui;
   }

   template < typename A, typename B >
   inline bool gt(A a, B b)
   {
      return a > b;
   }


   template < >
   inline bool gt(int i, unsigned int ui)
   {

      return i < 0 ? false : ((unsigned int)i) > ui;

   }


   template < >
   inline bool gt(int i, unsigned long ul)
   {

      return i < 0 ? false : ((unsigned int)i) > ul;

   }


   template < >
   inline bool gt(unsigned int ui, int i)
   {

      return i < 0 ? true : ui > ((unsigned int) i);

   }


   template < >
   inline bool gt(unsigned int ui, long l)
   {

      return l < 0 ? true : ui >((unsigned int)l);

   }


   template < >
   inline bool gt(unsigned int ui, char ch)
   {

      return ch < 0 ? true : ui >((unsigned int)ch);

   }


   template < >
   inline bool gt(i64 i, u64 ui)
   {

      return i < 0 ? false : ((u64)i) > ui;

   }

   template < >
   inline bool gt(int i, long long unsigned int llui)
   {

      return i < 0 ? false : ((long long unsigned int)i) > llui;

   }


   template < >
   inline bool gt(u64 ui, i64 i)
   {

      return i < 0 ? true : ui > ((u64) i);

   }


#ifdef WINDOWS
   template < >
   inline bool gt(DWORD dw, int i)
   {
      return i < 0 ? true : dw >((unsigned int)dw);
   }

   //template < >
   //inline bool gt(count i,u64 ui)
   //{

   //   return i < 0 ? false : ((u64)i) > ui;

   //}

#endif

   template < typename A, typename B >
   inline bool ge(A a, B b)
   {
      return a >= b;
   }

   template < >
   inline bool ge(int i, unsigned long long ul)
   {
      return i < 0 ? false : ((unsigned long)i) >= ul;
   }

   template < >
   inline bool ge(long long l, unsigned long long ul)
   {
      return l < 0 ? false : ((unsigned long long) l) >= ul;
   }

   template < >
   inline bool ge(unsigned int ui, unsigned long long ul)
   {
      return ui >= ul;
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
   inline bool ge(unsigned int ui, short sh)
   {
      return sh < 0 ? true : ui >= (unsigned int)sh;
   }

   template < >
   inline bool ge(int i, unsigned int ui)
   {
      return i < 0 ? false : (unsigned int)i >= ui;
   }

   template < >
   inline bool ge(unsigned int ui, int i)
   {
      return i < 0 ? true : ui >= (unsigned int)i;
   }


   template < >
   inline bool ge(unsigned long ul, int i)
   {
      return i < 0 ? true : ul >= (unsigned long)i;
   }


   template < >
   inline bool le(int i, unsigned long long ul)
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




