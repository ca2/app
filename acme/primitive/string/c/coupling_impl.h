#pragma once


inline ::ansi_character * ansi_dup(const ::ansi_character * psz) { return _strdup(psz); }

inline strsize ansi_len(const ::ansi_character * psz) { return strlen(psz); }

inline ::ansi_character * ansi_cat(::ansi_character * pszDst, const ::ansi_character * psz) { return strcat(pszDst, psz); }

inline ::ansi_character * ansi_cpy(::ansi_character * pszDst, const ::ansi_character * psz) { return strcpy(pszDst, psz); }

inline ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const ::ansi_character * psz, strsize len) { return strncpy(pszDst, psz, len); }

inline const ::ansi_character * ansi_chr(const ::ansi_character * psz1, ::ansi_character ch) { return strchr(psz1, ch); }

inline ::ansi_character * ansi_pbrk(::ansi_character * psz, const ::ansi_character * pszCharsToFind) { return strpbrk(psz, pszCharsToFind); }


inline ::ansi_character * ansi_tok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state)
{

#ifdef WINDOWS

    return strtok_s(psz, sep, state);

#else

    return strtok_r(psz, sep, state);

#endif

}

inline const ::ansi_character * ansi_rchr(const ::ansi_character * psz1, ::ansi_character ch) { return strrchr(psz1, ch); }

inline int ansi_cmp(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(psz1, psz2); }

inline int ansi_ncmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return strncmp(psz1, psz2, s); }

inline const ::ansi_character * ansi_str(const ::ansi_character * psz, const ::ansi_character * pszFind) { return strstr(psz, pszFind); }

inline ::ansi_character ansi_tolower(::ansi_character ch) { return tolower(ch); }

inline ::ansi_character ansi_toupper(::ansi_character ch) { return toupper(ch); }

#ifdef WINDOWS

inline ::ansi_character * ansi_lwr(::ansi_character * psz) { return _strlwr(psz); }

inline ::ansi_character * ansi_lwr_s(::ansi_character * psz, strsize s) { _strlwr_s(psz, s); return psz; }

inline ::ansi_character * ansi_upr(::ansi_character * psz) { return _strupr(psz); }

inline ::ansi_character * ansi_upr_s(::ansi_character * psz, strsize s) { _strupr_s(psz, s); return psz; }

#else

inline ::ansi_character * ansi_lwr(::ansi_character * psz) { return __ansilwr(psz); }

inline ::ansi_character * ansi_lwr_s(::ansi_character * psz, strsize s) { __ansilwr_s(psz, s); return psz; }

inline ::ansi_character * ansi_upr(::ansi_character * psz) { return __ansiupr(psz); }

inline ::ansi_character * ansi_upr_s(::ansi_character * psz, strsize s) { __ansiupr_s(psz, s); return psz; }

#endif

inline const ::ansi_character * ansi_ichr(const ::ansi_character * psz1, ::ansi_character ch) { return __ansiichr(psz1, ch); }


inline int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

inline int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}

inline const ::ansi_character * ansi_istr(const ::ansi_character * psz, const ::ansi_character * pszFind) { return __ansiistr(psz, pszFind); }

//inline ::ansi_character * u64tostr(::u64 u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __u64toansi(u, buf, iBase, edigitcase); }

//inline ::ansi_character * i64tostr(::u64 u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase) { return __i64toansi(u, buf, iBase, edigitcase); }

inline int ansi_coll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(psz1, psz2); }

inline int ansi_ncoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return strncmp(psz1, psz2, s); }

inline int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

inline int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}

inline strsize ansi_spn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strspn(psz1, psz2); }

inline strsize ansi_cspn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcspn(psz1, psz2); }

















#if WCHAR_T_SIZE == 16


inline strsize wd16_len(const ::wd16_character * psz) { return wcslen(psz); }
inline strsize wd32_len(const ::wd32_character * psz) { return __wd32len(psz); }

inline ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscat(pszDst, psz); }
inline ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cat(pszDst, psz); }

inline ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return wcscpy(pszDst, psz); }
inline ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return __wd32cpy(pszDst, psz); }

