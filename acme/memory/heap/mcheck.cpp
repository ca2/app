#include "framework.h"




//
//#ifdef MEMCHECK
//
//#include "heap_memory.h"
//
//
//
//
//
//
//#if AXIS_MEMORY_MANAGEMENT
//
//
//#if !defined(__VLD) && !defined(__MCRTDBG)
//void * aligned_memory_allocate(size_t size, memsize align)
//{
//
//   void * p;
//
//   align = align <= 0 ? ALIGN_BYTE_COUNT : align;
//
//#if defined(MCHECK)
//
//   p = aligned_alloc(align, size);
//
//#elif MEMDLEAK
//
//   throw todo();
//
//   p = unaligned_memory_allocate(size);
//
//#else
//
//   if(g_pheap == nullptr)
//   {
//
//      void * pusermessage = system_heap_alloc(heap_memory::aligned_provision_get_size(size, align));
//
//      if (pusermessage == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      p = heap_memory::aligned(pusermessage, size, 128, align);
//
//   }
//   else
//   {
//
//      if (heap_memory::aligned_provision_get_size(size) == 831
//            && heap_memory::aligned_provision_get_size(size) < 1024)
//      {
//         //informationf("*");
//      }
//
//      void * pusermessage = g_pheap->_alloc(heap_memory::aligned_provision_get_size(size, align));
//
//      if (pusermessage == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      p = heap_memory::aligned(pusermessage, size, 0, align);
//
//   }
//
//#endif
//
//   //zero(p, size);
//
//   return p;
//
//}
//
//void * unaligned_memory_allocate(size_t size)
//{
//
//   void * p;
//
//#if defined(MCHECK)
//
//   p =  malloc(size);
//
//#elif MEMDLEAK
//   size_t nAllocSize = size + sizeof(memdleak_block);
//
//   memdleak_block * pblock;
//
//   pblock = (memdleak_block *) class ::system_heap_alloc(nAllocSize);
//
//   pblock->m_iBlockUse = 0;
//
//   if (g_ee == nullptr)
//   {
////      pblock->m_puiStack = nullptr;
//      pblock->m_iStack = 0;
//      pblock->m_pszFileName = nullptr;
//   }
//   else
//   {
//      //string strCallStack;
//      //g_ee->xxxstack_trace(1);
//      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
//      g_ee->backtrace(pblock->m_puiStack, pblock->m_iStack);
//      pblock->m_pszFileName = nullptr;
//      //pblock->m_pszFileName = strdup(scopedstrFileName); // not trackable, at least think so certainly causes memory leak
//   }
//
//   ::acme::set_maximum(pblock->m_uiLine);
//
//   pblock->m_size = nAllocSize;
//
//   synchronous_lock lock(g_pmutgen);
//
//   pblock->m_pprevious = nullptr;
//
//   pblock->m_pnext = s_pmemdleakList;
//
//   if (s_pmemdleakList != nullptr)
//   {
//
//      s_pmemdleakList->m_pprevious = pblock;
//
//   }
//
//   s_pmemdleakList = pblock;
//
//   t_plastblock = pblock;
//
//   lock.unlock();
//
//   p = &pblock[1];
//
//
//#else
//
//#if defined(__APPLE__) || defined(LINUX)
//
//   p = aligned_memory_allocate(size);
//
//#else
//
//   void * pusermessage = g_pheap->_alloc(heap_memory::unaligned_provision_get_size(size));
//
//   if (pusermessage == nullptr)
//   {
//
//      return nullptr;
//
//   }
//   else
//   {
//
//      p = heap_memory::unaligned(pusermessage, size, 2);
//
//   }
//
//#endif
//
//#endif
//
//   //zero(p, size);
//
//   return p;
//
//}
//
//
//void * aligned_memory_allocate_debug(size_t size, int nBlockUse, const char * szFileName, int nLine, memsize align)
//{
//
//   void * p;
//
//   align = align <= 0 ? ALIGN_BYTE_COUNT : align;
//
//#if defined(MCHECK)
//
//   p = aligned_alloc(align, size);
//
//#elif MEMDLEAK
//
//   throw_todo();
//
//   p = unaligned_memory_allocate(size);
//
//#else
//
//   __UNREFERENCED_PARAMETER(nBlockUse);
//   __UNREFERENCED_PARAMETER(szFileName);
//   __UNREFERENCED_PARAMETER(nLine);
//
//   //TODO: to do the dbg version
//   //unsigned char * p = (unsigned char *) _system_heap_alloc_debug(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
//   if(g_pheap == nullptr)
//   {
//
//      void * pusermessage = system_heap_alloc(heap_memory::aligned_provision_get_size(size, align));
//
//      if (pusermessage == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      p = heap_memory::aligned(pusermessage, size, 129, align);
//
//   }
//   else
//   {
//
//      void * pusermessage = g_pheap->alloc_debug(heap_memory::aligned_provision_get_size(size, align), nBlockUse, szFileName, nLine);
//
//      if (pusermessage == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      p = heap_memory::aligned(pusermessage, size, 1, align);
//
//   }
//
//#endif
//
//   //zero(p, size);
//
//   return p;
//
//}
//
//
//void * unaligned_memory_allocate_debug(size_t size, int nBlockUse, const char * szFileName, int nLine)
//{
//
//   void * p;
//
//#if defined(MCHECK)
//
//   return malloc(size);
//
//#elif MEMDLEAK
//
//   p = unaligned_memory_allocate(size);
//
//#else
//
//
//#ifdef __APPLE__
//
//   p = aligned_memory_allocate(size);
//
//#else
//
//   __UNREFERENCED_PARAMETER(nBlockUse);
//   __UNREFERENCED_PARAMETER(szFileName);
//   __UNREFERENCED_PARAMETER(nLine);
//
//   //TODO: to do the dbg version
//   //unsigned char * p = (unsigned char *) _system_heap_alloc_debug(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
//   void * pusermessage = g_pheap->alloc_debug(heap_memory::unaligned_provision_get_size(size), nBlockUse, szFileName, nLine);
//
//   if (pusermessage == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   p = heap_memory::unaligned(pusermessage, size, 3);
//
//#endif
//
//#endif
//
//   //zero(p, size);
//
//   return p;
//
//}
//
//
//#endif
//
//#if !defined(__VLD) && !defined(__MCRTDBG)
//
//
//
//
//#if !defined(MCHECK)
//
//#undef ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
//
//void * ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(memsize size)
//{
//
//#if defined(__APPLE__)
//
//   return aligned_memory_allocate(size);
//
//#else
//
//   return unaligned_memory_allocate(size);
//
//#endif
//
//}
//
//#undef ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
//
//#endif
//
//
//void * memory_allocate_no_track(size_t size)
//{
//
//#if defined(MCHECK) || defined(__VLD) || defined(__MCRTDBG)
//
//   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(size);
//
//#else
//
//#if defined(__APPLE__)
//
//   return aligned_memory_allocate(size);
//
//#else
//
//   return unaligned_memory_allocate(size);
//
//#endif
//
//#endif
//
//}
//
//
//
//
//void * memory_calloc(size_t size, size_t bytes)
//{
//
//   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(size * bytes);
//
//}
//
//
//void * memory_allocate_debug(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
//{
//#ifdef MCHECK
//   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nSize);
//#else
//   return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);
//#endif
//
//}
//
//#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)
//
//void * memory_reallocate(void * pmemory, size_t nSize)
//{
//
//   return memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);
//
//}
//#endif
//
//
//
//
//
//
//void * memory_reallocate_debug(void * pmemory, size_t size, int nBlockUse, const char * szFileName, int nLine)
//{
//
//#if defined(__VLD)
//
//   return realloc(pmemory, size);
//
//#elif defined(__MCRTDBG)
//
//   return _realloc_debug(pmemory, size, _NORMAL_BLOCK, szFileName, nLine);
//
//#elif defined(MCHECK)
//
//   return memory_reallocate(pmemory, size);
//
//#elif MEMDLEAK
//   size_t nAllocSize = size + sizeof(memdleak_block);
//
//   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];
//
//   synchronous_lock lock(g_pmutgen);
//
//   if (s_pmemdleakList == pblock)
//   {
//      s_pmemdleakList = s_pmemdleakList->m_pnext;
//      s_pmemdleakList->m_pprevious = nullptr;
//   }
//   else
//   {
//      pblock->m_pprevious->m_pnext = pblock->m_pnext;
//      if (pblock->m_pnext != nullptr)
//      {
//         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
//      }
//   }
//
//   //if (pblock->m_pszFileName)
//   // class ::system_heap_free((void *)pblock->m_pszFileName);
//   //if (pblock->m_puiStack)
//   // class ::system_heap_free((void *)pblock->m_puiStack);
//
//   size_t * psizeNew = nullptr;
//
//   pblock = (memdleak_block *) class ::system_heap_realloc(pblock, size + sizeof(memdleak_block));
//
//   pblock->m_iBlockUse = nBlockUse;
//   if (g_ee == nullptr)
//   {
//      pblock->m_iStack = 0;
//      pblock->m_pszFileName = nullptr;
//
//   }
//   else
//   {
//      //string strCallStack;
//      //g_ee->xxxstack_trace(1);
//      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
//      g_ee->backtrace(pblock->m_puiStack, pblock->m_iStack);
//      pblock->m_pszFileName = nullptr;
//   }
//
//   ::acme::set_maximum(pblock->m_uiLine);
//
//   pblock->m_size = nAllocSize;
//
//   pblock->m_pprevious = nullptr;
//
//   pblock->m_pnext = s_pmemdleakList;
//
//   if (s_pmemdleakList != nullptr)
//   {
//
//      s_pmemdleakList->m_pprevious = pblock;
//
//   }
//
//   s_pmemdleakList = pblock;
//   lock.unlock();
//
//
//   return &pblock[1];
//
//#else
//
//   if (pmemory == nullptr)
//      return memory_allocate_debug(size, nBlockUse, szFileName, nLine);
//
//   unsigned char blockuse = heap_memory::heap_get_block_use(pmemory);
//
//   size_t sizeOld = heap_memory::heap_get_size(pmemory);
//
//   void * pusermessage = nullptr;
//
//   if(blockuse == 0) // aligned
//   {
//
//      pusermessage = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT);
//
//   }
//   else if(blockuse == 1) // aligned
//   {
//
//      //TODO: to do the dbg version
//
//      pusermessage = g_pheap->realloc_debug(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT,nBlockUse,szFileName,nLine);
//
//   }
//   else if(blockuse == 128) // aligned
//   {
//
//      pusermessage = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));
//
//   }
//   else if(blockuse == 129) // aligned
//   {
//
//      //TODO: to do the dbg version
//
//      pusermessage = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));
//
//   }
//   else if(blockuse == 2) // unaligned
//   {
//
//      pusermessage = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0);
//
//   }
//   else if(blockuse == 3) // unaligned
//   {
//
//      //TODO: to do the dbg version
//
//      pusermessage = g_pheap->realloc_debug(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0,nBlockUse,szFileName,nLine);
//
//   }
//   else
//   {
//
//      return nullptr;
//
//   }
//
//   if(pusermessage == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if(blockuse == 0 || blockuse == 1 || blockuse == 128 || blockuse == 129) // aligned
//   {
//
//      return heap_memory::aligned(pusermessage, size,blockuse);
//
//   }
//   else
//   {
//
//      return heap_memory::unaligned(pusermessage, size,blockuse);
//
//   }
//
//   return nullptr;
//
//#endif
//
//}
//
//#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)
//
//void ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(void * pmemory)
//{
//
//   return memory_free_debug(pmemory, 0);
//
//}
//
//#endif
//
//
//
//
//
//void memory_free_debug(void * pmemory, int iBlockType)
//{
//
//#if defined(__VLD) || defined(MCHECK) || defined(__MCRTDBG)
//
//   ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pmemory);
//
//#elif MEMDLEAK
//   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];
//
//   synchronous_lock lock(g_pmutgen);
//
//   if (s_pmemdleakList == pblock)
//   {
//      s_pmemdleakList = s_pmemdleakList->m_pnext;
//      if (s_pmemdleakList != nullptr)
//      {
//         s_pmemdleakList->m_pprevious = nullptr;
//
//      }
//   }
//   else
//   {
//      if (pblock->m_pprevious != nullptr)
//      {
//         pblock->m_pprevious->m_pnext = pblock->m_pnext;
//      }
//      if (pblock->m_pnext != nullptr)
//      {
//         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
//      }
//   }
//   //if (pblock->m_pszFileName)
//   // class ::system_heap_free((void *)pblock->m_pszFileName);
//   //if (pblock->m_puiStack)
//   // class ::system_heap_free((void *)pblock->m_puiStack);
//
//   return class ::system_heap_free(pblock);
//
//
//#else
//
//   heap_memory * pheap =  ::heap_memory::heap_get(pmemory);
//
//   void * pusermessage = (void *)(((iptr)pmemory) - pheap->m_back);
//
//
//   pheap->check_padding_after();
//
//
//   if(pheap->m_blockuse == 0)
//   {
//
//      g_pheap->_free(pusermessage,heap_memory::aligned_provision_get_size(pheap->m_size));
//
//   }
//   else if(pheap->m_blockuse == 1)
//   {
//
//      //TODO: to do the dbg version
//
//      g_pheap->free_debug(pusermessage,heap_memory::aligned_provision_get_size(pheap->m_size));
//
//   }
//   else if(pheap->m_blockuse == 128)
//   {
//
//      system_heap_free(pusermessage);
//
//   }
//   else if(pheap->m_blockuse == 129)
//   {
//
//      //TODO: to do the dbg version
//
//      system_heap_free(pusermessage);
//
//   }
//   else if(pheap->m_blockuse == 2)
//   {
//
//      g_pheap->_free(pusermessage,heap_memory::unaligned_provision_get_size(pheap->m_size));
//
//   }
//   else if(pheap->m_blockuse == 3)
//   {
//
//      //TODO: to do the dbg version
//
//      g_pheap->free_debug(pusermessage,heap_memory::unaligned_provision_get_size(pheap->m_size));
//
//   }
//   else
//   {
//
//      informationf("wrong free");
//
//   }
//#endif
//
//}
//
//
//#endif
//
//size_t memory_size(void * pmemory)
//{
//
//   return memory_size_debug(pmemory, _NORMAL_BLOCK);
//
//}
//
//size_t memory_size_debug(void * pmemory, int iBlockType)
//{
//
//#if defined(__VLD) || defined(__MCRTDBG)
//
//   return _msize(pmemory);
//
//#elif MEMDLEAK
//
//   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];
//
//   return pblock->m_size;
//
//#elif defined(MCHECK)
//
//   return malloc_usable_size(pmemory);
//
//#else
//
//   if (pmemory == nullptr)
//      return 0;
//
//   return heap_memory::heap_get_size(pmemory);
//
//#endif
//
//}
//
//
//#else
//
//
//
//void * aligned_memory_allocate(size_t size, memsize align)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//void * unaligned_memory_allocate(size_t size)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * aligned_memory_allocate_debug(size_t size, int nBlockUse, const char * szFileName, int nLine, memsize align)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//void * unaligned_memory_allocate_debug(size_t size, int nBlockUse, const char * szFileName, int nLine)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//
//
//void * ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(memsize size)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * memory_calloc(size_t size, size_t bytes)
//{
//
//   return calloc(size, bytes);
//
//}
//
//
//void * memory_allocate_debug(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
//{
//
//   return system_heap_alloc(nSize);
//
//}
//
//
//void * memory_reallocate(void * p, size_t nSize)
//{
//
//   return system_heap_realloc(pvoid, nSize);
//
//}
//
//
//void * memory_reallocate_debug(void * p, size_t size, int nBlockUse, const char * szFileName, int nLine)
//{
//
//
//   return system_heap_realloc(pvoid, size);
//
//
//
//}
//
//void ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(void * p)
//{
//   return system_heap_free(pvoid);
//}
//
//
//size_t memsize(void * p)
//{
//#ifdef WINDOWS
//   return _msize(pvoid);
//#else
//   return system_heap_alloc_size(pvoid);
//#endif
//}
//
//
//void memory_free_debug(void * p, int iBlockType)
//{
//
//   ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pvoid);
//
//}
//
//
//size_t memory_size_debug(void * p, int iBlockType)
//{
//#ifdef WINDOWS
//   return _msize(pvoid);
//#else
//
//   return system_heap_alloc_size(pvoid);
//#endif
//}
//
//
//#endif
//
//
//
//
//
//#endif
//
//
//#undef ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
//
//
//void * _memory_allocate(memsize size)
//{
//
////#if defined(__APPLE__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
//
//   return aligned_memory_allocate(size);
//
////#else
//
////   return unaligned_memory_allocate(size);
//
////#endif
//
//}
//
//
//void * _memory_allocate_no_track(memsize size)
//{
//
////#if defined(__APPLE__) || defined(RASPBERRYPIOS)
//
//   return aligned_memory_allocate(size);
//
////#else
//
////   return unaligned_memory_allocate(size);
//
////#endif
//
//}
//
//
//void * _memory_count_allocate(memsize size, memsize bytes)
//{
//
//   return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(size * bytes);
//
//}
//
//
//void * _memory_allocate_debug(memsize nSize, int nBlockUse, const char * szFileName, int nLine)
//{
//
//  // return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);
//
//   return aligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);
//
//}
//
//
//void * _memory_reallocate(void * pmemory, memsize nSize)
//{
//
//   return _memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);
//
//}
//
//
//void * _memory_reallocate_debug(void * pmemory, memsize size, int nBlockUse, const char * szFileName, int nLine)
//{
//
//   if (pmemory == nullptr)
//   {
//
//      return _memory_allocate_debug(size, nBlockUse, szFileName, nLine);
//
//   }
//
//   heap_memory* pheapmemory = heap_memory_get(pmemory);
//
//   if (pheapmemory->m_ememoryheap != HEAP_ENUMERATE)
//   {
//
//      return manage_memory_reallocate(pheapmemory->m_ememoryheap, pmemory, size);
//
//   }
//
//   unsigned char blockuse = pheapmemory->m_blockuse;
//
//   memsize sizeOld = pheapmemory->m_size;
//
//   unsigned char align = pheapmemory->m_align;
//
//   void * p = heap_memory_base_get(pmemory);
//
//   if(blockuse == 0) // aligned
//   {
//
//      p = g_pheap->_realloc(
//         p,
//         heap_memory_aligned_provision_get_size(size, align),
//         heap_memory_aligned_provision_get_size(sizeOld, align),
//         align);
//
//   }
//   else if(blockuse == 1) // unaligned
//   {
//
//      //TODO: to do the dbg version
//
//      p = g_pheap->_realloc(
//         p,
//         heap_memory_unaligned_provision_get_size(size),
//         heap_memory_unaligned_provision_get_size(sizeOld),
//         0);
//
//   }
//   else if(blockuse == 128) // aligned
//   {
//
//      p = system_heap_realloc(
//         p,
//         (size_t)heap_memory_aligned_provision_get_size(size, align));
//
//   }
//   else if(blockuse == 129) // unaligned
//   {
//
//      //TODO: to do the dbg version
//
//      p = system_heap_realloc(
//         p,
//         (size_t)heap_memory_unaligned_provision_get_size(size));
//
//   }
//   else if(blockuse == 2) // aligned
//   {
//
//      p = g_pheap->realloc_debug(
//         p,
//         heap_memory_aligned_provision_get_size(size, align),
//         heap_memory_aligned_provision_get_size(sizeOld, align),
//         align, nBlockUse, szFileName, nLine);
//
//   }
//   else if(blockuse == 3) // unaligned
//   {
//
//      //TODO: to do the dbg version
//
//      p = g_pheap->realloc_debug(
//         p,
//         heap_memory_unaligned_provision_get_size(size),
//         heap_memory_unaligned_provision_get_size(sizeOld),
//         0,nBlockUse,szFileName,nLine);
//
//   }
//   else if (blockuse == 130) // aligned
//   {
//
//      p = system_heap_realloc(
//         p,
//         (size_t)heap_memory_aligned_provision_get_size(size, align));
//
//   }
//   else if (blockuse == 131) // unaligned
//   {
//
//      //TODO: to do the dbg version
//
//      p = system_heap_realloc(
//         p,
//         (size_t)heap_memory_unaligned_provision_get_size(size));
//
//   }
//   else
//   {
//
//      throw ::exception(error_exception);
//
//   }
//
//   if(p == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if(blockuse == 0 || blockuse == 2 || blockuse == 128 || blockuse == 130) // aligned
//   {
//
//      return heap_memory_aligned(p, size, blockuse, align, HEAP_ENUMERATE);
//
//   }
//   else if (blockuse == 1 || blockuse == 3 || blockuse == 129 || blockuse == 131) // unaligned
//   {
//
//      return heap_memory_unaligned(p, size, blockuse, HEAP_ENUMERATE);
//
//   }
//   else
//   {
//
//      throw ::exception(error_exception);
//
//   }
//
//   return nullptr;
//
//}
//
//
//void _memory_free(void * pmemory)
//{
//
//   return _memory_free_debug(pmemory, 0);
//
//}
//
//
//void _memory_free_debug(void * pmemory, int iBlockType)
//{
//
//   if((iptr) pmemory < 1024)
//   {
//
//      return;
//
//   }
//
//   heap_memory * pheapmemory = heap_memory_get(pmemory);
//
//   if (pheapmemory->m_ememoryheap != HEAP_ENUMERATE)
//   {
//
//      manage_memory_free(pheapmemory->m_ememoryheap, pmemory);
//
//      return;
//
//   }
//
//   void * p = (void *)(((iptr)pmemory) - pheapmemory->m_back);
//
//#ifdef _DEBUG
//
//   heap_memory_check_padding_after(pheapmemory);
//
//#endif // !__DEBUG
//
//   if(pheapmemory->m_blockuse == 0)
//   {
//
//      memsize iAlignedSize = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);
//
//      if(g_pheap)
//      {
//
//         g_pheap->_free(p, iAlignedSize);
//
//      }
//
//   }
//   else if(pheapmemory->m_blockuse == 1)
//   {
//
//      //TODO: to do the dbg version
//
//      if(g_pheap)
//      {
//
//         g_pheap->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));
//
//      }
//
//   }
//   else if(pheapmemory->m_blockuse == 128)
//   {
//
//      system_heap_free(p);
//
//   }
//   else if(pheapmemory->m_blockuse == 129)
//   {
//
//      //TODO: to do the dbg version
//
//      system_heap_free(p);
//
//   }
//   else if(pheapmemory->m_blockuse == 2)
//   {
//
//      memsize sizeProvision = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);
//
//      g_pheap->free_debug(p, sizeProvision);
//
//   }
//   else if(pheapmemory->m_blockuse == 3)
//   {
//
//      //TODO: to do the dbg version
//
//      g_pheap->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));
//
//   }
//   else
//   {
//
//      system_heap_free(p);
//
//   }
//
//}
//
//
//memsize _memory_size(void * pmemory)
//{
//
//   return _memory_size_debug(pmemory, _NORMAL_BLOCK);
//
//}
//
//
//memsize _memory_size_debug(void * pmemory, int iBlockType)
//{
//
//   if (pmemory == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   return heap_memory_get_size(pmemory);
//
//}
//
//
//
//



