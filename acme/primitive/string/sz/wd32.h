// Refactored by camilo on 2022-11-04 05:47 <3ThomasBorregaardSorensen!!
#pragma once


#define const_wd32char_trigger const ::wd32_character *


inline  constexpr strsize     char_length_to_byte_length(const_wd32char_trigger, strsize nCharLength);
inline  constexpr strsize     byte_length_to_char_length(const_wd32char_trigger, memsize nByteLength);


inline void string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept;
inline void string_count_copy(::wd32_character * pchDest, size_t nDestLen, const ::wd32_character * pchSrc, strsize nChars) noexcept;
inline void overlapped_string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept;


inline ::std::strong_ordering _string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering _string_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering _string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering _case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering _string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;


inline ::std::strong_ordering string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering case_insensitive_string_order(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
inline ::std::strong_ordering string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
inline ::std::strong_ordering case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;


inline strsize string_get_length(const ::wd32_character * psz) noexcept;
inline strsize string_get_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept;
inline strsize string_safe_length(const ::wd32_character * psz) noexcept;
inline strsize string_safe_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept;
inline ::wd32_character * string_lowercase(::wd32_character * psz, strsize size) noexcept;


inline const ::wd32_character * string_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
inline const ::wd32_character * string_rear_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
//inline const ::wd32_character * string_rear_find_character(const ::wd32_character * psz, ::wd32_character ch, strsize iStart) noexcept;
inline const ::wd32_character * string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;
inline const ::wd32_character * string_rear_find_string(const ::wd32_character * psz, const ::wd32_character * pszFind) noexcept;
inline const ::wd32_character * string_find_string_ci(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;


inline ::wd32_character character_tolower(::wd32_character wd32ch) noexcept;
inline ::wd32_character character_toupper(::wd32_character wd32ch) noexcept;


inline bool character_isalpha(::wd32_character ansich) noexcept;
inline bool character_isalnum(::wd32_character ansich) noexcept;
inline bool character_isdigit(::wd32_character ansich) noexcept;
inline bool character_isspace(::wd32_character ansich) noexcept;



inline ::wd32_character * string_reverse(::wd32_character * psz) noexcept;
inline ::wd32_character * string_uppercase(::wd32_character * psz, strsize size) noexcept;


inline strsize string_span_including(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;
inline strsize string_span_excluding(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;


inline strsize get_formatted_length(const ::wd32_character * pszFormat, va_list args) noexcept;
inline strsize wd32string_format(::wd32_character * pszBuffer, strsize nlength, const ::wd32_character * pszFormat, va_list args) noexcept;
inline void  flood_characters(::wd32_character * psz, ::wd32_character ch, strsize len) noexcept;


inline strsize unichar_count(const ::wd32_character * pstr);




CLASS_DECL_ACME ::i64 string_to_signed(const ::wd32_character * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const ::wd32_character * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ::wd32_character * psz);