inline ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len) { return wcsncpy(pszDst, psz, len); }
inline ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, strsize len) { return __wd32ncpy(pszDst, psz, len); }

inline const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return wcschr(psz1, ch); }
inline const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32chr(psz1, ch); }

inline ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
inline ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return __wd32pbrk(psz, pszCharsToFind); }

inline ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(psz, sep, state); }
inline ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(psz, sep, state); }

inline const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return wcsrchr(psz1, ch); }
inline const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32rchr(psz1, ch); }

inline int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscmp(psz1, psz2); }
inline int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(psz1, psz2); }

inline int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return wcsncmp(psz1, psz2, s); }
inline int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32ncmp(psz1, psz2, s); }

inline const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return wcsstr(psz, pszFind); }
inline const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32str(psz, pszFind); }

inline ::wd16_character wd16_tolower(::wd16_character ch) { return towlower(ch); }
inline ::wd32_character wd32_tolower(::wd32_character ch) { return __wd32tolower(ch); }

inline ::wd32_character wd16_toupper(::wd16_character ch) { return towupper(ch); }
inline ::wd32_character wd32_toupper(::wd32_character ch) { return __wd32toupper(ch); }

inline ::wd16_character * wd16_lwr(::wd16_character * psz) { return _wcslwr(psz); }
inline ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(psz); }

inline ::wd16_character * wd16_lwr_s(::wd16_character * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline ::wd32_character * wd32_lwr_s(::wd32_character * psz, strsize s) { __wd32lwr_s(psz, s);  return psz; }

inline ::wd16_character * wd16_upr(::wd16_character * psz) { return _wcsupr(psz); }
inline ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(psz); }

inline ::wd16_character * wd16_upr_s(::wd16_character * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }
inline ::wd32_character * wd32_upr_s(::wd32_character * psz, strsize s) { __wd32upr_s(psz, s);  return psz; }

inline const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(psz1, ch); }
inline const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(psz1, ch); }

inline int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicmp(psz1, psz2); }
inline int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icmp(psz1, psz2); }

inline int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return _wcsnicmp(psz1, psz2, s); }
inline int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32nicmp(psz1, psz2, s); }
inline int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, strsize s) { return wd16_nicmp(psz1, psz2, s); }

inline const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(psz, pszFind); }
inline const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(psz, pszFind); }

inline ::wd16_character * u64towd16(::u64 u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { return __u64towd16(u, buf, iBase, edigitcase); }
inline ::wd32_character * u64towd32(::u64 u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }

inline ::wd16_character * i64towd16(::i64 i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { return __i64towd16(i, buf, iBase, edigitcase); }
inline ::wd32_character * i64towd32(::i64 i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(i, buf, iBase, edigitcase); }

inline int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscoll(psz1, psz2); }
inline int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cmp(psz1, psz2); }

inline int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return _wcsncoll(psz1, psz2, s); }
inline int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32ncoll(psz1, psz2, s); }

inline int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return _wcsicoll(psz1, psz2); }
inline int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(psz1, psz2); }

inline int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return _wcsnicoll(psz1, psz2, s); }
inline int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32nicoll(psz1, psz2, s); }

inline strsize wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcsspn(psz1, psz2); }
inline strsize wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32spn(psz1, psz2); }

inline strsize wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wcscspn(psz1, psz2); }
inline strsize wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32cspn(psz1, psz2); }

#elif WCHAR_T_SIZE == 32

inline strsize wd16_len(const ::wd16_character * psz) { return __wd16len(psz); }
inline strsize wd32_len(const ::wd32_character * psz) { return wcslen(psz); }
inline strsize wide_len(const ::wide_character * psz) { return wd32_len(psz); }

inline ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cat(pszDst, psz); }
inline ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscat(pszDst, psz); }
inline ::wide_character * wide_cat(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cat(pszDst, psz); }

inline ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz) { return __wd16cpy(pszDst, psz); }
inline ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz) { return wcscpy(pszDst, psz); }
inline ::wide_character * wide_cpy(::wide_character * pszDst, const ::wide_character * psz) { return wd32_cpy(pszDst, psz); }

