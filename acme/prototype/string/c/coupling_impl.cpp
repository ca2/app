#include "framework.h"

#include <string.h>
#include <wchar.h>
#include <string.h>

CLASS_DECL_ACME ::ansi_character * ansi_dup(const_char_pointer psz) ;

CLASS_DECL_ACME character_count ansi_len(const_char_pointer psz);

CLASS_DECL_ACME ::ansi_character * ansi_cat(::ansi_character * pszDst, const_char_pointer psz) ;

CLASS_DECL_ACME ::ansi_character * ansi_cpy(::ansi_character * pszDst, const_char_pointer psz) ;

CLASS_DECL_ACME ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const_char_pointer psz, character_count len) ;

CLASS_DECL_ACME const_char_pointer ansi_chr(const_char_pointer psz1, ::ansi_character ch) ;

CLASS_DECL_ACME const_char_pointer ansi_pbrk(const_char_pointer psz, const_char_pointer pszCharsToFind) ;

CLASS_DECL_ACME ::ansi_character * ansi_tok_r(::ansi_character * psz, const_char_pointer sep, ::ansi_character ** state);

CLASS_DECL_ACME const_char_pointer ansi_rchr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME int ansi_cmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int ansi_ncmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer ansi_str(const_char_pointer psz, const_char_pointer pszFind);

CLASS_DECL_ACME ::ansi_character ansi_tolower(::ansi_character ch) { return __ansitolower(ch); }

CLASS_DECL_ACME ::ansi_character ansi_toupper(::ansi_character ch) { return __ansitoupper(ch); }

#ifdef WINDOWS

CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz) { return _strlwr(psz); }

CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s) { _strlwr_s(psz, s); return psz; }

CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz) { return _strupr(psz); }

CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s) { _strupr_s(psz, s); return psz; }

#else

CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz) { return __ansilwr(psz); }

CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s) { __ansilwr_s(psz, s); return psz; }

CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz) { return __ansiupr(psz); }

CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s) { __ansiupr_s(psz, s); return psz; }

#endif

CLASS_DECL_ACME const_char_pointer ansi_ichr(const_char_pointer psz1, ::ansi_character ch) { return __ansiichr(psz1, ch); }


CLASS_DECL_ACME int ansi_icmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int ansi_nicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer ansi_istr(const_char_pointer psz, const_char_pointer pszFind) { return __ansiistr(psz, pszFind); }

//CLASS_DECL_ACME ::ansi_character * u64tostr(unsigned long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __u64toansi(u, buf, iBase, edigitcase); }

//CLASS_DECL_ACME ::ansi_character * i64tostr(unsigned long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __long_longtoansi(u, buf, iBase, edigitcase); }

CLASS_DECL_ACME int ansi_coll(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME int ansi_ncoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME int ansi_icoll(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int ansi_nicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME character_count ansi_spn(const_char_pointer psz1, const_char_pointer psz2) ;

CLASS_DECL_ACME character_count ansi_cspn(const_char_pointer psz1, const_char_pointer psz2) ;

















#if WCHAR_T_SIZE == 16


CLASS_DECL_ACME character_count wd16_len(const ::wd16_character * psz) { return wcslen(psz); }
CLASS_DECL_ACME character_count wd32_len(const ::wd32_character * psz) { return __wd32len(psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscat(pszDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cat(pszDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscpy(pszDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cpy(pszDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len) { return wcsncpy(pszDst, psz, len); }
CLASS_DECL_ACME ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len) { return __wd32ncpy(pszDst, psz, len); }

CLASS_DECL_ACME const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return wcschr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32chr(psz1, ch); }

CLASS_DECL_ACME ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
CLASS_DECL_ACME ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return __wd32pbrk(psz, pszCharsToFind); }

CLASS_DECL_ACME ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(psz, sep, state); }
CLASS_DECL_ACME ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(psz, sep, state); }

CLASS_DECL_ACME const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return wcsrchr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32rchr(psz1, ch); }

CLASS_DECL_ACME int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscmp(psz1, psz2); }
CLASS_DECL_ACME int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(psz1, psz2); }

