//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


#define HEAP_NAMESPACE_PREFIX main
#include "_____heap_namespace.h"


CLASS_DECL_ACME void* memory_allocate(memsize size)
{

   return ::HEAP_NAMESPACE::_memory_allocate(size);

}


CLASS_DECL_ACME void* memory_count_allocate(uptr count, memsize size)
{

   return ::HEAP_NAMESPACE::_memory_allocate(count * size);

}


CLASS_DECL_ACME void* memory_reallocate(void* p, memsize size)
{

   return ::HEAP_NAMESPACE::_memory_reallocate(p, size);

}


CLASS_DECL_ACME void memory_free(void* p)
{

   ::HEAP_NAMESPACE::_memory_free(p);

}


CLASS_DECL_ACME memsize memory_size(void* p)
{

   return ::HEAP_NAMESPACE::_memory_size(p);

}


CLASS_DECL_ACME void* memory_allocate_debug(memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return ::HEAP_NAMESPACE::_memory_allocate_debug(size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void* memory_reallocate_debug(void* p, memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return ::HEAP_NAMESPACE::_memory_reallocate_debug(p, size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void memory_free_debug(void* p, i32 nBlockUse)
{

   ::HEAP_NAMESPACE::_memory_free_debug(p, nBlockUse);

}


CLASS_DECL_ACME memsize memory_size_debug(void* p, i32 nBlockUse)
{

   return ::HEAP_NAMESPACE::_memory_size_debug(p, nBlockUse);

}

namespace HEAP_NAMESPACE
{

   void alloc_less_than_256()
   {


   }

   void alloc_256_or_more()
   {


   }


   void on_plex_new_block(::u32 nAllocSize)
   {


   }


   void on_plex_heap_alloc(plex_heap_alloc* palloc)
   {

      int iAllocSize = palloc->m_iAllocSize;

      if (iAllocSize < 256)
      {

         alloc_less_than_256();

      }
      else
      {

         alloc_256_or_more();

      }

   }
   void on_system_heap_alloc(memsize memsize)
   {


   }


} // namespace HEAP_NAMESPACE


#include "namespace_heap.inl"
#include "heap_namespace.inl"



