#include "framework.h"
#include "allocator.h"
#include "plex_heap.h"
#include "plex_heap_alloc_sync.h"


void * g_pDebugPointer = nullptr;


//#include "acme/platform/acme.h"


plex_heap_alloc_sync::plex_heap_alloc_sync(::heap::allocator * pallocator, memsize nAllocSize, ::u32 nBlockSize) :
   m_pallocator(pallocator)
{

   if (nBlockSize <= 1)
   {

      nBlockSize = 4;

   }

   ASSERT(nAllocSize >= sizeof(node));

   if (nAllocSize < sizeof(node))
   {

      nAllocSize = sizeof(node);

   }

   ASSERT(nBlockSize > 1);

   if (nBlockSize <= 0)
   {

      nBlockSize = 64;

   }

   m_nAllocSize = (::i32)nAllocSize;

   m_nBlockSize = nBlockSize;

   m_pnodeFree = nullptr;

   m_pBlocks = nullptr;

   m_iFreeHitCount = 0;

   m_pnodeLastBlock = nullptr;

}


plex_heap_alloc_sync::~plex_heap_alloc_sync()
{

   FreeAll();

}

void on_system_heap_alloc(memsize memsize);

void free_foo()
{


}



void * plex_heap_alloc_sync::Alloc()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   //   if(m_nAllocSize == 8192)
   //   {
   //
   //      printf("Alloc 8192");
   //
   //   }

   if (m_pnodeFree == nullptr)
   {

      //if (m_nAllocSize == 128)
      //{

      //   informationf("plex_heap_alloc_sync::Alloc 128");

      //}

      NewBlock();

   }
   if (((iptr)m_pnodeFree->m_pnext) & 1)
   {

      debug_break();

   }

   void * pnode = m_pnodeFree;

   m_pnodeFree = m_pnodeFree->m_pnext;

   ::zero(pnode, m_nAllocSize);

   return pnode;

}


CLASS_DECL_ACME void set_debug_pointer(void * p)
{

   g_pDebugPointer = p;

}


extern iptr g_iMonitor;


void plex_heap_alloc_sync::Free(void * pParam)
{

   iptr i = (iptr)pParam;

   if (i > g_iMonitor - m_nAllocSize && i < g_iMonitor + m_nAllocSize)
   {

      output_debug_string("MAKING FREE");

   }

   //   if(m_nAllocSize == 8192)
   //   {
   //
   //      printf("Free 8192");
   //
   //   }
   u64 & u = ((u64 &)pParam);
   if ((u & 0xffffffff) == 00)
   {
      informationf("");

   }

   if (m_nAllocSize == 128)
   {
      //u64 & u = ((u64 &)pParam);

      if ((u & 0xff000000) == 00)
      {
         informationf("");

      }

   }
   if ((::u8 *)0x0000000020000218 == ((::u8 *)pParam))
   {

      debug_break();

   }
   if (((iptr)pParam) & 1)
   {
      debug_break();

   }
   //else if ((((iptr)pParam) & 0xcccccc) == 0xcccccc)
   //{

   //   debug_break();

   //}
   else if (pParam == g_pDebugPointer)
   {

      //informationf("test");

   }

   if (is_null(pParam))
   {

      return;

   }

   node * pnode = (node *)pParam;

   critical_section_lock synchronouslock(&m_criticalsection);

#ifdef MEMDFREE // Free Debug - duplicate freeing ?

   node * pnodeFree = m_pnodeFree;

   while (pnodeFree != nullptr)
   {

      if (pnode == pnodeFree) // dbgsnp - debug snippet
      {

         // already in free list

         if (is_debugger_attached())
         {

            debug_break();

         }

         return;

      }

      pnodeFree = pnodeFree->m_pnext;

   }

#endif

#if STORE_LAST_BLOCK

   if (m_pnodeLastBlock != nullptr)
   {

      system_heap_free(m_pnodeLastBlock);

   }

   m_pnodeLastBlock = (node *)system_heap_alloc(m_nAllocSize + 32);

   ::memory_copy(m_pnodeLastBlock, pnode, m_nAllocSize + 32);

#endif

   pnode->m_pnext = m_pnodeFree;

   m_pnodeFree = pnode;

}


void plex_heap_alloc_sync::FreeAll()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   try
   {

      m_pBlocks->FreeDataChain(m_pallocator);

      m_pBlocks = nullptr;

      m_pnodeFree = nullptr;

   }
   catch (...)
   {

   }

}





void plex_heap_alloc_sync::NewBlock()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   ::u32 nAllocSize = m_nAllocSize;

   m_pallocator->m_pacme->heap()->on_plex_new_block(nAllocSize);

   auto pnewblock = plex_heap::create(m_pBlocks, m_nBlockSize, nAllocSize, m_pallocator);

   auto pnode = (node *)pnewblock->data();

   node * pnodeNext = nullptr;

   auto nBlockSize = m_nBlockSize;

   for (i32 i = 0; i < nBlockSize; i++)
   {

      pnode->m_pnext = pnodeNext;

      pnodeNext = pnode;

      pnode = (node *)&((::u8 *)pnode)[nAllocSize];

   }

   if ((::u8 *)0x0000000200000020 == ((::u8 *)pnodeNext))
   {

      debug_break();

   }

   m_pnodeFree = pnodeNext;

#ifdef XXDEBUG

   Free_check_pointer_in_cpp(m_pnodeFree);

#endif // XXDEBUG

}


