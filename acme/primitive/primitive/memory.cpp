#include "framework.h"
#include "memory.h"
#define HEAP_NAMESPACE_PREFIX main
#include "acme/memory/_____heap_namespace.h"
#include "acme/primitive/string/base64.h"


memory::memory(memory && memory) :
   memory_base(::move(memory))
{
   
   __zero(memory.m_memory);

}


memory::memory(manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   m_memory.m_pprimitivememory      = this;
   m_bAligned              = false;

}


memory::memory(const memory & s, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   m_memory.m_pprimitivememory      = this;
   m_bAligned              = false;
   operator = (s);

}


memory::memory(const memory * ps, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   m_memory.m_pprimitivememory      = this;
   m_bAligned              = false;
   operator   = (*ps);

}


memory::memory(const u8 * pchSrc, strsize nLength, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);

   m_memory.m_pprimitivememory      = this;

   m_bAligned              = false;

   set_size(nLength);

   ASSERT(__is_valid_address(pchSrc, nLength, false));

   ::memcpy_dup(m_memory.m_pbStorage, pchSrc, nLength);

}


memory::memory(enum_create_new, bool bAligned)
{

   m_memory.m_pprimitivememory      = this;
   m_bAligned              = bAligned;

}


memory::memory(const ::std::initializer_list < int > & iaList)
{

   m_memory.m_pprimitivememory = this;

   m_bAligned = false;

   for(auto i : iaList)
   {

      byte b = 0xff & i;

      append(&b, 1);

   }

}

memory::memory(const u8 * pdata, memsize iCount)
{

   m_memory.m_pprimitivememory      = this;
   assign(pdata, iCount);

}


memory::memory(const ::block & block)
{

   m_memory.m_pprimitivememory = this;
   assign(block.get_data(), block.get_size());

}

memory::memory(const void * pdata, memsize iCount)
{

   m_memory.m_pprimitivememory      = this;
   assign(pdata, iCount);

}


memory::memory(const memory_base & s)
{

   m_memory.m_pprimitivememory      = this;
   m_bAligned              = false;
   operator   = (s);

}


memory::memory(enum_copy_clone, const memory_base & memorybase)
{

   m_memory.m_pprimitivememory = this;
   m_bAligned = false;
   memory_base::operator = (memorybase);

}


memory::memory(const memory & s)
{

   m_memory.m_pprimitivememory      = this;
   m_bAligned              = s.m_bAligned;
   memory_base::operator   = (s);

}


memory::memory(const char * psz)
{

   m_memory.m_pprimitivememory   = this;
   m_memory.m_pbStorage          = (byte *) psz;
   m_memory.m_pdata              = m_memory.m_pbStorage;
   m_memory.m_cbStorage          = strlen(psz);
   m_memory.m_iSize              = m_memory.m_cbStorage;
   m_bAligned                    = false;

}


memory::memory(const ::string & str):
   memory(str.c_str(), str.length())
{

}


memory::memory(memory_container * pcontainer, memsize dwAllocationAddUp, ::u32 nAllocFlags)
{

   __UNREFERENCED_PARAMETER(nAllocFlags);
   m_memory.m_pprimitivememory   = this;
   m_memory.m_pcontainer         = pcontainer;
   if(dwAllocationAddUp == 0)
   {
#ifdef __DEBUG
      dwAllocationAddUp = 16 * 1024; // 16k
#else //__DEBUG
      dwAllocationAddUp = 4 * 1024; // 4k
#endif //!__DEBUG
   }
   m_memory.m_dAllocationRateUp  = m_memory.m_dAllocationRateUp;
   m_bAligned           = false;

}


memory::memory(memory_container * pcontainer, const void * pMemory, memsize dwSize)
{

   m_memory.m_pprimitivememory   = this;
   m_memory.m_pbStorage          = (byte *) pMemory;
   m_memory.m_pdata              = m_memory.m_pbStorage;
   m_memory.m_pcontainer         = pcontainer;
   m_memory.m_cbStorage          = dwSize;
   m_memory.m_iSize              = m_memory.m_cbStorage;
   m_bAligned                    = false;

}



























memory::~memory()
{

   if(m_memory.m_pbStorage != nullptr)
   {

      impl_free(m_memory.m_pbStorage);

      m_memory.m_pbStorage = nullptr;

   }

}



byte * memory::impl_alloc(memsize dwAllocation)
{

   if(dwAllocation < 0)
   {

      printf("Negative");

   }

#if !MEMDLEAK

   if(m_bAligned)
   {

      return (byte *)::HEAP_NAMESPACE::aligned_memory_allocate((size_t)dwAllocation);

   }
   else
   {

      return (byte *)memory_allocate((size_t)dwAllocation);

   }

#else

   if(m_strTag.has_char() && ::get_task() != nullptr)
   {

      if(::get_task()->m_strDebug.has_char())
      {

         if(m_bAligned)
         {

            return (byte *)aligned_memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + typeid(*::get_task()).name()) + "="+ ::get_task()->m_strDebug + ", memory://" + m_strTag, m_iLine;

         }
         else
         {

            return (byte *)memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + typeid(*::get_task()).name()) + "="+ ::get_task()->m_strDebug + ", memory://"+m_strTag, m_iLine;

         }

      }
      else
      {

         if(m_bAligned)
         {

            return (byte *)aligned_memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + typeid(*::get_task()).name()) + ", memory://" + m_strTag, m_iLine;

         }
         else
         {

            return (byte *)memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + typeid(*::get_task()).name()) + ", memory://"+m_strTag, m_iLine;

         }

      }

   }
   else if(m_strTag.has_char())
   {

      if(m_bAligned)
      {

         return (byte *)aligned_memory_allocate_debug((size_t)dwAllocation, 723, m_strTag, m_iLine);

      }
      else
      {

         return (byte *)memory_allocate_debug((size_t)dwAllocation, 723, m_strTag, m_iLine);

      }

   }
   else
   {

      if(m_bAligned)
      {

         return (byte *)aligned_memory_allocate((size_t)dwAllocation);

      }
      else
      {

         return (byte *)memory_allocate((size_t)dwAllocation);

      }

   }

#endif

}


byte * memory::impl_realloc(void * pdata, memsize dwAllocation)
{
   if(m_bAligned)
   {
      return nullptr;
   }
   else
   {
      return (byte *)memory_reallocate(pdata, (size_t)dwAllocation);
   }

}

void memory::impl_free(byte * pdata)
{

   if (m_memory.m_bOwn)
   {

      memory_free(pdata);

   }

}



strsize memory::sz_len() const
{

   return size() + 1;

}


void memory::to_sz(char * sz, strsize len) const
{

   if (len <= 0)
   {

      return;

   }

   if (::is_null(sz))
   {

      throw ::exception(error_null_pointer, "memory::to_sz sz is null");

   }

   if (::is_null(get_data()))
   {

      throw ::exception(error_null_pointer, "memory::to_sz get_data() is null");

   }


   len = minimum(len - 1, size() - 1);

   strncpy(sz, (const char *) get_data(), len);

   sz[len] = '\0';

}




