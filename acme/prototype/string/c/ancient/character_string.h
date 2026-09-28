#pragma once

//#include "platform.h"

// Header-only C-string-like operations for ca2 character types.
//
// Intended character_type values:
//    ::ansi_character   (char)
//    ::wd16_character   (char16_t)
//    ::wd32_character   (char32_t)
//    ::wide_character   (wchar_t)
//
// These functions deliberately avoid the STL and operate on code units,
// just like the classic C string routines do. Case conversion and character
// classification below are ASCII-only, matching the behavior of the original
// ca2 implementation shown in the source code.
//
// "collate" functions below intentionally fall back to code-unit comparison.
// True locale-aware collation is not realistically implementable generically
// without a locale/Unicode backend (platform API, ICU, etc.).

namespace character_string
{

   template < typename character_type >
   constexpr unsigned long long code_unit_value(character_type ch) noexcept
   {

      // Preserve the underlying code-unit value even when plain char or wchar_t
      // is a signed type. This makes lexical comparison closer to the C routines
      // (strcmp compares unsigned char values). The supported ca2 character types
      // are 1, 2, or 4-byte code units.
      if constexpr (sizeof(character_type) == 1)
      {

         return static_cast < unsigned char >(ch);

      }
      else if constexpr (sizeof(character_type) == 2)
      {

         return static_cast < unsigned short >(ch);

      }
      else if constexpr (sizeof(character_type) == 4)
      {

         return static_cast < unsigned int >(ch);

      }
      else
      {

         return static_cast < unsigned long long >(ch);

      }

   }


   template < typename character_type >
   constexpr character_type character_lowered(character_type ch) noexcept
   {

      return ch >= static_cast < character_type >('A') &&
             ch <= static_cast < character_type >('Z')
         ? static_cast < character_type >(
              ch - static_cast < character_type >('A') + static_cast < character_type >('a'))
         : ch;

   }


   template < typename character_type >
   constexpr character_type character_uppered(character_type ch) noexcept
   {

      return ch >= static_cast < character_type >('a') &&
             ch <= static_cast < character_type >('z')
         ? static_cast < character_type >(
              ch - static_cast < character_type >('a') + static_cast < character_type >('A'))
         : ch;

   }


   template < typename character_type >
   constexpr ::i32 character_isdigit(character_type ch) noexcept
   {

      return ch >= static_cast < character_type >('0') &&
             ch <= static_cast < character_type >('9');

   }


   template < typename character_type >
   constexpr ::i32 character_isalpha(character_type ch) noexcept
   {

      return
         (ch >= static_cast < character_type >('a') && ch <= static_cast < character_type >('z')) ||
         (ch >= static_cast < character_type >('A') && ch <= static_cast < character_type >('Z'));

   }


   template < typename character_type >
   constexpr ::i32 character_isalnum(character_type ch) noexcept
   {

      return character_isalpha(ch) || character_isdigit(ch);

   }


   template < typename character_type >
   constexpr ::i32 character_isspace(character_type ch) noexcept
   {

      return
         ch == static_cast < character_type >('\r') ||
         ch == static_cast < character_type >('\n') ||
         ch == static_cast < character_type >('\t') ||
         ch == static_cast < character_type >(' ');

   }


   template < typename character_type >
   constexpr ::i32 character_isxdigit(character_type ch) noexcept
   {

      return
         character_isdigit(ch) ||
         (ch >= static_cast < character_type >('a') && ch <= static_cast < character_type >('f')) ||
         (ch >= static_cast < character_type >('A') && ch <= static_cast < character_type >('F'));

   }


   template < typename character_type >
   inline character_count length(const character_type * psz) noexcept
   {

      const auto pszStart = psz;

      while (*psz)
      {

         ++psz;

      }

      return psz - pszStart;

   }


   template < typename character_type >
   inline character_type * copy(character_type * pszDst, const character_type * pszSrc) noexcept
   {

      auto pszStart = pszDst;

      while ((*pszDst++ = *pszSrc++) != static_cast < character_type >(0))
      {
      }

      return pszStart;

   }


