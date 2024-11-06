// Created by camilo on 2022-02-06 10:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "_memory.h"


//#ifdef WINDOWS
/*
* Find the first occurrence of the unsigned char string s in unsigned char string l.
*/

const void * memory_find(const void * l, memsize l_len, const void * s, memsize s_len)
{
   const unsigned char* cl = (const unsigned char*)l;
   const unsigned char* cs = (const unsigned char*)s;

   /* we need something to compare */
   if (l_len == 0 || s_len == 0)
      return nullptr;

   /* "s" must be smaller or equal to "l" */
   if (l_len < s_len)
      return nullptr;

   /* special case where s_len == 1 */
   if (s_len == 1) {
       return _memory_find_u8((void *) l, (int) *cs, l_len);

   }

   return _memory_find(l, l_len, s, s_len);

}

//#endif // #ifdef WINDOWS

void * reverse_memchr(const void * l, int ch, size_t l_len)
{

   char * end;

   if (l_len <= 0)
   {

      return nullptr;

   }

   end = (char *)l + l_len - 1;

   while (end >= l)
   {

      if (*end == ch)
      {

         return end;

      }

   }

   return nullptr;

}


/*
* Find the last occurrence of the unsigned char string s in unsigned char string l.
*/

void * reverse_memmem(const void * l, size_t l_len, const void * s, size_t s_len)
{

   char * cur, * last;
   const char * cl = (const char *)l;
   const char * cs = (const char *)s;

   /* we need something to compare */
   if (l_len == 0 || s_len == 0)
      return nullptr;

   /* "s" must be smaller or equal to "l" */
   if (l_len < s_len)
      return nullptr;

   /* special case where s_len == 1 */
   if (s_len == 1)
      return (void *) _memory_find_u8((const void *)l, (int)*cs, l_len);

   /* the last position where its possible to find "s" in "l" */
   last = (char *)cl + l_len - s_len;

   for (cur = (char *)last; cur >= cl; cur--)
   {

      if (cur[0] == cs[0] && _memory_order(cur, cs, s_len) == 0)
      {

         return cur;

      }

   }

   return nullptr;

}





void * reverse_byte_not_in_block(const void * l, size_t l_len, const void * s, size_t s_len)
{

   char * cur, * last, * curByte;
   char * prev = nullptr;
   const char * cl = (const char *)l;
   const char * cs = (const char *)s;
   const char * ends = (const char *)s + s_len;

   /* we need something to compare */
   if (l_len <= 0)
      return nullptr;

   /* the last position where its possible to find "s" in "l" */
   last = (char *)cl + l_len - 1;

   for (cur = (char *)last; cur >= cl; cur--)
   {

      for (curByte = (char *)cs; curByte < ends; curByte++)
      {

         if (cur[0] == curByte[0])
         {

            return prev;

         }

      }

      prev = cur;

   }

   return prev;

}


CLASS_DECL_ACMEunsigned int __u32_hash(const ::scoped_string & scopedstr)
{

   unsigned int u = 0;

   auto psz = scopedstr.begin();

   while (psz < scopedstr.end())
   {

      u = (u << 5) + *psz;

      psz++;

   }

   return u;

}





//#ifdef WINDOWS_DESKTOP
//
//
//::std::strong_ordering memory_order(const void * m1, const void * m2, memsize s)
//{
//
//   if (::is_null(m1))
//   {
//
//      if (::is_null(m2))
//      {
//
//         return ::std::strong_ordering::equal;
//
//      }
//      else
//      {
//
//         return ::std::strong_ordering::less;
//
//      }
//
//   }
//   else if (::is_null(m2))
//   {
//
//      return ::std::strong_ordering::greater;
//
//   }
//   else if (s == 0)
//   {
//
//      return ::std::strong_ordering::equal;
//
//   }
//
//   return memcmp(m1, m2, s) <=> 0;
//
//}
//
//
//#endif // WINDOWS_DESKTOP


#include "framework.h"
#ifdef WINDOWS
//#include "_memory.h"
#else
#if defined(FREEBSD) || defined(OPENBSD)
#define _POSIX_C_SOURCE 200809L
#define _ANSI_SOURCE
#endif
#include <string.h>
#endif
////#include "acme/exception/exception.h"


CLASS_DECL_ACME void * memory_transfer(void * dst, const void * src, memsize iSize)
{

   if (::is_null(dst))
   {

      return nullptr;

   }

   if (iSize <= 0)
   {

      return dst;

   }
   else if (iSize > UINTPTR_MAX)
   {

      return nullptr;

   }

   if (::is_null(src))
   {

      return nullptr;

   }

   return memmove(dst, src, (size_t)iSize);

}


