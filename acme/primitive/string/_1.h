#pragma once


CLASS_DECL_ACME int trailingBytesForUTF8(::ansi_character ch);


typedef i32 HRes;


#include "character.h"




struct end_of_line_and_next_line
{

   const char * end_of_line;
   const char * next_line;

};





#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/primitive/collection/bit_array.h"


template < typename TYPE >
const auto __string_base(const TYPE & t)
{

   return t.to_string_base();

}

inline const ansi_string __string_base(const ::ansi_character * psz);
inline const wd16_string __string_base(const ::wd16_character * psz);
inline const wd32_string __string_base(const ::wd32_character * psz);



#include "_unicode.h"


#include "sz.h"


//#include "acme/exception/throw.h"
#include "static_string.h"

#ifdef __cplusplus


#include "stdstring.h"


#include "static_string.h"

#include "acme/primitive/primitive/atomic.h"

#include "acme/primitive/primitive/interlocked_count.h"

#include "acme/memory/memory_allocator.h"

#include "acme/primitive/primitive/natural.h"



#include "string_meta_data.h"

#include "simple_string_base.h"

#include "string_iterator.h"

#include "string_base.h"

#include "as_string.h"


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/primitive/collection/bit_array.h"

inline  string consume_char(const ::ansi_character *& p)
{
   auto len = ::utf8_len(p);
   string strChar(p, len);
   p += len;
   return strChar;
}
inline  wd16_string consume_char(const ::wd16_character *& p)
{
   auto len = ::utf16_len(p);
   wd16_string wd16strChar(p, len);
   p += len;
   return wd16strChar;
}
inline  wd32_string consume_char(const ::wd32_character *& p)
{
   auto len = 1;
   wd32_string wd32strChar(p, len);
   p += len;
   return wd32strChar;
}


inline  ::ansi_character * next_char(const ::ansi_character *& p)
{
   auto len = ::utf8_len(p);
   p += len;
   return (::ansi_character *)p;
}
inline  const ::wd16_character * next_char(const ::wd16_character *& p)
{
   auto len = ::utf16_len(p);
   p += len;
   return (::wd16_character *)p;
}
inline  ::wd32_character * next_char(const ::wd32_character *& p)
{
   auto len = 1;
   p += len;
   return(::wd32_character *)p;
}




#include "string_inst.h"


//#include "as_string.h"


//#include "_trait.h"


#include "string_wide_conversion.h"


#include "to_integer.h"


#endif



#ifdef WINDOWS
#define unincpy wcsncpy
#else
#define unincpy wide_count_copy
#endif

#include "ch.h"

//#include "_compare.h"
#include "from_string.h"
#include "str.h"




#include "stringtow.h"
#include "from_integer.h"




#include "ch_class.h"
#include "international.h"

#include "tokenizer.h"

#include "whole_word.h"
#include "hex.h"

//#include "istring.h"

#include "parse.h"






#include "_conv.h"



CLASS_DECL_ACME string string_format(const scoped_string & strFormat, ...);



