// Refactored by camilo on 2022-11-04 05:50 <3ThomasBorregaardSorensen!!
#pragma once


#include <stdarg.h>
#include <string.h>

#define const_ansichar_trigger const ::ansi_character *


template < primitive_character CHARACTER >
CLASS_DECL_ACME constexpr memsize character_count_to_byte_length(const CHARACTER * pszTrigger, character_count nCharLength)
{
 
   return (::memsize)((nCharLength) * sizeof(CHARACTER));

}


template < primitive_character CHARACTER >
CLASS_DECL_ACME constexpr memsize character_count_to_byte_length_constrain_source_length(const CHARACTER * pszTrigger, character_count nCharLength)
{

   return (::memsize)::minimum((nCharLength) * sizeof(CHARACTER), (string_get_length(pszTrigger) + 1) * sizeof(CHARACTER));

}


template < primitive_character CHARACTER >
CLASS_DECL_ACME constexpr character_count byte_length_to_character_count(const CHARACTER * pszTrigger, memsize nByteLength)
{

   return (::character_count)((nByteLength / sizeof(CHARACTER)));

}


template < primitive_character CHARACTER >
CLASS_DECL_ACME constexpr memsize null_terminated_character_count_to_byte_length(const CHARACTER * pszTrigger, character_count nCharLength)
{
 
   return (::memsize)((nCharLength + 1) * sizeof(CHARACTER));

}


template < primitive_character CHARACTER >
constexpr character_count null_terminated_byte_length_to_character_count(const CHARACTER * pszTrigger, memsize nByteLength)
{

   return (::character_count)((nByteLength / sizeof(CHARACTER)) - 1);

}


CLASS_DECL_ACME void string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void string_count_copy(::ansi_character * pchDest, size_t nDestLen, const ::ansi_character * pchSrc, character_count nChars) noexcept;
CLASS_DECL_ACME void overlapped_string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, character_count nChars) noexcept;


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;


CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::ansi_character * pszA, character_count sizeA, const ::ansi_character * pszB, character_count sizeB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::ansi_character * pszA, character_count sizeA, const ::ansi_character * pszB, character_count sizeB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept;
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, character_count len) noexcept;



inline ::std::strong_ordering _string_count_compare(const ::ansi_character* pszA, const ::ansi_character* pszB, character_count len) noexcept { return strncmp(pszA, pszB, len)<=>0; }

#if defined(__BSD__)
inline ::std::strong_ordering _case_insensitive_string_count_compare(const ::ansi_character* pszA, const ::ansi_character* pszB, character_count len) noexcept { return strncasecmp(pszA, pszB, len)<=>0; }
#else
inline ::std::strong_ordering _case_insensitive_string_count_compare(const ::ansi_character* pszA, const ::ansi_character* pszB, character_count len) noexcept { return strnicmp(pszA, pszB, len)<=>0; }
#endif

inline bool string_equals(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept{return string_compare(pszA, pszB) == 0; }

CLASS_DECL_ACME character_count string_get_length(const ::ansi_character * psz) noexcept;
CLASS_DECL_ACME character_count string_get_length(const ::ansi_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME character_count string_safe_length(const ::ansi_character * psz) noexcept;
CLASS_DECL_ACME character_count string_safe_length(const ::ansi_character* psz, character_count sizeMaximumInterest) noexcept;
CLASS_DECL_ACME ::ansi_character * string_lowercase(::ansi_character * psz, character_count size) noexcept;



CLASS_DECL_ACME const ::ansi_character * string_find_character(const ::ansi_character * pszBlock, ::ansi_character chMatch) noexcept;
CLASS_DECL_ACME const ::ansi_character * string_find_character(const ::ansi_character * psz, const ::ansi_character * pszEnd, ::ansi_character chMatch) noexcept;
CLASS_DECL_ACME const ::ansi_character * string_rear_find_character(const ::ansi_character * psz, ::ansi_character ch) noexcept;
CLASS_DECL_ACME const ::ansi_character * string_find_string(const ::ansi_character * pszBlock, const ::ansi_character * pszMatch) noexcept;
CLASS_DECL_ACME const ::ansi_character * string_rear_find_string(const ::ansi_character * psz, const ::ansi_character * pszFind, character_count iStart) noexcept;
CLASS_DECL_ACME const ::ansi_character * case_insensitive_string_find_string(const ::ansi_character * pszBlock, const ::ansi_character * pszMatch) noexcept;


CLASS_DECL_ACME ::ansi_character character_tolower(::ansi_character ansich) noexcept;
CLASS_DECL_ACME ::ansi_character character_toupper(::ansi_character ansich) noexcept;





CLASS_DECL_ACME ::ansi_character character_tolower(::ansi_character ansich) noexcept;
CLASS_DECL_ACME ::ansi_character character_toupper(::ansi_character ansich) noexcept;


CLASS_DECL_ACME bool character_isalpha(::ansi_character ansich) noexcept;
CLASS_DECL_ACME bool character_isalnum(::ansi_character ansich) noexcept;
CLASS_DECL_ACME bool character_isdigit(::ansi_character ansich) noexcept;
CLASS_DECL_ACME bool character_isspace(::ansi_character ansich) noexcept;
CLASS_DECL_ACME bool character_isupper(::ansi_character ansich) noexcept;


CLASS_DECL_ACME bool character_isxdigit(::ansi_character ansich) noexcept;


CLASS_DECL_ACME ::ansi_character * string_uppercase(::ansi_character * psz, character_count size) noexcept;
CLASS_DECL_ACME ::ansi_character * string_reverse(::ansi_character * psz) noexcept;



CLASS_DECL_ACME character_count string_skip_any_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept;
CLASS_DECL_ACME character_count string_find_first_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept;


CLASS_DECL_ACME character_count get_formatted_length(const ::ansi_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME character_count _string_format(::ansi_character * pszBuffer, character_count nlength, const ::ansi_character * pszFormat, va_list args) noexcept;
CLASS_DECL_ACME void  flood_characters(::ansi_character * psz, ::ansi_character ch, character_count len) noexcept;

CLASS_DECL_ACME character_count unichar_count(const ::ansi_character * pstr);


CLASS_DECL_ACME long long string_to_signed(const ::ansi_character * psz);
CLASS_DECL_ACME unsigned long long as_unsigned_long_long(const ::ansi_character * psz);
CLASS_DECL_ACME double string_to_floating(const ::ansi_character * psz);



