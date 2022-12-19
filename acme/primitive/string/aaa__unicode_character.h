#pragma

// return number of characters need to be consumed to parse a Unicode Character
inline i32 unicode_len(const ::ansi_character * pszChar);
inline i32 unicode_len(const ::wd16_character * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
inline i32 unicode_len(const ::wd32_character * pszChar) { return 1; }


inline i32 ansichar_unicode_len(::wd32_character i);
inline i32 wd16char_unicode_len(::wd32_character i) { return utf32_is_surrogated(i) ? 2 : 1; }
inline i32 wd32char_unicode_len(::wd32_character i) { return 1; }

// return number of characters needed to represent the Unicode Character
inline i32 char_unicode_len(const ::ansi_character *, ::wd32_character i) { return ansichar_unicode_len(i); }
inline i32 char_unicode_len(const ::wd16_character *, ::wd32_character i) { return wd16char_unicode_len(i); }
inline i32 char_unicode_len(const ::wd32_character *, ::wd32_character i) { return wd32char_unicode_len(i); }





inline bool unicode_is_whitespace(i32 i);
inline bool unicode_is_space_char(i32 i);
inline i32 unicode_to_lower_case(i32 i);
inline i32 unicode_to_upper_case(i32 i);
inline i32 unicode_to_title_case(i32 i);
inline i32 unicode_to_numeric_value(i32 i, float * f);


inline bool unicode_is_lower_case(::i32 iUniIndex);
inline bool unicode_is_upper_case(::i32 iUniIndex);
inline bool unicode_is_title_case(::i32 iUniIndex);
inline bool unicode_is_letter(::i32 iUniIndex);
inline bool unicode_is_letter_or_digit(::i32 iUniIndex);
inline bool unicode_is_digit(::i32 iUniIndex);
inline bool unicode_is_number(::i32 iUniIndex);
inline bool unicode_is_assigned(::i32 iUniIndex);
inline bool unicode_is_space_char(::i32 iUniIndex);


// bool is_whitespace(const scoped_string & strUtf8Char, const scoped_string & strEnd);

bool unicode_is_number(const scoped_string & strUtf8Char);
//       bool to_numeric_value(const scoped_string & strUtf8Char, float *f);

inline ECharCategory unicode_get_category(i32 i);
inline i32 unicode_get_combining_class(i32 i);
inline bool unicode_is_mirrored(i32 i);

string unicode_get_category_name(const scoped_string & strUtf8Char);
ECharCategory unicode_get_category(const scoped_string & strUtf8Char);

i32 unicode_get_combining_class(const scoped_string & strUtf8Char);
bool unicode_is_mirrored(const scoped_string & strUtf8Char);

i32 unicode_size_of_tables();


inline  bool unicode_is_kanji(i64 i) { return i >= 0x4E00 && i <= 0x9FBF; }
inline  bool unicode_is_hiragana(i64 i) { return i >= 0x3040 && i <= 0x309F; }
inline  bool unicode_is_katakana(i64 i) { return i >= 0x30A0 && i <= 0x30FF; }
inline  bool unicode_is_japanese(i64 i) { return unicode_is_kanji(i) || unicode_is_hiragana(i) || unicode_is_katakana(i); }
inline  bool unicode_is_kanji(const scoped_string & strUtf8) { return unicode_is_kanji(unicode_index(pszUtf8)); }
inline  bool unicode_is_hiragana(const scoped_string & strUtf8) { return unicode_is_hiragana(unicode_index(pszUtf8)); }
inline  bool unicode_is_katakana(const scoped_string & strUtf8) { return unicode_is_katakana(unicode_index(pszUtf8)); }
inline  bool unicode_is_japanese(const scoped_string & strUtf8) { return unicode_is_japanese(unicode_index(pszUtf8)); }

void * unicode_char_bidi_names_non_usage_warning();

i32 unicode_ref_tables();
const char * unicode_get_category_name(i32 i);



