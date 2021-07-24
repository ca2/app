

#include "acme/platform/static_start_internal.h"


#include "acme/memory/aligned_memory_allocate.h"


#include "acme/memory/_memory_allocate.h"


#if !defined(MCHECK) && !defined(_VLD) && !defined(__MCRTDBG) && !MEMDLEAK


#include "acme/memory/heap_memory.h"


void * aligned_memory_allocate(memsize size, memsize align)
{

   void * paligned;

   align = align <= 0 ? ALIGN_BYTE_COUNT : align;

   auto sizeProvision = heap_memory_aligned_provision_get_size(size, (int) align);

   if(::acme::g_pheap == nullptr)
   {

      void * p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 128, (int)align);

   }
   else
   {

      if (sizeProvision == 831 && sizeProvision < 1024)
      {

         //output_debug_string("*");

      }

      void * p = ::acme::g_pheap->_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 0, (int)align);

   }

   return paligned;

}


void * unaligned_memory_allocate(memsize size)
{

   void * punaligned;

#if defined(APPLEOS) || defined(LINUX)

   punaligned = aligned_memory_allocate(size);

#else

   void * p = nullptr;

   if (::acme::g_pheap == nullptr)
   {

      p = system_heap_alloc(size);

   }
   else
   {

      p = ::acme::g_pheap->_alloc(heap_memory_unaligned_provision_get_size(size));

   }

   if (p == nullptr)
   {

      return nullptr;

   }
   else
   {

      punaligned = heap_memory_unaligned(p, size, 2);

   }

#endif

   return punaligned;

}


void * aligned_memory_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
{

   void * paligned;

   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   align = align <= 0 ? ALIGN_BYTE_COUNT : align;

   auto sizeProvision = heap_memory_aligned_provision_get_size(size, (int) align);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_debug(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
   if(::acme::g_pheap == nullptr)
   {

      void * p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 129, (int)align);

      memset(paligned, 0, size);

   }
   else
   {

      void * p = ::acme::g_pheap->alloc_debug(sizeProvision, nBlockUse, szFileName, nLine);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 1, (int)align);

   }

   return paligned;

}


void * unaligned_memory_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   void * punaligned;

#if defined(APPLEOS) || defined(RASPBIAN)

   punaligned = aligned_memory_allocate(size);

#else

   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_debug(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);

   void * p = nullptr;

   if (::acme::g_pheap == nullptr)
   {

      p = system_heap_alloc(heap_memory_unaligned_provision_get_size(size));

      nBlockUse = 128;

   }
   else
   {

      p = ::acme::g_pheap->alloc_debug(heap_memory_unaligned_provision_get_size(size), nBlockUse, szFileName, nLine);

      nBlockUse = 3;

   }

   if (p == nullptr)
   {

      return nullptr;

   }

   punaligned = heap_memory_unaligned(p, size, nBlockUse);

#endif

   //zero(p, size);

   return punaligned;

}


#undef memory_allocate

void * _memory_allocate(memsize size)
{

//#if defined(APPLEOS) || defined(RASPBIAN) || defined(WINDOWS)

   return aligned_memory_allocate(size);

//#else

//   return unaligned_memory_allocate(size);

//#endif

}


void * memory_allocate_no_track(memsize size)
{

//#if defined(APPLEOS) || defined(RASPBIAN)

   return aligned_memory_allocate(size);

//#else

//   return unaligned_memory_allocate(size);

//#endif

}


void * memory_calloc(memsize size, memsize bytes)
{

   return memory_allocate(size * bytes);

}


void * _memory_allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{

  // return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

   return aligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

}


void * _memory_reallocate(void * pmemory, memsize nSize)
{

   return _memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);

}


