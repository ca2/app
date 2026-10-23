#pragma once

// coupling/wd32_impl.h
// ready-to-use implementation for wd32_character.
//
// IMPORTANT: wd32_character is a distinct C++ type from wchar_t. Therefore Windows
// and Linux wchar_t CRT functions are not used by reinterpret-casting. The
// safe default is ancient/wd32.h, whose implementation is based on
// character_string templates.
//
// Override hook:
//   #define ACME_COUPLING_WD32_IMPL_HEADER "my_os/wd32_impl.h"

//#if defined(ACME_COUPLING_WD32_IMPL_HEADER)
//
//#include ACME_COUPLING_WD32_IMPL_HEADER
//
//#else
//
//#include "wd32.h"
//#include "../ancient/wd32.h"
//#include <stdlib.h>

inline ::wd32_character * wd32_dup(const ::wd32_character * psz)
{
   auto len = __wd32len(psz) + 1;
   auto p = (::wd32_character *) ::malloc((size_t) len * sizeof(::wd32_character));
   return p ? __wd32cpy(p, psz) : nullptr;
}

inline character_count wd32_len(const ::wd32_character * psz)
{ return __wd32len(psz); }

inline character_count wd32_nlen(const ::wd32_character * psz, memsize len)
{
   character_count n = 0;
   while (n < (character_count) len && psz[n]) ++n;
   return n;
}

inline ::wd32_character * wd32_cat(::wd32_character * d, const ::wd32_character * s)
{ return __wd32cat(d, s); }

inline ::wd32_character * wd32_cpy(::wd32_character * d, const ::wd32_character * s)
{ return __wd32cpy(d, s); }

inline ::wd32_character * wd32_ncpy(::wd32_character * d, const ::wd32_character * s, character_count n)
{ return __wd32ncpy(d, s, n); }

inline const ::wd32_character * wd32_chr(const ::wd32_character * s, ::wd32_character ch)
{ return __wd32chr(s, ch); }

inline const ::wd32_character * wd32_pbrk(const ::wd32_character * s, const ::wd32_character * chars)
{ return ::character_string::find_any_character(s, chars); }

inline ::wd32_character * wd32_tok_r(::wd32_character * s, const ::wd32_character * sep, ::wd32_character ** state)
{ return __wd32tok_r(s, sep, state); }

inline ::wd32_character * wd32_token(::wd32_character * s, const ::wd32_character * sep)
{
   static thread_local ::wd32_character * state = nullptr;
   return __wd32tok_r(s, sep, &state);
}

inline const ::wd32_character * wd32_rchr(const ::wd32_character * s, ::wd32_character ch)
{ return __wd32rchr(s, ch); }

inline ::i32 wd32_cmp(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32cmp(a, b); }

inline ::i32 wd32_ncmp(const ::wd32_character * a, const ::wd32_character * b, character_count n)
{ return __wd32ncmp(a, b, n); }

inline const ::wd32_character * wd32_str(const ::wd32_character * s, const ::wd32_character * find)
{ return __wd32str(s, find); }

inline ::wd32_character wd32_tolower(::wd32_character ch)
{ return __wd32tolower(ch); }

inline ::wd32_character wd32_toupper(::wd32_character ch)
{ return __wd32toupper(ch); }

inline ::wd32_character * wd32_lwr(::wd32_character * s)
{ return __wd32lwr(s); }

inline ::wd32_character * wd32_lwr_s(::wd32_character * s, character_count n)
{ return __wd32lwr_s(s, n); }

inline ::wd32_character * wd32_upr(::wd32_character * s)
{ return __wd32upr(s); }

inline ::wd32_character * wd32_upr_s(::wd32_character * s, character_count n)
{ return __wd32upr_s(s, n); }

inline const ::wd32_character * wd32_ichr(const ::wd32_character * s, ::wd32_character ch)
{ return __wd32ichr(s, ch); }

inline ::i32 wd32_icmp(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32icmp(a, b); }

inline ::i32 wd32_nicmp(const ::wd32_character * a, const ::wd32_character * b, character_count n)
{ return __wd32nicmp(a, b, n); }

inline const ::wd32_character * wd32_istr(const ::wd32_character * s, const ::wd32_character * find)
{ return __wd32istr(s, find); }

inline ::i32 wd32_coll(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32coll(a, b); }

inline ::i32 wd32_ncoll(const ::wd32_character * a, const ::wd32_character * b, character_count n)
{ return __wd32ncoll(a, b, n); }

inline ::i32 wd32_icoll(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32icoll(a, b); }

inline ::i32 wd32_nicoll(const ::wd32_character * a, const ::wd32_character * b, character_count n)
{ return __wd32nicoll(a, b, n); }

inline character_count wd32_spn(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32spn(a, b); }

inline character_count wd32_cspn(const ::wd32_character * a, const ::wd32_character * b)
{ return __wd32cspn(a, b); }

//#endif // ACME_COUPLING_WD32_IMPL_HEADER
