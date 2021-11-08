#include "framework.h"
#include "acme/operating_system.h"
 
//#include "plex_heap1.h"

//#include "plex_heap_impl1.h"

//#include "align_byte_count.h"
//#include "acme/platform/static_start_internal.h"


//#if !defined(MCHECK) && !defined(_VLD) && !defined(__MCRTDBG) && !MEMDLEAK
//
//#include "heap_memory.h"
//
//#endif

#include "acme/platform/static_start.h"

#undef new


void on_plex_heap_alloc(plex_heap_alloc* palloc);
void on_system_heap_alloc(memsize memsize);


void * plex_heap_alloc_sync::operator new(size_t s)
{

   return system_heap_alloc(sizeof(plex_heap_alloc_sync));

}

void plex_heap_alloc_sync::operator delete(void * p)
{

   system_heap_free(p);

}




void Alloc_check_pointer_in_cpp(void * p);

void Free_check_pointer_in_cpp(void * p);


plex_heap_alloc_sync::plex_heap_alloc_sync(memsize nAllocSize, ::u32 nBlockSize)
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

   m_nAllocSize = (::i32) nAllocSize;

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


plex_heap_alloc::plex_heap_alloc(memsize nAllocSize, ::u32 nBlockSize)
{

   i32 iShareCount = 1;

   allocate(iShareCount);

   for(i32 i = 0; i < get_count(); i++)
   {
      set_at(i, new plex_heap_alloc_sync(nAllocSize, nBlockSize));
   }

   m_iShareCount = iShareCount;

   m_iShareBound = iShareCount - 1;

   m_iAllocSize = (::i32) nAllocSize;

   m_iAlloc = 0;

   m_iFree = 0;

}

#undef new

void Free_check_pointer_in_cpp(void * p);



plex_heap_alloc::~plex_heap_alloc()
{

   for(i32 i = 0; i < get_count(); i++)
   {

      delete element_at(i);

   }

}

void * plex_heap_alloc::operator new(size_t s)
{

   return system_heap_alloc(sizeof(plex_heap_alloc));

}


void plex_heap_alloc::operator delete(void * p)
{

   system_heap_free(p);

}


void plex_heap_alloc::FreeAll()
{

   for(i32 i = 0; i < get_count(); i++)
   {

      try
      {

         element_at(i)->FreeAll();

      }
      catch(...)
      {

      }

   }

}


void plex_heap_alloc::pre_finalize()
{

   FreeAll();

}





plex_heap_alloc_array::plex_heap_alloc_array()
{

   add(new plex_heap_alloc(32       , 256)); 
   add(new plex_heap_alloc(64       , 128)); 
   add(new plex_heap_alloc(128      , 128)); 
   add(new plex_heap_alloc(256      , 128)); 
   add(new plex_heap_alloc(512      , 64)); 
   add(new plex_heap_alloc(1024     , 64)); 
   add(new plex_heap_alloc(2_kb     , 32));
   add(new plex_heap_alloc(4_kb     , 32));
   add(new plex_heap_alloc(8_kb     , 16));
   add(new plex_heap_alloc(16_kb    , 16));

#if !MOBILE_PLATFORM

   add(new plex_heap_alloc(24_kb    , 16));
   add(new plex_heap_alloc(32_kb    , 16));
   add(new plex_heap_alloc(48_kb    , 16));
   add(new plex_heap_alloc(64_kb    , 16));
   add(new plex_heap_alloc(128_kb   , 16));
   add(new plex_heap_alloc(256_kb   , 8));
   add(new plex_heap_alloc(512_kb   , 8));
   add(new plex_heap_alloc(1024_kb  , 4));



#if OSBIT > 32

   add(new plex_heap_alloc(2_mb     , 2)); // 2 * 1024 * 1024
   add(new plex_heap_alloc(4_mb     , 2)); // 4 * 1024 * 1024
   add(new plex_heap_alloc(8_mb     , 2)); // 8 * 1024 * 1024
   add(new plex_heap_alloc(16_mb    , 2)); // 16 * 1024 * 1024

#endif

#endif

}


plex_heap_alloc_array::~plex_heap_alloc_array()
{

   pre_finalize();

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {

      delete this->element_at(i);

   }

   erase_all();

   if(g_pheap == this)
   {

      g_pheap = nullptr;

   }

}

void plex_heap_alloc_array::pre_finalize()
{

   for (index i = this->get_upper_bound(); i >= 0; i--)
   {

      this->element_at(i)->pre_finalize();

   }

}



void * plex_heap_alloc_array::alloc_debug(memsize size, i32 nBlockUse, const char * pszFileName, i32 iLine)
{

#if LAST_MEM_FILE_AND_LINE

   string str;

   str.format("%s(%d)", pszFileName, iLine);

   memsize nAllocSize = size + sizeof(memsize) + 128;

   plex_heap_alloc * palloc = find(nAllocSize);

   memsize * psize = nullptr;

   if(palloc != nullptr)
   {

      psize (memsize *) palloc->Alloc();

      psize[0] = nAllocSize;

   }
   else
   {

      psize = (memsize *) ::system_heap_alloc(nAllocSize);

      psize[0] = 0;

   }

   ansi_count_copy((char *) &psize1], str->Mid(maximum(0, str->get_length() - 124)), 124);

   return ((u8 *) &psize[1]) + 128;

