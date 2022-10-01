#pragma once


class plex_heap;





class CLASS_DECL_ACME plex_heap_alloc_sync
{
public:


   struct node
   {

      node * m_pnext; // only valid when in free list

   };


   i32                        m_nAllocSize;  // size_i32 of each block from Alloc
   i32                        m_nBlockSize;  // number of blocks to get at a time
   plex_heap *                m_pBlocks;     // linked list of blocks (is nBlocks*nAllocSize)
   node*                      m_pnodeFree;   // first free node (nullptr if no free nodes)
   critical_section           m_criticalsection;
   i64                        m_iFreeHitCount;
   node *                     m_pnodeLastBlock;


   plex_heap_alloc_sync(memsize nAllocSize, ::u32 nBlockSize = 64);
   virtual ~plex_heap_alloc_sync();

   ::u32 GetAllocSize() { return m_nAllocSize; }

   void * Alloc();               // return a chunk of memory of nAllocSize
   void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

   void * operator new(size_t s);
   void operator delete(void * p);


};


