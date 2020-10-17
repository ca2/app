#pragma once


#if !defined(_UWP)

   class CLASS_DECL_ACME shared_memory :
      public memory_base
   {
   public:


      UINT                                   m_nAllocFlags;
   HGLOBAL                                m_hGlobalMemory;
      bool                                   m_bAllowGrow;


      shared_memory(const memory_base & memory);
      shared_memory(memory_container * pmsc = nullptr, double dAllocationRateUp = 4096, UINT nAllocFlags = 0);
      shared_memory(memory_container * pmsc, void * pMemory, memsize dwSize);
      shared_memory(const void *, memsize iCount);
      virtual ~shared_memory();


      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = TRUE);
      
      virtual byte * impl_alloc(memsize nBytes) override;
      virtual byte * impl_realloc(void * pdata, memsize nBytes) override;
      virtual void impl_free(byte * pMem) override;



      byte * detach_shared_memory(HGLOBAL & hglobal);
      //byte * detach(HGLOBAL & hglobal);
//      virtual bool allocate_internal(memsize dwNewLength);



      //virtual ::matter * clone() override;

   };


#endif


