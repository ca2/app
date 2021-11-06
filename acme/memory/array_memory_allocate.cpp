//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


#define HEAP_NAMESPACE_PREFIX array
#include "_____heap_namespace.h"


// debugging helpers
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