CLASS_DECL_ACME void * memory_set(void * p, int i, memsize iSize)
{

   if (iSize <= 0)
   {

      return p;

   }

   if (iSize > UINTPTR_MAX)
   {

      return nullptr;

   }

   if (::is_null(p))
   {

      return nullptr;

   }

   return ::memset(p, i, (size_t)iSize);
   //   uchar * puch = (uchar * ) p;
   //   while(iSize > 0)
   //   {
   //      *puch = static_cast < uchar > (i);
   //      puch++;
   //      iSize--;
   //   }
      //return p;
}


CLASS_DECL_ACME void * memory_and(void * p, const void * p1, const void * p2, memsize iSize)
{

   if (is_null(p)) return nullptr;
   if (is_null(p1)) return nullptr;
   if (is_null(p2)) return nullptr;

   unsigned char * pb = (unsigned char *)p;
   const unsigned char * pb1 = (const unsigned char *)p1;
   const unsigned char * pb2 = (const unsigned char *)p2;

   while (iSize > 0)
   {
      *pb = *pb1 & *pb2;
      pb++;
      pb1++;
      pb2++;
      iSize--;
   }

   return p;

}


CLASS_DECL_ACME void * memory_copy(void * dst, const void * src, memsize iSize)
{

   if (::is_null(dst))
   {

      return nullptr;

   }


   if (::is_null(src))
   {

      return nullptr;

   }

   if (iSize <= 0)
   {

      return dst;

   }
   else if (iSize > UINTPTR_MAX)
   {

      return nullptr;

   }

   uchar * puchDst = (uchar *)dst;

   uchar * puchSrc = (uchar *)src;

   if (puchDst == puchSrc)
   {

      return dst;

   }

   ::memcpy(dst, src, (size_t)iSize);

   return dst;

}


CLASS_DECL_ACME::std::strong_ordering memory_order(const void * p1, const void * p2, memsize iLen)
{

   if (iLen <= 0)
   {

      return ::std::strong_ordering::equal; // equal

   }
   else if (iLen > UINTPTR_MAX)
   {

      throw ::exception(error_bad_argument);

   }

   if (::is_null(p1))
   {

      if (::is_null(p2))
      {

         return ::std::strong_ordering::equal; // equal

      }
      else
      {

         return ::std::strong_ordering::less; // less

      }
   }
   else if (::is_null(p2))
   {

      return ::std::strong_ordering::greater; // equal;

   }

   return memcmp(p1, p2, (size_t)iLen) <=> 0;

}


CLASS_DECL_ACME::wide_character * wide_memory_copy(::wide_character * dst, const ::wide_character * src, memsize iSize)
{

   ::memory_copy(dst, src, iSize * sizeof(::wide_character));

   return dst;

}


CLASS_DECL_ACME void * reverse_memory(void * p, memsize iLen)
{

   if (::is_null(p))
   {

      return nullptr;

   }

   auto pleft = (unsigned char *)p;

   auto pright = pleft + iLen - 1;

   while (pleft < pright) ::swap(*pleft++, *pright--);

   return p;

}


CLASS_DECL_ACME void * reverse_memory_copy(void * dst, const void * src, memsize size)
{

   if (::is_null(dst))
   {

      return nullptr;

   }


   if (::is_null(src))
   {

      return nullptr;

   }

   if (size <= 0)
   {

      return dst;

   }
   else if (size > UINTPTR_MAX)
   {

      return nullptr;

   }

   char * pchDst = (char *)dst;

   const char * pchSrc = (const char *)src;

   memsize i = size - 1;

   while (true)
   {

      *pchDst = pchSrc[i];

      if (i == 0)
      {

         break;

      }

      pchDst++;

      i--;

   }

   return dst;

}






#if defined(_WIN32) || defined(__APPLE__) || defined(__BSD__)


const void * _memory_find(const void * l, memsize l_len, const void * s, memsize s_len)
{

   const unsigned char * cur;

   const unsigned char * last;

   const unsigned char * cl = (const unsigned char *)l;
   const unsigned char * cs = (const unsigned char *)s;

   /* the last position where its possible to find "s" in "l" */
   last = cl + l_len - s_len;

   for (cur = cl; cur <= last; cur++)
   {

      if (cur[0] == cs[0] && _memory_order(cur, cs, s_len) == 0)
      {

         return (const void *)cur;

      }

   }

   return nullptr;

}


#endif



