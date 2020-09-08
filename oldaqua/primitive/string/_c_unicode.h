#pragma once






// return UTF8 offset
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


inline strsize utf8_len(const char* psz) { if (::c_is_null(psz)) return 0; return strlen(psz); }
CLASS_DECL_AQUA const char* utf8_inc(const char* psz);




CLASS_DECL_AQUA strsize wd16_to_wd32_len(const wd16char* pcwsz, strsize input_size = -1);
CLASS_DECL_AQUA strsize wd16_to_wd32(wd32char* pwsz, const wd16char* pcwsz, strsize input_size = -1);

CLASS_DECL_AQUA wd32char* wd16_to_wd32_dup(const wd16char* pcwsz, strsize input_size = -1);



CLASS_DECL_AQUA strsize wd32_to_wd16_len(const wd32char* pcwsz, strsize input_size = -1);
CLASS_DECL_AQUA strsize wd32_to_wd16(wd16char * pwsz, const wd32char* pcwsz, strsize input_size = -1);

CLASS_DECL_AQUA wd16char* wd32_to_wd16_dup(const wd16char* pcwsz, strsize input_size = -1);









CLASS_DECL_AQUA strsize utf16_len(const wd16char* psz);
CLASS_DECL_AQUA const wd16char* utf16_inc(const wd16char* psz);

CLASS_DECL_AQUA strsize ansi_to_wd16_len(const char* psz, strsize srclen = -1);
CLASS_DECL_AQUA strsize ansi_to_wd16(wd16char* pwsz, const char* psz, strsize srclen = -1);

CLASS_DECL_AQUA wd16char * ansi_to_wd16_dup(const char * input, strsize input_size);


CLASS_DECL_AQUA strsize wd16_to_ansi_len(const wd16char* pwsz, strsize srclen = -1);
CLASS_DECL_AQUA strsize wd16_to_ansi(char* psz, const wd16char* pwsz, strsize srclen = -11);

CLASS_DECL_AQUA char * wd16_to_ansi_dup(const wd16char * input, strsize input_size);





CLASS_DECL_AQUA strsize utf32_len(const wd32char* psz);
CLASS_DECL_AQUA const wd32char* utf32_inc(const wd32char* psz);

CLASS_DECL_AQUA strsize ansi_to_wd32_len(const char* psz, strsize srclen = -1);
CLASS_DECL_AQUA strsize ansi_to_wd32(wd32char* pwsz, const char* psz, strsize srclen = -1);

CLASS_DECL_AQUA wd32char* ansi_to_wd32_dup(const char* pcwsz, strsize input_size = -1);


CLASS_DECL_AQUA strsize wd32_to_ansi_len(const wd32char* pwsz, strsize srclen = -1);
CLASS_DECL_AQUA strsize wd32_to_ansi(char* psz, const wd32char* pwsz, strsize srclen = -1);

CLASS_DECL_AQUA char * wd32_to_ansi_dup(const wd32char * input, strsize input_size);


/**
 * Encode a code point using UTF-8
 *
 * @adaptor ca2
 * @authorr Ondřej Hruška <ondra@ondrovo.com>
 * @license MIT
 *
 * @paramrr out - output buffer (min 5 characters), will be 0-terminated
 * @paramrr utf - code point 0-0x10FFFF
 * @returnr number of bytes on success, 0 on failure (also produces U+FFFD, which uses 3 bytes)
 */
