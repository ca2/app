#pragma once


#define ZEROED_ALLOC 1




CLASS_DECL_AQUA void * unaligned_memory_alloc(memsize size);
CLASS_DECL_AQUA void * unaligned_memory_alloc_dbg(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);

CLASS_DECL_AQUA void * aligned_memory_alloc(memsize size, memsize align = 0);
CLASS_DECL_AQUA void * aligned_memory_alloc_dbg(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align = 0);
CLASS_DECL_AQUA void * memory_alloc_no_track(memsize size);
CLASS_DECL_AQUA void * memory_calloc(memsize size, memsize bytes);
CLASS_DECL_AQUA void * memory_alloc_dbg(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
CLASS_DECL_AQUA void * memory_realloc_dbg(void * p, memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
CLASS_DECL_AQUA void   memory_free_dbg(void * p, i32 iBlockType);

CLASS_DECL_AQUA memsize memory_size(void * p);
CLASS_DECL_AQUA memsize memory_size_dbg(void * p, i32 iBlockType);



#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)
CLASS_DECL_AQUA void * CDECL memory_alloc(memsize size);
CLASS_DECL_AQUA void * CDECL memory_realloc(void * p, memsize nSize);
CLASS_DECL_AQUA void   CDECL memory_free(void * p);
#endif

#if MEMDLEAK
CLASS_DECL_AQUA int  memdleak_enabled();
CLASS_DECL_AQUA void memdleak_enable(int enable);
CLASS_DECL_AQUA int  global_memdleak_enabled();
CLASS_DECL_AQUA void memdleak_init();
CLASS_DECL_AQUA void memdleak_term();
#endif



#if MEMDLEAK
CLASS_DECL_AQUA void set_last_block_file_name(const char * psz);
CLASS_DECL_AQUA void memdleak_dump();
#endif

#if MEMDLEAK  || defined(__MCRTDBG)
CLASS_DECL_AQUA void * system_heap_alloc_dbg(memsize size, int nBlockUse, const char * pszFile, int iLine);
CLASS_DECL_AQUA void * system_heap_realloc_dbg(void * p, memsize size, int nBlockUse, const char * pszFile, int iLine);
#endif

CLASS_DECL_AQUA void * system_heap_alloc_normal(memsize size);
CLASS_DECL_AQUA void * system_heap_realloc_normal(void * pvoidOld, memsize size);

#if MEMDLEAK  || defined(__MCRTDBG)
#define system_heap_alloc(s) system_heap_alloc_dbg(s, 49, __FILE__, __LINE__)
#define system_heap_realloc(p, s) system_heap_realloc_dbg(p, s, 49, __FILE__, __LINE__)
#else
#define system_heap_alloc(s) system_heap_alloc_normal(s)
#define system_heap_realloc(p, s) system_heap_realloc_normal(p, s)
#endif
CLASS_DECL_AQUA void   system_heap_free(void * p);
CLASS_DECL_AQUA memsize   system_heap_alloc_size(void * p);


struct memdleak_block
{


   i32                           m_iBlockUse;
   i32                           m_iEnabled;
   const char *                  m_pszFileName;
#if OSBIT == 32
   DWORD                         m_puiStack[64];
#else
   DWORD64                       m_puiStack[64];
#endif
   int                           m_iStack;
   u32                           m_uiLine;
   memsize                       m_size;
   struct memdleak_block *       m_pnext;
   struct memdleak_block *       m_pprevious;

};



