//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "heap.h"
#include "memory.h"
#include "acme/exception/interface_only.h"
#include "acme/memory/c_malloc.h"


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


   void * memory::allocate(memsize size)
   {

      return m_pheap->allocate(size);

   }


   void * memory::count_allocate(::count count, memsize size)
   {

      return m_pheap->count_allocate(count, size);

   }


   void * memory::reallocate(void * p, memsize size)
   {

      return m_pheap->reallocate(p, size);

   }


   void memory::free(void * p)
   {

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


   void * memory::allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
   {

      return m_pheap->allocate_debug(size, nBlockUse, szFileName,nLine);

   }


   void * memory::reallocate_debug(void * p, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
   {

      return m_pheap->reallocate_debug(p, size, nBlockUse, szFileName, nLine);
   }


   void memory::free_debug(void * p, i32 nBlockUse)
   {

      return m_pheap->free_debug(p, nBlockUse);

   }


   memsize memory::size_debug(void * p, i32 nBlockUse)
   {

      return m_pheap->size_debug(p, nBlockUse);


   }


   void * memory::aligned_allocate(memsize s, memsize align)
   {

      return m_pheap->aligned_allocate(s, align);

   }


   void * memory::aligned_allocate_debug(memsize s, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
   {

      return m_pheap->aligned_allocate_debug(s, nBlockUse, szFileName, nLine, align);

   }


   void * memory::unaligned_allocate(memsize s)
   {

      return m_pheap->unaligned_allocate(s);

   }


   void * memory::unaligned_allocate_debug(memsize s, i32 nBlockUse, const char * szFileName, i32 nLine)
   {

      return m_pheap->aligned_allocate_debug(s, nBlockUse, szFileName, nLine);

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


