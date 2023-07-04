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


   template < primitive_character CHAR_TYPE >
   static inline  string_base < const CHAR_TYPE * > repeat(const CHAR_TYPE * psz, strsize c);

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
   static inline  string case_insensitive_find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return case_insensitive_replace_with(pszNew, pszOld, psz, iStart);
   }
   static inline  ::count case_insensitive_find_replace_count(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
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


   // static inline const ::ansi_character * windows_bbqbunc(const ansi_string &);
   // static inline const ::ansi_character * windows_bbqb(const ansi_string &);
   // static inline const ::ansi_character * windows_bb(const ansi_string &);


   // static inline const ::wide_character * windows_bbqbunc(const wide_string &);
   // static inline const ::wide_character * windows_bbqb(const wide_string &);
   // static inline const ::wide_character * windows_bb(const wide_string &);


   static inline strsize unichar_count(const ::ansi_character * pstr);
   static inline strsize unichar_count(const ::wd16_character * pstr);
   static inline strsize unichar_count(const ::wd32_character * pstr);


   static void get_lines(::string & str, bool bFinal, const ::function < void(const ::scoped_string &) > & functionNewLine);


   static void get_lines(::string_array & stra, ::string & str, const ::string & strPrefix, bool bFinal, ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLines = nullptr);


}; // class str


CLASS_DECL_ACME  string normalize_wildcard_criteria(const ::string & strPattern);


CLASS_DECL_ACME string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


CLASS_DECL_ACME string string_from_strdup(const ::ansi_character * psz);

//
//
//template<typename ITERATOR_TYPE>
//auto string_range < ITERATOR_TYPE>::consume_quoted_value()
//{
//
//   return ::str::consume_quoted_value(*this);
//
//}



