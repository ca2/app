#include "framework.h"

#if !defined(__VLD) && defined(__MCRTDBG) && !MEMDLEAK

struct heap_memory
{


   i32              m_back;
   i32              m_blockuse;
   memsize               m_size;
   char                 m_paddingBefore[16];
   static const int     m_iPaddingAfter;


   inline static memsize aligned_provision_get_size(memsize size)
   {

      return size + sizeof(heap_memory) + m_iPaddingAfter + ALIGN_BYTE_COUNT - 1;

   }

   inline static memsize unaligned_provision_get_size(memsize size)
   {

      return size + sizeof(heap_memory) + m_iPaddingAfter;

   }

   inline static void * unaligned(void * pusermessage, memsize size, i32 blockuse)
   {

      void * pmemory = (void *)((iptr)pusermessage + sizeof(heap_memory));

      heap_memory * pheap = heap_get(pmemory);

      pheap->m_back = (i32)(((iptr)pmemory) - ((iptr)pusermessage));

      pheap->m_blockuse = blockuse;

      pheap->m_size = size;

      return pmemory;

   }


   inline static void * aligned(void * pusermessage, memsize size, i32 blockuse)
   {

      void * pmemory = (void *)((((iptr)pusermessage) + sizeof(heap_memory) + ALIGN_BYTE_COUNT - 1) & ((~((iptr)ALIGN_BYTE_COUNT - 1))));

      heap_memory * pheap = heap_get(pmemory);

      pheap->m_back = (i32)(((iptr)pmemory) - ((iptr)pusermessage));

      pheap->m_blockuse = blockuse;

      pheap->m_size = size;

      return pmemory;

   }


   inline static heap_memory * heap_get(void * pmemory)
   {

      return (heap_memory *)(((iptr)pmemory) - sizeof(heap_memory));

   }


   inline static void * base_get(void * pmemory)
   {

      return (void *)(((iptr)pmemory) - heap_get(pmemory)->m_back);

   }

   inline static i32 heap_get_block_use(void * pmemory)
   {

      return heap_get(pmemory)->m_blockuse;

   }


   inline static memsize heap_get_size(void * pmemory)
   {

      return heap_get(pmemory)->m_size;

   }


   inline void check_padding_after()
   {

      for(int i = 0; i < m_iPaddingAfter; i++)
      {

         if(((byte *)&m_paddingBefore[16])[m_size + i] != 0)
         {

//            ::output_debug_string("*&!@");

         }

      }

   }



};


const int heap_memory::m_iPaddingAfter = 16;





c_class c_class::s_cclass;


c_class::c_class()
{
}

c_class::c_class(const c_class &)
{
}

c_class::~c_class()
{
}


plex_heap_alloc_array * g_pheap = nullptr;





#define AXIS_MEMORY_MANAGEMENT true


#if AXIS_MEMORY_MANAGEMENT


#if !defined(__VLD) && !defined(__MCRTDBG)
void * aligned_memory_alloc(memsize size, memsize align)
{

   void * p;

   align = align <= 0 ? ALIGN_BYTE_COUNT : align;

#if defined(MCHECK)

   p = aligned_alloc(align, size);

#elif MEMDLEAK

   throw_todo();

   p = unaligned_memory_alloc(size);

#else

   if(g_pheap == nullptr)
   {

      void * pusermessage = system_heap_alloc(heap_memory::aligned_provision_get_size(size, align));

      if (pusermessage == nullptr)
      {

         return nullptr;

      }

      p = heap_memory::aligned(pusermessage, size, 128, align);

   }
   else
   {

      if (heap_memory::aligned_provision_get_size(size) == 831
            && heap_memory::aligned_provision_get_size(size) < 1024)
      {
         output_debug_string("*");
      }

      void * pusermessage = g_pheap->_alloc(heap_memory::aligned_provision_get_size(size, align));

      if (pusermessage == nullptr)
      {

         return nullptr;

      }

      p = heap_memory::aligned(pusermessage, size, 0, align);

   }

#endif

   //zero(p, size);

   return p;

}

