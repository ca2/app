﻿#pragma once


CLASS_DECL_ACME int trailingBytesForUTF8(ansichar ch);


typedef i32 HRes;


#include "character.h"




struct end_of_line_and_next_line
{

   const char * end_of_line;
   const char * next_line;

};


inline ::string operator+(const char * psz, const ::string & str);
inline ::string operator+(const char * psz, const ::atom & atom);
inline ::string operator+(const char * psz, const ::payload & payload);
inline ::string operator+(const char * psz, const ::property & property);

#include "_c.h"

//#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/primitive/collection/bit_array.h"
#include "ch.h"
#include "_unicode.h"


// template < typename TYPE >
// const auto __string_base(const TYPE & t)
// {

//    return t.to_string_base();

// }

// inline const ansistring __string_base(const ansichar * psz);
// inline const wd16string __string_base(const wd16char * psz);
// inline const wd32string __string_base(const wd32char * psz);



// #include "_unicode.h"


// #include "sz.h"


// //#include "acme/exception/throw.h"
// #include "static_string.h"

// #ifdef __cplusplus


// #include "stdstring.h"


// #include "static_string.h"

// #include "acme/primitive/primitive/atomic.h"

// #include "acme/primitive/primitive/interlocked_count.h"

// #include "acme/memory/memory_allocator.h"

// #include "acme/primitive/primitive/natural.h"



// #include "string_meta_data.h"

// #include "string_natural_pointer.h"

// #include "string_iterator.h"

// #include "string_base.h"

// #include "__string.h"


// #include "acme/primitive/string/x/x_charcategory.h"
// #include "acme/primitive/primitive/bit.h"
// #include "acme/primitive/collection/bit_array.h"

// inline  string consume_char(const ansichar *& p)
// {
//    auto len = ::utf8_len(p);
//    string strChar(p, len);
//    p += len;
//    return strChar;
// }
// inline  wd16string consume_char(const wd16char *& p)
// {
//    auto len = ::utf16_len(p);
//    wd16string wd16strChar(p, len);
//    p += len;
//    return wd16strChar;
// }
// inline  wd32string consume_char(const wd32char *& p)
// {
//    auto len = 1;
//    wd32string wd32strChar(p, len);
//    p += len;
//    return wd32strChar;
// }


// inline  ansichar * next_char(const ansichar *& p)
// {
//    auto len = ::utf8_len(p);
//    p += len;
//    return (ansichar *)p;
// }
// inline  const wd16char * next_char(const wd16char *& p)
// {
//    auto len = ::utf16_len(p);
//    p += len;
//    return (wd16char *)p;
// }
// inline  wd32char * next_char(const wd32char *& p)
// {
//    auto len = 1;
//    p += len;
//    return(wd32char *)p;
// }




// #include "string_inst.h"


// //#include "__string.h"


// //#include "_trait.h"


// #include "string_wide_conversion.h"


// #include "to_integer.h"


// #endif



// #ifdef WINDOWS
// #define unincpy wcsncpy
// #else
// #define unincpy wide_count_copy
// #endif

// #include "ch.h"

// //#include "_compare.h"
// #include "from_string.h"
// #include "str.h"




// #include "stringtow.h"
// #include "from_integer.h"




// #include "ch_class.h"
// #include "international.h"

// #include "tokenizer.h"

// #include "whole_word.h"
// #include "hex.h"

// //#include "istring.h"

// #include "parse.h"






// #include "_conv.h"



// CLASS_DECL_ACME string string_format(const char * pszFormat, ...);


