#include "framework.h"


#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG) && MEMDLEAK


#include "heap_memory.h"

#ifdef WINDOWS_DESKTOP
#include <mmsystem.h>
#endif // WINDOWS_DESKTOP




#define MEMDLEAK_DEFAULT 1

int g_iGlobalMemdleakEnabled;



extern class ::exception_engine * g_pexceptionengine;

thread_int_ptr < iptr > t_iMemdleak;

::mutex * g_pmutgen = nullptr;

extern memdleak_block * s_pmemdleakList;

thread_pointer < memdleak_block > t_plastblock;

void memdleak_init();
void memdleak_term();






void * aligned_memory_allocate(size_t size, memsize align)
{

   void * p;

   throw_todo();

   p = unaligned_memory_allocate(size);

   //zero(p, size);

   return p;

}

void * unaligned_memory_allocate(size_t size)
{

   void * p;

   size_t nAllocSize = sizeof(memdleak_block) + size;

   memdleak_block * pblock;

   pblock = (memdleak_block *) class ::system_heap_alloc(nAllocSize);

   pblock->m_iBlockUse = 0;

   if (g_pexceptionengine == nullptr)
   {
//      pblock->m_puiStack = nullptr;
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;
   }
   else
   {
      //string strCallStack;
      //::exception_engine().stack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
      ::exception_engine().backtrace(pblock->m_puiStack, pblock->m_iStack);
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

   zero(p, size);

   return p;

}


void * aligned_memory_allocate_debug(size_t size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
{

   void * p;

   throw_todo();

   p = unaligned_memory_allocate(size);


   //zero(p, size);

   return p;

}


void * unaligned_memory_allocate_debug(size_t size, i32 nBlockUse, const char * szFileName, i32 nLine)
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


void * memory_allocate_no_track(size_t size)
{


#if defined(__APPLE__)

   return aligned_memory_allocate(size);

#else

   return unaligned_memory_allocate(size);

#endif


}




void * memory_calloc(size_t size, size_t bytes)
{

   return memory_allocate(size * bytes);

}


void * memory_allocate_debug(size_t nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

}


void * memory_reallocate(void * pmemory, size_t nSize)
{

   return memory_reallocate_debug(pmemory, nSize, 0, nullptr, -1);

}





void * memory_reallocate_debug(void * pmemory, size_t size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   size_t nAllocSize = size + sizeof(memdleak_block);

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

   size_t * psizeNew = nullptr;

   pblock = (memdleak_block *) class ::system_heap_realloc(pblock, size + sizeof(memdleak_block));
   if (nAllocSize > pblock->m_size)
   {

      zero(&((byte*)pblock)[pblock->m_size], nAllocSize - pblock.m_size);

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
   //   //::exception_engine().stack_trace(1);
   //   pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
   //   ::exception_engine().backtrace(pblock->m_puiStack, pblock->m_iStack);
   //   pblock->m_pszFileName = nullptr;
   //}

   //::papaya::set_maximum(pblock->m_uiLine);

   //pblock->m_size = nAllocSize;

   //pblock->m_pprevious = nullptr;

   //pblock->m_pnext = s_pmemdleakList;

   //if (s_pmemdleakList != nullptr)
   //{

   //   s_pmemdleakList->m_pprevious = pblock;

   //}

   //s_pmemdleakList = pblock;
   pblock->m_iBlockUse = nBlockUse;

   if (g_pexceptionengine == nullptr)
   {
      //      pblock->m_puiStack = nullptr;
      pblock->m_iStack = 0;
      pblock->m_pszFileName = nullptr;
   }
   else
   {
      //string strCallStack;
      //::exception_engine().stack_trace(1);
      pblock->m_iStack = sizeof(pblock->m_puiStack) / sizeof(pblock->m_puiStack[0]);
      ::exception_engine().backtrace(pblock->m_puiStack, pblock->m_iStack);
      pblock->m_pszFileName = nullptr;
      //pblock->m_pszFileName = strdup(pszFileName); // not trackable, at least think so certainly causes memory leak
   }

   ::papaya::set_maximum(pblock->m_uiLine);

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
   // class ::system_heap_free((void *)pblock->m_pszFileName);
   //if (pblock->m_puiStack)
   // class ::system_heap_free((void *)pblock->m_puiStack);

   return class ::system_heap_free(pblock);


}



size_t memory_size(void * pmemory)
{

   return memory_size_debug(pmemory, _NORMAL_BLOCK);

}


size_t memory_size_debug(void * pmemory, i32 iBlockType)
{


   memdleak_block * pblock = &((memdleak_block *)pmemory)[-1];

   return pblock->m_size;


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

CLASS_DECL_ACME int  global_memdleak_enabled()
{

   if (g_iGlobalMemdleakEnabled == 0)
   {

      bool bMemdleak = false;

#ifdef WINDOWS

      u32 dwFileAttributes = windows_get_file_attributes(L"C:\\archive\\ca2\\config\\system\\memdleak.txt");

      bMemdleak = dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;

#else

      bMemdleak = ::m_psystem->m_pacmefile->exists("/archive/ca2/config/system/memdleak.txt");

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


typedef __pointer_array(memblock) memblocka;


string get_mem_info_report1()
{

   string str;

   int * piUse = nullptr;
   const char ** pszFile = nullptr;
   const char ** pszCallStack = nullptr;
   u32 * puiLine = nullptr;
   size_t * psize = nullptr;

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


      int_array ia;

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
         output_debug_string("\n");
         output_debug_string("--------------------------------------------------------\n");
         ansi_from_u64(sz, ++i, 10);
         output_debug_string("Index : ");
         output_debug_string(sz);
         output_debug_string("\n");
         ansi_from_u64(sz, pblock->m_size, 10);
         output_debug_string("Size : ");
         output_debug_string(sz);
         output_debug_string("\n");
#if FAST_STACK_TRACE
         output_debug_string(::exception_engine().stack_trace(pblock->m_puiStack + 1, pblock->m_iStack));
#else
         output_debug_string(::exception_engine().stack_trace(pblock->m_puiStack, pblock->m_iStack));
#endif
      }
      pblock = pblock->m_pnext;
   }
   output_debug_string("\n");
   output_debug_string("--------------------------------------------------------\n");
   ansi_from_u64(sz, i, 10);
   output_debug_string("\nFound ");
   output_debug_string(sz);
   output_debug_string(" memory leaks.");

   //m_psystem->m_pacmefile->put_contents(         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->system() / "m.html", get_mem_info_report1());
}

#undef print

#endif



void memdleak_init()
{

   g_pmutgen = new ::mutex();

}


void memdleak_term()
{

   ::acme::del(g_pmutgen);

}



#endif


