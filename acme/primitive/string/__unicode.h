#pragma once

#if WCHAR_T_SIZE == 16

CLASS_DECL_ACME wstring wd32_to_wd16_str(const wd32char * pcwsz, strsize input_size = -1);

#endif

CLASS_DECL_ACME string wd16_to_ansi_str(const wd16char * pwsz, strsize srclen = -1);

CLASS_DECL_ACME string wd32_to_ansi_str(const wd32char * pwsz, strsize srclen = -1);


inline const ansichar * unicode_next(const ansichar * psz);
inline const wd16char * unicode_next(const wd16char * psz);
inline const wd32char * unicode_next(const wd32char * psz);

inline ansichar * unicode_next(ansichar * psz) { return (ansichar *)unicode_next((const ansichar *)psz); }
inline wd16char * unicode_next(wd16char * psz) { return (wd16char *)unicode_next((const wd16char *)psz); }
inline wd32char * unicode_next(wd32char * psz) { return (wd32char *)unicode_next((const wd32char *)psz); }

inline const ansichar * unicode_increment(const ansichar *& psz) { return psz = unicode_next(psz); }
inline const wd16char * unicode_increment(const wd16char *& psz) { return psz = unicode_next(psz); }
inline const wd32char * unicode_increment(const wd32char *& psz) { return psz = unicode_next(psz); }


inline ansichar * unicode_increment(ansichar *& psz) { return (ansichar *)unicode_increment((const ansichar *&)psz); }
inline wd16char * unicode_increment(wd16char *& psz) { return (wd16char *)unicode_increment((const wd16char *&)psz); }
inline wd32char * unicode_increment(wd32char *& psz) { return (wd32char *)unicode_increment((const wd32char *&)psz); }


const ansichar * unicode_prior(const ansichar * psz, const ansichar * pszBeg);
const wd16char * unicode_prior(const wd16char * psz, const wd16char * pszBeg);
const wd32char * unicode_prior(const wd32char * psz, const wd32char * pszBeg);


inline const ::index unicode_prior_index(::index i, const ansichar * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const wd16char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const wd32char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }


inline ansichar * unicode_prior(ansichar * psz, const ansichar * pszBeg) { return (ansichar *)unicode_prior((const ansichar *&)psz, pszBeg); }
inline wd16char * unicode_prior(wd16char * psz, const wd16char * pszBeg) { return (wd16char *)unicode_prior((const wd16char *&)psz, pszBeg); }
inline wd32char * unicode_prior(wd32char * psz, const wd32char * pszBeg) { return (wd32char *)unicode_prior((const wd32char *&)psz, pszBeg); }


inline const strsize unicode_decrement(strsize & i, const ansichar * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const wd16char * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const wd32char * pszBeg) { return i = unicode_prior_index(i, pszBeg); }