   template < typename character_type >
   inline character_type * copy_count(
      character_type * pszDst,
      const character_type * pszSrc,
      character_count count) noexcept
   {

      auto pszStart = pszDst;

      while (count > 0 && *pszSrc)
      {

         *pszDst++ = *pszSrc++;
         --count;

      }

      while (count > 0)
      {

         *pszDst++ = static_cast < character_type >(0);
         --count;

      }

      return pszStart;

   }


   template < typename character_type >
   inline character_type * move_count(
      character_type * pszDst,
      const character_type * pszSrc,
      character_count count) noexcept
   {

      if (pszDst == pszSrc || count <= 0)
      {

         return pszDst;

      }

      if (pszDst < pszSrc || pszDst >= pszSrc + count)
      {

         for (character_count i = 0; i < count; ++i)
         {

            pszDst[i] = pszSrc[i];

         }

      }
      else
      {

         for (character_count i = count; i > 0; --i)
         {

            pszDst[i - 1] = pszSrc[i - 1];

         }

      }

      return pszDst;

   }


   template < typename character_type >
   inline character_type * overlap_safe_copy_count(
      character_type * pszDst,
      const character_type * pszSrc,
      character_count count) noexcept
   {

      return move_count(pszDst, pszSrc, count);

   }


   template < typename character_type >
   inline character_type * concatenate(
      character_type * pszTarget,
      const character_type * pszConcat) noexcept
   {

      copy(pszTarget + length(pszTarget), pszConcat);

      return pszTarget;

   }


   template < typename character_type >
   inline const character_type * find_character(
      const character_type * psz,
      character_type ch) noexcept
   {

      // C strchr/wcschr semantics include the terminating NUL when ch == 0.
      for (;; ++psz)
      {

         if (*psz == ch)
         {

            return psz;

         }

         if (*psz == static_cast < character_type >(0))
         {

            return nullptr;

         }

      }

   }


   template < typename character_type >
   inline character_type * find_character(
      character_type * psz,
      character_type ch) noexcept
   {

      return const_cast < character_type * >(
         find_character(static_cast < const character_type * >(psz), ch));

   }


   template < typename character_type >
   inline const character_type * find_character_reverse(
      const character_type * psz,
      character_type ch) noexcept
   {

      const character_type * p = psz + length(psz);

      // Includes the terminating NUL when ch == 0, like strrchr/wcsrchr.
      for (;;)
      {

         if (*p == ch)
         {

            return p;

         }

         if (p == psz)
         {

            break;

         }

         --p;

      }

      return nullptr;

   }


   template < typename character_type >
   inline character_type * find_character_reverse(
      character_type * psz,
      character_type ch) noexcept
   {

      return const_cast < character_type * >(
         find_character_reverse(static_cast < const character_type * >(psz), ch));

   }


   template < typename character_type >
   inline const character_type * find_any_character(
      const character_type * psz,
      const character_type * pszFind) noexcept
   {

      while (*psz)
      {

         const auto p = find_character(pszFind, *psz);

         if (p)
         {

            return psz;

         }

         ++psz;

      }

      return nullptr;

   }


   template < typename character_type >
   inline character_type * find_any_character(
      character_type * psz,
      const character_type * pszFind) noexcept
   {

      return const_cast < character_type * >(
         find_any_character(static_cast < const character_type * >(psz), pszFind));

   }


   template < typename character_type >
   inline ::i32 compare(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      while (*psz1 == *psz2)
      {

         if (*psz1 == static_cast < character_type >(0))
         {

            return 0;

         }

         ++psz1;
         ++psz2;

      }

      return code_unit_value(*psz1) < code_unit_value(*psz2) ? -1 : 1;

   }


   template < typename character_type >
   inline ::i32 compare_count(
      const character_type * psz1,
      const character_type * psz2,
      character_count count) noexcept
   {

      while (count > 0)
      {

         if (*psz1 != *psz2)
         {

            return code_unit_value(*psz1) < code_unit_value(*psz2) ? -1 : 1;

         }

         if (*psz1 == static_cast < character_type >(0))
         {

            return 0;

         }

         ++psz1;
         ++psz2;
         --count;

      }

      return 0;

   }