CLASS_DECL_ACME int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return wcsncmp(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncmp(psz1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return wcsstr(psz, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32str(psz, pszFind); }

CLASS_DECL_ACME ::wd16_character wd16_tolower(::wd16_character ch) { return towlower(ch); }
CLASS_DECL_ACME ::wd32_character wd32_tolower(::wd32_character ch) { return __wd32tolower(ch); }

CLASS_DECL_ACME ::wd16_character wd16_toupper(::wd16_character ch) { return towupper(ch); }
CLASS_DECL_ACME ::wd32_character wd32_toupper(::wd32_character ch) { return __wd32toupper(ch); }

CLASS_DECL_ACME ::wd16_character * wd16_lwr(::wd16_character * psz) { return _wcslwr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(psz); }

CLASS_DECL_ACME ::wd16_character * wd16_lwr_s(::wd16_character * psz, character_count s) { _wcslwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { __wd32lwr_s(psz, s);  return psz; }

CLASS_DECL_ACME ::wd16_character * wd16_upr(::wd16_character * psz) { return _wcsupr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(psz); }

CLASS_DECL_ACME ::wd16_character * wd16_upr_s(::wd16_character * psz, character_count s) { _wcsupr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { __wd32upr_s(psz, s);  return psz; }

CLASS_DECL_ACME const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(psz1, ch); }

CLASS_DECL_ACME int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicmp(psz1, psz2); }
CLASS_DECL_ACME int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icmp(psz1, psz2); }

CLASS_DECL_ACME int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsnicmp(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicmp(psz1, psz2, s); }
CLASS_DECL_ACME int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd16_nicmp(psz1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(psz, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(psz, pszFind); }

CLASS_DECL_ACME ::wd16_character * u64towd16(unsigned long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character * pend=nullptr; return __u64towd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * u64towd32(unsigned long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character * pend=nullptr; return __u64towd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME ::wd16_character * i64towd16(long long i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character * pend=nullptr; return __long_longtowd16(i, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * i64towd32(long long i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character * pend=nullptr; return __long_longtowd32(i, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscoll(psz1, psz2); }
CLASS_DECL_ACME int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(psz1, psz2); }

CLASS_DECL_ACME int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsncoll(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncoll(psz1, psz2, s); }

CLASS_DECL_ACME int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicoll(psz1, psz2); }
CLASS_DECL_ACME int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(psz1, psz2); }

CLASS_DECL_ACME int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsnicoll(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicoll(psz1, psz2, s); }

CLASS_DECL_ACME character_count wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcsspn(psz1, psz2); }
CLASS_DECL_ACME character_count wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32spn(psz1, psz2); }

CLASS_DECL_ACME character_count wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscspn(psz1, psz2); }
CLASS_DECL_ACME character_count wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cspn(psz1, psz2); }

#elif WCHAR_T_SIZE == 32

CLASS_DECL_ACME character_count wd16_len(const ::wd16_character * psz) { return __wd16len(psz); }
CLASS_DECL_ACME character_count wd32_len(const ::wd32_character * psz) { return wcslen(psz); }
CLASS_DECL_ACME character_count wide_len(const ::wide_character * psz) { return wd32_len(psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cat(pszDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscat(pszDst, psz); }
CLASS_DECL_ACME ::wide_character * wide_cat(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cat(pszDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cpy(pszDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscpy(pszDst, psz); }
CLASS_DECL_ACME ::wide_character * wide_cpy(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cpy(pszDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len) { return __wd16ncpy(pszDst, psz, len); }
CLASS_DECL_ACME ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len) { return wcsncpy(pszDst, psz, len); }
CLASS_DECL_ACME ::wide_character * wide_ncpy(::wide_character * pszDst, const ::wide_character * psz, character_count len) { return wd32_ncpy(pszDst, psz, len); }

//CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(psz, pszFind); }
//CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(psz, pszFind); }

CLASS_DECL_ACME const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16chr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return wcschr(psz1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_chr(const ::wide_character * psz1, ::wide_character ch) { return wd32_chr(psz1, ch); }

CLASS_DECL_ACME ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return __wd16pbrk(psz, pszCharsToFind); }
CLASS_DECL_ACME ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
CLASS_DECL_ACME ::wide_character * wide_pbrk(::wide_character * psz, const ::wide_character * pszCharsToFind) { return wd32_pbrk(psz, pszCharsToFind); }

CLASS_DECL_ACME ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(psz, sep, state); }
CLASS_DECL_ACME ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(psz, sep, state); }
CLASS_DECL_ACME ::wide_character * wide_tok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state) { return wd32_tok_r(psz, sep, state); }

CLASS_DECL_ACME const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16rchr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return wcsrchr(psz1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_rchr(const ::wide_character * psz1, ::wide_character ch) { return wd32_rchr(psz1, ch); }

CLASS_DECL_ACME int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(psz1, psz2); }
CLASS_DECL_ACME int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscmp(psz1, psz2); }
CLASS_DECL_ACME int wide_cmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cmp(psz1, psz2); }