inline const ansichar * unicode_decrement(const ansichar *& psz, const ansichar * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const wd16char * unicode_decrement(const wd16char *& psz, const wd16char * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const wd32char * unicode_decrement(const wd32char *& psz, const wd32char * pszBeg) { return psz = unicode_prior(psz, pszBeg); }


inline ansichar * unicode_decrement(ansichar *& psz, const ansichar * pszBeg = nullptr)
{

   return (ansichar *)unicode_decrement((const ansichar *&)psz, pszBeg);

}


inline wd16char * unicode_decrement(wd16char *& psz, const wd16char * pszBeg = nullptr)
{

   return (wd16char *)unicode_decrement((const wd16char *&)psz, pszBeg);

}


inline wd32char * unicode_decrement(wd32char *& psz, const wd32char * pszBeg = nullptr)
{

   return (wd32char *)unicode_decrement((const wd32char *&)psz, pszBeg);

}


string         get_utf8_char(const ansichar * psz);
int            get_utf8_char_length(const ansichar * psz);
string         get_utf8_char(const ansichar * psz, const ansichar * pszEnd);
bool           get_utf8_char(string & strChar, const char *& psz, const char * pszEnd);
string         get_utf8_char(const ansichar * pszBeg, const ansichar * psz, strsize i);
string         utf8_next_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
string         utf8_previous_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
string         unicode_to_utf8(i64 ch);
i32            unicode_to_utf8_2_or_more(ansichar * dest, i32 ch);


//const ansichar * utf8_dec(const ::character & character, const ansichar * pszBeg, const ansichar * psz);
const ansichar * utf8_dec(const ansichar * pszBeg, const ansichar * psz);

inline i32 parse_unicode(const ansichar *& pszChar);
inline i32 parse_unicode(const wd16char * &pszChar);
inline i32 parse_unicode(const wd32char *& pszChar) { return *pszChar++; }

inline i32 __unicode_index(const ansichar *& input, strsize * psrclen);
inline i32 __unicode_index(const wd16char *& input, strsize * psrclen);
inline i32 __unicode_index(const wd32char *& input, strsize * psrclen);


// return Unicode Index and
// number of characters need to be consumed to parse a Unicode Character
inline i32 unicode_index_len(const ansichar * pszChar, i32 & len);
inline i32 unicode_index_len(const wd16char * pszChar, i32 & len);
inline i32 unicode_index_len(const wd32char * pszChar, i32 & len) { len = *pszChar != 0; return *pszChar; }


inline i32 unicode_index(const ansichar * pszChar) { ::i32 len = 0; return unicode_index_len(pszChar, len); }
inline i32 unicode_index(const wd16char * pszChar) { ::i32 len = 0; return unicode_index_len(pszChar, len); }
inline i32 unicode_index(const wd32char * pszChar) { ::i32 len = 0; return unicode_index_len(pszChar, len); }


inline i32 unicode_index(const ansichar *& pszChar, strsize * psrclen) { return ::__unicode_index(pszChar, psrclen); }
inline i32 unicode_index(const wd16char *& pszChar, strsize * psrclen) { return ::__unicode_index(pszChar, psrclen); }
inline i32 unicode_index(const wd32char *& pszChar, strsize * psrclen) { return ::__unicode_index(pszChar, psrclen); }


inline bool is_legal_unicode_index(i32 iUnicodeIndex);


CLASS_DECL_ACME ::i32 unicode_to_lower_case(::i32 i);
CLASS_DECL_ACME::i32 unicode_to_upper_case(::i32 i);


#define UNI_DECLARE_IS_FUNCTION(function) \
inline bool function(::i32 i); \
inline bool function(const ansichar * psz); \
inline bool function(const wd16char * psz); \
inline bool function(const wd32char * psz);

#define UNI_IMPLEMENT_IS_FUNCTION(function) \
inline bool function(const ansichar * psz) { return function(unicode_index(psz)); } \
inline bool function(const wd16char * psz) { return function(unicode_index(psz)); } \
inline bool function(const wd32char * psz) { return function(unicode_index(psz)); }


//inline bool unicode_is_lower_case(::i32 i);
//inline bool unicode_is_upper_case(::i32 i);
//inline bool unicode_is_title_case(::i32 i);
//inline bool unicode_is_letter(::i32 i);
//inline bool unicode_is_letter_or_digit(::i32 i);
//inline bool unicode_is_digit(i32 i);
//inline bool unicode_is_assigned(i32 i);
//inline bool unicode_is_space_char(i32 i);
//inline bool unicode_is_whitespace(i32 i);
//inline bool unicode_is_number(i32 i);
//inline bool unicode_is_mirrored(i32 i);


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





inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource, strsize srclen);


// template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource, strsize srclen);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource, strsize srclen);


//   template < typename TYPE_TARGET, typename TYPE_SOURCE >
//   inline strsize utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource)
//   {
//
//      throw ::interface_only();
//
//      return 0;
//
//   }


//template <  >
inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource);


//template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource);


//template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource);


//template <  >
inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource);


//template <  >
inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource);


//template <  >
inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource);


//template <  >
inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource);


//   template < typename TYPE_TARGET, typename TYPE_SOURCE >
//   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource, strsize srclen)
//   {
//
//      throw ::interface_only();
//
//   }


//   inline void utf_to_utf(::string & str, const wd16char * psource, strsize srclen)
//   {
//
//      char * psz = nullptr;
//
//      auto dstlen = utf_to_utf_length(psz, psource, srclen);
//
//      psz = str.get_string_buffer(dstlen);
//
//      utf_to_utf(psz, psource, srclen);
//
//      psz[dstlen]='\0';
//
//   }


