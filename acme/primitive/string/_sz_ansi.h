// Refactored by camilo on 2022-11-04 05:50 <3ThomasBorregaardSorensen!!
#pragma once


#define const_ansichar_trigger const ansichar *


inline  constexpr strsize     char_length_to_byte_length(const_ansichar_trigger, strsize nCharLength);
inline  constexpr strsize     byte_length_to_char_length(const_ansichar_trigger, memsize nByteLength);


inline void copy_chars(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept;
inline void copy_chars(ansichar * pchDest, size_t nDestLen, const ansichar * pchSrc, strsize nChars) noexcept;
inline void copy_chars_overlapped(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept;




inline i32 string_compare(const ansichar * pszA, const ansichar * pszB) noexcept;
inline i32 string_compare_ci(const ansichar * pszA, const ansichar * pszB) noexcept;
inline i32 string_count_compare(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
inline i32 string_count_compare_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
inline i32 string_collate(const ansichar * pszA, const ansichar * pszB) noexcept;
inline i32 string_collate_ci(const ansichar * pszA, const ansichar * pszB) noexcept;
inline i32 string_n_collate(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
inline i32 string_n_collate_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
inline strsize string_get_length(const ansichar * psz) noexcept;
inline strsize string_safe_length(const ansichar * psz) noexcept;
inline ansichar * string_lowercase(ansichar * psz, strsize size) noexcept;



inline const ansichar * string_find_char(const ansichar * pszBlock, ansichar chMatch) noexcept;
inline const ansichar * string_find_string_reverse(const ansichar * psz, const ansichar * pszFind, strsize iStart) noexcept;
inline const ansichar * string_find_char_reverse(const ansichar * psz, ansichar ch, strsize iStart) noexcept;
inline const ansichar * string_find_string(const ansichar * pszBlock, const ansichar * pszMatch) noexcept;



inline ansichar character_tolower(ansichar ansich) noexcept;
inline ansichar character_toupper(ansichar ansich) noexcept;


inline bool character_isalpha(ansichar ansich) noexcept;
inline bool character_isalnum(ansichar ansich) noexcept;
inline bool character_isdigit(ansichar ansich) noexcept;
inline bool character_isspace(ansichar ansich) noexcept;


inline ansichar * string_uppercase(ansichar * psz, strsize size) noexcept;
inline ansichar * string_reverse(ansichar * psz) noexcept;



inline strsize string_span_including(const ansichar * pszBlock, const ansichar * pszSet) noexcept;
inline strsize string_span_excluding(const ansichar * pszBlock, const ansichar * pszSet) noexcept;


inline strsize get_formatted_length(const ansichar * pszFormat, va_list args) noexcept;
inline strsize string_format(ansichar * pszBuffer, strsize nlength, const ansichar * pszFormat, va_list args) noexcept;
inline void  flood_characters(ansichar * psz, ansichar ch, strsize len) noexcept;

inline strsize unichar_count(const ansichar * pstr);


CLASS_DECL_ACME ::i64 string_to_signed(const ansichar * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const ansichar * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ansichar * psz);