inline ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len) { return __wd16ncpy(pszDst, psz, len); }
inline ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, strsize len) { return wcsncpy(pszDst, psz, len); }
inline ::wide_character * wide_ncpy(::wide_character * pszDst, const ::wide_character * psz, strsize len) { return wd32_ncpy(pszDst, psz, len); }

//inline const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(psz, pszFind); }
//inline const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(psz, pszFind); }

inline const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16chr(psz1, ch); }
inline const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch) { return wcschr(psz1, ch); }
inline const ::wide_character * wide_chr(const ::wide_character * psz1, ::wide_character ch) { return wd32_chr(psz1, ch); }

inline ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind) { return __wd16pbrk(psz, pszCharsToFind); }
inline ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
inline ::wide_character * wide_pbrk(::wide_character * psz, const ::wide_character * pszCharsToFind) { return wd32_pbrk(psz, pszCharsToFind); }

inline ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state) { return __wd16tok_r(psz, sep, state); }
inline ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state) { return __wd32tok_r(psz, sep, state); }
inline ::wide_character * wide_tok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state) { return wd32_tok_r(psz, sep, state); }

inline const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16rchr(psz1, ch); }
inline const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch) { return wcsrchr(psz1, ch); }
inline const ::wide_character * wide_rchr(const ::wide_character * psz1, ::wide_character ch) { return wd32_rchr(psz1, ch); }

inline int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(psz1, psz2); }
inline int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscmp(psz1, psz2); }
inline int wide_cmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cmp(psz1, psz2); }

inline int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return __wd16ncmp(psz1, psz2, s); }
inline int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s)
{
#ifdef WINDOWS
   return wcsncmp(psz1, psz2, s);
#else
   return __wd32ncmp(psz1, psz2, s);
#endif
   
}
inline int wide_ncmp(const ::wide_character * psz1, const ::wide_character * psz2, strsize s) { return wd32_ncmp(psz1, psz2, s); }

inline const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16str(psz, pszFind); }
inline const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind) { return wcsstr(psz, pszFind); }
inline const ::wide_character * wide_str(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_str(psz, pszFind); }

inline ::wd16_character wd16_tolower(::wd16_character ch) { return __wd16tolower(ch); }
inline ::wd32_character wd32_tolower(::wd32_character ch) { return towlower(ch); }
inline ::wide_character wide_tolower(::wide_character ch) { return wd32_tolower(ch); }

inline ::wd32_character wd16_toupper(::wd16_character ch) { return __wd16toupper(ch); }
inline ::wd32_character wd32_toupper(::wd32_character ch) { return towupper(ch); }
inline ::wide_character wide_toupper(::wide_character ch) { return wd32_toupper(ch); }


inline ::wd16_character * wd16_lwr(::wd16_character * psz) { return __wd16lwr(psz); }
inline ::wd16_character * wd16_lwr_s(::wd16_character * psz, strsize s) { __wd16lwr_s(psz, s);  return psz; }
inline ::wd16_character * wd16_upr(::wd16_character * psz) { return __wd16upr(psz); }
inline ::wd16_character * wd16_upr_s(::wd16_character * psz, strsize s) { __wd16upr_s(psz, s);  return psz; }


#ifdef WINDOWS

