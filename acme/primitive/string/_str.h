#pragma once


struct end_of_line_and_next_line
{

   const char * end_of_line;
   const char * next_line;

};



inline string consume_char(const ansichar * & p)
{
   auto len = ::utf8_len(p);
   string strChar(p, len);
   p+=len;
   return strChar;
}
inline wd16string consume_char(const wd16char * & p)
{
   auto len = ::utf16_len(p);
   wd16string wd16strChar(p, len);
   p+=len;
   return wd16strChar;
}
inline wd32string consume_char(const wd32char * & p)
{
   auto len = 1;
   wd32string wd32strChar(p, len);
   p+=len;
   return wd32strChar;
}


inline ansichar * next_char(const ansichar * & p)
{
   auto len = ::utf8_len(p);
   p+=len;
   return (ansichar *)p;
}
inline const wd16char * next_char(const wd16char * & p)
{
   auto len = ::utf16_len(p);
   p+=len;
   return (wd16char *)p;
}
inline wd32char * next_char(const wd32char * & p)
{
   auto len = 1;
   p+=len;
   return(wd32char *) p;
}


namespace str
{


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


   //inline i32 compare_ignore_case(const ::string & left, const ::string & right, size_t len = 0);
   //inline bool equal_ignore_case(const ::string & left, const ::string & right, size_t len = 0);


   inline CLASS_DECL_ACME bool trimmed_is_empty(const ::string & psz);


   template < typename CHAR_TYPE >
   inline string_base < CHAR_TYPE > repeat(const CHAR_TYPE * psz, strsize c);

   CLASS_DECL_ACME extern enum_error g_eerror;



   inline i32 compare_ignore_case(const string & left, const string & right, size_t len = 0);
   inline bool equal_ignore_case(const string & left, const string & right, size_t len = 0);


   void CLASS_DECL_ACME increment_digit_letter(string & str);

   void CLASS_DECL_ACME copy(string & str, const ::string & pcsz, i32 iCount);

   string CLASS_DECL_ACME replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   string CLASS_DECL_ACME replace_with_ci(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME replace_with_ci_count(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);
   ::count CLASS_DECL_ACME utf8_replace_with(string & str, const ::string & pszNew, const ::string & pszOld, strsize iStart = 0);
   string CLASS_DECL_ACME utf8_replace_with(const ::string & pszNew, const ::string & pszOld, const ::string & psz, strsize iStart = 0);

   inline string find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with(pszNew, pszOld, psz, iStart);
   }
   inline string find_replace_ci(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with_ci(pszNew, pszOld, psz, iStart);
   }
   inline ::count find_replace_ci_count(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return replace_with_ci_count(pszNew, pszOld, psz, iStart);
   }
   inline ::count utf8_find_replace(string & str, const ::string & pszOld, const ::string & pszNew, strsize iStart = 0)
   {
      return utf8_replace_with(str, pszNew, pszOld, iStart);
   }
   inline string utf8_find_replace(const ::string & pszOld, const ::string & pszNew, const ::string & psz, strsize iStart = 0)
   {
      return utf8_replace_with(pszNew, pszOld, psz, iStart);
   }

   string CLASS_DECL_ACME random_replace(::matter * pmatter, const string_array & straNew, const string_array & straOld, const ::string & psz);

