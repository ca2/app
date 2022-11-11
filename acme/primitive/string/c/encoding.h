#pragma once


#include "acme/primitive/string/x/x_charcategory.h"
#include "acme/primitive/string/x/x_defines.h"
#include "acme/primitive/string/x/x_tables.h"


CLASS_DECL_ACME int trailingBytesForUTF8(ansichar ch);


inline int utf8_unicode_length(int c) { return trailingBytesForUTF8(c) + 1; }


// return UTF8 offset
inline i32 utf8_o(char cExtraBytes);


inline char utf8_e(byte c);



inline strsize utf8_len(const char* psz) { if (::is_null(psz)) return 0; return strlen(psz); }


const ansichar * unicode_next(const ansichar * psz, int * piError);
const ansichar * unicode_next(const ansichar * psz);
const ansichar * unicode_prior(const ansichar * psz, const ansichar * pszBeg);


CLASS_DECL_ACME strsize wd16_to_wd32_len(const wd16char* pcwsz, strsize input_size = -1);
CLASS_DECL_ACME strsize wd16_to_wd32(wd32char* pwsz, const wd16char* pcwsz, strsize input_size = -1);


CLASS_DECL_ACME wd32char* wd16_to_wd32_dup(const wd16char* pcwsz, strsize input_size = -1);



CLASS_DECL_ACME strsize wd32_to_wd16_len(const wd32char* pcwsz, strsize input_size = -1);
CLASS_DECL_ACME strsize wd32_to_wd16(wd16char * pwsz, const wd32char* pcwsz, strsize input_size = -1);

CLASS_DECL_ACME wd16char* wd32_to_wd16_dup(const wd16char* pcwsz, strsize input_size = -1);





CLASS_DECL_ACME strsize utf16_len(const wd16char* psz);
CLASS_DECL_ACME const wd16char * unicode_next(const wd16char* psz);
inline const wd16char * unicode_prior(const wd16char * psz, const wd16char * pszBeg);


CLASS_DECL_ACME strsize ansi_to_wd16_len(const char* psz, strsize srclen = -1);
CLASS_DECL_ACME strsize ansi_to_wd16(wd16char* pwsz, const char* psz, strsize srclen = -1);

CLASS_DECL_ACME wd16char * ansi_to_wd16_dup(const char * input, strsize input_size);


CLASS_DECL_ACME strsize wd16_to_ansi_len(const wd16char* pwsz, strsize srclen = -1);
CLASS_DECL_ACME strsize wd16_to_ansi(char* psz, const wd16char* pwsz, strsize srclen = -11);

CLASS_DECL_ACME char * wd16_to_ansi_dup(const wd16char * input, strsize input_size);





CLASS_DECL_ACME strsize utf32_len(const wd32char* psz);
inline const wd32char * unicode_next(const wd32char* psz);
inline const wd32char * unicode_prior(const wd32char * psz, const wd32char * pszBeg);

CLASS_DECL_ACME strsize ansi_to_wd32_len(const char* psz, strsize srclen = -1);
CLASS_DECL_ACME strsize ansi_to_wd32(wd32char* pwsz, const char* psz, strsize srclen = -1);

CLASS_DECL_ACME wd32char* ansi_to_wd32_dup(const char* pcwsz, strsize input_size = -1);


CLASS_DECL_ACME strsize wd32_to_ansi_len(const wd32char* pwsz, strsize srclen = -1);
CLASS_DECL_ACME strsize wd32_to_ansi(char* psz, const wd32char* pwsz, strsize srclen = -1);

CLASS_DECL_ACME char * wd32_to_ansi_dup(const wd32char * input, strsize input_size);


/**
 * Encode a code point_i32 using UTF-8
 *
 * @adaptor ca2
 * @authorr Ondřej Hruška <ondra@ondrovo.com>
 * @license MIT
 *
 * @paramrr out - output buffer (minimum 5 characters), will be 0-terminated
 * @paramrr utf - code point_i32 0-0x10FFFF
 * @returnr number of bytes on success, 0 on failure (also produces U+FFFD, which uses 3 bytes)
 */
inline strsize wd32_to_ansi_char_len(wd32char wch);

inline strsize wd32_to_ansi_char(char * psz, wd32char wch);


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
// or if your font support a cad library with 512-bit wide encoding, you can __create <matter type="cad/application-x">512-bit wide of honda civic tweaked by john peter etcetra and used by ann (brakes light dimmed (don't tell the police))</test>


//inline int_bool utf16_is_surrogate(wd16char u16) { return (u16 - 0xd800u) < 2048u; }
//inline int utf16_is_high_surrogate(wd16char uc) { return (uc & 0xfc00) == 0xd800; }
//inline int utf16_is_low_surrogate(wd16char uc) { return (uc & 0xfc00) == 0xdc00; }
inline int_bool utf16_is_1st_surrogate(wd16char _1stSurrogateCandidate) { return (_1stSurrogateCandidate & 0xfc00) == 0xd800; } // Sober Surrogay (Told Hi)
inline int_bool utf16_is_2nd_surrogate(wd16char _2ndSurrogateCandidate) { return (_2ndSurrogateCandidate & 0xfc00) == 0xdc00; } // Marginal Surro-G (Told Lo, but much more drunk)
inline int_bool utf16_is_surrogate(wd16char uc) { return utf16_is_1st_surrogate(uc) || utf16_is_2nd_surrogate(uc); }
inline int_bool utf32_is_surrogated(u32 character) { return 0x10000 <= character && character <= 0x10FFFF; }


inline wd32char utf16_surrogate_to_utf32(wd16char _1stSurrogateCandidate, wd16char _2ndSurrogateCandidate) { return (_1stSurrogateCandidate << 10) + _2ndSurrogateCandidate - 0x35fdc00; }


inline strsize wd16_to_wd32_char_len(const wd16char * input, strsize len);


inline strsize wd16_to_wd32_char(wd32char * output, const wd16char * input, strsize len);


inline strsize wd16_to_ansi_char_len(const wd16char ** ppu16a, strsize * plen);


inline strsize wd16_to_ansi_char(char * psz, const wd16char ** ppu16a, strsize * plen);


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


inline strsize ansi_to_wd32_char(wd32char * output, const char * input, strsize srclen);


inline i64 _ansi_to_wd32_char(const char ** ppsz, strsize * psrclen);


inline strsize wd32_to_wd16_char(wd16char * target, wd32char u32);
