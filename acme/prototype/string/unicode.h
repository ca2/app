#pragma once


#include "acme/prototype/collection/range.h"


#if WCHAR_T_SIZE == 16

CLASS_DECL_ACME wstring wd32_to_wd16_str(const ::wd32_character * pcwsz, character_count input_size = -1);

#endif

CLASS_DECL_ACME string wd16_to_ansi_str(const ::wd16_character * pwsz, character_count srclen = -1);

CLASS_DECL_ACME string wd32_to_ansi_str(const ::wd32_character * pwsz, character_count srclen = -1);



CLASS_DECL_ACME string         get_utf8_char(const_char_pointer psz);
inline bool next_unicode_character(::string & strChar, const ::ansi_character*& psz)
{
   strChar = get_utf8_char(psz);
   if (strChar.is_empty())
   {

      return false;
   }
   psz += strChar.length();
   return true;

}
int            get_utf8_char_length(const_char_pointer psz);
string         get_utf8_char(const_char_pointer psz, const_char_pointer pszEnd);
::const_ansi_range get_utf8_char(::const_ansi_range & range);

bool           get_utf8_char(string & strChar, const_char_pointer &psz, const_char_pointer pszEnd);
string         get_utf8_char(const_char_pointer pszBeg, const_char_pointer psz, character_count i);
string         utf8_next_char(const_char_pointer pszBeg, const_char_pointer psz, character_count i = 0);
string         utf8_previous_char(const_char_pointer pszBeg, const_char_pointer psz, character_count i = 0);
CLASS_DECL_ACME utf8_character         unicode_to_utf8(long long ch);
CLASS_DECL_ACME character_count        unicode_to_utf8_length(long long ch);
int            unicode_to_utf8_2_or_more(::ansi_character * dest, int ch);


CLASS_DECL_ACME const_char_pointer utf8_dec(const_char_pointer pszBeg, const_char_pointer psz);


//inline int unicode_index(const_char_pointer &input, character_count * psrclen);
//inline int unicode_index(const ::wd16_character *& input, character_count * psrclen);
//inline int unicode_index(const ::wd32_character *& input, character_count * psrclen);


// return Unicode Index and
// number of characters need to be consumed to parse a Unicode Character
inline int unicode_index_length(const_char_pointer pszChar, int & len);
inline int unicode_index_length(const ::wd16_character * pszChar, int & len);
inline int unicode_index_length(const ::wd32_character * pszChar, int & len) { len = *pszChar != 0; return *pszChar; }


inline int consume_unicode_index_length(const_char_pointer &pszChar);
inline int consume_unicode_index_length(const ::wd16_character * & pszChar);
inline int consume_unicode_index_length(const ::wd32_character * & pszChar) { return *pszChar++; }


inline int unicode_index(const_char_pointer pszChar) { int len = 0; return unicode_index_length(pszChar, len); }
inline int unicode_index(const ::wd16_character * pszChar) { int len = 0; return unicode_index_length(pszChar, len); }
inline int unicode_index(const ::wd32_character * pszChar) { int len = 0; return unicode_index_length(pszChar, len); }


inline bool is_legal_unicode_index(int iUnicodeIndex);


CLASS_DECL_ACME int unicode_to_lower_case(int i);
CLASS_DECL_ACME int unicode_to_upper_case(int i);


#define UNI_DECLARE_IS_FUNCTION(function) \
inline bool function(int i); \
inline bool function(const_char_pointer psz); \
inline bool function(const ::wd16_character * psz); \
inline bool function(const ::wd32_character * psz);

#define UNI_IMPLEMENT_IS_FUNCTION(function) \
inline bool function(const_char_pointer psz) { return function(unicode_index(psz)); } \
inline bool function(const ::wd16_character * psz) { return function(unicode_index(psz)); } \
inline bool function(const ::wd32_character * psz) { return function(unicode_index(psz)); }


UNI_DECLARE_IS_FUNCTION(unicode_is_whitespace);
UNI_DECLARE_IS_FUNCTION(unicode_is_lower_case);
UNI_DECLARE_IS_FUNCTION(unicode_is_upper_case);
UNI_DECLARE_IS_FUNCTION(unicode_is_title_case);
UNI_DECLARE_IS_FUNCTION(unicode_is_letter);
UNI_DECLARE_IS_FUNCTION(unicode_is_letter_or_digit);
UNI_DECLARE_IS_FUNCTION(unicode_is_digit);
UNI_DECLARE_IS_FUNCTION(unicode_is_assigned);
UNI_DECLARE_IS_FUNCTION(unicode_is_space_char);
UNI_DECLARE_IS_FUNCTION(unicode_is_number);
UNI_DECLARE_IS_FUNCTION(unicode_is_mirrored);


