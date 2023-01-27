#pragma once






template < typename STRING >
inline STRING & string_concatenate(STRING & strResult, const typename STRING::CHARACTER_TYPE * psz1, strsize nLength1, const typename STRING::CHARACTER_TYPE * psz2, strsize nLength2);

//template < typename CHARACTER_TYPE >
//class string_buffer;
#include "acme/primitive/primitive/natural_pointer.h"


template < primitive_character CHARACTER >
class string_meta_data :
   public meta_data < CHARACTER >
{
public:

   
   typedef string_meta_data < CHARACTER > STRING_META_DATA;


   using meta_data < CHARACTER >::meta_data;


   /// in bytes, without meta, with null(s)
   inline ::memsize storage_size() const { return (::memsize) this->m_sizeStorage; }
   /// storage_size expressed in number of characters
   inline ::strsize storage_character_count() const;


   /// always char count (before first [and possibly final, but not necessarily final] null terminator)
   inline ::strsize character_count() const { return (::strsize) this->m_countData; }
   inline ::memsize character_count_in_bytes() const;
   

   inline void raw_set_character_count(::strsize strsize);
   inline void set_character_count(::strsize strsize);


   operator const CHARACTER * () const noexcept { return this->begin(); }


   operator CHARACTER * () noexcept { return this->begin(); }


   const CHARACTER * c_str() const noexcept { return this->begin(); }


};


template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < ::ansi_character > > * __nil < natural_meta_data < string_meta_data < ::ansi_character > > >();

template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < ::wd16_character > > * __nil < natural_meta_data < string_meta_data < ::wd16_character > > >();

template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < ::wd32_character > > * __nil < natural_meta_data < string_meta_data < ::wd32_character > > >();





enum e_char_count
{

   char_count,
};

enum e_byte_count
{

   byte_count,
};


#include "acme/memory/string_memory_allocator.h"



