#pragma once


#include "acme/prototype/string/x/x_charcategory.h"
#include "acme/prototype/string/x/x_defines.h"
#include "acme/prototype/string/x/x_tables.h"


CLASS_DECL_ACME int trailingBytesForUTF8(::ansi_character ch);


inline int utf8_unicode_length(int c) { return trailingBytesForUTF8(c) + 1; }


// return UTF8 offset
inline int utf8_o(char cExtraBytes);


inline char utf8_e(unsigned char c);



CLASS_DECL_ACME character_count utf8_len(const_char_pointer psz);


template < typename CHARACTER, typename CHARACTER_COUNT >
inline CHARACTER *unicode_next(CHARACTER *psz, CHARACTER_COUNT *piRemaining)
   requires(sizeof(CHARACTER) == 1);


template<typename CHARACTER, typename CHARACTER_COUNT>
inline CHARACTER *unicode_next(CHARACTER *psz, CHARACTER_COUNT *piRemaining)
   requires(sizeof(CHARACTER) == 2);


template<typename CHARACTER, typename CHARACTER_COUNT>
inline CHARACTER *unicode_next(CHARACTER *psz, CHARACTER_COUNT *piRemaining)
   requires(sizeof(CHARACTER) == 4);


template < typename CHARACTER >
inline CHARACTER * unicode_next(CHARACTER * psz)
{

   return unicode_next(psz, (int *)nullptr);

}


template<typename CHARACTER>
inline CHARACTER *unicode_prior(CHARACTER *psz, const non_const<CHARACTER> *piRemaining)
   requires(sizeof(CHARACTER) == 1);


template<typename CHARACTER>
inline CHARACTER *unicode_prior(CHARACTER *psz, const non_const<CHARACTER> *piRemaining)
   requires(sizeof(CHARACTER) == 2);


template<typename CHARACTER>
inline CHARACTER *unicode_prior(CHARACTER *psz, const non_const<CHARACTER> *piRemaining)
   requires(sizeof(CHARACTER) == 4);


//CLASS_DECL_ACME const_char_pointer unicode_next(const_char_pointer psz);
//CLASS_DECL_ACME const_char_pointer unicode_prior(const_char_pointer psz, const_char_pointer pszBeg);


CLASS_DECL_ACME character_count ansi_to_ansi_len(const_char_pointer pcwsz, character_count input_size = -1);
CLASS_DECL_ACME character_count ansi_to_ansi_len2(const_char_pointer pcwsz, character_count & input_size);
CLASS_DECL_ACME character_count ansi_to_ansi(const_char_pointer *pwsz, const const_char_pointer *pcwsz,
                                             character_count input_size = -1);



CLASS_DECL_ACME character_count wd16_to_wd32_len(const ::wd16_character* pcwsz, character_count input_size = -1);
CLASS_DECL_ACME character_count wd16_to_wd32_len2(const ::wd16_character *pcwsz, character_count & input_size);
CLASS_DECL_ACME character_count wd16_to_wd32(::wd32_character* pwsz, const ::wd16_character* pcwsz, character_count input_size = -1);


CLASS_DECL_ACME ::wd32_character* wd16_to_wd32_dup(const ::wd16_character* pcwsz, character_count input_size = -1);



CLASS_DECL_ACME character_count wd32_to_wd16_len(const ::wd32_character* pcwsz, character_count input_size = -1);
CLASS_DECL_ACME character_count wd32_to_wd16_len2(const ::wd32_character *pcwsz, character_count & input_size);
CLASS_DECL_ACME character_count wd32_to_wd16(::wd16_character * pwsz, const ::wd32_character* pcwsz, character_count input_size = -1);

CLASS_DECL_ACME ::wd16_character* wd32_to_wd16_dup(const ::wd16_character* pcwsz, character_count input_size = -1);



CLASS_DECL_ACME character_count utf16_len(const ::wd16_character* psz);


//CLASS_DECL_ACME const ::wd16_character * unicode_next(const ::wd16_character* psz, int * piError);
//CLASS_DECL_ACME const ::wd16_character *unicode_prior(const ::wd16_character *psz, const ::wd16_character *pszBeg);

CLASS_DECL_ACME character_count wd16_to_wd16_len(const wd16_character * pcwsz, character_count input_size = -1);
CLASS_DECL_ACME character_count wd16_to_wd16_len2(const wd16_character * pcwsz, character_count &input_size);
CLASS_DECL_ACME character_count wd16_to_wd16(wd16_character *pwsz, const wd16_character *pcwsz,
                                             character_count input_size = -1);




CLASS_DECL_ACME character_count ansi_to_wd16_len(const_char_pointer psz, character_count srclen = -1);
CLASS_DECL_ACME character_count ansi_to_wd16_len2(const_char_pointer psz, character_count & srclen);
CLASS_DECL_ACME character_count ansi_to_wd16(::wd16_character* pwsz, const_char_pointer psz, character_count srclen = -1);

CLASS_DECL_ACME ::wd16_character * ansi_to_wd16_dup(const_char_pointer input, character_count input_size);


CLASS_DECL_ACME character_count wd16_to_ansi_len(const ::wd16_character* pwsz, character_count srclen = -1);
CLASS_DECL_ACME character_count wd16_to_ansi_len2(const ::wd16_character *pwsz, character_count & srclen);
CLASS_DECL_ACME character_count wd16_to_ansi(char* psz, const ::wd16_character* pwsz, character_count srclen = -11);

