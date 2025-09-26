#pragma once


#include "memory_base.h"
//#include "acme/prototype/prototype/pointer.h"


// class CLASS_DECL_ACME read_only_memory :
//    public memory_base
// {
// public:


//    read_only_memory(const block& block) : read_only_memory(block.get_data(), block.get_size()) {}

//    read_only_memory(const void *p, memsize size)
//    {

//       m_memory.m_bOwn = false;
//       m_memory.m_preadonlymemory = this;
//       m_memory.m_pbStorage = (unsigned char *) p;
//       m_memory.m_pdata = (unsigned char *) p;
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


   memory(::particle * pparticle = nullptr) { this->m_pprimitivememory = this; this->m_bAligned = false; }
   memory(enum_create_new, bool bAligned);
   template < primitive_integral INTEGRAL >
   memory(INTEGRAL i, bool bAligned = false) { this->m_pprimitivememory = this; this->m_bAligned = bAligned; this->set_size(i); }
   memory(const ::std::initializer_list < int > & iaList);
   memory(const unsigned char *, memsize size);
   memory(void*, memsize size);
   memory(const void *, memsize size);
   memory(enum_copy_clone, const memory_base & memorybase);
   memory(const memory_base & memorybase);
   memory(const memory & memory);
   memory(const ::block & block);
   memory(memory_container * pcontainer, memsize size = 0, unsigned int uAllocFlags = 0);
   memory(memory_container * pcontainer, const void * pdata, memsize size);
   memory(manager * pmanager);
   memory(const memory & memory, manager * pmanager);
   memory(const memory * pmemory, manager * pmanager);
   memory(const unsigned char * pchSrc, character_count nLength, manager * pmanager);
   memory(memory && memory);
   memory(const ::scoped_string & scopedstr);
   memory(const ::string & str);
   ~memory() override;


   virtual unsigned char * impl_alloc(memsize dwAllocation) override;
   virtual unsigned char * impl_realloc(void * pdata, memsize dwAllocation) override;
   virtual void impl_free(unsigned char * pdata) override;

   using memory_base::operator =;
   using memory_base::operator +=;
   
   
   inline memory & operator = (const ::memory & memory) { assign(memory); return *this; }
   inline memory & operator += (const ::memory & memory) { append(memory); return *this; };

   
   character_count sz_len() const override;
   void to_sz(char * sz, character_count len) const override;


};

using memory_pointer = ::pointer<memory>;

inline memory_pointer create_memory() { return øallocate ::memory (); }


inline ::memory memory_base::slice(memsize start, memsize count)
{

   auto p = this->data() + start;

   return {p, count};

}


inline ::memory memory_base::left(memsize count)
{

   auto left = minimum(count, this->size());

   if (left <= 0)
   {

      return {};

   }

   return slice(0, left);

}


inline ::memory memory_base::right(memsize count)
{

   auto start = this->size() - count;

   if (start <= 0)
   {

      return {};

   }

   return slice(start, count);

}



inline void memory_base::set_char_at_grow(character_count iChar, char ch)
{

   if (::comparison::ge(iChar, size()))
   {

      set_size(iChar + 1);

   }

   ((char*)data())[iChar] = ch;

}

