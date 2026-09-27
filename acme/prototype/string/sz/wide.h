// Refactored by camilo on 2022-11-04 05:47 <3ThomasBorregaardSorensen!!
#pragma once


#define const_widechar_trigger const ::wide_character *


//CLASS_DECL_ACME  constexpr character_count     character_count_to_byte_length(const_widechar_trigger, character_count nCharLength);
//CLASS_DECL_ACME  constexpr character_count     byte_length_to_character_count(const_widechar_trigger, memsize nByteLength);


CLASS_DECL_ACME void string_count_copy(::wide_character * pchDest, const ::wide_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void string_count_copy(::wide_character * pchDest, size_t nDestLen, const ::wide_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void overlapped_string_count_copy(::wide_character * pchDest, const ::wide_character * pchSrc, character_count nChars) noexcept;


CLASS_DECL_ACME ::i32 _string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::i32 case_insensitive__string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::i32 _string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::i32 case_insensitive__string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;


CLASS_DECL_ACME ::i32 string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::i32 case_insensitive_string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::i32 string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::i32 case_insensitive_string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept;

inline ::i32 _string_count_compare(const ::wide_character* pszA, const ::wide_character* pszB, character_count len) noexcept { return string_count_compare(pszA, pszB, len); }
inline ::i32 _case_insensitive_string_count_compare(const ::wide_character* pszA, const ::wide_character* pszB, character_count len) noexcept { return case_insensitive_string_count_compare(pszA, pszB, len); }

CLASS_DECL_ACME character_count string_get_length(const ::wide_character * psz) noexcept;
CLASS_DECL_ACME character_count string_get_length2(const ::wide_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME character_count string_safe_length(const ::wide_character * psz) noexcept;
CLASS_DECL_ACME character_count string_safe_length2(const ::wide_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME ::wide_character * string_lowercase(::wide_character * psz, character_count size) noexcept;


CLASS_DECL_ACME const ::wide_character * string_find_character(const ::wide_character * pszBlock, ::wide_character chMatch) noexcept;
CLASS_DECL_ACME const ::wide_character * string_find_character(const ::wide_character * psz, const ::wide_character * pszEnd, ::wide_character chMatch) noexcept;
CLASS_DECL_ACME const ::wide_character * string_rear_find_character(const ::wide_character * pszBlock, ::wide_character chMatch) noexcept;
//CLASS_DECL_ACME const ::wide_character * string_rear_find_character(const ::wide_character * psz, ::wide_character ch, character_count iStart) noexcept;
CLASS_DECL_ACME const ::wide_character * string_find_string(const ::wide_character * pszBlock, const ::wide_character * pszMatch) noexcept;
CLASS_DECL_ACME const ::wide_character * string_rear_find_string(const ::wide_character * psz, const ::wide_character * pszFind) noexcept;
CLASS_DECL_ACME const ::wide_character * case_insensitive_string_find_string(const ::wide_character * pszBlock, const ::wide_character * pszMatch) noexcept;


CLASS_DECL_ACME ::wide_character character_tolower(::wide_character widech) noexcept;
CLASS_DECL_ACME ::wide_character character_toupper(::wide_character widech) noexcept;


CLASS_DECL_ACME bool character_isalpha(::wide_character ansich) noexcept;
CLASS_DECL_ACME bool character_isalnum(::wide_character ansich) noexcept;
CLASS_DECL_ACME bool character_isdigit(::wide_character ansich) noexcept;
CLASS_DECL_ACME bool character_isspace(::wide_character ansich) noexcept;


CLASS_DECL_ACME bool character_isxdigit(::wide_character ansich) noexcept;


CLASS_DECL_ACME ::wide_character * string_reverse(::wide_character * psz) noexcept;
CLASS_DECL_ACME ::wide_character * string_uppercase(::wide_character * psz, character_count size) noexcept;


CLASS_DECL_ACME character_count string_skip_any_character_in(const ::wide_character * pszBlock, const ::wide_character * pszSet) noexcept;
CLASS_DECL_ACME character_count string_find_first_character_in(const ::wide_character * pszBlock, const ::wide_character * pszSet) noexcept;


CLASS_DECL_ACME character_count get_formatted_length(const ::wide_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME character_count _string_format(::wide_character * pszBuffer, character_count nlength, const ::wide_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME void  flood_characters(::wide_character * psz, ::wide_character ch, character_count len) noexcept;


CLASS_DECL_ACME character_count unichar_count(const ::wide_character * pstr);




CLASS_DECL_ACME ::i64 string_to_signed(const ::wide_character * psz);
CLASS_DECL_ACME ::u64 as_u64(const ::wide_character * psz);
CLASS_DECL_ACME ::f64 string_to_floating(const ::wide_character * psz);







