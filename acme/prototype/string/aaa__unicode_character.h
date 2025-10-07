#pragma

// return number of characters need to be consumed to parse a Unicode Character
inline int unicode_len(const ::ansi_character * pszChar);
inline int unicode_len(const ::wd16_character * pszChar) { return utf16_is_1st_surrogate(*pszChar) ? 2 : 1; }
inline int unicode_len(const ::wd32_character * pszChar) { return 1; }


inline int ansichar_unicode_len(::wd32_character i);
inline int wd16char_unicode_len(::wd32_character i) { return utf32_is_surrogated(i) ? 2 : 1; }
inline int wd32char_unicode_len(::wd32_character i) { return 1; }

// return number of characters needed to represent the Unicode Character
inline int char_unicode_len(const ::ansi_character *, ::wd32_character i) { return ansichar_unicode_len(i); }
inline int char_unicode_len(const ::wd16_character *, ::wd32_character i) { return wd16char_unicode_len(i); }
inline int char_unicode_len(const ::wd32_character *, ::wd32_character i) { return wd32char_unicode_len(i); }





inline bool unicode_is_whitespace(int i);
inline bool unicode_is_space_char(int i);
inline int unicode_to_lower_case(int i);
inline int unicode_to_upper_case(int i);
inline int unicode_to_title_case(int i);
inline int unicode_to_numeric_value(int i, float * f);


inline bool unicode_is_lower_case(int iUniIndex);
inline bool unicode_is_upper_case(int iUniIndex);
inline bool unicode_is_title_case(int iUniIndex);
inline bool unicode_is_letter(int iUniIndex);
inline bool unicode_is_letter_or_digit(int iUniIndex);
inline bool unicode_is_digit(int iUniIndex);
inline bool unicode_is_number(int iUniIndex);
inline bool unicode_is_assigned(int iUniIndex);
inline bool unicode_is_space_char(int iUniIndex);


// bool is_whitespace(const ::scoped_string & scopedstrUtf8Char, const ::ansi_character * pszEnd);

bool unicode_is_number(const ::scoped_string & scopedstrUtf8Char);
//       bool to_numeric_value(const ::scoped_string & scopedstrUtf8Char, float *f);

inline ECharCategory unicode_get_category(int i);
inline int unicode_get_combining_class(int i);
inline bool unicode_is_mirrored(int i);

string unicode_get_category_name(const ::scoped_string & scopedstrUtf8Char);
ECharCategory unicode_get_category(const ::scoped_string & scopedstrUtf8Char);

int unicode_get_combining_class(const ::scoped_string & scopedstrUtf8Char);
bool unicode_is_mirrored(const ::scoped_string & scopedstrUtf8Char);

int unicode_size_of_tables();


inline  bool unicode_is_kanji(long long i) { return i >= 0x4E00 && i <= 0x9FBF; }
inline  bool unicode_is_hiragana(long long i) { return i >= 0x3040 && i <= 0x309F; }
inline  bool unicode_is_katakana(long long i) { return i >= 0x30A0 && i <= 0x30FF; }
inline  bool unicode_is_japanese(long long i) { return unicode_is_kanji(i) || unicode_is_hiragana(i) || unicode_is_katakana(i); }
inline  bool unicode_is_kanji(const ::scoped_string & scopedstrUtf8) { return unicode_is_kanji(unicode_index(scopedstrUtf8)); }
inline  bool unicode_is_hiragana(const ::scoped_string & scopedstrUtf8) { return unicode_is_hiragana(unicode_index(scopedstrUtf8)); }
inline  bool unicode_is_katakana(const ::scoped_string & scopedstrUtf8) { return unicode_is_katakana(unicode_index(scopedstrUtf8)); }
inline  bool unicode_is_japanese(const ::scoped_string & scopedstrUtf8) { return unicode_is_japanese(unicode_index(scopedstrUtf8)); }

void * unicode_char_bidi_names_non_usage_warning();

int unicode_ref_tables();
const char * unicode_get_category_name(int i);