   strsize CLASS_DECL_ACME find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart = 0);

   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ::string & strFind, const ansichar   * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind, const ::string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);

   strsize CLASS_DECL_ACME utf8_find(const ansichar   * pszFind, const ansichar   * psz, strsize iStart = 0);


   strsize CLASS_DECL_ACME find_ci(const ansichar   * pszFind,const ::string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_ACME find_file_extension(const ::string & pszExtension,const ::string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_ACME find_ww(const ::string& pszFind, const ::string & psz, strsize iStart = 0);
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
   string CLASS_DECL_ACME if_null(const ansichar * psz, const ::string & pszIfNull = nullptr);


   inline const ansichar * __utf8_inc(const ansichar * psz) { return psz + 1 + trailingBytesForUTF8(*psz); }

   inline enum_error      get_error() { return g_eerror; }
   inline void            set_error(enum_error eerror) { g_eerror = eerror; }
   inline void            clear_error() { g_eerror = e_error_none; }

   CLASS_DECL_ACME  const ansichar *    utf8_inc(const ansichar * psz);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_slide(strsize * pslide, const ansichar * psz);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_copy_slide_back(strsize * pslideback, ansichar * pchDst, const ansichar * pchSrc);
   CLASS_DECL_ACME  const ansichar *    utf8_inc_count(const ansichar * psz, strsize * piCount);

   CLASS_DECL_ACME string block(ansichar ch, i32 iSize);
   CLASS_DECL_ACME void fill(string & str, ansichar ch);

   inline const ansichar * uni_inc(const ansichar * psz) { return utf8_inc(psz); }
   inline const wd16char * uni_inc(const wd16char * psz) { return utf16_inc(psz); }
   inline const wd32char * uni_inc(const wd32char * psz) { return utf32_inc(psz); }

   CLASS_DECL_ACME  const ansichar * uni_dec(const ansichar * pszBeg, const ansichar * psz);
   CLASS_DECL_ACME  const wd16char * uni_dec(const wd16char * pszBeg, const wd16char * psz);
   CLASS_DECL_ACME  const wd32char * uni_dec(const wd32char * pszBeg, const wd32char * psz);


   CLASS_DECL_ACME  string         get_utf8_char(const ansichar *psz);
   CLASS_DECL_ACME  int            get_utf8_char_length(const ansichar *psz);
   CLASS_DECL_ACME  string         get_utf8_char(const ansichar *psz, const ansichar * pszEnd);
   CLASS_DECL_ACME  bool           get_utf8_char(string & strChar, const char * psz, const char * pszEnd);
   CLASS_DECL_ACME  string         get_utf8_char(const ansichar * pszBeg, const ansichar *psz, strsize i);
   CLASS_DECL_ACME  string         utf8_next_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
   CLASS_DECL_ACME  string         utf8_previous_char(const ansichar * pszBeg, const ansichar *psz, strsize i = 0);
   CLASS_DECL_ACME  string         uni_to_utf8(i64 ch);
   CLASS_DECL_ACME  i32            uni_to_utf8_2_or_more(ansichar * dest, i32 ch);

   CLASS_DECL_ACME  const ansichar * utf8_dec(::str::utf8_char * pchar, const ansichar * pszBeg, const ansichar * psz);
   CLASS_DECL_ACME  const ansichar * utf8_dec( const ansichar* pszBeg, const ansichar* psz);




   
   inline bool begins_ci_skip(const char*& psz, const char* pszPrefix);
   inline struct ::end_of_line_and_next_line end_of_line_and_next_line(const char* psz);


} // namespace str


namespace str
{



   CLASS_DECL_ACME  bool           trim_any_quotes(string & str);
   CLASS_DECL_ACME  bool           paired_trim(string & str, ansichar ch);
   CLASS_DECL_ACME  bool           trim(string & str);
   CLASS_DECL_ACME  bool           _008Trim(string & str);




   CLASS_DECL_ACME  string &       zero_pad(string & str, strsize iPad);
   CLASS_DECL_ACME  string         zero_padded(const ::string & str, strsize iPad);
   CLASS_DECL_ACME  i32            get_escaped_char(const ::string & str, strsize pos, strsize &retPos);
   CLASS_DECL_ACME  bool           get_curly_content(const ::string & psz, string & str);
   CLASS_DECL_ACME  bool           is_simple_natural(const ::string & psz, strsize iCount = -1);
   CLASS_DECL_ACME  bool           is_natural(const ::string & psz);
   CLASS_DECL_ACME  bool           is_integer(const ::string & psz);

   CLASS_DECL_ACME string          ansi_lower(const ::string & psz);
   CLASS_DECL_ACME string          ansi_upper(const ::string & psz);



   string CLASS_DECL_ACME get_word(
   const ::string & psz,
   const ::string & pszSeparator,
   bool bWithSeparator = false,
   bool bEndIsSeparator = true);


   CLASS_DECL_ACME bool eats(const ansichar * & pszParse, const ::string & psz);
   CLASS_DECL_ACME bool eats_ci(const ansichar * & szParse, const ::string & psz);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ::string & psz);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ::string & psz, const ::string & pszEnd);
   CLASS_DECL_ACME void consume(const ansichar * & pszParse, const ::string & psz, ::count iLen, const ::string & pszEnd);
   CLASS_DECL_ACME void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount = 1);
   CLASS_DECL_ACME u64 consume_natural(const ansichar * & pszParse, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME u64 consume_natural(string & str, u64 uiMax = ((u64) -1), u64 uiMin = 0);
   CLASS_DECL_ACME string consume_hex(const ansichar * & pszParse);
   CLASS_DECL_ACME void consume_spaces(const ansichar * & pszParse, ::count iMinimumCount, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(const ansichar * & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_non_spaces(string & str);
   CLASS_DECL_ACME string consume_nc_name(const ansichar * & pszParse);
   //CLASS_DECL_ACME string consume_quoted_value(const ansichar * & pszParse);
   CLASS_DECL_ACME void no_escape_consume_quoted_value(const ansichar * & pszParse, const ::string & pszEnd, ansichar ** ppsz, strsize & iBufferSize);
   CLASS_DECL_ACME string no_escape_consume_quoted_value(const ansichar *& pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME void skip_quoted_value_ex2(const ansichar * & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_quoted_value(const ansichar * & pszParse, const ::string & pszEnd = nullptr);
   CLASS_DECL_ACME string consume_quoted_value_ex(const ansichar * & pszParse,const ::string & pszEnd);
   CLASS_DECL_ACME void skip_quoted_value_ex(const ansichar * & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_spaced_value(string & str);
   CLASS_DECL_ACME string consume_spaced_value(const ansichar * & pszParse);
   CLASS_DECL_ACME string consume_spaced_value(const ansichar * & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME string consume_command_line_argument(string & str);
   CLASS_DECL_ACME string consume_command_line_argument(const ansichar * & pszParse);
   CLASS_DECL_ACME string consume_command_line_argument(const ansichar * & pszParse, const ::string & pszEnd);
   CLASS_DECL_ACME bool begins_consume(const ansichar * & pszParse, const ::string & psz);

   CLASS_DECL_ACME bool xml_is_comment(const ::string & pszParse);
   CLASS_DECL_ACME string xml_consume_comment(const ansichar * & pszParse);

   CLASS_DECL_ACME string consume_c_quoted_value(const ansichar * & pszParse, const ::string & pszEnd = nullptr);

   CLASS_DECL_ACME string token(string & str, const ::string & pszSeparatorText, bool bWithSeparator = false);

   //CLASS_DECL_ACME void token(string & strToken, ::string & strSource, const ::string & pszSeparatorText, bool bWithSeparator = false);

   CLASS_DECL_ACME string line(string& str, bool bWithNewLine = false);

   CLASS_DECL_ACME string pad(const ::string & psz, ::count iLen, const ::string & pszPattern, enum_pad epad);


   inline strsize length(const ansichar * pansichar) { return ansi_length(pansichar); }
   inline strsize length(const wd16char * pwd16char) { return wd16_length(pwd16char); }
   inline strsize length(const wd32char * pwd32char) { return wd32_length(pwd32char); }


   template < typename TYPE >
   inline TYPE from_string(const char * psz);


   CLASS_DECL_ACME bool simple_escaped(const ::string & str,strsize pos);


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


   inline void make_upper(wd16char * psz)
   {

      while (*psz)
      {
         *psz = upper_char(*psz);
         psz++;
      }

   }

   inline void make_upper(wd32char * psz)
   {

      while (*psz)
      {
         *psz = upper_char(*psz);
         psz++;
      }

   }



   CLASS_DECL_ACME bool utf8_check_is_valid(const string& string);

   CLASS_DECL_ACME string q_valid(string str);

   inline ansichar * dup(const ::string & psz)
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


   CLASS_DECL_ACME inline strsize utf8_dec_len(const ::string & pszBeg, const ::string & psz);

   CLASS_DECL_ACME inline strsize utf8_inc_len(const ::string & psz);

   CLASS_DECL_ACME inline bool namespaced(const ansichar *psz, const ::string & pszNamespace, const ::string & pszSeparator = "::");


} // namespace str











CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2);


CLASS_DECL_ACME string _002Underscore(string str);


namespace str
{


   CLASS_DECL_ACME void fix_eol(string & str);


} // namespace str


inline CLASS_DECL_ACME string string_from_strdup(const char * psz);

