#pragma once


#include "string.h"




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


   inline     bool trimmed_is_empty(const ::string & psz);


   template < typename CHAR_TYPE >
   inline  string_base < CHAR_TYPE > repeat(const CHAR_TYPE * psz, strsize c);

   //extern enum_error g_eerror;



   inline  i32 compare_ignore_case(const string & left, const string & right, size_t len = 0);
   inline  bool equal_ignore_case(const string & left, const string & right, size_t len = 0);


   void   increment_digit_letter(string & str);

   void   copy(string & str, const ::string & pcsz, i32 iCount);

   string   replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   string   replace_with_ci(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count   replace_with_ci_count(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count   utf8_replace_with(string & str, const ::string & pszNew, const ::string & pszOld, strsize iStart = 0);
   string   utf8_replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);

   inline  string find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with(pszNew, pszOld, psz, iStart);
   }
   inline  string find_replace_ci(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with_ci(pszNew, pszOld, psz, iStart);
   }
   inline  ::count find_replace_ci_count(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with_ci_count(pszNew, pszOld, psz, iStart);
   }
   inline  ::count utf8_find_replace(string & str, const ::string & pszOld, const ::string & pszNew, strsize iStart = 0)
   {
      return utf8_replace_with(str, pszNew, pszOld, iStart);
   }
   inline  string utf8_find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return utf8_replace_with(pszNew, pszOld, psz, iStart);
   }

   string   random_replace(::particle * pparticle, const string_array & straNew, const string_array & straOld, const ::string & psz);

   strsize   find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   strsize   find_ci(const ::string & strFind, const ::string & str, strsize iStart = 0);

   strsize   utf8_find(const ::string & strFind, const ::string & str, strsize iStart = 0);

   strsize   find_file_extension(const ::string & pszExtension, const ::string & str, strsize iStart = 0, strsize iLast = -1);

   strsize   find_ww(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize   find_wwci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize   find_aww(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize   find_awwci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   string   has_char(const ::string & strIfHasChar, const ::string & strBefore = nullptr, const ::string & strAfter = nullptr, const ::string & strDoesnt = nullptr);
   bool   has_upper(const ::string & str);
   bool   has_lower(const ::string & str);
   bool   has_digit(const ::string & str);
   void   calc_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_one_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_all_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_all_v1(const ::string & str);
   string   if_null(const ::string & str, const ::string & strIfNull = nullptr);


   //inline  const ::ansi_character * __utf8_inc(const ::ansi_character * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   //const ::ansi_character *    utf8_next_add_length(strsize * paddlength, const ::ansi_character * psz);
   //const ::ansi_character *    utf8_inc_copy_slide_back(strsize * pslideback, ::ansi_character * pchDst, const ::ansi_character * pchSrc);
   //const ::ansi_character *    utf8_inc_count(const ::ansi_character * psz, strsize * piCount);

   string block(::ansi_character ch, i32 iSize);
   void fill(string & str, ::ansi_character ch);




   inline  bool begins_ci_skip(const char *& psz, const char * pszPrefix);
   inline  struct ::end_of_line_and_next_line end_of_line_and_next_line(const char * psz);

   bool replace_prefix(::string & str, const char * pszPrefixReplacement, const char * pszPrefix);
   inline bool begins_replace(::string & str, const char * pszPrefixReplacement, const char * pszPrefix)
   {
      
      return replace_prefix(str, pszPrefixReplacement, pszPrefix);

   }


   bool replace_prefix_ci(::string & str, const char * pszPrefixReplacement, const char * pszPrefix);
   inline bool begins_replace_ci(::string & str, const char * pszPrefixReplacement, const char * pszPrefix)
   {

      return replace_prefix_ci(str, pszPrefixReplacement, pszPrefix);

   }


   bool           trim_any_quotes(string & str);
   bool           paired_trim(string & str, ::ansi_character ch);
   bool           trim(string & str);
   bool           _008Trim(string & str);




   string & zero_pad(string & str, strsize iPad);
   string         zero_padded(const ::string & str, strsize iPad);
   i32            get_escaped_char(const char * psz, strsize pos, strsize & retPos);
   bool           get_curly_content(const char * psz, string & str);
   bool           is_simple_natural(const char * psz, strsize iCount = -1);
   bool           is_natural(const ::string & str);
   bool           is_integer(const ::string & str);

   string          ansi_lower(const ::string & str);
   string          ansi_upper(const ::string & str);


   string   get_word(const ::string & str, const ::string & strSeparator, bool bWithSeparator = false, bool bEndIsSeparator = true);


   bool eats(const ::ansi_character *& pszParse, const ::string & strToEat);
   bool eats_ci(const ::ansi_character *& szParse, const ::string & strToEat);
   void consume(const ::ansi_character *& pszParse, const ::string & strToConsume);
   void consume(const ::ansi_character *& pszParse, const ::ansi_character * psz, const ::ansi_character * pszEnd);
   void consume(const ::ansi_character *& pszParse, const ::ansi_character * psz, ::count iLen, const ::ansi_character * pszEnd);
   void consume_spaces(const ::ansi_character *& pszParse, ::count iMinimumCount = 1);
   u64 consume_natural(const ::ansi_character *& pszParse, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   u64 consume_natural(string & str, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   string consume_hex(const ::ansi_character *& pszParse);
   void consume_spaces(const ::ansi_character *& pszParse, ::count iMinimumCount, const ::ansi_character * pszEnd);
   string consume_non_spaces(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   string consume_non_spaces(const ::ansi_character *& psz);
   string consume_nc_name(const ::ansi_character *& pszParse);
   //  string consume_quoted_value(const ::ansi_character * & pszParse);
   void no_escape_consume_quoted_value(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd, ::ansi_character ** ppsz, strsize & iBufferSize);
   string no_escape_consume_quoted_value(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   void skip_quoted_value_ex2(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   string consume_quoted_value(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd = nullptr);
   string consume_quoted_value_ex(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   void skip_quoted_value_ex(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   string consume_spaced_value(string & str);
   string consume_spaced_value(const ::ansi_character *& pszParse);
   string consume_spaced_value(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   string consume_command_line_argument(string & str);
   string consume_command_line_argument(const ::ansi_character *& pszParse);
   string consume_command_line_argument(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd);
   bool begins_consume(const ::ansi_character *& pszParse, const ::string & psz);

   bool xml_is_comment(const ::string & pszParse);
   string xml_consume_comment(const ::ansi_character *& pszParse);

   string consume_c_quoted_value(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd = nullptr);

   string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   //  void token(string & strToken, ::string & strSource, const ::string & pszSeparatorText, bool bWithSeparator = false);

   string line(string & str, bool bWithNewLine = false);

   string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, enum_pad epad);

   inline  strsize length(const ::ansi_character * pansichar) { return ansi_length(pansichar); }
   inline  strsize length(const ::wd16_character * pwd16char) { return wd16_length(pwd16char); }
   inline  strsize length(const ::wd32_character * pwd32char) { return wd32_length(pwd32char); }


   template < typename TYPE >
   inline  TYPE from_string(const char * psz);


   bool simple_escaped(const ::string & str, strsize pos);






   bool utf8_check_is_valid(const string & string);

   string q_valid(string str);


   inline ::ansi_character * dup(const ::string & str)
   {

      try
      {

         return ansi_dup(str);

      }
      catch (...)
      {

      }

      return nullptr;

   }



   string signed_double(double d);

   string signed_int(int i);

   bool is_true(string str);


   inline  strsize utf8_dec_len(const ::ansi_character * pszBeg, const ::ansi_character * psz);

   inline  strsize utf8_inc_len(const ::ansi_character * psz);

   inline  bool namespaced(const ::ansi_character * psz, const ::ansi_character * pszNamespace, const ::ansi_character * pszSeparator = "::");



   void fix_eol(string & str);


   bool to(i64 & i, const ::string & strParam);
   bool to(i32 & i, const ::string & strParam);
   bool to(u64 & u, const ::string & strParam);
   bool to(u32 & u, const ::string & strParam);


   bool to(i32 & i, i32 iBase, const ::string & strParam);
   bool to(i64 & i, int iBase, const ::string & strParam);
   bool to(u64 & u, i32 iBase, const ::string & strParam);
   bool to(u32 & u, i32 iBase, const ::string & strParam);


   iptr         to_iptr(const ::string & psz);
   i32          to_i32(const ::string & psz);
   u32          to_u32(const ::string & psz);


   i64           to_i64(const ::string & psz);
   u64           to_u64(const ::string & psz);



   inline   i32 to_with_fallback(const ::string & psz, i32 iDefault);
   inline   i64 to_with_fallback(const ::string & psz, i64 iDefault);
   inline   i32 to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase);
   inline   i64 to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase);



   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const ::string & str, const ::string & strPrefix);
   bool begins_ci_iws(const wstring & wstr, const wstring & wstrPrefix);

   bool  while_begins_with_chars_eat(string & str, const char * pcszChars);
   bool  while_begins_with_chars_eat_ci(string & str, const char * pcszChars);


   inline const ::ansi_character * windows_bbqbunc(const ansi_string &);
   inline const ::ansi_character * windows_bbqb(const ansi_string &);
   inline const ::ansi_character * windows_bb(const ansi_string &);


   inline const ::wide_character * windows_bbqbunc(const wide_string &);
   inline const ::wide_character * windows_bbqb(const wide_string &);
   inline const ::wide_character * windows_bb(const wide_string &);


   inline strsize unichar_count(const ::ansi_character * pstr);
   inline strsize unichar_count(const ::wd16_character * pstr);
   inline strsize unichar_count(const ::wd32_character * pstr);



   void get_lines(::string_array & stra, ::string & str, const ::string & strPrefix, bool bFinal, ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLines = nullptr);


}; // class str


CLASS_DECL_ACME  string normalize_wildcard_criteria(const ::string & strPattern);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


CLASS_DECL_ACME string string_from_strdup(const char * psz);




