#pragma once


#include "acme/operating_system/shared_memory.h"
#include "acme/_operating_system.h"


namespace windows
{

   class CLASS_DECL_ACME shared_memory :
      virtual public ::shared_memory
   {
   public:


      //::u32                     m_nAllocFlags;
      //HGLOBAL                          m_hGlobalMemory;
      memsize m_memsize;
      HANDLE m_hToMap;
      //void *m_memory;

      //bool                             m_bAllowGrow;


      //shared_memory(const memory_base & memory);
      //shared_memory(memory_container * pmsc = nullptr, ::f64 dAllocationRateUp = 4096, ::u32 nAllocFlags = 0);
      //shared_memory(memory_container * pmsc, const void * pMemory, memsize dwSize);
      //shared_memory(const void *, memsize iCount);
      shared_memory();
      ~shared_memory() override;


      //virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = true);

      bool CreateSharedMemory(const_char_pointer pszName, memsize size) override;
      bool OpenSharedMemory(const_char_pointer pszName, memsize size) override;

      //virtual ::u8 * impl_alloc(memsize nBytes) override;
      //virtual ::u8 * impl_realloc(void * pdata, memsize nBytes) override;
      //virtual void impl_free(::u8 * pMem) override;

void Close() override;

      //::u8 * detach_shared_memory(HGLOBAL & hglobal);
      //::u8 * detach(HGLOBAL & hglobal);
   //      virtual bool allocate_internal(memsize dwNewLength);

   protected:

      virtual bool _createFile(const_char_pointer pszName, memsize size);
      virtual void _mapViewOfFile();
      virtual void _setAllAccess(HANDLE handle);

         //virtual ::matter * clone() override;

   };


} // namespace windows


