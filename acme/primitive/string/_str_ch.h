
class CLASS_DECL_ACME ch
{

public:

   //    /*
   // * Index into the table below with the first byte of a UTF-8 sequence to
   // * get the number of trailing bytes that are supposed to follow it.
   // * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
   // * left as-is for anyone who may want to do such conversion, which was
   // * allowed in earlier algorithms.
   // */
   //static const char trailingBytesForUTF8[256] = {
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   //    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
   //};
   // return UTF8 Extra Bytes based on supplied First Char

   inline i32 parse_unicode(const ansichar *& pszChar);
   inline i32 parse_unicode(const wd16char *& pszChar);
   inline i32 parse_unicode(const wd32char *& pszChar) { return *pszChar++; }

   // return Unicode Index
   inline i32 uni_index(const ansichar * pszChar);
   inline i32 uni_index(const wd16char * pszChar) { strsize srclen = 2; return ::__uni_index(pszChar, &srclen); }
   inline i32 uni_index(const wd32char * pszChar) { return *pszChar; }

   // return number of characters need to be consumed to parse a Unicode Character
   inline i32 uni_len(const ansichar * pszChar);
   inline i32 uni_len(const wd16char * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
   inline i32 uni_len(const wd32char * pszChar) { return 1; }

   
   template < typename CHAR_TYPE >
   inline CHAR_TYPE * inc(CHAR_TYPE * & pszChar)
   {
      
      return pszChar += uni_len(pszChar);
      
   }
 
   
   inline i32 ansichar_uni_len(wd32char i);
   inline i32 wd16char_uni_len(wd32char i) { return utf32_is_surrogated(i) ? 2 : 1; }
   inline i32 wd32char_uni_len(wd32char i) { return 1; }

   // return number of characters needed to represent the Unicode Character
   inline i32 char_uni_len(const ansichar *, wd32char i) { return ansichar_uni_len(i); }
   inline i32 char_uni_len(const wd16char *, wd32char i) { return wd16char_uni_len(i); }
   inline i32 char_uni_len(const wd32char *, wd32char i) { return wd32char_uni_len(i); }

   // return Unicode Index and
   // number of characters need to be consumed to parse a Unicode Character
   inline i32 uni_index_len(const ansichar * pszChar, i32 & len);
   inline i32 uni_index_len(const wd16char * pszChar, i32 & len);
   inline i32 uni_index_len(const wd32char * pszChar, i32 & len) { len = 1; return *pszChar; }


   inline bool is_legal_uni_index(i64 iUnicodeIndex)
   {

      return iUnicodeIndex >= 0 && iUnicodeIndex < 65536 ? true : false;

      //return ca >= ((u64) 0xffffffffu) ? false : true;

   }


   inline bool is_space_char(i32 i);
   inline i32 to_lower_case(i32 i);
   inline i32 to_upper_case(i32 i);
   inline i32 to_title_case(i32 i);
   inline i32 to_numeric_value(i32 i, float * f);


   inline bool is_lower_case(::i32 iUniIndex);
   inline bool is_upper_case(::i32 iUniIndex);
   inline bool is_title_case(::i32 iUniIndex);
   inline bool is_letter(::i32 iUniIndex);
   inline bool is_letter_or_digit(::i32 iUniIndex);
   inline bool is_digit(::i32 iUniIndex);
   inline bool is_number(::i32 iUniIndex);
   inline bool is_assigned(::i32 iUniIndex);
   //inline bool is_space_char(::i32 iUniIndex);

   inline bool is_lower_case(const ansichar * pszChar) { return is_lower_case(__uni_index(pszChar)); }
   inline bool is_upper_case(const ansichar * pszChar) { return is_upper_case(__uni_index(pszChar)); }
   inline bool is_title_case(const ansichar * pszChar) { return is_title_case(__uni_index(pszChar)); }
   inline bool is_letter(const ansichar * pszChar) { return is_letter(__uni_index(pszChar)); }
   inline bool is_letter_or_digit(const ansichar * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
   inline bool is_digit(const ansichar * pszChar) { return is_digit(__uni_index(pszChar)); }
   inline bool is_assigned(const ansichar * pszChar) { return is_assigned(__uni_index(pszChar)); }
   inline bool is_space_char(const ansichar * pszChar) { return is_space_char(__uni_index(pszChar)); }

   inline bool is_lower_case(const wd16char * pszChar) { return is_lower_case(__uni_index(pszChar)); }
   inline bool is_upper_case(const wd16char * pszChar) { return is_upper_case(__uni_index(pszChar)); }
   inline bool is_title_case(const wd16char * pszChar) { return is_title_case(__uni_index(pszChar)); }
   inline bool is_letter(const wd16char * pszChar) { return is_letter(__uni_index(pszChar)); }
   inline bool is_letter_or_digit(const wd16char * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
   inline bool is_digit(const wd16char * pszChar) { return is_digit(__uni_index(pszChar)); }
   inline bool is_assigned(const wd16char * pszChar) { return is_assigned(__uni_index(pszChar)); }
   inline bool is_space_char(const wd16char * pszChar) { return is_space_char(__uni_index(pszChar)); }

   inline bool is_lower_case(const wd32char * pszChar) { return is_lower_case(__uni_index(pszChar)); }
   inline bool is_upper_case(const wd32char * pszChar) { return is_upper_case(__uni_index(pszChar)); }
   inline bool is_title_case(const wd32char * pszChar) { return is_title_case(__uni_index(pszChar)); }
   inline bool is_letter(const wd32char * pszChar) { return is_letter(__uni_index(pszChar)); }
   inline bool is_letter_or_digit(const wd32char * pszChar) { return is_letter_or_digit(__uni_index(pszChar)); }
   inline bool is_digit(const wd32char * pszChar) { return is_digit(__uni_index(pszChar)); }
   inline bool is_assigned(const wd32char * pszChar) { return is_assigned(__uni_index(pszChar)); }
   inline bool is_space_char(const wd32char * pszChar) { return is_space_char(__uni_index(pszChar)); }

   inline bool is_whitespace(i32 i);
   //{
   //   if (!is_legal_uni_index(i))
   //      return false;
   //   return  (i == 0x20)
   //      ||
   //      ((i <= 0x0020) &&
   //      (((((1 << 0x0009) |
   //         (1 << 0x000A) |
   //         (1 << 0x000C) |
   //         (1 << 0x000D)) >> i) & 1) != 0))
   //      ||
   //      (((((1 << CHAR_CATEGORY_Zs) |
   //      (1 << CHAR_CATEGORY_Zl) |
   //         (1 << CHAR_CATEGORY_Zp)
   //         ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0);
   //}

   inline bool is_whitespace(const char * psz) { return is_whitespace(uni_index(psz)); }
   inline bool is_whitespace(const wd16char * psz) { return is_whitespace(uni_index(psz)); }
   inline bool is_whitespace(const wd32char * psz) { return is_whitespace(uni_index(psz)); }

   // bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

    bool is_number(const char * pszUtf8Char);
   //       bool to_numeric_value(const char * pszUtf8Char, float *f);

   inline ECharCategory get_category(i32 i);
   inline i32 get_combining_class(i32 i);
   inline bool is_mirrored(i32 i);

    string get_category_name(const char * pszUtf8Char);
   ECharCategory get_category(const char * pszUtf8Char);

    i32 get_combining_class(const char * pszUtf8Char);
    bool is_mirrored(const char * pszUtf8Char);

    i32 size_of_tables();


   inline  bool is_kanji(i64 i) { return i >= 0x4E00 && i <= 0x9FBF; }
   inline  bool is_hiragana(i64 i) { return i >= 0x3040 && i <= 0x309F; }
   inline  bool is_katakana(i64 i) { return i >= 0x30A0 && i <= 0x30FF; }
   inline  bool is_japanese(i64 i) { return is_kanji(i) || is_hiragana(i) || is_katakana(i); }
   inline  bool is_kanji(const char * pszUtf8) { return is_kanji(uni_index(pszUtf8)); }
   inline  bool is_hiragana(const char * pszUtf8) { return is_hiragana(uni_index(pszUtf8)); }
   inline  bool is_katakana(const char * pszUtf8) { return is_katakana(uni_index(pszUtf8)); }
   inline  bool is_japanese(const char * pszUtf8) { return is_japanese(uni_index(pszUtf8)); }

   void * char_bidi_names_non_usage_warning();

   i32 ref_tables();
   const char * get_category_name(i32 i);

}; //  class ch


