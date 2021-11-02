#pragma once


CLASS_DECL_ACME int trailingBytesForUTF8(ansichar ch);


typedef i32 HRes;


/////////////////////////////////////////////////////////////////////////////
// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const widechar* psz, memsize nMaxLength = INT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const char* psz, memsize nMaxLength = UINT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a pointer points to valid memory
inline bool __is_valid_address(const void* p, memsize nBytes, bool bReadWrite = true)
{
#ifdef WINDOWS
   (bReadWrite);
   (nBytes);
#endif
   return (p != nullptr);
}


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/primitive/collection/bit_array.h"


template < typename TYPE >
const auto __string_base(const TYPE & t)
{

   return t.to_string_base();

}

inline const ansistring __string_base(const ansichar * psz);
inline const wd16string __string_base(const wd16char * psz);
inline const wd32string __string_base(const wd32char * psz);


template < typename STRING >
class string_type
{
public:

   using STRING_TYPE = STRING;

   STRING * this_string() { return (STRING_TYPE *)this; }
   const STRING * this_string() const { return (const STRING_TYPE *)this; }

};


#include "_unicode.h"


#include "ch.h"
#include "sz.h"


#include "acme/exception/throw.h"
#include "static_string.h"

#ifdef __cplusplus


#include "stdstring.h"


#include "static_string.h"

#include "acme/primitive/primitive/atomic.h"

#include "acme/primitive/primitive/interlocked_count.h"

#include "acme/memory/memory_allocator.h"

#include "acme/primitive/primitive/natural.h"


#include "_trait_ansi.h"
#include "_trait_wd16.h"
#include "_trait_wd32.h"

#include "_natural.h"
#include "_base.h"


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/primitive/bit.h"
#include "acme/primitive/collection/bit_array.h"


#include "string_inst.h"


#include "_conv_ansi.h"


#include "_trait.h"


#include "string_wide_conversion.h"


#include "to_integer.h"


#endif



#ifdef WINDOWS
#define unincpy wcsncpy
#else
#define unincpy wide_count_copy
#endif


#include "_compare.h"
#include "_str.h"

#include "stringtow.h"
#include "from_integer.h"




#include "ch_class.h"
#include "international.h"

#include "tokenizer.h"

#include "x.h"
#include "hex.h"

//#include "istring.h"

#include "parse.h"






#include "_conv.h"