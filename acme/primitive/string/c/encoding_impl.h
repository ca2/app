// Created by camilo on 2022-11-07 16:02 <3ThomasBorregaardSorensen!!
#pragma once



inline i32 utf8_o(char cExtraBytes)
{

   switch (cExtraBytes)
   {
   case 0:
      return 0x00000000UL;
   case 1:
      return 0x00003080UL;
   case 2:
      return 0x000E2080UL;
   case 3:
      return 0x03C82080UL;
   case 4:
      return 0xFA082080UL;
   case 5:
      return 0x82082080UL;
   default:
      return -1;
   };

}


inline char utf8_e(byte c)
{

   if (c < 192)
      return 0;
   else if (c < 192 + 32)
      return 1;
   else if (c < 192 + 32 + 16)
      return 2;
   else if (c < 192 + 32 + 16 + 8)
      return 3;
   else if (c < 192 + 32 + 16 + 8 + 4)
      return 4;
   else
      return 5;

}




inline strsize wd32_to_ansi_char_len(::wd32_character wch)
{
   if (wch == 0)
   {
      return 0;
   }
   else if (wch <= 0x7F)
   {
      // Plain ASCII
      return 1;
   }
   else if (wch <= 0x07FF)
   {
      // 2-byte unicode
      return 2;
   }
   else if (wch <= 0xFFFF)
   {
      // 3-byte unicode
      return 3;
   }
   else if (wch <= 0x10FFFF)
   {
      // 4-byte unicode
      return 4;
   }
   else
   {
      return -1;
   }
}


inline strsize wd16_to_wd32_char(::wd32_character * output, const ::wd16_character * input, strsize len)
{

   if (len < 1)
   {

      return -1;

   }

   auto _1stSurrogateCandidate = input[0];

   if (_1stSurrogateCandidate == 0)
   {

      return 0;

   }

   if (utf16_is_2nd_surrogate(_1stSurrogateCandidate))
   {

      // ERROR Maticki

      return -1;

   }
   else if (utf16_is_1st_surrogate(_1stSurrogateCandidate))
   {

      if (len < 2)
      {

         return -1;

      }

      auto _2ndSurrogateCandidate = input[1];

      if (utf16_is_2nd_surrogate(_2ndSurrogateCandidate))
      {

         *output = utf16_surrogate_to_utf32(_1stSurrogateCandidate, _2ndSurrogateCandidate);

         return 2;

      }
      else
      {

         return -1;

      }

   }
   else
   {

      *output = _1stSurrogateCandidate; // just candidate so, not surrogay-tea

      return 1;

   }

}


inline strsize ansi_to_wd32_char(::wd32_character * output, const char * input, strsize srclen)
{

   ::wd32_character u32 = 0;

   byte c;
   char extraBytesToRead = utf8_e(*input);
   int len = extraBytesToRead + 1;
   if (srclen < len) return -1;
   if (*input == '\0') return -1;
   switch (extraBytesToRead)
   {
   case 5:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 4:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 3:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 2:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 1:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 0:
      c = *input;
      if (c == '\0') return -1;
      u32 += c;
      input++;
   }

   u32 -= (::wd32_character)utf8_o(extraBytesToRead);
   *output = u32;

   return len;

}


inline i64 _ansi_to_wd32_char(const char ** ppsz, strsize * psrclen)
{

   ::wd32_character u32 = 0;

   auto used_len = ansi_to_wd32_char(&u32, *ppsz, *psrclen);

   if (used_len < 0)
   {

      return -1;

   }

   *ppsz += used_len;

   *psrclen -= used_len;

   return u32;

}


