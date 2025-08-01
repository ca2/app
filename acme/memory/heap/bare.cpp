#include "framework.h"




//
//
//#include "acme/memory/heap_memory.h"
//
//
//void * bare_aligned_memory_allocate(memsize size, memsize align)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_unaligned_memory_allocate(memsize size)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_aligned_memory_allocate_debug(memsize size, int nBlockUse, const_char_pointer szFileName, int nLine, memsize align)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_unaligned_memory_allocate_debug(memsize size, int nBlockUse, const_char_pointer szFileName, int nLine)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_memory_allocate(memsize size)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_memory_allocate_no_track(memsize size)
//{
//
//   return system_heap_alloc(size);
//
//}
//
//
//void * bare_memory_calloc(memsize size, memsize bytes)
//{
//
//   return calloc(size, bytes);
//
//}
//
//
//void * bare_memory_allocate_debug(memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine)
//{
//
//   return system_heap_alloc(nSize);
//
//}
//
//
//void * bare_memory_reallocate(void * pvoid, memsize nSize)
//{
//
//   return system_heap_realloc(pvoid, nSize);
//
//}
//
//
//void * bare_memory_reallocate_debug(void * p, memsize size, int nBlockUse, const_char_pointer szFileName, int nLine)
//{
//
//   return system_heap_realloc(p, size);
//
//}
//
//
//void bare_memory_free(void * p)
//{
//
//   return system_heap_free(p);
//
//}
//
//
//memsize bare_memory_size(void * p)
//{
//
//#ifdef WINDOWS
//
//   return _msize(p);
//
//#else
//
//   return system_heap_alloc_size(p);
//
//#endif
//
//}
//
//
//void memory_free_debug(void * p, int iBlockType)
//{
//
//   ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(p);
//
//}
//
//
//memsize memory_size_debug(void * p, int iBlockType)
//{
//
//#ifdef WINDOWS
//
//   return _msize(p);
//
//#else
//
//   return system_heap_alloc_size(p);
//
//#endif
//
//}
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
//void * _memory_allocate_debug(memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine)
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
//void * _memory_reallocate_debug(void * pmemory, memsize size, int nBlockUse, const_char_pointer szFileName, int nLine)
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
//   system_heap_free(pmemory);
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
//#ifdef WINDOWS
//
//   return _msize(pmemory);
//
//#else
//
//   return malloc_size(pmemory);
//
//#endif
//
//}
//
//
//



