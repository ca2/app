/* Alloc.ca -- Memory allocation functions
2008-09-24
Igor Pavlov
Public domain */
// from 7-zip on 2010-12-19
#include "framework.h"
#include "acme/operating_system.h"

////#include "Alloc.h"

/* #define _SZ_ALLOC_DEBUG */

/* use _SZ_ALLOC_DEBUG to debug alloc/free operations */
#ifdef _SZ_ALLOC_DEBUG
i32 g_allocCount = 0;
i32 g_allocCountMid = 0;
i32 g_allocCountBig = 0;
#endif

void * MyAlloc(size_t size)
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

void * MyRealloc(void * addr, size_t sizeOld, size_t sizeNew)
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

void MyFree(void * address)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree; count = %10d,  addr = %8X", --g_allocCount, (u32)address);
#endif
   free(address);
}

#if defined(_WIN32) && !defined(_UWP)

void * MidAlloc(size_t size)
{
   if (size == 0)
      return 0;
#ifdef _SZ_ALLOC_DEBUG
   fprintf(stderr, "\nAlloc_Mid %10d bytes;  count = %10d", size, g_allocCountMid++);
#endif
   return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
}

void * MidRealloc(void * address, size_t sizeOld, size_t sizeNew)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree_Mid; count = %10d", --g_allocCountMid);
#endif
   if (address == 0)
      return ::MidAlloc(sizeNew);
   u8 * pnew = (u8 *) ::MidAlloc(sizeNew);
   if(pnew == nullptr)
   {
      MidFree(address);
      return nullptr;
   }
   ::memcpy_dup(pnew, address, minimum(sizeOld, sizeNew));
   MidFree(address);
   return pnew;
}

void MidFree(void * address)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree_Mid; count = %10d", --g_allocCountMid);
#endif
   if (address == 0)
      return;
   VirtualFree(address, 0, MEM_RELEASE);
}

#ifndef MEM_LARGE_PAGES
#undef _7ZIP_LARGE_PAGES
#endif

#ifdef _7ZIP_LARGE_PAGES
SIZE_T g_LargePageSize = 0;
typedef SIZE_T (WINAPI *GetLargePageMinimumP)();
#endif

void SetLargePageSize()
{
#ifdef _7ZIP_LARGE_PAGES
   SIZE_T size = 0;
   GetLargePageMinimumP largePageMinimum = (GetLargePageMinimumP)
                                           GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetLargePageMinimum");
   if (largePageMinimum == 0)
      return;
   size = largePageMinimum();
   if (size == 0 || (size & (size - 1)) != 0)
      return;
   g_LargePageSize = size;
#endif
}


void *BigAlloc(size_t size)
{
   if (size == 0)
      return 0;
#ifdef _SZ_ALLOC_DEBUG
   fprintf(stderr, "\nAlloc_Big %10d bytes;  count = %10d", size, g_allocCountBig++);
#endif

#ifdef _7ZIP_LARGE_PAGES
   if (g_LargePageSize != 0 && g_LargePageSize <= (1 << 30) && size >= (1 << 18))
   {
      void *res = VirtualAlloc(0, (size + g_LargePageSize - 1) & (~(g_LargePageSize - 1)),
                               MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
      if (res != 0)
         return res;
   }
#endif
   return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
}

void BigFree(void *address)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree_Big; count = %10d", --g_allocCountBig);
#endif

   if (address == 0)
      return;
   VirtualFree(address, 0, MEM_RELEASE);
}

#endif


