//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//  Refactoring 2023-11-24 02:02 <3ThomasBorregaardSoerensen!!
//
#include "framework.h"
#include "heap.h"
#include "system_heap.h"
#include "acme/exception/__string.h"
#include "acme/exception/interface_only.h"
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


namespace heap
{


   heap::heap()
   {


   }


   heap:: ~heap()
   {


   }


   void heap::initialize_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory)
   {

      m_pallocator = pallocator;
      m_ememory = ememory;

   }


   void heap::start_heap()
   {



   }


   void * heap::allocate_debug(memsize size, int nBlockUse, const_char_pointer pszFile, int iLine, const_char_pointer pszAnnotation)
   {

      throw ::interface_only();

      return nullptr;

   }



   //Created by camilo on 2021-07-24 01:06 BRT <3ThomasBorregaardSorensen!!
//#include "__aligned_memory_allocate.h"
   void * heap::aligned_allocate(memsize size, memsize * psizeAllocated, memsize align, const_char_pointer pszAnnotation)
   {

      throw ::interface_only();

      return nullptr;

    }


   void * heap::aligned_allocate_debug(memsize nSize, memsize * psizeAllocated, int nBlockUse, const_char_pointer szFileName, int nLine, memsize align, const_char_pointer pszAnnotation)
   {

      throw ::interface_only();

      return nullptr;


    }


   //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
//#include "__unaligned_memory_allocate.h"
    void * heap::unaligned_allocate(memsize size, memsize * psizeAllocated, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;


    }

  

    void * heap::unaligned_allocate_debug(memsize nSize, memsize * psizeAllocated, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;


    }

    void * heap::count_allocate(::collection::count count, memsize size, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;


    }
   //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
   //#include "__memory_allocate.h"


#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)


    void * heap::allocate(memsize size, memsize * psizeAllocated, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;

    }



    void * heap::reallocate(void * p, memsize nSize, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;


    }


    void      heap::free(void * p)
    {

       throw ::interface_only();

    }


    memsize   heap::size(void * p)
    {

       throw ::interface_only();

       return -1;


    }


#endif


    //void * heap::allocate_debug(memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine)
    //{


    //   throw ::interface_only();

    //   return nullptr;

    //}


    void * heap::reallocate_debug(void * p, memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation)
    {

       throw ::interface_only();

       return nullptr;

    }


    void heap::free_debug(void * p, int iBlockType)
    {

       throw ::interface_only();

    }


    memsize   heap::size_debug(void * p, int iBlockType)
    {

       throw ::interface_only();

       return -1;


    }


} // namespace heap



//typedef DWORD64[64]
//::collection::count get_mem_info2(int ** ppiUse, const_char_pointer ** ppszFile, DWORD64 ** ppuiStack[64], long long ** ppiStack, int ** ppiLine, long long ** ppiSize)
//{
//
//#ifndef MEMDLEAK
//
//   throw ::exception(::exception("plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined"));
//
//#endif
//
//   synchronous_lock lock(g_pmutgen);
//
//   memdleak_block * pblock = s_pmemdleakList;
//
//   ::collection::count ca = 0;
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
//   int * piUse = (int *)malloc(sizeof(int) * ca);
//   const_char_pointer *pszFile = (const_char_pointer *)malloc(sizeof(const_char_pointer )* ca);
//   DWORD64 ** puiStack[64] = (DWORD64 **[64])malloc(sizeof(DWORD64[64]) * ca);
//   long long * piStack = (long long *)malloc(sizeof(long long) * ca);
//   int * piLine = (int *)malloc(sizeof(int) * ca);
//   long long * piSize = (long long *)malloc(sizeof(long long) * ca);
//
//   ::collection::index i = 0;
//
//   pblock = s_pmemdleakList;
//
//   while (pblock != nullptr && i < ca)
//   {
//      piUse[i] = pblock->m_iBlockUse;
//      pszFile[i] = pblock->m_pszFileName == nullptr ? nullptr : _strdup(pblock->m_pszFileName);
//      ::memory_copy(puiStack[i], pblock->m_puiStack, pblock->m_iStack * sizeof(DWORD64));
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
void set_last_block_file_name(const ::scoped_string & scopedstr)
{

   //t_plastblock->m_pszFileName = strdup(scopedstr == nullptr ? "" : psz);

}
#endif

#if !defined(MEMDLEAK_DEFAULT)
#define MEMDLEAK_DEFAULT 0
#endif

int g_iGlobalMemdleakEnabled;


CLASS_DECL_ACME int  global_memdleak_enabled()
{

   if (g_iGlobalMemdleakEnabled == 0)
   {

      bool bMemdleak = false;

#ifdef WINDOWS

      bMemdleak = ::file_exists("C:\\archive\\ca2\\config\\system\\memdleak.txt");

#else

      bMemdleak = file_exists("/archive/ca2/config/system/memdleak.txt");

#endif

      if (bMemdleak)
      {

         g_iGlobalMemdleakEnabled = 1;

      }
      else
      {

         if (MEMDLEAK_DEFAULT)
         {

            g_iGlobalMemdleakEnabled = 1;

         }
         else
         {

            g_iGlobalMemdleakEnabled = -1;

         }

      }

   }

   return g_iGlobalMemdleakEnabled == 1;

}




