#pragma once


#include "memory_base.h"


class CLASS_DECL_ACME virtual_memory :
   public memory_base
{
public:


   virtual_memory();
   virtual_memory(const void *, memsize iCount);
   virtual_memory(const memory_base & memory);
   virtual_memory(const char * psz);
   virtual_memory(memory_container * pcontainer, double dAllocationRateUp = 4096, ::u32 nAllocFlags = 0);
   virtual_memory(memory_container * pcontainer, void * pMemory, memsize dwSize);
   ~virtual_memory() override;


   //void construct_memory(memory_container * pcontainer, memsize dwAllocationAddUp = 4096, ::u32 nAllocFlags = 0);


   virtual byte * impl_alloc(memsize dwAllocation) override;
   virtual byte * impl_realloc(void * pdata, memsize dwAllocation) override;
   virtual void impl_free(byte * pdata) override;

   //virtual ::matter * clone() override;


};

