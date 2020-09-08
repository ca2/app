#pragma once



   class CLASS_DECL_APEX virtual_memory :
      public memory_base
   {
   public:


      virtual_memory(::object * pobject);
      virtual_memory(const void *, memsize iCount);
      virtual_memory(const memory_base & memory);
      virtual_memory(const char * psz);
      virtual_memory(memory_container * pcontainer = nullptr, double dAllocationRateUp = 4096, UINT nAllocFlags = 0);
      virtual_memory(memory_container * pcontainer, void * pMemory, memsize dwSize);
      virtual ~virtual_memory();


      void construct_memory(memory_container * pcontainer, memsize dwAllocationAddUp = 4096, UINT nAllocFlags = 0);


      virtual byte * impl_alloc(memsize dwAllocation) override;
      virtual byte * impl_realloc(void * pdata, memsize dwAllocation) override;
      virtual void impl_free(byte * pdata) override;

      //virtual ::object * clone() override;


   };

