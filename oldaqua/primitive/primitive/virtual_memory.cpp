#include "framework.h"



   virtual_memory::virtual_memory(::object * pobject)
   {

      m_memory.m_pbStorage = nullptr;
      m_memory.m_pbComputed = nullptr;

   }


   virtual_memory::virtual_memory(const void * pdata, memsize iCount)
   {

      m_memory.m_pbStorage = nullptr;

      m_memory.m_pbComputed = nullptr;

      set_size(iCount);

      ASSERT(__is_valid_address(pdata, iCount, FALSE));

      ::memcpy_dup(m_memory.m_pbStorage, pdata, iCount);

   }


   virtual_memory::virtual_memory(const memory_base & s)
   {

      m_memory.m_pbStorage = nullptr;

      m_memory.m_pbComputed = nullptr;

      memory_base::operator = (s);

   }


   virtual_memory::virtual_memory(const char * psz)
   {

      from_string(psz);

   }


   virtual_memory::virtual_memory(memory_container * pcontainer, void * pdata, memsize size)
   {

      m_memory.m_pbStorage = nullptr;

      m_memory.m_pbComputed = nullptr;

      set_size(size);

      ASSERT(__is_valid_address(pdata, (uptr) size, FALSE));

      ::memcpy_dup(m_memory.m_pbStorage, pdata, (size_t) size);

   }


   virtual_memory::virtual_memory(memory_container * pcontainer, double dAllocationRateUp, UINT nAllocFlags)
   {

      UNREFERENCED_PARAMETER(nAllocFlags);

      m_memory.m_pbStorage          = nullptr;
      m_memory.m_pbComputed = nullptr;
      m_memory.m_pcontainer         = pcontainer;
      m_memory.m_dAllocationRateUp  = dAllocationRateUp;

   }


   virtual_memory::~virtual_memory()
   {

      if(m_memory.m_pbStorage != nullptr)
      {

         try
         {

            impl_free(m_memory.m_pbStorage);

         }
         catch(...)
         {

         }

      }

   }


   //byte * virtual_memory::detach()
   //{

   //   byte * point          = m_pbStorage;

   //   if(m_iOffset > 0)
   //   {
   //      virtual_memory mem(m_pbComputed, m_cbStorage);

   //      point = mem.detach();

   //   }
   //   else
   //   {

   //      point = m_pbStorage;

   //   }

   //   m_pbStorage       = nullptr;

   //   m_cbStorage       = 0;

   //   m_dwAllocation    = 0;

   //   return point;

   //}


   byte * virtual_memory::impl_alloc(memsize dwAllocation)
   {

      return (byte *) ::MidAlloc((size_t)dwAllocation);

   }


   byte * virtual_memory::impl_realloc(void * pdata, memsize dwAllocation)
   {

      return (byte *) ::MidRealloc(pdata, (size_t) m_memory.m_dwAllocation, (size_t)dwAllocation);

   }


   void virtual_memory::impl_free(byte * pdata)
   {

      return ::MidFree(pdata);

   }



