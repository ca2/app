// Refactored by camilo on 2022-11-04 05:50 <3ThomasBorregaardSorensen!!
#pragma once


#define const_ansichar_trigger const ::ansi_character *


inline  constexpr strsize     char_length_to_byte_length(const_ansichar_trigger, strsize nCharLength);
inline  constexpr strsize     byte_length_to_char_length(const_ansichar_trigger, memsize nByteLength);


inline void string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, strsize nChars) noexcept;
inline void string_count_copy(::ansi_character * pchDest, size_t nDestLen, const ::ansi_character * pchSrc, strsize nChars) noexcept;
inline void overlapped_string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, strsize nChars) noexcept;


inline ::std::strong_ordering _string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering _string_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering _string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _string_count_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering _case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering _string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;


inline ::std::strong_ordering string_compare(const ::ansi_character * pszA, strsize sizeA, const ::ansi_character * pszB, strsize sizeB) noexcept;
inline ::std::strong_ordering case_insensitive_string_order(const ::ansi_character * pszA, strsize sizeA, const ::ansi_character * pszB, strsize sizeB) noexcept;
inline ::std::strong_ordering string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering case_insensitive_string_order(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering string_count_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
inline ::std::strong_ordering string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept;


inline strsize string_get_length(const ::ansi_character * psz) noexcept;
inline strsize string_get_length(const ::ansi_character* psz, strsize sizeMaximumInterest) noexcept;
inline strsize string_safe_length(const ::ansi_character * psz) noexcept;
inline strsize string_safe_length(const ::ansi_character* psz, strsize sizeMaximumInterest) noexcept;
inline ::ansi_character * string_lowercase(::ansi_character * psz, strsize size) noexcept;



inline const ::ansi_character * string_find_character(const ::ansi_character * pszBlock, ::ansi_character chMatch) noexcept;
inline const ::ansi_character * string_rear_find_character(const ::ansi_character * psz, ::ansi_character ch) noexcept;
inline const ::ansi_character * string_find_string(const ::ansi_character * pszBlock, const ::ansi_character * pszMatch) noexcept;
inline const ::ansi_character * string_rear_find_string(const ::ansi_character * psz, const ::ansi_character * pszFind, strsize iStart) noexcept;



inline ::ansi_character character_tolower(::ansi_character ansich) noexcept;
inline ::ansi_character character_toupper(::ansi_character ansich) noexcept;


inline bool character_isalpha(::ansi_character ansich) noexcept;
inline bool character_isalnum(::ansi_character ansich) noexcept;
inline bool character_isdigit(::ansi_character ansich) noexcept;
inline bool character_isspace(::ansi_character ansich) noexcept;


inline ::ansi_character * string_uppercase(::ansi_character * psz, strsize size) noexcept;
inline ::ansi_character * string_reverse(::ansi_character * psz) noexcept;



inline strsize string_skip_any_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept;
inline strsize string_find_first_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept;


inline strsize get_formatted_length(const ::ansi_character * pszFormat, va_list args) noexcept;
inline strsize ansistring_format(::ansi_character * pszBuffer, strsize nlength, const ::ansi_character * pszFormat, va_list args) noexcept;
inline void  flood_characters(::ansi_character * psz, ::ansi_character ch, strsize len) noexcept;

inline strsize unichar_count(const ::ansi_character * pstr);


CLASS_DECL_ACME ::i64 string_to_signed(const ::ansi_character * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const ::ansi_character * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ::ansi_character * psz);



