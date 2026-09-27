#pragma once

#include "character_string.h"

// Compatibility forwarding layer for the ancient ca2 character API.
// Implementations live in ::character_string and are code-unit based.
// Case conversion/classification is intentionally ASCII-only.

inline ::ansi_character __ansicharlowered(::i32 i) noexcept
{
   return ::character_string::character_lowered(static_cast < ::ansi_character >(i));
}

inline ::ansi_character __ansicharuppered(::i32 i) noexcept
{
   return ::character_string::character_uppered(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharisdigit(::i32 i) noexcept
{
   return ::character_string::character_isdigit(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharisalpha(::i32 i) noexcept
{
   return ::character_string::character_isalpha(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharisalnum(::i32 i) noexcept
{
   return ::character_string::character_isalnum(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharisspace(::i32 i) noexcept
{
   return ::character_string::character_isspace(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharisxdigit(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::ansi_character >(i));
}

inline ::i32 __ansicharishexadecimal(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::ansi_character >(i));
}

inline character_count __ansilen(const ::ansi_character * psz) noexcept
{
   return ::character_string::length(psz);
}

inline ::ansi_character * __ansicat(::ansi_character * pszTarget, const ::ansi_character * pszConcat) noexcept
{
   return ::character_string::concatenate(pszTarget, pszConcat);
}

inline ::ansi_character * __ansicpy(::ansi_character * pszDst, const ::ansi_character * pszSrc) noexcept
{
   return ::character_string::copy(pszDst, pszSrc);
}

inline ::ansi_character * __ansincpy(::ansi_character * pszDst, const ::ansi_character * pszSrc, character_count len) noexcept
{
   return ::character_string::copy_count(pszDst, pszSrc, len);
}

inline const ::ansi_character * __ansichr(const ::ansi_character * psz, ::ansi_character ch) noexcept
{
   return ::character_string::find_character(psz, ch);
}

inline ::ansi_character * __ansipbrk(::ansi_character * psz, const ::ansi_character * pszCharsToFind) noexcept
{
   return ::character_string::find_any_character(psz, pszCharsToFind);
}

inline ::ansi_character * __ansitok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state) noexcept
{
   return ::character_string::tokenize_reentrant(psz, sep, state);
}

inline const ::ansi_character * __ansirchr(const ::ansi_character * psz, ::ansi_character ch) noexcept
{
   return ::character_string::find_character_reverse(psz, ch);
}

inline ::i32 __ansicmp(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::compare(psz1, psz2);
}

inline ::i32 __ansincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count(psz1, psz2, count);
}

inline const ::ansi_character * __ansistr(const ::ansi_character * psz, const ::ansi_character * pszFind) noexcept
{
   return ::character_string::find_string(psz, pszFind);
}

inline ::ansi_character __ansitolower(::ansi_character ch) noexcept
{
   return ::character_string::to_lower(ch);
}

inline ::ansi_character __ansitoupper(::ansi_character ch) noexcept
{
   return ::character_string::to_upper(ch);
}

inline ::ansi_character * __ansilwr(::ansi_character * psz) noexcept
{
   return ::character_string::make_lower(psz);
}

inline ::ansi_character * __ansilwr_s(::ansi_character * psz, character_count count) noexcept
{
   return ::character_string::make_lower_count(psz, count);
}

inline ::ansi_character * __ansiupr(::ansi_character * psz) noexcept
{
   return ::character_string::make_upper(psz);
}

inline ::ansi_character * __ansiupr_s(::ansi_character * psz, character_count count) noexcept
{
   return ::character_string::make_upper_count(psz, count);
}

inline const ::ansi_character * __ansiichr(const ::ansi_character * psz, ::ansi_character ch) noexcept
{
   return ::character_string::find_character_case_insensitive(psz, ch);
}

inline ::i32 __ansiicmp(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::compare_case_insensitive(psz1, psz2);
}

inline ::i32 __ansinicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count_case_insensitive(psz1, psz2, count);
}

inline const ::ansi_character * __ansiistr(const ::ansi_character * psz, const ::ansi_character * pszFind) noexcept
{
   return ::character_string::find_string_case_insensitive(psz, pszFind);
}

inline ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const ::ansi_character * pszSrc, character_count count) noexcept
{
   return ::character_string::overlap_safe_copy_count(pszDst, pszSrc, count);
}

inline ::i32 __ansicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::collate(psz1, psz2);
}

inline ::i32 __ansincoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count(psz1, psz2, count);
}

inline ::i32 __ansiicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::collate_case_insensitive(psz1, psz2);
}

inline ::i32 __ansinicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count_case_insensitive(psz1, psz2, count);
}

inline character_count __ansispn(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::span_including(psz1, psz2);
}

inline character_count __ansicspn(const ::ansi_character * psz1, const ::ansi_character * psz2) noexcept
{
   return ::character_string::span_excluding(psz1, psz2);
}

inline ::i64 __ansitoi64(const ::ansi_character * psz, ::ansi_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_64(psz, ppszEnd, iBase);
}

inline ::u64 __ansitou64(const ::ansi_character * psz, ::ansi_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_64(psz, ppszEnd, iBase);
}

inline ::i32 __ansitoi32(const ::ansi_character * psz, ::ansi_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_32(psz, ppszEnd, iBase);
}

inline ::u32 __ansitou32(const ::ansi_character * psz, ::ansi_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_32(psz, ppszEnd, iBase);
}

inline ::ansi_character lower_char(::i32 ch) noexcept
{
   return ::character_string::to_lower(static_cast < ::ansi_character >(ch));
}

inline ::ansi_character upper_char(::i32 ch) noexcept
{
   return ::character_string::to_upper(static_cast < ::ansi_character >(ch));
}

inline void make_lower(::ansi_character * psz) noexcept
{
   (void) ::character_string::make_lower(psz);
}