CLASS_DECL_ACME int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16ncmp(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s)
{
#ifdef WINDOWS
   return wcsncmp(psz1, psz2, s);
#else
   return __wd32ncmp(psz1, psz2, s);
#endif
   
}
CLASS_DECL_ACME int wide_ncmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_ncmp(psz1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(psz, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(psz, pszFind); }
CLASS_DECL_ACME const ::wide_character * wide_str(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_str(psz, pszFind); }

CLASS_DECL_ACME ::wd16_character wd16_tolower(::wd16_character ch) { return __wd16tolower(ch); }
CLASS_DECL_ACME ::wd32_character wd32_tolower(::wd32_character ch) { return __wd32tolower(ch); }
CLASS_DECL_ACME ::wide_character wide_tolower(::wide_character ch) { return __wd32tolower(ch); }

CLASS_DECL_ACME ::wd16_character wd16_toupper(::wd16_character ch) { return __wd16toupper(ch); }
CLASS_DECL_ACME ::wd32_character wd32_toupper(::wd32_character ch) { return __wd32toupper(ch); }
CLASS_DECL_ACME ::wide_character wide_toupper(::wide_character ch) { return __wd32toupper(ch); }


CLASS_DECL_ACME ::wd16_character * wd16_lwr(::wd16_character * psz) { return __wd16lwr(psz); }
CLASS_DECL_ACME ::wd16_character * wd16_lwr_s(::wd16_character * psz, character_count s) { __wd16lwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wd16_character * wd16_upr(::wd16_character * psz) { return __wd16upr(psz); }
CLASS_DECL_ACME ::wd16_character * wd16_upr_s(::wd16_character * psz, character_count s) { __wd16upr_s(psz, s);  return psz; }


#ifdef WINDOWS

CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return wcslwr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { _wcslwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return wcsupr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { _wcsupr_s(psz, s);  return psz; }

CLASS_DECL_ACME ::wide_character * wide_lwr(::wd32_character * psz) { return wcslwr(psz); }
CLASS_DECL_ACME ::wide_character * wide_lwr_s(::wd32_character * psz, character_count s) { _wcslwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wide_character * wide_upr(::wd32_character * psz) { return wcsupr(psz); }
CLASS_DECL_ACME ::wide_character * wide_upr_s(::wd32_character * psz, character_count s) { _wcsupr_s(psz, s);  return psz; }

#else

CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { __wd32lwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(psz); }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { __wd32upr_s(psz, s);  return psz; }

CLASS_DECL_ACME ::wide_character * wide_lwr(::wide_character * psz) { return wd32_lwr(psz); }
CLASS_DECL_ACME ::wide_character * wide_lwr_s(::wide_character * psz, character_count s) { wd32_lwr_s(psz, s);  return psz; }
CLASS_DECL_ACME ::wide_character * wide_upr(::wide_character * psz) { return wd32_upr(psz); }
CLASS_DECL_ACME ::wide_character * wide_upr_s(::wide_character * psz, character_count s) { wd32_upr_s(psz, s);  return psz; }

#endif

CLASS_DECL_ACME const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(psz1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(psz1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_ichr(const ::wide_character * psz1, ::wd32_character ch) { return wd32_ichr(psz1, ch); }

CLASS_DECL_ACME int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icmp(psz1, psz2); }
CLASS_DECL_ACME int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2)
{
#ifdef WINDOWS
   return wcsicmp(psz1, psz2);
#else
   return __wd32icmp(psz1, psz2);
#endif
   
}
CLASS_DECL_ACME int wide_icmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icmp(psz1, psz2); }

CLASS_DECL_ACME int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16nicmp(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s)
{
#ifdef WINDOWS
   return wcsnicmp(psz1, psz2, s);
#else
   return __wd32nicmp(psz1, psz2, s);
#endif
}
CLASS_DECL_ACME int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_nicmp(psz1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(psz, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(psz, pszFind); }
CLASS_DECL_ACME const ::wd32_character * widew_istr(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_istr(psz, pszFind); }

CLASS_DECL_ACME ::wd16_character * u64towd16(unsigned long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character *pend=nullptr;return __u64towd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * u64towd32(unsigned long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __u64towd32(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wide_character * u64towide(unsigned long long u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __u64towd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME ::wd16_character * i64towd16(long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character *pend=nullptr;return __long_longtowd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * i64towd32(long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __long_longtowd32(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wide_character * i64towide(long long u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __long_longtowd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(psz1, psz2); }
CLASS_DECL_ACME int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscoll(psz1, psz2); }
CLASS_DECL_ACME int wide_coll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_coll(psz1, psz2); }

CLASS_DECL_ACME int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16ncoll(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncoll(psz1, psz2, s); }
CLASS_DECL_ACME int wide_ncoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_ncoll(psz1, psz2, s); }

CLASS_DECL_ACME int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icoll(psz1, psz2); }
CLASS_DECL_ACME int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(psz1, psz2); }
CLASS_DECL_ACME int wide_icoll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icoll(psz1, psz2); }

CLASS_DECL_ACME int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16nicoll(psz1, psz2, s); }
CLASS_DECL_ACME int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicoll(psz1, psz2, s); }
CLASS_DECL_ACME int wide_nicoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_nicoll(psz1, psz2, s); }

CLASS_DECL_ACME character_count wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16spn(psz1, psz2); }
CLASS_DECL_ACME character_count wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcsspn(psz1, psz2); }
CLASS_DECL_ACME character_count wide_spn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_spn(psz1, psz2); }

CLASS_DECL_ACME character_count wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cspn(psz1, psz2); }
CLASS_DECL_ACME character_count wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscspn(psz1, psz2); }
CLASS_DECL_ACME character_count wide_cspn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cspn(psz1, psz2); }


#else

#error "Not supported ::wide_character int_size"

#endif






