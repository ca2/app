/* Alloc.ca -- Memory allocation functions
2008-09-24
Igor Pavlov
Public domain */
// from 7-zip on 2010-12-19
#include "framework.h"
#include "acme/_operating_system.h"
////#include "Alloc.h"

/* #define _SZ_ALLOC_DEBUG */

/* use _SZ_ALLOC_DEBUG to debug alloc/free operations */
#ifdef _SZ_ALLOC_DEBUG
i32 g_allocCount = 0;

i32 g_allocCountMid = 0;
i32 g_allocCountBig = 0;
#endif

void * paged_allocate(size_t size)
{
   if (size == 0)
      return 0;
#ifdef _SZ_ALLOC_DEBUG
   {
      void *point = malloc(size);
      fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", size, g_allocCount++, (u32)point_i32);
      return point;
   }
#else
   return malloc(size);
#endif
}

void * paged_reallocate(void * addr, size_t sizeOld, size_t sizeNew)
{
   if (sizeNew == 0)
      return addr;
#ifdef _SZ_ALLOC_DEBUG
   {
      void *point = realloc(addr, sizeNew);
      fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", sizeNew, g_allocCount++, (u32)point_i32);
      return point;
   }
#else
   return realloc(addr, sizeNew);
#endif
}

void paged_free(void * address)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree; count = %10d,  addr = %8X", --g_allocCount, (u32)address);
#endif
   free(address);
}



