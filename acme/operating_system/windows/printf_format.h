#pragma once

// XP's MSVCRT understands I64, but not the C99 ll/j/z/t integer lengths.
// Normalize only integer conversions; preserve Windows wide %s/%S semantics.
#if defined(__REACTOS__)
#include <cstddef>
#include <cstdint>
#include <string>

namespace ca2_xp
{
   template <typename CHARACTER>
   std::basic_string<CHARACTER> printf_format(const CHARACTER *format)
   {
      std::basic_string<CHARACTER> result;
      if (!format)
         return result;
      const CHARACTER *copy = format;
      for (const CHARACTER *p = format; *p;)
      {
         if (*p++ != '%')
            continue;
         if (*p == '%')
         {
            ++p;
            continue;
         }
         while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0')
            ++p;
         if (*p == '*') ++p;
         else while (*p >= '0' && *p <= '9') ++p;
         if (*p == '.')
         {
            ++p;
            if (*p == '*') ++p;
            else while (*p >= '0' && *p <= '9') ++p;
         }
         const CHARACTER *length = p;
         std::size_t bytes = 0;
         if (p[0] == 'l' && p[1] == 'l') { bytes = sizeof(long long); p += 2; }
         else if (*p == 'j') { bytes = sizeof(std::intmax_t); ++p; }
         else if (*p == 'z') { bytes = sizeof(std::size_t); ++p; }
         else if (*p == 't') { bytes = sizeof(std::ptrdiff_t); ++p; }
         if (bytes && (*p == 'd' || *p == 'i' || *p == 'u' || *p == 'o' || *p == 'x' || *p == 'X'))
         {
            result.append(copy, length);
            // On 32-bit Windows these pointer-sized values are promoted to int.
            if (bytes == 8)
            {
               result += CHARACTER('I'); result += CHARACTER('6'); result += CHARACTER('4');
            }
            copy = p;
         }
         if (*p) ++p;
      }
      result.append(copy);
      return result;
   }
}

// The temporary lives through the formatting call. Do not retain this pointer.
#define CA2_PRINTF_FORMAT(format) (::ca2_xp::printf_format(format).c_str())
#else
#define CA2_PRINTF_FORMAT(format) (format)
#endif
