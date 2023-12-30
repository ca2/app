//
//  simple_allocate.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/12/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "allocation.h"
#include "align_byte_count.h"


void * simple_memory_allocate(size_t s)
{
   
   auto s2 = heap_memory_aligned_provision_get_size(s, ALIGN_BYTE_COUNT);
   
   auto p = malloc(s2);
   
   auto p2 = heap_memory_aligned(p, s, 0, ALIGN_BYTE_COUNT, ::heap::e_memory_simple);
   
   return p2;
   
}


void * simple_memory_reallocate(void * p2, size_t s)
{
   
   auto pheapmemory = heap_memory_get(p2);
   
   if(pheapmemory->m_ememory == ::heap::e_memory_simple)
   {
      
      void * p = (void *)(((iptr)p2) - pheapmemory->m_back);
      
      auto s2 = heap_memory_aligned_provision_get_size(s, ALIGN_BYTE_COUNT);
      
      auto prealloc = ::realloc(p, s2);
      
      auto prealloc2 = heap_memory_aligned(prealloc, s, 0, ALIGN_BYTE_COUNT, ::heap::e_memory_simple);
      
      return prealloc2;

   }
   else
   {
      
      return ::acme::get()->m_pheapmanagement->memory(pheapmemory->m_ememory)->reallocate(p2, s);

   }
   
}


void simple_memory_free(void * p2)
{

   if(::is_null(p2))
   {

      return;

   }
   
   auto pheapmemory = heap_memory_get(p2);
   
   if(pheapmemory->m_ememory == ::heap::e_memory_simple)
   {
      
      void * p = (void *)(((iptr)p2) - pheapmemory->m_back);
      
      ::free(p);
      
   }
   else
   {

      ::acme::get()->m_pheapmanagement->memory(pheapmemory->m_ememory)->free(p2);

   }
   
}


memsize simple_memory_size(void * p2)
{
   
   auto pheapmemory = heap_memory_get(p2);
   
   return pheapmemory->m_size;

}



