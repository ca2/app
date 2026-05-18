#pragma once


#include "acme/operating_system/shared_memory.h"
#include "acme/_operating_system.h"


namespace windows
{

   class CLASS_DECL_ACME shared_memory :
      virtual public ::shared_memory
   {
   public:


      //unsigned int                     m_nAllocFlags;
      //HGLOBAL                          m_hGlobalMemory;
      memsize m_memsize;
      HANDLE m_hToMap;
      //void *m_memory;

      //bool                             m_bAllowGrow;


      //shared_memory(const memory_base & memory);
      //shared_memory(memory_container * pmsc = nullptr, double dAllocationRateUp = 4096, unsigned int nAllocFlags = 0);
      //shared_memory(memory_container * pmsc, const void * pMemory, memsize dwSize);
      //shared_memory(const void *, memsize iCount);
      shared_memory();
      ~shared_memory() override;


      //virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = true);

      bool CreateSharedMemory(const char* name, memsize size) override;
      bool OpenSharedMemory(const char * name, memsize size) override;

      //virtual unsigned char * impl_alloc(memsize nBytes) override;
      //virtual unsigned char * impl_realloc(void * pdata, memsize nBytes) override;
      //virtual void impl_free(unsigned char * pMem) override;

void Close() override;

      //unsigned char * detach_shared_memory(HGLOBAL & hglobal);
      //unsigned char * detach(HGLOBAL & hglobal);
   //      virtual bool allocate_internal(memsize dwNewLength);

   protected:

      virtual bool _createFile(const char *name, memsize size);
      virtual void _mapViewOfFile();
      virtual void _setAllAccess(HANDLE handle);

         //virtual ::matter * clone() override;

   };


} // namespace windows