inline ::wd32_character * wd32_lwr(::wd32_character * psz) { return wcslwr(psz); }
inline ::wd32_character * wd32_lwr_s(::wd32_character * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline ::wd32_character * wd32_upr(::wd32_character * psz) { return wcsupr(psz); }
inline ::wd32_character * wd32_upr_s(::wd32_character * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }

inline ::wide_character * wide_lwr(::wd32_character * psz) { return wcslwr(psz); }
inline ::wide_character * wide_lwr_s(::wd32_character * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline ::wide_character * wide_upr(::wd32_character * psz) { return wcsupr(psz); }
inline ::wide_character * wide_upr_s(::wd32_character * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }

#else

inline ::wd32_character * wd32_lwr(::wd32_character * psz) { return __wd32lwr(psz); }
inline ::wd32_character * wd32_lwr_s(::wd32_character * psz, strsize s) { __wd32lwr_s(psz, s);  return psz; }
inline ::wd32_character * wd32_upr(::wd32_character * psz) { return __wd32upr(psz); }
inline ::wd32_character * wd32_upr_s(::wd32_character * psz, strsize s) { __wd32upr_s(psz, s);  return psz; }

inline ::wide_character * wide_lwr(::wide_character * psz) { return wd32_lwr(psz); }
inline ::wide_character * wide_lwr_s(::wide_character * psz, strsize s) { wd32_lwr_s(psz, s);  return psz; }
inline ::wide_character * wide_upr(::wide_character * psz) { return wd32_upr(psz); }
inline ::wide_character * wide_upr_s(::wide_character * psz, strsize s) { wd32_upr_s(psz, s);  return psz; }

#endif

inline const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch) { return __wd16ichr(psz1, ch); }
inline const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch) { return __wd32ichr(psz1, ch); }
inline const ::wide_character * wide_ichr(const ::wide_character * psz1, ::wd32_character ch) { return wd32_ichr(psz1, ch); }

inline int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icmp(psz1, psz2); }
inline int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2)
{
#ifdef WINDOWS
   return wcsicmp(psz1, psz2);
#else
   return __wd32icmp(psz1, psz2);
#endif
   
}
inline int wide_icmp(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icmp(psz1, psz2); }

inline int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return __wd16nicmp(psz1, psz2, s); }
inline int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s)
{
#ifdef WINDOWS
   return wcsnicmp(psz1, psz2, s);
#else
   return __wd32nicmp(psz1, psz2, s);
#endif
}
inline int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, strsize s) { return wd32_nicmp(psz1, psz2, s); }

inline const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind) { return __wd16istr(psz, pszFind); }
inline const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind) { return __wd32istr(psz, pszFind); }
inline const ::wd32_character * widew_istr(const ::wide_character * psz, const ::wide_character * pszFind) { return wd32_istr(psz, pszFind); }

inline ::wd16_character * u64towd16(::u64 u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { return __u64towd16(u, buf, iBase, edigitcase); }
inline ::wd32_character * u64towd32(::u64 u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }
inline ::wide_character * u64towide(::u64 u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }

inline ::wd16_character * i64towd16(::i64 u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase) { return __i64towd16(u, buf, iBase, edigitcase); }
inline ::wd32_character * i64towd32(::i64 u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(u, buf, iBase, edigitcase); }
inline ::wide_character * i64towide(::i64 u, ::wide_character * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(u, buf, iBase, edigitcase); }

inline int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cmp(psz1, psz2); }
inline int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscoll(psz1, psz2); }
inline int wide_coll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_coll(psz1, psz2); }

inline int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return __wd16ncoll(psz1, psz2, s); }
inline int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32ncoll(psz1, psz2, s); }
inline int wide_ncoll(const ::wide_character * psz1, const ::wide_character * psz2, strsize s) { return wd32_ncoll(psz1, psz2, s); }

inline int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16icoll(psz1, psz2); }
inline int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2) { return __wd32icoll(psz1, psz2); }
inline int wide_icoll(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_icoll(psz1, psz2); }

inline int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return __wd16nicoll(psz1, psz2, s); }
inline int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s) { return __wd32nicoll(psz1, psz2, s); }
inline int wide_nicoll(const ::wide_character * psz1, const ::wide_character * psz2, strsize s) { return wd32_nicoll(psz1, psz2, s); }

inline strsize wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16spn(psz1, psz2); }
inline strsize wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcsspn(psz1, psz2); }
inline strsize wide_spn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_spn(psz1, psz2); }

inline strsize wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2) { return __wd16cspn(psz1, psz2); }
inline strsize wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2) { return wcscspn(psz1, psz2); }
inline strsize wide_cspn(const ::wide_character * psz1, const ::wide_character * psz2) { return wd32_cspn(psz1, psz2); }


#else

#error "Not supported ::wide_character size_i32"

#endif






