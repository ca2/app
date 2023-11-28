#include "framework.h"
#include "allocator.h"
#include "plex_heap_alloc.h"

//#include "acme/platform/acme.h"







void Alloc_check_pointer_in_cpp(void * p);

void Free_check_pointer_in_cpp(void * p);


plex_heap_alloc::plex_heap_alloc(::heap::allocator * pallocator, memsize nAllocSize, ::u32 nBlockSize) :
   m_pallocator(pallocator)
{

   //disable_referencing_debugging();

   i32 iShareCount = 1;

   set_size(iShareCount);

   for (i32 i = 0; i < get_count(); i++)
   {

      set_at(i, ::platform::raw_allocator::__allocator_base_new < plex_heap_alloc_sync >(pallocator, pallocator, nAllocSize, nBlockSize));

   }

   m_iShareCount = iShareCount;

   m_iShareBound = iShareCount - 1;

   m_iAllocSize = (::i32)nAllocSize;

   m_iAlloc = 0;

   m_iFree = 0;

}



void Free_check_pointer_in_cpp(void * p);



plex_heap_alloc::~plex_heap_alloc()
{

   for (i32 i = 0; i < get_count(); i++)
   {

      ::platform::raw_allocator::__allocator_base_delete(m_pallocator, element_at(i));

   }

}

//
//void * plex_heap_alloc::operator new(size_t s)
//{
//
//   return m_pallocator->allocate(sizeof(plex_heap_alloc));
//
//}
//
//
//void plex_heap_alloc::operator delete(void * p)
//{
//
//   return m_pallocator->allocate->free(p);
//
//}


void plex_heap_alloc::FreeAll()
{

   for (i32 i = 0; i < get_count(); i++)
   {

      try
      {

         element_at(i)->FreeAll();

      }
      catch (...)
      {

      }

   }

}


void plex_heap_alloc::pre_finalize()
{

   FreeAll();

}





//void * g_pf1 = nullptr;



#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#ifdef RASPBERRYPIOS
#define QUOTED_KERNEL_SPACE (1024)
#elif  defined(ANDROID)
#define QUOTED_KERNEL_SPACE (1024 * 1024)
#else
#if OSBIT == 64
#define QUOTED_KERNEL_SPACE (1024 * 1024)
#else
#define QUOTED_KERNEL_SPACE 1024
#endif
#endif

void Alloc_check_pointer_in_cpp(void * p)
{

   if ((uptr)p < QUOTED_KERNEL_SPACE)
   {

      if (p == nullptr)
      {

         output_debug_string("Alloc_check_pointer_in_cpp return nullptr ?!?!?!");

      }
      else
      {

         output_debug_string("Alloc_check_pointer_in_cpp returning address less than " STR(QUOTED_KERNEL_SPACE));

      }

   }

}


void Free_check_pointer_in_cpp(void * p)
{

   //if((u8 *) p <  (u8 *)  g_pf1)
   //{

   //   output_debug_string("hit g_pf1");

   //}

   if ((::u8 *)0x0000000200000020 == ((::u8 *)p))
   {

      output_debug_string("found it?!");

   }


   if ((dword_ptr)p & 0x8000000000000000LLU)
   {

      output_debug_string("hit hiptr");

   }

#if OSBIT >= 64

   if ((dword_ptr)p == 0x0000000200000020LLU)
   {

      output_debug_string("hit 0x0000000200000020LLU");

   }

#endif

   if ((uptr)p < QUOTED_KERNEL_SPACE)
   {

      if (p == nullptr)
      {

         output_debug_string("Free_check_pointer_in_cpp FREEING nullptr?!?! WHAT!! == nullptr!!");

      }
      else
      {

         output_debug_string("Free_check_pointer_in_cpp WHAT!! < " STR(QUOTED_KERNEL_SPACE));

      }

   }

}
//
//
//void * plex_heap_alloc_array::operator new(size_t s)
//{
//
//   return system_heap_alloc(sizeof(plex_heap_alloc_array));
//
//}
//
//
//void plex_heap_alloc_array::operator delete(void * p)
//{
//
//   system_heap_free(p);
//
//}

//
//plex_heap_alloc * plex_heap_alloc_array::find(memsize nAllocSize)
//{
//
//   for (auto p = m_begin; p < m_end; p++)
//   {
//
//      auto palloc = *p;
//
//      if (nAllocSize <= palloc->m_iAllocSize)
//      {
//
//         if (palloc->m_iAllocSize == 16384)
//         {
//
//            //::acme::get()->platform()->informationf(".");
//
//         }
//
//         return palloc;
//
//      }
//
//   }
//
//   return nullptr;
//
//}
//
//
//void * plex_heap_alloc_array::_alloc(memsize size)
//{
//
//   plex_heap_alloc * palloc = find(size);
//
//   if (palloc != nullptr)
//   {
//
//      ::HEAP_NAMESPACE::on_plex_heap_alloc(palloc);
//
//      return palloc->Alloc();
//
//   }
//   else
//   {
//
//      ::HEAP_NAMESPACE::on_system_heap_alloc(size);
//
//      return ::system_heap_alloc(size);
//
//   }
//
//}
//
//void free_foo()
//{
//
//
//}
//void plex_heap_alloc_array::_free(void * p, memsize size)
//{
//
//   plex_heap_alloc * palloc = find(size);
//
//   if (palloc != nullptr)
//   {
//
//      ASSERT(size <= palloc->m_iAllocSize);
//
//      if (palloc->m_iAllocSize == 256)
//      {
//
//         free_foo();
//
//      }
//
//      return palloc->Free(p);
//
//   }
//   else
//   {
//
//      return ::system_heap_free(p);
//
//   }
//
//}

