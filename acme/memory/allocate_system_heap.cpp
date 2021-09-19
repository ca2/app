#include "framework.h"

//#include <crtdbg.h>


#include "memory/os_alloc.h"


#if MEMDLEAK


extern ::mutex * g_pmutgen;
memdleak_block * s_pmemdleakList;
extern thread_pointer < memdleak_block > t_plastblock;


#endif


void * system_heap_alloc_normal(memsize size)
{

   void * p = ::os_alloc(size);

   if(p == nullptr)
   {

      throw_memory_exception();

   }

   return p;

}


void * system_heap_alloc_debug(memsize size, int nBlockUse, const char * pszFileName, int iLine)
{

#if MEMDLEAK

   if (!global_memdleak_enabled())
   {

      return system_heap_alloc_normal(size);

   }

#endif


   void * p;

   memsize nAllocSize = size + sizeof(memsize) + sizeof(memdleak_block);

   memdleak_block * pblock;

   pblock = (memdleak_block *) ::os_alloc(nAllocSize);

   p = pblock;

   if(p == nullptr)
   {

      throw_memory_exception();

   }

   return p;

}



void * system_heap_realloc_normal(void * p, memsize size)
{

   return ::os_realloc(p, size);

}

memsize system_heap_alloc_size(void * p)
{

   return ::os_size(p);

}

#ifdef MEMDLEAK

void * system_heap_realloc_debug(void * p,  memsize size, i32 nBlockUse, const char * pszFileName, i32 iLine)
{

#if MEMDLEAK

   if (!global_memdleak_enabled())
   {

      return system_heap_realloc_normal(p, size);

   }

#endif

   //memsize nAllocSize = size + sizeof(memsize) + sizeof(memdleak_block);

   //memsize * psizeOld = &((memsize *)p)[-1];

   //memdleak_block * pblock = &((memdleak_block *)psizeOld)[-1];

   //synchronous_lock lock(g_pmutgen);

   //if(s_pmemdleakList == pblock)
   //{
   //   s_pmemdleakList = pblock->m_pnext;
   //   s_pmemdleakList->m_pprevious = nullptr;
   //}
   //else
   //{
   //   pblock->m_pprevious->m_pnext = pblock->m_pnext;
   //   if(pblock->m_pnext != nullptr)
   //   {
   //      pblock->m_pnext->m_pprevious = pblock->m_pprevious;
   //   }
   //}

   //if(pblock->m_pszCallStack)
   //::free((void *)pblock->m_pszCallStack);
   //if(pblock->m_pszFileName)
   //::free((void *) pblock->m_pszFileName);

   //memsize * psizeNew = nullptr;

   p = (memdleak_block *) ::os_realloc(p, size);


//   p->m_iEnabled = memdleak_enabled();

   //psizeNew = (memsize *) &pblock[1];

   //psizeNew[0] = nAllocSize;

   //pblock->m_iBlockUse     = nBlockUse;
   //if (g_ee == nullptr)
   //{
   //   pblock->m_pszCallStack = nullptr;
   //   pblock->m_pszFileName = nullptr;
   //}
   //else
   //{
   //   string strCallStack;
   //   g_ee->stack_trace(1);
   //   pblock->m_pszCallStack = strdup(g_ee->_strS);
   //   pblock->m_pszFileName = strdup(pszFileName == nullptr ? "" : pszFileName);
   //}

   //
   //pblock->m_iLine         = iLine;
   //pblock->m_iSize         = nAllocSize;


   //pblock->m_pprevious                 = nullptr;
   //pblock->m_pnext                     = s_pmemdleakList;
   //if(s_pmemdleakList != nullptr)
   //{
   //   s_pmemdleakList->m_pprevious        = pblock;
   //}
   //s_pmemdleakList                     = pblock;
   //lock.unlock();


   //return &psizeNew[1];

   return p;

//   memsize * psize (memsize *) g_pheap->realloc_debug(&((memsize *)pvoidOld)[-1], ((memsize *)pvoidOld)[-1], size + sizeof(memsize), nBlockUse, szFileName, iLine);
   // psize[0] = size + sizeof(memsize);
   //return &psize[1];

}

#endif