#else

   return _alloc(size);

#endif

}


void plex_heap_alloc_array::free_debug(void * p, memsize size)
{

#if LAST_MEM_FILE_AND_LINE

   memsize * psize = &((memsize *)((u8 *)pvoid) - 128))[-1];

   if(*psize == 0)
   {

      return ::system_heap_free(psize);

   }

   plex_heap_alloc * palloc = find(*psize);

   if(palloc != nullptr)
{

   return palloc->Free(psize);

   }
   else
   {

      return ::system_heap_free(psize);

   }

#else

   return _free(p, size);

#endif

}


void * plex_heap_alloc_array::realloc_debug(void * p,  memsize size, memsize sizeOld, int align, i32 nBlockUse, const char * pszFileName, i32 iLine)
{

#if LAST_MEM_FILE_AND_LINE

   string str;

   str.format("%s(%d)", szFileName, iLine);

   memsize * psize = (memsize *) realloc(&((memsize *)(((u8 *)pvoidOld) - 128))[-1], ((memsize *)(((u8 *)pvoidOld) - 128))[-1], size + sizeof(memsize) + 128);

   psize[0] = size + sizeof(memsize) + 128;

   ansi_count_copy((char *) &psize1], str->Mid(maximum(0, str->get_length() - 124)), 124);

   return ((u8 *) &psize[1]) + 128;

#else

   return _realloc(p, size, sizeOld, align);

#endif

}


void * plex_heap_alloc_array::_realloc(void * p, memsize size, memsize sizeOld, int align)
{

   plex_heap_alloc * pallocOld = find(sizeOld);

   plex_heap_alloc * pallocNew = find(size);

   char * pNew = nullptr;

   if (pallocOld == nullptr && pallocNew == nullptr && align == 0)
   {

      pNew = (char *) ::system_heap_realloc(p, size);

      if(size > sizeOld)
      {

         auto pZero = pNew + sizeOld;

         __memset(pZero, 0, size - sizeOld);

      }

   }
   else if(pallocOld != NULL && pallocOld == pallocNew)
   {

      pNew = (char *) p;

   }
   else
   {

      if (pallocNew != nullptr)
      {

         pNew = (char *) pallocNew->Alloc();

      }
      else
      {

         pNew = (char *) ::system_heap_alloc(size);

      }

#if !MEMDLEAK
      if (align > 0)
      {

         memsize oldSize = sizeOld - heap_memory_aligned_provision_get_size(0, ALIGN_BYTE_COUNT);

         memsize newSize = size - heap_memory_aligned_provision_get_size(0, ALIGN_BYTE_COUNT);

         ::memcpy_dup(heap_memory_aligned(pNew,newSize,0, ALIGN_BYTE_COUNT, HEAP_ENUMERATE),
                heap_memory_aligned(p,oldSize,0, ALIGN_BYTE_COUNT, HEAP_ENUMERATE),
                minimum(oldSize, newSize));

      }
      else
#endif
      {

         ::memcpy_dup(pNew, p, minimum(sizeOld, size));

      }

      if (pallocOld != nullptr)
      {

         pallocOld->Free(p);

      }
      else
      {

         ::system_heap_free(p);

      }

   }

   return pNew;

}

//void * g_pf1 = nullptr;



#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#ifdef RASPBIAN
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

         simple_debug_print("Alloc_check_pointer_in_cpp return nullptr ?!?!?!");

      }
      else
      {

         simple_debug_print("Alloc_check_pointer_in_cpp returning address less than " STR(QUOTED_KERNEL_SPACE));

      }

   }

}


void Free_check_pointer_in_cpp(void * p)
{

   //if((u8 *) p <  (u8 *)  g_pf1)
   //{

   //   simple_debug_print("hit g_pf1");

   //}

   if ((byte *)0x0000000200000020 == ((byte *)p))
   {

      simple_debug_print("found it?!");

   }


   if((dword_ptr) p   & 0x8000000000000000LLU)
   {

      simple_debug_print("hit hiptr");

   }

#if OSBIT >= 64

   if ((dword_ptr)p == 0x0000000200000020LLU)
   {

      simple_debug_print("hit 0x0000000200000020LLU");

   }

#endif

   if ((uptr)p < QUOTED_KERNEL_SPACE)
   {

      if (p == nullptr)
      {

         simple_debug_print("Free_check_pointer_in_cpp FREEING nullptr?!?! WHAT!! == nullptr!!");

      }
      else
      {

         simple_debug_print("Free_check_pointer_in_cpp WHAT!! < " STR(QUOTED_KERNEL_SPACE));

      }

   }

}


void * plex_heap_alloc_array::operator new(size_t s)
{

   return system_heap_alloc(sizeof(plex_heap_alloc_array));

}


void plex_heap_alloc_array::operator delete(void * p)
{

   system_heap_free(p);

}