//
//void * plex_heap_alloc_sync::Alloc()
//{
//
//   critical_section_lock synchronouslock(&m_criticalsection);
//
//   //   if(m_nAllocSize == 8192)
//   //   {
//   //
//   //      printf("Alloc 8192");
//   //
//   //   }
//
//   if (m_pnodeFree == nullptr)
//   {
//
//      //if (m_nAllocSize == 128)
//      //{
//
//      //   informationf("plex_heap_alloc_sync::Alloc 128");
//
//      //}
//
//      NewBlock();
//
//   }
//   if (((iptr)m_pnodeFree->m_pnext) & 1)
//   {
//
//      debug_break();
//
//   }
//
//   void * pnode = m_pnodeFree;
//
//   m_pnodeFree = m_pnodeFree->m_pnext;
//
//   ::zero(pnode, m_nAllocSize);
//
//   return pnode;
//
//}
//
//
//void * g_pDebugPointer = nullptr;
//
//CLASS_DECL_ACME void set_debug_pointer(void * p)
//{
//
//   g_pDebugPointer = p;
//
//}
//
//
//void plex_heap_alloc_sync::Free(void * pParam)
//{
//
//   iptr i = (iptr)pParam;
//
//   if (i > g_iMonitor - m_nAllocSize && i < g_iMonitor + m_nAllocSize)
//   {
//
//      output_debug_string("MAKING FREE");
//
//   }
//
//   //   if(m_nAllocSize == 8192)
//   //   {
//   //
//   //      printf("Free 8192");
//   //
//   //   }
//
//   if (m_nAllocSize == 128)
//   {
//      u64 & u = ((u64 &)pParam);
//
//      if ((u & 0xff000000) == 00)
//      {
//         //informationf("");
//
//      }
//
//   }
//   if ((::u8 *)0x0000000200000020 == ((::u8 *)pParam))
//   {
//
//      debug_break();
//
//   }
//   if (((iptr)pParam) & 1)
//   {
//      debug_break();
//
//   }
//   //else if ((((iptr)pParam) & 0xcccccc) == 0xcccccc)
//   //{
//
//   //   debug_break();
//
//   //}
//   else if (pParam == g_pDebugPointer)
//   {
//
//      //informationf("test");
//
//   }
//
//   if (is_null(pParam))
//   {
//
//      return;
//
//   }
//
//   node * pnode = (node *)pParam;
//
//   critical_section_lock synchronouslock(&m_criticalsection);
//
//#ifdef MEMDFREE // Free Debug - duplicate freeing ?
//
//   node * pnodeFree = m_pnodeFree;
//
//   while (pnodeFree != nullptr)
//   {
//
//      if (pnode == pnodeFree) // dbgsnp - debug snippet
//      {
//
//         // already in free list
//
//         if (is_debugger_attached())
//         {
//
//            debug_break();
//
//         }
//
//         return;
//
//      }
//
//      pnodeFree = pnodeFree->m_pnext;
//
//   }
//
//#endif
//
//#if STORE_LAST_BLOCK
//
//   if (m_pnodeLastBlock != nullptr)
//   {
//
//      system_heap_free(m_pnodeLastBlock);
//
//   }
//
//   m_pnodeLastBlock = (node *)system_heap_alloc(m_nAllocSize + 32);
//
//   ::memory_copy(m_pnodeLastBlock, pnode, m_nAllocSize + 32);
//
//#endif
//
//   pnode->m_pnext = m_pnodeFree;
//
//   m_pnodeFree = pnode;
//
//}
//
//
//
//
//
//void plex_heap_alloc_sync::FreeAll()
//{
//
//   critical_section_lock synchronouslock(&m_criticalsection);
//
//   try
//   {
//
//      m_pBlocks->FreeDataChain();
//
//      m_pBlocks = nullptr;
//
//      m_pnodeFree = nullptr;
//
//   }
//   catch (...)
//   {
//
//   }
//
//}
//
//
//void plex_heap_alloc_sync::NewBlock()
//{
//
//   critical_section_lock synchronouslock(&m_criticalsection);
//
//   ::u32 nAllocSize = m_nAllocSize;
//
//   ::HEAP_NAMESPACE::on_plex_new_block(nAllocSize);
//
//   plex_heap * pnewblock = plex_heap::create(m_pBlocks, m_nBlockSize, nAllocSize);
//
//   auto pnode = (node *)pnewblock->data();
//
//   node * pnodeNext = nullptr;
//
//   auto nBlockSize = m_nBlockSize;
//
//   for (i32 i = 0; i < nBlockSize; i++)
//   {
//
//      pnode->m_pnext = pnodeNext;
//
//      pnodeNext = pnode;
//
//      pnode = (node *)&((::u8 *)pnode)[nAllocSize];
//
//   }
//
//   if ((::u8 *)0x0000000200000020 == ((::u8 *)pnodeNext))
//   {
//
//      debug_break();
//
//   }
//
//   m_pnodeFree = pnodeNext;
//
//#ifdef XXDEBUG
//
//   Free_check_pointer_in_cpp(m_pnodeFree);
//
//#endif // XXDEBUG
//
//}
//
//
//
//

//plex_heap_alloc_sync * plex_heap_alloc::new_plex_heap_alloc_sync(memsize nAllocSize, ::u32 nBlockSize)
//{
//
//   auto palloc = (plex_heap_alloc_sync*) m_pallocator->allocate(sizeof(plex_heap_alloc_sync));
//
//   ::new(palloc) ::plex_heap_alloc_sync(m_pallocator, nAllocSize, nBlockSize);
//
//   return palloc;
//}
//

//void plex_heap_alloc::delete_plex_heap_alloc_sync(plex_heap_alloc_sync * p)
//{
//   
//   p->~plex_heap_alloc_sync();
//
//   m_pallocator->free(p);
//
//}
