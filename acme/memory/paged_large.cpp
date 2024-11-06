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
int g_allocCount = 0;

int g_allocCountMid = 0;
int g_allocCountBig = 0;
#endif

void * paged_allocate(size_t size)
{
   if (size == 0)
      return 0;
#ifdef _SZ_ALLOC_DEBUG
   {
      void *point = malloc(size);
      fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", size, g_allocCount++, (unsigned int)int_point);
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
      fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", sizeNew, g_allocCount++, (unsigned int)int_point);
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
      fprintf(stderr, "\nFree; count = %10d,  addr = %8X", --g_allocCount, (unsigned int)address);
#endif
   free(address);
}