void * unaligned_memory_alloc(memsize size)
{

   void * p;

#if defined(MCHECK)

   p =  malloc(size);

#elif MEMDLEAK
   memsize nAllocSize = size + sizeof(memdleak_block);

   memdleak_block * pblock;

   pblock = (memdleak_block *) ::system_heap_alloc(nAllocSize);

   pblock->m_iBlockUse = 0;

   if (g_ee == nullptr)
   {
//      pblock->m_puiStack = nullptr;
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;
   }
   else
   {
      //string strCallStack;
      //g_ee->stack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
      g_ee->backtrace(pblock->m_puiStack, pblock->m_iStack);
      pblock->m_pszFileName = nullptr;
      //pblock->m_pszFileName = strdup(pszFileName); // not trackable, at least think so certainly causes memory leak
   }

   ::papaya::set_maximum(pblock->m_uiLine);

   pblock->m_size = nAllocSize;

   synchronous_lock lock(g_pmutgen);

   pblock->m_pprevious = nullptr;

   pblock->m_pnext = s_pmemdleakList;

   if (s_pmemdleakList != nullptr)
   {

      s_pmemdleakList->m_pprevious = pblock;

   }

   s_pmemdleakList = pblock;

   t_plastblock = pblock;

   lock.unlock();

   p = &pblock[1];


#else

#if defined(APPLEOS) || defined(LINUX)

   p = aligned_memory_alloc(size);

#else

   void * pusermessage = g_pheap->_alloc(heap_memory::unaligned_provision_get_size(size));

   if (pusermessage == nullptr)
   {

      return nullptr;

   }
   else
   {

      p = heap_memory::unaligned(pusermessage, size, 2);

   }

#endif

#endif

   //zero(p, size);

   return p;

}


