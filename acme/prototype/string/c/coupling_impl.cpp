#include "framework.h"

#include <string.h>
#include <wchar.h>
#include <string.h>

CLASS_DECL_ACME ::ansi_character * ansi_dup(const ::ansi_character * psz) ;

CLASS_DECL_ACME character_count ansi_len(const ::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * ansi_cat(::ansi_character * pszDst, const ::ansi_character * psz) ;

CLASS_DECL_ACME ::ansi_character * ansi_cpy(::ansi_character * pszDst, const ::ansi_character * psz) ;

CLASS_DECL_ACME ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const ::ansi_character * psz, character_count len) ;

CLASS_DECL_ACME const ::ansi_character * ansi_chr(const ::ansi_character * psz1, ::ansi_character ch) ;

CLASS_DECL_ACME const ::ansi_character * ansi_pbrk(const ::ansi_character * psz, const ::ansi_character * pszCharsToFind) ;

CLASS_DECL_ACME ::ansi_character * ansi_tok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state);

CLASS_DECL_ACME const ::ansi_character * ansi_rchr(const ::ansi_character * psz1, ::ansi_character ch);

CLASS_DECL_ACME int ansi_cmp(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int ansi_ncmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s);

CLASS_DECL_ACME const ::ansi_character * ansi_str(const ::ansi_character * psz, const ::ansi_character * pszFind);

CLASS_DECL_ACME ::ansi_character ansi_tolower(::ansi_character ch) { return __ansitolower(ch); }

CLASS_DECL_ACME ::ansi_character ansi_toupper(::ansi_character ch) { return __ansitoupper(ch); }

#ifdef WINDOWS

CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz) { return _strlwr(scopedstr); }

CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s) { _strlwr_s(scopedstr, s); return psz; }

CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz) { return _strupr(scopedstr); }

CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s) { _strupr_s(scopedstr, s); return psz; }

#else

CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz) { return __ansilwr(scopedstr); }

CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s) { __ansilwr_s(scopedstr, s); return psz; }

CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz) { return __ansiupr(scopedstr); }

CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s) { __ansiupr_s(scopedstr, s); return psz; }

#endif

CLASS_DECL_ACME const ::ansi_character * ansi_ichr(const ::ansi_character * psz1, ::ansi_character ch) { return __ansiichr(scopedstr1, ch); }


CLASS_DECL_ACME int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s);

CLASS_DECL_ACME const ::ansi_character * ansi_istr(const ::ansi_character * psz, const ::ansi_character * pszFind) { return __ansiistr(scopedstr, pszFind); }

//CLASS_DECL_ACME ::ansi_character * u64tostr(unsigned long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __u64toansi(u, buf, iBase, edigitcase); }

//CLASS_DECL_ACME ::ansi_character * i64tostr(unsigned long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __long_longtoansi(u, buf, iBase, edigitcase); }

CLASS_DECL_ACME int ansi_coll(const ::ansi_character * psz1, const ::ansi_character * psz2);
CLASS_DECL_ACME int ansi_ncoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s);

CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s);

CLASS_DECL_ACME character_count ansi_spn(const ::ansi_character * psz1, const ::ansi_character * psz2) ;

CLASS_DECL_ACME character_count ansi_cspn(const ::ansi_character * psz1, const ::ansi_character * psz2) ;

















#if WCHAR_T_SIZE == 16


CLASS_DECL_ACME character_count wd16_len(const ::wd16_character * psz) { return wcslen(scopedstr); }
CLASS_DECL_ACME character_count wd32_len(const ::wd32_character * psz) { return __wd32len(scopedstr); }

CLASS_DECL_ACME ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscat(scopedstrDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cat(scopedstrDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscpy(scopedstrDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cpy(scopedstrDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len) { return wcsncpy(scopedstrDst, psz, len); }
CLASS_DECL_ACME ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len) { return __wd32ncpy(scopedstrDst, psz, len); }

CLASS_DECL_ACME const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return wcschr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32chr(scopedstr1, ch); }

CLASS_DECL_ACME ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return wcspbrk(scopedstr, pszCharsToFind); }
CLASS_DECL_ACME ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return __wd32pbrk(scopedstr, pszCharsToFind); }

CLASS_DECL_ACME ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(scopedstr, sep, state); }
CLASS_DECL_ACME ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(scopedstr, sep, state); }

CLASS_DECL_ACME const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return wcsrchr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32rchr(scopedstr1, ch); }

