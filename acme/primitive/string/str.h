#pragma once


struct end_of_line_and_next_line
{

   const char * end_of_line;
   const char * next_line;

};

inline  string consume_char(const ansichar * & p)
{
   auto len = ::utf8_len(p);
   string strChar(p, len);
   p+=len;
   return strChar;
}
inline  wd16string consume_char(const wd16char * & p)
{
   auto len = ::utf16_len(p);
   wd16string wd16strChar(p, len);
   p+=len;
   return wd16strChar;
}
inline  wd32string consume_char(const wd32char * & p)
{
   auto len = 1;
   wd32string wd32strChar(p, len);
   p+=len;
   return wd32strChar;
}


inline  ansichar * next_char(const ansichar * & p)
{
   auto len = ::utf8_len(p);
   p+=len;
   return (ansichar *)p;
}
inline  const wd16char * next_char(const wd16char * & p)
{
   auto len = ::utf16_len(p);
   p+=len;
   return (wd16char *)p;
}
inline  wd32char * next_char(const wd32char * & p)
{
   auto len = 1;
   p+=len;
   return(wd32char *) p;
}


class  str
{
public:


   enum enum_pad
   {

      e_pad_left,
      e_pad_right

   };


   enum enum_error
   {

      e_error_none,
      e_error_invalid_utf8_character

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
   strsize   find_ci(const ::string & strFind, const ansichar   * psz, strsize iStart = 0);
   strsize   find_ci(const ansichar   * pszFind, const ::string & str, strsize iStart = 0);
   strsize   find_ci(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);

   strsize   utf8_find(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);


   strsize   find_ci(const ansichar   * pszFind,const ::string & str,strsize iStart, strsize iLast);
   strsize   find_file_extension(const ::string & pszExtension,const ::string & str,strsize iStart = 0, strsize iLast = -1);

