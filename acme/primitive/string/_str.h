#pragma once


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


   inline i32 compare_ignore_case(const char * left, const char * right, size_t len = 0);
   inline bool equal_ignore_case(const char * left, const char * right, size_t len = 0);


   inline CLASS_DECL_ACME bool trimmed_is_empty(const char * psz);


   template < typename CHAR_TYPE >
   inline string_base < CHAR_TYPE > repeat(const CHAR_TYPE * psz, strsize c);

   CLASS_DECL_ACME extern e_err g_eerr;



   inline i32 compare_ignore_case(const string & left, const string & right, size_t len = 0);
   inline bool equal_ignore_case(const string & left, const string & right, size_t len = 0);
   inline i32 compare_ignore_case(const ansichar * left, const string & right, size_t len = 0);
   inline bool equal_ignore_case(const ansichar * left, const string & right, size_t len = 0);
   inline i32 compare_ignore_case(const string & left, const ansichar * right, size_t len = 0);



   void CLASS_DECL_ACME increment_digit_letter(string & str);

   void CLASS_DECL_ACME copy(string & str, const ansichar * pcsz, i32 iCount);

   string CLASS_DECL_ACME replace_with(const ansichar * pszNew, const ansichar * pszOld, const ansichar * psz, strsize iStart = 0);
   string CLASS_DECL_ACME replace_with_ci(const ansichar * pszNew, const ansichar * pszOld, const ansichar * psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME replace_with_ci_count(const ansichar * pszNew, const ansichar * pszOld, const ansichar * psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME utf8_replace_with(string & str, const ansichar * pszNew, const ansichar * pszOld, strsize iStart = 0);
   string CLASS_DECL_ACME utf8_replace_with(const ansichar * pszNew, const ansichar * pszOld, const ansichar * psz, strsize iStart = 0);

   inline string find_replace(const ansichar * pszOld, const ansichar * pszNew, const ansichar * psz, strsize iStart = 0)
   {
      return replace_with(pszNew, pszOld, psz, iStart);
   }
   inline string find_replace_ci(const ansichar * pszOld, const ansichar * pszNew, const ansichar * psz, strsize iStart = 0)
   {
      return replace_with_ci(pszNew, pszOld, psz, iStart);
   }
   inline ::count find_replace_ci_count(const ansichar * pszOld, const ansichar * pszNew, const ansichar * psz, strsize iStart = 0)
   {
      return replace_with_ci_count(pszNew, pszOld, psz, iStart);
   }
   inline ::count utf8_find_replace(string & str, const ansichar * pszOld, const ansichar * pszNew, strsize iStart = 0)
   {
      return utf8_replace_with(str, pszNew, pszOld, iStart);
   }
   inline string utf8_find_replace(const ansichar * pszOld, const ansichar * pszNew, const ansichar * psz, strsize iStart = 0)
   {
      return utf8_replace_with(pszNew, pszOld, psz, iStart);
   }

   string CLASS_DECL_ACME random_replace(::matter * pmatter, const string_array & straNew, const string_array & straOld, const ansichar * psz);

   strsize CLASS_DECL_ACME find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ansichar   * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);

   strsize CLASS_DECL_ACME utf8_find(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);


   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind,const ::string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_ACME find_file_extension(const ansichar * pszExtension,const ::string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_ACME find_ww(const ansichar * pszFind, const ansichar * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_wwci(const ansichar * pszFind, const ansichar * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_aww(const ansichar * pszFind, const ansichar * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_awwci(const ansichar * pszFind, const ansichar * psz, strsize iStart = 0);
   string CLASS_DECL_ACME has_char(const ansichar * pszIfHasChar, const ansichar * pszBefore = nullptr, const ansichar * pszAfter = nullptr, const ansichar * pszDoesnt = nullptr);
   bool CLASS_DECL_ACME has_upper(const ansichar * psz);
   bool CLASS_DECL_ACME has_lower(const ansichar * psz);
   bool CLASS_DECL_ACME has_digit(const ansichar * psz);
   void CLASS_DECL_ACME calc_v1(const ansichar * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_one_v1(const ansichar * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const ansichar * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACME has_all_v1(const ansichar * psz);
   string CLASS_DECL_ACME if_null(const ansichar * psz, const ansichar * pszIfNull = nullptr);


   inline const ansichar * __utf8_inc(const ansichar * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   inline e_err           err() { return g_eerr; }
   inline void            set_err(e_err eerr) { g_eerr = eerr; }
   inline void            clear_err() { g_eerr = err_none; }

   CLASS_DECL_ACME  const ansichar *    utf8_inc(const ansichar * psz);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_slide(strsize * pslide, const ansichar * psz);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_copy_slide_back(strsize * pslideback, ansichar * pchDst, const ansichar * pchSrc);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_count(const ansichar * psz, strsize * piCount);

   CLASS_DECL_ACME string block(ansichar ch, i32 iSize);
   CLASS_DECL_ACME void fill(string & str, ansichar ch);

   inline const ansichar * uni_inc(const ansichar * psz) { return utf8_inc(psz); }
   inline const wd16char * uni_inc(const wd16char * psz) { return utf16_inc(psz); }
   inline const wd32char * uni_inc(const wd32char * psz) { return utf32_inc(psz); }

   CLASS_DECL_ACME   const ansichar *      uni_dec(const ansichar * pszBeg, const ansichar * psz);
   CLASS_DECL_ACME   const wd16char * uni_dec(const wd16char * pszBeg, const wd16char * psz);
   CLASS_DECL_ACME   const wd32char * uni_dec(const wd32char * pszBeg, const wd32char * psz);


   CLASS_DECL_ACME  string         get_utf8_char(const ansichar *psz);
   CLASS_DECL_ACME  int            get_utf8_char_length(const ansichar *psz);
   CLASS_DECL_ACME  string         get_utf8_char(const ansichar *psz, const ansichar * pszEnd);
   CLASS_DECL_ACME  bool           get_utf8_char(string & strChar, const ansichar * & psz, const ansichar * pszEnd);
   CLASS_DECL_ACME  string         get_utf8_char(const ansichar * pszBeg, const ansichar *psz, strsize i);
   CLASS_DECL_ACME  string         utf8_next_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
   CLASS_DECL_ACME  string         utf8_previous_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
   CLASS_DECL_ACME  string         uni_to_utf8(i64 ch);
   CLASS_DECL_ACME  i32            uni_to_utf8_2_or_more(ansichar * dest, i32 ch);

   CLASS_DECL_ACME  const ansichar *   utf8_dec(::str::utf8_char * pchar, const ansichar * pszBeg, const ansichar * psz);
   CLASS_DECL_ACME  const ansichar *   utf8_dec( const ansichar* pszBeg, const ansichar* psz);


} // namespace str

inline  void           from_string(ansichar & ch, const ansichar * psz);
inline  void           from_string(widechar & ch, const ansichar * psz);

inline  void           from_string(i8 & i, const ansichar * psz);
inline  void           from_string(i16 & i, const ansichar * psz);
inline  void           from_string(i32 & i, const ansichar * psz);
inline  void           from_string(i64 & i, const ansichar * psz);
inline  void           from_string(i32 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(i64 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(u8 & i, const ansichar * psz);
inline  void           from_string(u16 & i, const ansichar * psz);
inline  void           from_string(u32 & i, const ansichar * psz);
inline  void           from_string(u64 & i, const ansichar * psz);
inline  void           from_string(u32 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(u64 & i, i32 iBase, const ansichar * psz);

#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
inline  void           from_string(long & l, const ansichar * psz);
inline  void           from_string(long & l, i32 iBase, const ansichar * psz);
#endif

inline  void           from_string(float & f, const ansichar * psz);
inline  void           from_string(double & d, const ansichar * psz);


inline  void           from_string(ansichar * sz, const ansichar * psz);
inline  void           from_string(wd16char * sz, const ansichar * psz);
inline  void           from_string(wd32char * sz, const ansichar * psz);

template < size_t n >
inline  void           from_string(ansichar sz[n], const ansichar * psz);
template < size_t n >
inline  void           from_string(wd16char sz[n], const ansichar * psz);
template < size_t n >
inline  void           from_string(wd32char sz[n], const ansichar * psz);


inline  void           from_string(::id & id, const ansichar * psz);

inline void from_string(::element & element, const ansichar * psz);

namespace str
{



   CLASS_DECL_ACME  bool           trim_any_quotes(string & str);
   CLASS_DECL_ACME  bool           paired_trim(string & str, ansichar ch);
   CLASS_DECL_ACME  bool           trim(string & str);
   CLASS_DECL_ACME  bool           _008Trim(string & str);


   CLASS_DECL_ACME  iptr         to_iptr(const ansichar * psz);
   CLASS_DECL_ACME  i32          to_i32(const ansichar * psz);
   CLASS_DECL_ACME  u32          to_u32(const ansichar * psz);


   CLASS_DECL_ACME i64           to_i64(const ::string & str) ;
   CLASS_DECL_ACME i64           to_i64(const ansichar * psz) ;
   CLASS_DECL_ACME u64           to_u64(const ::string & str) ;
   CLASS_DECL_ACME u64           to_u64(const ansichar * psz) ;



   inline CLASS_DECL_ACME i32 to_with_fallback(const ansichar * psz, i32 iDefault) { from_string(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ansichar * psz, i64 iDefault) { from_string(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i32 to_with_fallback(const ansichar * psz, i32 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ansichar * psz, i64 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }


   CLASS_DECL_ACME  string &       zero_pad(string & str, strsize iPad);
   CLASS_DECL_ACME  string         zero_padded(const ::string & str, strsize iPad);
   CLASS_DECL_ACME  i32            get_escaped_char(const ansichar * str, strsize pos, strsize &retPos);
   CLASS_DECL_ACME  bool           get_curly_content(const ansichar * psz, string & str);
   CLASS_DECL_ACME  bool           is_simple_natural(const ansichar * psz, strsize iCount = -1);
   CLASS_DECL_ACME  bool           is_natural(const ansichar * psz);
   CLASS_DECL_ACME  bool           is_integer(const ansichar * psz);

   CLASS_DECL_ACME string          ansi_lower(const ansichar * psz);
   CLASS_DECL_ACME string          ansi_upper(const ansichar * psz);



   string CLASS_DECL_ACME get_word(
   const ansichar * psz,
   const ansichar * pszSeparator,
   bool bWithSeparator = false,
   bool bEndIsSeparator = true);


   CLASS_DECL_ACME bool eats(const ansichar * & pszParse, const ansichar * psz);
   CLASS_DECL_ACME bool eats_ci(const ansichar * & pszParse, const ansichar * psz);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ansichar * psz);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ansichar * psz, const ansichar * pszEnd);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ansichar * psz, ::count iLen, const ansichar * pszEnd);
   CLASS_DECL_ACME void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount = 1);
   CLASS_DECL_ACME u64 consume_natural(const ansichar * & pszParse, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME u64 consume_natural(string & str, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME string consume_hex(const ansichar * & pszParse);
   CLASS_DECL_ACME void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount, const ansichar * pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(const ansichar * & pszParse, const ansichar * pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(string & str);
   CLASS_DECL_ACME string consume_nc_name(const ansichar * & pszParse);
   //CLASS_DECL_ACME string consume_quoted_value(const ansichar * & pszParse);
   CLASS_DECL_ACME void consume_quoted_value_ex2(const ansichar * & pszParse, const ansichar * pszEnd, ansichar ** ppsz, strsize & iBufferSize);
   CLASS_DECL_ACME void skip_quoted_value_ex2(const ansichar * & pszParse, const ansichar * pszEnd);
   CLASS_DECL_ACME string consume_quoted_value(const ansichar * & pszParse, const ansichar * pszEnd = nullptr);
   CLASS_DECL_ACME string consume_quoted_value_ex(const ansichar * & pszParse,const ansichar * pszEnd);
   CLASS_DECL_ACME void skip_quoted_value_ex(const ansichar * & pszParse, const ansichar * pszEnd);
   CLASS_DECL_ACME string consume_spaced_value(string & str);
   CLASS_DECL_ACME string consume_spaced_value(const ansichar * & pszParse);
   CLASS_DECL_ACME string consume_spaced_value(const ansichar * & pszParse, const ansichar * pszEnd);
   CLASS_DECL_ACME string consume_command_line_argument(string & str);
   CLASS_DECL_ACME string consume_command_line_argument(const ansichar * & pszParse);
   CLASS_DECL_ACME string consume_command_line_argument(const ansichar * & pszParse, const ansichar * pszEnd);
   CLASS_DECL_ACME bool begins_consume(const ansichar * & pszParse, const ansichar * psz);

   CLASS_DECL_ACME bool xml_is_comment(const ansichar * pszParse);
   CLASS_DECL_ACME string xml_consume_comment(const ansichar * & pszParse);

   CLASS_DECL_ACME string consume_c_quoted_value(const ansichar * & pszParse, const char * pszEnd = nullptr);

   CLASS_DECL_ACME string token(string & str, const ansichar * pszSeparatorText, bool bWithSeparator = false);

   //CLASS_DECL_ACME void token(string & strToken, ::string & strSource, const ansichar * pszSeparatorText, bool bWithSeparator = false);

   CLASS_DECL_ACME string line(string& str, bool bWithNewLine = false);

   CLASS_DECL_ACME string pad(const ansichar * psz, ::count iLen, const ansichar * pszPattern, e_pad epad);

   inline ::count ilen(const ansichar * psz) { return (count) strlen(psz); }
   inline i64 len(const ansichar * psz) { return (i64) strlen(psz); }


   template < typename TYPE >
   inline TYPE from_string(const ansichar * psz);


   CLASS_DECL_ACME bool simple_escaped(const ::string & str,strsize pos);


   inline int get_utf8_char_length(const ansichar * psz)
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


   inline ansichar lower_char(i32 ch)
   {
      if (ch >= 'A' && ch <= 'Z')
      {
         ch = ch - 'A' + 'a';
      }
      return ch;
   }



   inline ansichar upper_char(i32 ch)
   {
      if (ch >= 'a' && ch <= 'z')
      {
         ch = ch - 'a' + 'A';
      }
      return ch;
   }

   inline void          make_lower(ansichar * psz)
   {

      while (*psz)
      {
         *psz = lower_char(*psz);
         psz++;
      }

   }


   inline void          make_upper(ansichar * psz)
   {

      while (*psz)
      {
         *psz = upper_char(*psz);
         psz++;
      }

   }


   CLASS_DECL_ACME bool utf8_check_is_valid(const string& string);

   CLASS_DECL_ACME string q_valid(string str);

   inline ansichar * dup(const ansichar * psz)
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


   CLASS_DECL_ACME string signed_double(double d);

   CLASS_DECL_ACME string signed_int(int i);

   CLASS_DECL_ACME bool is_true(string str);


   CLASS_DECL_ACME inline strsize utf8_dec_len(const ansichar * pszBeg, const ansichar * psz);

   CLASS_DECL_ACME inline strsize utf8_inc_len(const ansichar * psz);

   CLASS_DECL_ACME inline bool namespaced(const ansichar *psz, const ansichar * pszNamespace, const ansichar * pszSeparator = "::");


} // namespace str











CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


CLASS_DECL_ACME string _002Underscore(string str);


namespace str
{


   CLASS_DECL_ACME void fix_eol(string & str);


} // namespace str


