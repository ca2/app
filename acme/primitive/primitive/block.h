#pragma once


#include "acme/primitive/mathematics/_.h"
#include "acme/primitive/primitive/_u32hash.h"


inline strsize string_get_length(const ansichar* psz) noexcept { return strlen(psz); }
inline strsize string_safe_length(const ansichar* psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }


struct CLASS_DECL_ACME BLOCK
{

   byte *                     m_pdata;
   memsize_storage            m_iSize;

};

template <std::size_t N>
struct ____array_count
{
    typedef char type[N];
};

enum enum_as_block
{

   e_as_block,

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

   block(enum_no_initialize) {}
   block() { m_pdata = nullptr; m_iSize = 0; }
   block(const void* pdata) { m_pdata = (byte*)pdata; m_iSize = string_safe_length((const char *) pdata); }
   template < primitive_integral INTEGRAL >
   block(const void * pdata, INTEGRAL iSize) { m_pdata = (byte *) pdata; m_iSize = (memsize_storage) iSize; }
   block(const memory_base & memory);
   block(const memory_base * pmemory);
   block(const block & block) : ::block(block.m_pdata, block.m_iSize) {}
   block(const atom & atom);
   template < typename TYPE >
   block(enum_as_block, TYPE & t): ::block((void *) & t, sizeof(t)) {}
   template < typename TYPE >
   block(enum_as_block, const TYPE & t):  ::block((void *)&t, sizeof(t)) {}
   

   block & operator = (const block & block) { if (this != &block) { m_pdata = block.m_pdata; m_iSize = block.m_iSize; } return *this; }

   void* get_data() { return m_pdata; }
   const void * get_data() const { return m_pdata; }
   memsize get_size() const { return m_iSize; }
   memsize size() const { return (memsize)m_iSize; }

   inline bool is_empty() const { return ::is_null(m_pdata) || get_size() <= 0; }
   inline bool is_set() const { return !is_empty(); }

   inline operator int() const { return is_set();}
   inline bool operator !() const { return !operator int(); }

//#ifdef _UWP
//
//   ::winrt::Windows::Storage::Streams::IBuffer^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
//   Array < uchar, 1U >^ get_os_bytes(memsize pos, memsize size) const;
//
//#endif

   block & from_base64(const char * psz, strsize iSize) const;


   int compare(const block& block) const
   {

      auto commonSize = minimum(get_size(), block.get_size());

      int iCompare = memcmp(get_data(), block.get_data(), commonSize);

      if (iCompare == 0)
      {

         return (int) (get_size() - block.get_size());

      }

      return iCompare;

   }


   bool operator == (const block& block) const
   {

      if (block.get_size() != get_size())
      {

         return false;

      }

      return __memcmp(block.get_data(), get_data(), (size_t)get_size()) == 0;

   }


   bool operator != (const block& block) const
   {

      return !operator == (block);

   }


};


namespace acme
{


   template < typename T >
   inline void memory_free(T * & point);

}


template < typename TYPE >
inline ::block as_block(const TYPE & type) 
{ 
   
   return { (void *)&type, (memsize) sizeof(TYPE) };

}


template < >
inline u32hash u32_hash < const block & >(const block & b)
{

   if (::is_null(b.get_data()) || b.is_empty())
   {

      return { 0 };

   }

   auto psz = (const char *)b.get_data();

   u32 uHash = 0;

   strsize i = 1;

   for (; i < b.get_size(); i++)
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


