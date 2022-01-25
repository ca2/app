#pragma once


class ::payload;
class id;
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
   i32  CLASS_DECL_ACME compare(const char * psz1, const char * psz2);
   i32  CLASS_DECL_ACME compare_ci(const char * psz1, const char * psz2);
   bool CLASS_DECL_ACME equals(const char * psz1, const char * psz2);
   bool CLASS_DECL_ACME equals_ci(const char * psz1, const char * psz2);
   string CLASS_DECL_ACME equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = nullptr);
   string CLASS_DECL_ACME equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = nullptr);

   inline bool begins(const char * psz,string & strFed, const ::string & strPrefix);
   inline bool begins(const ::string & str,string & strFed,const ::string & strPrefix);
   inline bool begins(const id & id,string & strFed,const ::string & strPrefix);

   inline bool begins(const char * psz, const ::string & strPrefix);
   inline bool begins(const ::string & str, const ::string & strPrefix);
   inline bool begins(const id & id, const ::string & strPrefix);
   inline bool begins_with(const char * psz, const ::string & strPrefix);
   inline bool begins_with(const ::string & str, const ::string & strPrefix);


   void CLASS_DECL_ACME begin(wstring & wstr, const unichar * pcszPrefix);


   bool CLASS_DECL_ACME begins(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins(const wstring & str, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_with(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_with(const wstring & str, const unichar * pcszPrefix);



   bool CLASS_DECL_ACME begins_ci(const char * pcsz, const char * lpcszPrefix);

   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACME begins_ci_iws(const char * psz, const char * pcszPrefix);

   bool CLASS_DECL_ACME begins_ci_iws(const ::string & str, const char * pcszPrefix);



   bool CLASS_DECL_ACME begins_ci(const unichar * pcsz, const unichar * lpcszPrefix);

   bool CLASS_DECL_ACME begins_ci(const wstring & wstr, const unichar * pcszPrefix);

   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACME begins_ci_iws(const unichar * psz, const unichar * pcszPrefix);

   bool CLASS_DECL_ACME begins_ci_iws(const wstring & str, const unichar * pcszPrefix);



   bool CLASS_DECL_ACME eat_before(string & strBefore,const string & strSeparator, string & str, bool bEatEverythingIfNotFound = false);
   bool CLASS_DECL_ACME eat_before_let_separator(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound = false);


   inline bool begins_eat(string & str, const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(string & str, const char * pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(string & str, const char * pcszPrefix, const char * pszSeparator); // case insensitive

   inline bool begins_eat(::payload & payload,const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(::payload & payload, const char * pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(::payload & payload, const char * pcszPrefix, const char * pszSeparator); // case insensitive

   inline bool begins_eat(property & property, const ::string & strPrefix);
   bool CLASS_DECL_ACME begins_eat_ci(property & property, const char * pcszPrefix); // case insensitive

   bool CLASS_DECL_ACME begins_eat_ci(property & property, const char * pcszPrefix, const char * pszSeparator); // case insensitive

   bool CLASS_DECL_ACME while_begins_with_chars_eat(string & str, const char * pcszChars);

   bool CLASS_DECL_ACME while_begins_with_chars_eat_ci(string & str, const char * pcszChars); // case insensitive

   bool CLASS_DECL_ACME ends(const char * pcsz, const char * lpcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const char * pcsz, const char * lpcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const ::string & str, const char * pcszSuffix);

   bool CLASS_DECL_ACME ends_ci(const ::payload & payload, const char * pcszSuffix);

   bool CLASS_DECL_ACME ends_eat(string & str, const char * pcszSuffix);

   bool CLASS_DECL_ACME ends_eat_ci(string & str, const char * pcszSuffix);

   void CLASS_DECL_ACME copy(string & str, const char * pcsz, i32 iCount);

   string CLASS_DECL_ACME replace_with(const char * pszNew, const char * pszOld, const char * psz, strsize iStart = 0);
   string CLASS_DECL_ACME replace_with_ci(const char * pszNew, const char * pszOld, const char * psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME replace_with_ci_count(const char * pszNew, const char * pszOld, const char * psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME utf8_replace_with(string & str, const char * pszNew, const char * pszOld, strsize iStart = 0);
   string CLASS_DECL_ACME utf8_replace_with(const char * pszNew, const char * pszOld, const char * psz, strsize iStart = 0);

   string CLASS_DECL_ACME random_replace(::matter * pobject, const string_array & straNew, const string_array & straOld, const char * psz);

   strsize CLASS_DECL_ACME find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const char   * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const char   * pszFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const char   * pszFind, const char   * psz, strsize iStart = 0);

   strsize CLASS_DECL_ACME utf8_find(const char   * pszFind, const char   * psz, strsize iStart = 0);


   strsize CLASS_DECL_ACME find_ci(const char   * pszFind,const ::string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_ACME find_file_extension(const char * pszExtension,const ::string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_ACME find_ww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_wwci(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_aww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_awwci(const char * pszFind, const char * psz, strsize iStart = 0);
   string CLASS_DECL_ACME has_char(const char * pszIfHasChar, const char * pszBefore = nullptr, const char * pszAfter = nullptr, const char * pszDoesnt = nullptr);
   bool CLASS_DECL_ACME has_upper(const char * psz);
   bool CLASS_DECL_ACME has_lower(const char * psz);
   bool CLASS_DECL_ACME has_digit(const char * psz);
   void CLASS_DECL_ACME calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const char * psz);
   string CLASS_DECL_ACME if_null(const char * psz, const char * pszIfNull = nullptr);


   FORCEINLINE  const char * __utf8_inc(const char * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   inline e_err           err() { return g_eerr; }
   inline void            set_err(e_err eerr) { g_eerr = eerr; }
   inline void            clear_err() { g_eerr = err_none; }

   CLASS_DECL_ACME  const char *   utf8_inc(const char * psz);
   CLASS_DECL_ACME  const char *   utf8_inc_slide(strsize * pslide, const char * psz);
   CLASS_DECL_ACME  const char *   utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc);


   CLASS_DECL_ACME string block(char ch, i32 iSize);
   CLASS_DECL_ACME void fill(string & str, char ch);


   CLASS_DECL_ACME  const char *   utf8_dec(const char * pszBeg, const char * psz);
   CLASS_DECL_ACME  string         get_utf8_char(const char *psz);
   CLASS_DECL_ACME  int            get_utf8_char_length(const char *psz);
   CLASS_DECL_ACME  string         get_utf8_char(const char *psz, const char * pszEnd);
   CLASS_DECL_ACME  bool           get_utf8_char(string & strChar, const char * & psz, const char * pszEnd);
   CLASS_DECL_ACME  string         get_utf8_char(const char * pszBeg, const char *psz, strsize i);
   CLASS_DECL_ACME  string         utf8_next_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACME  string         utf8_previous_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACME  string         uni_to_utf8(i64 ch);
   CLASS_DECL_ACME  i32 uni_to_utf8_2_or_more(char * dest, i32 ch);

   CLASS_DECL_ACME  const char *   utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz);


   CLASS_DECL_ACME  bool           to(i32 & i, const char * psz);
   CLASS_DECL_ACME  bool           to(i64 & i, const char * psz);
   CLASS_DECL_ACME  bool           to(i32 & i, i32 iBase, const char * psz);
   CLASS_DECL_ACME  bool           to(i64 & i, i32 iBase, const char * psz);
   CLASS_DECL_ACME  bool           to(u32 & i, const char * psz);
   CLASS_DECL_ACME  bool           to(u64 & i, const char * psz);
   CLASS_DECL_ACME  bool           to(u32 & i, i32 iBase, const char * psz);
   CLASS_DECL_ACME  bool           to(u64 & i, i32 iBase, const char * psz);

   CLASS_DECL_ACME  bool           trim_any_quotes(string & str);
   CLASS_DECL_ACME  bool           paired_trim(string & str, char ch);
   CLASS_DECL_ACME  bool           trim(string & str);
   CLASS_DECL_ACME  bool           _008Trim(string & str);


   CLASS_DECL_ACME  iptr        to_iptr(const char * psz);
   CLASS_DECL_ACME  i32            to_i32(const char * psz);
   CLASS_DECL_ACME  u32   to_u32(const char * psz);


   /** C++ Sockets Library \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/

   //CLASS_DECL_ACME string l2string(long l); // please use itoa
   //CLASS_DECL_ACME string bigint2string(u64 l); // please use itoa
   CLASS_DECL_ACME i64         to_i64(const ::string & str) ;
   CLASS_DECL_ACME i64         to_i64(const char * psz) ;
   CLASS_DECL_ACME u64        to_u64(const ::string & str) ;
   CLASS_DECL_ACME u64        to_u64(const char * psz) ;

   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/



   inline CLASS_DECL_ACME i32 to_with_fallback(const char * psz, i32 iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const char * psz, i64 iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i32 to_with_fallback(const char * psz, i32 iDefault, i32 iBase) { to(iDefault, iBase, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const char * psz, i64 iDefault, i32 iBase) { to(iDefault, iBase, psz); return iDefault; }

   // template < typename T >
   // inline string from(const T & t);

   // template < typename T >
   // inline string  from_int(const T & t);

   // template < typename T >
   // inline string  from_u(const T & t);

   // inline CLASS_DECL_ACME string from_strdup(const char * psz);





   /*inline CLASS_DECL_ACME string  to_string(i32 i);
   inline CLASS_DECL_ACME string  to_string(u32 u);
   inline CLASS_DECL_ACME string  to_string(i64 i);
   inline CLASS_DECL_ACME string  to_string(u64 u);
   inline CLASS_DECL_ACME string  to_string(const ::payload & payload);
   inline CLASS_DECL_ACME string  to_string(const id & id);
   inline CLASS_DECL_ACME string  to_string(double d);
   inline CLASS_DECL_ACME string  to_string(float f);*/

   /*
      CLASS_DECL_ACME  string &       to_string(string & str, i32 i);
      CLASS_DECL_ACME  string &       to_string(string & str, u32 u);
      CLASS_DECL_ACME  string &       to_string(string & str, i64 i);
      CLASS_DECL_ACME  string &       to_string(string & str, u64 u);
      CLASS_DECL_ACME  string &       to_string(string & str, float f);
      CLASS_DECL_ACME  string &       to_string(string & str, double d);
      inline CLASS_DECL_ACME string & to_string(string & str, const id & id);
      inline CLASS_DECL_ACME string & to_string(string & str, const ::payload & payload);


   #ifdef ANDROID

      CLASS_DECL_ACME  string &       to_string(string & str, long int i);

   #endif
   */


   //inline CLASS_DECL_ACME string   i64toa(i64 i);

   //CLASS_DECL_ACME  string         ansi_zero_pad(const ::string & strSrc,int iPad);
   CLASS_DECL_ACME  i32        get_escaped_char(const char * str, strsize pos, strsize &retPos);
   CLASS_DECL_ACME  bool           get_curly_content(const char * psz, string & str);
   CLASS_DECL_ACME  bool           is_simple_natural(const char * psz, strsize iCount = -1);
   CLASS_DECL_ACME  bool           is_natural(const char * psz);
   CLASS_DECL_ACME  bool           is_integer(const char * psz);

   CLASS_DECL_ACME string          ansi_lower(const char * psz);
   CLASS_DECL_ACME string          ansi_upper(const char * psz);


//   string CLASS_DECL_ACME get_window_text_timeout(::windowing::window * pwindow, ::duration tickTimeout = 1000);

   string CLASS_DECL_ACME get_word(
   const char * psz,
   const char * pszSeparator,
   bool bWithSeparator = false,
   // if end is separator, return entire string if separator is not found
   // otherwise, return is_empty
   bool bEndIsSeparator = true);

   CLASS_DECL_ACME bool eats(const char * & pszParse, const char * psz);
   CLASS_DECL_ACME bool eats_ci(const char * & pszParse, const char * psz);
   CLASS_DECL_ACME void consume(const char * & pszParse, const char * psz);
   CLASS_DECL_ACME void consume(const char * & pszParse, const char * psz, const char * pszEnd);
   CLASS_DECL_ACME void consume(const char * & pszParse, const char * psz, ::count iLen, const char * pszEnd);
   CLASS_DECL_ACME void consume_spaces(const char * & pszParse, ::count iMinimumCount = 1);
   CLASS_DECL_ACME u64 consume_natural(const char * & pszParse, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME u64 consume_natural(string & str, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME string consume_hex(const char * & pszParse);
   CLASS_DECL_ACME void consume_spaces(const char * & pszParse, ::count iMinimumCount, const char * pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(string & str);
   CLASS_DECL_ACME string consume_nc_name(const char * & pszParse);
   //CLASS_DECL_ACME string consume_quoted_value(const char * & pszParse);
   CLASS_DECL_ACME void consume_quoted_value_ex2(const char * & pszParse, const char * pszEnd, char ** ppsz, strsize & iBufferSize);
   CLASS_DECL_ACME void skip_quoted_value_ex2(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME string consume_quoted_value(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME string consume_quoted_value_ex(const char * & pszParse,const char * pszEnd);
   CLASS_DECL_ACME void skip_quoted_value_ex(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME string consume_spaced_value(string & str);
   CLASS_DECL_ACME string consume_spaced_value(const char * & pszParse);
   CLASS_DECL_ACME string consume_spaced_value(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME string consume_command_line_argument(string & str);
   CLASS_DECL_ACME string consume_command_line_argument(const char * & pszParse);
   CLASS_DECL_ACME string consume_command_line_argument(const char * & pszParse, const char * pszEnd);
   CLASS_DECL_ACME bool begins_consume(const char * & pszParse, const char * psz);

   CLASS_DECL_ACME bool xml_is_comment(const char * pszParse);
   CLASS_DECL_ACME string xml_consume_comment(const char * & pszParse);

   CLASS_DECL_ACME string consume_c_quoted_value(const char * & pszParse);

   CLASS_DECL_ACME string token(string & str, const char * pszSeparatorText, bool bWithSeparator = false);

   CLASS_DECL_ACME string line(string& str, bool bWithNewLine = false);

   CLASS_DECL_ACME string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad);

   inline ::count ilen(const char * psz) { return (count) strlen(psz); }
   inline i64 len(const char * psz) { return (i64) strlen(psz); }


   template < typename TYPE >
   inline TYPE string_from_string(const char * psz);

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
//   CLASS_DECL_ACME void format(string_format * pformat, const char * const & psz);
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


   //inline bool begins(const id & id, const ::string & strPrefix) { return begins(id.m_psz, strPrefix); }

   inline int get_utf8_char_length(const char * psz)
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

   inline char * dup(const char * point)
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


   CLASS_DECL_ACME inline strsize utf8_dec_len(const char * pszBeg, const char * psz);

   CLASS_DECL_ACME inline strsize utf8_inc_len(const char * psz);

   CLASS_DECL_ACME inline bool namespaced(const char *psz, const char * pszNamespace, const char * pszSeparator = "::");


} // namespace str




template < typename T >
inline c_number < T > & c_number < T >::to_string(const ::string & str)
{

   ::from_string(m_number, str);

   return *this;

}


CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern);


CLASS_DECL_ACME string _002Underscore(string str);



