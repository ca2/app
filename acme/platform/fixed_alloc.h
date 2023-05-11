#pragma once


#include "acme/primitive/collection/address_array.h"


namespace main_memory_allocate_heap
{
 
   struct plex;

}


class CLASS_DECL_ACME fixed_alloc_no_sync
{
public:


   struct node
   {
      node* pNext;   // only valid when in free list
   };

   ::u32 m_nAllocSize;   // size_i32 of each block from Alloc
   ::u32 m_nBlockSize;   // number of blocks to get at a time
   ::main_memory_allocate_heap::plex* m_pBlocks;   // linked list of blocks (is nBlocks*nAllocSize)
   node* m_pnodeFree;   // first free node (nullptr if no free nodes)


   fixed_alloc_no_sync(::u32 nAllocSize, ::u32 nBlockSize = 64);
   ~fixed_alloc_no_sync();


   ::u32 GetAllocSize() { return m_nAllocSize; }


   inline void * Alloc();  // return a chunk of memory of nAllocSize
   inline void Free(void * p); // free chunk of memory returned from Alloc
   void FreeAll(); // free everything allocated from this allocator


   void NewBlock();

};


inline void * fixed_alloc_no_sync::Alloc()
{
   if (m_pnodeFree == nullptr)
   {
      NewBlock();
   }
   // erase the first available node from the free list
   void * pNode = m_pnodeFree;
   m_pnodeFree = m_pnodeFree->pNext;
   return (void *) (((u8 *)pNode) + 16);
}

inline void fixed_alloc_no_sync::Free(void * p)
{
   p = (void *) (((u8 *)p) - 16);
   if (p != nullptr)
   {
      // simply return the node to the free list
      node* pNode = (node*)p;
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
   }
}


class CLASS_DECL_ACME fixed_alloc_sync
{
public:


   i32                                       m_i;
   i32                                       m_iShareCount;
   ::array < ::critical_section >            m_criticalsectiona;
   address_array < fixed_alloc_no_sync * >   m_allocptra;


   fixed_alloc_sync(::u32 nAllocSize, ::u32 nBlockSize = 64, i32 iShareCount = 2);
   ~fixed_alloc_sync();


   inline void * Alloc();   // return a chunk of memory of nAllocSize
   inline void Free(void * p);   // free chunk of memory returned from Alloc
   void FreeAll();   // free everything allocated from this allocator


};




class CLASS_DECL_ACME fixed_alloc
{
public:


   i32                                         m_i;
   i32                                         m_iShareCount;
   address_array < fixed_alloc_sync * >            m_allocptra;


   fixed_alloc(::u32 nAllocSize, ::u32 nBlockSize = 64);
   ~fixed_alloc();


   inline void * Alloc();   // return a chunk of memory of nAllocSize
   inline void Free(void * p);   // free chunk of memory returned from Alloc
   void FreeAll();   // free everything allocated from this allocator


};




class CLASS_DECL_ACME fixed_alloc_array :
   public address_array < fixed_alloc * >
{
public:


   fixed_alloc_array();
   virtual ~fixed_alloc_array();

   void * _alloc(size_t nAllocSize);
   void _free(void * p, size_t nAllocSize);
   void * _realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);

   fixed_alloc * find(size_t nAllocSize);


};




// DECLARE_FIXED_ALLOC -- used in class definition
/*#define DECLARE_AXIS_FIXED_ALLOC(class_name) \
public: \
   void * operator new(size_t) { return s_palloc->Alloc(); } \
   void * operator new(size_t, void * p) { return p; } \
   void operator delete(void * p) { s_palloc->Free(p); } \
   void * operator new(size_t, const char *, i32) { return s_palloc->Alloc(); } \
   void operator delete(void * p, const char *, i32) { s_palloc->Free(p); } \
   static fixed_alloc * s_palloc;


// IMPLEMENT_FIXED_ALLOC -- used in class implementation file
#define IMPLEMENT_AXIS_FIXED_ALLOC_STATIC(class_name) \
fixed_alloc * class_name::s_palloc = nullptr;


#define IMPLEMENT_AXIS_FIXED_ALLOC_CONSTRUCTOR(class_name, block_size) \
class_name::s_palloc = memory_new fixed_alloc(sizeof(class_name), block_size);

#define IMPLEMENT_AXIS_FIXED_ALLOC_DESTRUCTOR(class_name) \
if(class_name::s_palloc != nullptr) \
{ \
   delete class_name::s_palloc; \
}*/