UNI_IMPLEMENT_IS_FUNCTION(unicode_is_whitespace);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_lower_case);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_upper_case);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_title_case);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_letter);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_letter_or_digit);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_digit);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_assigned);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_space_char);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_number);
UNI_IMPLEMENT_IS_FUNCTION(unicode_is_mirrored);


inline int unicode_to_title_case(int i);
inline int unicode_to_numeric_value(int i, float * f);
inline ECharCategory unicode_get_category(int i);
inline int unicode_get_combining_class(int i);
inline int unicode_size_of_tables();


CLASS_DECL_ACME int unicode_to_lower_case(int i);
CLASS_DECL_ACME int unicode_to_upper_case(int i);


//inline const_char_pointer _string_scan(::const_ansi_range range, ::const_ansi_range rangeCharacters) noexcept;
//inline const ::wd16_character * _string_scan(::const_wd16_range range, ::const_wd16_range rangeCharacters) noexcept;
//inline const ::wd32_character * _string_scan(::const_wd32_range range, ::const_wd32_range rangeCharacters) noexcept;


//template < primitive_character CHARACTER >
//inline const CHARACTER * string_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockCharacters) noexcept;


inline int ansichar_unicode_len(::wd32_character i);







template < typename TYPE1, typename TYPE2 >
inline ::std::strong_ordering compare(const TYPE1 & str1, const TYPE2 & str2);


template < typename TYPE1, typename TYPE2 >
inline ::std::strong_ordering case_insensitive_order(const TYPE1 & str1, const TYPE2 & str2);


template < typename TYPE1, typename TYPE2 >
inline bool equals(const TYPE1 & str1, const TYPE2 & str2) { return compare(str1, str2) == 0; }


template < typename TYPE1, typename TYPE2 >
inline bool case_insensitive_equals(const TYPE1 & str1, const TYPE2 & str2) { return case_insensitive_order(str1, str2) == 0; }


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent);


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent);




template < primitive_character CHARACTER >
inline bool case_insensitive_range_begins(::range < const CHARACTER * > range, ::range < const CHARACTER * > rangePrefix)
{

   return range.begins(rangePrefix, ::comparison::case_insensitive< CHARACTER >());

}


template < primitive_character CHARACTER >
inline bool case_insensitive_range_ends(::range < const CHARACTER * > range, ::range < const CHARACTER * > rangeSuffix)
{

   return range.ends(rangeSuffix, ::comparison::case_insensitive< CHARACTER >());

}


template < primitive_character CHARACTER >
constexpr bool case_insensitive_sz_begins_sz(const CHARACTER * psz, const CHARACTER * pszPrefix)
{

   bool b;

   if (sz_contains_sz_prefix(b, psz, pszPrefix))
   {

      return b;

   }

   while (*psz && *pszPrefix)
   {

      if (::comparison::case_insensitive < CHARACTER >()(*psz, *pszPrefix))
      {

         return false;

      }

      psz++;

      pszPrefix++;

   }

   return true;

}
//template < primitive_character CHARACTER >
//constexpr bool case_insensitive_sz_ends_sz(const CHARACTER * psz, const CHARACTER * pszSuffix)
//{
//
//   return case_insensitive_string_range_ends<CHARACTER>(psz, pszSuffix);
//
//}


inline bool string_begins(const_char_pointer pz, const_char_pointer pzPrefix)
{   return null_terminated_begins_null_terminated(pz, pzPrefix, ::comparison::comparison<::ansi_character>()); }
inline bool string_begins(const ::wd16_character * pz, const ::wd16_character * pzPrefix)
{   return null_terminated_begins_null_terminated(pz, pzPrefix, ::comparison::comparison<::wd16_character>());}
inline bool string_begins(const ::wd32_character * pz, const ::wd32_character * pzPrefix)
{   return null_terminated_begins_null_terminated(pz, pzPrefix, ::comparison::comparison<::wd32_character>());}


template < primitive_character CHARACTER >
inline bool _string_begins(const CHARACTER * psz, character_count len, const CHARACTER * pszPrefix, character_count & lenPrefix)
{
   return string_begins<const CHARACTER>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
}

