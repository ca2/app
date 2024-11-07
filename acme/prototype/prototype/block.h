#pragma once


#include "acme/memory/_memory.h"
//#include "acme/prototype/prototype/_u32hash.h"


#include "acme/prototype/collection/array_range.h"




CLASS_DECL_ACME character_count string_get_length(const ::ansi_character* psz) noexcept;
CLASS_DECL_ACME character_count string_safe_length(const ::ansi_character * psz) noexcept;


using BLOCK = ::range < unsigned char * >;
//using BLOCK = array_range < ::range < unsigned char * > >;
//struct CLASS_DECL_ACME BLOCK
//{
//
//   unsigned char *                     m_pbegin;
//   ::collection::count                    m_iSize;
//
//
//   memsize length_in_bytes() const { return sizeof(unsigned char) * m_iSize; }
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

   using PRIMITIVE_BLOCK_TAG = PRIMITIVE_BLOCK_TAG_TYPE;
   
   //using BLOCK::BLOCK;


   block() : BLOCK() {}
   block(const block & block)
   {
      this->m_begin = block.m_begin;
      this->m_end = block.m_end;
   }
   block(const range < unsigned char * > & range);
   block(const memory_base & memory);
   block(const memory_base * pmemory);
   block(const atom & atom);
   template < ::collection::count c >
   block(const char(&sz)[c])
   {

      this->m_begin = (unsigned char *)(sz);
      this->m_end = (unsigned char *)(this->m_begin + c);

   }
   template < ::collection::count c >
   block(const unsigned char(&ba)[c])
   {

      this->m_begin = (unsigned char *) ba;
      this->m_end = (unsigned char *) (this->m_begin + c);

   }
   block(const ::ansi_character * psz)
   {
      this->m_begin = (unsigned char *) psz;
      this->m_end = this->m_begin + ::string_safe_length(psz);
   }
   //block(const ::scoped_string  & scopedstr);
   template < primitive_integral INTEGRAL >
   block(INTEGRAL & i) : block(e_as_little_endian_block, i) {}
   template < typename TYPE >
   block(enum_as_little_endian_block, TYPE & t) : 
      block((void *)&t, sizeof(t))
   {
#if BIG_ENDIAN
      reverse(m_begin, m_end);
#endif
   }
   template < typename TYPE >
   block(enum_as_block, TYPE & t) : block((void *)&t, sizeof(t)) {}
   template < typename TYPE >
   block(enum_as_block, const TYPE & t) : block((void *)&t, sizeof(t)) {}
   block(const void * begin, const void * end) : BLOCK((unsigned char *)begin, (unsigned char *)end) {}
   template < primitive_integral INTEGRAL >
   block(const void * data, INTEGRAL count) : BLOCK((unsigned char *) data, count) { }

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
   //const unsigned char * data () const { return (const  unsigned char *) m_pbegin;  }
   //unsigned char * data() { return (unsigned char *)m_pbegin; }
   //::collection::count size() const { return (::collection::count)m_iSize; }


   constexpr bool has_data() const { return !this->is_empty(); }

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

   template < primitive_aggregate AGGREGATE >
   block & operator = (const AGGREGATE & aggregate)
   {

      if (this->size() < sizeof(AGGREGATE))
      {

         throw_exception(error_end_of_file);

      }
   
      ::memory_copy(this->m_begin, &aggregate, sizeof(aggregate));

      return *this;

   }

   template < character_count c >
   block & operator = (const unsigned char(&ba)[c])
   {

      if (this->size() < c)
      {

         throw_exception(error_end_of_file);

      }

      ::memory_copy(this->m_begin, ba, c);

      return *this;

   }

   template < typename T >
   block & operator >>(T & t)
   {

      if (this->size() < sizeof(T))
      {

         throw_exception(error_end_of_file);

      }

      ::memory_copy(&t, this->begin(), sizeof(t));

      return *this;

   }

   template < character_count c >
   block & operator >>(unsigned char(&ba)[c])
   {

      if (this->size() < c)
      {

         throw_exception(error_end_of_file);

      }

      memory_copy(ba, this->m_begin, c);

      return *this;

   }



//#ifdef UNIVERSAL_WINDOWS
//
//   ::winrt::Windows::Storage::Streams::IBuffer^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
//   Array < uchar, 1U >^ get_os_bytes(memsize pos, memsize size) const;
//
//#endif

   block & from_base64(const ::scoped_string & scopedstr) const;


   ::std::strong_ordering compare(const block& block) const
   {

      auto commonSize = minimum(size(), block.size());

      auto ordering = memory_order(begin(), block.begin(), commonSize) <=>0;

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

      return memory_order(begin(), block.begin(), (size_t)size()) == 0;

   }


   bool operator != (const block& block) const
   {

      return !operator == (block);

   }


   memsize find(const ::block& blockFind, memsize start = 0) const;

   inline memsize _find(const ::block& blockFind, memsize start = 0) const
   {
      return ((unsigned char*)_memory_find(
         as_pointer<unsigned char>() + start, size() - start,
         blockFind.begin(), blockFind.size())) - as_pointer <unsigned char>();

   }


   inline void copy(const ::block & block)
   {

      memory_copy(m_begin, block.data(), minimum(block.size(), this->size()));

   }


   inline bool begins(const ::block & block) const
   {

      if(block.is_empty())
      {

         return true;

      }

      if(this->size() < block.size())
      {

         return false;

      }

      if(::memory_order(this->data(), block.data(), block.size()) != 0)
      {

         return false;

      }

      return true;

   }


   inline bool ends(const ::block & block) const
   {

      if(block.is_empty())
      {

         return true;

      }

      if(this->size() < block.size())
      {

         return false;

      }

      if(::memory_order(this->end() - block.size(), block.data(), block.size()) != 0)
      {

         return false;

      }

      return true;

   }


   unsigned char & first_byte(::collection::index i = 0){return this->m_begin[i];}
   unsigned char first_byte(::collection::index i = 0)const{return this->m_begin[i];}
   unsigned char & last_byte(::collection::index i = -1){return this->m_end[i];}
   unsigned char last_byte(::collection::index i = -1)const{return this->m_end[i];}

};


namespace acme
{


   template < typename T >
   inline void memory_free(T * & p);

}




template < typename ITEM_TYPE >
class GET_BLOCK_TYPE
{
public:


   //using TYPE = ::array_range < ::range < ITEM_TYPE * > >;
   using TYPE = ::range < ITEM_TYPE * >;


};


template <  >
class GET_BLOCK_TYPE< unsigned char >
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
inline ::hash32 as_hash32 < const ::block & >(const ::block & b)
{

   if (!b)
   {

      return { 0 };

   }

   auto psz = b.begin();

   unsigned int uHash = 0;

   character_count i = 1;

   auto len = minimum(64, b.size());

   for (; i < len; i++)
   {

      if (i % 4 == 3)
      {

         uHash = (uHash << 5) + ((unsigned int *)psz)[i >> 2];

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


