//
//  paged.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/2022.
//  16:33
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "paged.h"


#include "acme/_operating_system.h"



void * paged_allocate(size_t size)
{
   if (size == 0)
      return 0;
#ifdef _SZ_ALLOC_DEBUG
   fprintf(stderr, "\nAlloc_Mid %10d bytes;  count = %10d", size, g_allocCountMid++);
#endif
   return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
}


void * paged_reallocate(void * address, size_t sizeOld, size_t sizeNew)
{
#ifdef _SZ_ALLOC_DEBUG
   if (address != 0)
      fprintf(stderr, "\nFree_Mid; count = %10d", --g_allocCountMid);
#endif
   if (address == 0)
      return ::paged_allocate(sizeNew);
   u8 * pnew = (u8 *) ::paged_allocate(sizeNew);
   if(pnew == nullptr)
   {
      paged_free(address);
      return nullptr;
   }
   ::memory_copy(pnew, address, minimum(sizeOld, sizeNew));
   paged_free(address);
   return pnew;
}

void paged_free(void * address)
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

