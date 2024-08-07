// Refactored by camilo on 2022-11-04 05:49 <3ThomasBorregaardSorensen!!
#pragma once


#define const_wd16char_trigger const ::wd16_character *




//CLASS_DECL_ACME  constexpr strsize     character_count_to_byte_length(const_wd16char_trigger, strsize nCharLength);
//CLASS_DECL_ACME  constexpr strsize     byte_length_to_character_count(const_wd16char_trigger, memsize nByteLength);



CLASS_DECL_ACME void string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, strsize nChars) noexcept;
CLASS_DECL_ACME void string_count_copy(::wd16_character * pchDest, size_t nDestLen, const ::wd16_character * pchSrc, strsize nChars) noexcept;
CLASS_DECL_ACME void overlapped_string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, strsize nChars) noexcept;


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;


CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept;

CLASS_DECL_ACME strsize string_get_length(const ::wd16_character * psz) noexcept;
CLASS_DECL_ACME strsize string_get_length(const ::wd16_character* psz, strsize sizeMaximumInterest) noexcept;
CLASS_DECL_ACME strsize string_safe_length(const ::wd16_character * psz) noexcept;
CLASS_DECL_ACME strsize string_safe_length(const ::wd16_character* psz, strsize sizeMaximumInterest) noexcept;
CLASS_DECL_ACME ::wd16_character * string_lowercase(::wd16_character * psz, strsize size) noexcept;


CLASS_DECL_ACME const ::wd16_character * string_find_character(const ::wd16_character * pszBlock, ::wd16_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd16_character * string_find_character(const ::wd16_character * psz, const ::wd16_character * pszEnd, ::wd16_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd16_character * string_rear_find_character(const ::wd16_character * psz, ::wd16_character ch) noexcept;
CLASS_DECL_ACME const ::wd16_character * string_find_string(const ::wd16_character * pszBlock, const ::wd16_character * pszMatch) noexcept;
CLASS_DECL_ACME const ::wd16_character * string_rear_find_string(const ::wd16_character * psz, const ::wd16_character * pszFind, strsize iStart) noexcept;


CLASS_DECL_ACME ::wd16_character character_tolower(::wd16_character wd16ch) noexcept;
CLASS_DECL_ACME ::wd16_character character_toupper(::wd16_character wd16ch) noexcept;


CLASS_DECL_ACME bool character_isalpha(::wd16_character ansich) noexcept;
CLASS_DECL_ACME bool character_isalnum(::wd16_character ansich) noexcept;
CLASS_DECL_ACME bool character_isdigit(::wd16_character ansich) noexcept;
CLASS_DECL_ACME bool character_isspace(::wd16_character ansich) noexcept;


CLASS_DECL_ACME bool character_isxdigit(::wd16_character ansich) noexcept;


CLASS_DECL_ACME ::wd16_character * string_uppercase(::wd16_character * psz, strsize size) noexcept;
CLASS_DECL_ACME ::wd16_character * string_reverse(::wd16_character * psz) noexcept;


CLASS_DECL_ACME strsize string_skip_any_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept;
CLASS_DECL_ACME strsize string_find_first_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept;


CLASS_DECL_ACME strsize get_formatted_length(const ::wd16_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME strsize _string_format(::wd16_character * pszBuffer, strsize nlength, const ::wd16_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME void  flood_characters(::wd16_character * psz, ::wd16_character ch, strsize len) noexcept;


CLASS_DECL_ACME strsize unichar_count(const ::wd16_character * pstr);



CLASS_DECL_ACME ::i64 string_to_signed(const ::wd16_character * psz);
CLASS_DECL_ACME ::u64 string_to_natural(const ::wd16_character * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ::wd16_character * psz);