   template < typename character_type >
   inline const character_type * find_string(
      const character_type * psz,
      const character_type * pszFind) noexcept
   {

      if (!*pszFind)
      {

         return psz;

      }

      for (; *psz; ++psz)
      {

         auto p1 = psz;
         auto p2 = pszFind;

         while (*p1 && *p2 && *p1 == *p2)
         {

            ++p1;
            ++p2;

         }

         if (!*p2)
         {

            return psz;

         }

      }

      return nullptr;

   }


   template < typename character_type >
   inline character_type * find_string(
      character_type * psz,
      const character_type * pszFind) noexcept
   {

      return const_cast < character_type * >(
         find_string(static_cast < const character_type * >(psz), pszFind));

   }


   template < typename character_type >
   constexpr character_type to_lower(character_type ch) noexcept
   {

      return character_lowered(ch);

   }


   template < typename character_type >
   constexpr character_type to_upper(character_type ch) noexcept
   {

      return character_uppered(ch);

   }


   template < typename character_type >
   inline character_type * make_lower(character_type * psz) noexcept
   {

      for (auto p = psz; *p; ++p)
      {

         *p = to_lower(*p);

      }

      return psz;

   }


   template < typename character_type >
   inline character_type * make_lower_count(
      character_type * psz,
      character_count count) noexcept
   {

      auto p = psz;

      while (*p && count > 0)
      {

         *p = to_lower(*p);
         ++p;
         --count;

      }

      return psz;

   }


   template < typename character_type >
   inline character_type * make_upper(character_type * psz) noexcept
   {

      for (auto p = psz; *p; ++p)
      {

         *p = to_upper(*p);

      }

      return psz;

   }


   template < typename character_type >
   inline character_type * make_upper_count(
      character_type * psz,
      character_count count) noexcept
   {

      auto p = psz;

      while (*p && count > 0)
      {

         *p = to_upper(*p);
         ++p;
         --count;

      }

      return psz;

   }


   template < typename character_type >
   inline const character_type * find_character_case_insensitive(
      const character_type * psz,
      character_type ch) noexcept
   {

      ch = to_lower(ch);

      for (;; ++psz)
      {

         if (to_lower(*psz) == ch)
         {

            return psz;

         }

         if (*psz == static_cast < character_type >(0))
         {

            return nullptr;

         }

      }

   }


   template < typename character_type >
   inline ::i32 compare_case_insensitive(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      for (;;)
      {

         const auto ch1 = to_lower(*psz1);
         const auto ch2 = to_lower(*psz2);

         if (ch1 != ch2)
         {

            return code_unit_value(ch1) < code_unit_value(ch2) ? -1 : 1;

         }

         if (*psz1 == static_cast < character_type >(0))
         {

            return 0;

         }

         ++psz1;
         ++psz2;

      }

   }


   template < typename character_type >
   inline ::i32 compare_count_case_insensitive(
      const character_type * psz1,
      const character_type * psz2,
      character_count count) noexcept
   {

      while (count > 0)
      {

         const auto ch1 = to_lower(*psz1);
         const auto ch2 = to_lower(*psz2);

         if (ch1 != ch2)
         {

            return code_unit_value(ch1) < code_unit_value(ch2) ? -1 : 1;

         }

         if (*psz1 == static_cast < character_type >(0))
         {

            return 0;

         }

         ++psz1;
         ++psz2;
         --count;

      }

      return 0;

   }


   template < typename character_type >
   inline const character_type * find_string_case_insensitive(
      const character_type * psz,
      const character_type * pszFind) noexcept
   {

      if (!*pszFind)
      {

         return psz;

      }

      for (; *psz; ++psz)
      {

         auto p1 = psz;
         auto p2 = pszFind;

         while (*p1 && *p2 && to_lower(*p1) == to_lower(*p2))
         {

            ++p1;
            ++p2;

         }

         if (!*p2)
         {

            return psz;

         }

      }

      return nullptr;

   }


   // Locale-aware collation cannot be implemented correctly and portably
   // from code-unit operations alone. These therefore intentionally preserve
   // ca2's current behavior: ordinary lexical comparison.
   template < typename character_type >
   inline ::i32 collate(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      return compare(psz1, psz2);

   }


   template < typename character_type >
   inline ::i32 collate_count(
      const character_type * psz1,
      const character_type * psz2,
      character_count count) noexcept
   {

      return compare_count(psz1, psz2, count);

   }


