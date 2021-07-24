#pragma once



enum e_get_buffer
{

   get_buffer,

};


template < typename STRING >
inline STRING & string_concatenate(STRING & strResult, const typename STRING::CHAR_TYPE * psz1, strsize nLength1, const typename STRING::CHAR_TYPE * psz2, strsize nLength2);

//template < typename CHAR_TYPE >
//class string_file;



template < typename TYPE_CHAR >
class string_meta_data :
   public meta_data < TYPE_CHAR >
{
public:


   typedef TYPE_CHAR                               CHAR_TYPE;
   typedef string_meta_data < TYPE_CHAR >          STRING_META_DATA;

   using meta_data < TYPE_CHAR >::meta_data;

   /// in bytes, without meta, with null(s)
   inline ::memsize memsize() const { return (::memsize) this->m_memsize; }
   inline ::strsize memsize_in_chars() const { return (::strsize) ::str::byte_length_to_char_length(&this->get_data()[0], (::strsize) this->m_memsize); }

   /// always char count (before first [and possibly final, but not necessarily final] null terminator)
   inline ::strsize get_length() const { return (::strsize) this->m_datasize; }
   inline ::memsize length_in_bytes() const { return ::str::char_length_to_byte_length(&this->get_data()[0], this->m_datasize); }
   inline ::strsize length() const { return (::strsize) this->m_datasize; }


   inline void set_length(::strsize strsize);

   operator const CHAR_TYPE * () const noexcept { return this->m_pdata; }

   operator CHAR_TYPE * () noexcept { return this->m_pdata; }

   const CHAR_TYPE * c_str() const noexcept { return this->m_pdata; }

   CHAR_TYPE * data() const noexcept { return this->m_pdata; }




};


template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < ansichar > > * __nil < natural_meta_data < string_meta_data < ansichar > > >();

template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < wd16char > > * __nil < natural_meta_data < string_meta_data < wd16char > > >();

template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < wd32char > > * __nil < natural_meta_data < string_meta_data < wd32char > > >();





enum e_char_count
{

   char_count,
};

enum e_byte_count
{

   byte_count,
};


#include "acme/memory/string_memory_allocator.h"


template < typename TYPE_CHAR >
class natural_string_base :
   public natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >
{
public:

   using NATURAL_POINTER = natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >;

   using NATURAL_META_DATA = typename NATURAL_POINTER::NATURAL_META_DATA;

   using NATURAL_POINTER::NATURAL_POINTER;

   natural_string_base(e_char_count, strsize iCharCount)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(sizeof(TYPE_CHAR) * (iCharCount + 1)));

   }

   natural_string_base(e_byte_count, memsize iMemSize)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(((iMemSize + sizeof(TYPE_CHAR) + sizeof(TYPE_CHAR) - 1) / sizeof(TYPE_CHAR)) * sizeof(TYPE_CHAR)));

   }


   operator TYPE_CHAR * () { return this->m_pdata; }
   operator const TYPE_CHAR * () const { return this->m_pdata; }


   inline auto length() { return this->metadata()->length(); }
   inline auto memsize() { return this->metadata()->memsize(); }


};



using natural_ansistring = natural_string_base < ansichar >;
using natural_wd16string = natural_string_base < wd16char >;
using natural_wd32string = natural_string_base < wd32char >;
using natural_widestring = natural_string_base < widechar >;

typedef natural_ansistring natural_string;
typedef natural_widestring natural_wstring;



