#pragma once


class synchronization_lock;


template < typename TYPE_CHAR >
class single_char
{
public:

   TYPE_CHAR cha[8];

};


template < >
class single_char < ansichar >
{
public:

   ansichar cha[6];

};


template < >
class single_char < wd16char >
{
public:

   wd16char cha[2];

};


template < >
class single_char < wd32char >
{
public:

   wd32char cha[1];

};


class CLASS_DECL_ACME str
{
public:


   enum enum_pad
   {

      e_pad_left,
      e_pad_right

   };



#include "_str_ch.h"


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

   string   random_replace(::matter * pmatter, const string_array & straNew, const string_array & straOld, const ::string & psz);

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


   //inline  const ansichar * __utf8_inc(const ansichar * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   //const ansichar *    utf8_next_add_length(strsize * paddlength, const ansichar * psz);
   //const ansichar *    utf8_inc_copy_slide_back(strsize * pslideback, ansichar * pchDst, const ansichar * pchSrc);
   //const ansichar *    utf8_inc_count(const ansichar * psz, strsize * piCount);

   string block(ansichar ch, i32 iSize);
   void fill(string & str, ansichar ch);

   inline const ansichar * next(const ansichar * psz) { return unicode_next(psz); }
   inline const wd16char * next(const wd16char * psz) { return unicode_next(psz); }
   inline const wd32char * next(const wd32char * psz) { return unicode_next(psz); }

   inline ansichar * next(ansichar * psz) { return (ansichar *)next((const ansichar *)psz); }
   inline wd16char * next(wd16char * psz) { return (wd16char *)next((const wd16char *)psz); }
   inline wd32char * next(wd32char * psz) { return (wd32char *)next((const wd32char *)psz); }


   inline const ansichar * increment(const ansichar *& psz) { return psz = next(psz); }
   inline const wd16char * increment(const wd16char *& psz) { return psz = next(psz); }
   inline const wd32char * increment(const wd32char *& psz) { return psz = next(psz); }


   ansichar * increment(ansichar *& psz)
   {

      return (ansichar *)increment((const ansichar *&)psz);

   }


   wd16char * increment(wd16char *& psz)
   {

      return (wd16char *)increment((const wd16char *&)psz);

   }


   wd32char * increment(wd32char *& psz)
   {

      return (wd32char *)increment((const wd32char *&)psz);

   }