CLASS_DECL_ACME int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return wcsncmp(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return wcsstr(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32str(scopedstr, pszFind); }

CLASS_DECL_ACME ::wd16_character wd16_tolower(::wd16_character ch) { return towlower(ch); }
CLASS_DECL_ACME ::wd32_character wd32_tolower(::wd32_character ch) { return __wd32tolower(ch); }

CLASS_DECL_ACME ::wd32_character wd16_toupper(::wd16_character ch) { return towupper(ch); }
CLASS_DECL_ACME ::wd32_character wd32_toupper(::wd32_character ch) { return __wd32toupper(ch); }

CLASS_DECL_ACME ::wd16_character * wd16_lwr(::wd16_character * psz) { return _wcslwr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(scopedstr); }

CLASS_DECL_ACME ::wd16_character * wd16_lwr_s(::wd16_character * psz, character_count s) { _wcslwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { __wd32lwr_s(scopedstr, s);  return psz; }

CLASS_DECL_ACME ::wd16_character * wd16_upr(::wd16_character * psz) { return _wcsupr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(scopedstr); }

CLASS_DECL_ACME ::wd16_character * wd16_upr_s(::wd16_character * psz, character_count s) { _wcsupr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { __wd32upr_s(scopedstr, s);  return psz; }

CLASS_DECL_ACME const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(scopedstr1, ch); }

CLASS_DECL_ACME int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icmp(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsnicmp(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicmp(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd16_nicmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(scopedstr, pszFind); }

CLASS_DECL_ACME ::wd16_character * u64towd16(unsigned long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character * pend=nullptr; return __u64towd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * u64towd32(unsigned long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character * pend=nullptr; return __u64towd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME ::wd16_character * i64towd16(long long i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character * pend=nullptr; return __long_longtowd16(i, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * i64towd32(long long i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character * pend=nullptr; return __long_longtowd32(i, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscoll(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsncoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncoll(scopedstr1, psz2, s); }

CLASS_DECL_ACME int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicoll(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return _wcsnicoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicoll(scopedstr1, psz2, s); }

CLASS_DECL_ACME character_count wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcsspn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32spn(scopedstr1, psz2); }

CLASS_DECL_ACME character_count wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscspn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cspn(scopedstr1, psz2); }

#elif WCHAR_T_SIZE == 32

CLASS_DECL_ACME character_count wd16_len(const ::wd16_character * psz) { return __wd16len(scopedstr); }
CLASS_DECL_ACME character_count wd32_len(const ::wd32_character * psz) { return wcslen(scopedstr); }
CLASS_DECL_ACME character_count wide_len(const ::wide_character * psz) { return wd32_len(scopedstr); }

CLASS_DECL_ACME ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cat(scopedstrDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscat(scopedstrDst, psz); }
CLASS_DECL_ACME ::wide_character * wide_cat(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cat(scopedstrDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cpy(scopedstrDst, psz); }
CLASS_DECL_ACME ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscpy(scopedstrDst, psz); }
CLASS_DECL_ACME ::wide_character * wide_cpy(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cpy(scopedstrDst, psz); }

CLASS_DECL_ACME ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len) { return __wd16ncpy(scopedstrDst, psz, len); }
CLASS_DECL_ACME ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len) { return wcsncpy(scopedstrDst, psz, len); }
CLASS_DECL_ACME ::wide_character * wide_ncpy(::wide_character * pszDst, const ::wide_character * psz, character_count len) { return wd32_ncpy(scopedstrDst, psz, len); }

//CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(scopedstr, pszFind); }
//CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(scopedstr, pszFind); }

CLASS_DECL_ACME const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16chr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return wcschr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_chr(const ::wide_character * psz1, ::wide_character ch) { return wd32_chr(scopedstr1, ch); }

CLASS_DECL_ACME ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return __wd16pbrk(scopedstr, pszCharsToFind); }
CLASS_DECL_ACME ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return wcspbrk(scopedstr, pszCharsToFind); }
CLASS_DECL_ACME ::wide_character * wide_pbrk(::wide_character * psz, const ::wide_character * pszCharsToFind) { return wd32_pbrk(scopedstr, pszCharsToFind); }

CLASS_DECL_ACME ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(scopedstr, sep, state); }
CLASS_DECL_ACME ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(scopedstr, sep, state); }
CLASS_DECL_ACME ::wide_character * wide_tok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state) { return wd32_tok_r(scopedstr, sep, state); }

CLASS_DECL_ACME const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16rchr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return wcsrchr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_rchr(const ::wide_character * psz1, ::wide_character ch) { return wd32_rchr(scopedstr1, ch); }

CLASS_DECL_ACME int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wide_cmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cmp(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16ncmp(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s)
{
#ifdef WINDOWS
   return wcsncmp(scopedstr1, psz2, s);
#else
   return __wd32ncmp(scopedstr1, psz2, s);
#endif
   
}
CLASS_DECL_ACME int wide_ncmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_ncmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wide_character * wide_str(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_str(scopedstr, pszFind); }

CLASS_DECL_ACME ::wd16_character wd16_tolower(::wd16_character ch) { return __wd16tolower(ch); }
CLASS_DECL_ACME ::wd32_character wd32_tolower(::wd32_character ch) { return __wd32tolower(ch); }
CLASS_DECL_ACME ::wide_character wide_tolower(::wide_character ch) { return __wd32tolower(ch); }

CLASS_DECL_ACME ::wd32_character wd16_toupper(::wd16_character ch) { return __wd16toupper(ch); }
CLASS_DECL_ACME ::wd32_character wd32_toupper(::wd32_character ch) { return __wd32toupper(ch); }
CLASS_DECL_ACME ::wide_character wide_toupper(::wide_character ch) { return __wd32toupper(ch); }


CLASS_DECL_ACME ::wd16_character * wd16_lwr(::wd16_character * psz) { return __wd16lwr(scopedstr); }
CLASS_DECL_ACME ::wd16_character * wd16_lwr_s(::wd16_character * psz, character_count s) { __wd16lwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wd16_character * wd16_upr(::wd16_character * psz) { return __wd16upr(scopedstr); }
CLASS_DECL_ACME ::wd16_character * wd16_upr_s(::wd16_character * psz, character_count s) { __wd16upr_s(scopedstr, s);  return psz; }


#ifdef WINDOWS

CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return wcslwr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { _wcslwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return wcsupr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { _wcsupr_s(scopedstr, s);  return psz; }

CLASS_DECL_ACME ::wide_character * wide_lwr(::wd32_character * psz) { return wcslwr(scopedstr); }
CLASS_DECL_ACME ::wide_character * wide_lwr_s(::wd32_character * psz, character_count s) { _wcslwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wide_character * wide_upr(::wd32_character * psz) { return wcsupr(scopedstr); }
CLASS_DECL_ACME ::wide_character * wide_upr_s(::wd32_character * psz, character_count s) { _wcsupr_s(scopedstr, s);  return psz; }

#else

CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s) { __wd32lwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(scopedstr); }
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s) { __wd32upr_s(scopedstr, s);  return psz; }

CLASS_DECL_ACME ::wide_character * wide_lwr(::wide_character * psz) { return wd32_lwr(scopedstr); }
CLASS_DECL_ACME ::wide_character * wide_lwr_s(::wide_character * psz, character_count s) { wd32_lwr_s(scopedstr, s);  return psz; }
CLASS_DECL_ACME ::wide_character * wide_upr(::wide_character * psz) { return wd32_upr(scopedstr); }
CLASS_DECL_ACME ::wide_character * wide_upr_s(::wide_character * psz, character_count s) { wd32_upr_s(scopedstr, s);  return psz; }

#endif

CLASS_DECL_ACME const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(scopedstr1, ch); }
CLASS_DECL_ACME const ::wide_character * wide_ichr(const ::wide_character * psz1, ::wd32_character ch) { return wd32_ichr(scopedstr1, ch); }

CLASS_DECL_ACME int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2)
{
#ifdef WINDOWS
   return wcsicmp(scopedstr1, psz2);
#else
   return __wd32icmp(scopedstr1, psz2);
#endif
   
}
CLASS_DECL_ACME int wide_icmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icmp(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16nicmp(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s)
{
#ifdef WINDOWS
   return wcsnicmp(scopedstr1, psz2, s);
#else
   return __wd32nicmp(scopedstr1, psz2, s);
#endif
}
CLASS_DECL_ACME int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_nicmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(scopedstr, pszFind); }
CLASS_DECL_ACME const ::wd32_character * widew_istr(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_istr(scopedstr, pszFind); }

CLASS_DECL_ACME ::wd16_character * u64towd16(unsigned long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character *pend=nullptr;return __u64towd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * u64towd32(unsigned long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __u64towd32(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wide_character * u64towide(unsigned long long u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __u64towd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME ::wd16_character * i64towd16(long long u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { ::wd16_character *pend=nullptr;return __long_longtowd16(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wd32_character * i64towd32(long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __long_longtowd32(u, buf, iBase, edigitcase, pend); }
CLASS_DECL_ACME ::wide_character * i64towide(long long u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { ::wd32_character *pend=nullptr;return __long_longtowd32(u, buf, iBase, edigitcase, pend); }

CLASS_DECL_ACME int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscoll(scopedstr1, psz2); }
CLASS_DECL_ACME int wide_coll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_coll(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16ncoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32ncoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wide_ncoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_ncoll(scopedstr1, psz2, s); }

CLASS_DECL_ACME int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icoll(scopedstr1, psz2); }
CLASS_DECL_ACME int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(scopedstr1, psz2); }
CLASS_DECL_ACME int wide_icoll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icoll(scopedstr1, psz2); }

CLASS_DECL_ACME int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s) { return __wd16nicoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s) { return __wd32nicoll(scopedstr1, psz2, s); }
CLASS_DECL_ACME int wide_nicoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s) { return wd32_nicoll(scopedstr1, psz2, s); }

CLASS_DECL_ACME character_count wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16spn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcsspn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wide_spn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_spn(scopedstr1, psz2); }

CLASS_DECL_ACME character_count wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cspn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscspn(scopedstr1, psz2); }
CLASS_DECL_ACME character_count wide_cspn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cspn(scopedstr1, psz2); }


#else

#error "Not supported ::wide_character int_size"

#endif