   template < typename character_type >
   inline ::i32 collate_case_insensitive(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      return compare_case_insensitive(psz1, psz2);

   }


   template < typename character_type >
   inline ::i32 collate_count_case_insensitive(
      const character_type * psz1,
      const character_type * psz2,
      character_count count) noexcept
   {

      return compare_count_case_insensitive(psz1, psz2, count);

   }


   template < typename character_type >
   inline character_count span_including(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      const auto pszStart = psz1;

      while (*psz1 && find_character(psz2, *psz1))
      {

         ++psz1;

      }

      return psz1 - pszStart;

   }


   template < typename character_type >
   inline character_count span_excluding(
      const character_type * psz1,
      const character_type * psz2) noexcept
   {

      const auto pszStart = psz1;

      while (*psz1 && !find_character(psz2, *psz1))
      {

         ++psz1;

      }

      return psz1 - pszStart;

   }


   template < typename character_type >
   inline character_type * tokenize_reentrant(
      character_type * psz,
      const character_type * separators,
      character_type ** state) noexcept
   {

      if (!psz)
      {

         psz = state ? *state : nullptr;

      }

      if (!psz)
      {

         return nullptr;

      }

      // Match strtok/strtok_r behavior: leading delimiters are skipped.
      psz += span_including(psz, separators);

      if (!*psz)
      {

         if (state)
         {

            *state = nullptr;

         }

         return nullptr;

      }

      auto p = psz + span_excluding(psz, separators);

      if (*p)
      {

         *p = static_cast < character_type >(0);

         if (state)
         {

            *state = p + 1;

         }

      }
      else if (state)
      {

         *state = nullptr;

      }

      return psz;

   }


   template < typename character_type >
   constexpr ::i32 digit_value(character_type ch) noexcept
   {

      if (ch >= static_cast < character_type >('0') && ch <= static_cast < character_type >('9'))
      {

         return static_cast < ::i32 >(ch - static_cast < character_type >('0'));

      }

      if (ch >= static_cast < character_type >('a') && ch <= static_cast < character_type >('z'))
      {

         return static_cast < ::i32 >(ch - static_cast < character_type >('a')) + 10;

      }

      if (ch >= static_cast < character_type >('A') && ch <= static_cast < character_type >('Z'))
      {

         return static_cast < ::i32 >(ch - static_cast < character_type >('A')) + 10;

      }

      return -1;

   }


   template < typename character_type >
   inline ::u64 to_unsigned_64(
      const character_type * psz,
      character_type ** ppszEnd,
      ::i32 iBase) noexcept
   {

      auto p = psz;

      while (character_isspace(*p))
      {

         ++p;

      }

      bool bNegative = false;

      if (*p == static_cast < character_type >('+') || *p == static_cast < character_type >('-'))
      {

         bNegative = *p == static_cast < character_type >('-');
         ++p;

      }

      if (iBase == 0)
      {

         if (p[0] == static_cast < character_type >('0'))
         {

            if ((p[1] == static_cast < character_type >('x') || p[1] == static_cast < character_type >('X')) &&
                digit_value(p[2]) >= 0 && digit_value(p[2]) < 16)
            {

               iBase = 16;
               p += 2;

            }
            else
            {

               iBase = 8;

            }

         }
         else
         {

            iBase = 10;

         }

      }
      else if (iBase == 16 &&
               p[0] == static_cast < character_type >('0') &&
               (p[1] == static_cast < character_type >('x') || p[1] == static_cast < character_type >('X')) &&
               digit_value(p[2]) >= 0 && digit_value(p[2]) < 16)
      {

         p += 2;

      }

      if (iBase < 2 || iBase > 36)
      {

         if (ppszEnd)
         {

            *ppszEnd = const_cast < character_type * >(psz);

         }

         return 0;

      }

      const auto pDigits = p;
      ::u64 u = 0;

      while (*p)
      {

         const auto iDigit = digit_value(*p);

         if (iDigit < 0 || iDigit >= iBase)
         {

            break;

         }

         u = u * static_cast < ::u64 >(iBase) + static_cast < ::u64 >(iDigit);
         ++p;

      }

      if (p == pDigits)
      {

         if (ppszEnd)
         {

            *ppszEnd = const_cast < character_type * >(psz);

         }

         return 0;

      }

      if (ppszEnd)
      {

         *ppszEnd = const_cast < character_type * >(p);

      }

      return bNegative ? static_cast < ::u64 >(0 - u) : u;

   }


