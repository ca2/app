#pragma once


#include "acme/memory/_memory.h"
//#include "acme/primitive/primitive/_u32hash.h"


#include "acme/primitive/collection/array_range.h"




inline strsize string_get_length(const ::ansi_character* psz) noexcept { return strlen(psz); }
inline strsize string_safe_length(const ::ansi_character* psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }


using BLOCK = ::range < ::byte * >;
//using BLOCK = array_range < ::range < ::byte * > >;
//struct CLASS_DECL_ACME BLOCK
//{
//
//   byte *                     m_pbegin;
//   ::count                    m_iSize;
//
//
//   memsize length_in_bytes() const { return sizeof(::byte) * m_iSize; }
//
//};

template <std::size_t N>
struct ____array_count
{
    typedef char type[N];
};


template <typename T, std::size_t Size>
typename ____array_count<Size>::type& ___array_count(T(&)[Size]);

template <typename TYPE >
const TYPE * __memory_address_of(const TYPE a[]) { return (TYPE *)a; }

template <typename TYPE >
const TYPE * __memory_address_of(const TYPE & a) { return &a; }


struct CLASS_DECL_ACME block :
   public BLOCK
{

   
   //using BLOCK::BLOCK;


   block() : BLOCK() {}
   block(const block & block)
   {
      this->m_begin = block.m_begin;
      this->m_end = block.m_end;
   }
   block(const memory_base & memory);
   block(const memory_base * pmemory);
   block(const atom & atom);
   template < ::count c >
   block(const char(&sz)[c])
   {

      this->m_begin = sz;
      this->m_end = this->m_begin + c;

   }
   block(const ::ansi_character * psz)
   {
      this->m_begin = (::byte *) psz;
      this->m_end = this->m_begin + ::string_safe_length(psz);
   }
   //block(const ::scoped_string  & scopedstr);
   template < typename TYPE >
   block(enum_as_block, TYPE & t) : block((void *)&t, sizeof(t)) {}
   template < typename TYPE >
   block(enum_as_block, const TYPE & t) : block((void *)&t, sizeof(t)) {}
   block(const void * begin, const void * end) : BLOCK((const ::byte *)begin, (const ::byte *)end) {}
   template < primitive_integral INTEGRAL >
   block(const void * data, INTEGRAL count) : BLOCK((::byte *) data, count) { }

   //block & operator = (const block & block) 
   //{
   //   
   //   if (this != &block)
   //   {

   //      this->m_begin = block.m_begin;
   //      this->m_end = block.m_end;

   //      assign_block(block);

   //   }

   //   return *this;

   //}

   //void * get_data() { return m_pbegin; }
   //const void * get_data() const { return m_pbegin; }
   //memsize get_size() const { return m_iSize; }
   //const ::byte * data () const { return (const  ::byte *) m_pbegin;  }
   //::byte * data() { return (::byte *)m_pbegin; }
   //::count size() const { return (::count)m_iSize; }

   template < typename TYPE >
   const TYPE* as_pointer() const
   {

      return (const TYPE*)begin();

   }

   template < typename TYPE >
   TYPE* as_pointer() 
   {

      return (TYPE*) begin();

   }


//#ifdef _UWP
//
//   ::winrt::Windows::Storage::Streams::IBuffer^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
//   Array < uchar, 1U >^ get_os_bytes(memsize pos, memsize size) const;
//
//#endif

   block & from_base64(const ::scoped_string & scopedstr) const;


   ::std::strong_ordering compare(const block& block) const
   {

      auto commonSize = minimum(size(), block.size());

      auto ordering = memcmp(begin(), block.begin(), commonSize) <=>0;

      if (ordering != 0)
      {

         return ordering;

      }

      return size() <=> block.size();

   }


   bool operator == (const block& block) const
   {

      if (block.size() != size())
      {

         return false;

      }

      if (size() <= 0)
      {

         return true;

      }

      return memcmp(begin(), block.begin(), (size_t)size()) == 0;

   }


   bool operator != (const block& block) const
   {

      return !operator == (block);

   }


   memsize find(const ::block& blockFind, memsize start = 0) const;

   inline memsize _find(const ::block& blockFind, memsize start = 0) const
   {
      return ((::byte*)_memory_find(
         as_pointer<::byte>() + start, size() - start,
         blockFind.begin(), blockFind.size())) - as_pointer <::byte>();

   }


};


namespace acme
{


   template < typename T >
   inline void memory_free(T * & point);

}




template < typename ITEM_TYPE >
class GET_BLOCK_TYPE
{
public:


   //using TYPE = ::array_range < ::range < ITEM_TYPE * > >;
   using TYPE = ::range < ITEM_TYPE * >;


};


template <  >
class GET_BLOCK_TYPE< ::byte >
{
public:

   using TYPE = ::block;

};


template < typename TYPE >
inline ::block as_block(const TYPE & type) 
{ 
   
   return { (void *)&type, (memsize) sizeof(TYPE) };

}


template < >
inline ::u32hash u32_hash < const ::block & >(const ::block & b)
{

   if (!b)
   {

      return { 0 };

   }

   auto psz = b.begin();

   u32 uHash = 0;

   strsize i = 1;

   auto len = minimum(64, b.size());

   for (; i < len; i++)
   {

      if (i % 4 == 3)
      {

         uHash = (uHash << 5) + ((u32 *)psz)[i >> 2];

      }

   }

   psz += i;

   i %= 4;

   if (i > 0)
   {

      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);

   }

   return { uHash };

}