/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (::wd32_character)0x0000FFFD
#define UNI_MAX_BMP (::wd32_character)0x0000FFFF
#define UNI_MAX_UTF16 (::wd32_character)0x0010FFFF
#define UNI_MAX_UTF32 (::wd32_character)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (::wd32_character)0x0010FFFF
#define UNI_SUR_HIGH_START  (::wd32_character)0xD800
#define UNI_SUR_HIGH_END    (::wd32_character)0xDBFF
#define UNI_SUR_LOW_START   (::wd32_character)0xDC00
#define UNI_SUR_LOW_END     (::wd32_character)0xDFFF
//#define false	   0
//#define true	    1
// /* --------------------------------------------------------------------- */
// status_resut wd32_to_wd16 (
// 	const UTF32** sourceStart, const UTF32* sourceEnd,
// 	UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
//     ConversionResult result = conversionOK;
//     const UTF32* source = *sourceStart;
//     UTF16* target = *targetStart;
//     while (source < sourceEnd) {
// 	UTF32 ch;
// 	if (target >= targetEnd) {
// 	    result = targetExhausted; break;
// 	}
// 	ch = *source++;
// 	if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
// 	    /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
// 	    if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
// 		if (flags == strictConversion) {
// 		    --source; /* return to the illegal value itself */
// 		    result = sourceIllegal;
// 		    break;
// 		} else {
// 		    *target++ = UNI_REPLACEMENT_CHAR;
// 		}
// 	    } else {
// 		*target++ = (UTF16)ch; /* normal case */
// 	    }
// 	} else if (ch > UNI_MAX_LEGAL_UTF32) {
// 	    if (flags == strictConversion) {
// 		result = sourceIllegal;
// 	    } else {
// 		*target++ = UNI_REPLACEMENT_CHAR;
// 	    }
// 	} else {
// 	    /* target is a character in range 0xFFFF - 0x10FFFF. */
// 	    if (target + 1 >= targetEnd) {
// 		--source; /* Back up source pointer! */
// 		result = targetExhausted; break;
// 	    }
// 	    ch -= halfBase;
// 	    *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
// 	    *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
// 	}
//     }
//     *sourceStart = source;
//     *targetStart = target;
//     return result;
// }


inline strsize wd32_to_wd16_char(::wd16_character * target, ::wd32_character u32)
{

   const int halfShift = 10; /* used for shifting by 10 bits */
   const ::wd32_character halfBase = 0x0010000UL;
   const ::wd32_character halfMask = 0x3FFUL;

   if (u32 <= UNI_MAX_BMP)
   {

      /* Target is a character <= 0xFFFF */
      /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
      if (u32 >= UNI_SUR_HIGH_START && u32 <= UNI_SUR_LOW_END)
      {

         //if (flags == strictConversion) {
         //--source; /* return to the illegal value itself */
         //result = sourceIllegal;
         return -1;

      }

      *target = (::wd16_character)u32; /* normal case */

      return 1;

   }
   else if (u32 > UNI_MAX_LEGAL_UTF32)
   {

      return -1;

   }

   u32 -= halfBase;

   *target++ = (::wd16_character)((u32 >> halfShift) + UNI_SUR_HIGH_START);

   *target = (::wd16_character)((u32 & halfMask) + UNI_SUR_LOW_START);

   return 2;

}


inline strsize wd16_to_ansi_char_len(const ::wd16_character ** ppu16a, strsize * plen)
{

   ::wd32_character u32;

   auto used_len = wd16_to_wd32_char(&u32, *ppu16a, *plen);

   if (used_len < 0)
   {

      return -1;

   }

   *plen -= used_len;

   *ppu16a += used_len;

   return wd32_to_ansi_char_len(u32);

}


inline strsize wd16_to_ansi_char(char * psz, const ::wd16_character ** ppu16a, strsize * plen)
{

   ::wd32_character u32;

   auto used_len = wd16_to_wd32_char(&u32, *ppu16a, *plen);

   if (used_len < 0)
   {

      return -1;

   }

   *plen -= used_len;

   *ppu16a += used_len;

   return wd32_to_ansi_char(psz, u32);

}


