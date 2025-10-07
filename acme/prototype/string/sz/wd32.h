// Refactored by camilo on 2022-11-04 05:47 <3ThomasBorregaardSorensen!!
#pragma once


#define const_wd32char_trigger const ::wd32_character *


//CLASS_DECL_ACME  constexpr character_count     character_count_to_byte_length(const_wd32char_trigger, character_count nCharLength);
//CLASS_DECL_ACME  constexpr character_count     byte_length_to_character_count(const_wd32char_trigger, memsize nByteLength);


CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, size_t nDestLen, const ::wd32_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void overlapped_string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, character_count nChars) noexcept;


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;


CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept;

inline ::std::strong_ordering _string_count_compare(const ::wd32_character* pszA, const ::wd32_character* pszB, character_count len) noexcept { return string_count_compare(pszA, pszB, len); }
inline ::std::strong_ordering _case_insensitive_string_count_compare(const ::wd32_character* pszA, const ::wd32_character* pszB, character_count len) noexcept { return case_insensitive_string_count_compare(pszA, pszB, len); }

CLASS_DECL_ACME character_count string_get_length(const ::wd32_character * psz) noexcept;
CLASS_DECL_ACME character_count string_get_length2(const ::wd32_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME character_count string_safe_length(const ::wd32_character * psz) noexcept;
CLASS_DECL_ACME character_count string_safe_length2(const ::wd32_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME ::wd32_character * string_lowercase(::wd32_character * psz, character_count size) noexcept;


CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * psz, const ::wd32_character * pszEnd, ::wd32_character chMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_rear_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept;
//CLASS_DECL_ACME const ::wd32_character * string_rear_find_character(const ::wd32_character * psz, ::wd32_character ch, character_count iStart) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;
CLASS_DECL_ACME const ::wd32_character * string_rear_find_string(const ::wd32_character * psz, const ::wd32_character * pszFind) noexcept;
CLASS_DECL_ACME const ::wd32_character * case_insensitive_string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept;


CLASS_DECL_ACME ::wd32_character character_tolower(::wd32_character wd32ch) noexcept;
CLASS_DECL_ACME ::wd32_character character_toupper(::wd32_character wd32ch) noexcept;


CLASS_DECL_ACME bool character_isalpha(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isalnum(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isdigit(::wd32_character ansich) noexcept;
CLASS_DECL_ACME bool character_isspace(::wd32_character ansich) noexcept;


CLASS_DECL_ACME bool character_isxdigit(::wd32_character ansich) noexcept;


CLASS_DECL_ACME ::wd32_character * string_reverse(::wd32_character * psz) noexcept;
CLASS_DECL_ACME ::wd32_character * string_uppercase(::wd32_character * psz, character_count size) noexcept;


CLASS_DECL_ACME character_count string_skip_any_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;
CLASS_DECL_ACME character_count string_find_first_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept;


CLASS_DECL_ACME character_count get_formatted_length(const ::wd32_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME character_count _string_format(::wd32_character * pszBuffer, character_count nlength, const ::wd32_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME void  flood_characters(::wd32_character * psz, ::wd32_character ch, character_count len) noexcept;


CLASS_DECL_ACME character_count unichar_count(const ::wd32_character * pstr);




CLASS_DECL_ACME long long string_to_signed(const ::wd32_character * psz);
CLASS_DECL_ACME unsigned long long as_unsigned_long_long(const ::wd32_character * psz);
CLASS_DECL_ACME double string_to_floating(const ::wd32_character * psz);






