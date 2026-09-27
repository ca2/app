#pragma once

// coupling/ansi_impl.h
// ready-to-use ANSI implementation.
//
// Override hook:
//   Define ACME_COUPLING_ANSI_IMPL_HEADER to a quoted include path before
//   including this file, for example:
//      #define ACME_COUPLING_ANSI_IMPL_HEADER "my_os/ansi_impl.h"
//
// Default policy:
//   Windows -> use the Microsoft CRT when it has an exact/equivalent API.
//   Linux   -> use the C/POSIX runtime when it has an exact/equivalent API.
//   Missing OS primitive -> ancient/ansi.h (character_string based).

//#if defined(ACME_COUPLING_ANSI_IMPL_HEADER)
//
//#include ACME_COUPLING_ANSI_IMPL_HEADER
//
//#else
//
//#include "ansi.h"
//#include "../ancient/ansi.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <strings.h>
#endif

inline ::ansi_character * ansi_dup(const_char_pointer psz)
{
#if defined(_WIN32)
   return ::_strdup(psz);
#elif defined(__linux__)
   return ::strdup(psz);
#else
   auto len = __ansilen(psz) + 1;
   auto p = (::ansi_character *) ::malloc((size_t) len * sizeof(::ansi_character));
   return p ? __ansicpy(p, psz) : nullptr;
#endif
}

inline character_count ansi_len(const_char_pointer psz)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::strlen(psz);
#else
   return __ansilen(psz);
#endif
}

inline character_count ansi_nlen(const_char_pointer psz, memsize len)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::strnlen(psz, (size_t) len);
#else
   character_count n = 0;
   while (n < (character_count) len && psz[n]) ++n;
   return n;
#endif
}

inline ::ansi_character * ansi_cat(::ansi_character * pszDst, const_char_pointer psz)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strcat(pszDst, psz);
#else
   return __ansicat(pszDst, psz);
#endif
}

inline ::ansi_character * ansi_cpy(::ansi_character * pszDst, const_char_pointer psz)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strcpy(pszDst, psz);
#else
   return __ansicpy(pszDst, psz);
#endif
}

inline ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const_char_pointer psz, character_count len)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strncpy(pszDst, psz, (size_t) len);
#else
   return __ansincpy(pszDst, psz, len);
#endif
}

inline const_char_pointer ansi_chr(const_char_pointer psz, ::ansi_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strchr(psz, ch);
#else
   return __ansichr(psz, ch);
#endif
}

inline const_char_pointer ansi_pbrk(const_char_pointer psz, const_char_pointer pszCharsToFind)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strpbrk(psz, pszCharsToFind);
#else
   return ::character_string::find_any_character(psz, pszCharsToFind);
#endif
}

inline ::ansi_character * ansi_tok_r(::ansi_character * psz, const_char_pointer sep, ::ansi_character ** state)
{
#if defined(_WIN32)
   return ::strtok_s(psz, sep, state);
#elif defined(__linux__)
   return ::strtok_r(psz, sep, state);
#else
   return __ansitok_r(psz, sep, state);
#endif
}

inline ::ansi_character * ansi_token(::ansi_character * psz, const_char_pointer separators)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strtok(psz, separators);
#else
   static thread_local ::ansi_character * s_state = nullptr;
   return __ansitok_r(psz, separators, &s_state);
#endif
}

inline const_char_pointer ansi_rchr(const_char_pointer psz, ::ansi_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strrchr(psz, ch);
#else
   return __ansirchr(psz, ch);
#endif
}

inline ::i32 ansi_cmp(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::strcmp(psz1, psz2);
#else
   return __ansicmp(psz1, psz2);
#endif
}

inline ::i32 ansi_ncmp(const_char_pointer psz1, const_char_pointer psz2, character_count s)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::strncmp(psz1, psz2, (size_t) s);
#else
   return __ansincmp(psz1, psz2, s);
#endif
}

