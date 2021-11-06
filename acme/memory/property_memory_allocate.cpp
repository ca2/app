// Created by camilo on 2021-07-25 01:30 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


#define HEAP_NAMESPACE_PREFIX property
#include "_____heap_namespace.h"


namespace HEAP_NAMESPACE
{

   void on_plex_heap_alloc(plex_heap_alloc* palloc)
   {


   }
   void on_system_heap_alloc(memsize memsize)
   {


   }

   void on_plex_new_block(::u32 nAllocSize)
   {


   }


} // namespace HEAP_NAMESPACE


#include "namespace_heap.inl"
#include "heap_namespace.inl"



