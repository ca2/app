#pragma



//class CLASS_DECL_ACME ch
//{
//
//public:

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

   //inline i32 parse_unicode(const ansichar*& pszChar);
   //inline i32 parse_unicode(const wd16char*& pszChar);
   //inline i32 parse_unicode(const wd32char*& pszChar) { return *pszChar++; }

   // return Unicode Index

   // return number of characters need to be consumed to parse a Unicode Character
   inline i32 unicode_len(const ansichar* pszChar);
   inline i32 unicode_len(const wd16char* pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
   inline i32 unicode_len(const wd32char* pszChar) { return 1; }


   //inline ansichar* increment(ansichar*& pszChar) { return pszChar += unicode_len(pszChar); }
   //inline wd16char* increment(wd16char*& pszChar) { return pszChar += unicode_len(pszChar); }
   //inline wd32char* increment(wd32char*& pszChar) { return pszChar += unicode_len(pszChar); }

   //inline ansichar* decrement(ansichar*& pszChar, ansichar * pszBeg = nullptr) { return unicode_decrement(pszChar, pszBeg); }
   //inline wd16char* decrement(wd16char*& pszChar, wd16char * pszBeg = nullptr) { return unicode_decrement(pszChar, pszBeg); }
   //inline wd32char* decrement(wd32char*& pszChar, wd32char * pszBeg = nullptr) { return unicode_decrement(pszChar, pszBeg); }


   inline i32 ansichar_unicode_len(wd32char i);
   inline i32 wd16char_unicode_len(wd32char i) { return utf32_is_surrogated(i) ? 2 : 1; }
   inline i32 wd32char_unicode_len(wd32char i) { return 1; }

   // return number of characters needed to represent the Unicode Character
   inline i32 char_unicode_len(const ansichar*, wd32char i) { return ansichar_unicode_len(i); }
   inline i32 char_unicode_len(const wd16char*, wd32char i) { return wd16char_unicode_len(i); }
   inline i32 char_unicode_len(const wd32char*, wd32char i) { return wd32char_unicode_len(i); }



   

   inline bool unicode_is_whitespace(i32 i);
   inline bool unicode_is_space_char(i32 i);
   inline i32 unicode_to_lower_case(i32 i);
   inline i32 unicode_to_upper_case(i32 i);
   inline i32 unicode_to_title_case(i32 i);
   inline i32 unicode_to_numeric_value(i32 i, float* f);


   inline bool unicode_is_lower_case(::i32 iUniIndex);
   inline bool unicode_is_upper_case(::i32 iUniIndex);
   inline bool unicode_is_title_case(::i32 iUniIndex);
   inline bool unicode_is_letter(::i32 iUniIndex);
   inline bool unicode_is_letter_or_digit(::i32 iUniIndex);
   inline bool unicode_is_digit(::i32 iUniIndex);
   inline bool unicode_is_number(::i32 iUniIndex);
   inline bool unicode_is_assigned(::i32 iUniIndex);
   inline bool unicode_is_space_char(::i32 iUniIndex);

   //inline bool unicode_is_lower_case(const ansichar* pszChar) { return unicode_is_lower_case(unicode_index(pszChar)); }
   //inline bool unicode_is_upper_case(const ansichar* pszChar) { return unicode_is_upper_case(unicode_index(pszChar)); }
   //inline bool unicode_is_title_case(const ansichar* pszChar) { return unicode_is_title_case(unicode_index(pszChar)); }
   //inline bool unicode_is_letter(const ansichar* pszChar) { return unicode_is_letter(unicode_index(pszChar)); }
   //inline bool unicode_is_letter_or_digit(const ansichar* pszChar) { return unicode_is_letter_or_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_digit(const ansichar* pszChar) { return unicode_is_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_assigned(const ansichar* pszChar) { return unicode_is_assigned(unicode_index(pszChar)); }
   //inline bool unicode_is_space_char(const ansichar* pszChar) { return unicode_is_space_char(unicode_index(pszChar)); }

   //inline bool unicode_is_lower_case(const wd16char* pszChar) { return unicode_is_lower_case(unicode_index(pszChar)); }
   //inline bool unicode_is_upper_case(const wd16char* pszChar) { return unicode_is_upper_case(unicode_index(pszChar)); }
   //inline bool unicode_is_title_case(const wd16char* pszChar) { return unicode_is_title_case(unicode_index(pszChar)); }
   //inline bool unicode_is_letter(const wd16char* pszChar) { return unicode_is_letter(unicode_index(pszChar)); }
   //inline bool unicode_is_letter_or_digit(const wd16char* pszChar) { return unicode_is_letter_or_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_digit(const wd16char* pszChar) { return unicode_is_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_assigned(const wd16char* pszChar) { return unicode_is_assigned(unicode_index(pszChar)); }
   //inline bool unicode_is_space_char(const wd16char* pszChar) { return unicode_is_space_char(unicode_index(pszChar)); }

   //inline bool unicode_is_lower_case(const wd32char* pszChar) { return unicode_is_lower_case(unicode_index(pszChar)); }
   //inline bool unicode_is_upper_case(const wd32char* pszChar) { return unicode_is_upper_case(unicode_index(pszChar)); }
   //inline bool unicode_is_title_case(const wd32char* pszChar) { return unicode_is_title_case(unicode_index(pszChar)); }
   //inline bool unicode_is_letter(const wd32char* pszChar) { return unicode_is_letter(unicode_index(pszChar)); }
   //inline bool unicode_is_letter_or_digit(const wd32char* pszChar) { return unicode_is_letter_or_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_digit(const wd32char* pszChar) { return unicode_is_digit(unicode_index(pszChar)); }
   //inline bool unicode_is_assigned(const wd32char* pszChar) { return unicode_is_assigned(unicode_index(pszChar)); }
   //inline bool unicode_is_space_char(const wd32char* pszChar) { return unicode_is_space_char(unicode_index(pszChar)); }

   
   //{
   //   if (!is_legal_unicode_index(i))
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


   // bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

   bool unicode_is_number(const char* pszUtf8Char);
   //       bool to_numeric_value(const char * pszUtf8Char, float *f);

   inline ECharCategory unicode_get_category(i32 i);
   inline i32 unicode_get_combining_class(i32 i);
   inline bool unicode_is_mirrored(i32 i);

   string unicode_get_category_name(const char* pszUtf8Char);
   ECharCategory unicode_get_category(const char* pszUtf8Char);

   i32 unicode_get_combining_class(const char* pszUtf8Char);
   bool unicode_is_mirrored(const char* pszUtf8Char);

   i32 unicode_size_of_tables();


   inline  bool unicode_is_kanji(i64 i) { return i >= 0x4E00 && i <= 0x9FBF; }
   inline  bool unicode_is_hiragana(i64 i) { return i >= 0x3040 && i <= 0x309F; }
   inline  bool unicode_is_katakana(i64 i) { return i >= 0x30A0 && i <= 0x30FF; }
   inline  bool unicode_is_japanese(i64 i) { return unicode_is_kanji(i) || unicode_is_hiragana(i) || unicode_is_katakana(i); }
   inline  bool unicode_is_kanji(const char* pszUtf8) { return unicode_is_kanji(unicode_index(pszUtf8)); }
   inline  bool unicode_is_hiragana(const char* pszUtf8) { return unicode_is_hiragana(unicode_index(pszUtf8)); }
   inline  bool unicode_is_katakana(const char* pszUtf8) { return unicode_is_katakana(unicode_index(pszUtf8)); }
   inline  bool unicode_is_japanese(const char* pszUtf8) { return unicode_is_japanese(unicode_index(pszUtf8)); }

   void* unicode_char_bidi_names_non_usage_warning();

   i32 unicode_ref_tables();
   const char* unicode_get_category_name(i32 i);

//}; //  class ch


