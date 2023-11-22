
::count get_mem_info(i32** ppiUse, const char*** ppszFile, const char*** ppszCallStack, u32** ppuiLine, memsize** ppsize);

#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG) && MEMDLEAK



#include "heap_memory.h"


//#ifdef WINDOWS_DESKTOP
//#include <mmsystem.h>
//#endif // WINDOWS_DESKTOP




#define MEMDLEAK_DEFAULT 1



thread_local  ::iptr t_iMemdleak;

::critical_section * g_pmutgen = nullptr;

memdleak_block * s_pmemdleakList;

thread_local  memdleak_block * t_plastblock;

void memdleak_init();
void memdleak_term();






void * aligned_memory_allocate(memsize size, memsize align)
{

   void * p;

   throw_todo();

   p = unaligned_memory_allocate(size);

   //zero(p, size);

   return p;

}

void * unaligned_memory_allocate(memsize size)
{

   void * p;

   memsize nAllocSize = sizeof(memdleak_block) + size;

   memdleak_block * pblock;

   pblock = (memdleak_block *) ::system_heap_alloc(nAllocSize);

   pblock->m_iBlockUse = 0;

#if !MEMDLEAK_CALL_STACK
//      pblock->m_puiStack = nullptr;
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;
#else
      //string strCallStack;
      //::exception_engine().xxxstack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_stacka) / sizeof(pblock->m_stacka[0]);
      ::get_call_stack_frames(pblock->m_stacka, pblock->m_iStack);
      pblock->m_pszFileName = nullptr;
      //pblock->m_pszFileName = strdup(pszFileName); // not trackable, at least think so certainly causes memory leak
#endif

   //::acme::set_maximum(pblock->m_uiLine);

   pblock->m_size = nAllocSize;

   critical_section_lock lock(g_pmutgen);

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

   zero(p, size);

   return p;

}


void * aligned_memory_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
{

   void * p;

   throw_todo();

   p = unaligned_memory_allocate(size);


   //zero(p, size);

   return p;

}


void * unaligned_memory_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   void * p;


   //p = unaligned_memory_allocate(size);

   p = unaligned_memory_allocate(size);


   //zero(p, size);

   return p;

}






#undef memory_allocate

void * memory_allocate(memsize size)
{

#if defined(__APPLE__)

   return aligned_memory_allocate(size);

#else

   return unaligned_memory_allocate(size);

#endif

}


void * memory_allocate_no_track(memsize size)
{


#if defined(__APPLE__)

   return aligned_memory_allocate(size);

#else

   return unaligned_memory_allocate(size);

#endif


}




void * memory_calloc(memsize size, memsize bytes)
{

   return memory_allocate(size * bytes);

}


void * memory_allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

}


void * memory_reallocate(void * pmemory, memsize nSize)
{

   return memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);

}





void * memory_reallocate_debug(void * pmemory, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   memsize nAllocSize = size + sizeof(memdleak_block);

   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   critical_section_lock lock(g_pmutgen);
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

   //if (s_pmemdleakList == pblock)
   //{
   //   s_pmemdleakList = s_pmemdleakList->m_pnext;
   //   s_pmemdleakList->m_pprevious = nullptr;
   //}
   //else
   //{
   //   pblock->m_pprevious->m_pnext = pblock->m_pnext;
   //   if (pblock->m_pnext != nullptr)
   //   {
   //      pblock->m_pnext->m_pprevious = pblock->m_pprevious;
   //   }
   //}

   //if (pblock->m_pszFileName)
   // class ::system_heap_free((void *)pblock->m_pszFileName);
   //if (pblock->m_puiStack)
   // class ::system_heap_free((void *)pblock->m_puiStack);

   memsize * psizeNew = nullptr;

   pblock = (memdleak_block *) ::system_heap_realloc(pblock, size + sizeof(memdleak_block));

   if (nAllocSize > pblock->m_size)
   {

      zero(&((::u8*)pblock)[pblock->m_size], nAllocSize - pblock->m_size);

   }
   //pblock->m_iBlockUse = nBlockUse;
   //if (g_pexceptionengine == nullptr)
   //{
   //   pblock->m_iStack = 0;
   //   pblock->m_pszFileName = nullptr;

   //}
   //else
   //{
   //   //string strCallStack;
   //   //::exception_engine().xxxxstack_trace(1);
   //   pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
   //   ::exception_engine().backtrace(pblock->m_puiStack, pblock->m_iStack);
   //   pblock->m_pszFileName = nullptr;
   //}

   //::acme::set_maximum(pblock->m_uiLine);

   //pblock->m_size = nAllocSize;

   //pblock->m_pprevious = nullptr;

   //pblock->m_pnext = s_pmemdleakList;

   //if (s_pmemdleakList != nullptr)
   //{

   //   s_pmemdleakList->m_pprevious = pblock;

   //}

   //s_pmemdleakList = pblock;
   pblock->m_iBlockUse = nBlockUse;

#if !MEMDLEAK_CALL_STACK
      //      pblock->m_puiStack = nullptr;
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;
#else
      //string strCallStack;
      //::exception_engine().xxxstack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_stacka) / sizeof(pblock->m_stacka[0]);
      ::get_call_stack_frames(pblock->m_stacka, pblock->m_iStack);
      pblock->m_pszFileName = nullptr;
      //pblock->m_pszFileName = strdup(pszFileName); // not trackable, at least think so certainly causes memory leak
#endif

   //::acme::set_maximum(pblock->m_uiLine);

   pblock->m_size = nAllocSize;

//   synchronous_lock lock(g_pmutgen);

   pblock->m_pprevious = nullptr;

   pblock->m_pnext = s_pmemdleakList;

   if (s_pmemdleakList != nullptr)
   {

      s_pmemdleakList->m_pprevious = pblock;

   }

   s_pmemdleakList = pblock;

   t_plastblock = pblock;

   lock.unlock();

//   p = &pblock[1];

   lock.unlock();


   return &pblock[1];


}