void * aligned_memory_alloc_dbg(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
{

   void * p;

   align = align <= 0 ? ALIGN_BYTE_COUNT : align;

#if defined(MCHECK)

   p = aligned_alloc(align, size);

#elif MEMDLEAK

   throw_todo();

   p = unaligned_memory_alloc(size);

#else

   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
   if(g_pheap == nullptr)
   {

      void * pusermessage = system_heap_alloc(heap_memory::aligned_provision_get_size(size, align));

      if (pusermessage == nullptr)
      {

         return nullptr;

      }

      p = heap_memory::aligned(pusermessage, size, 129, align);

   }
   else
   {

      void * pusermessage = g_pheap->alloc_dbg(heap_memory::aligned_provision_get_size(size, align), nBlockUse, szFileName, nLine);

      if (pusermessage == nullptr)
      {

         return nullptr;

      }

      p = heap_memory::aligned(pusermessage, size, 1, align);

   }

#endif

   //zero(p, size);

   return p;

}


void * unaligned_memory_alloc_dbg(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   void * p;

#if defined(MCHECK)

   return malloc(size);

#elif MEMDLEAK

   p = unaligned_memory_alloc(size);

#else


#ifdef APPLEOS

   p = aligned_memory_alloc(size);

#else

   UNREFERENCED_PARAMETER(nBlockUse);
   UNREFERENCED_PARAMETER(szFileName);
   UNREFERENCED_PARAMETER(nLine);

   //TODO: to do the dbg version
   //byte * p = (byte *) _system_heap_alloc_dbg(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
   void * pusermessage = g_pheap->alloc_dbg(heap_memory::unaligned_provision_get_size(size), nBlockUse, szFileName, nLine);

   if (pusermessage == nullptr)
   {

      return nullptr;

   }

   p = heap_memory::unaligned(pusermessage, size, 3);

#endif

#endif

   //zero(p, size);

   return p;

}


#endif

#if !defined(__VLD) && !defined(__MCRTDBG)




#if !defined(MCHECK)

#undef memory_alloc

void * memory_alloc(memsize size)
{

#if defined(APPLEOS)

   return aligned_memory_alloc(size);

#else

   return unaligned_memory_alloc(size);

#endif

}

#undef memory_alloc

#endif


void * memory_alloc_no_track(memsize size)
{

#if defined(MCHECK) || defined(__VLD) || defined(__MCRTDBG)

   return memory_alloc(size);

#else

#if defined(APPLEOS)

   return aligned_memory_alloc(size);

#else

   return unaligned_memory_alloc(size);

#endif

#endif

}




void * memory_calloc(memsize size, memsize bytes)
{

   return memory_alloc(size * bytes);

}


void * memory_alloc_dbg(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{
#ifdef MCHECK
   return memory_alloc(nSize);
#else
   return unaligned_memory_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
#endif

}

#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)

void * memory_realloc(void * pmemory, memsize nSize)
{

   return memory_realloc_dbg(pmemory, nSize, 0, nullptr, -1);

}
#endif






void * memory_realloc_dbg(void * pmemory, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

#if defined(__VLD)

   return realloc(pmemory, size);

#elif defined(__MCRTDBG)

   return _realloc_dbg(pmemory, size, _NORMAL_BLOCK, szFileName, nLine);

#elif defined(MCHECK)

   return memory_realloc(pmemory, size);

#elif MEMDLEAK
   memsize nAllocSize = size + sizeof(memdleak_block);

   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   synchronous_lock lock(g_pmutgen);

   if (s_pmemdleakList == pblock)
   {
      s_pmemdleakList = s_pmemdleakList->m_pnext;
      s_pmemdleakList->m_pprevious = nullptr;
   }
   else
   {
      pblock->m_pprevious->m_pnext = pblock->m_pnext;
      if (pblock->m_pnext != nullptr)
      {
         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
      }
   }

   //if (pblock->m_pszFileName)
   // ::system_heap_free((void *)pblock->m_pszFileName);
   //if (pblock->m_puiStack)
   // ::system_heap_free((void *)pblock->m_puiStack);

   memsize * psizeNew = nullptr;

   pblock = (memdleak_block *) ::system_heap_realloc(pblock, size + sizeof(memdleak_block));

   pblock->m_iBlockUse = nBlockUse;
   if (g_ee == nullptr)
   {
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;

   }
   else
   {
      //string strCallStack;
      //g_ee->stack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
      g_ee->backtrace(pblock->m_puiStack, pblock->m_iStack);
      pblock->m_pszFileName = nullptr;
   }

   ::papaya::set_maximum(pblock->m_uiLine);

   pblock->m_size = nAllocSize;

   pblock->m_pprevious = nullptr;

   pblock->m_pnext = s_pmemdleakList;

   if (s_pmemdleakList != nullptr)
   {

      s_pmemdleakList->m_pprevious = pblock;

   }

   s_pmemdleakList = pblock;
   lock.unlock();


   return &pblock[1];

#else

   if (pmemory == nullptr)
      return memory_alloc_dbg(size, nBlockUse, szFileName, nLine);

   byte blockuse = heap_memory::heap_get_block_use(pmemory);

   memsize sizeOld = heap_memory::heap_get_size(pmemory);

   void * pusermessage = nullptr;

   if(blockuse == 0) // aligned
   {

      pusermessage = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT);

   }
   else if(blockuse == 1) // aligned
   {

      //TODO: to do the dbg version

      pusermessage = g_pheap->realloc_dbg(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size),heap_memory::aligned_provision_get_size(sizeOld),ALIGN_BYTE_COUNT,nBlockUse,szFileName,nLine);

   }
   else if(blockuse == 128) // aligned
   {

      pusermessage = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));

   }
   else if(blockuse == 129) // aligned
   {

      //TODO: to do the dbg version

      pusermessage = realloc(heap_memory::base_get(pmemory),heap_memory::aligned_provision_get_size(size));

   }
   else if(blockuse == 2) // unaligned
   {

      pusermessage = g_pheap->_realloc(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0);

   }
   else if(blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      pusermessage = g_pheap->realloc_dbg(heap_memory::base_get(pmemory),heap_memory::unaligned_provision_get_size(size),heap_memory::unaligned_provision_get_size(sizeOld),0,nBlockUse,szFileName,nLine);

   }
   else
   {

      return nullptr;

   }

   if(pusermessage == nullptr)
   {

      return nullptr;

   }

   if(blockuse == 0 || blockuse == 1 || blockuse == 128 || blockuse == 129) // aligned
   {

      return heap_memory::aligned(pusermessage, size,blockuse);

   }
   else
   {

      return heap_memory::unaligned(pusermessage, size,blockuse);

   }

   return nullptr;

