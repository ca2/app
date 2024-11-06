#include "framework.h"
#include "default_heap.h"
#include "system_heap.h"
#include "acme/exception/__string.h"
#include "acme/exception/no_memory.h"
#include "acme/parallelization/synchronous_lock.h"
//
//
////#include "memory/os_alloc.h"
//
//
//#if MEMDLEAK
//
//
//
////extern ::critical_section * g_pmutgen;
////memdleak_block * s_pmemdleakList;
////extern thread_local memdleak_block * t_plastblock;
//
//
//#endif
//
////
////void * system_heap_alloc_normal(memsize size)
////{
////
////   void * p = ::__operating_system_memory_allocate(size);
////
////   if(p == nullptr)
////   {
////
////      throw no_memory();
////
////   }
////
////   return p;
////
////}
//namespace heap
//{
//
//
//   void * default_heap::allocate_debug(memsize size, int nBlockUse, const char * pszFile, int iLine)
//   {
//
//#if MEMDLEAK
//
//      if (!global_memdleak_enabled())
//      {
//
//         return system_heap_alloc_normal(size);
//
//      }
//
//#endif
//
//
//      void * p;
//
//      memsize nAllocSize = size + sizeof(memsize) + sizeof(memdleak_block);
//
//      memdleak_block * pblock;
//
//      pblock = (memdleak_block *)m_pallocator->allocate(nAllocSize);
//
//      p = pblock;
//
//      if (p == nullptr)
//      {
//
//         throw no_memory();
//
//      }
//
//      return p;
//
//   }
//
//
//
//   void * default_heap::reallocate_normal(void * p, memsize size)
//   {
//
//      return m_pallocator->reallocate(p, size);
//
//   }
//
//
//   memsize default_heap::allocation_size(void * p)
//   {
//
//      if (!m_pallocator->has_size())
//      {
//
//         return -1;
//
//      }
//
//      return m_pallocator->size(p);
//
//   }
//
//
//#ifdef MEMDLEAK
//
//
//   void * default_heap::reallocate_debug(void * p, memsize size, int nBlockUse, const char * pszFile, int iLine)
//   {
//
//#if MEMDLEAK
//
//      if (!global_memdleak_enabled())
//      {
//
//         return system_heap_realloc_normal(p, size);
//
//      }
//
//#endif
//
//      //memsize nAllocSize = size + sizeof(memsize) + sizeof(memdleak_block);
//
//      //memsize * psizeOld = &((memsize *)p)[-1];
//
//      //memdleak_block * pblock = &((memdleak_block *)psizeOld)[-1];
//
//      //synchronous_lock lock(g_pmutgen);
//
//      //if(s_pmemdleakList == pblock)
//      //{
//      //   s_pmemdleakList = pblock->m_pnext;
//      //   s_pmemdleakList->m_pprevious = nullptr;
//      //}
//      //else
//      //{
//      //   pblock->m_pprevious->m_pnext = pblock->m_pnext;
//      //   if(pblock->m_pnext != nullptr)
//      //   {
//      //      pblock->m_pnext->m_pprevious = pblock->m_pprevious;
//      //   }
//      //}
//
//      //if(pblock->m_pszCallStack)
//      //::free((void *)pblock->m_pszCallStack);
//      //if(pblock->m_pszFileName)
//      //::free((void *) pblock->m_pszFileName);
//
//      //memsize * psizeNew = nullptr;
//
//      p = (memdleak_block *)m_pallocator->reallocate(p, size);
//
//
//      //   p->m_iEnabled = memdleak_enabled();
//
//         //psizeNew = (memsize *) &pblock[1];
//
//         //psizeNew[0] = nAllocSize;
//
//         //pblock->m_iBlockUse     = nBlockUse;
//         //if (g_ee == nullptr)
//         //{
//         //   pblock->m_pszCallStack = nullptr;
//         //   pblock->m_pszFileName = nullptr;
//         //}
//         //else
//         //{
//         //   string strCallStack;
//         //   g_ee->xxxstack_trace(1);
//         //   pblock->m_pszCallStack = strdup(g_ee->_strS);
//         //   pblock->m_pszFileName = strdup(pszFileName == nullptr ? "" : pszFileName);
//         //}
//
//         //
//         //pblock->m_iLine         = iLine;
//         //pblock->m_iSize         = nAllocSize;
//
//
//         //pblock->m_pprevious                 = nullptr;
//         //pblock->m_pnext                     = s_pmemdleakList;
//         //if(s_pmemdleakList != nullptr)
//         //{
//         //   s_pmemdleakList->m_pprevious        = pblock;
//         //}
//         //s_pmemdleakList                     = pblock;
//         //lock.unlock();
//
//
//         //return &psizeNew[1];
//
//      return p;
//
//      //   memsize * psize (memsize *) g_pheap->realloc_debug(&((memsize *)pvoidOld)[-1], ((memsize *)pvoidOld)[-1], size + sizeof(memsize), nBlockUse, szFileName, iLine);
//         // psize[0] = size + sizeof(memsize);
//         //return &psize[1];
//
//   }
//
//#endif
//
//
//
//   void default_heap::free(void * p)
//   {
//
//#if defined(__VLD) || defined(__MCRTDBG)
//
//      return free(p);
//
//#else
//
//#if MEMDLEAK
//      if (!global_memdleak_enabled())
//#endif
//      {
//
//         try
//         {
//
//            m_pallocator->free(p);
//
//         }
//         catch (...)
//         {
//
//            //informationf("system_heap_free : Failed to free memory");
//
//         }
//
//#endif
//      }
//
//#if MEMDLEAK
//      else
//      {
//         /*
//            memsize * psize = &((memsize *)p)[-1];
//
//            memdleak_block * pblock = &((memdleak_block *)psize)[-1];
//
//            if(s_pmemdleakList != nullptr)
//            {
//
//               synchronous_lock lock(g_pmutgen);
//
//               if(s_pmemdleakList == pblock)
//               {
//                  s_pmemdleakList = pblock->m_pnext;
//                  s_pmemdleakList->m_pprevious = nullptr;
//               }
//               else
//               {
//                  pblock->m_pprevious->m_pnext = pblock->m_pnext;
//                  if(pblock->m_pnext != nullptr)
//                  {
//                     pblock->m_pnext->m_pprevious = pblock->m_pprevious;
//                  }
//               }
//               if(pblock->m_pszCallStack)
//               ::free((void *)pblock->m_pszCallStack);
//               if(pblock->m_pszFileName)
//               ::free((void *) pblock->m_pszFileName);
//
//            }
//         */
//         ::__operating_system_memory_free(p);
//      }
//
//#endif
//
//
//   }
//
//
//} // namespace heap
//
//
//
////typedef DWORD64[64]
////::collection::count get_mem_info2(int ** ppiUse, const char *** ppszFile, DWORD64 ** ppuiStack[64], huge_integer ** ppiStack, int ** ppiLine, huge_integer ** ppiSize)
////{
////
////#ifndef MEMDLEAK
////
////   throw ::exception(::exception("plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined"));
////
////#endif
////
////   synchronous_lock lock(g_pmutgen);
////
////   memdleak_block * pblock = s_pmemdleakList;
////
////   ::collection::count ca = 0;
////
////   while (pblock != nullptr)
////   {
////
////      ca++;
////
////      pblock = pblock->m_pnext;
////
////   }
////
////
////   int * piUse = (int *)malloc(sizeof(int) * ca);
////   const char ** pszFile = (const char **)malloc(sizeof(const char *) * ca);
////   DWORD64 ** puiStack[64] = (DWORD64 **[64])malloc(sizeof(DWORD64[64]) * ca);
////   huge_integer * piStack = (huge_integer *)malloc(sizeof(huge_integer) * ca);
////   int * piLine = (int *)malloc(sizeof(int) * ca);
////   huge_integer * piSize = (huge_integer *)malloc(sizeof(huge_integer) * ca);
////
////   ::collection::index i = 0;
////
////   pblock = s_pmemdleakList;
////
////   while (pblock != nullptr && i < ca)
////   {
////      piUse[i] = pblock->m_iBlockUse;
////      pszFile[i] = pblock->m_pszFileName == nullptr ? nullptr : _strdup(pblock->m_pszFileName);
////      ::memory_copy(puiStack[i], pblock->m_puiStack, pblock->m_iStack * sizeof(DWORD64));
////      piStack[i] = pblock->m_iStack;
////      piLine[i] = pblock->m_iLine;
////      piSize[i] = pblock->m_iSize;
////
////      i++;
////
////      pblock = pblock->m_pnext;
////
////
////
////   }
////
////   *ppiUse = piUse;
////   *ppszFile = pszFile;
////   *ppuiStack = puiStack;
////   *ppiStack = piStack;
////   *ppiLine = piLine;
////   *ppiSize = piSize;
////
////
////   return ca;
////
////}
////
//
//#ifdef MEMDLEAK
//void set_last_block_file_name(const ::scoped_string & scopedstr)
//{
//
//   //t_plastblock->m_pszFileName = strdup(psz == nullptr ? "" : psz);
//
//}
//#endif
//
//
//
//int g_iGlobalMemdleakEnabled;
//
//
//CLASS_DECL_ACME int  global_memdleak_enabled()
//{
//
//   if (g_iGlobalMemdleakEnabled == 0)
//   {
//
//      bool bMemdleak = false;
//
//#ifdef WINDOWS
//
//      bMemdleak = ::file_exists("C:\\archive\\ca2\\config\\system\\memdleak.txt");
//
//#else
//
//      bMemdleak = ::file_system()->exists("/archive/ca2/config/system/memdleak.txt");
//
//#endif
//
//      if (bMemdleak)
//      {
//
//         g_iGlobalMemdleakEnabled = 1;
//
//      }
//      else
//      {
//
//         if (MEMDLEAK_DEFAULT)
//         {
//
//            g_iGlobalMemdleakEnabled = 1;
//
//         }
//         else
//         {
//
//            g_iGlobalMemdleakEnabled = -1;
//
//         }
//
//      }
//
//   }
//
//   return g_iGlobalMemdleakEnabled == 1;
//
//}
//
//
//
//
