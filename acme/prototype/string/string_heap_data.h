#pragma once






template < typename STRING >
inline STRING & string_concatenate(STRING & strResult, const typename STRING::CHARACTER_TYPE * psz1, character_count nLength1, const typename STRING::CHARACTER_TYPE * psz2, character_count nLength2);

//template < typename CHARACTER_TYPE >
//class string_buffer;
#include "acme/prototype/prototype/natural_pointer.h"


template < primitive_character CHARACTER >
class string_heap_data :
   public heap_data < CHARACTER >
{
public:

   
   typedef string_heap_data < CHARACTER > STRING_HEAP_DATA;


   using heap_data < CHARACTER >::heap_data;


   /// in bytes, without meta, with null(s)
   inline ::memsize storage_size() const { return (::memsize) this->m_sizeStorageInBytes; }
   /// storage_size expressed in number of characters
   inline ::character_count storage_character_count() const;


   ///// always char count (before first [and possibly final, but not necessarily final] null terminator)
   //inline ::character_count character_count() const { return (::character_count) this->m_countData; }
   //inline ::memsize character_count_in_bytes() const;
   //inline ::memsize null_terminated_character_count_in_bytes() const;
   //

   //inline void raw_set_character_count(::character_count character_count);
   //inline void set_character_count(::character_count character_count);


   operator const CHARACTER * () const noexcept { return this->c_data(); }


   operator CHARACTER * () noexcept { return this->data(); }


   const CHARACTER * c_str() const noexcept { return this->c_data(); }


};


template < >
CLASS_DECL_ACME base_data < string_heap_data < ::ansi_character > > * __nil < base_data < string_heap_data < ::ansi_character > > >();

template < >
CLASS_DECL_ACME base_data < string_heap_data < ::wd16_character > > * __nil < base_data < string_heap_data < ::wd16_character > > >();

template < >
CLASS_DECL_ACME base_data < string_heap_data < ::wd32_character > > * __nil < base_data < string_heap_data < ::wd32_character > > >();





enum e_char_count
{

   char_count,
};

enum e_byte_count
{

   byte_count,
};


//#include "acme/memory/string_memory_allocator.h"