void memory_free(void * pmemory)
{

   return memory_free_debug(pmemory, 0);

}






void memory_free_debug(void * pmemory, i32 iBlockType)
{

   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   critical_section_lock lock(g_pmutgen);

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
   // class ::system_heap_free((void *)pblock->m_pszFileName);
   //if (pblock->m_puiStack)
   // class ::system_heap_free((void *)pblock->m_puiStack);

   return ::system_heap_free(pblock);

}



memsize memory_size(void * pmemory)
{

   return memory_size_debug(pmemory, _NORMAL_BLOCK);

}


memsize memory_size_debug(void * pmemory, i32 iBlockType)
{


   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   return pblock->m_size;


}




#undef memory_allocate


void* _memory_allocate(memsize size)
{

   //#if defined(__APPLE__) || defined(RASPBERRYPIOS) || defined(WINDOWS)

   return aligned_memory_allocate(size);

   //#else

   //   return unaligned_memory_allocate(size);

   //#endif

}


void* _memory_allocate_no_track(memsize size)
{

   //#if defined(__APPLE__) || defined(RASPBERRYPIOS)

   return aligned_memory_allocate(size);

   //#else

   //   return unaligned_memory_allocate(size);

   //#endif

}


void* _memory_count_allocate(memsize size, memsize bytes)
{

   return memory_allocate(size * bytes);

}


void* _memory_allocate_debug(memsize nSize, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   // return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

   return aligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

}


void* _memory_reallocate(void* pmemory, memsize nSize)
{

   return _memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);

}


void* _memory_reallocate_debug(void* pmemory, memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   if (pmemory == nullptr)
   {

      return _memory_allocate_debug(size, nBlockUse, szFileName, nLine);

   }

   heap_memory* pheapmemory = heap_memory_get(pmemory);

   if (pheapmemory->m_ememoryheap != HEAP_ENUMERATE)
   {

      return manage_memory_reallocate(pheapmemory->m_ememoryheap, pmemory, size);

   }

   ::u8 blockuse = pheapmemory->m_blockuse;

   memsize sizeOld = pheapmemory->m_size;

   ::u8 align = pheapmemory->m_align;

   void* p = heap_memory_base_get(pmemory);

   if (blockuse == 0) // aligned
   {

      p = g_pheap->_realloc(
         p,
         heap_memory_aligned_provision_get_size(size, align),
         heap_memory_aligned_provision_get_size(sizeOld, align),
         align);

   }
   else if (blockuse == 1) // unaligned
   {

      //TODO: to do the dbg version

      p = g_pheap->_realloc(
         p,
         heap_memory_unaligned_provision_get_size(size),
         heap_memory_unaligned_provision_get_size(sizeOld),
         0);

   }
   else if (blockuse == 128) // aligned
   {

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if (blockuse == 129) // unaligned
   {

      //TODO: to do the dbg version

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_unaligned_provision_get_size(size));

   }
   else if (blockuse == 2) // aligned
   {

      p = g_pheap->realloc_debug(
         p,
         heap_memory_aligned_provision_get_size(size, align),
         heap_memory_aligned_provision_get_size(sizeOld, align),
         align, nBlockUse, szFileName, nLine);

   }
   else if (blockuse == 3) // unaligned
   {

      //TODO: to do the dbg version

      p = g_pheap->realloc_debug(
         p,
         heap_memory_unaligned_provision_get_size(size),
         heap_memory_unaligned_provision_get_size(sizeOld),
         0, nBlockUse, szFileName, nLine);

   }
   else if (blockuse == 130) // aligned
   {

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_aligned_provision_get_size(size, align));

   }
   else if (blockuse == 131) // unaligned
   {

      //TODO: to do the dbg version

      p = system_heap_realloc(
         p,
         (size_t)heap_memory_unaligned_provision_get_size(size));

   }
   else
   {

      throw ::exception(error_exception);

   }

   if (p == nullptr)
   {

      return nullptr;

   }

   if (blockuse == 0 || blockuse == 2 || blockuse == 128 || blockuse == 130) // aligned
   {

      return heap_memory_aligned(p, size, blockuse, align, HEAP_ENUMERATE);

   }
   else if (blockuse == 1 || blockuse == 3 || blockuse == 129 || blockuse == 131) // unaligned
   {

      return heap_memory_unaligned(p, size, blockuse, HEAP_ENUMERATE);

   }
   else
   {

      throw ::exception(error_exception);

   }

   return nullptr;

}


