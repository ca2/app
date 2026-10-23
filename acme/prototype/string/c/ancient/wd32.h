#pragma once

#include "character_string.h"


CLASS_DECL_ACME ::wd32_character * __u64towd32(::u64 u, ::wd32_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wd32_character *& end);
CLASS_DECL_ACME ::wd32_character * __i64towd32(::i64 i, ::wd32_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wd32_character *& end);

// Compatibility forwarding layer for the ancient ca2 character API.
// Implementations live in ::character_string and are code-unit based.
// Case conversion/classification is intentionally ASCII-only.

inline ::wd32_character __wd32charlowered(::i32 i) noexcept
{
   return ::character_string::character_lowered(static_cast < ::wd32_character >(i));
}

inline ::wd32_character __wd32charuppered(::i32 i) noexcept
{
   return ::character_string::character_uppered(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charisdigit(::i32 i) noexcept
{
   return ::character_string::character_isdigit(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charisalpha(::i32 i) noexcept
{
   return ::character_string::character_isalpha(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charisalnum(::i32 i) noexcept
{
   return ::character_string::character_isalnum(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charisspace(::i32 i) noexcept
{
   return ::character_string::character_isspace(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charisxdigit(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wd32_character >(i));
}

inline ::i32 __wd32charishexadecimal(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wd32_character >(i));
}

inline character_count __wd32len(const ::wd32_character * psz) noexcept
{
   return ::character_string::length(psz);
}

inline ::wd32_character * __wd32cat(::wd32_character * pszTarget, const ::wd32_character * pszConcat) noexcept
{
   return ::character_string::concatenate(pszTarget, pszConcat);
}

inline ::wd32_character * __wd32cpy(::wd32_character * pszDst, const ::wd32_character * pszSrc) noexcept
{
   return ::character_string::copy(pszDst, pszSrc);
}

inline ::wd32_character * __wd32ncpy(::wd32_character * pszDst, const ::wd32_character * pszSrc, character_count len) noexcept
{
   return ::character_string::copy_count(pszDst, pszSrc, len);
}

inline const ::wd32_character * __wd32chr(const ::wd32_character * psz, ::wd32_character ch) noexcept
{
   return ::character_string::find_character(psz, ch);
}

inline ::wd32_character * __wd32pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) noexcept
{
   return ::character_string::find_any_character(psz, pszCharsToFind);
}

inline ::wd32_character * __wd32tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) noexcept
{
   return ::character_string::tokenize_reentrant(psz, sep, state);
}

inline const ::wd32_character * __wd32rchr(const ::wd32_character * psz, ::wd32_character ch) noexcept
{
   return ::character_string::find_character_reverse(psz, ch);
}

inline ::i32 __wd32cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::compare(psz1, psz2);
}

inline ::i32 __wd32ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count(psz1, psz2, count);
}

inline const ::wd32_character * __wd32str(const ::wd32_character * psz, const ::wd32_character * pszFind) noexcept
{
   return ::character_string::find_string(psz, pszFind);
}

inline ::wd32_character __wd32tolower(::wd32_character ch) noexcept
{
   return ::character_string::to_lower(ch);
}

inline ::wd32_character __wd32toupper(::wd32_character ch) noexcept
{
   return ::character_string::to_upper(ch);
}

inline ::wd32_character * __wd32lwr(::wd32_character * psz) noexcept
{
   return ::character_string::make_lower(psz);
}

inline ::wd32_character * __wd32lwr_s(::wd32_character * psz, character_count count) noexcept
{
   return ::character_string::make_lower_count(psz, count);
}

inline ::wd32_character * __wd32upr(::wd32_character * psz) noexcept
{
   return ::character_string::make_upper(psz);
}

inline ::wd32_character * __wd32upr_s(::wd32_character * psz, character_count count) noexcept
{
   return ::character_string::make_upper_count(psz, count);
}

inline const ::wd32_character * __wd32ichr(const ::wd32_character * psz, ::wd32_character ch) noexcept
{
   return ::character_string::find_character_case_insensitive(psz, ch);
}

inline ::i32 __wd32icmp(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::compare_case_insensitive(psz1, psz2);
}

inline ::i32 __wd32nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count_case_insensitive(psz1, psz2, count);
}

inline const ::wd32_character * __wd32istr(const ::wd32_character * psz, const ::wd32_character * pszFind) noexcept
{
   return ::character_string::find_string_case_insensitive(psz, pszFind);
}

inline ::wd32_character * overlap_safe_wd32ncpy(::wd32_character * pszDst, const ::wd32_character * pszSrc, character_count count) noexcept
{
   return ::character_string::overlap_safe_copy_count(pszDst, pszSrc, count);
}

inline ::i32 __wd32coll(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::collate(psz1, psz2);
}

inline ::i32 __wd32ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count(psz1, psz2, count);
}

inline ::i32 __wd32icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::collate_case_insensitive(psz1, psz2);
}

inline ::i32 __wd32nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count_case_insensitive(psz1, psz2, count);
}

inline character_count __wd32spn(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::span_including(psz1, psz2);
}

inline character_count __wd32cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) noexcept
{
   return ::character_string::span_excluding(psz1, psz2);
}

inline ::i64 __wd32toi64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_64(psz, ppszEnd, iBase);
}

inline ::u64 __wd32tou64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_64(psz, ppszEnd, iBase);
}

inline ::i32 __wd32toi32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_32(psz, ppszEnd, iBase);
}

inline ::u32 __wd32tou32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_32(psz, ppszEnd, iBase);
}
