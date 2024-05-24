#pragma once


#define ZEROED_ALLOC 1




CLASS_DECL_ACID void *     memory_allocate_no_track(memsize size);



CLASS_DECL_ACID void *     memory_allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
CLASS_DECL_ACID void *     memory_reallocate_debug(void * p, memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
CLASS_DECL_ACID void       memory_free_debug(void * p, i32 iBlockType);
CLASS_DECL_ACID memsize    memory_size_debug(void* p, i32 iBlockType);






#if MEMDLEAK


CLASS_DECL_ACID int        memdleak_enabled();
CLASS_DECL_ACID void       memdleak_enable(int enable);
CLASS_DECL_ACID int        global_memdleak_enabled();
CLASS_DECL_ACID void       memdleak_init();
CLASS_DECL_ACID void       memdleak_term();


#endif


#if MEMDLEAK


CLASS_DECL_ACID void       set_last_block_file_name(const ::scoped_string & scopedstr);
CLASS_DECL_ACID void       memdleak_dump();


#endif

class CLASS_DECL_ACID system_heap :
   virtual public ::particle
{


#if MEMDLEAK || defined(__MCRTDBG)


   void * system_heap_alloc_debug(memsize size, int nBlockUse, const char * pszFile, int iLine);
   void * system_heap_realloc_debug(void * p, memsize size, int nBlockUse, const char * pszFile, int iLine);


#endif


   void * system_heap_alloc_normal(memsize size);
   void * system_heap_realloc_normal(void * pvoidOld, memsize size);
//
//
//#if MEMDLEAK  || defined(__MCRTDBG)
//
//
//#define system_heap_alloc(s)        system_heap_alloc_debug(s, 49, __FILE__, __LINE__)
//#define system_heap_realloc(p, s)   system_heap_realloc_debug(p, s, 49, __FILE__, __LINE__)
//
//
//#else
//
//
//#define system_heap_alloc(s)        system_heap_alloc_normal(s)
//#define system_heap_realloc(p, s)   system_heap_realloc_normal(p, s)
//
//
//#endif
//

   void                system_heap_free(void * p);
   memsize             system_heap_alloc_size(void * p);


};


struct memdleak_block
{


   i32                           m_iBlockUse;
   i32                           m_iEnabled;
   const char *                  m_pszFileName;
   void *                        m_stacka[64];
   int                           m_iStack;
   u32                           m_uiLine;
   memsize                       m_size;
   struct memdleak_block *       m_pnext;
   struct memdleak_block *       m_pprevious;

};