//inline bool _string_begins(const ::wd16_character * psz, character_count len, const ::wd16_character * pszPrefix, character_count & lenPrefix)
//{
//   return string_begins<const ::wd16_character>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}
//inline bool _string_begins(const ::wd16_character* psz, character_count len, const ::wd16_character* pszPrefix, character_count& lenPrefix)
//{
//   return string_begins<const ::wd16_character>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}
//inline bool _string_begins(const ::wd32_character* psz, character_count len, const ::wd32_character* pszPrefix, character_count& lenPrefix)
//{
//   return string_begins<const ::wd32_character>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}



inline bool string_ends(const_char_pointer psz, const_char_pointer pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::comparison<::ansi_character>()); }
inline bool string_ends(const ::wd16_character * psz, const ::wd16_character * pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::comparison<::wd16_character>()); }
inline bool string_ends(const ::wd32_character * psz, const ::wd32_character * pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::comparison<::wd32_character>()); }

//template < primitive_character CHARACTER >
//inline bool _string_ends(const CHARACTER * psz, character_count len, const CHARACTER * pszSuffix, character_count& lenSuffix)
//{
//   return _range_ends<const CHARACTER>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}
//inline bool _string_ends(const ::wd16_character* psz, character_count len, const ::wd16_character* pszSuffix, character_count& lenSuffix)
//{
//   return string_ends<const ::wd16_character>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}
//inline bool _string_ends(const ::wd32_character* psz, character_count len, const ::wd32_character* pszSuffix, character_count& lenSuffix)
//{
//   return string_ends<const ::wd32_character>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}





inline bool case_insensitive_string_begins(const_char_pointer psz, const_char_pointer pszPrefix)
{   return null_terminated_begins_null_terminated(psz, pszPrefix, ::comparison::case_insensitive<::ansi_character>()); }
inline bool case_insensitive_string_begins(const ::wd16_character * psz, const ::wd16_character * pszPrefix)
{   return null_terminated_begins_null_terminated(psz, pszPrefix, ::comparison::case_insensitive<::wd16_character>()); }
inline bool case_insensitive_string_begins(const ::wd32_character * psz, const ::wd32_character * pszPrefix)
{   return null_terminated_begins_null_terminated(psz, pszPrefix, ::comparison::case_insensitive<::wd32_character>()); }


//template < primitive_character CHARACTER >
//inline bool case_insensitive__string_begins(const CHARACTER * psz, character_count len, const CHARACTER * pszPrefix, character_count & lenPrefix)
//{
//   return case_insensitive_string_begins<const CHARACTER>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}
//inline bool case_insensitive__string_begins(const ::wd16_character* psz, character_count len, const ::wd16_character* pszPrefix, character_count& lenPrefix)
//{
//   return case_insensitive_string_begins<const ::wd16_character>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}
//inline bool case_insensitive__string_begins(const ::wd32_character* psz, character_count len, const ::wd32_character* pszPrefix, character_count& lenPrefix)
//{
//   return case_insensitive_string_begins<const ::wd32_character>({ psz, len }, { pszPrefix, (character_count)(lenPrefix = string_safe_length(pszPrefix)) });
//}

inline bool case_insensitive_string_ends(const_char_pointer psz, const_char_pointer pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::case_insensitive<::ansi_character>());}
inline bool case_insensitive_string_ends(const ::wd16_character * psz, const ::wd16_character * pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::case_insensitive<::wd16_character>());}
inline bool case_insensitive_string_ends(const ::wd32_character * psz, const ::wd32_character * pszSuffix)
{   return ::null_terminated_ends(psz, pszSuffix, ::comparison::case_insensitive<::wd32_character>());}

//template < primitive_character CHARACTER >
//inline bool case_insensitive__string_ends(const CHARACTER * psz, character_count len, const CHARACTER * pszSuffix, character_count & lenSuffix)
//{
//   return case_insensitive_string_ends<const CHARACTER>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}
//inline bool case_insensitive__string_ends(const ::wd16_character* psz, character_count len, const ::wd16_character* pszSuffix, character_count& lenSuffix)
//{
//   return case_insensitive_string_ends<const ::wd16_character>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}
//inline bool case_insensitive__string_ends(const ::wd32_character* psz, character_count len, const ::wd32_character* pszSuffix, character_count& lenSuffix)
//{
//   return case_insensitive_string_ends<const ::wd32_character>({ psz, len }, { pszSuffix, (character_count)(lenSuffix = string_safe_length(pszSuffix)) });
//}


template < typename CHAR_TYPE >
bool string_eat_before(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);


template < typename CHAR_TYPE >
bool string_eat_before_let_separator(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);