void * _memory_reallocate_debug(void * pmemory, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   if (pmemory == nullptr)
   {

      return _memory_allocate_debug(size, nBlockUse, szFileName, nLine);

   }

   byte blockuse = heap_memory_get_block_use(pmemory);

   memsize sizeOld = heap_memory_get_size(pmemory);

   byte align = heap_memory_get_align(pmemory);

   void * p = nullptr;

   if(blockuse == 0) // aligned
   {

      p = ::acme::g_pheap->_realloc(
         heap_memory_base_get(pmemory), 
         heap_memory_aligned_provision_get_size(size, align), 
         heap_memory_aligned_provision_get_size(sizeOld, align), 
         align);

   }
   else if(blockuse == 1) // aligned
   {

      //TODO: to do the dbg version

      p = ::acme::g_pheap->realloc_debug(heap_memory_base_get(pmemory), heap_memory_aligned_provision_get_size(size, align), heap_memory_aligned_provision_get_size(sizeOld,align), align, nBlockUse,szFileName,nLine);

   }
   else if(blockuse == 128) // aligned
   {

      p = realloc(heap_memory_base_get(pmemory),(size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if(blockuse == 129) // aligned
   {

      //TODO: to do the dbg version

      p = realloc(heap_memory_base_get(pmemory),(size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if(blockuse == 2) // unaligned
   {

      p = ::acme::g_pheap->_realloc(heap_memory_base_get(pmemory), heap_memory_unaligned_provision_get_size(size), heap_memory_unaligned_provision_get_size(sizeOld),0);

   }
   else if(blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      p = ::acme::g_pheap->realloc_debug(heap_memory_base_get(pmemory), heap_memory_unaligned_provision_get_size(size), heap_memory_unaligned_provision_get_size(sizeOld),0,nBlockUse,szFileName,nLine);

   }
   else
   {

      return realloc(pmemory, size);

   }

   if(p == nullptr)
   {

      return nullptr;

   }

   if(blockuse == 0 || blockuse == 1 || blockuse == 128 || blockuse == 129) // aligned
   {

      return heap_memory_aligned(p, size, blockuse, align);

   }
   else
   {

      return heap_memory_unaligned(p, size, blockuse);

   }

   return nullptr;

}


void _memory_free(void * pmemory)
{

   return _memory_free_debug(pmemory, 0);

}


void _memory_free_debug(void * pmemory, i32 iBlockType)
{

   if((iptr) pmemory < 1024)
   {

      return;

   }

   heap_memory * pheapmemory = heap_memory_get(pmemory);

   void * p = (void *)(((iptr)pmemory) - pheapmemory->m_back);

#ifdef __DEBUG

   heap_memory_check_padding_after(pheapmemory);

#endif // !__DEBUG

   if(pheapmemory->m_blockuse == 0)
   {

      memsize iAlignedSize = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);

      if(::acme::g_pheap)
      {

         ::acme::g_pheap->_free(p, iAlignedSize);

      }

   }
   else if(pheapmemory->m_blockuse == 1)
   {

      //TODO: to do the dbg version

      if(::acme::g_pheap)
      {

         ::acme::g_pheap->free_debug(p, heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align));

      }

   }
   else if(pheapmemory->m_blockuse == 128)
   {

      system_heap_free(p);

   }
   else if(pheapmemory->m_blockuse == 129)
   {

      //TODO: to do the dbg version

      system_heap_free(p);

   }
   else if(pheapmemory->m_blockuse == 2)
   {

      memsize iUnalignedSize = heap_memory_unaligned_provision_get_size(pheapmemory->m_size);

      ::acme::g_pheap->_free(p, iUnalignedSize);

   }
   else if(pheapmemory->m_blockuse == 3)
   {

      //TODO: to do the dbg version

      ::acme::g_pheap->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));

   }
   else
   {

      free(pmemory);

   }

}


memsize _memory_size(void * pmemory)
{

   return _memory_size_debug(pmemory, _NORMAL_BLOCK);

}


memsize _memory_size_debug(void * pmemory, i32 iBlockType)
{

   if (pmemory == nullptr)
   {

      return 0;

   }

   return heap_memory_get_size(pmemory);

}


#endif