//template <  >
inline void utf_to_utf(ansichar * ptarget, const ansichar * psource, strsize srclen);



//template <  >
inline void utf_to_utf(wd16char * ptarget, const wd16char * psource, strsize srclen);


//template <  >
inline void utf_to_utf(wd16char * ptarget, const wd32char * psource, strsize srclen);


//template <  >
inline void utf_to_utf(wd32char * ptarget, const wd32char * psource, strsize srclen);


//template <  >
inline void utf_to_utf(wd32char * ptarget, const wd16char * psource, strsize srclen);



//template <  >
inline void utf_to_utf(ansichar * ptarget, const wd16char * psource, strsize srclen);


//template <  >
inline void utf_to_utf(ansichar * ptarget, const wd32char * psource, strsize srclen);


//template <  >
inline void utf_to_utf(wd16char * ptarget, const ansichar * psource, strsize srclen);



//template <  >
inline void utf_to_utf(wd32char * ptarget, const ansichar * psource, strsize srclen);



//   template < typename TYPE_TARGET, typename TYPE_SOURCE >
//   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource)
//   {
//
//      throw ::interface_only();
//
//   }


//template <  >
inline void utf_to_utf(ansichar * ptarget, const ansichar * psource);


//template <  >
inline void utf_to_utf(wd16char * ptarget, const wd16char * psource);


//template <  >
inline void utf_to_utf(wd32char * ptarget, const wd16char * psource);


//template <  >
inline void utf_to_utf(wd32char * ptarget, const wd32char * psource);



//template <  >
inline void utf_to_utf(wd16char * ptarget, const wd32char * psource);



//template <  >
inline void utf_to_utf(ansichar * ptarget, const wd16char * psource);



//template <  >
inline void utf_to_utf(ansichar * ptarget, const wd32char * psource);


//template <  >
inline void utf_to_utf(wd16char * ptarget, const ansichar * psource);

//template <  >
inline void utf_to_utf(wd32char * ptarget, const ansichar * psource);



inline bool _str_safe_precmp(int & i, const ansichar * pszA, const ansichar * pszB)
{

   if(::is_null(pszA))
   {

      if(::is_null(pszB))
      {

         i = 0;

         return true;

      }
      else
      {

         i = 1;

         return true;

      }

   }
   else if(::is_null(pszB))
   {

      i = -1;

      return true;

   }

   return false;

}


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
inline strsize string_begins(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix);
template < typename TYPE_CHAR >
inline strsize string_ends(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix);
template < typename TYPE_CHAR >
inline strsize string_begins_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix);
template < typename TYPE_CHAR >
inline strsize string_ends_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix);


inline strsize string_begins(const ansichar * psz, const ansichar * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline strsize string_begins(const wd16char * psz, const wd16char * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline strsize string_begins(const wd32char * psz, const wd32char * pszPrefix)
{   return string_begins(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }


inline strsize string_ends(const ansichar * psz, const ansichar * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline strsize string_ends(const wd16char * psz, const wd16char * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline strsize string_ends(const wd32char * psz, const wd32char * pszSuffix)
{   return string_ends(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }


inline strsize string_begins_ci(const ansichar * psz, const ansichar * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline strsize string_begins_ci(const wd16char * psz, const wd16char * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }
inline strsize string_begins_ci(const wd32char * psz, const wd32char * pszPrefix)
{   return string_begins_ci(psz, string_safe_length(psz), pszPrefix, string_safe_length(pszPrefix)); }


inline strsize string_ends_ci(const ansichar * psz, const ansichar * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline strsize string_ends_ci(const wd16char * psz, const wd16char * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }
inline strsize string_ends_ci(const wd32char * psz, const wd32char * pszSuffix)
{   return string_ends_ci(psz, string_safe_length(psz), pszSuffix, string_safe_length(pszSuffix)); }


template < typename CHAR_TYPE >
bool string_eat_before(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);


template < typename CHAR_TYPE >
bool string_eat_before_let_separator(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound);



//inline void string_assign(ansistring & t, const ansichar * psz)
//inline void string_assign(ansistring & t, const widechar * psz)
//inline void string_assign(ansistring & t, const string * pstr)
//inline void string_assign(ansistring & t, const wstring * pwstr);
//
//inline void string_bassign(string & t, const u8 * psz, strsize nsize)