void _memory_free(void* pmemory)
{

   return _memory_free_debug(pmemory, 0);

}


void _memory_free_debug(void* pmemory, i32 iBlockType)
{

   system_heap_free(pmemory);

}


memsize _memory_size(void* pmemory)
{

   return _memory_size_debug(pmemory, _NORMAL_BLOCK);

}


memsize _memory_size_debug(void* pmemory, i32 iBlockType)
{

#ifdef WINDOWS

   return _msize(pmemory);

#else

   return malloc_size(pmemory);

#endif

}
















CLASS_DECL_ACME int  memdleak_enabled()
{

   return global_memdleak_enabled() && (t_iMemdleak == (iptr) 1 || t_iMemdleak == (iptr)0);

}

CLASS_DECL_ACME void memdleak_enable(int enable)
{

   if (!enable)
   {

      t_iMemdleak = 1;

   }
   else
   {

      t_iMemdleak = -1;

   }


}






#if MEMDLEAK

#define print str+=

class memblock :
   virtual public ::matter
{
public:

   int 	m_iUse;
   string 	m_strFile;
   int		m_iLine;

   int		m_iCount;
   i64     m_iSize;

};


typedef pointer_array < memblock > memblocka;


string get_mem_info_report1()
{

   string str;

   int * piUse = nullptr;
   const char ** pszFile = nullptr;
   const char ** pszCallStack = nullptr;
   u32 * puiLine = nullptr;
   memsize * psize = nullptr;

   try
   {

      ::count c = get_mem_info(&piUse, &pszFile, &pszCallStack, &puiLine, &psize);

      memblocka bla;

      int j;


      for (int i = 0; i < c; i++)
      {
         for (j = 0; j < bla.get_size(); j++)
         {
            memblock * pbl = bla.ptr_at(j);
            if (pbl->m_iUse == piUse[i] && pbl->m_strFile == pszFile[i] && pbl->m_iLine == puiLine[i])
            {
               pbl->m_iCount++;
               pbl->m_iSize += psize[i];
               break;
            }
         }
         if (j == bla.get_size())
         {
            bla.add(__new(memblock));
            auto & pbl = bla[bla.get_upper_bound()];
            pbl->m_iUse = piUse[i];
            pbl->m_strFile = pszFile[i];
            pbl->m_iLine = puiLine[i];
            pbl->m_iCount = 1;
            pbl->m_iSize = psize[i];
         }
         //			free((void *) pszFile[i]);
      }


      ::i32_array ia;

      ia.set_size(bla.get_count());

      for (int i = 0; i < bla.get_count(); i++)
      {
         ia[i] = i;
      }

      int s;

      for (int i = 0; i < bla.get_count(); i++)
      {
         for (j = i + 1; j < bla.get_count(); j++)
         {
            if (bla[ia[i]]->m_iSize < bla[ia[j]]->m_iSize)
            {
               s = ia[i];
               ia[i] = ia[j];
               ia[j] = s;
            }
         }
      }

      print("<table>");
      print("<tbody>");
      print("<tr>");
      print("<td>");
      print("Block Use");
      print("</td>");
      print("<td>");
      print("File Name");
      print("</td>");
      print("<td>");
      print("Line");
      print("</td>");
      print("<td>");
      print("Count");
      print("</td>");
      print("<td>");
      print("Size");
      print("</td>");
      print("</tr>");


      for (int i = 0; i < bla.get_count(); i++)
      {
         if ((i % 2) == 0)
         {
            print("<tr style=\"background-color:#c0efb7;\">");
         }
         else
         {
            print("<tr style=\"background-color:#e0ffd7;\">");
         }
         print("<td>");
         print(::payload(bla[ia[i]]->m_iUse));
         print("</td>");
         print("<td>");
         print(bla[ia[i]]->m_strFile);
         print("</td>");
         print("<td>");
         print(::payload(bla[ia[i]]->m_iLine));
         print("</td>");
         print("<td>");
         print(::payload(bla[ia[i]]->m_iCount));
         print("</td>");
         print("<td>");
         print(::payload(bla[ia[i]]->m_iSize));
         print("</td>");
         print("</tr>");;
      }
      print("</tbody>");
      print("</table>");
   }
   catch (...)
   {

   }

   if (piUse)
      ::free(piUse);
   if (pszFile)
      ::free(pszFile);
   if (puiLine)
      ::free(puiLine);
   if (psize)
      ::free(psize);


   return str;

}