inline const_char_pointer ansi_str(const_char_pointer psz, const_char_pointer pszFind)
{
#if defined(_WIN32) || defined(__linux__)
   return ::strstr(psz, pszFind);
#else
   return __ansistr(psz, pszFind);
#endif
}

inline ::ansi_character ansi_tolower(::ansi_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return (::ansi_character) ::tolower((unsigned char) ch);
#else
   return __ansitolower(ch);
#endif
}

inline ::ansi_character ansi_toupper(::ansi_character ch)
{
#if defined(_WIN32) || defined(__linux__)
   return (::ansi_character) ::toupper((unsigned char) ch);
#else
   return __ansitoupper(ch);
#endif
}

inline ::ansi_character * ansi_lwr(::ansi_character * psz)
{
#if defined(_WIN32)
   return ::_strlwr(psz);
#else
   return __ansilwr(psz); // no POSIX strlwr
#endif
}

inline ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s)
{
#if defined(_WIN32)
   return ::_strlwr_s(psz, (size_t) s) == 0 ? psz : nullptr;
#else
   return __ansilwr_s(psz, s); // no POSIX strlwr_s
#endif
}

inline ::ansi_character * ansi_upr(::ansi_character * psz)
{
#if defined(_WIN32)
   return ::_strupr(psz);
#else
   return __ansiupr(psz); // no POSIX strupr
#endif
}

inline ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s)
{
#if defined(_WIN32)
   return ::_strupr_s(psz, (size_t) s) == 0 ? psz : nullptr;
#else
   return __ansiupr_s(psz, s); // no POSIX strupr_s
#endif
}

inline const_char_pointer ansi_ichr(const_char_pointer psz, ::ansi_character ch)
{
   return __ansiichr(psz, ch); // no portable CRT/POSIX case-insensitive strchr
}

inline ::i32 ansi_icmp(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32)
   return (::i32) ::_stricmp(psz1, psz2);
#elif defined(__linux__)
   return (::i32) ::strcasecmp(psz1, psz2);
#else
   return __ansiicmp(psz1, psz2);
#endif
}

inline ::i32 ansi_nicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s)
{
#if defined(_WIN32)
   return (::i32) ::_strnicmp(psz1, psz2, (size_t) s);
#elif defined(__linux__)
   return (::i32) ::strncasecmp(psz1, psz2, (size_t) s);
#else
   return __ansinicmp(psz1, psz2, s);
#endif
}

inline const_char_pointer ansi_istr(const_char_pointer psz, const_char_pointer pszFind)
{
   return __ansiistr(psz, pszFind); // no portable CRT/POSIX strcasestr contract
}

inline ::i32 ansi_coll(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32) || defined(__linux__)
   return (::i32) ::strcoll(psz1, psz2);
#else
   return __ansicoll(psz1, psz2);
#endif
}

inline ::i32 ansi_ncoll(const_char_pointer psz1, const_char_pointer psz2, character_count s)
{
#if defined(_WIN32)
   return (::i32) ::_strncoll(psz1, psz2, (size_t) s);
#else
   return __ansincoll(psz1, psz2, s); // POSIX has no strncoll
#endif
}

inline ::i32 ansi_icoll(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32)
   return (::i32) ::_stricoll(psz1, psz2);
#else
   return __ansiicoll(psz1, psz2); // POSIX has no standard strcasecoll
#endif
}

inline ::i32 ansi_nicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s)
{
#if defined(_WIN32)
   return (::i32) ::_strnicoll(psz1, psz2, (size_t) s);
#else
   return __ansinicoll(psz1, psz2, s);
#endif
}

inline character_count ansi_spn(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::strspn(psz1, psz2);
#else
   return __ansispn(psz1, psz2);
#endif
}

inline character_count ansi_cspn(const_char_pointer psz1, const_char_pointer psz2)
{
#if defined(_WIN32) || defined(__linux__)
   return (character_count) ::strcspn(psz1, psz2);
#else
   return __ansicspn(psz1, psz2);
#endif
}

//#endif // ACME_COUPLING_ANSI_IMPL_HEADER