void system_heap_free(void * p)
{

#if defined(__VLD) || defined(__MCRTDBG)

   return free(p);

#else

#if MEMDLEAK
   if (!global_memdleak_enabled())
#endif
   {

      try
      {

         ::os_free(p);

      }
      catch (...)
      {

         ::output_debug_string("system_heap_free : Failed to free memory");

      }

#endif
}

#if MEMDLEAK
else
{
   /*
      memsize * psize = &((memsize *)p)[-1];

      memdleak_block * pblock = &((memdleak_block *)psize)[-1];

      if(s_pmemdleakList != nullptr)
      {

         synchronous_lock lock(g_pmutgen);

         if(s_pmemdleakList == pblock)
         {
            s_pmemdleakList = pblock->m_pnext;
            s_pmemdleakList->m_pprevious = nullptr;
         }
         else
         {
            pblock->m_pprevious->m_pnext = pblock->m_pnext;
            if(pblock->m_pnext != nullptr)
            {
               pblock->m_pnext->m_pprevious = pblock->m_pprevious;
            }
         }
         if(pblock->m_pszCallStack)
         ::free((void *)pblock->m_pszCallStack);
         if(pblock->m_pszFileName)
         ::free((void *) pblock->m_pszFileName);

      }
   */
   ::os_free(p);
}

#endif

}


::count get_mem_info(i32 ** ppiUse, const char *** ppszFile, const char *** ppszCallStack, u32 ** ppuiLine, memsize ** ppsize)
{

#if MEMDLEAK

   __throw(::exception("plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined"));


   synchronous_lock lock(g_pmutgen);

   memdleak_block * pblock = s_pmemdleakList;

   ::count ca = 0;

   while(pblock != nullptr)
   {

      ca++;

      pblock = pblock->m_pnext;

   }


   i32 * piUse =(i32 *)  malloc(sizeof(i32) * ca);
   const char ** pszFile = (const char **) malloc(sizeof(const char *) * ca);
   const char ** pszCallStack = (const char **)malloc(sizeof(const char *) * ca);
   u32 * puiLine =(u32 *)  malloc(sizeof(u32) * ca);
   memsize * psize =(memsize *)  malloc(sizeof(memsize) * ca);

   index i = 0;

   pblock = s_pmemdleakList;

   while(pblock != nullptr && i < ca)
   {
      piUse[i] = pblock->m_iBlockUse;
      pszFile[i] = pblock->m_pszFileName== nullptr ? nullptr : _strdup(pblock->m_pszFileName);
      pszCallStack[i] = pblock->m_iStack <= 0 ? nullptr :_strdup(::exception_engine().stack_trace(pblock->m_puiStack, pblock->m_iStack));
      puiLine[i] = pblock->m_uiLine;
      psize] = pblock->m_size;

      i++;

      pblock = pblock->m_pnext;



   }

   *ppiUse = piUse;
   *ppszFile = pszFile;
   *ppszCallStack = pszCallStack;
   *ppuiLine = puiLine;
   *ppsize = psize;


   return ca;

#endif

   return 0;

}
//typedef DWORD64[64]
//::count get_mem_info2(i32 ** ppiUse, const char *** ppszFile, DWORD64 ** ppuiStack[64], i64 ** ppiStack, i32 ** ppiLine, i64 ** ppiSize)
//{
//
//#ifndef MEMDLEAK
//
//   __throw(::exception("plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined"));
//
//#endif
//
//   synchronous_lock lock(g_pmutgen);
//
//   memdleak_block * pblock = s_pmemdleakList;
//
//   ::count ca = 0;
//
//   while (pblock != nullptr)
//   {
//
//      ca++;
//
//      pblock = pblock->m_pnext;
//
//   }
//
//
//   i32 * piUse = (i32 *)malloc(sizeof(i32) * ca);
//   const char ** pszFile = (const char **)malloc(sizeof(const char *) * ca);
//   DWORD64 ** puiStack[64] = (DWORD64 **[64])malloc(sizeof(DWORD64[64]) * ca);
//   i64 * piStack = (i64 *)malloc(sizeof(i64) * ca);
//   i32 * piLine = (i32 *)malloc(sizeof(i32) * ca);
//   i64 * piSize = (i64 *)malloc(sizeof(i64) * ca);
//
//   index i = 0;
//
//   pblock = s_pmemdleakList;
//
//   while (pblock != nullptr && i < ca)
//   {
//      piUse[i] = pblock->m_iBlockUse;
//      pszFile[i] = pblock->m_pszFileName == nullptr ? nullptr : _strdup(pblock->m_pszFileName);
//      ::memcpy_dup(puiStack[i], pblock->m_puiStack, pblock->m_iStack * sizeof(DWORD64));
//      piStack[i] = pblock->m_iStack;
//      piLine[i] = pblock->m_iLine;
//      piSize[i] = pblock->m_iSize;
//
//      i++;
//
//      pblock = pblock->m_pnext;
//
//
//
//   }
//
//   *ppiUse = piUse;
//   *ppszFile = pszFile;
//   *ppuiStack = puiStack;
//   *ppiStack = piStack;
//   *ppiLine = piLine;
//   *ppiSize = piSize;
//
//
//   return ca;
//
//}
//

#ifdef MEMDLEAK
void set_last_block_file_name(const char * psz)
{

   //t_plastblock->m_pszFileName = strdup(psz == nullptr ? "" : psz);

}
#endif


