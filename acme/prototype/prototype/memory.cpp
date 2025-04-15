#include "framework.h"
#include "memory.h"
#define HEAP_NAMESPACE_PREFIX main
#include "acme/memory/_____heap_namespace.h"
#include "acme/prototype/string/base64.h"
////#include "acme/exception/exception.h"


memory::memory(memory && memory) :
   memory_base(::transfer(memory))
{

}


memory::memory(manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   m_pprimitivememory      = this;
   m_bAligned              = false;

}


memory::memory(const memory & s, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   this->m_pprimitivememory      = this;
   m_bAligned              = false;
   operator = (s);

}


memory::memory(const memory * ps, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);
   this->m_pprimitivememory      = this;
   m_bAligned              = false;
   operator   = (*ps);

}


memory::memory(const unsigned char * pchSrc, character_count nLength, manager * pmanager)
{

   __UNREFERENCED_PARAMETER(pmanager);

   this->m_pprimitivememory      = this;

   m_bAligned              = false;

   set_size(nLength);

   ASSERT(is_memory_segment_ok(pchSrc, nLength));

   ::memory_copy(this->storage_begin(), pchSrc, nLength);

}


memory::memory(enum_create_new, bool bAligned)
{

   this->m_pprimitivememory      = this;
   m_bAligned              = bAligned;

}


memory::memory(const ::std::initializer_list < int > & iaList)
{

   this->m_pprimitivememory = this;

   m_bAligned = false;

   for(auto i : iaList)
   {

      unsigned char b = 0xff & i;

      append(&b, 1);

   }

}

memory::memory(const unsigned char * pdata, memsize iCount)
{

   this->m_pprimitivememory      = this;
   assign(pdata, iCount);

}


memory::memory(const ::block & block)
{

   this->m_pprimitivememory = this;
   assign(block.data(), block.size());

}


memory::memory(void * pdata, memsize iCount)
{

   this->m_begin = (unsigned char*)pdata;
   this->m_end = this->m_begin + iCount;

   this->m_bOwner = false;
   this->m_bReadOnly = false;
   this->m_beginStorage = (unsigned char *) pdata;

   this->m_sizeStorage = iCount;
   this->m_dAllocationRateUp = 0.0;
   this->m_dwAllocationAddUp = 4096;

   this->m_pcontainer = nullptr;

   this->m_ememory = e_memory_primitive;

   this->m_preadonlymemory = nullptr;
   this->m_pprimitivememory = this;
   this->m_psharedmemory = nullptr;
   this->m_pvirtualmemory = nullptr;

}


memory::memory(const void* pdata, memsize iCount)
{

   this->m_begin = (unsigned char*)pdata;
   this->m_end = this->m_begin + iCount;

   this->m_bOwner = false;
   this->m_bReadOnly = true;
   this->m_beginStorage = (unsigned char*)pdata;

   this->m_sizeStorage = iCount;
   this->m_dAllocationRateUp = 0.0;
   this->m_dwAllocationAddUp = 4096;

   this->m_pcontainer = nullptr;

   this->m_ememory = e_memory_primitive;

   this->m_preadonlymemory = nullptr;
   this->m_pprimitivememory = this;
   this->m_psharedmemory = nullptr;
   this->m_pvirtualmemory = nullptr;

}


memory::memory(const memory_base & s)
{

   this->m_pprimitivememory      = this;
   m_bAligned              = false;
   operator   = (s);

}


memory::memory(enum_copy_clone, const memory_base & memorybase)
{

   this->m_pprimitivememory = this;
   m_bAligned = false;
   memory_base::operator = (memorybase);

}


memory::memory(const memory & s)
{

   this->m_pprimitivememory      = this;
   m_bAligned              = s.m_bAligned;
   memory_base::operator   = (s);

}


memory::memory(const ::scoped_string & scopedstr)
{

   this->m_pprimitivememory      = this;
   this->m_beginStorage          = (unsigned char *) scopedstr.begin();
   this->m_begin                 = this->m_beginStorage;
   this->m_end                   = (unsigned char *) scopedstr.end();
   this->m_sizeStorage           = scopedstr.size();
   m_bAligned                    = false;

}


memory::memory(const ::string & str):
   memory(str.c_str(), str.length())
{

}


memory::memory(memory_container * pcontainer, memsize dwAllocationAddUp, unsigned int nAllocFlags)
{

   __UNREFERENCED_PARAMETER(nAllocFlags);
   this->m_pprimitivememory   = this;
   this->m_pcontainer         = pcontainer;
   if(dwAllocationAddUp == 0)
   {
#ifdef _DEBUG
      dwAllocationAddUp = 16 * 1024; // 16k
#else //__DEBUG
      dwAllocationAddUp = 4 * 1024; // 4k
#endif //!__DEBUG
   }
   this->m_dAllocationRateUp  = this->m_dAllocationRateUp;
   m_bAligned           = false;

}


