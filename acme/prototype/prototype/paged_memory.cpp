#include "framework.h"
#include "paged_memory.h"
#include "acme/memory/paged.h"


paged_memory::paged_memory()
{

}


paged_memory::paged_memory(const void * pdata, memsize iCount)
{

   set_size(iCount);

   ASSERT(is_memory_segment_ok(pdata, iCount));

   ::memory_copy(storage_begin(), pdata, iCount);

}


paged_memory::paged_memory(const memory_base & s)
{

   assign(s);

}


paged_memory::paged_memory(const ::scoped_string & scopedstr)
{

   from_string(scopedstr);

}


paged_memory::paged_memory(memory_container * pcontainer, const void * pdata, memsize size)
{

   m_beginStorage = nullptr;

   m_begin = nullptr;

   set_size(size);

   ASSERT(is_memory_segment_ok(pdata, (uptr)size));

   ::memory_copy(storage_begin(), pdata, (size_t)size);

}


paged_memory::paged_memory(memory_container * pcontainer, double dAllocationRateUp, unsigned int nAllocFlags)
{

   __UNREFERENCED_PARAMETER(nAllocFlags);

   m_beginStorage = nullptr;
   m_begin = nullptr;
   m_pcontainer = pcontainer;
   m_dAllocationRateUp = dAllocationRateUp;

}


paged_memory::~paged_memory()
{

   if (storage_begin() != nullptr)
   {

      try
      {

         impl_free(storage_begin());

      }
      catch (...)
      {

      }

   }

}


//unsigned char * paged_memory::detach()
//{

//   unsigned char * int_point          = storage_begin();

//   if(m_iOffset > 0)
//   {
//      paged_memory mem(m_pdata, m_cbStorage);

//      point = mem.detach();

//   }
//   else
//   {

//      point = storage_begin();

//   }

//   storage_begin()       = nullptr;

//   m_cbStorage       = 0;

//   m_iSize    = 0;

//   return point;

//}


unsigned char * paged_memory::impl_alloc(memsize dwAllocation)
{

   return (unsigned char *) ::paged_allocate((size_t)dwAllocation);

}


unsigned char * paged_memory::impl_realloc(void * pdata, memsize dwAllocation)
{

   return (unsigned char *) ::paged_reallocate(pdata, (size_t)size(), (size_t)dwAllocation);

}


void paged_memory::impl_free(unsigned char * pdata)
{

   return ::paged_free(pdata);

}



