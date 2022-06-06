#pragma once


class ::payload;
class atom;
//class string_format;


namespace calculator
{


   class value;


} // namespace calculator


namespace acme
{


   class property;

}


inline int trailingBytesForUTF8(char ch);

#ifdef __APPLE__
#undef err_none
#endif




///
/// \author Camilo Sasuke Tsumanuma
///
namespace str
{



   enum e_pad
   {
      pad_left,
      pad_right
   };

   enum e_err
   {
      err_none,
      err_invalid_utf8_character
   };


   CLASS_DECL_ACME extern e_err g_eerr;


   void CLASS_DECL_ACME increment_digit_letter(string & str);
   i32  CLASS_DECL_ACME compare(const ::string & psz1, const ::string & psz2);
   i32  CLASS_DECL_ACME compare_ci(const ::string & psz1, const ::string & psz2);
   bool CLASS_DECL_ACME equals(const ::string & psz1, const ::string & psz2);
   bool CLASS_DECL_ACME equals_ci(const ::string & psz1, const ::string & psz2);
   string CLASS_DECL_ACME equals_get(const ::string & psz1, const ::string & psz2, const ::string & pszGetOnEqual, const ::string & pszGetOnDifferent = nullptr);
   string CLASS_DECL_ACME equals_ci_get(const ::string & psz1, const ::string & psz2, const ::string & pszGetOnEqual, const ::string & pszGetOnDifferent = nullptr);

   inline bool begins(const ::string & psz,string & strFed, const ::string & strPrefix);
   inline bool begins(const ::string & str,string & strFed,const ::string & strPrefix);
   inline bool begins(const atom & atom,string & strFed,const ::string & strPrefix);

   inline bool begins(const ::string & psz, const ::string & strPrefix);
   inline bool begins(const ::string & str, const ::string & strPrefix);
   inline bool begins(const atom & atom, const ::string & strPrefix);
   inline bool begins_with(const ::string & psz, const ::string & strPrefix);
   inline bool begins_with(const ::string & str, const ::string & strPrefix);


   void CLASS_DECL_ACME begin(wstring & wstr, const unichar * pcszPrefix);


