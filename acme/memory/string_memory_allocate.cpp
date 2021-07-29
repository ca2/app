// Created by camilo on 2021-07-23 21:53 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


#define HEAP_NAMESPACE_PREFIX string
#include "_____heap_namespace.h"


//CLASS_DECL_ACME void* string_memory_allocate(memsize size)
//{
//
//   return ::HEAP_NAMESPACE::_memory_allocate(size);
//
//}
//
//
//CLASS_DECL_ACME void* string_memory_count_allocate(uptr count, memsize size)
//{
//
//   return ::HEAP_NAMESPACE::_memory_allocate(count * size);
//
//}
//
//
//CLASS_DECL_ACME void* string_memory_reallocate(void* p, memsize size)
//{
//
//   return ::HEAP_NAMESPACE::_memory_reallocate(p, size);
//
//}
//
//
//CLASS_DECL_ACME void string_memory_free(void* p)
//{
//
//   ::HEAP_NAMESPACE::_memory_free(p);
//
//}
//
//
//
//CLASS_DECL_ACME memsize string_memory_size(void* p)
//{
//
//   return ::HEAP_NAMESPACE::_memory_size(p);
//
//}
//
//

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



