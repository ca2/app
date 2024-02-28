// Refactored by camilo on 2022-11-04 05:47 <3ThomasBorregaardSorensen!!
#pragma once


#define const_wd32char_trigger const ::wd32_character *


//CLASS_DECL_ACME  constexpr strsize     character_count_to_byte_length(const_wd32char_trigger, strsize nCharLength);
//CLASS_DECL_ACME  constexpr strsize     byte_length_to_character_count(const_wd32char_trigger, memsize nByteLength);


CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept;
CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, size_t nDestLen, const ::wd32_character * pchSrc, strsize nChars) noexcept;
CLASS_DECL_ACME void overlapped_string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept;


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;


CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept;


CLASS_DECL_ACME strsize string_get_length(const ::wd32_character * psz) noexcept;
CLASS_DECL_ACME strsize string_get_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept;
CLASS_DECL_ACME strsize string_safe_length(const ::wd32_character * psz) noexcept;
CLASS_DECL_ACME strsize string_safe_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept;
CLASS_DECL_ACME ::wd32_character * string_lowercase(::wd32_character * psz, strsize size) noexcept;


CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * psz, const ::wd32_character * pszEnd, ::wd32_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_rear_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
//CLASS_DECL_ACME const ::wd32_character * string_rear_find_character(const ::wd32_character * psz, ::wd32_character ch, strsize iStart) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_rear_find_string(const ::wd32_character * psz, const ::wd32_character * pszFind) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_find_string_ci(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;


CLASS_DECL_ACME ::wd32_character character_tolower(::wd32_character wd32ch) noexcept;
CLASS_DECL_ACME ::wd32_character character_toupper(::wd32_character wd32ch) noexcept;


CLASS_DECL_ACME bool character_isalpha(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isalnum(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isdigit(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isspace(::wd32_character ansich) noexcept;


CLASS_DECL_ACME bool character_isxdigit(::wd32_character ansich) noexcept;


CLASS_DECL_ACME ::wd32_character * string_reverse(::wd32_character * psz) noexcept;
CLASS_DECL_ACME ::wd32_character * string_uppercase(::wd32_character * psz, strsize size) noexcept;


CLASS_DECL_ACME strsize string_skip_any_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;
CLASS_DECL_ACME strsize string_find_first_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;


CLASS_DECL_ACME strsize get_formatted_length(const ::wd32_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME strsize _string_format(::wd32_character * pszBuffer, strsize nlength, const ::wd32_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME void  flood_characters(::wd32_character * psz, ::wd32_character ch, strsize len) noexcept;


CLASS_DECL_ACME strsize unichar_count(const ::wd32_character * pstr);




CLASS_DECL_ACME ::i64 string_to_signed(const ::wd32_character * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const ::wd32_character * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ::wd32_character * psz);