inline strsize wd32_to_ansi_char_len(wd32char wch)
{
    if(wch == 0)
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


inline strsize wd32_to_ansi_char(char* psz, wd32char wch)
{

    if (wch <= 0)
    {
        return 0;
    }
    else if (wch <= 0x7F)
    {
        // Plain ASCII
        psz[0] = (char) wch;
        return 1;
    }
    else if (wch <= 0x07FF)
    {
        // 2-byte unicode
        psz[0] = (char) (((wch >> 6) & 0x1F) | 0xC0);
        psz[1] = (char) (((wch >> 0) & 0x3F) | 0x80);
        return 2;
    }
    else if (wch <= 0xFFFF)
    {
        // 3-byte unicode
        psz[0] = (char) (((wch >> 12) & 0x0F) | 0xE0);
        psz[1] = (char) (((wch >>  6) & 0x3F) | 0x80);
        psz[2] = (char) (((wch >>  0) & 0x3F) | 0x80);
        return 3;
    }
    else if (wch <= 0x10FFFF)
    {
        // 4-byte unicode
        psz[0] = (char) (((wch >> 18) & 0x07) | 0xF0);
        psz[1] = (char) (((wch >> 12) & 0x3F) | 0x80);
        psz[2] = (char) (((wch >>  6) & 0x3F) | 0x80);
        psz[3] = (char) (((wch >>  0) & 0x3F) | 0x80);
        return 4;
    }
    else
    {
        return -1;
    }
}


inline strsize replacement_utf8_char(char * psz)
{
    psz[0] = (char) 0xEF;
    psz[1] = (char) 0xBF;
    psz[2] = (char) 0xBD;
    return 3;
}

// The High Surrogate is first UTF-16 character
// The Losh Surrogate is secnd UTF-16 codepointchar
// I suggest if you want to transmit a face, you can use <img tag>
// or if your font support a cad library with 512-bit wide encoding, you can __create <object type="cad/application-x">512-bit wide of honda civic tweaked by john peter etcetra and used by ann (brakes light dimmed (don't tell the police))</test>


//inline int_bool utf16_is_surrogate(wd16char u16) { return (u16 - 0xd800u) < 2048u; }
//inline int utf16_is_high_surrogate(wd16char uc) { return (uc & 0xfc00) == 0xd800; }
//inline int utf16_is_low_surrogate(wd16char uc) { return (uc & 0xfc00) == 0xdc00; }
inline int_bool utf16_is_1st_surrogate(wd16char _1stSurrogateCandidate) { return (_1stSurrogateCandidate & 0xfc00) == 0xd800; } // Sober Surrogay (Told Hi)
inline int_bool utf16_is_2nd_surrogate(wd16char _2ndSurrogateCandidate) { return (_2ndSurrogateCandidate & 0xfc00) == 0xdc00; } // Marginal Surro-G (Told Lo, but much more drunk)
inline int_bool utf16_is_surrogate(wd16char uc) { return utf16_is_1st_surrogate(uc) || utf16_is_2nd_surrogate(uc); }
inline int_bool utf32_is_surrogated(u32 character) { return 0x10000 <= character && character <= 0x10FFFF; }


inline wd32char utf16_surrogate_to_utf32(wd16char _1stSurrogateCandidate, wd16char _2ndSurrogateCandidate) { return (_1stSurrogateCandidate << 10) + _2ndSurrogateCandidate - 0x35fdc00; }


inline strsize wd16_to_wd32_char_len(const wd16char* input, strsize len)
{

    if(len < 1)
    {

        return -1;

    }

    auto _1stSurrogateCandidate = input[0];

    if(_1stSurrogateCandidate == 0)
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

        if(len < 2)
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


inline strsize wd16_to_wd32_char(wd32char * output, const wd16char * input, strsize len)
{

    if(len < 1)
    {

        return -1;

    }

    auto _1stSurrogateCandidate = input[0];

    if(_1stSurrogateCandidate == 0)
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

        if(len < 2)
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


inline strsize wd16_to_ansi_char_len(const wd16char ** ppu16a, strsize * plen)
{

   wd32char u32;

   auto used_len = wd16_to_wd32_char(&u32, *ppu16a, *plen);

   if(used_len < 0)
   {

      return -1;

   }

   *plen -= used_len;

   *ppu16a += used_len;

   return wd32_to_ansi_char_len(u32);

}


inline strsize wd16_to_ansi_char(char* psz, const wd16char ** ppu16a, strsize * plen)
{

   wd32char u32;

   auto used_len = wd16_to_wd32_char(&u32, *ppu16a, *plen);

   if(used_len < 0)
   {

      return -1;

   }

   *plen -= used_len;

   *ppu16a += used_len;

   return wd32_to_ansi_char(psz, u32);

}



#if WCHAR_T_SIZE == 16


inline strsize utf8_to_unichar_len(const char* psz, strsize srclen = -1) { return ansi_to_wd16_len(psz, srclen); }
inline strsize utf8_to_unichar(wd16char* pwsz, const char* psz, strsize srclen = -1) { return ansi_to_wd16(pwsz, psz, srclen); }


inline strsize unichar_to_utf8_len(const wd16char* pwsz, strsize srclen = -1) { return wd16_to_ansi_len(pwsz, srclen); }
inline strsize unichar_to_utf8(char * psz, const wd16char* pwsz, strsize srclen = -1) { return wd16_to_ansi(psz, pwsz, srclen); }


#else


inline strsize utf8_to_unichar_len(const char* psz, strsize srclen = -1) { return ansi_to_wd32_len(psz, srclen); }
inline strsize utf8_to_unichar(wd32char* pwsz, const char* psz, strsize srclen = -1) { return ansi_to_wd32(pwsz, psz, srclen); }


inline strsize unichar_to_utf8_len(const wd32char* pwsz, strsize srclen = -1) { return wd32_to_ansi_len(pwsz, srclen); }
inline strsize unichar_to_utf8(char* psz, const wd32char* pwsz, strsize srclen = -1) { return wd32_to_ansi(psz, pwsz, srclen); }


#endif





inline const char * __utf8_inc(const char * psz, strsize srclen)
{
   char len =  1 + trailingBytesForUTF8(*psz);
   if(len > srclen) return nullptr;
   if(len == 0)      return nullptr;
   if(*psz++ == 0)   return nullptr;
   if(len == 1)      return psz;
   if(*psz++ == 0)   return nullptr;
   if(len == 2)      return psz;
   if(*psz++ == 0)   return nullptr;
   if(len == 3)      return psz;
   if(*psz++ == 0)   return nullptr;
   if(len == 4)      return psz;
   if(*psz++ == 0)   return nullptr;
   if(len == 5)      return psz;
   if(*psz++ == 0)   return nullptr;
   if(len == 6)      return psz;
   return nullptr;
}


inline strsize ansi_to_wd32_char(wd32char * output, const char * input, strsize srclen)
{

   wd32char u32 = 0;

   byte c;
   char extraBytesToRead = utf8_e(*input);
   int len = extraBytesToRead + 1;
   if(srclen < len) return -1;
   if(*input == '\0') return -1;
   switch(extraBytesToRead)
   {
   case 5:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 4:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 3:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 2:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 1:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      u32 <<= 6;
      input++;
   case 0:
      c = *input;
      if(c == '\0') return -1;
      u32 += c;
      input++;
   }
   u32 -= (wd32char) utf8_o(extraBytesToRead);
   *output = u32;
   return len;
}


inline i64 _ansi_to_wd32_char(const char ** ppsz, strsize * psrclen)
{

   wd32char u32 = 0;

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
#define UNI_REPLACEMENT_CHAR (wd32char)0x0000FFFD
#define UNI_MAX_BMP (wd32char)0x0000FFFF
#define UNI_MAX_UTF16 (wd32char)0x0010FFFF
#define UNI_MAX_UTF32 (wd32char)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (wd32char)0x0010FFFF
#define UNI_SUR_HIGH_START  (wd32char)0xD800
#define UNI_SUR_HIGH_END    (wd32char)0xDBFF
#define UNI_SUR_LOW_START   (wd32char)0xDC00
#define UNI_SUR_LOW_END     (wd32char)0xDFFF
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


inline strsize wd32_to_wd16_char(wd16char * target, wd32char u32)
{
   const int halfShift  = 10; /* used for shifting by 10 bits */
   const wd32char halfBase = 0x0010000UL;
   const wd32char halfMask = 0x3FFUL;

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

        *target = (wd16char)u32; /* normal case */

        return 1;

	}
    else if (u32 > UNI_MAX_LEGAL_UTF32)
    {
        return -1;
	}

    u32 -= halfBase;

    *target++ = (wd16char)((u32 >> halfShift) + UNI_SUR_HIGH_START);

    *target = (wd16char)((u32 & halfMask) + UNI_SUR_LOW_START);

    return 2;

}







