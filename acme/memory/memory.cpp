//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "heap.h"
#include "memory.h"
#include "acme/exception/interface_only.h"
#include "acme/memory/c_malloc.h"
#include "acme/_operating_system.h"

//#define HEAP_NAMESPACE_PREFIX main
//#include "_____heap_namespace.h"
//
namespace heap
{

   //memory::memory(::heap::heap * pheap) :
   //   m_pheap(pheap)
   memory::memory()
   {

      //m_pheap = plex_heap_alloc_array::new_plex_heap_alloc_array(pallocator);

   }


   memory::~memory()
   {

      ::c::malloc::destroy(m_pheap);

      
      //plex_heap_alloc_array::delete_plex_heap_alloc_array(m_pheap);

      //m_pallocator->free(m_pheap);

   }

   void memory::initialize_memory(::heap::heap * pheap)
      
   {

      m_pheap = pheap;

      //m_pheap = plex_heap_alloc_array::new_plex_heap_alloc_array(pallocator);

   }


   void memory::start_memory()
   {

      m_pheap->start_heap();

   }


   void * memory::allocate(memsize size, memsize * psizeAllocated, const char * pszAnnotation)
   {

      return m_pheap->allocate(size, psizeAllocated, pszAnnotation);

   }


   void * memory::count_allocate(::collection::count count, memsize size, const char * pszAnnotation)
   {

      return m_pheap->count_allocate(count, size, pszAnnotation);

   }


   void * memory::reallocate(void * p, memsize size, const char * pszAnnotation)
   {

      return m_pheap->reallocate(p, size, pszAnnotation);

   }

   ::i64 g_iDebugMemoryA = 0;

   void memory::free(void * p)
   {

#if 0

      auto i = g_iDebugMemoryA;

      g_iDebugMemoryA++;

      if (i >= 1510)
      {

         char sz[1024];
         
         sprintf(sz, "heap::memory::free %06lld 0x%016llx\n", i, p);

         ::OutputDebugStringA(sz);

      }
      else
      {

         char sz[1024];

         sprintf(sz, "heap::memory::free %06lld 0x%016llx\n", i, p);

         ::OutputDebugStringA(sz);

      }

#endif

      return m_pheap->free(p);

   }


   bool memory::has_size() const
   {

      return true;

   }


   memsize memory::size(void * p)
   {

      return m_pheap->size(p);

   }


   void * memory::allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation)
   {

      return m_pheap->allocate_debug(size, nBlockUse, szFileName, nLine, pszAnnotation);

   }


   void * memory::reallocate_debug(void * p, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation)
   {

      return m_pheap->reallocate_debug(p, size, nBlockUse, szFileName, nLine, pszAnnotation);
   }


   void memory::free_debug(void * p, i32 nBlockUse)
   {

      return m_pheap->free_debug(p, nBlockUse);

   }


   memsize memory::size_debug(void * p, i32 nBlockUse)
   {

      return m_pheap->size_debug(p, nBlockUse);


   }


   void * memory::aligned_allocate(memsize s, memsize * psizeAllocated, memsize align, const char * pszAnnotation)
   {

      return m_pheap->aligned_allocate(s, psizeAllocated, align, pszAnnotation);

   }


   void * memory::aligned_allocate_debug(memsize s, memsize * psizeAllocated, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align, const char * pszAnnotation)
   {

      return m_pheap->aligned_allocate_debug(s, psizeAllocated, nBlockUse, szFileName, nLine, align, pszAnnotation);

   }


   void * memory::unaligned_allocate(memsize s, memsize * psizeAllocated, const char * pszAnnotation)
   {

      return m_pheap->unaligned_allocate(s, psizeAllocated, pszAnnotation);

   }


   void * memory::unaligned_allocate_debug(memsize s, memsize * psizeAllocated, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation)
   {

      return m_pheap->aligned_allocate_debug(s, psizeAllocated, nBlockUse, szFileName, nLine, 0, pszAnnotation);

   }


   memory * management::_new_memory(enum_memory ememory)
   {

      return ::c::malloc::create< ::heap::memory >();

   }

   memory * management::new_memory(enum_memory ememory)
   {

      auto p = _new_memory(ememory);

      p->initialize_memory(new_heap(::heap::e_heap_default, ememory));

      return p;

   }

   //void memory::free_debug(void * p, i32 nBlockUse)
   //{

   //   return m_pheap->free_debug(p, nBlockUse);

   //}


   //memsize memory::size_debug(void * p, i32 nBlockUse)
   //{

   //   return m_pheap->size_debug(p, nBlockUse);

   //}


//   namespace HEAP_NAMESPACE
//   {
//
//      void alloc_less_than_256()
//      {
//
//
//      }
//
//      void alloc_256_or_more()
//      {
//
//
//      }
//
//
//      void on_plex_new_block(::u32 nAllocSize)
//      {
//
//
//      }
//
//
//      void on_plex_heap_alloc(plex_heap_alloc * palloc)
//      {
//
//         int iAllocSize = palloc->m_iAllocSize;
//
//         if (iAllocSize < 256)
//         {
//
//            alloc_less_than_256();
//
//         }
//         else
//         {
//
//            alloc_256_or_more();
//
//         }
//
//      }
//      void on_system_heap_alloc(memsize memsize)
//      {
//
//
//      }
//
////
//   }
////
////
////#include "namespace_heap.inl"
////#include "heap_namespace.inl"
//


} // namespace heap