memory::memory(memory_container * pcontainer, const void * pdata, memsize size)
{

   this->m_begin = (unsigned char*) pdata;
   this->m_end = this->m_begin + size;

   this->m_bOwner = false;
   this->m_bReadOnly = true;
   this->m_beginStorage = (unsigned char*)pdata;

   this->m_sizeStorage = size;
   this->m_dAllocationRateUp = 0.0;
   this->m_dwAllocationAddUp = 4096;

   this->m_pcontainer = pcontainer;

   this->m_ememory = e_memory_primitive;

   this->m_preadonlymemory = nullptr;
   this->m_pprimitivememory = this;
   this->m_psharedmemory = nullptr;
   this->m_pvirtualmemory = nullptr;

}



























memory::~memory()
{

   if(this->storage_begin() != nullptr)
   {

      impl_free(this->storage_begin());

      this->m_beginStorage = nullptr;

      this->m_begin = nullptr;

   }

}



unsigned char * memory::impl_alloc(memsize dwAllocation)
{

   if(dwAllocation < 0)
   {

      output_debug_string("Negative");

   }

#if !MEMDLEAK

   if(m_bAligned)
   {

      return (unsigned char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->aligned_allocate((size_t)dwAllocation, nullptr);

   }
   else
   {

      return (unsigned char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate((size_t)dwAllocation, nullptr);

   }

#else

   if(m_strTag.has_character() && ::get_task() != nullptr)
   {

      if(::get_task_object_debug().has_character())
      {

         if(m_bAligned)
         {

            return (unsigned char *)::HEAP_NAMESPACE::aligned_memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + ::get_task_object_name() + "="+ ::get_task_object_debug() + ", memory://" + m_strTag, m_iLine);

         }
         else
         {

            return (unsigned char *)memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + ::get_task_object_name() + "="+ ::get_task_object_debug() + ", memory://"+m_strTag, m_iLine);

         }

      }
      else
      {

         if(m_bAligned)
         {

            return (unsigned char *)::HEAP_NAMESPACE::aligned_memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + ::get_task_object_name() + ", memory://" + m_strTag, m_iLine);

         }
         else
         {

            return (unsigned char *)memory_allocate_debug((size_t)dwAllocation, 723, "thread://" + ::get_task_object_name() + ", memory://"+m_strTag, m_iLine);

         }

      }

   }
   else if(m_strTag.has_character())
   {

      if(m_bAligned)
      {

         return (unsigned char *)::HEAP_NAMESPACE::aligned_memory_allocate_debug((size_t)dwAllocation, 723, m_strTag, m_iLine);

      }
      else
      {

         return (unsigned char *)memory_allocate_debug((size_t)dwAllocation, 723, m_strTag, m_iLine);

      }

   }
   else
   {

      if(m_bAligned)
      {

         return (unsigned char *)::HEAP_NAMESPACE::aligned_memory_allocate((size_t)dwAllocation);

      }
      else
      {

         return (unsigned char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate((size_t)dwAllocation);

      }

   }

#endif

}


unsigned char * memory::impl_realloc(void * pdata, memsize dwAllocation)
{
   if(m_bAligned)
   {
      return nullptr;
   }
   else
   {
      return (unsigned char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->reallocate(pdata, (size_t)dwAllocation);
   }

}

void memory::impl_free(unsigned char * pdata)
{

   if (this->m_bOwner)
   {

      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pdata);

   }

}



character_count memory::sz_len() const
{

   return size() + 1;

}


void memory::to_sz(char * sz, character_count len) const
{

   if (len <= 0)
   {

      return;

   }

   if (::is_null(sz))
   {

      throw ::exception(error_null_pointer, "memory::to_sz sz is null");

   }

   if (::is_null(data()))
   {

      throw ::exception(error_null_pointer, "memory::to_sz data() is null");

   }


   len = minimum(len - 1, size() - 1);

   ansi_ncpy(sz, (const char *) data(), len);

   sz[len] = '\0';

}





//
//CLASS_DECL_ACME const void * memory_find(const void* l, memsize l_len, const void* s, memsize s_len)
//{
//
//   if(::is_null(l) || ::is_null(s))
//   {
//
//      throw exception(error_bad_argument);
//
//   }
//
//   return _memory_find(l, l_len, s, s_len);
//
//}