plex_heap_alloc * plex_heap_alloc_array::find(memsize nAllocSize)
{

   for (index i = 0; i < m_nSize; i++)
   {

      auto palloc = m_pData[i];

      if (nAllocSize <= palloc->m_iAllocSize)
      {

         if (palloc->m_iAllocSize == 16384)
         {

            //::output_debug_string(".");

         }

         return m_pData[i];

      }

   }

   return nullptr;

}


void * plex_heap_alloc_array::_alloc(memsize size)
{

   plex_heap_alloc * palloc = find(size);

   if (palloc != nullptr)
   {

      ::HEAP_NAMESPACE::on_plex_heap_alloc(palloc);

      return palloc->Alloc();

   }
   else
   {

      ::HEAP_NAMESPACE::on_system_heap_alloc(size);

      return ::system_heap_alloc(size);

   }

}


void plex_heap_alloc_array::_free(void * p,memsize size)
{

   plex_heap_alloc * palloc = find(size);

   if(palloc != nullptr)
   {

      ASSERT(size <= palloc->m_iAllocSize);

      return palloc->Free(p);

   }
   else
   {

      return ::system_heap_free(p);

   }

}


void * plex_heap_alloc_sync::Alloc()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   if (m_pnodeFree == nullptr)
   {

      //if (m_nAllocSize == 128)
      //{

      //   output_debug_string("plex_heap_alloc_sync::Alloc 128");

      //}

      NewBlock();

   }

   void * pnode = m_pnodeFree;

   m_pnodeFree = m_pnodeFree->m_pnext;

   ::zero(pnode, m_nAllocSize);

   return pnode;

}


void * g_pDebugPointer = nullptr;

CLASS_DECL_ACME void set_debug_pointer(void * p)
{

   g_pDebugPointer = p;

}

void plex_heap_alloc_sync::Free(void * pParam)
{
   if (m_nAllocSize == 128)
   {
      u64 & u = ((u64 &)pParam);

      if ((u & 0xff000000) == 00)
      {
         //output_debug_string("");

      }

   }
   if ((byte *) 0x0000000200000020 == ((byte *)pParam))
   {

      DEBUG_BREAK;

   }
   //else if ((((iptr)pParam) & 0xcccccc) == 0xcccccc)
   //{

   //   debug_break();

   //}
   else if (pParam == g_pDebugPointer)
   {

      //output_debug_string("test");

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

   ::memcpy_dup(m_pnodeLastBlock, pnode, m_nAllocSize + 32);

#endif

   pnode->m_pnext = m_pnodeFree;

   m_pnodeFree = pnode;

}



#undef new


class CLASS_DECL_ACME plex_heap     // warning ::payload length structure
{
public:


   plex_heap *    m_pheapNext;
   byte           m_data; // first data byte of this ::payload length structure


   void * data() { return &m_data; }


   static plex_heap* create(plex_heap*& head, uptr nMax, uptr cbElement);


   void FreeDataChain();


};



plex_heap * plex_heap::create(plex_heap * & pheapHead, uptr nMax, uptr cbElement)
{

   ASSERT(nMax > 0 && cbElement > 0);

   if (nMax == 0 || cbElement == 0)
   {

      __throw(error_invalid_argument);

   }

   auto pheap = (plex_heap *) system_heap_alloc(sizeof(plex_heap) + nMax * cbElement);

#ifdef XXDEBUG

   Alloc_check_pointer_in_cpp(pheap);

#endif // XXDEBUG

   pheap->m_pheapNext = pheapHead;

   pheapHead = pheap;

   return pheap;

}


void plex_heap::FreeDataChain()     // free this one and links
{

   plex_heap * pheap = this;

   while (pheap != NULL)
   {

      byte * pbytes = (byte *) pheap;

      auto pheapNext = pheap->m_pheapNext;

      system_heap_free(pbytes);

      pheap = pheapNext;

   }

}


void plex_heap_alloc_sync::FreeAll()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   try
   {

      m_pBlocks->FreeDataChain();

      m_pBlocks = nullptr;

      m_pnodeFree = nullptr;

   }
   catch(...)
   {

   }

}


void plex_heap_alloc_sync::NewBlock()
{

   critical_section_lock synchronouslock(&m_criticalsection);

   ::u32 nAllocSize = m_nAllocSize;

   ::HEAP_NAMESPACE::on_plex_new_block(nAllocSize);

   plex_heap * pnewblock = plex_heap::create(m_pBlocks, m_nBlockSize, nAllocSize);

   auto pnode = (node *) pnewblock->data();

   node * pnodeNext = nullptr;

   auto nBlockSize = m_nBlockSize;

   for (i32 i = 0; i < nBlockSize; i++)
   {

      pnode->m_pnext = pnodeNext;

      pnodeNext = pnode;

      pnode = (node *) &((byte *) pnode)[nAllocSize];

   }

   if ((byte *)0x0000000200000020 == ((byte *)pnodeNext))
   {

      DEBUG_BREAK;

   }

   m_pnodeFree = pnodeNext;

#ifdef XXDEBUG

   Free_check_pointer_in_cpp(m_pnodeFree);

#endif // XXDEBUG

}
