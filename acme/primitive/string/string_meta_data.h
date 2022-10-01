#pragma once



enum e_get_buffer
{

   get_buffer,

};


template < typename STRING >
inline STRING & string_concatenate(STRING & strResult, const typename STRING::CHAR_TYPE * psz1, strsize nLength1, const typename STRING::CHAR_TYPE * psz2, strsize nLength2);

//template < typename CHAR_TYPE >
//class string_buffer;



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
   //inline ::strsize memsize_in_chars() const { return (::strsize) ::str().byte_length_to_char_length(&this->get_data()[0], (::strsize) this->m_memsize); }
   inline ::strsize memsize_in_chars() const;

   /// always char count (before first [and possibly final, but not necessarily final] null terminator)
   inline ::strsize get_length() const { return (::strsize) this->m_datasize; }
   inline ::memsize length_in_bytes() const;
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



