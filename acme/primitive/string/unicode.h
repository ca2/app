#pragma once


#if WCHAR_T_SIZE == 16

CLASS_DECL_ACME wstring wd32_to_wd16_str(const wd32char * pcwsz, strsize input_size = -1);

#endif

CLASS_DECL_ACME string wd16_to_ansi_str(const wd16char * pwsz, strsize srclen = -1);

CLASS_DECL_ACME string wd32_to_ansi_str(const wd32char * pwsz, strsize srclen = -1);



CLASS_DECL_ACME string         get_utf8_char(const ansichar * psz);
int            get_utf8_char_length(const ansichar * psz);
string         get_utf8_char(const ansichar * psz, const ansichar * pszEnd);
bool           get_utf8_char(string & strChar, const char *& psz, const char * pszEnd);
string         get_utf8_char(const ansichar * pszBeg, const ansichar * psz, strsize i);
string         utf8_next_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
string         utf8_previous_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
CLASS_DECL_ACME utf8_character         unicode_to_utf8(i64 ch);
CLASS_DECL_ACME strsize        unicode_to_utf8_length(i64 ch);
i32            unicode_to_utf8_2_or_more(ansichar * dest, i32 ch);


CLASS_DECL_ACME const ansichar * utf8_dec(const ansichar * pszBeg, const ansichar * psz);


//inline i32 unicode_index(const ansichar *& input, strsize * psrclen);
//inline i32 unicode_index(const wd16char *& input, strsize * psrclen);
//inline i32 unicode_index(const wd32char *& input, strsize * psrclen);


// return Unicode Index and
// number of characters need to be consumed to parse a Unicode Character
inline i32 unicode_index_length(const ansichar * pszChar, i32 & len);
inline i32 unicode_index_length(const wd16char * pszChar, i32 & len);
inline i32 unicode_index_length(const wd32char * pszChar, i32 & len) { len = *pszChar != 0; return *pszChar; }


inline i32 consume_unicode_index_length(const ansichar * & pszChar);
inline i32 consume_unicode_index_length(const wd16char * & pszChar);
inline i32 consume_unicode_index_length(const wd32char * & pszChar) { return *pszChar++; }


inline i32 unicode_index(const ansichar * pszChar) { ::i32 len = 0; return unicode_index_length(pszChar, len); }
inline i32 unicode_index(const wd16char * pszChar) { ::i32 len = 0; return unicode_index_length(pszChar, len); }
inline i32 unicode_index(const wd32char * pszChar) { ::i32 len = 0; return unicode_index_length(pszChar, len); }


inline bool is_legal_unicode_index(i32 iUnicodeIndex);


CLASS_DECL_ACME ::i32 unicode_to_lower_case(::i32 i);
CLASS_DECL_ACME ::i32 unicode_to_upper_case(::i32 i);


#define UNI_DECLARE_IS_FUNCTION(function) \
inline bool function(::i32 i); \
inline bool function(const ansichar * psz); \
inline bool function(const wd16char * psz); \
inline bool function(const wd32char * psz);

#define UNI_IMPLEMENT_IS_FUNCTION(function) \
inline bool function(const ansichar * psz) { return function(unicode_index(psz)); } \
inline bool function(const wd16char * psz) { return function(unicode_index(psz)); } \
inline bool function(const wd32char * psz) { return function(unicode_index(psz)); }


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


inline ::i32 unicode_to_title_case(::i32 i);
inline i32 unicode_to_numeric_value(i32 i, float * f);
inline ECharCategory unicode_get_category(i32 i);
inline i32 unicode_get_combining_class(i32 i);
inline i32 unicode_size_of_tables();


CLASS_DECL_ACME ::i32 unicode_to_lower_case(::i32 i);
CLASS_DECL_ACME ::i32 unicode_to_upper_case(::i32 i);


inline const ansichar * string_scan(const ansichar * pszBlock, const ansichar * pszMatch) noexcept;
inline const wd16char * string_scan(const wd16char * pszBlock, const wd16char * pszMatch) noexcept;
inline const wd32char * string_scan(const wd32char * pszBlock, const wd32char * pszMatch) noexcept;


inline i32 ansichar_unicode_len(wd32char i);







template < typename TYPE1, typename TYPE2 >
inline i32 compare(const TYPE1 & str1, const TYPE2 & str2);


template < typename TYPE1, typename TYPE2 >
inline i32 compare_ci(const TYPE1 & str1, const TYPE2 & str2);


template < typename TYPE1, typename TYPE2 >
inline bool equals(const TYPE1 & str1, const TYPE2 & str2) { return !compare(str1, str2); }


