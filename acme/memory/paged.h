//
//  paged.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/2022.
//  16:33:33
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#if defined(_WIN32) && !defined(UNIVERSAL_WINDOWS)

void SetLargePageSize();

#endif

CLASS_DECL_ACME void * paged_allocate(size_t size);
CLASS_DECL_ACME void * paged_reallocate(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_ACME void paged_free(void *address);
CLASS_DECL_ACME void * BigAlloc(size_t size);
CLASS_DECL_ACME void BigFree(void *address);

//#else
//
//#define paged_allocate(size) MyAlloc(size)
//#define page_reallocate(addr, sizeOld, sizeNew) MyRealloc(addr, sizeOld, sizeNew)
//#define paged_free(address) MyFree(address)
//#define BigAlloc(size) MyAlloc(size)
//#define BigFree(address) MyFree(address)
//
//#endif
