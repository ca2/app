#pragma once


class CLASS_DECL_ACME plex_heap_alloc :
   public array < plex_heap_alloc_sync *, plex_heap_alloc_sync *, ::allocator::sys < plex_heap_alloc_sync * > >
{
public:

   // // Now alloc from any pool and release to any pool (not necessaraly the same allocated at) . save four bytes per allocation
   i32                      m_iAlloc; // Now alloc from any pool
   i32                      m_iFree; // and release to any pool
   i32                      m_iShareCount;
   i32                      m_iShareBound;
   i32                      m_iAllocSize;


   plex_heap_alloc(memsize nAllocSize, ::u32 nBlockSize = 64);
   virtual ~plex_heap_alloc();

   inline ::u32 GetAllocSize() { return m_iAllocSize; }

   void * Alloc();               // return a chunk of memory of nAllocSize
   void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

   void pre_finalize();

   void * operator new(size_t s);
   void operator delete(void * p);

};


inline void * plex_heap_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast

   auto iAlloc = m_iAlloc;

   m_iAlloc = (iAlloc + 1) % m_iShareCount;

   iAlloc %= m_iShareCount;

   return element_at(iAlloc)->Alloc();

}

inline void plex_heap_alloc::Free(void * p)
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast

   element_at((m_iFree++) % m_iShareCount)->Free(p);

}




//#define PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT 3

//#ifdef OS64BIT
//#define PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT 6
//#else
//#define PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT 5
//#endif

class CLASS_DECL_ACME plex_heap_alloc_array :
   public array < plex_heap_alloc *, plex_heap_alloc *, ::allocator::sys < plex_heap_alloc * > >
{
public:


   plex_heap_alloc_array();
   virtual ~plex_heap_alloc_array();


   plex_heap_alloc * find(memsize nAllocSize);


   void * _alloc(memsize size);
   void * _realloc(void * p, memsize nAllocSize, memsize nOldAllocSize, int align);
   void _free(void * p, memsize nAllocSize);

   void pre_finalize();

   void * alloc_debug(memsize nAllocSize, i32 nBlockUse, const char * szFileName, i32 iLine);
   void * realloc_debug(void * p, memsize nAllocSize, memsize nOldAllocSize, int align, i32 nBlockUse, const char * szFileName, i32 iLine);
   void free_debug(void * p, memsize nAllocSize);

   void * operator new(size_t s);

   void operator delete(void * p);


};


//#define memory_new ACME_NEW