   const ::index prior_index(::index i, const ansichar * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
   const ::index prior_index(::index i, const wd16char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
   const ::index prior_index(::index i, const wd32char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }


   const ansichar * prior(const ansichar * psz, const ansichar * pszBeg) { return unicode_prior(psz, pszBeg); }
   const wd16char * prior(const wd16char * psz, const wd16char * pszBeg) { return unicode_prior(psz, pszBeg); }
   const wd32char * prior(const wd32char * psz, const wd32char * pszBeg) { return unicode_prior(psz, pszBeg); }


   ansichar * prior(ansichar * psz, const ansichar * pszBeg) { return (ansichar *)prior((const ansichar *&)psz, pszBeg); }
   wd16char * prior(wd16char * psz, const wd16char * pszBeg) { return (wd16char *)prior((const wd16char *&)psz, pszBeg); }
   wd32char * prior(wd32char * psz, const wd32char * pszBeg) { return (wd32char *)prior((const wd32char *&)psz, pszBeg); }


   const strsize decrement(strsize & i, const ansichar * pszBeg) { return i = prior_index(i, pszBeg); }
   const strsize decrement(strsize & i, const wd16char * pszBeg) { return i = prior_index(i, pszBeg); }
   const strsize decrement(strsize & i, const wd32char * pszBeg) { return i = prior_index(i, pszBeg); }


   const ansichar * decrement(const ansichar *& psz, const ansichar * pszBeg) { return psz = prior(psz, pszBeg); }
   const wd16char * decrement(const wd16char *& psz, const wd16char * pszBeg) { return psz = prior(psz, pszBeg); }
   const wd32char * decrement(const wd32char *& psz, const wd32char * pszBeg) { return psz = prior(psz, pszBeg); }


   ansichar * decrement(ansichar *& psz, const ansichar * pszBeg = nullptr)
   {

      return (ansichar *)decrement((const ansichar *&)psz, pszBeg);

   }


   wd16char * decrement(wd16char *& psz, const wd16char * pszBeg = nullptr)
   {

      return (wd16char *)decrement((const wd16char *&)psz, pszBeg);

   }


   wd32char * decrement(wd32char *& psz, const wd32char * pszBeg = nullptr)
   {

      return (wd32char *)decrement((const wd32char *&)psz, pszBeg);

   }


   string         get_utf8_char(const ansichar * psz);
   int            get_utf8_char_length(const ansichar * psz);
   string         get_utf8_char(const ansichar * psz, const ansichar * pszEnd);
   bool           get_utf8_char(string & strChar, const char *& psz, const char * pszEnd);
   string         get_utf8_char(const ansichar * pszBeg, const ansichar * psz, strsize i);
   string         utf8_next_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
   string         utf8_previous_char(const ansichar * pszBeg, const ansichar * psz, strsize i = 0);
   string         uni_to_utf8(i64 ch);
   i32            uni_to_utf8_2_or_more(ansichar * dest, i32 ch);


   //const ansichar * utf8_dec(const ::character & character, const ansichar * pszBeg, const ansichar * psz);
   const ansichar * utf8_dec(const ansichar * pszBeg, const ansichar * psz);


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
   bool           paired_trim(string & str, ansichar ch);
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


   bool eats(const ansichar *& pszParse, const ::string & strToEat);
   bool eats_ci(const ansichar *& szParse, const ::string & strToEat);
   void consume(const ansichar *& pszParse, const ::string & strToConsume);
   void consume(const ansichar *& pszParse, const ansichar * psz, const ansichar * pszEnd);
   void consume(const ansichar *& pszParse, const ansichar * psz, ::count iLen, const ansichar * pszEnd);
   void consume_spaces(const ansichar *& pszParse, ::count iMinimumCount = 1);
   u64 consume_natural(const ansichar *& pszParse, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   u64 consume_natural(string & str, u64 uiMax = ((u64)-1), u64 uiMin = 0);
   string consume_hex(const ansichar *& pszParse);
   void consume_spaces(const ansichar *& pszParse, ::count iMinimumCount, const ansichar * pszEnd);
   string consume_non_spaces(const ansichar *& pszParse, const ansichar * pszEnd);
   string consume_non_spaces(const ansichar *& psz);
   string consume_nc_name(const ansichar *& pszParse);
   //  string consume_quoted_value(const ansichar * & pszParse);
   void no_escape_consume_quoted_value(const ansichar *& pszParse, const ansichar * pszEnd, ansichar ** ppsz, strsize & iBufferSize);
   string no_escape_consume_quoted_value(const ansichar *& pszParse, const ansichar * pszEnd);
   void skip_quoted_value_ex2(const ansichar *& pszParse, const ansichar * pszEnd);
   string consume_quoted_value(const ansichar *& pszParse, const ansichar * pszEnd = nullptr);
   string consume_quoted_value_ex(const ansichar *& pszParse, const ansichar * pszEnd);
   void skip_quoted_value_ex(const ansichar *& pszParse, const ansichar * pszEnd);
   string consume_spaced_value(string & str);
   string consume_spaced_value(const ansichar *& pszParse);
   string consume_spaced_value(const ansichar *& pszParse, const ansichar * pszEnd);
   string consume_command_line_argument(string & str);
   string consume_command_line_argument(const ansichar *& pszParse);
   string consume_command_line_argument(const ansichar *& pszParse, const ansichar * pszEnd);
   bool begins_consume(const ansichar *& pszParse, const ::string & psz);

   bool xml_is_comment(const ::string & pszParse);
   string xml_consume_comment(const ansichar *& pszParse);

   string consume_c_quoted_value(const ansichar *& pszParse, const ansichar * pszEnd = nullptr);

   string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   //  void token(string & strToken, ::string & strSource, const ::string & pszSeparatorText, bool bWithSeparator = false);

   string line(string & str, bool bWithNewLine = false);

   string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, enum_pad epad);

   inline  strsize length(const ansichar * pansichar) { return ansi_length(pansichar); }
   inline  strsize length(const wd16char * pwd16char) { return wd16_length(pwd16char); }
   inline  strsize length(const wd32char * pwd32char) { return wd32_length(pwd32char); }


   template < typename TYPE >
   inline  TYPE from_string(const char * psz);


   bool simple_escaped(const ::string & str, strsize pos);






   bool utf8_check_is_valid(const string & string);

   string q_valid(string str);


   inline ansichar * dup(const ::string & str)
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


   //namespace str
   //{
   //string consume_quoted_value_ex(const char *& pszXml, const char * pszEnd);
   //}



   string signed_double(double d);

   string signed_int(int i);

   bool is_true(string str);


   inline  strsize utf8_dec_len(const ansichar * pszBeg, const ansichar * psz);

   inline  strsize utf8_inc_len(const ansichar * psz);

   inline  bool namespaced(const ansichar * psz, const ansichar * pszNamespace, const ansichar * pszSeparator = "::");



   void fix_eol(string & str);


#include "_str_to.h"
#include "_str_compare.h"
#include "_str_trait.h"
#include "_str_trait_ansi.h"
#include "_str_trait_wd16.h"
#include "_str_trait_wd32.h"


   void get_lines(::string_array & stra, ::string & str, const ::string & strPrefix, bool bFinal, ::synchronization_lock * psynchronizationlock = nullptr, ::file::file * pfileLines = nullptr);


}; // class str


CLASS_DECL_ACME  string normalize_wildcard_criteria(const ::string & strPattern);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


inline string string_from_strdup(const char * psz);




inline string __string(const ::e_display & edisplay) { return __string((::enum_display) edisplay); }
