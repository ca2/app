#pragma once


//#include "string.h"




struct end_of_line_and_next_line
{

   const char * end_of_line;
   const char * next_line;

};



template < typename TYPE_CHAR >
class single_char
{
public:

   TYPE_CHAR cha[8];

};


template < >
class single_char < ::ansi_character >
{
public:

   ::ansi_character cha[6];

};


template < >
class single_char < ::wd16_character >
{
public:

   ::wd16_character cha[2];

};


template < >
class single_char < ::wd32_character >
{
public:

   ::wd32_character cha[1];

};


class CLASS_DECL_ACME str
{
public:


   enum enum_pad
   {

      e_pad_left,
      e_pad_right

   };



///#include "_____str_ch.h"



   //inline  i32 compare_ignore_case(const ::string & left, const ::string & right, size_t len = 0);
   //inline  bool equal_ignore_case(const ::string & left, const ::string & right, size_t len = 0);


   static inline     bool trimmed_is_empty(const ::scoped_string & scopedstr);


   template < typename CHAR_TYPE >
   static inline  string_base < CHAR_TYPE > repeat(const CHAR_TYPE * psz, strsize c);

   //extern enum_error g_eerror;



   static inline  i32 compare_ignore_case(const string & left, const string & right, size_t len = 0);
   static inline  bool equal_ignore_case(const string & left, const string & right, size_t len = 0);


   static void   increment_digit_letter(string & str);

   static void   copy(string & str, const ::string & pcsz, i32 iCount);

   static string   replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   static string   case_insensitive_replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   static ::count   replace_with_ci_count(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   static ::count   utf8_replace_with(string & str, const ::string & pszNew, const ::string & pszOld, strsize iStart = 0);
   static string   utf8_replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);

   static inline  string find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with(pszNew, pszOld, psz, iStart);
   }
   static inline  string find_replace_ci(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return case_insensitive_replace_with(pszNew, pszOld, psz, iStart);
   }
   static inline  ::count find_replace_ci_count(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with_ci_count(pszNew, pszOld, psz, iStart);
   }
   static inline  ::count utf8_find_replace(string & str, const ::string & pszOld, const ::string & pszNew, strsize iStart = 0)
   {
      return utf8_replace_with(str, pszNew, pszOld, iStart);
   }
   static inline  string utf8_find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return utf8_replace_with(pszNew, pszOld, psz, iStart);
   }

   static string   random_replace(::particle * pparticle, const string_array & straNew, const string_array & straOld, const ::string & psz);

   static strsize   find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   static strsize   case_insensitive_find(const ::string & strFind, const ::string & str, strsize iStart = 0);

   static strsize   utf8_find(const ::string & strFind, const ::string & str, strsize iStart = 0);

   static strsize   find_file_extension(const ::string & pszExtension, const ::string & str, strsize iStart = 0, strsize iLast = -1);

   static strsize   find_ww(const ::string & strFind, const ::string & str, strsize iStart = 0);
   static strsize   find_wwci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   static strsize   find_aww(const ::string & strFind, const ::string & str, strsize iStart = 0);
   static strsize   find_awwci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   static string   has_char(const ::string & strIfHasChar, const ::string & strBefore = nullptr, const ::string & strAfter = nullptr, const ::string & strDoesnt = nullptr);
   static bool   has_upper(const ::string & str);
   static bool   has_lower(const ::string & str);
   static bool   has_digit(const ::string & str);
   static void   calc_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   static bool   has_one_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   static bool   has_all_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   static bool   has_all_v1(const ::string & str);
   static string   if_null(const ::string & str, const ::string & strIfNull = nullptr);


   //inline  const ::ansi_character * __utf8_inc(const ::ansi_character * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   //const ::ansi_character *    utf8_next_add_length(strsize * paddlength, const ::ansi_character * psz);
   //const ::ansi_character *    utf8_inc_copy_slide_back(strsize * pslideback, ::ansi_character * pchDst, const ::ansi_character * pchSrc);
   //const ::ansi_character *    utf8_inc_count(const ::ansi_character * psz, strsize * piCount);

   static string block(::ansi_character ch, i32 iSize);
   static void fill(string & str, ::ansi_character ch);




   static inline  bool begins_ci_skip(const char *& psz, const ::scoped_string & scopedstrPrefix);
   static inline  struct ::end_of_line_and_next_line end_of_line_and_next_line(const ::scoped_string & scopedstr);

