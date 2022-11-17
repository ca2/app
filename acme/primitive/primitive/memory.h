#pragma once


#include "memory_base.h"
#include "acme/primitive/primitive/pointer.h"


// class CLASS_DECL_ACME read_only_memory :
//    public memory_base
// {
// public:


//    read_only_memory(const block& block) : read_only_memory(block.get_data(), block.get_size()) {}

//    read_only_memory(const void *p, memsize size)
//    {

//       m_memory.m_bOwn = false;
//       m_memory.m_preadonlymemory = this;
//       m_memory.m_pbStorage = (byte *) p;
//       m_memory.m_pdata = (byte *) p;
//       m_memory.m_cbStorage = size;
//       m_memory.m_iSize = size;

//    }

// };


class CLASS_DECL_ACME memory :
   public memory_base
{
public:


   typedef memory data_type;


   bool        m_bAligned;


   memory(::particle * pparticle = nullptr) { m_memory.m_pprimitivememory = this; m_bAligned = false; }
   memory(enum_create_new, bool bAligned);
   template < primitive_integral INTEGRAL >
   memory(INTEGRAL i, bool bAligned = false) { m_memory.m_pprimitivememory = this; m_bAligned = bAligned; set_size(i); }
   memory(const ::std::initializer_list < int > & iaList);
   memory(const u8 *, memsize size);
   memory(void*, memsize size);
   memory(const void *, memsize size);
   memory(enum_copy_clone, const memory_base & memorybase);
   memory(const memory_base & memorybase);
   memory(const memory & memory);
   memory(const char * psz);
   memory(const ::block & block);
   memory(memory_container * pcontainer, memsize size = 0, ::u32 uAllocFlags = 0);
   memory(memory_container * pcontainer, const void * pdata, memsize size);
   memory(manager * pmanager);
   memory(const memory & memory, manager * pmanager);
   memory(const memory * pmemory, manager * pmanager);
   memory(const u8 * pchSrc, strsize nLength, manager * pmanager);
   memory(memory && memory);
   memory(const ::string & str);
   ~memory() override;


   virtual byte * impl_alloc(memsize dwAllocation) override;
   virtual byte * impl_realloc(void * pdata, memsize dwAllocation) override;
   virtual void impl_free(byte * pdata) override;

   using memory_base::operator =;
   using memory_base::operator +=;
   
   
   inline memory & operator = (const ::memory & memory) { assign(memory); return *this; }
   inline memory & operator += (const ::memory & memory) { append(memory); return *this; };

   
   strsize sz_len() const override;
   void to_sz(char * sz, strsize len) const override;


};

using memory_pointer = ::pointer<memory>;

inline memory_pointer create_memory() { return __new(::memory); }





