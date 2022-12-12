#pragma once


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/string/x/x_defines.h"
#include "acme/primitive/string/x/x_tables.h"



/** Character information class.
    \par Basic features:
    - All Unicode information is generated into tables by scripts
      xcharsets.pl  and  xtables_gen.pl
      They are using UnicodeData.txt file and some codepage files, available
      from <a href="http://www.unicode.org/">http://www.unicode.org/</a>
    - Character class supports most Unicode character properties, except for
      Bidirectional char class, and Decomposition information.
      Most of these methods works like Java Character class methods.

    \par Todo:
    - retrieving of bidirectional class information,
    - retrieving of character decomposition mappings (and normalization
      process information),
    - character 'Digit', 'Decimal Digit' properties. You can retrieve
      only 'Number' value property from digit characters.
    - No explicit surrogate characters support. Surrogate pairs are treated as distinct characters.

    @ingroup unicode
*/


CLASS_DECL_ACME int trailingBytesForUTF8(::ansi_character ch);


inline int ch_unicode_len(int c)
{

   return trailingBytesForUTF8(c) + 1;

}


inline int str_uni_len(const char * pszUtf8)
{

   return ch_unicode_len(*pszUtf8);

}



template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p);


inline bool is_trimmed_empty(const ::ansi_character * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const ::wd16_character * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const ::wd32_character * p) { return is_trimmed_string_empty(p); }



