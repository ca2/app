#pragma once


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
   block(const void * pdata = nullptr, memsize iSize = 0) { m_pdata = (byte *) pdata; m_iSize = iSize; }
   block(const memory_base & memory);
   block(const memory_base * pmemory);
   block(const block & block) : ::block(block.m_pdata, block.m_iSize) {}
   block(const atom & atom);
   block(const ::string & str);
   block(const ::string & str, ::strsize s);
   block(const char * psz, ::strsize s = -1) : ::block((const void *)psz, (::i64) (s >= 0 ? s : strlen(psz) + s + 1)) {}
   template < typename TYPE >
   block(enum_as_block, TYPE & t): ::block((void *) & t, sizeof(t)) {}
   template < typename TYPE >
   block(enum_as_block, const TYPE & t):  ::block((void *)&t, sizeof(t)) {}
   //   template < primitive_integral INTEGRAL >
//   block(const INTEGRAL & integral) : ::block((const void*)&integral, sizeof(integral)) {}


   block & operator = (const block & block) { if (this != &block) { m_pdata = block.m_pdata; m_iSize = block.m_iSize; } return *this; }

   void * get_data() const { return m_pdata; }
   memsize get_size() const { return m_iSize; }
   memsize size() const { return (memsize)m_iSize; }

   inline bool is_empty() const { return m_pdata == nullptr || get_size() <= 0; }


   inline bool operator !() const { return is_empty(); }

//#ifdef _UWP
//
//   ::winrt::Windows::Storage::Streams::IBuffer^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
//   Array < uchar, 1U >^ get_os_bytes(memsize pos, memsize size) const;
//
//#endif

   block & from_base64(const char * psz, strsize iSize) const;
   string to_base64() const;


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


   bool operator == (const block & block) const
   {

      if (block.get_size() != get_size())
      {

         return false;

      }

      return __memcmp(block.get_data(), get_data(), (size_t) get_size()) == 0;

   }

   void to_string(string & str) const;

};

namespace acme
{


   template < typename T >
   inline void memory_free(T * & point);

}


//struct CLASS_DECL_ACME fork_block :
//   public block
//{
//
//   fork_block() { }
//   fork_block(void * pdata, memsize iSize) : block(memory_allocate(iSize), iSize) { memcpy_dup(m_pdata, pdata, (size_t) iSize); }
//   fork_block(const block & block) : fork_block(block.get_data(), block.get_size()) {}
//   fork_block(block && block) : fork_block(block.get_data(), block.get_size()) { block.m_pdata = NULL; block.m_iSize = 0; }
//   fork_block(const memory_base & memory);
//   ~fork_block() { destroy(); }
//
//   fork_block & from_base64(const char * psz, strsize iSize);
//
//   void destroy();
//
//   fork_block & operator = (const block & block);
//
//   fork_block & operator = (const fork_block & block);
//
//
//   void assign(const void * pdata, i64 iSize);
//
//
//   fork_block & operator = (block && block);
//
//
//};


namespace hex
{


   CLASS_DECL_ACME string lower_from(const block & block);

   CLASS_DECL_ACME string upper_from(const block & block);


} // namespace hex


template < typename TYPE >
inline ::block memory_block(TYPE type) 
{ 
   
   return { (void *)__memory_address_of(type), (memsize) sizeof(type) };

}






template < >
inline uptr uptr_hash < block >(block b)
{

   if (::is_null(b.get_data()) || b.is_empty())
   {

      return 0;

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

   return uHash;

}