template < typename TYPE1, typename TYPE2 >
inline bool equals_ci(const TYPE1 & str1, const TYPE2 & str2) { return !compare_ci(str1, str2); }


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent);


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent);




template < typename TYPE_CHAR >
inline bool string_begins(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix);
template < typename TYPE_CHAR >
inline bool string_ends(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix);
template < typename TYPE_CHAR >
inline bool string_begins_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix);
template < typename TYPE_CHAR >
inline bool string_ends_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix);


inline bool string_begins(const ansichar * psz, const ansichar * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline bool string_begins(const wd16char * psz, const wd16char * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline bool string_begins(const wd32char * psz, const wd32char * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }

inline bool _string_begins(const ansichar* psz, strsize len, const ansichar* pszPrefix, strsize & lenPrefix)
{
   return string_begins(psz, len, pszPrefix, (strsize)(lenPrefix = string_safe_length(pszPrefix)));
}
inline bool _string_begins(const wd16char* psz, strsize len, const wd16char* pszPrefix, strsize& lenPrefix)
{
   return string_begins(psz, len, pszPrefix, (strsize)(lenPrefix = string_safe_length(pszPrefix)));
}
inline bool _string_begins(const wd32char* psz, strsize len, const wd32char* pszPrefix, strsize& lenPrefix)
{
   return string_begins(psz, len, pszPrefix, (strsize)(lenPrefix = string_safe_length(pszPrefix)));
}


inline bool string_ends(const ansichar * psz, const ansichar * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline bool string_ends(const wd16char * psz, const wd16char * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline bool string_ends(const wd32char * psz, const wd32char * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }


inline bool _string_ends(const ansichar* psz, strsize len, const ansichar* pszSuffix, strsize& lenSuffix)
{
   return string_ends(psz, len, pszSuffix, (strsize)(lenSuffix= string_safe_length(pszSuffix)));
}
inline bool _string_ends(const wd16char* psz, strsize len, const wd16char* pszSuffix, strsize& lenSuffix)
{
   return string_ends(psz, len, pszSuffix, (strsize)(lenSuffix =string_safe_length(pszSuffix)));
}
inline bool _string_ends(const wd32char* psz, strsize len, const wd32char* pszSuffix, strsize& lenSuffix)
{
   return string_ends(psz, len, pszSuffix, (strsize)(lenSuffix= string_safe_length(pszSuffix)));
}

inline bool string_begins_ci(const ansichar * psz, const ansichar * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline bool string_begins_ci(const wd16char * psz, const wd16char * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline bool string_begins_ci(const wd32char * psz, const wd32char * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }

inline bool _string_begins_ci(const ansichar* psz, strsize len, const ansichar* pszPrefix, strsize & lenPrefix)
{
   return string_begins_ci(psz, len, pszPrefix,(strsize)( lenPrefix =string_safe_length(pszPrefix)));
}
inline bool _string_begins_ci(const wd16char* psz, strsize len, const wd16char* pszPrefix, strsize& lenPrefix)
{
   return string_begins_ci(psz, len, pszPrefix, (strsize)(lenPrefix= string_safe_length(pszPrefix)));
}
inline bool _string_begins_ci(const wd32char* psz, strsize len, const wd32char* pszPrefix, strsize& lenPrefix)
{
   return string_begins_ci(psz, len, pszPrefix, (strsize)(lenPrefix=string_safe_length(pszPrefix)));
}

inline bool string_ends_ci(const ansichar * psz, const ansichar * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline bool string_ends_ci(const wd16char * psz, const wd16char * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline bool string_ends_ci(const wd32char * psz, const wd32char * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }

inline bool _string_ends_ci(const ansichar* psz, strsize len, const ansichar* pszSuffix, strsize & lenSuffix)
{
   return string_ends_ci(psz, len, pszSuffix, (strsize)(lenSuffix = string_safe_length(pszSuffix)));
}
inline bool _string_ends_ci(const wd16char* psz, strsize len, const wd16char* pszSuffix, strsize& lenSuffix)
{
   return string_ends_ci(psz, len, pszSuffix, (strsize)(lenSuffix = string_safe_length(pszSuffix)));
}
inline bool _string_ends_ci(const wd32char* psz, strsize len, const wd32char* pszSuffix, strsize& lenSuffix)
{
   return string_ends_ci(psz, len, pszSuffix, (strsize)(lenSuffix = string_safe_length(pszSuffix)));
}

template < typename CHAR_TYPE >
bool string_eat_before(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);


template < typename CHAR_TYPE >
bool string_eat_before_let_separator(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);

template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p);


inline bool is_trimmed_empty(const ansichar * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd16char * p) { return is_trimmed_string_empty(p); }
inline bool is_trimmed_empty(const wd32char * p) { return is_trimmed_string_empty(p); }


#pragma

// return number of characters need to be consumed to parse a Unicode Character
inline i32 unicode_len(const ansichar * pszChar);
inline i32 unicode_len(const wd16char * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
inline i32 unicode_len(const wd32char * pszChar) { return 1; }


inline i32 ansichar_unicode_len(wd32char i);
inline i32 wd16char_unicode_len(wd32char i) { return utf32_is_surrogated(i) ? 2 : 1; }
inline i32 wd32char_unicode_len(wd32char i) { return 1; }

// return number of characters needed to represent the Unicode Character
inline i32 char_unicode_len(const ansichar *, wd32char i) { return ansichar_unicode_len(i); }
inline i32 char_unicode_len(const wd16char *, wd32char i) { return wd16char_unicode_len(i); }
inline i32 char_unicode_len(const wd32char *, wd32char i) { return wd32char_unicode_len(i); }





inline bool unicode_is_whitespace(i32 i);
inline bool unicode_is_space_char(i32 i);
inline i32 unicode_to_lower_case(i32 i);
inline i32 unicode_to_upper_case(i32 i);
inline i32 unicode_to_title_case(i32 i);
inline i32 unicode_to_numeric_value(i32 i, float * f);


inline bool unicode_is_lower_case(::i32 iUniIndex);
inline bool unicode_is_upper_case(::i32 iUniIndex);
inline bool unicode_is_title_case(::i32 iUniIndex);
inline bool unicode_is_letter(::i32 iUniIndex);
inline bool unicode_is_letter_or_digit(::i32 iUniIndex);
inline bool unicode_is_digit(::i32 iUniIndex);
inline bool unicode_is_number(::i32 iUniIndex);
inline bool unicode_is_assigned(::i32 iUniIndex);
inline bool unicode_is_space_char(::i32 iUniIndex);


// bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

bool unicode_is_number(const char * pszUtf8Char);
//       bool to_numeric_value(const char * pszUtf8Char, float *f);

inline ECharCategory unicode_get_category(i32 i);
inline i32 unicode_get_combining_class(i32 i);
inline bool unicode_is_mirrored(i32 i);

string unicode_get_category_name(const char * pszUtf8Char);
ECharCategory unicode_get_category(const char * pszUtf8Char);

i32 unicode_get_combining_class(const char * pszUtf8Char);
bool unicode_is_mirrored(const char * pszUtf8Char);

i32 unicode_size_of_tables();


inline  bool unicode_is_kanji(i64 i) { return i >= 0x4E00 && i <= 0x9FBF; }
inline  bool unicode_is_hiragana(i64 i) { return i >= 0x3040 && i <= 0x309F; }
inline  bool unicode_is_katakana(i64 i) { return i >= 0x30A0 && i <= 0x30FF; }
inline  bool unicode_is_japanese(i64 i) { return unicode_is_kanji(i) || unicode_is_hiragana(i) || unicode_is_katakana(i); }
inline  bool unicode_is_kanji(const char * pszUtf8) { return unicode_is_kanji(unicode_index(pszUtf8)); }
inline  bool unicode_is_hiragana(const char * pszUtf8) { return unicode_is_hiragana(unicode_index(pszUtf8)); }
inline  bool unicode_is_katakana(const char * pszUtf8) { return unicode_is_katakana(unicode_index(pszUtf8)); }
inline  bool unicode_is_japanese(const char * pszUtf8) { return unicode_is_japanese(unicode_index(pszUtf8)); }

void * unicode_char_bidi_names_non_usage_warning();

i32 unicode_ref_tables();
const char * unicode_get_category_name(i32 i);





template < typename POINTER >
inline ::string as_string(const ::acme::memory_allocate < POINTER > & memoryallocpointer)
{

   string str;

   str.assign(memoryallocpointer.m_p, memoryallocpointer.m_iSize);

   return str;

}


CLASS_DECL_ACME string demangle(const char * psz);


CLASS_DECL_ACME void copy(::string & str, const particle & particle);



CLASS_DECL_ACME string string_from_strdup(const ansichar * psz);


CLASS_DECL_ACME::string & copy(::string & str, const integral_byte & memsize);


CLASS_DECL_ACME void copy(::string & str, const particle & particle);



