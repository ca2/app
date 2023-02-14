#include "framework.h"
#include "_c_memory.h"
////#include "acme/exception/exception.h"


CLASS_DECL_ACME void* __memmov(void * dst, const void * src, memsize iSize)
{

   if (::is_null(dst))
   {

      return nullptr;

   }

   if(iSize <= 0)
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

   return memmove(dst, src, (size_t) iSize);

}

void * memory_set(void * p, i32 i, memsize iSize)
{

   if (iSize <= 0)
   {

      return p;

   }

   if(iSize > UINTPTR_MAX)
   {

      return nullptr;

   }

   if (::is_null(p)) return nullptr;
   return memset(p, i, (size_t) iSize);
//   uchar * puch = (uchar * ) p;
//   while(iSize > 0)
//   {
//      *puch = static_cast < uchar > (i);
//      puch++;
//      iSize--;
//   }
   //return p;
}

void * __memand(void * p, const void * p1, const void * p2, memsize iSize)
{

   if (is_null(p)) return nullptr;
   if (is_null(p1)) return nullptr;
   if (is_null(p2)) return nullptr;

   u8 * pb = (u8 *) p;
   const u8 * pb1 = (const u8 *) p1;
   const u8 * pb2 = (const u8 *) p2;

   while(iSize > 0)
   {
      *pb = *pb1 & *pb2;
      pb++;
      pb1++;
      pb2++;
      iSize--;
   }

   return p;

}



void * memcpy_dup(void * dst, const void * src, memsize iSize)
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

   uchar * puchDst = (uchar * ) dst;

   uchar * puchSrc = (uchar * ) src;

   if (puchDst == puchSrc)
   {

      return dst;

   }

   ::memcpy(dst, src, (size_t) iSize);

   return dst;

}


void * memmov_dup(void * dst, const void * src, memsize iSize)
{

   __memmov(dst,  src, iSize);

   return dst;

}


::std::strong_ordering memory_order(const void * p1, const void * p2, memsize iLen)
{

   if (iLen <= 0)
   {

      return ::std::strong_ordering::equal; // equal

   }
   else if (iLen > UINTPTR_MAX)
   {

      throw ::exception(error_bad_argument);

   }

   if(::is_null(p1))
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
   else if(::is_null(p2))
   {

      return ::std::strong_ordering::greater; // equal;

   }

   return memcmp(p1, p2, (size_t) iLen) <=> 0;

}


::wide_character * wmemcpy_dup(::wide_character * dst, const ::wide_character * src, memsize iSize)
{

   ::memcpy_dup(dst, src, iSize * sizeof(::wide_character));

   return dst;

}


void * reverse_memory(void * p, memsize iLen)
{

   if (::is_null(p))
   {

      return nullptr;

   }

   auto pleft = (::byte *) p;

   auto pright = pleft + iLen - 1;

   while(pleft < pright) ::swap(*pleft++, *pright--);

   return p;

}


void * reverse_memcpy(void * dst, const void * src, memsize size)
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

   char * pchDst = (char *) dst;

   const char * pchSrc = (const char *) src;

   memsize i = size - 1;

   while(true)
   {

      *pchDst = pchSrc[i];

      if(i == 0)
      {

         break;

      }

      pchDst++;

      i--;

   }

   return dst;

}



