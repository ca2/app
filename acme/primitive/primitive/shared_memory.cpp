#include "framework.h"


#if !defined(_UWP)




   shared_memory::shared_memory(const memory_base & s)
   {

      m_nAllocFlags     = 0;
      m_hGlobalMemory   = nullptr;
      m_bAllowGrow      = TRUE;
      m_memory.m_pbStorage = nullptr;
      m_memory.m_pbComputed = nullptr;

      memory_base::operator             = (s);

   }

   shared_memory::shared_memory(memory_container * pcontainer, double dAllocationRateUp, UINT nAllocFlags)
   {

      m_nAllocFlags        = nAllocFlags;
      m_bAllowGrow         = TRUE;
      m_memory.m_pcontainer         = pcontainer;
      m_memory.m_dAllocationRateUp  = dAllocationRateUp;
      m_memory.m_pbStorage = nullptr;
      m_memory.m_pbComputed = nullptr;

   }

   shared_memory::shared_memory(memory_container * pcontainer, void * pMemory, memsize dwSize)
   {

      m_nAllocFlags     = 0;
      m_memory.m_pcontainer      = pcontainer;
      m_bAllowGrow      = TRUE;
      m_memory.m_pbStorage = nullptr;
      m_memory.m_pbComputed = nullptr;

      set_size(dwSize);

      ASSERT(__is_valid_address(pMemory, (uptr) dwSize, FALSE));

      ::memcpy_dup(m_memory.m_pbStorage, pMemory, (size_t) dwSize);

   }


   shared_memory::shared_memory(const void * pMemory, memsize dwSize)
   {

      m_nAllocFlags     = 0;
      m_memory.m_pcontainer      = nullptr;
      m_bAllowGrow      = TRUE;
      m_memory.m_pbStorage = nullptr;
      m_memory.m_pbComputed = nullptr;

      set_size(dwSize);

      ASSERT(__is_valid_address(pMemory, (uptr) dwSize, FALSE));

      ::memcpy_dup(m_memory.m_pbStorage, pMemory, (size_t) dwSize);

   }


   shared_memory::~shared_memory()
   {

      if(m_memory.m_pbStorage != nullptr)
      {

         impl_free(m_memory.m_pbStorage);

      }

   }


   byte * shared_memory::detach_shared_memory(HGLOBAL & hglobal)
   {

      if(m_memory.m_iOffset > 0)
      {

         __pointer(shared_memory) pbase = clone();

         impl_free(m_memory.m_pbStorage);

         pbase->detach_shared_memory(hglobal);

      }
      else
      {

         hglobal              = m_hGlobalMemory;

      }

      byte * pbStorage     = m_memory.m_pbStorage;

      m_hGlobalMemory      = nullptr;
      m_memory.m_pbStorage          = nullptr;
      m_memory.m_pbComputed   = nullptr;
      m_memory.m_cbStorage          = 0;
      m_memory.m_dwAllocation       = 0;

      return pbStorage;

   }


   void shared_memory::SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow)
   {

      UNREFERENCED_PARAMETER(bAllowGrow);

      ASSERT(m_hGlobalMemory == nullptr);        // do once only

      ASSERT(m_memory.m_pbStorage == nullptr);     // do once only

      if (hGlobalMemory == nullptr)
      {

         __throw(invalid_argument_exception());

      }

      m_hGlobalMemory = hGlobalMemory;

      m_memory.m_pbStorage = (BYTE*)::GlobalLock(m_hGlobalMemory);

      m_memory.m_pbComputed = m_memory.m_pbStorage;

      m_memory.m_dwAllocation = m_memory.m_cbStorage = (WINULONG)::GlobalSize(m_hGlobalMemory);

      // xxx m_bAllowGrow = bAllowGrow;

   }


   byte * shared_memory::impl_alloc(memsize nBytes)
   {

      ASSERT(m_hGlobalMemory == nullptr);        // do once only

      m_hGlobalMemory = ::GlobalAlloc(m_nAllocFlags, (SIZE_T) nBytes);

      if (m_hGlobalMemory == nullptr)
         return nullptr;

      return (byte *) ::GlobalLock(m_hGlobalMemory);

   }


   byte * shared_memory::impl_realloc(void*, memsize nBytes)
   {

      if (!m_bAllowGrow)
         return nullptr;

      ASSERT(m_hGlobalMemory != nullptr);

      ::GlobalUnlock(m_hGlobalMemory);

      HGLOBAL hNew;

      hNew = ::GlobalReAlloc(m_hGlobalMemory, (SIZE_T)nBytes, m_nAllocFlags);

      if (hNew == nullptr)
         return nullptr;

      m_hGlobalMemory = hNew;

      return (byte *) ::GlobalLock(m_hGlobalMemory);

   }


   void shared_memory::impl_free(byte *)
   {

      ASSERT(m_hGlobalMemory != nullptr);

      ::GlobalUnlock(m_hGlobalMemory);

      ::GlobalFree(m_hGlobalMemory);

   }


   //byte * * shared_memory::detach()
   //{

   //   __throw(not_supported_exception("not valid for Global Memory(\"HGLOBAL\")"));

   //}


   //void shared_memory::free_data()
   //{
   //   if(m_pbStorage != nullptr)
   //   {
   //      m_dwAllocation    = 0;
   //      try
   //      {
   //         ::GlobalUnlock(m_hGlobalMemory);
   //         ::GlobalFree(m_hGlobalMemory);
   //      }
   //      catch(...)
   //      {
   //      }
   //      m_pbStorage       = nullptr;
   //      m_pbComputed = nullptr;
   //   }
   //}

















   /*void shared_memory::copy_from(const memory_base *pstorage)
   {
      ASSERT(pstorage != nullptr);
      allocate(pstorage->get_size());
      ::memcpy_dup(get_data(), pstorage->get_data(), (size_t) this->get_size());

   }

   void shared_memory::set_data(void *pdata, memsize uiSize)
   {
      allocate(uiSize);
      ::memcpy_dup(get_data(), pdata, (size_t) uiSize);
   }
   */

   /*void shared_memory::To(string & str, memsize iStart, memsize iEnd)
   {
      iStart = max(iStart, 0);
      if(iEnd == -1)
         iEnd = this->get_size() - 1;
      char * pch = (char *) get_data();
      for(memsize i = iStart; i <= iEnd; i++)
      {
         if(((pch[i] & 0xf0) >> 4) < 10)
            str += (char)(((pch[i] & 0xf0) >> 4) + '0');
         else
            str += (char)(((pch[i] & 0xf0) >> 4) + 'A' - 10);
         if(((pch[i] & 0x0f)) < 10)
            str += (char)((pch[i] & 0x0f) + '0');
         else
            str += (char)((pch[i] & 0x0f) + 'A' - 10);
      }
   }

   void shared_memory::From(const char * psz)
   {
      char ch;
      i32 iLen = strlen(psz);
      allocate(iLen / 2);
      char * pch = (char *) get_data();
      while(*psz != '\0')
      {
         ch = 0;
         if(*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
         else
            ch |= ((*psz - '0') & 0x0f) << 4;
         if(*psz == '\0')
            break;
         psz++;
         if(*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f);
         else
            ch |= ((*psz - '0') & 0x0f);
         *pch = ch;
         psz++;
         pch++;
      }
   }

   void shared_memory::ToAsc(string & str)
   {
      string strTo;
      To(strTo);
      char ch;
      i32 iLen = strTo.get_length() - 1;
      for(i32 i = 0; i < iLen; i+=2)
      {
         if(strTo[i] <= '9')
            ch = (strTo[i] - '0') << 4;
         else
            ch = (strTo[i] - 'A' + 10) << 4;
         if(strTo[i + 1] <= '9')
            ch |= (strTo[i + 1] - '0');
         else
            ch |= (strTo[i + 1] - 'A' + 10);
         str += ch;
      }
   }

   void shared_memory::FromAsc(const char * psz)
   {
      string str;
      while(*psz)
      {
         char ch = ((*psz & 0xf0) >> 4);
         if(ch < 10)
            ch += '0';
         else
            ch += 'A' - 10;
         str += ch;
         ch = ((*psz & 0xf));
         if(ch < 10)
            ch += '0';
         else
            ch += 'A' - 10;
         str += ch;
         psz++;
      }
      From(str);
   }*/


   /*void shared_memory::from_string(const unichar * pwsz)
   {
      from_string(::str::international::unicode_to_utf8(pwsz));
   }

   void shared_memory::from_string(const char * psz)
   {
      allocate(strlen(psz));
      ::memcpy_dup(get_data(), psz, this->get_size());
   }

   void shared_memory::to_string(string & str)
   {
      LPTSTR psz = str.get_string_buffer(this->get_size() + 1);

      ::memcpy_dup(psz, get_data(), this->get_size());

      psz[this->get_size()] = '\0';

      str.ReleaseBuffer();
   }
   */



#endif