inline strsize wd16_to_wd32_char_len(const ::wd16_character * input, strsize len)
{

   if (len < 1)
   {

      return -1;

   }

   auto _1stSurrogateCandidate = input[0];

   if (_1stSurrogateCandidate == 0)
   {

      return 0;

   }

   if (utf16_is_2nd_surrogate(_1stSurrogateCandidate))
   {

      // ERROR Maticki

      return -1;

   }
   else if (utf16_is_1st_surrogate(_1stSurrogateCandidate))
   {

      if (len < 2)
      {

         return -1;

      }

      auto _2ndSurrogateCandidate = input[1];

      if (utf16_is_2nd_surrogate(_2ndSurrogateCandidate))
      {

         return 2;

      }
      else
      {

         return -1;

      }

   }
   else
   {

      return 1;

   }

}


inline strsize wd32_to_ansi_char(char * psz, ::wd32_character wch)
{

   if (wch <= 0)
   {
      return 0;
   }
   else if (wch <= 0x7F)
   {
      // Plain ASCII
      psz[0] = (char)wch;
      return 1;
   }
   else if (wch <= 0x07FF)
   {
      // 2-byte unicode
      psz[0] = (char)(((wch >> 6) & 0x1F) | 0xC0);
      psz[1] = (char)(((wch >> 0) & 0x3F) | 0x80);
      return 2;
   }
   else if (wch <= 0xFFFF)
   {
      // 3-byte unicode
      psz[0] = (char)(((wch >> 12) & 0x0F) | 0xE0);
      psz[1] = (char)(((wch >> 6) & 0x3F) | 0x80);
      psz[2] = (char)(((wch >> 0) & 0x3F) | 0x80);
      return 3;
   }
   else if (wch <= 0x10FFFF)
   {
      // 4-byte unicode
      psz[0] = (char)(((wch >> 18) & 0x07) | 0xF0);
      psz[1] = (char)(((wch >> 12) & 0x3F) | 0x80);
      psz[2] = (char)(((wch >> 6) & 0x3F) | 0x80);
      psz[3] = (char)(((wch >> 0) & 0x3F) | 0x80);
      return 4;
   }
   else
   {
      return -1;
   }
}


#if WCHAR_T_SIZE == 16


inline strsize utf8_to_unichar_len(const ::ansi_character * psz) { return ansi_to_wd16_len(psz, string_safe_length(psz)); }
inline strsize utf8_to_unichar_len(const ::ansi_character * psz, strsize srclen) { return ansi_to_wd16_len(psz, srclen); }
inline strsize utf8_to_unichar(::wd16_character * pwsz, const ::ansi_character * psz) { return ansi_to_wd16(pwsz, psz, string_safe_length(psz)); }
inline strsize utf8_to_unichar(::wd16_character * pwsz, const ::ansi_character * psz, strsize srclen) { return ansi_to_wd16(pwsz, psz, srclen); }


inline strsize unichar_to_utf8_len(const ::wd16_character * pwsz) { return wd16_to_ansi_len(pwsz, string_safe_length(pwsz)); }
inline strsize unichar_to_utf8_len(const ::wd16_character * pwsz, strsize srclen) { return wd16_to_ansi_len(pwsz, srclen); }
inline strsize unichar_to_utf8(char * psz, const ::wd16_character * pwsz) { return wd16_to_ansi(psz, pwsz, string_safe_length(pwsz)); }
inline strsize unichar_to_utf8(char * psz, const ::wd16_character * pwsz, strsize srclen) { return wd16_to_ansi(psz, pwsz, srclen); }


#else


inline strsize utf8_to_unichar_len(const ::ansi_character * psz, strsize srclen) { return ansi_to_wd32_len(psz, srclen); }
inline strsize utf8_to_unichar(::wd32_character * pwsz, const ::ansi_character * psz, strsize srclen) { return ansi_to_wd32(pwsz, psz, srclen); }


inline strsize unichar_to_utf8_len(const ::wd32_character * pwsz, strsize srclen) { return wd32_to_ansi_len(pwsz, srclen); }
inline strsize unichar_to_utf8(char * psz, const ::wd32_character * pwsz, strsize srclen) { return wd32_to_ansi(psz, pwsz, srclen); }


#endif