   bool CLASS_DECL_ACME begins(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins(const wstring & str, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_with(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_with(const wstring & str, const unichar * pcszPrefix);



   bool CLASS_DECL_ACME begins_ci(const ::string & pcsz, const ::string & lpcszPrefix);

   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACME begins_ci_iws(const ::string & psz, const ::string & pcszPrefix);

   bool CLASS_DECL_ACME begins_ci_iws(const ::string & str, const ::string & pcszPrefix);



   bool CLASS_DECL_ACME begins_ci(const unichar * pcsz, const unichar * lpcszPrefix);

   bool CLASS_DECL_ACME begins_ci(const wstring & wstr, const unichar * pcszPrefix);

   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACME begins_ci_iws(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_ci_iws(const wstring & str, const unichar * pcszPrefix);



   bool CLASS_DECL_ACME eat_before(string & strBefore,const string & strSeparator, string & str, bool bEatEverythingIfNotFound = false);
   bool CLASS_DECL_ACME eat_before_let_separator(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound = false);


   inline bool begins_eat(string & str, const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(string & str, const ::string & pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(string & str, const ::string & pcszPrefix, const ::string & pszSeparator); // case insensitive

   inline bool begins_eat(::payload & payload,const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(::payload & payload, const ::string & pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(::payload & payload, const ::string & pcszPrefix, const ::string & pszSeparator); // case insensitive

   inline bool begins_eat(property & property, const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(property & property, const ::string & pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(property & property, const ::string & pcszPrefix, const ::string & pszSeparator); // case insensitive

   bool CLASS_DECL_ACME while_begins_with_chars_eat(string & str, const ::string & pcszChars);

   bool CLASS_DECL_ACME while_begins_with_chars_eat_ci(string & str, const ::string & pcszChars); // case insensitive

   bool CLASS_DECL_ACME ends(const ::string & pcsz, const ::string & lpcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const ::string & pcsz, const ::string & lpcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const ::string & str, const ::string & pcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const ::payload & payload, const ::string & pcszSuffix);

   bool CLASS_DECL_ACME ends_eat(string & str, const ::string & pcszSuffix);

   bool CLASS_DECL_ACME ends_eat_ci(string & str, const ::string & pcszSuffix);

   void CLASS_DECL_ACME copy(string & str, const ::string & pcsz, i32 iCount);

   string CLASS_DECL_ACME replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   string CLASS_DECL_ACME replace_with_ci(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME replace_with_ci_count(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME utf8_replace_with(string & str, const ::string & pszNew, const ::string & pszOld, strsize iStart = 0);
   string CLASS_DECL_ACME utf8_replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);

   string CLASS_DECL_ACME random_replace(::matter * pobject, const string_array & straNew, const string_array & straOld, const ::string & psz);

   strsize CLASS_DECL_ACME find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const char   * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const char   * pszFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const char   * pszFind, const char   * psz, strsize iStart = 0);

   strsize CLASS_DECL_ACME utf8_find(const char   * pszFind, const char   * psz, strsize iStart = 0);


   strsize CLASS_DECL_ACME find_ci(const char   * pszFind,const ::string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_ACME find_file_extension(const ::string & pszExtension,const ::string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_ACME find_ww(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_wwci(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_aww(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_awwci(const ::string & pszFind, const ::string & psz, strsize iStart = 0);
   string CLASS_DECL_ACME has_char(const ::string & pszIfHasChar, const ::string & pszBefore = nullptr, const ::string & pszAfter = nullptr, const ::string & pszDoesnt = nullptr);
   bool CLASS_DECL_ACME has_upper(const ::string & psz);
   bool CLASS_DECL_ACME has_lower(const ::string & psz);
   bool CLASS_DECL_ACME has_digit(const ::string & psz);
   void CLASS_DECL_ACME calc_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_one_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const ::string & psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const ::string & psz);
   string CLASS_DECL_ACME if_null(const ::string & psz, const ::string & pszIfNull = nullptr);


   FORCEINLINE  const ::string & __utf8_inc(const ::string & psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   inline e_err           err() { return g_eerr; }
   inline void            set_err(e_err eerr) { g_eerr = eerr; }
   inline void            clear_err() { g_eerr = err_none; }

   CLASS_DECL_ACME  const ::string &   utf8_inc(const ::string & psz);
   CLASS_DECL_ACME  const ::string &   utf8_inc_slide(strsize * pslide, const ::string & psz);
   CLASS_DECL_ACME  const ::string &   utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const ::string & pchSrc);


   CLASS_DECL_ACME string block(char ch, i32 iSize);
   CLASS_DECL_ACME void fill(string & str, char ch);


   CLASS_DECL_ACME  const ::string &   utf8_dec(const ::string & pszBeg, const ::string & psz);
   CLASS_DECL_ACME  string         get_utf8_char(const ansichar *psz);
   CLASS_DECL_ACME  int            get_utf8_char_length(const char *psz);
   CLASS_DECL_ACME  string         get_utf8_char(const char *psz, const ::string & pszEnd);
   CLASS_DECL_ACME  bool           get_utf8_char(string & strChar, const ::string & & psz, const ::string & pszEnd);
   CLASS_DECL_ACME  string         get_utf8_char(const ::string & pszBeg, const char *psz, strsize i);
   CLASS_DECL_ACME  string         utf8_next_char(const ::string & pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACME  string         utf8_previous_char(const ::string & pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACME  string         uni_to_utf8(i64 ch);
   CLASS_DECL_ACME  i32 uni_to_utf8_2_or_more(char * dest, i32 ch);

   CLASS_DECL_ACME  const ::string &   utf8_dec(::str::utf8_char * pchar, const ::string & pszBeg, const ::string & psz);


   CLASS_DECL_ACME  bool           to(i32 & i, const ::string & psz);
   CLASS_DECL_ACME  bool           to(i64 & i, const ::string & psz);
   CLASS_DECL_ACME  bool           to(i32 & i, i32 iBase, const ::string & psz);
   CLASS_DECL_ACME  bool           to(i64 & i, i32 iBase, const ::string & psz);
   CLASS_DECL_ACME  bool           to(u32 & i, const ::string & psz);
   CLASS_DECL_ACME  bool           to(u64 & i, const ::string & psz);
   CLASS_DECL_ACME  bool           to(u32 & i, i32 iBase, const ::string & psz);
   CLASS_DECL_ACME  bool           to(u64 & i, i32 iBase, const ::string & psz);

   CLASS_DECL_ACME  bool           trim_any_quotes(string & str);
   CLASS_DECL_ACME  bool           paired_trim(string & str, char ch);
   CLASS_DECL_ACME  bool           trim(string & str);
   CLASS_DECL_ACME  bool           _008Trim(string & str);


   CLASS_DECL_ACME  iptr        to_iptr(const ::string & psz);
   CLASS_DECL_ACME  i32            to_i32(const ::string & psz);
   CLASS_DECL_ACME  u32   to_u32(const ::string & psz);


   /** C++ Sockets Library \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/

   //CLASS_DECL_ACME string l2string(long l); // please use itoa
   //CLASS_DECL_ACME string bigint2string(u64 l); // please use itoa
   CLASS_DECL_ACME i64         to_i64(const ::string & str) ;
   CLASS_DECL_ACME i64         to_i64(const ::string & psz) ;
   CLASS_DECL_ACME u64        to_u64(const ::string & str) ;
   CLASS_DECL_ACME u64        to_u64(const ::string & psz) ;

   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/



   inline CLASS_DECL_ACME i32 to_with_fallback(const ::string & psz, i32 iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ::string & psz, i64 iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i32 to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase) { to(iDefault, iBase, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase) { to(iDefault, iBase, psz); return iDefault; }


   //inline CLASS_DECL_ACME string   i64toa(i64 i);

   //CLASS_DECL_ACME  string         ansi_zero_pad(const ::string & strSrc,int iPad);
   CLASS_DECL_ACME  i32        get_escaped_char(const ::string & str, strsize pos, strsize &retPos);
   CLASS_DECL_ACME  bool           get_curly_content(const ::string & psz, string & str);
   CLASS_DECL_ACME  bool           is_simple_natural(const ::string & psz, strsize iCount = -1);
   CLASS_DECL_ACME  bool           is_natural(const ::string & psz);
   CLASS_DECL_ACME  bool           is_integer(const ::string & psz);

   CLASS_DECL_ACME string          ansi_lower(const ::string & psz);
   CLASS_DECL_ACME string          ansi_upper(const ::string & psz);


//   string CLASS_DECL_ACME get_window_text_timeout(::windowing::window * pwindow, ::duration tickTimeout = 1000);

   string CLASS_DECL_ACME get_word(
   const ::string & psz,
   const ::string & pszSeparator,
   bool bWithSeparator = false,
   // if end is separator, return entire string if separator is not found
   // otherwise, return is_empty
   bool bEndIsSeparator = true);

   CLASS_DECL_ACME bool eats(const ::string & & pszParse, const ::string & psz);
   CLASS_DECL_ACME bool eats_ci(const ::string & & pszParse, const ::string & psz);
   CLASS_DECL_ACME void consume(const ::string & & pszParse, const ::string & psz);
   CLASS_DECL_ACME void consume(const ::string & & pszParse, const ::string & psz, const ::string & pszEnd);
   CLASS_DECL_ACME void consume(const ::string & & pszParse, const ::string & psz, ::count iLen, const ::string & pszEnd);
   CLASS_DECL_ACME void consume_spaces(const ::string & & pszParse, ::count iMinimumCount = 1);
   CLASS_DECL_ACME u64 consume_natural(const ::string & & pszParse, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME u64 consume_natural(string & str, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME string consume_hex(const ::string & & pszParse);
   CLASS_DECL_ACME void consume_spaces(const ::string & & pszParse, ::count iMinimumCount, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(string & str);
   CLASS_DECL_ACME string consume_nc_name(const ::string & & pszParse);
   //CLASS_DECL_ACME string consume_quoted_value(const ::string & & pszParse);
   CLASS_DECL_ACME void consume_quoted_value_ex2(const ::string & & pszParse, const ::string & pszEnd, char ** ppsz, strsize & iBufferSize);
   CLASS_DECL_ACME void skip_quoted_value_ex2(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_quoted_value(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_quoted_value_ex(const ::string & & pszParse,const ::string & pszEnd);
   CLASS_DECL_ACME void skip_quoted_value_ex(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_spaced_value(string & str);
   CLASS_DECL_ACME string consume_spaced_value(const ::string & & pszParse);
   CLASS_DECL_ACME string consume_spaced_value(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_command_line_argument(string & str);
   CLASS_DECL_ACME string consume_command_line_argument(const ::string & & pszParse);
   CLASS_DECL_ACME string consume_command_line_argument(const ::string & & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME bool begins_consume(const ::string & & pszParse, const ::string & psz);

   CLASS_DECL_ACME bool xml_is_comment(const ::string & pszParse);
   CLASS_DECL_ACME string xml_consume_comment(const ::string & & pszParse);

   CLASS_DECL_ACME string consume_c_quoted_value(const ::string & & pszParse);

   CLASS_DECL_ACME string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   CLASS_DECL_ACME string line(string& str, bool bWithNewLine = false);

   CLASS_DECL_ACME string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, e_pad epad);

   inline ::count ilen(const ::string & psz) { return (count) strlen(psz); }
   inline i64 len(const ::string & psz) { return (i64) strlen(psz); }


   template < typename TYPE >
   inline TYPE string_from_string(const ::string & psz);

//   CLASS_DECL_ACME void format(string_format * pformat, char const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, byte const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, i16 const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, u16 const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, i32 const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, u32 const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, i64 const & i);
//
//#ifdef RASPBIAN
//
//   CLASS_DECL_ACME void format(string_format * pformat, long unsigned int const & u);
//
//#endif
//
//#ifdef ANDROID
//
//   CLASS_DECL_ACME void format(string_format * pformat, long int const & i);
//
//#endif
//
//   CLASS_DECL_ACME void format(string_format * pformat, u64 const & i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, double const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, float const &  i);
//
//   CLASS_DECL_ACME void format(string_format * pformat, void * const & point);
//
//   CLASS_DECL_ACME void format(string_format * pformat, const void * const & point);
//
//   CLASS_DECL_ACME void format(string_format * pformat, u8 * const & point);
//
//   CLASS_DECL_ACME void format(string_format * pformat, const ::string & const & psz);
//
//   CLASS_DECL_ACME void format(string_format * pformat, const ::string & str);
//
//   CLASS_DECL_ACME void format(string_format * pformat, const lparam & lparam);

//
//   CLASS_DECL_ACME void format(string_format * pformat, const ::payload & payload);
//
//   CLASS_DECL_ACME void format(string_format * pformat, const property & property);

//
//#ifdef LINUX
//
//   inline CLASS_DECL_ACME void format(string_format * pformat,const pthread & point)
//   {
//
//      ::str::format(pformat, (u64) point);
//
//   }
//
//#endif

   //template < typename TYPE >
   //void format_type(string_format * pformat,const TYPE & t)
   //{

   //   ::str::format(pformat, t);

   //}

   CLASS_DECL_ACME bool simple_escaped(const ::string & str,strsize pos);

//#ifdef WINDOWS
//
//   inline void format(string_format * pformat,const ::u32 & dw) { return format(pformat,(const u32 &)dw);  }
//
//#endif


   //inline bool begins(const atom & atom, const ::string & strPrefix) { return begins(atom.m_psz, strPrefix); }

   inline int get_utf8_char_length(const ::string & psz)
   {

      int len = ch_uni_len(*psz);
      if (len == 0) return 0;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 1) return 1;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 2) return 2;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 3) return 3;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 4) return 4;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 5) return 5;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 6) return 6;

      {
         return -1;
      }
      return -1;
   }


   inline char lower_char(i32 ch)
   {
      if (ch >= 'A' && ch <= 'Z')
      {
         ch = ch - 'A' + 'a';
      }
      return ch;
   }



   inline char upper_char(i32 ch)
   {
      if (ch >= 'a' && ch <= 'z')
      {
         ch = ch - 'a' + 'A';
      }
      return ch;
   }

   inline void          make_lower(char * psz)
   {

      while (*psz)
      {
         *psz = lower_char(*psz);
         psz++;
      }

   }


   inline void          make_upper(char * psz)
   {

      while (*psz)
      {
         *psz = upper_char(*psz);
         psz++;
      }

   }


   CLASS_DECL_ACME bool utf8_check_is_valid(const string& string);

   CLASS_DECL_ACME string q_valid(string str);

   inline char * dup(const ::string & point)
   {


      try
      {

         if (point == nullptr)
         {

            return nullptr;

         }

         return _strdup(point);

      }
      catch (...)
      {

      }

      return nullptr;

   }


   CLASS_DECL_ACME string signed_double(double d);

   CLASS_DECL_ACME string signed_int(int i);

   CLASS_DECL_ACME bool is_true(string str);


   CLASS_DECL_ACME inline strsize utf8_dec_len(const ::string & pszBeg, const ::string & psz);

   CLASS_DECL_ACME inline strsize utf8_inc_len(const ::string & psz);

   CLASS_DECL_ACME inline bool namespaced(const char *psz, const ::string & pszNamespace, const ::string & pszSeparator = "::");


} // namespace str




template < typename T >
inline c_number < T > & c_number < T >::to_string(const ::string & str)
{

   ::from_string(m_number, str);

   return *this;

}


CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern);


CLASS_DECL_ACME string _002Underscore(string str);



