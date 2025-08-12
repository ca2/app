#pragma once


class plex_heap;


class CLASS_DECL_ACME plex_heap_alloc_sync
{
protected:


   friend class ::allocator::accessor;
   friend class plex_heap_alloc;


   plex_heap_alloc_sync(::heap::allocator * pallocator, memsize nAllocSize, unsigned int nBlockSize = 64);
   virtual ~plex_heap_alloc_sync();


public:


   struct node
   {

      node * m_pnext; // only valid when in free list_base

   };


   ::heap::allocator *              m_pallocator;
   int                              m_nAllocSize;  // int_size of each block from Alloc
   int                              m_nBlockSize;  // number of blocks to get at a time
   plex_heap *                      m_pBlocks;     // linked list_base of blocks (is nBlocks*nAllocSize)
   node*                            m_pnodeFree;   // first free node (nullptr if no free nodes)
   ::critical_section               m_criticalsection;
   long long                              m_iFreeHitCount;
   node *                           m_pnodeLastBlock;



   unsigned int GetAllocSize() { return m_nAllocSize; }

   void * Alloc();               // return a chunk of memory of nAllocSize
   void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();


};


