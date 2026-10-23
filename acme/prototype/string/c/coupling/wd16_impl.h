#pragma once

// coupling/wd16_impl.h
// ready-to-use implementation for wd16_character.
//
// IMPORTANT: wd16_character is a distinct C++ type from wchar_t. Therefore Windows
// and Linux wchar_t CRT functions are not used by reinterpret-casting. The
// safe default is ancient/wd16.h, whose implementation is based on
// character_string templates.
//
// Override hook:
//   #define ACME_COUPLING_WD16_IMPL_HEADER "my_os/wd16_impl.h"

//#if defined(ACME_COUPLING_WD16_IMPL_HEADER)
//
//#include ACME_COUPLING_WD16_IMPL_HEADER
//
//#else
//
//#include "wd16.h"
//#include "../ancient/wd16.h"
//#include <stdlib.h>

inline ::wd16_character * wd16_dup(const ::wd16_character * psz)
{
   auto len = __wd16len(psz) + 1;
   auto p = (::wd16_character *) ::malloc((size_t) len * sizeof(::wd16_character));
   return p ? __wd16cpy(p, psz) : nullptr;
}

inline character_count wd16_len(const ::wd16_character * psz)
{ return __wd16len(psz); }

inline character_count wd16_nlen(const ::wd16_character * psz, memsize len)
{
   character_count n = 0;
   while (n < (character_count) len && psz[n]) ++n;
   return n;
}

inline ::wd16_character * wd16_cat(::wd16_character * d, const ::wd16_character * s)
{ return __wd16cat(d, s); }

inline ::wd16_character * wd16_cpy(::wd16_character * d, const ::wd16_character * s)
{ return __wd16cpy(d, s); }

inline ::wd16_character * wd16_ncpy(::wd16_character * d, const ::wd16_character * s, character_count n)
{ return __wd16ncpy(d, s, n); }

inline const ::wd16_character * wd16_chr(const ::wd16_character * s, ::wd16_character ch)
{ return __wd16chr(s, ch); }

inline const ::wd16_character * wd16_pbrk(const ::wd16_character * s, const ::wd16_character * chars)
{ return ::character_string::find_any_character(s, chars); }

inline ::wd16_character * wd16_tok_r(::wd16_character * s, const ::wd16_character * sep, ::wd16_character ** state)
{ return __wd16tok_r(s, sep, state); }

inline ::wd16_character * wd16_token(::wd16_character * s, const ::wd16_character * sep)
{
   static thread_local ::wd16_character * state = nullptr;
   return __wd16tok_r(s, sep, &state);
}

inline const ::wd16_character * wd16_rchr(const ::wd16_character * s, ::wd16_character ch)
{ return __wd16rchr(s, ch); }

inline ::i32 wd16_cmp(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16cmp(a, b); }

inline ::i32 wd16_ncmp(const ::wd16_character * a, const ::wd16_character * b, character_count n)
{ return __wd16ncmp(a, b, n); }

inline const ::wd16_character * wd16_str(const ::wd16_character * s, const ::wd16_character * find)
{ return __wd16str(s, find); }

inline ::wd16_character wd16_tolower(::wd16_character ch)
{ return __wd16tolower(ch); }

inline ::wd16_character wd16_toupper(::wd16_character ch)
{ return __wd16toupper(ch); }

inline ::wd16_character * wd16_lwr(::wd16_character * s)
{ return __wd16lwr(s); }

inline ::wd16_character * wd16_lwr_s(::wd16_character * s, character_count n)
{ return __wd16lwr_s(s, n); }

inline ::wd16_character * wd16_upr(::wd16_character * s)
{ return __wd16upr(s); }

inline ::wd16_character * wd16_upr_s(::wd16_character * s, character_count n)
{ return __wd16upr_s(s, n); }

inline const ::wd16_character * wd16_ichr(const ::wd16_character * s, ::wd16_character ch)
{ return __wd16ichr(s, ch); }

inline ::i32 wd16_icmp(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16icmp(a, b); }

inline ::i32 wd16_nicmp(const ::wd16_character * a, const ::wd16_character * b, character_count n)
{ return __wd16nicmp(a, b, n); }

inline const ::wd16_character * wd16_istr(const ::wd16_character * s, const ::wd16_character * find)
{ return __wd16istr(s, find); }

inline ::i32 wd16_coll(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16coll(a, b); }

inline ::i32 wd16_ncoll(const ::wd16_character * a, const ::wd16_character * b, character_count n)
{ return __wd16ncoll(a, b, n); }

inline ::i32 wd16_icoll(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16icoll(a, b); }

inline ::i32 wd16_nicoll(const ::wd16_character * a, const ::wd16_character * b, character_count n)
{ return __wd16nicoll(a, b, n); }

inline character_count wd16_spn(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16spn(a, b); }

inline character_count wd16_cspn(const ::wd16_character * a, const ::wd16_character * b)
{ return __wd16cspn(a, b); }

//#endif // ACME_COUPLING_WD16_IMPL_HEADER
