// Refactored by camilo on 2022-11-04 05:47 <3ThomasBorregaardSorensen!!
#pragma once


#define const_wd32char_trigger const wd32char *


inline  constexpr strsize     char_length_to_byte_length(const_wd32char_trigger, strsize nCharLength);
inline  constexpr strsize     byte_length_to_char_length(const_wd32char_trigger, memsize nByteLength);


inline void copy_chars(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept;
inline void copy_chars(wd32char * pchDest, size_t nDestLen, const wd32char * pchSrc, strsize nChars) noexcept;
inline void copy_chars_overlapped(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept;



inline i32 string_compare(const wd32char * pszA, const wd32char * pszB) noexcept;
inline i32 string_compare_ci(const wd32char * pszA, const wd32char * pszB) noexcept;
inline i32 string_count_compare(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
inline i32 string_count_compare_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
inline i32 string_collate(const wd32char * pszA, const wd32char * pszB) noexcept;
inline i32 string_collate_ci(const wd32char * pszA, const wd32char * pszB) noexcept;
inline i32 string_n_collate(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
inline i32 string_n_collate_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
inline strsize string_get_length(const wd32char * psz) noexcept;
inline strsize string_safe_length(const wd32char * psz) noexcept;
inline wd32char * string_lowercase(wd32char * psz, strsize size) noexcept;


inline const wd32char * string_find_char(const wd32char * pszBlock, wd32char chMatch) noexcept;
inline const wd32char * string_find_string_reverse(const wd32char * psz, const wd32char * pszFind, strsize iStart) noexcept;
inline const wd32char * string_find_char_reverse(const wd32char * psz, wd32char ch, strsize iStart) noexcept;
inline const wd32char * string_find_string(const wd32char * pszBlock, const wd32char * pszMatch) noexcept;


inline wd32char character_tolower(wd32char wd32ch) noexcept;
inline wd32char character_toupper(wd32char wd32ch) noexcept;


inline bool character_isalpha(wd32char ansich) noexcept;
inline bool character_isalnum(wd32char ansich) noexcept;
inline bool character_isdigit(wd32char ansich) noexcept;
inline bool character_isspace(wd32char ansich) noexcept;



inline wd32char * string_reverse(wd32char * psz) noexcept;
inline wd32char * string_uppercase(wd32char * psz, strsize size) noexcept;


inline strsize string_span_including(const wd32char * pszBlock, const wd32char * pszSet) noexcept;
inline strsize string_span_excluding(const wd32char * pszBlock, const wd32char * pszSet) noexcept;


inline strsize get_formatted_length(const wd32char * pszFormat, va_list args) noexcept;
inline strsize string_format(wd32char * pszBuffer, strsize nlength, const wd32char * pszFormat, va_list args) noexcept;
inline void  flood_characters(wd32char * psz, wd32char ch, strsize len) noexcept;


inline strsize unichar_count(const wd32char * pstr);




CLASS_DECL_ACME ::i64 string_to_signed(const wd32char * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const wd32char * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const wd32char * psz);






