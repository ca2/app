#pragma once


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/string/x/x_defines.h"
#include "acme/primitive/string/x/x_tables.h"


inline i32 __uni_index(const ansichar * pszChar);
inline i32 __uni_index(const wd16char * pszChar);
inline i32 __uni_index(const wd32char * pszChar);


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

inline int ch_uni_len(int c)
{

   return trailingBytesForUTF8(c) + 1;

}


inline int str_uni_len(const char * pszUtf8)
{

   return ch_uni_len(*pszUtf8);

}


namespace str
{


   class CLASS_DECL_ACME utf8_char
   {
   public:


      char     m_sz[32];
      char     m_chLen;


      utf8_char(u64 u = 0);

      i32 parse(const char * psz);


   };


   namespace ch
   {

      //    /*
      // * Index into the table below with the first byte of a UTF-8 sequence to
      // * get the number of trailing bytes that are supposed to follow it.
      // * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
      // * left as-is for anyone who may want to do such conversion, which was
      // * allowed in earlier algorithms.
      // */
      //static const char trailingBytesForUTF8[256] = {
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      //    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
      //};
      // return UTF8 Extra Bytes based on supplied First Char

      // return Unicode Index
      inline i32 uni_index(const ansichar * pszChar);
      inline i32 uni_index(const wd16char * pszChar) { strsize srclen = 2; return ::__uni_index(pszChar, &srclen); }
      inline i32 uni_index(const wd32char * pszChar) { return *pszChar; }