template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p);


inline bool is_trimmed_empty(const_char_pointer p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const ::wd16_character * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const ::wd32_character * p) { return is_trimmed_string_empty(p); }


#pragma

// return number of characters need to be consumed to parse a Unicode Character
inline int unicode_len(const_char_pointer pszChar);
inline int unicode_len(const ::wd16_character * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
inline int unicode_len(const ::wd32_character * pszChar) { return 1; }


inline int ansichar_unicode_len(::wd32_character i);
inline int wd16char_unicode_len(::wd32_character i) { return utf32_is_surrogated(i) ? 2 : 1; }
inline int wd32char_unicode_len(::wd32_character i) { return 1; }

// return number of characters needed to represent the Unicode Character
inline int char_unicode_len(const_char_pointer ,::wd32_character i) { return ansichar_unicode_len(i); }
inline int char_unicode_len(const ::wd16_character *, ::wd32_character i) { return wd16char_unicode_len(i); }
inline int char_unicode_len(const ::wd32_character *, ::wd32_character i) { return wd32char_unicode_len(i); }





inline bool unicode_is_whitespace(int i);
inline bool unicode_is_space_char(int i);
inline int unicode_to_lower_case(int i);
inline int unicode_to_upper_case(int i);
inline int unicode_to_title_case(int i);
inline int unicode_to_numeric_value(int i, float * f);


inline bool unicode_is_lower_case(int iUniIndex);
inline bool unicode_is_upper_case(int iUniIndex);
inline bool unicode_is_title_case(int iUniIndex);
inline bool unicode_is_letter(int iUniIndex);
inline bool unicode_is_letter_or_digit(int iUniIndex);
inline bool unicode_is_digit(int iUniIndex);
inline bool unicode_is_number(int iUniIndex);
inline bool unicode_is_assigned(int iUniIndex);
inline bool unicode_is_space_char(int iUniIndex);


// bool is_whitespace(const ::scoped_string & scopedstrUtf8Char, const_char_pointer pszEnd);

bool unicode_is_number(const ::scoped_string & scopedstrUtf8Char);
//       bool to_numeric_value(const ::scoped_string & scopedstrUtf8Char, float *f);

inline ECharCategory unicode_get_category(int i);
inline int unicode_get_combining_class(int i);
inline bool unicode_is_mirrored(int i);

string unicode_get_category_name(const ::scoped_string & scopedstrUtf8Char);
ECharCategory unicode_get_category(const ::scoped_string & scopedstrUtf8Char);

int unicode_get_combining_class(const ::scoped_string & scopedstrUtf8Char);
bool unicode_is_mirrored(const ::scoped_string & scopedstrUtf8Char);

int unicode_size_of_tables();


inline  bool unicode_is_kanji(long long i) { return i >= 0x4E00 && i <= 0x9FBF; }
inline  bool unicode_is_hiragana(long long i) { return i >= 0x3040 && i <= 0x309F; }
inline  bool unicode_is_katakana(long long i) { return i >= 0x30A0 && i <= 0x30FF; }
inline  bool unicode_is_japanese(long long i) { return unicode_is_kanji(i) || unicode_is_hiragana(i) || unicode_is_katakana(i); }
inline  bool unicode_is_kanji(const_char_pointer pszUtf8) { return unicode_is_kanji(unicode_index(pszUtf8)); }
inline  bool unicode_is_hiragana(const_char_pointer pszUtf8) { return unicode_is_hiragana(unicode_index(pszUtf8)); }
inline  bool unicode_is_katakana(const_char_pointer pszUtf8) { return unicode_is_katakana(unicode_index(pszUtf8)); }
inline  bool unicode_is_japanese(const_char_pointer pszUtf8) { return unicode_is_japanese(unicode_index(pszUtf8)); }


void * unicode_char_bidi_names_non_usage_warning();


int unicode_ref_tables();
const_char_pointer unicode_get_category_name(int i);


//template < typename POINTER >
//inline ::string as_string(const ::platform::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate < POINTER > & memoryallocpointer)
//{
//
//   string str;
//
//   str.assign(memoryallocpointer.m_p, memoryallocpointer.m_iSize);
//
//   return str;
//
//}


CLASS_DECL_ACME string demangle(const_char_pointer pszMangledName);


CLASS_DECL_ACME void copy(::string & str, const subparticle & subparticle);


CLASS_DECL_ACME string string_from_strdup(const_char_pointer psz);


CLASS_DECL_ACME void copy(::string & str, const subparticle & subparticle);



