#pragma once


#include "acme/prototype/collection/address_array.h"


//namespace main_memory_allocate_heap
//{
// 
 struct plex;
//
//}


class CLASS_DECL_ACME fixed_alloc_no_sync
{
public:


   struct node
   {
      node* pNext;   // only valid when in free list
   };

   ::heap::allocator * m_pallocator;
   unsigned int m_nAllocSize;   // int_size of each block from Alloc
   unsigned int m_nBlockSize;   // number of blocks to get at a time
   ::plex* m_pBlocks;   // linked list of blocks (is nBlocks*nAllocSize)
   node* m_pnodeFree;   // first free node (nullptr if no free nodes)


   fixed_alloc_no_sync(::heap::allocator * pallocator, unsigned int nAllocSize, unsigned int nBlockSize = 64);
   ~fixed_alloc_no_sync();


   unsigned int GetAllocSize() { return m_nAllocSize; }


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
   return (void *) (((unsigned char *)pNode) + 16);
}

inline void fixed_alloc_no_sync::Free(void * p)
{
   p = (void *) (((unsigned char *)p) - 16);
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


   ::heap::allocator * m_pallocator;
   int                                       m_i;
   int                                       m_iShareCount;
   ::array < ::critical_section >            m_criticalsectiona;
   address_array < fixed_alloc_no_sync * >   m_allocptra;


   fixed_alloc_sync(::heap::allocator * pallocator, unsigned int nAllocSize, unsigned int nBlockSize = 64, int iShareCount = 2);
   ~fixed_alloc_sync();


   inline void * Alloc();   // return a chunk of memory of nAllocSize
   inline void Free(void * p);   // free chunk of memory returned from Alloc
   void FreeAll();   // free everything allocated from this allocator


};




class CLASS_DECL_ACME fixed_alloc
{
public:


   ::heap::allocator * m_pallocator;
   int                                         m_i;
   int                                         m_iShareCount;
   address_array < fixed_alloc_sync * >            m_allocptra;


   fixed_alloc(::heap::allocator * pallocator, unsigned int nAllocSize, unsigned int nBlockSize = 64);
   ~fixed_alloc();


   inline void * Alloc();   // return a chunk of memory of nAllocSize
   inline void Free(void * p);   // free chunk of memory returned from Alloc
   void FreeAll();   // free everything allocated from this allocator


};




class CLASS_DECL_ACME fixed_alloc_array :
   public address_array < fixed_alloc * >
{
public:


   ::heap::allocator * m_pallocator;

   fixed_alloc_array(::heap::allocator * pallocator);
   virtual ~fixed_alloc_array();

   void * _alloc(size_t nAllocSize, memsize * psizeAllocated);
   void _free(void * p, size_t nAllocSize);
   void * _realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);

   fixed_alloc * find(size_t nAllocSize, memsize * psizeFound);


};




// DECLARE_FIXED_ALLOC -- used in class definition
/*#define DECLARE_AXIS_FIXED_ALLOC(class_name) \
public: \
   void * operator new(size_t) { return s_palloc->Alloc(); } \
   void * operator new(size_t, void * p) { return p; } \
   void operator delete(void * p) { s_palloc->Free(p); } \
   void * operator new(size_t, const_char_pointer ,int) { return s_palloc->Alloc(); } \
   void operator delete(void * p, const_char_pointer ,int) { s_palloc->Free(p); } \
   static fixed_alloc * s_palloc;


// IMPLEMENT_FIXED_ALLOC -- used in class implementation file
#define IMPLEMENT_AXIS_FIXED_ALLOC_STATIC(class_name) \
fixed_alloc * class_name::s_palloc = nullptr;


#define IMPLEMENT_AXIS_FIXED_ALLOC_CONSTRUCTOR(class_name, block_size) \
class_name::s_palloc = __allocate< fixed_alloc(sizeof >(class_name), block_size);

#define IMPLEMENT_AXIS_FIXED_ALLOC_DESTRUCTOR(class_name) \
if(class_name::s_palloc != nullptr) \
{ \
   delete class_name::s_palloc; \
}*/






