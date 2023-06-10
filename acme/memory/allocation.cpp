#include "framework.h"




//PFN_MEMORY_ALLOC g_pfnAceAlloc = nullptr;
//PFN_MEMORY_REALLOC g_pfnAceRealloc = nullptr;
//PFN_MEMORY_FREE g_pfnAceFree = nullptr;
//PFN_MEMORY_SIZE g_pfnAceSize = nullptr;
//
//
//#ifdef __APPLE__
//
//
//#define ACE_ALIGN_BYTE_COUNT (sizeof(memsize) * 2)
//
//
//#else
//
//
//#define ACE_ALIGN_BYTE_COUNT 16
//
//
//#endif
//
//
//int g_ace_set = 0;
//
//
//#define INITIAL_ACE 0xff
//#define ACE_SET 0xf7


//CLASS_DECL_ACME void * ace_memory_alloc(memsize s)
//{
//
//#if OSBIT == 32
//
//   if (s >= 0x100000000ll)
//   {
//
//      return nullptr;
//
//   }
//
//#endif
//
//   if (g_ace_set)
//   {
//
//      return g_pfnAceAlloc(s);
//
//   }
//   else
//   {
//
//      auto sizeProvision = heap_memory_aligned_provision_get_size(s, ACE_ALIGN_BYTE_COUNT);
//
//      auto pdata = malloc((size_t)sizeProvision);
//
//      pdata = heap_memory_aligned(pdata, s, INITIAL_ACE, ACE_ALIGN_BYTE_COUNT);
//
//      return pdata;
//
//   }
//
//}
//
//
//CLASS_DECL_ACME void * ace_memory_realloc(void * pParam, memsize s)
//{
//
//
//#if OSBIT == 32
//
//   if (s >= 0x100000000ll)
//   {
//
//      return nullptr;
//
//   }
//
//#endif
//
//   if (heap_memory_get_block_use(pParam) == INITIAL_ACE)
//   {
//
//      auto pdata = realloc(heap_memory_base_get(pParam), heap_memory_aligned_provision_get_size(s, ACE_ALIGN_BYTE_COUNT));
//
//      pdata = heap_memory_aligned(pdata, s, INITIAL_ACE, ACE_ALIGN_BYTE_COUNT);
//
//      return pdata;
//
//   }
//   else
//   {
//
//      return g_pfnAceRealloc(pParam, s);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME void ace_memory_free(void * pParam)
//{
//
//   u8 * pdata = (u8 *)pParam;
//
//   if (((iptr)pdata) < 1024 * 16)
//   {
//
//      return;
//
//   }
//
//   if (heap_memory_get_block_use(pParam) == INITIAL_ACE)
//   {
//
//      free(heap_memory_base_get(pParam));
//
//   }
//   else
//   {
//
//      return g_pfnAceFree(pParam);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME memsize ace_memory_size(void * pParam)
//{
//
//   return heap_memory_get_size(pParam);
//
//}
//
//
//CLASS_DECL_ACME void ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize)
//{
//
//   g_pfnAceAlloc = palloc;
//
//   g_pfnAceRealloc = prealloc;
//
//   g_pfnAceFree = pfree;
//
//   g_pfnAceSize = psize;
//
//   g_ace_set = 1;
//
//}
//
//
//
//
//

#ifdef CPP17



void * __cdecl operator new(size_t size, std::align_val_t alignment)
{
   
   return aligned_memory_allocate(size, (memsize) alignment);

}


void operator delete(void * ptr, std::align_val_t) noexcept
{

   memory_free(ptr);

}



#endif // CPP17



void heap_memory_check_padding_after(struct heap_memory* pheapmemory)
{

   ::u8* pbyte = (::u8*)pheapmemory;

   int iStructSize = sizeof(heap_memory);

   // Heap Memory
   // 1 ::u8 + 1 ::u8 + 1 ::u8 + 1 ::u8 + 4 bytes
   // 8 bytes + padding
   // 16 bytes?

   ::u32 iSize = pheapmemory->m_size;

   auto ppaddingAfter = pbyte + iStructSize + iSize;

   for (int i = 0; i < HEAP_PADDING_SIZE; i++)
   {

      if (ppaddingAfter[i] != 0)
      {

         //            ::output_debug_string("*&!@");

      }

   }

}