#undef print

void memdleak_dump()
{


   memdleak_block * pblock = s_pmemdleakList;

   char sz[24];
   int i = 0;
   while (pblock != nullptr)
   {
      if (pblock->m_iStack > 0)
      {
         informationf("\n");
         informationf("--------------------------------------------------------\n");
         ansi_from_u64(sz, ++i, 10);
         informationf("Index : ");
         information(sz);
         informationf("\n");
         ansi_from_u64(sz, pblock->m_size, 10);
         informationf("Size : ");
         information(sz);
         informationf("\n");
#if FAST_STACK_TRACE
         information(::exception_engine().xxxstack_trace(pblock->m_puiStack + 1, pblock->m_iStack));
#else
         information(::get_call_stack_trace(pblock->m_stacka, pblock->m_iStack));
#endif
      }
      pblock = pblock->m_pnext;
   }
   informationf("\n");
   informationf("--------------------------------------------------------\n");
   ansi_from_u64(sz, i, 10);
   informationf("\nFound ");
   information(sz);
   informationf(" memory leaks.");

   auto pacmedirectory = ::platform::get()->acmedirectory();

   ::platform::get()->acmefile()->put_contents(pacmedirectory->system() / "m.html", get_mem_info_report1());

}

#undef print

#endif



void memdleak_init()
{

   g_pmutgen = memory_new ::critical_section;

}


void memdleak_term()
{

   ::acme::del(g_pmutgen);

}



#endif



#if MEMDLEAK


::count get_mem_info(i32** ppiUse, const char*** ppszFile, const char*** ppszCallStack, u32** ppuiLine, memsize** ppsize)
{

   //throw ::exception(error_failed, "plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined");


   critical_section_lock lock(g_pmutgen);

   memdleak_block* pblock = s_pmemdleakList;

   ::count ca = 0;

   while (pblock != nullptr)
   {

      ca++;

      pblock = pblock->m_pnext;

   }


   i32* piUse = (i32*)malloc(sizeof(i32) * ca);
   const char** pszFile = (const char**)malloc(sizeof(const char*) * ca);
   const char** pszCallStack = (const char**)malloc(sizeof(const char*) * ca);
   u32* puiLine = (u32*)malloc(sizeof(u32) * ca);
   memsize* psize = (memsize*)malloc(sizeof(memsize) * ca);

   index i = 0;

   pblock = s_pmemdleakList;

   while (pblock != nullptr && i < ca)
   {
      piUse[i] = pblock->m_iBlockUse;
      pszFile[i] = pblock->m_pszFileName == nullptr ? nullptr : _strdup(pblock->m_pszFileName);
      pszCallStack[i] = pblock->m_iStack <= 0 ? nullptr : _strdup(::get_call_stack_trace(pblock->m_stacka, pblock->m_iStack));
      puiLine[i] = pblock->m_uiLine;
      psize[i] = pblock->m_size;

      i++;

      pblock = pblock->m_pnext;



   }

   *ppiUse = piUse;
   *ppszFile = pszFile;
   *ppszCallStack = pszCallStack;
   *ppuiLine = puiLine;
   *ppsize = psize;


   return ca;

   //#endif
   //
   //   return 0;

}

#endif // MEMDLEAK


