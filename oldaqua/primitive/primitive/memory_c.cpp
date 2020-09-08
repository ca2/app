#include "framework.h"


CLASS_DECL_AQUA void* __memmov(void * dst, const void * src, memsize iSize)
{

   if (::is_null(dst))
   {

      return nullptr;

   }

   if(iSize <= 0)
   {

      return dst;

   }
   else if (iSize > MAXUINT_PTR)
   {

      return nullptr;

   }

   if (::is_null(src))
   {

      return nullptr;

   }

   return memmove(dst, src, (size_t) iSize);

}

void * __memset(void * p, i32 i, memsize iSize)
{

   if (iSize <= 0)
   {

      return p;

   }

   if(iSize > MAXINT_PTR)
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
   else if (iSize > MAXUINT_PTR)
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


i32 __memcmp(const void * p1, const void * p2, memsize iLen)
{

   if (iLen <= 0)
   {

      return 0; // equal

   }
   else if (iLen > MAXUINT_PTR)
   {

      throw invalid_argument_exception();

   }

   if(::is_null(p1))
   {

      if (::is_null(p2))
      {

         return 0;

      }
      else
      {

         return -1;

      }
   }
   else if(::is_null(p2))
   {

      return 1;

   }

   return memcmp(p1, p2, (size_t) iLen);

}


widechar * wmemcpy_dup(widechar * dst, const widechar * src, memsize iSize)
{

   ::memcpy_dup(dst, src, iSize * sizeof(widechar));

   return dst;

}


void * reverse_memory(void * p, memsize iLen)
{

   if (::is_null(p))
   {

      return nullptr;

   }

   char * sz = (char *) p;

   ::count iMid = iLen / 2;

   ::count iL = 0;

   ::count iR = iLen - 1;

   char ch;

   for(; iL < iMid; iL++, iR--)
   {

      ch = sz[iL];

      sz[iL] = sz[iR];

      sz[iR] = ch;

   }

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
   else if (size > MAXUINT_PTR)
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