#endif

}

#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)

void memory_free(void * pmemory)
{

   return memory_free_dbg(pmemory, 0);

}

#endif





void memory_free_dbg(void * pmemory, i32 iBlockType)
{

#if defined(__VLD) || defined(MCHECK) || defined(__MCRTDBG)

   memory_free(pmemory);

#elif MEMDLEAK
   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   synchronous_lock lock(g_pmutgen);

   if (s_pmemdleakList == pblock)
   {
      s_pmemdleakList = s_pmemdleakList->m_pnext;
      if (s_pmemdleakList != nullptr)
      {
         s_pmemdleakList->m_pprevious = nullptr;

      }
   }
   else
   {
      if (pblock->m_pprevious != nullptr)
      {
         pblock->m_pprevious->m_pnext = pblock->m_pnext;
      }
      if (pblock->m_pnext != nullptr)
      {
         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
      }
   }
   //if (pblock->m_pszFileName)
   // ::system_heap_free((void *)pblock->m_pszFileName);
   //if (pblock->m_puiStack)
   // ::system_heap_free((void *)pblock->m_puiStack);

   return ::system_heap_free(pblock);


#else

   heap_memory * pheap =  ::heap_memory::heap_get(pmemory);

   void * pusermessage = (void *)(((iptr)pmemory) - pheap->m_back);


   pheap->check_padding_after();


   if(pheap->m_blockuse == 0)
   {

      g_pheap->_free(pusermessage,heap_memory::aligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 1)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(pusermessage,heap_memory::aligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 128)
   {

      system_heap_free(pusermessage);

   }
   else if(pheap->m_blockuse == 129)
   {

      //TODO: to do the dbg version

      system_heap_free(pusermessage);

   }
   else if(pheap->m_blockuse == 2)
   {

      g_pheap->_free(pusermessage,heap_memory::unaligned_provision_get_size(pheap->m_size));

   }
   else if(pheap->m_blockuse == 3)
   {

      //TODO: to do the dbg version

      g_pheap->free_dbg(pusermessage,heap_memory::unaligned_provision_get_size(pheap->m_size));

   }
   else
   {

      ::output_debug_string("wrong free");

   }
#endif

}


#endif

memsize memory_size(void * pmemory)
{

   return memory_size_dbg(pmemory, _NORMAL_BLOCK);

}

memsize memory_size_dbg(void * pmemory, i32 iBlockType)
{

#if defined(__VLD) || defined(__MCRTDBG)

   return _msize(pmemory);

#elif MEMDLEAK

   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   return pblock->m_size;

#elif defined(MCHECK)

   return malloc_usable_size(pmemory);

#else

   if (pmemory == nullptr)
      return 0;

   return heap_memory::heap_get_size(pmemory);

#endif

}


#else



void * aligned_memory_alloc(memsize size)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc(memsize size)
{

   return system_heap_alloc(size);

}


void * aligned_memory_alloc_dbg(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc_dbg(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return system_heap_alloc(size);

}




void * memory_alloc(memsize size)
{

   return system_heap_alloc(size);

}


void * memory_calloc(memsize size, memsize bytes)
{

   return calloc(size, bytes);

}


void * memory_alloc_dbg(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return system_heap_alloc(nSize);

}


void * memory_realloc(void * p, memsize nSize)
{

   return system_heap_realloc(pvoid, nSize);

}


void * memory_realloc_dbg(void * p, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{


   return system_heap_realloc(pvoid, size);



}

void memory_free(void * p)
{
   return system_heap_free(pvoid);
}


memsize memsize(void * p)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else
   return system_heap_alloc_size(pvoid);
#endif
}


void memory_free_dbg(void * p, i32 iBlockType)
{

   memory_free(pvoid);

}


memsize memory_size_dbg(void * p, i32 iBlockType)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else

   return system_heap_alloc_size(pvoid);
#endif
}


#endif







//id_space * create_id_space()
//{
//
//   return new id_space();
//
//}

/*
void destroy_id_space() // let it go with the ({"eco}system") processs
{

   delete ::acme::system::s_pidspace;

   ::acme::system::s_pidspace = nullptr;

}
*/


#endif