      // return number of characters need to be consumed to parse a Unicode Character
      inline i32 uni_len(const ansichar * pszChar);
      inline i32 uni_len(const wd16char * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
      inline i32 uni_len(const wd32char * pszChar) { return 1; }

      inline i32 ansichar_uni_len(wd32char i);
      inline i32 wd16char_uni_len(wd32char i) { return utf32_is_surrogated(i) ? 2 : 1; }
      inline i32 wd32char_uni_len(wd32char i) { return 1; }

      // return number of characters needed to represent the Unicode Character
      inline i32 char_uni_len(const ansichar *, wd32char i) { return ansichar_uni_len(i); }
      inline i32 char_uni_len(const wd16char *, wd32char i) { return wd16char_uni_len(i); }
      inline i32 char_uni_len(const wd32char *, wd32char i) { return wd32char_uni_len(i); }

      // return Unicode Index and
      // number of characters need to be consumed to parse a Unicode Character
      i32 uni_index_len(const ansichar * pszChar, i32 & len);
      i32 uni_index_len(const wd16char * pszChar, i32 & len);
      inline i32 uni_index_len(const wd32char * pszChar, i32 & len) { len = 1; return *pszChar; }


      inline bool is_legal_uni_index(i64 iUnicodeIndex)
      {

         return iUnicodeIndex >= 0 && iUnicodeIndex < 65536 ? true : false;

         //return ca >= ((u64) 0xffffffffu) ? false : true;

      }


      inline bool is_space_char(i32 i);
      inline i32 to_lower_case(i32 i);
      inline i32 to_upper_case(i32 i);
      inline i32 to_numeric_value(i32 i, float * f);


      inline bool is_lower_case(::i32 iUniIndex);
      inline bool is_upper_case(::i32 iUniIndex);
      inline bool is_title_case(::i32 iUniIndex);
      inline bool is_letter(::i32 iUniIndex);
      inline bool is_letter_or_digit(::i32 iUniIndex);
      inline bool is_digit(::i32 iUniIndex);
      inline bool is_assigned(::i32 iUniIndex);
      inline bool is_space_char(::i32 iUniIndex);

      inline bool is_lower_case(const ansichar * pszChar) { return is_lower_case(__uni_index(pszChar)); }
      inline bool is_upper_case(const ansichar * pszChar) { return is_upper_case(__uni_index(pszChar)); }
      inline bool is_title_case(const ansichar * pszChar) { return is_title_case(__uni_index(pszChar)); }
      inline bool is_letter(const ansichar * pszChar) { return is_letter(__uni_index(pszChar)); }
      inline bool is_letter_or_digit(const ansichar * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
      inline bool is_digit(const ansichar * pszChar) { return is_digit(__uni_index(pszChar)); }
      inline bool is_assigned(const ansichar * pszChar) { return is_assigned(__uni_index(pszChar)); }
      inline bool is_space_char(const ansichar * pszChar) { return is_space_char(__uni_index(pszChar)); }

      inline bool is_lower_case(const wd16char * pszChar) { return is_lower_case(__uni_index(pszChar)); }
      inline bool is_upper_case(const wd16char * pszChar) { return is_upper_case(__uni_index(pszChar)); }
      inline bool is_title_case(const wd16char * pszChar) { return is_title_case(__uni_index(pszChar)); }
      inline bool is_letter(const wd16char * pszChar) { return is_letter(__uni_index(pszChar)); }
      inline bool is_letter_or_digit(const wd16char * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
      inline bool is_digit(const wd16char * pszChar) { return is_digit(__uni_index(pszChar)); }
      inline bool is_assigned(const wd16char * pszChar) { return is_assigned(__uni_index(pszChar)); }
      inline bool is_space_char(const wd16char * pszChar) { return is_space_char(__uni_index(pszChar)); }

      inline bool is_lower_case(const wd32char * pszChar) { return is_lower_case(__uni_index(pszChar)); }
      inline bool is_upper_case(const wd32char * pszChar) { return is_upper_case(__uni_index(pszChar)); }
      inline bool is_title_case(const wd32char * pszChar) { return is_title_case(__uni_index(pszChar)); }
      inline bool is_letter(const wd32char * pszChar) { return is_letter(__uni_index(pszChar)); }
      inline bool is_letter_or_digit(const wd32char * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
      inline bool is_digit(const wd32char * pszChar) { return is_digit(__uni_index(pszChar)); }
      inline bool is_assigned(const wd32char * pszChar) { return is_assigned(__uni_index(pszChar)); }
      inline bool is_space_char(const wd32char * pszChar) { return is_space_char(__uni_index(pszChar)); }

      inline bool is_whitespace(i64 i)
      {
         if (!is_legal_uni_index(i))
            return false;
         return  (i == 0x20)
            ||
            ((i <= 0x0020) &&
            (((((1 << 0x0009) |
               (1 << 0x000A) |
               (1 << 0x000C) |
               (1 << 0x000D)) >> i) & 1) != 0))
            ||
            (((((1 << CHAR_CATEGORY_Zs) |
            (1 << CHAR_CATEGORY_Zl) |
               (1 << CHAR_CATEGORY_Zp)
               ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0);
      }

      inline bool is_whitespace(const char * psz) { return is_whitespace(uni_index(psz)); }
      inline bool is_whitespace(const wd16char * psz) { return is_whitespace(uni_index(psz)); }
      inline bool is_whitespace(const wd32char * psz) { return is_whitespace(uni_index(psz)); }

      //CLASS_DECL_ACME bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

      CLASS_DECL_ACME bool is_number(const char * pszUtf8Char);
//      CLASS_DECL_ACME bool to_numeric_value(const char * pszUtf8Char, float *f);

      CLASS_DECL_ACME string get_category_name(const char * pszUtf8Char);
      ECharCategory get_category(const char * pszUtf8Char);

      CLASS_DECL_ACME i32 get_combining_class(const char * pszUtf8Char);
      CLASS_DECL_ACME bool is_mirrored(const char * pszUtf8Char);

      CLASS_DECL_ACME i32 size_of_tables();


      inline CLASS_DECL_ACME bool is_kanji(i64 i) { return i >=0x4E00 && i <=0x9FBF; }
      inline CLASS_DECL_ACME bool is_hiragana(i64 i) { return i >= 0x3040 && i <= 0x309F; }
      inline CLASS_DECL_ACME bool is_katakana(i64 i) { return i >= 0x30A0 && i <= 0x30FF; }
      inline CLASS_DECL_ACME bool is_japanese(i64 i) { return is_kanji(i) || is_hiragana(i) || is_katakana(i); }
      inline CLASS_DECL_ACME bool is_kanji(const char * pszUtf8) { return is_kanji(uni_index(pszUtf8)); }
      inline CLASS_DECL_ACME bool is_hiragana(const char * pszUtf8) { return is_hiragana(uni_index(pszUtf8));  }
      inline CLASS_DECL_ACME bool is_katakana(const char * pszUtf8) { return is_katakana(uni_index(pszUtf8));  }
      inline CLASS_DECL_ACME bool is_japanese(const char * pszUtf8) { return is_japanese(uni_index(pszUtf8));  }

      inline i32 ansichar_uni_len(wd32char i)
      {
         if (i < 0)
         {
            return -1;
         }
         else if (i < 0x0080)
         {
            return 1;
         }
         else if (i < 0x0800)
         {
            return 2;
         }
         else
         {
            return 3;
         }
      }

   }


} // namespace str


/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are topic to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


inline i32 __uni_index(const ansichar * pszChar) { return ::str::ch::uni_index(pszChar); }
inline i32 __uni_len(const ansichar * pszChar) { return ::str::ch::uni_len(pszChar); }
inline i32 __uni_index_len(const ansichar * pszChar, i32 & len) { return ::str::ch::uni_index_len(pszChar, len); }


inline i32 __uni_index(const wd16char * pszChar) { return ::str::ch::uni_index(pszChar); }
inline i32 __uni_len(const wd16char * pszChar) { return ::str::ch::uni_len(pszChar); }
inline i32 __uni_index_len(const wd16char * pszChar, i32 & len) { return ::str::ch::uni_index_len(pszChar, len); }


inline i32 __uni_index(const wd32char * pszChar) { return ::str::ch::uni_index(pszChar); }
inline i32 __uni_len(const wd32char * pszChar) { return ::str::ch::uni_len(pszChar); }
inline i32 __uni_index_len(const wd32char * pszChar, i32 & len) { return ::str::ch::uni_index_len(pszChar, len); }



template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p)
{

   if(::is_null(p))
   {

      return true;

   }

   while(*p)
   {

      if(!::str::ch::is_whitespace(*p))
      {

         return false;

      }

      p++;

   }

   return true;

}


inline bool is_trimmed_empty(const ansichar * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd16char * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd32char * p) { return is_trimmed_string_empty(p); }

