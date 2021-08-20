

#if !defined(MCHECK) && !defined(_VLD) && !defined(__MCRTDBG) && !MEMDLEAK


#include "acme/memory/heap_memory.h"


void * aligned_memory_allocate(memsize size, memsize align)
{

   void * paligned;

   align = align <= 0 ? ALIGN_BYTE_COUNT : align;

   auto sizeProvision = heap_memory_aligned_provision_get_size(size, (int) align);

   if(g_pheap == nullptr)
   {

      void * p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 128, (int)align, HEAP_ENUMERATE);

   }
   else
   {

      void * p = g_pheap->_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 0, (int)align, HEAP_ENUMERATE);

   }

   return paligned;

}


void * unaligned_memory_allocate(memsize size)
{

   void * punaligned;

#if defined(__APPLE__) || defined(LINUX)

   punaligned = aligned_memory_allocate(size);

#else

   auto sizeProvision = heap_memory_unaligned_provision_get_size(size);

   if (g_pheap == nullptr)
   {

      void* p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      punaligned = heap_memory_unaligned(p, size, 129, HEAP_ENUMERATE);

   }
   else
   {

      void* p = g_pheap->_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      punaligned = heap_memory_unaligned(p, size, 1, HEAP_ENUMERATE);

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
   if(g_pheap == nullptr)
   {

      void * p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 130, (int)align, HEAP_ENUMERATE);

      memset(paligned, 0, size);

   }
   else
   {

      void * p = g_pheap->alloc_debug(sizeProvision, nBlockUse, szFileName, nLine);

      if (p == nullptr)
      {

         return nullptr;

      }

      paligned = heap_memory_aligned(p, size, 2, (int)align, HEAP_ENUMERATE);

   }

   return paligned;

}


void * unaligned_memory_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   void* punaligned;

#if defined(__APPLE__) || defined(LINUX)

   punaligned = aligned_memory_allocate(size);

#else

   auto sizeProvision = heap_memory_unaligned_provision_get_size(size);

   if (g_pheap == nullptr)
   {

      void* p = system_heap_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      punaligned = heap_memory_unaligned(p, size, 131, HEAP_ENUMERATE);

   }
   else
   {

      void* p = g_pheap->_alloc(sizeProvision);

      if (p == nullptr)
      {

         return nullptr;

      }

      punaligned = heap_memory_unaligned(p, size, 3, HEAP_ENUMERATE);

   }

#endif

   return punaligned;


}


#undef memory_allocate


void * _memory_allocate(memsize size)
{

//#if defined(__APPLE__) || defined(RASPBIAN) || defined(WINDOWS)

   return aligned_memory_allocate(size);

//#else

//   return unaligned_memory_allocate(size);

//#endif

}


void * _memory_allocate_no_track(memsize size)
{

//#if defined(__APPLE__) || defined(RASPBIAN)

   return aligned_memory_allocate(size);

//#else

//   return unaligned_memory_allocate(size);

//#endif

}


void * _memory_count_allocate(memsize size, memsize bytes)
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

   heap_memory* pheapmemory = heap_memory_get(pmemory);

   if (pheapmemory->m_ememoryheap != HEAP_ENUMERATE)
   {

      return manage_memory_reallocate(pheapmemory->m_ememoryheap, pmemory, size);

   }

   byte blockuse = pheapmemory->m_blockuse;

   memsize sizeOld = pheapmemory->m_size;

   byte align = pheapmemory->m_align;

   void * p = heap_memory_base_get(pmemory);

   if(blockuse == 0) // aligned
   {

      p = g_pheap->_realloc(
         p, 
         heap_memory_aligned_provision_get_size(size, align), 
         heap_memory_aligned_provision_get_size(sizeOld, align), 
         align);

   }
   else if(blockuse == 1) // unaligned
   {

      //TODO: to do the dbg version

      p = g_pheap->_realloc(
         p,
         heap_memory_unaligned_provision_get_size(size), 
         heap_memory_unaligned_provision_get_size(sizeOld),
         0);

   }
   else if(blockuse == 128) // aligned
   {

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if(blockuse == 129) // unaligned
   {

      //TODO: to do the dbg version

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_unaligned_provision_get_size(size));

   }
   else if(blockuse == 2) // aligned
   {

      p = g_pheap->realloc_debug(
         p,
         heap_memory_aligned_provision_get_size(size, align), 
         heap_memory_aligned_provision_get_size(sizeOld, align),
         align, nBlockUse, szFileName, nLine);

   }
   else if(blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      p = g_pheap->realloc_debug(
         p, 
         heap_memory_unaligned_provision_get_size(size), 
         heap_memory_unaligned_provision_get_size(sizeOld),
         0,nBlockUse,szFileName,nLine);

   }
   else if (blockuse == 130) // aligned
   {

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if (blockuse == 131) // unaligned
   {

      //TODO: to do the dbg version

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_unaligned_provision_get_size(size));

   }
   else
   {

      __throw(error_exception);

   }

   if(p == nullptr)
   {

      return nullptr;

   }

   if(blockuse == 0 || blockuse == 2 || blockuse == 128 || blockuse == 130) // aligned
   {

      return heap_memory_aligned(p, size, blockuse, align, HEAP_ENUMERATE);

   }
   else if (blockuse == 1 || blockuse == 3 || blockuse == 129 || blockuse == 131) // unaligned
   {

      return heap_memory_unaligned(p, size, blockuse, HEAP_ENUMERATE);

   }
   else
   {

      __throw(error_exception);

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

   if (pheapmemory->m_ememoryheap != HEAP_ENUMERATE)
   {

      manage_memory_free(pheapmemory->m_ememoryheap, pmemory);

      return;

   }

   void * p = (void *)(((iptr)pmemory) - pheapmemory->m_back);

#ifdef __DEBUG

   heap_memory_check_padding_after(pheapmemory);

#endif // !__DEBUG

   if(pheapmemory->m_blockuse == 0)
   {

      memsize iAlignedSize = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);

      if(g_pheap)
      {

         g_pheap->_free(p, iAlignedSize);

      }

   }
   else if(pheapmemory->m_blockuse == 1)
   {

      //TODO: to do the dbg version

      if(g_pheap)
      {

         g_pheap->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));

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

      memsize sizeProvision = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);

      g_pheap->free_debug(p, sizeProvision);

   }
   else if(pheapmemory->m_blockuse == 3)
   {

      //TODO: to do the dbg version

      g_pheap->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));

   }
   else
   {

      system_heap_free(p);

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



