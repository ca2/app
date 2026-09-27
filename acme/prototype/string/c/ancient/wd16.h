#pragma once

#include "character_string.h"


CLASS_DECL_ACME ::wd16_character * __u64towd16(::u64 u, ::wd16_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wd16_character *& end);
CLASS_DECL_ACME ::wd16_character * __i64towd16(::i64 i, ::wd16_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wd16_character *& end);

// Compatibility forwarding layer for the ancient ca2 character API.
// Implementations live in ::character_string and are code-unit based.
// Case conversion/classification is intentionally ASCII-only.

inline ::wd16_character __wd16charlowered(::i32 i) noexcept
{
   return ::character_string::character_lowered(static_cast < ::wd16_character >(i));
}

inline ::wd16_character __wd16charuppered(::i32 i) noexcept
{
   return ::character_string::character_uppered(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charisdigit(::i32 i) noexcept
{
   return ::character_string::character_isdigit(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charisalpha(::i32 i) noexcept
{
   return ::character_string::character_isalpha(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charisalnum(::i32 i) noexcept
{
   return ::character_string::character_isalnum(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charisspace(::i32 i) noexcept
{
   return ::character_string::character_isspace(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charisxdigit(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wd16_character >(i));
}

inline ::i32 __wd16charishexadecimal(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wd16_character >(i));
}

inline character_count __wd16len(const ::wd16_character * psz) noexcept
{
   return ::character_string::length(psz);
}

inline ::wd16_character * __wd16cat(::wd16_character * pszTarget, const ::wd16_character * pszConcat) noexcept
{
   return ::character_string::concatenate(pszTarget, pszConcat);
}

inline ::wd16_character * __wd16cpy(::wd16_character * pszDst, const ::wd16_character * pszSrc) noexcept
{
   return ::character_string::copy(pszDst, pszSrc);
}

inline ::wd16_character * __wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, character_count len) noexcept
{
   return ::character_string::copy_count(pszDst, pszSrc, len);
}

inline const ::wd16_character * __wd16chr(const ::wd16_character * psz, ::wd16_character ch) noexcept
{
   return ::character_string::find_character(psz, ch);
}

inline ::wd16_character * __wd16pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) noexcept
{
   return ::character_string::find_any_character(psz, pszCharsToFind);
}

inline ::wd16_character * __wd16tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) noexcept
{
   return ::character_string::tokenize_reentrant(psz, sep, state);
}

inline const ::wd16_character * __wd16rchr(const ::wd16_character * psz, ::wd16_character ch) noexcept
{
   return ::character_string::find_character_reverse(psz, ch);
}

inline ::i32 __wd16cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::compare(psz1, psz2);
}

inline ::i32 __wd16ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count(psz1, psz2, count);
}

inline const ::wd16_character * __wd16str(const ::wd16_character * psz, const ::wd16_character * pszFind) noexcept
{
   return ::character_string::find_string(psz, pszFind);
}

inline ::wd16_character __wd16tolower(::wd16_character ch) noexcept
{
   return ::character_string::to_lower(ch);
}

inline ::wd16_character __wd16toupper(::wd16_character ch) noexcept
{
   return ::character_string::to_upper(ch);
}

inline ::wd16_character * __wd16lwr(::wd16_character * psz) noexcept
{
   return ::character_string::make_lower(psz);
}

inline ::wd16_character * __wd16lwr_s(::wd16_character * psz, character_count count) noexcept
{
   return ::character_string::make_lower_count(psz, count);
}

inline ::wd16_character * __wd16upr(::wd16_character * psz) noexcept
{
   return ::character_string::make_upper(psz);
}

inline ::wd16_character * __wd16upr_s(::wd16_character * psz, character_count count) noexcept
{
   return ::character_string::make_upper_count(psz, count);
}

inline const ::wd16_character * __wd16ichr(const ::wd16_character * psz, ::wd16_character ch) noexcept
{
   return ::character_string::find_character_case_insensitive(psz, ch);
}

inline ::i32 __wd16icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::compare_case_insensitive(psz1, psz2);
}

inline ::i32 __wd16nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count_case_insensitive(psz1, psz2, count);
}

inline const ::wd16_character * __wd16istr(const ::wd16_character * psz, const ::wd16_character * pszFind) noexcept
{
   return ::character_string::find_string_case_insensitive(psz, pszFind);
}

inline ::wd16_character * overlap_safe_wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, character_count count) noexcept
{
   return ::character_string::overlap_safe_copy_count(pszDst, pszSrc, count);
}

inline ::i32 __wd16coll(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::collate(psz1, psz2);
}

inline ::i32 __wd16ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count(psz1, psz2, count);
}

inline ::i32 __wd16icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::collate_case_insensitive(psz1, psz2);
}

inline ::i32 __wd16nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count_case_insensitive(psz1, psz2, count);
}

inline character_count __wd16spn(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::span_including(psz1, psz2);
}

inline character_count __wd16cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) noexcept
{
   return ::character_string::span_excluding(psz1, psz2);
}

inline ::i64 __wd16toi64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_64(psz, ppszEnd, iBase);
}

inline ::u64 __wd16tou64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_64(psz, ppszEnd, iBase);
}

inline ::i32 __wd16toi32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_32(psz, ppszEnd, iBase);
}

inline ::u32 __wd16tou32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_32(psz, ppszEnd, iBase);
}
