#pragma once


#include "plex_heap_alloc_sync.h"


class CLASS_DECL_ACME plex_heap_alloc :
   public ::proto < ::array < plex_heap_alloc_sync *, plex_heap_alloc_sync * > >
{
protected:

   
   friend class ::allocator::accessor;
   friend class plex_heap_alloc_array;


   plex_heap_alloc(::heap::allocator * pallocator, memsize nAllocSize, unsigned int nBlockSize = 64);
   virtual ~plex_heap_alloc();


public:

   // // Now alloc from any pool and release to any pool (not necessaraly the same allocated at) . save four bytes per allocation
   ::heap::allocator *      m_pallocator;
   int                      m_iAlloc; // Now alloc from any pool
   int                      m_iFree; // and release to any pool
   int                      m_iShareCount;
   int                      m_iShareBound;
   int                      m_iAllocSize;



   inline unsigned int GetAllocSize() { return m_iAllocSize; }

   void * Alloc();               // return a chunk of memory of nAllocSize
   void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

   void pre_finalize();

   //void * operator new(size_t s);
   //void operator delete(void * p);


   //plex_heap_alloc_sync * new_plex_heap_alloc_sync(memsize nAllocSize, unsigned int nBlockSize = 64);
   //void delete_plex_heap_alloc_sync(plex_heap_alloc_sync *p);



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
