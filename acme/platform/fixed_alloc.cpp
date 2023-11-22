#include "framework.h"
#include "fixed_alloc.h"
#include "fixed_alloc_impl.h"
#include "acme/operating_system/process.h"
#define HEAP_NAMESPACE_PREFIX main
#include "acme/memory/_____heap_namespace.h"


fixed_alloc_no_sync::fixed_alloc_no_sync(::u32 nAllocSize, ::u32 nBlockSize)
{
   if(nBlockSize <= 1)
      nBlockSize = 4;

   ASSERT(nAllocSize >= sizeof(node));
   ASSERT(nBlockSize > 1);

   if (nAllocSize < sizeof(node))
      nAllocSize = sizeof(node);
   if (nBlockSize <= 1)
      nBlockSize = 64;

   m_nAllocSize = nAllocSize;
   m_nBlockSize = nBlockSize;
   m_pnodeFree = nullptr;
   m_pBlocks = nullptr;
}

fixed_alloc_no_sync::~fixed_alloc_no_sync()
{
   FreeAll();
}

void fixed_alloc_no_sync::FreeAll()
{
   m_pBlocks->FreeDataChain();
   m_pBlocks = nullptr;
   m_pnodeFree = nullptr;
}

void fixed_alloc_no_sync::NewBlock()
{

   i32 nAllocSize = m_nAllocSize + 32;
   // add another block
   ::main_memory_allocate_heap::plex* pNewBlock = ::main_memory_allocate_heap::plex::create(m_pBlocks, m_nBlockSize, nAllocSize);

   // chain them into _free list
   node* pNode = (node*)pNewBlock->data();
   // _free in reverse order to make it easier to debug
   (::u8*&)pNode += (nAllocSize * m_nBlockSize) - nAllocSize;
   for (i32 i = m_nBlockSize-1; i >= 0; i--, (::u8*&)pNode -= nAllocSize)
   {
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
   }

   ASSERT(m_pnodeFree != nullptr);  // we must have something

}

/////////////////////////////////////////////////////////////////////////////
// fixed_alloc_sync
//

fixed_alloc_sync::fixed_alloc_sync(::u32 nAllocSize, ::u32 nBlockSize, i32 iShareCount)
{

   m_i = 0;
   
   m_iShareCount = iShareCount;
   
   m_allocptra.set_size(iShareCount);
   
   m_criticalsectiona.set_size(iShareCount);
   
   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {
      
      m_allocptra[i] = memory_new fixed_alloc_no_sync(nAllocSize + sizeof(i32), nBlockSize);
      
   }

}

fixed_alloc_sync::~fixed_alloc_sync()
{
   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }

}

void fixed_alloc_sync::FreeAll()
{

   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {

      m_criticalsectiona[i].lock();

#ifdef WINDOWS

      __try
      {
         m_allocptra[i]->FreeAll();
      }
      __finally
      {
         m_criticalsectiona[i].unlock();
      }

#else

      try
      {
         m_allocptra[i]->FreeAll();
      }
      catch(...)
      {
      }

      m_criticalsectiona[i].unlock();
      
#endif

   }

}












/////////////////////////////////////////////////////////////////////////////
// fixed_alloc
//

fixed_alloc::fixed_alloc(::u32 nAllocSize, ::u32 nBlockSize)
{

   m_i = 0;

   i32 iShareCount = 0;

//#if defined(UNIVERSAL_WINDOWS) || defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//   i32 iShareCount = 0;
//#else
//   i32 iShareCount = system()->acmenode()->get_current_process_maximum_affinity() + 1;
//#endif

   if(iShareCount <= 0)
   {
      
      iShareCount = 4;
      
   }

   m_allocptra.set_size(iShareCount);

   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {
      
      m_allocptra[i] = memory_new fixed_alloc_sync(nAllocSize + sizeof(i32), nBlockSize, 12);
      
   }

   m_iShareCount = iShareCount;

}

fixed_alloc::~fixed_alloc()
{

   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }

}

void fixed_alloc::FreeAll()
{

   for(i32 i = 0; i < m_allocptra.get_count(); i++)
   {
#ifdef WINDOWS
      __try
      {
         m_allocptra[i]->FreeAll();
      }
      __finally
      {
      }
#else
      try
      {
         m_allocptra[i]->FreeAll();
      }
      catch(...)
      {
      }
#endif
   }

}

















/////////////////////////////////////////////////////////////////////////////
// fixed_alloc_array
//

fixed_alloc_array::fixed_alloc_array()
{
}



fixed_alloc_array::~fixed_alloc_array()
{
   for(i32 i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }
}

void * fixed_alloc_array::_alloc(size_t nAllocSize)
{
   fixed_alloc * palloc = find(nAllocSize);
   if(palloc != nullptr)
   {
      return palloc->Alloc();
   }
   else
   {
      return memory_allocate(nAllocSize);
   }
}


void fixed_alloc_array::_free(void * p, size_t nAllocSize)
{

   fixed_alloc * palloc = find(nAllocSize);

   if(palloc != nullptr)
   {

      return palloc->Free(p);

   }
   else
   {

      return ::memory_free(p);

   }

}


void * fixed_alloc_array::_realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{

   fixed_alloc * pallocOld = find(nOldAllocSize);

   fixed_alloc * pallocNew = find(nNewAllocSize);

   //if(pallocOld == nullptr && pallocNew == nullptr)
   //{

      //return ::memory_reallocate(pOld, nNewAllocSize);

   //}
   //else if(pallocOld == pallocNew)
   if (pallocOld == pallocNew)
   {

      return pOld;

   }
   else
   {

      void * pNew = pallocNew == nullptr ? memory_allocate(nNewAllocSize) : pallocNew->Alloc();

      if(pNew == nullptr)
         return nullptr;

      ::memory_copy(pNew, pOld, minimum(nOldAllocSize, nNewAllocSize));

      if(pallocOld != nullptr)
      {

         pallocOld->Free(pOld);

      }
      else
      {

         ::memory_free(pOld);

      }

      return pNew;

   }

}


fixed_alloc * fixed_alloc_array::find(size_t nAllocSize)
{
   //synchronous_lock lock(m_pmutex, true);
   size_t nFoundSize = UINT_MAX;
   i32 iFound = -1;
   for(i32 i = 0; i < this->get_count(); i++)
   {
      if(this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize >= nAllocSize
            && (nFoundSize == UINT_MAX || this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize < nFoundSize))
      {
         iFound = i;
         nFoundSize = this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize;
         break;
      }
   }
   if(iFound >= 0)
      return this->element_at(iFound);
   else
      return nullptr;
}