   template < typename character_type >
   inline ::i64 to_signed_64(
      const character_type * psz,
      character_type ** ppszEnd,
      ::i32 iBase) noexcept
   {

      // This intentionally provides the parsing behavior needed by ca2 without
      // depending on strtoll/wcstoll or the STL. Like the old ca2 wrappers, it
      // does not expose errno/ERANGE overflow reporting.
      auto p = psz;

      while (character_isspace(*p))
      {

         ++p;

      }

      bool bNegative = false;

      if (*p == static_cast < character_type >('+') || *p == static_cast < character_type >('-'))
      {

         bNegative = *p == static_cast < character_type >('-');
         ++p;

      }

      if (iBase == 0)
      {

         if (p[0] == static_cast < character_type >('0'))
         {

            if ((p[1] == static_cast < character_type >('x') || p[1] == static_cast < character_type >('X')) &&
                digit_value(p[2]) >= 0 && digit_value(p[2]) < 16)
            {

               iBase = 16;
               p += 2;

            }
            else
            {

               iBase = 8;

            }

         }
         else
         {

            iBase = 10;

         }

      }
      else if (iBase == 16 &&
               p[0] == static_cast < character_type >('0') &&
               (p[1] == static_cast < character_type >('x') || p[1] == static_cast < character_type >('X')) &&
               digit_value(p[2]) >= 0 && digit_value(p[2]) < 16)
      {

         p += 2;

      }

      if (iBase < 2 || iBase > 36)
      {

         if (ppszEnd)
         {

            *ppszEnd = const_cast < character_type * >(psz);

         }

         return 0;

      }

      const auto pDigits = p;
      ::u64 u = 0;

      while (*p)
      {

         const auto iDigit = digit_value(*p);

         if (iDigit < 0 || iDigit >= iBase)
         {

            break;

         }

         u = u * static_cast < ::u64 >(iBase) + static_cast < ::u64 >(iDigit);
         ++p;

      }

      if (p == pDigits)
      {

         if (ppszEnd)
         {

            *ppszEnd = const_cast < character_type * >(psz);

         }

         return 0;

      }

      if (ppszEnd)
      {

         *ppszEnd = const_cast < character_type * >(p);

      }

      if (bNegative)
      {

         return static_cast < ::i64 >(0 - u);

      }

      return static_cast < ::i64 >(u);

   }


   template < typename character_type >
   inline ::i32 to_signed_32(
      const character_type * psz,
      character_type ** ppszEnd,
      ::i32 iBase) noexcept
   {

      return static_cast < ::i32 >(to_signed_64(psz, ppszEnd, iBase));

   }


   template < typename character_type >
   inline ::u32 to_unsigned_32(
      const character_type * psz,
      character_type ** ppszEnd,
      ::i32 iBase) noexcept
   {

      return static_cast < ::u32 >(to_unsigned_64(psz, ppszEnd, iBase));

   }

} // namespace character_string


// Optional ca2-style convenience wrappers.
// These names can coexist for all four ca2 character types through overloads.

template < typename character_type >
inline character_count __character_length(const character_type * psz) noexcept
{
   return ::character_string::length(psz);
}


template < typename character_type >
inline character_type * __character_copy(character_type * pszDst, const character_type * pszSrc) noexcept
{
   return ::character_string::copy(pszDst, pszSrc);
}


template < typename character_type >
inline character_type * __character_copy_count(
   character_type * pszDst,
   const character_type * pszSrc,
   character_count count) noexcept
{
   return ::character_string::copy_count(pszDst, pszSrc, count);
}


template < typename character_type >
inline ::i32 __character_compare(const character_type * psz1, const character_type * psz2) noexcept
{
   return ::character_string::compare(psz1, psz2);
}


template < typename character_type >
inline ::i32 __character_compare_count(
   const character_type * psz1,
   const character_type * psz2,
   character_count count) noexcept
{
   return ::character_string::compare_count(psz1, psz2, count);
}


