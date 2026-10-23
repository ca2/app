#pragma once

#include "character_string.h"

CLASS_DECL_ACME ::wide_character * __u64towide(::u64 u, ::wide_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wide_character *& end);
CLASS_DECL_ACME ::wide_character * __i64towide(::i64 i, ::wide_character * buf, ::i32 iBase, enum_digit_case edigitcase, ::wide_character *& end);

// Compatibility forwarding layer for the ancient ca2 character API.
// Implementations live in ::character_string and are code-unit based.
// Case conversion/classification is intentionally ASCII-only.

inline ::wide_character __widecharlowered(::i32 i) noexcept
{
   return ::character_string::character_lowered(static_cast < ::wide_character >(i));
}

inline ::wide_character __widecharuppered(::i32 i) noexcept
{
   return ::character_string::character_uppered(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharisdigit(::i32 i) noexcept
{
   return ::character_string::character_isdigit(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharisalpha(::i32 i) noexcept
{
   return ::character_string::character_isalpha(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharisalnum(::i32 i) noexcept
{
   return ::character_string::character_isalnum(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharisspace(::i32 i) noexcept
{
   return ::character_string::character_isspace(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharisxdigit(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wide_character >(i));
}

inline ::i32 __widecharishexadecimal(::i32 i) noexcept
{
   return ::character_string::character_isxdigit(static_cast < ::wide_character >(i));
}

inline character_count __widelen(const ::wide_character * psz) noexcept
{
   return ::character_string::length(psz);
}

inline ::wide_character * __widecat(::wide_character * pszTarget, const ::wide_character * pszConcat) noexcept
{
   return ::character_string::concatenate(pszTarget, pszConcat);
}

inline ::wide_character * __widecpy(::wide_character * pszDst, const ::wide_character * pszSrc) noexcept
{
   return ::character_string::copy(pszDst, pszSrc);
}

inline ::wide_character * __widencpy(::wide_character * pszDst, const ::wide_character * pszSrc, character_count len) noexcept
{
   return ::character_string::copy_count(pszDst, pszSrc, len);
}

inline const ::wide_character * __widechr(const ::wide_character * psz, ::wide_character ch) noexcept
{
   return ::character_string::find_character(psz, ch);
}

inline ::wide_character * __widepbrk(::wide_character * psz, const ::wide_character * pszCharsToFind) noexcept
{
   return ::character_string::find_any_character(psz, pszCharsToFind);
}

inline ::wide_character * __widetok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state) noexcept
{
   return ::character_string::tokenize_reentrant(psz, sep, state);
}

inline const ::wide_character * __widerchr(const ::wide_character * psz, ::wide_character ch) noexcept
{
   return ::character_string::find_character_reverse(psz, ch);
}

inline ::i32 __widecmp(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::compare(psz1, psz2);
}

inline ::i32 __widencmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count(psz1, psz2, count);
}

inline const ::wide_character * __widestr(const ::wide_character * psz, const ::wide_character * pszFind) noexcept
{
   return ::character_string::find_string(psz, pszFind);
}

inline ::wide_character __widetolower(::wide_character ch) noexcept
{
   return ::character_string::to_lower(ch);
}

inline ::wide_character __widetoupper(::wide_character ch) noexcept
{
   return ::character_string::to_upper(ch);
}

inline ::wide_character * __widelwr(::wide_character * psz) noexcept
{
   return ::character_string::make_lower(psz);
}

inline ::wide_character * __widelwr_s(::wide_character * psz, character_count count) noexcept
{
   return ::character_string::make_lower_count(psz, count);
}

inline ::wide_character * __wideupr(::wide_character * psz) noexcept
{
   return ::character_string::make_upper(psz);
}

inline ::wide_character * __wideupr_s(::wide_character * psz, character_count count) noexcept
{
   return ::character_string::make_upper_count(psz, count);
}

inline const ::wide_character * __wideichr(const ::wide_character * psz, ::wide_character ch) noexcept
{
   return ::character_string::find_character_case_insensitive(psz, ch);
}

inline ::i32 __wideicmp(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::compare_case_insensitive(psz1, psz2);
}

inline ::i32 __widenicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count count) noexcept
{
   return ::character_string::compare_count_case_insensitive(psz1, psz2, count);
}

inline const ::wide_character * __wideistr(const ::wide_character * psz, const ::wide_character * pszFind) noexcept
{
   return ::character_string::find_string_case_insensitive(psz, pszFind);
}

inline ::wide_character * overlap_safe_widencpy(::wide_character * pszDst, const ::wide_character * pszSrc, character_count count) noexcept
{
   return ::character_string::overlap_safe_copy_count(pszDst, pszSrc, count);
}

inline ::i32 __widecoll(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::collate(psz1, psz2);
}

inline ::i32 __widencoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count(psz1, psz2, count);
}

inline ::i32 __wideicoll(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::collate_case_insensitive(psz1, psz2);
}

inline ::i32 __widenicoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count count) noexcept
{
   return ::character_string::collate_count_case_insensitive(psz1, psz2, count);
}

inline character_count __widespn(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::span_including(psz1, psz2);
}

inline character_count __widecspn(const ::wide_character * psz1, const ::wide_character * psz2) noexcept
{
   return ::character_string::span_excluding(psz1, psz2);
}

inline ::i64 __widetoi64(const ::wide_character * psz, ::wide_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_64(psz, ppszEnd, iBase);
}

inline ::u64 __widetou64(const ::wide_character * psz, ::wide_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_64(psz, ppszEnd, iBase);
}

inline ::i32 __widetoi32(const ::wide_character * psz, ::wide_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_signed_32(psz, ppszEnd, iBase);
}

inline ::u32 __widetou32(const ::wide_character * psz, ::wide_character ** ppszEnd, ::i32 iBase) noexcept
{
   return ::character_string::to_unsigned_32(psz, ppszEnd, iBase);
}
