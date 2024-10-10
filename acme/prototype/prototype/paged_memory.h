#pragma once


#include "memory_base.h"


class CLASS_DECL_ACME paged_memory :
   public memory_base
{
public:


   paged_memory();
   paged_memory(const void *, memsize iCount);
   paged_memory(const memory_base & memory);
   paged_memory(const ::scoped_string & scopedstr);
   paged_memory(memory_container * pcontainer, double dAllocationRateUp = 4096, ::u32 nAllocFlags = 0);
   paged_memory(memory_container * pcontainer, const void * pMemory, memsize dwSize);
   ~paged_memory() override;


   virtual ::u8 * impl_alloc(memsize dwAllocation) override;
   virtual ::u8 * impl_realloc(void * pdata, memsize dwAllocation) override;
   virtual void impl_free(::u8 * pdata) override;


};

