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


CLASS_DECL_ACME void * paged_allocate(size_t size)
{
   
   return MyAlloc(size);
   
}


CLASS_DECL_ACME void * paged_reallocate(void * address, size_t sizeOld, size_t sizeNew)
{
   
   return MyRealloc(address, sizeOld, sizeNew);
   
}


CLASS_DECL_ACME void paged_free(void *address)
{
 
   return MyFree(address);
   
   
}


CLASS_DECL_ACME void * BigAlloc(size_t size)
{
   
   return MyAlloc(size);
   
}


CLASS_DECL_ACME void BigFree(void *address)
{
 
   return MyFree(address);
   
}