CLASS_DECL_ACME char * wd16_to_ansi_dup(const ::wd16_character * input, character_count input_size);














CLASS_DECL_ACME character_count utf32_len(const ::wd32_character* psz);


//CLASS_DECL_ACME const ::wd32_character *unicode_next(const ::wd32_character *psz, int *piError);
//CLASS_DECL_ACME const ::wd32_character *unicode_prior(const ::wd32_character *psz, const ::wd32_character *pszBeg);


CLASS_DECL_ACME character_count wd32_to_wd32_len(const wd32_character * pcwsz, character_count input_size = -1);
CLASS_DECL_ACME character_count wd32_to_wd32_len2(const wd32_character * pcwsz, character_count &input_size);
CLASS_DECL_ACME character_count wd32_to_wd32(wd32_character *pwsz, const wd32_character *pcwsz,
                                             character_count input_size = -1);


CLASS_DECL_ACME character_count ansi_to_wd32_len(const_char_pointer psz, character_count srclen = -1);
CLASS_DECL_ACME character_count ansi_to_wd32_len2(const_char_pointer psz, character_count & srclen);
CLASS_DECL_ACME character_count ansi_to_wd32(::wd32_character* pwsz, const_char_pointer psz, character_count srclen = -1);

CLASS_DECL_ACME ::wd32_character* ansi_to_wd32_dup(const_char_pointer pcwsz, character_count input_size = -1);


CLASS_DECL_ACME character_count wd32_to_ansi_len(const ::wd32_character* pwsz, character_count srclen = -1);
CLASS_DECL_ACME character_count wd32_to_ansi_len2(const ::wd32_character *pwsz, character_count & srclen);
CLASS_DECL_ACME character_count wd32_to_ansi(char* psz, const ::wd32_character* pwsz, character_count srclen = -1);

CLASS_DECL_ACME char * wd32_to_ansi_dup(const ::wd32_character * input, character_count input_size);


/**
 * Encode a code int_point using UTF-8
 *
 * @adaptor ca2
 * @authorr Ondrhej Hrusjka <ondra@ondrovo.com>
 * @license MIT
 *
 * @paramrr out - output buffer (minimum 5 characters), will be 0-terminated
 * @paramrr utf - code int_point 0-0x10FFFF
 * @returnr number of bytes on success, 0 on failure (also produces U+FFFD, which uses 3 bytes)
 */
inline character_count wd32_to_ansi_char_len(::wd32_character wch);

inline character_count wd32_to_ansi_char(char * psz, ::wd32_character wch);


inline character_count replacement_utf8_char(char * psz)
{
    psz[0] = (char) 0xEF;
    psz[1] = (char) 0xBF;
    psz[2] = (char) 0xBD;
    return 3;
}

// The High Surrogate is first UTF-16 character
// The Losh Surrogate is secnd UTF-16 codepointchar
// I suggest if you want to transmit a face, you can use <img tag>
// or if your font support a cad library with 512-bit wide encoding, you can øcreate <matter type="cad/application-x">512-bit wide of honda civic tweaked by john peter etcetra and used by ann (brakes light dimmed (don't tell the police))</test>


//inline int_bool utf16_is_surrogate(::wd16_character unsigned short) { return (unsigned short - 0xd800u) < 2048u; }
//inline int utf16_is_high_surrogate(::wd16_character uc) { return (uc & 0xfc00) == 0xd800; }
//inline int utf16_is_low_surrogate(::wd16_character uc) { return (uc & 0xfc00) == 0xdc00; }


inline character_count wd16_to_wd32_char_len(const ::wd16_character * input, character_count len);


inline character_count wd16_to_wd32_char(::wd32_character * output, const ::wd16_character * input, character_count len);


inline character_count wd16_to_ansi_char_len(const ::wd16_character ** ppu16a, character_count * plen);


inline character_count wd16_to_ansi_char(char * psz, const ::wd16_character ** ppu16a, character_count * plen);


#if WCHAR_T_SIZE == 16


inline character_count utf8_to_unichar_len(const_char_pointer psz);
inline character_count utf8_to_unichar_len(const_char_pointer psz, character_count srclen);
inline character_count utf8_to_unichar(::wd16_character * pwsz, const_char_pointer psz);
inline character_count utf8_to_unichar(::wd16_character * pwsz, const_char_pointer psz, character_count srclen);


inline character_count unichar_to_utf8_len(const ::wd16_character * pwsz);
inline character_count unichar_to_utf8_len(const ::wd16_character * pwsz, character_count srclen);
inline character_count unichar_to_utf8(char * psz, const ::wd16_character * pwsz);
inline character_count unichar_to_utf8(char * psz, const ::wd16_character * pwsz, character_count srclen);


#else


inline character_count utf8_to_unichar_len(const_char_pointer psz, character_count srclen = -1);
inline character_count utf8_to_unichar(::wd32_character* pwsz, const_char_pointer psz, character_count srclen = -1);


inline character_count unichar_to_utf8_len(const ::wd32_character* pwsz, character_count srclen = -1);
inline character_count unichar_to_utf8(char* psz, const ::wd32_character* pwsz, character_count srclen = -1);


#endif


inline character_count ansi_to_wd32_char(::wd32_character * output, const_char_pointer input, character_count srclen);


inline long long _ansi_to_wd32_char(const_char_pointer *ppsz, character_count * psrclen);


inline character_count wd32_to_wd16_char(::wd16_character * pwd16sz, ::wd32_character wd32ch);