   strsize   find_ww(const ::string& pszFind, const ::string & psz, strsize iStart = 0);
   strsize   find_wwci(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   strsize   find_aww(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   strsize   find_awwci(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   string   has_char(const ::string & pszIfHasChar, const ::string & pszBefore = nullptr, const ::string & pszAfter = nullptr, const ::string & pszDoesnt = nullptr);
   bool   has_upper(const ::string & psz);
   bool   has_lower(const ::string & psz);
   bool   has_digit(const ::string & psz);
   void   calc_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_one_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_all_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool   has_all_v1(const ::string & psz);
   string   if_null(const ansichar * psz, const ::string & pszIfNull = nullptr);


   inline  const ansichar * __utf8_inc(const ansichar * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   //inline  enum_error      get_error() { return g_eerror; }
   //inline  void            set_error(enum_error eerror) { g_eerror = eerror; }
   //inline  void            clear_error() { g_eerror = e_error_none; }

      const ansichar *    utf8_inc(const ansichar * psz);
      const ansichar *    utf8_inc_slide(strsize * pslide, const ansichar * psz);
      const ansichar *    utf8_inc_copy_slide_back(strsize * pslideback, ansichar * pchDst, const ansichar * pchSrc);
      const ansichar *    utf8_inc_count(const ansichar * psz, strsize * piCount);

     string block(ansichar ch, i32 iSize);
     void fill(string & str, ansichar ch);

   inline  const ansichar * uni_inc(const ansichar * psz) { return utf8_inc(psz); }
   inline  const wd16char * uni_inc(const wd16char * psz) { return utf16_inc(psz); }
   inline  const wd32char * uni_inc(const wd32char * psz) { return utf32_inc(psz); }

      const ansichar * uni_dec(const ansichar * pszBeg, const ansichar * psz);
      const wd16char * uni_dec(const wd16char * pszBeg, const wd16char * psz);
      const wd32char * uni_dec(const wd32char * pszBeg, const wd32char * psz);


      string         get_utf8_char(const ansichar *psz);
      int            get_utf8_char_length(const ansichar *psz);
      string         get_utf8_char(const ansichar *psz, const ansichar * pszEnd);
      bool           get_utf8_char(string & strChar, const char * psz, const char * pszEnd);
      string         get_utf8_char(const ansichar * pszBeg, const ansichar *psz, strsize i);
      string         utf8_next_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
      string         utf8_previous_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
      string         uni_to_utf8(i64 ch);
      i32            uni_to_utf8_2_or_more(ansichar * dest, i32 ch);

      const ansichar * utf8_dec(::utf8_char * pchar, const ansichar * pszBeg, const ansichar * psz);
      const ansichar * utf8_dec( const ansichar* pszBeg, const ansichar* psz);




   
   inline  bool begins_ci_skip(const char*& psz, const char* pszPrefix);
   inline  struct ::end_of_line_and_next_line end_of_line_and_next_line(const char* psz);




      bool           trim_any_quotes(string & str);
      bool           paired_trim(string & str, ansichar ch);
      bool           trim(string & str);
      bool           _008Trim(string & str);




      string &       zero_pad(string & str, strsize iPad);
      string         zero_padded(const ::string & str, strsize iPad);
      i32            get_escaped_char(const ::string & str, strsize pos, strsize &retPos);
      bool           get_curly_content(const ::string & psz, string & str);
      bool           is_simple_natural(const ::string & psz, strsize iCount = -1);
      bool           is_natural(const ::string & psz);
      bool           is_integer(const ::string & psz);

     string          ansi_lower(const ::string & psz);
     string          ansi_upper(const ::string & psz);



   string   get_word(const ansichar * psz, const ansichar * pszSeparator, bool bWithSeparator = false, bool bEndIsSeparator = true);


     bool eats(const ansichar * & pszParse, const ansichar * psz);
     bool eats_ci(const ansichar * & szParse, const ansichar * psz);
     void consume(const ansichar * & pszParse, const ansichar * psz);
     void consume(const ansichar * & pszParse, const ansichar * psz, const ansichar * pszEnd);
     void consume(const ansichar * & pszParse, const ansichar * psz, ::count iLen, const ansichar * pszEnd);
     void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount = 1);
     u64 consume_natural(const ansichar * & pszParse, u64 uiMax = ((u64) -1), u64 uiMin = 0);
     u64 consume_natural(string & str, u64 uiMax = ((u64) -1), u64 uiMin = 0);
     string consume_hex(const ansichar * & pszParse);
     void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount, const ansichar * pszEnd);
     string consume_non_spaces(const ansichar * & pszParse, const ansichar * pszEnd);
     string consume_non_spaces(string & str);
     string consume_nc_name(const ansichar * & pszParse);
   //  string consume_quoted_value(const ansichar * & pszParse);
     void no_escape_consume_quoted_value(const ansichar * & pszParse, const ansichar * pszEnd, ansichar ** ppsz, strsize & iBufferSize);
     string no_escape_consume_quoted_value(const ansichar * & pszParse, const ansichar * pszEnd);
     void skip_quoted_value_ex2(const ansichar * & pszParse, const ansichar * pszEnd);
     string consume_quoted_value(const ansichar * & pszParse, const ansichar * pszEnd = nullptr);
     string consume_quoted_value_ex(const ansichar * & pszParse,const ansichar * pszEnd);
     void skip_quoted_value_ex(const ansichar * & pszParse, const ansichar * pszEnd);
     string consume_spaced_value(string & str);
     string consume_spaced_value(const ansichar * & pszParse);
     string consume_spaced_value(const ansichar * & pszParse, const ansichar * pszEnd);
     string consume_command_line_argument(string & str);
     string consume_command_line_argument(const ansichar * & pszParse);
     string consume_command_line_argument(const ansichar * & pszParse, const ansichar * pszEnd);
     bool begins_consume(const ansichar * & pszParse, const ::string & psz);

     bool xml_is_comment(const ::string & pszParse);
     string xml_consume_comment(const ansichar * & pszParse);

     string consume_c_quoted_value(const ansichar * & pszParse, const ansichar * pszEnd = nullptr);

     string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   //  void token(string & strToken, ::string & strSource, const ::string & pszSeparatorText, bool bWithSeparator = false);

     string line(string& str, bool bWithNewLine = false);

     string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, enum_pad epad);


   inline  strsize length(const ansichar * pansichar) { return ansi_length(pansichar); }
   inline  strsize length(const wd16char * pwd16char) { return wd16_length(pwd16char); }
   inline  strsize length(const wd32char * pwd32char) { return wd32_length(pwd32char); }


   template < typename TYPE >
   inline  TYPE from_string(const char * psz);


     bool simple_escaped(const ::string & str,strsize pos);






     bool utf8_check_is_valid(const string& string);

     string q_valid(string str);

   inline  ansichar * dup(const ::string & psz)
   {


      try
      {

         if (psz == nullptr)
         {

            return nullptr;

         }

         return ansi_dup(psz);

      }
      catch (...)
      {

      }

      return nullptr;

   }


     string signed_double(double d);

     string signed_int(int i);

     bool is_true(string str);


     inline  strsize utf8_dec_len(const ansichar * pszBeg, const ansichar* psz);

     inline  strsize utf8_inc_len(const ansichar * psz);

     inline  bool namespaced(const ansichar * psz, const ansichar * pszNamespace, const ansichar * pszSeparator = "::");



     void fix_eol(string & str);


#include "_str_to.h"
#include "_str_compare.h"
#include "_str_trait.h"
#include "_str_trait_ansi.h"
#include "_str_trait_wd16.h"
#include "_str_trait_wd32.h"




}; // class str











CLASS_DECL_ACME  string normalize_wildcard_criteria(const ::string & strPattern);


inline  string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


  string _002Underscore(string str);




inline    string string_from_strdup(const char * psz);