//   bool replace_prefix(::string & str, const ::scoped_string & scopedstrPrefixReplacement, const ::scoped_string & scopedstrPrefix);
//   inline bool begins_replace(::string & str, const ::scoped_string & scopedstrPrefixReplacement, const ::scoped_string & scopedstrPrefix)
//   {
//
//      return replace_prefix(str, scopedstrPrefixReplacement, scopedstrPrefix);
//
//   }
//
//
//   bool replace_prefix_ci(::string & str, const ::scoped_string & scopedstrPrefixReplacement, const ::scoped_string & scopedstrPrefix);
//   inline bool begins_replace_ci(::string & str, const ::scoped_string & scopedstrPrefixReplacement, const ::scoped_string & scopedstrPrefix)
//   {
//
//      return replace_prefix_ci(str, scopedstrPrefixReplacement, scopedstrPrefix);
//
//   }


   static bool           trim_any_quotes(string & str);
   static bool           paired_trim(string & str, ::ansi_character ch);
   static bool           trim(string & str);
   static bool           _008Trim(string & str);




   static string & zero_pad(string & str, strsize iPad);
   static string         zero_padded(const ::string & str, strsize iPad);
   static i32            get_escaped_char(const ::ansi_character * psz, strsize pos, strsize & retPos);
   static bool           get_curly_content(const ::ansi_character * psz, string & str);
   static bool           is_simple_natural(const ::ansi_character * psz, strsize iCount = -1);
   static bool           is_natural(const ::string & str);
   static bool           is_integer(const ::string & str);

   static string          ansi_lower(const ::string & str);
   static string          ansi_upper(const ::string & str);


   static string   get_word(const ::string & str, const ::string & strSeparator, bool bWithSeparator = false, bool bEndIsSeparator = true);


   static bool begins_consume(::const_ansi_range & range, const ::scoped_string & scopedstr);
   static bool begins_consume(::const_ansi_range & range, ansi_character ansich) {return (*range.m_begin == ansich)?(range.m_begin++, true): false;}
   static bool begins_consume(::ansi_character & characterReturn, ::const_ansi_range & range, ansi_character ansich) {return (*range.m_begin == ansich)?(characterReturn = ansich, range.m_begin++, true): false;}
   static bool case_insensitive_begins_consume(::const_ansi_range & range, const ::scoped_string & scopedstr);
   static void consume(::const_ansi_range & range, const ::ansi_character * pszToConsume);
   //static void consume(::const_ansi_range & range, const ::ansi_character * psz);
   static void consume(::const_ansi_range & range, const ::scoped_string & scopedstr);
   static void consume_spaces(::const_ansi_range & range, ::count iMinimumCount = 1);
   static u64 consume_natural(::const_ansi_range & range, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   static u64 consume_natural(string & str, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   static string consume_hex(::const_ansi_range & range);
   //void consume_spaces(::const_ansi_range & range, ::count iMinimumCount);
   static string consume_non_spaces(::const_ansi_range & range);
   //string consume_non_spaces(::const_ansi_range & range);
   static string consume_nc_name(::const_ansi_range & range);
   //  string consume_quoted_value(const ::ansi_character * & pszParse);
   //static void no_escape_consume_quoted_value(::const_ansi_range & range, ::ansi_character ** ppsz, strsize & iBufferSize);
   static string no_escape_consume_quoted_value(::const_ansi_range & range);
   static void no_escape_skip_quoted_value(::const_ansi_range & range);
   static string consume_quoted_value(::const_ansi_range & range);
   static string consume_quoted_value_ex(::const_ansi_range & range);
   static void skip_quoted_value_ex(::const_ansi_range & range);
   //static string consume_spaced_value(string & str);
   //string consume_spaced_value(const ::ansi_character *& pszParse);
   static string consume_spaced_value(::const_ansi_range & range);
   //static string consume_command_line_argument(string & str);
   //string consume_command_line_argument(const ::ansi_character *& pszParse);
   static string consume_command_line_argument(::const_ansi_range & range);
   static void consume_until_any_character_in(::const_ansi_range & range, const ::scoped_string & scopedstr);
   //static bool begins_consume(::const_ansi_range & range, const ::string & psz);

   static bool xml_is_comment(const ::string & pszParse);
   static string xml_consume_comment(::const_ansi_range & range);

   static string consume_c_quoted_value(::const_ansi_range & range);

   static string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   //  void token(string & strToken, ::string & strSource, const ::string & pszSeparatorText, bool bWithSeparator = false);

   static string line(string & str, bool bWithNewLine = false);

   static string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, enum_pad epad);

   static inline  strsize length(const ::ansi_character * pansichar) { return ansi_length(pansichar); }
   static inline  strsize length(const ::wd16_character * pwd16char) { return wd16_length(pwd16char); }
   static inline  strsize length(const ::wd32_character * pwd32char) { return wd32_length(pwd32char); }


   template < typename TYPE >
   static inline  TYPE from_string(const ::ansi_character * psz);


   static bool simple_escaped(const ::string & str, strsize pos);






   static bool utf8_check_is_valid(const string & string);

   static string q_valid(string str);


   static inline ::ansi_character * dup(const ::ansi_character * psz)
   {

      try
      {

         return ansi_dup(psz);

      }
      catch (...)
      {

      }

      return nullptr;

   }



   static string signed_double(double d);

   static string signed_int(int i);

   static bool is_true(string str);


   static inline  strsize utf8_dec_len(const ::ansi_character * pszBeg, const ::ansi_character * psz);

   static inline  strsize utf8_inc_len(const ::ansi_character * psz);

   static inline  bool namespaced(const ::ansi_character * psz, const ::ansi_character * pszNamespace, const ::ansi_character * pszSeparator = "::");



   static void fix_eol(string & str);


   static bool to(i64 & i, const ::string & strParam);
   static bool to(i32 & i, const ::string & strParam);
   static bool to(u64 & u, const ::string & strParam);
   static bool to(u32 & u, const ::string & strParam);


   static bool to(i32 & i, i32 iBase, const ::string & strParam);
   static bool to(i64 & i, int iBase, const ::string & strParam);
   static bool to(u64 & u, i32 iBase, const ::string & strParam);
   static bool to(u32 & u, i32 iBase, const ::string & strParam);


   static iptr         to_iptr(const ::string & psz);
   static i32          to_i32(const ::string & psz);
   static u32          to_u32(const ::scoped_string & scopedstr);


   static i64           to_i64(const ::string & psz);
   static u64           to_u64(const ::string & psz);



   static inline   i32 to_with_fallback(const ::string & psz, i32 iDefault);
   static inline   i64 to_with_fallback(const ::string & psz, i64 iDefault);
   static inline   i32 to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase);
   static inline   i64 to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase);



   // case insensitive, ignore white space - only in searched string
   static bool begins_ci_iws(const ::string & str, const ::string & strPrefix);
   static bool begins_ci_iws(const wstring & wstr, const wstring & wstrPrefix);

   //bool  while_begins_with_chars_eat(string & str, const ::scoped_string & scopedstrChars);
   //bool  while_begins_with_chars_eat_ci(string & str, const ::scoped_string & scopedstrChars);


   static inline const ::ansi_character * windows_bbqbunc(const ansi_string &);
   static inline const ::ansi_character * windows_bbqb(const ansi_string &);
   static inline const ::ansi_character * windows_bb(const ansi_string &);


   static inline const ::wide_character * windows_bbqbunc(const wide_string &);
   static inline const ::wide_character * windows_bbqb(const wide_string &);
   static inline const ::wide_character * windows_bb(const wide_string &);


   static inline strsize unichar_count(const ::ansi_character * pstr);
   static inline strsize unichar_count(const ::wd16_character * pstr);
   static inline strsize unichar_count(const ::wd32_character * pstr);



   static void get_lines(::string_array & stra, ::string & str, const ::string & strPrefix, bool bFinal, ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLines = nullptr);

   //========================================================
// Name   : _tcsechr
// Desc   : similar with strchr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
   static void escape_find_character(::const_ansi_range & range, i32 ch, i32 escape);
   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with ansi_scan with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   static void escape_find_any_character_in(::const_ansi_range & range, const char * chset, i32 escape);

   //========================================================
// Name   : _tcsenicmp
// Desc   : similar with ansi_count_compare_ci with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
   static ::std::strong_ordering escape_case_insensitive_count_order(::const_ansi_range & range, const ::const_ansi_range & rangeCompare, i32 escape);

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   static void escape_case_insensitive_find(::const_ansi_range & range, const ::const_ansi_range & rangeFind, i32 escape);
//========================================================
    // Name   : _tcsecpy
    // Desc   : similar with _tcscpy with escape process
    // Param  : escape - will be escape character
    // Return :
    //--------------------------------------------------------
    // Coder    Date                      Desc
    // bro      2002-10-29
    //========================================================
   static void escape_copy(::ansi_range & rangeTarget, char escape, const ::const_ansi_range & rangeSource);


}; // class str


CLASS_DECL_ACME  string normalize_wildcard_criteria(const ::string & strPattern);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


CLASS_DECL_ACME string string_from_strdup(const ::ansi_character * psz);




