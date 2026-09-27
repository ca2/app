#pragma once

// coupling/wide_impl.h
// ready-to-use wchar_t implementation.
// Windows and Linux both have a real native wchar_t CRT, so use it whenever
// an equivalent function exists. Missing operations fall back to ancient/wide.h.
//
// Override hook:
//   #define ACME_COUPLING_WIDE_IMPL_HEADER "my_os/wide_impl.h"

//#if defined(ACME_COUPLING_WIDE_IMPL_HEADER)
//
//#include ACME_COUPLING_WIDE_IMPL_HEADER
//
//#else
//
//#include "wide.h"
//#include "../ancient/wide.h"

#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#if defined(__linux__)
#include <wctype.h>
#endif

inline ::wide_character * wide_dup(const ::wide_character * psz)
{
#if defined(_WIN32)
   return ::_wcsdup(psz);
#elif defined(__linux__)
   return ::wcsdup(psz);
#else
   auto len = __widelen(psz) + 1;
   auto p = (::wide_character *) ::malloc((size_t) len * sizeof(::wide_character));
   return p ? __widecpy(p, psz) : nullptr;
#endif
}

inline character_count wide_len(const ::wide_character * psz)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::wcslen(psz);
#else
   return __widelen(psz);
#endif
}

inline character_count wide_nlen(const ::wide_character * psz, memsize len)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::wcsnlen(psz, (size_t) len);
#else
   character_count n = 0;
   while (n < (character_count) len && psz[n]) ++n;
   return n;
#endif
}

inline ::wide_character * wide_cat(::wide_character * d, const ::wide_character * s)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcscat(d, s);
#else
   return __widecat(d, s);
#endif
}

inline ::wide_character * wide_cpy(::wide_character * d, const ::wide_character * s)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcscpy(d, s);
#else
   return __widecpy(d, s);
#endif
}

inline ::wide_character * wide_ncpy(::wide_character * d, const ::wide_character * s, character_count n)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcsncpy(d, s, (size_t) n);
#else
   return __widencpy(d, s, n);
#endif
}

inline const ::wide_character * wide_chr(const ::wide_character * s, ::wide_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcschr(s, ch);
#else
   return __widechr(s, ch);
#endif
}

inline const ::wide_character * wide_pbrk(const ::wide_character * s, const ::wide_character * chars)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcspbrk(s, chars);
#else
   return ::character_string::find_any_character(s, chars);
#endif
}

inline ::wide_character * wide_tok_r(::wide_character * s, const ::wide_character * sep, ::wide_character ** state)
{
#if defined(_WIN32)
   return ::wcstok_s(s, sep, state);
#elif defined(__linux__)
   return ::wcstok(s, sep, state);
#else
   return __widetok_r(s, sep, state);
#endif
}

inline ::wide_character * wide_token(::wide_character * s, const ::wide_character * sep)
{
   static thread_local ::wide_character * state = nullptr;
#if defined(_WIN32)
   return ::wcstok_s(s, sep, &state);
#elif defined(__linux__)
   return ::wcstok(s, sep, &state);
#else
   return __widetok_r(s, sep, &state);
#endif
}

inline const ::wide_character * wide_rchr(const ::wide_character * s, ::wide_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcsrchr(s, ch);
#else
   return __widerchr(s, ch);
#endif
}

inline ::i32 wide_cmp(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::wcscmp(a, b);
#else
   return __widecmp(a, b);
#endif
}

inline ::i32 wide_ncmp(const ::wide_character * a, const ::wide_character * b, character_count n)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::wcsncmp(a, b, (size_t) n);
#else
   return __widencmp(a, b, n);
#endif
}

inline const ::wide_character * wide_str(const ::wide_character * s, const ::wide_character * find)
{
#if defined(_WIN32) || defined(__linux__)
   return ::wcsstr(s, find);
#else
   return __widestr(s, find);
#endif
}

inline ::wide_character wide_tolower(::wide_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return (::wide_character) ::towlower(ch);
#else
   return __widetolower(ch);
#endif
}

inline ::wide_character wide_toupper(::wide_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return (::wide_character) ::towupper(ch);
#else
   return __widetoupper(ch);
#endif
}

inline ::wide_character * wide_lwr(::wide_character * s)
{
#if defined(_WIN32)
   return ::_wcslwr(s);
#else
   return __widelwr(s); // no POSIX wcslwr
#endif
}

inline ::wide_character * wide_lwr_s(::wide_character * s, character_count n)
{
#if defined(_WIN32)
   return ::_wcslwr_s(s, (size_t) n) == 0 ? s : nullptr;
#else
   return __widelwr_s(s, n);
#endif
}

inline ::wide_character * wide_upr(::wide_character * s)
{
#if defined(_WIN32)
   return ::_wcsupr(s);
#else
   return __wideupr(s); // no POSIX wcsupr
#endif
}

inline ::wide_character * wide_upr_s(::wide_character * s, character_count n)
{
#if defined(_WIN32)
   return ::_wcsupr_s(s, (size_t) n) == 0 ? s : nullptr;
#else
   return __wideupr_s(s, n);
#endif
}

inline const ::wide_character * wide_ichr(const ::wide_character * s, ::wide_character ch)
{
   return __wideichr(s, ch);
}

inline ::i32 wide_icmp(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32)
   return (::i32) ::_wcsicmp(a, b);
#elif defined(__linux__)
   return (::i32) ::wcscasecmp(a, b);
#else
   return __wideicmp(a, b);
#endif
}

inline ::i32 wide_nicmp(const ::wide_character * a, const ::wide_character * b, character_count n)
{
#if defined(_WIN32)
   return (::i32) ::_wcsnicmp(a, b, (size_t) n);
#elif defined(__linux__)
   return (::i32) ::wcsncasecmp(a, b, (size_t) n);
#else
   return __widenicmp(a, b, n);
#endif
}

inline const ::wide_character * wide_istr(const ::wide_character * s, const ::wide_character * find)
{
   return __wideistr(s, find);
}

inline ::i32 wide_coll(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::wcscoll(a, b);
#else
   return __widecoll(a, b);
#endif
}

inline ::i32 wide_ncoll(const ::wide_character * a, const ::wide_character * b, character_count n)
{
#if defined(_WIN32)
   return (::i32) ::_wcsncoll(a, b, (size_t) n);
#else
   return __widencoll(a, b, n); // POSIX has no wcsncoll
#endif
}

inline ::i32 wide_icoll(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32)
   return (::i32) ::_wcsicoll(a, b);
#else
   return __wideicoll(a, b);
#endif
}

inline ::i32 wide_nicoll(const ::wide_character * a, const ::wide_character * b, character_count n)
{
#if defined(_WIN32)
   return (::i32) ::_wcsnicoll(a, b, (size_t) n);
#else
   return __widenicoll(a, b, n);
#endif
}

inline character_count wide_spn(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::wcsspn(a, b);
#else
   return __widespn(a, b);
#endif
}

inline character_count wide_cspn(const ::wide_character * a, const ::wide_character * b)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::wcscspn(a, b);
#else
   return __widecspn(a, b);
#endif
}

//#endif // ACME_COUPLING_WIDE_IMPL_HEADER
