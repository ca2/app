#include "framework.h"




fixed_alloc_no_sync::fixed_alloc_no_sync(unsigned int nAllocSize, unsigned int nBlockSize)
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

   int nAllocSize = m_nAllocSize + 32;
   // add another block
   plex* pNewBlock = plex::create(m_pBlocks, m_nBlockSize, nAllocSize);

   // chain them into _free list
   node* pNode = (node*)pNewBlock->data();
   // _free in reverse order to make it easier to debug
   (unsigned char*&)pNode += (nAllocSize * m_nBlockSize) - nAllocSize;
   for (int i = m_nBlockSize-1; i >= 0; i--, (unsigned char*&)pNode -= nAllocSize)
   {
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
   }

   ASSERT(m_pnodeFree != nullptr);  // we must have something

}

/////////////////////////////////////////////////////////////////////////////
// fixed_alloc_sync
//

fixed_alloc_sync::fixed_alloc_sync(unsigned int nAllocSize, unsigned int nBlockSize, int iShareCount)
{

   m_i = 0;
   m_iShareCount = iShareCount;
   m_allocptra.allocate(iShareCount);
   m_protectptra.allocate(iShareCount);
   for(int i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = aaa_primitive_new fixed_alloc_no_sync(nAllocSize + sizeof(int), nBlockSize);
   }
   for(int i = 0; i < m_protectptra.get_count(); i++)
   {
      m_protectptra[i] = aaa_primitive_new critical_section();
   }

   m_allocptra.allocate(iShareCount);
   m_protectptra.allocate(iShareCount);
   for(int i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = aaa_primitive_new fixed_alloc_no_sync(nAllocSize + sizeof(int), nBlockSize);
   }
   for(int i = 0; i < m_protectptra.get_count(); i++)
   {
      m_protectptra[i] = aaa_primitive_new critical_section();
   }
}

fixed_alloc_sync::~fixed_alloc_sync()
{
   for(int i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }
   for(int i = 0; i < m_protectptra.get_count(); i++)
   {
      delete m_protectptra[i];
   }
}

void fixed_alloc_sync::FreeAll()
{

   for(int i = 0; i < m_allocptra.get_count(); i++)
   {

      m_protectptra[i]->lock();

#ifdef WINDOWS

      __try
      {
         m_allocptra[i]->FreeAll();
      }
      __finally
      {
         m_protectptra[i]->unlock();
      }

#else

      try
      {
         m_allocptra[i]->FreeAll();
      }
      catch(...)
      {
      }

      m_protectptra[i]->unlock();
#endif

   }

}












/////////////////////////////////////////////////////////////////////////////
// fixed_alloc
//

fixed_alloc::fixed_alloc(unsigned int nAllocSize, unsigned int nBlockSize)
{

   m_i = 0;

#if defined(UNIVERSAL_WINDOWS) || defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
   int iShareCount = 0;
#else
   int iShareCount = ::get_current_process_maximum_affinity() + 1;
#endif

   if(iShareCount <= 0)
      iShareCount = 4;

   m_allocptra.allocate(iShareCount);

   for(int i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = aaa_primitive_new fixed_alloc_sync(nAllocSize + sizeof(int), nBlockSize, 12);
   }

   m_iShareCount = iShareCount;

}

fixed_alloc::~fixed_alloc()
{

   for(int i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }

}

void fixed_alloc::FreeAll()
{

   for(int i = 0; i < m_allocptra.get_count(); i++)
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
   for(int i = 0; i < this->get_count(); i++)
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
      return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nAllocSize);
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

      return ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(p);

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

      void * pNew = pallocNew == nullptr ? ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(nNewAllocSize) : pallocNew->Alloc();

      if(pNew == nullptr)
         return nullptr;

      ::memory_copy(pNew, pOld, minimum(nOldAllocSize, nNewAllocSize));

      if(pallocOld != nullptr)
      {

         pallocOld->Free(pOld);

      }
      else
      {

         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pOld);

      }

      return pNew;

   }

}


fixed_alloc * fixed_alloc_array::find(size_t nAllocSize)
{
   //synchronous_lock lock(m_pmutex, true);
   size_t nFoundSize = UINT_MAX;
   int iFound = -1;
   for(int i = 0; i < this->get_count(); i++)
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
