#pragma once


inline ansichar * ansi_dup(const ansichar * psz) { return _strdup(psz); }

inline strsize ansi_len(const ansichar * psz) { return strlen(psz); }

inline ansichar * ansi_cat(ansichar * pszDst, const ansichar * psz) { return strcat(pszDst, psz); }

inline ansichar * ansi_cpy(ansichar * pszDst, const ansichar * psz) { return strcpy(pszDst, psz); }

inline ansichar * ansi_ncpy(ansichar * pszDst, const ansichar * psz, strsize len) { return strncpy(pszDst, psz, len); }

inline const ansichar * ansi_chr(const ansichar * psz1, ansichar ch) { return strchr(psz1, ch); }

inline ansichar * ansi_pbrk(ansichar * psz, const ansichar * pszCharsToFind) { return strpbrk(psz, pszCharsToFind); }


inline ansichar * ansi_tok_r(ansichar * psz, const ansichar * sep, ansichar ** state)
{

#ifdef WINDOWS

    return strtok_s(psz, sep, state);

#else

    return strtok_r(psz, sep, state);

#endif

}

inline const ansichar * ansi_rchr(const ansichar * psz1, ansichar ch) { return strrchr(psz1, ch); }

inline int ansi_cmp(const ansichar * psz1, const ansichar * psz2) { return strcmp(psz1, psz2); }

inline int ansi_ncmp(const ansichar * psz1, const ansichar * psz2, strsize s) { return strncmp(psz1, psz2, s); }

inline const ansichar * ansi_str(const ansichar * psz, const ansichar * pszFind) { return strstr(psz, pszFind); }

inline ansichar ansi_tolower(ansichar ch) { return tolower(ch); }

inline ansichar ansi_toupper(ansichar ch) { return toupper(ch); }

#ifdef WINDOWS

inline ansichar * ansi_lwr(ansichar * psz) { return _strlwr(psz); }

inline ansichar * ansi_lwr_s(ansichar * psz, strsize s) { _strlwr_s(psz, s); return psz; }

inline ansichar * ansi_upr(ansichar * psz) { return _strupr(psz); }

inline ansichar * ansi_upr_s(ansichar * psz, strsize s) { _strupr_s(psz, s); return psz; }

#else

inline ansichar * ansi_lwr(ansichar * psz) { return __ansilwr(psz); }

inline ansichar * ansi_lwr_s(ansichar * psz, strsize s) { __ansilwr_s(psz, s); return psz; }

inline ansichar * ansi_upr(ansichar * psz) { return __ansiupr(psz); }

inline ansichar * ansi_upr_s(ansichar * psz, strsize s) { __ansiupr_s(psz, s); return psz; }

#endif

inline const ansichar * ansi_ichr(const ansichar * psz1, ansichar ch) { return __ansiichr(psz1, ch); }


inline int ansi_icmp(const ansichar * psz1, const ansichar * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

inline int ansi_nicmp(const ansichar * psz1, const ansichar * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}

inline const ansichar * ansi_istr(const ansichar * psz, const ansichar * pszFind) { return __ansiistr(psz, pszFind); }

inline ansichar * ui64tostr(::u64 u, ansichar * buf, int iBase, enum_digit_case edigitcase) { return __u64toansi(u, buf, iBase, edigitcase); }

inline ansichar * i64tostr(::u64 u, ansichar * buf, int iBase, enum_digit_case edigitcase) { return __i64toansi(u, buf, iBase, edigitcase); }

inline int ansi_coll(const ansichar * psz1, const ansichar * psz2) { return strcmp(psz1, psz2); }

inline int ansi_ncoll(const ansichar * psz1, const ansichar * psz2, strsize s) { return strncmp(psz1, psz2, s); }

inline int ansi_icoll(const ansichar * psz1, const ansichar * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

inline int ansi_nicoll(const ansichar * psz1, const ansichar * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}

inline strsize ansi_spn(const ansichar * psz1, const ansichar * psz2) { return strspn(psz1, psz2); }

inline strsize ansi_cspn(const ansichar * psz1, const ansichar * psz2) { return strcspn(psz1, psz2); }

















#if WCHAR_T_SIZE == 16


inline strsize wd16_len(const wd16char * psz) { return wcslen(psz); }
inline strsize wd32_len(const wd32char * psz) { return __wd32len(psz); }

inline wd16char * wd16_cat(wd16char * pszDst, const wd16char * psz) { return wcscat(pszDst, psz); }
inline wd32char * wd32_cat(wd32char * pszDst, const wd32char * psz) { return __wd32cat(pszDst, psz); }

inline wd16char * wd16_cpy(wd16char * pszDst, const wd16char * psz) { return wcscpy(pszDst, psz); }
inline wd32char * wd32_cpy(wd32char * pszDst, const wd32char * psz) { return __wd32cpy(pszDst, psz); }

inline wd16char * wd16_ncpy(wd16char * pszDst, const wd16char * psz, strsize len) { return wcsncpy(pszDst, psz, len); }
inline wd32char * wd32_ncpy(wd32char * pszDst, const wd32char * psz, strsize len) { return __wd32ncpy(pszDst, psz, len); }

inline const wd16char * wd16_chr(const wd16char * psz1, wd16char ch) { return wcschr(psz1, ch); }
inline const wd32char * wd32_chr(const wd32char * psz1, wd32char ch) { return __wd32chr(psz1, ch); }

inline wd16char * wd16_pbrk(wd16char * psz, const wd16char * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
inline wd32char * wd32_pbrk(wd32char * psz, const wd32char * pszCharsToFind) { return __wd32pbrk(psz, pszCharsToFind); }

inline wd16char * wd16_tok_r(wd16char * psz, const wd16char * sep, wd16char ** state) { return __wd16tok_r(psz, sep, state); }
inline wd32char * wd32_tok_r(wd32char * psz, const wd32char * sep, wd32char ** state) { return __wd32tok_r(psz, sep, state); }

inline const wd16char * wd16_rchr(const wd16char * psz1, wd16char ch) { return wcsrchr(psz1, ch); }
inline const wd32char * wd32_rchr(const wd32char * psz1, wd32char ch) { return __wd32rchr(psz1, ch); }

inline int wd16_cmp(const wd16char * psz1, const wd16char * psz2) { return wcscmp(psz1, psz2); }
inline int wd32_cmp(const wd32char * psz1, const wd32char * psz2) { return __wd32cmp(psz1, psz2); }

inline int wd16_ncmp(const wd16char * psz1, const wd16char * psz2, strsize s) { return wcsncmp(psz1, psz2, s); }
inline int wd32_ncmp(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32ncmp(psz1, psz2, s); }

inline const wd16char * wd16_str(const wd16char * psz, const wd16char * pszFind) { return wcsstr(psz, pszFind); }
inline const wd32char * wd32_str(const wd32char * psz, const wd32char * pszFind) { return __wd32str(psz, pszFind); }

inline wd16char wd16_tolower(wd16char ch) { return towlower(ch); }
inline wd32char wd32_tolower(wd32char ch) { return __wd32tolower(ch); }

inline wd32char wd16_toupper(wd16char ch) { return towupper(ch); }
inline wd32char wd32_toupper(wd32char ch) { return __wd32toupper(ch); }

inline wd16char * wd16_lwr(wd16char * psz) { return _wcslwr(psz); }
inline wd32char * wd32_lwr(wd32char * psz) { return __wd32lwr(psz); }

inline wd16char * wd16_lwr_s(wd16char * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline wd32char * wd32_lwr_s(wd32char * psz, strsize s) { __wd32lwr_s(psz, s);  return psz; }

inline wd16char * wd16_upr(wd16char * psz) { return _wcsupr(psz); }
inline wd32char * wd32_upr(wd32char * psz) { return __wd32upr(psz); }

inline wd16char * wd16_upr_s(wd16char * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }
inline wd32char * wd32_upr_s(wd32char * psz, strsize s) { __wd32upr_s(psz, s);  return psz; }

inline const wd16char * wd16_ichr(const wd16char * psz1, wd16char ch) { return __wd16ichr(psz1, ch); }
inline const wd32char * wd32_ichr(const wd32char * psz1, wd32char ch) { return __wd32ichr(psz1, ch); }

inline int wd16_icmp(const wd16char * psz1, const wd16char * psz2) { return _wcsicmp(psz1, psz2); }
inline int wd32_icmp(const wd32char * psz1, const wd32char * psz2) { return __wd32icmp(psz1, psz2); }

inline int wd16_nicmp(const wd16char * psz1, const wd16char * psz2, strsize s) { return _wcsnicmp(psz1, psz2, s); }
inline int wd32_nicmp(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32nicmp(psz1, psz2, s); }
inline int wide_nicmp(const widechar * psz1, const widechar * psz2, strsize s) { return wd16_nicmp(psz1, psz2, s); }

inline const wd16char * wd16_istr(const wd16char * psz, const wd16char * pszFind) { return __wd16istr(psz, pszFind); }
inline const wd32char * wd32_istr(const wd32char * psz, const wd32char * pszFind) { return __wd32istr(psz, pszFind); }

inline wd16char * u64towd16(::u64 u, wd16char * buf, int iBase, enum_digit_case edigitcase) { return __u64towd16(u, buf, iBase, edigitcase); }
inline wd32char * u64towd32(::u64 u, wd32char * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }

inline wd16char * i64towd16(::i64 i, wd16char * buf, int iBase, enum_digit_case edigitcase) { return __i64towd16(i, buf, iBase, edigitcase); }
inline wd32char * i64towd32(::i64 i, wd32char * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(i, buf, iBase, edigitcase); }

inline int wd16_coll(const wd16char * psz1, const wd16char * psz2) { return wcscoll(psz1, psz2); }
inline int wd32_coll(const wd32char * psz1, const wd32char * psz2) { return __wd32cmp(psz1, psz2); }

inline int wd16_ncoll(const wd16char * psz1, const wd16char * psz2, strsize s) { return _wcsncoll(psz1, psz2, s); }
inline int wd32_ncoll(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32ncoll(psz1, psz2, s); }

inline int wd16_icoll(const wd16char * psz1, const wd16char * psz2) { return _wcsicoll(psz1, psz2); }
inline int wd32_icoll(const wd32char * psz1, const wd32char * psz2) { return __wd32icoll(psz1, psz2); }

inline int wd16_nicoll(const wd16char * psz1, const wd16char * psz2, strsize s) { return _wcsnicoll(psz1, psz2, s); }
inline int wd32_nicoll(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32nicoll(psz1, psz2, s); }

inline strsize wd16_spn(const wd16char * psz1, const wd16char * psz2) { return wcsspn(psz1, psz2); }
inline strsize wd32_spn(const wd32char * psz1, const wd32char * psz2) { return __wd32spn(psz1, psz2); }

inline strsize wd16_cspn(const wd16char * psz1, const wd16char * psz2) { return wcscspn(psz1, psz2); }
inline strsize wd32_cspn(const wd32char * psz1, const wd32char * psz2) { return __wd32cspn(psz1, psz2); }

#elif WCHAR_T_SIZE == 32

inline strsize wd16_len(const wd16char * psz) { return __wd16len(psz); }
inline strsize wd32_len(const wd32char * psz) { return wcslen(psz); }
inline strsize wide_len(const widechar * psz) { return wd32_len(psz); }

inline wd16char * wd16_cat(wd16char * pszDst, const wd16char * psz) { return __wd16cat(pszDst, psz); }
inline wd32char * wd32_cat(wd32char * pszDst, const wd32char * psz) { return wcscat(pszDst, psz); }
inline widechar * wide_cat(widechar * pszDst, const widechar * psz) { return wd32_cat(pszDst, psz); }

inline wd16char * wd16_cpy(wd16char * pszDst, const wd16char * psz) { return __wd16cpy(pszDst, psz); }
inline wd32char * wd32_cpy(wd32char * pszDst, const wd32char * psz) { return wcscpy(pszDst, psz); }
inline widechar * wide_cpy(widechar * pszDst, const widechar * psz) { return wd32_cpy(pszDst, psz); }

inline wd16char * wd16_ncpy(wd16char * pszDst, const wd16char * psz, strsize len) { return __wd16ncpy(pszDst, psz, len); }
inline wd32char * wd32_ncpy(wd32char * pszDst, const wd32char * psz, strsize len) { return wcsncpy(pszDst, psz, len); }
inline widechar * wide_ncpy(widechar * pszDst, const widechar * psz, strsize len) { return wd32_ncpy(pszDst, psz, len); }

//inline const wd16char * wd16_str(const wd16char * psz, const wd16char * pszFind) { return __wd16str(psz, pszFind); }
//inline const wd32char * wd32_str(const wd32char * psz, const wd32char * pszFind) { return wcsstr(psz, pszFind); }

inline const wd16char * wd16_chr(const wd16char * psz1, wd16char ch) { return __wd16chr(psz1, ch); }
inline const wd32char * wd32_chr(const wd32char * psz1, wd32char ch) { return wcschr(psz1, ch); }
inline const widechar * wide_chr(const widechar * psz1, widechar ch) { return wd32_chr(psz1, ch); }

inline wd16char * wd16_pbrk(wd16char * psz, const wd16char * pszCharsToFind) { return __wd16pbrk(psz, pszCharsToFind); }
inline wd32char * wd32_pbrk(wd32char * psz, const wd32char * pszCharsToFind) { return wcspbrk(psz, pszCharsToFind); }
inline widechar * wide_pbrk(widechar * psz, const widechar * pszCharsToFind) { return wd32_pbrk(psz, pszCharsToFind); }

inline wd16char * wd16_tok_r(wd16char * psz, const wd16char * sep, wd16char ** state) { return __wd16tok_r(psz, sep, state); }
inline wd32char * wd32_tok_r(wd32char * psz, const wd32char * sep, wd32char ** state) { return __wd32tok_r(psz, sep, state); }
inline widechar * wide_tok_r(widechar * psz, const widechar * sep, widechar ** state) { return wd32_tok_r(psz, sep, state); }

inline const wd16char * wd16_rchr(const wd16char * psz1, wd16char ch) { return __wd16rchr(psz1, ch); }
inline const wd32char * wd32_rchr(const wd32char * psz1, wd32char ch) { return wcsrchr(psz1, ch); }
inline const widechar * wide_rchr(const widechar * psz1, widechar ch) { return wd32_rchr(psz1, ch); }

inline int wd16_cmp(const wd16char * psz1, const wd16char * psz2) { return __wd16cmp(psz1, psz2); }
inline int wd32_cmp(const wd32char * psz1, const wd32char * psz2) { return wcscmp(psz1, psz2); }
inline int wide_cmp(const widechar * psz1, const widechar * psz2) { return wd32_cmp(psz1, psz2); }

inline int wd16_ncmp(const wd16char * psz1, const wd16char * psz2, strsize s) { return __wd16ncmp(psz1, psz2, s); }
inline int wd32_ncmp(const wd32char * psz1, const wd32char * psz2, strsize s)
{
#ifdef WINDOWS
   return wcsncmp(psz1, psz2, s);
#else
   return __wd32ncmp(psz1, psz2, s);
#endif
   
}
inline int wide_ncmp(const widechar * psz1, const widechar * psz2, strsize s) { return wd32_ncmp(psz1, psz2, s); }

inline const wd16char * wd16_str(const wd16char * psz, const wd16char * pszFind) { return __wd16str(psz, pszFind); }
inline const wd32char * wd32_str(const wd32char * psz, const wd32char * pszFind) { return wcsstr(psz, pszFind); }
inline const widechar * wide_str(const widechar * psz, const widechar * pszFind) { return wd32_str(psz, pszFind); }

inline wd16char wd16_tolower(wd16char ch) { return __wd16tolower(ch); }
inline wd32char wd32_tolower(wd32char ch) { return towlower(ch); }
inline widechar wide_tolower(widechar ch) { return wd32_tolower(ch); }

inline wd32char wd16_toupper(wd16char ch) { return __wd16toupper(ch); }
inline wd32char wd32_toupper(wd32char ch) { return towupper(ch); }
inline widechar wide_toupper(widechar ch) { return wd32_toupper(ch); }


inline wd16char * wd16_lwr(wd16char * psz) { return __wd16lwr(psz); }
inline wd16char * wd16_lwr_s(wd16char * psz, strsize s) { __wd16lwr_s(psz, s);  return psz; }
inline wd16char * wd16_upr(wd16char * psz) { return __wd16upr(psz); }
inline wd16char * wd16_upr_s(wd16char * psz, strsize s) { __wd16upr_s(psz, s);  return psz; }


#ifdef WINDOWS

inline wd32char * wd32_lwr(wd32char * psz) { return wcslwr(psz); }
inline wd32char * wd32_lwr_s(wd32char * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline wd32char * wd32_upr(wd32char * psz) { return wcsupr(psz); }
inline wd32char * wd32_upr_s(wd32char * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }

inline widechar * wide_lwr(wd32char * psz) { return wcslwr(psz); }
inline widechar * wide_lwr_s(wd32char * psz, strsize s) { _wcslwr_s(psz, s);  return psz; }
inline widechar * wide_upr(wd32char * psz) { return wcsupr(psz); }
inline widechar * wide_upr_s(wd32char * psz, strsize s) { _wcsupr_s(psz, s);  return psz; }

#else

inline wd32char * wd32_lwr(wd32char * psz) { return __wd32lwr(psz); }
inline wd32char * wd32_lwr_s(wd32char * psz, strsize s) { __wd32lwr_s(psz, s);  return psz; }
inline wd32char * wd32_upr(wd32char * psz) { return __wd32upr(psz); }
inline wd32char * wd32_upr_s(wd32char * psz, strsize s) { __wd32upr_s(psz, s);  return psz; }

inline widechar * wide_lwr(widechar * psz) { return wd32_lwr(psz); }
inline widechar * wide_lwr_s(widechar * psz, strsize s) { wd32_lwr_s(psz, s);  return psz; }
inline widechar * wide_upr(widechar * psz) { return wd32_upr(psz); }
inline widechar * wide_upr_s(widechar * psz, strsize s) { wd32_upr_s(psz, s);  return psz; }

#endif

inline const wd16char * wd16_ichr(const wd16char * psz1, wd16char ch) { return __wd16ichr(psz1, ch); }
inline const wd32char * wd32_ichr(const wd32char * psz1, wd32char ch) { return __wd32ichr(psz1, ch); }
inline const widechar * wide_ichr(const widechar * psz1, wd32char ch) { return wd32_ichr(psz1, ch); }

inline int wd16_icmp(const wd16char * psz1, const wd16char * psz2) { return __wd16icmp(psz1, psz2); }
inline int wd32_icmp(const wd32char * psz1, const wd32char * psz2)
{
#ifdef WINDOWS
   return wcsicmp(psz1, psz2);
#else
   return __wd32icmp(psz1, psz2);
#endif
   
}
inline int wide_icmp(const widechar * psz1, const widechar * psz2) { return wd32_icmp(psz1, psz2); }

inline int wd16_nicmp(const wd16char * psz1, const wd16char * psz2, strsize s) { return __wd16nicmp(psz1, psz2, s); }
inline int wd32_nicmp(const wd32char * psz1, const wd32char * psz2, strsize s)
{
#ifdef WINDOWS
   return wcsnicmp(psz1, psz2, s);
#else
   return __wd32nicmp(psz1, psz2, s);
#endif
}
inline int wide_nicmp(const widechar * psz1, const widechar * psz2, strsize s) { return wd32_nicmp(psz1, psz2, s); }

inline const wd16char * wd16_istr(const wd16char * psz, const wd16char * pszFind) { return __wd16istr(psz, pszFind); }
inline const wd32char * wd32_istr(const wd32char * psz, const wd32char * pszFind) { return __wd32istr(psz, pszFind); }
inline const wd32char * widew_istr(const widechar * psz, const widechar * pszFind) { return wd32_istr(psz, pszFind); }

inline wd16char * u64towd16(::u64 u, wd16char * buf, int iBase, enum_digit_case edigitcase) { return __u64towd16(u, buf, iBase, edigitcase); }
inline wd32char * u64towd32(::u64 u, wd32char * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }
inline widechar * u64towide(::u64 u, widechar * buf, int iBase, enum_digit_case edigitcase) { return __u64towd32(u, buf, iBase, edigitcase); }

inline wd16char * i64towd16(::i64 u, wd16char * buf, int iBase, enum_digit_case edigitcase) { return __i64towd16(u, buf, iBase, edigitcase); }
inline wd32char * i64towd32(::i64 u, wd32char * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(u, buf, iBase, edigitcase); }
inline widechar * i64towide(::i64 u, widechar * buf, int iBase, enum_digit_case edigitcase) { return __i64towd32(u, buf, iBase, edigitcase); }

inline int wd16_coll(const wd16char * psz1, const wd16char * psz2) { return __wd16cmp(psz1, psz2); }
inline int wd32_coll(const wd32char * psz1, const wd32char * psz2) { return wcscoll(psz1, psz2); }
inline int wide_coll(const widechar * psz1, const widechar * psz2) { return wd32_coll(psz1, psz2); }

inline int wd16_ncoll(const wd16char * psz1, const wd16char * psz2, strsize s) { return __wd16ncoll(psz1, psz2, s); }
inline int wd32_ncoll(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32ncoll(psz1, psz2, s); }
inline int wide_ncoll(const widechar * psz1, const widechar * psz2, strsize s) { return wd32_ncoll(psz1, psz2, s); }

inline int wd16_icoll(const wd16char * psz1, const wd16char * psz2) { return __wd16icoll(psz1, psz2); }
inline int wd32_icoll(const wd32char * psz1, const wd32char * psz2) { return __wd32icoll(psz1, psz2); }
inline int wide_icoll(const widechar * psz1, const widechar * psz2) { return wd32_icoll(psz1, psz2); }

inline int wd16_nicoll(const wd16char * psz1, const wd16char * psz2, strsize s) { return __wd16nicoll(psz1, psz2, s); }
inline int wd32_nicoll(const wd32char * psz1, const wd32char * psz2, strsize s) { return __wd32nicoll(psz1, psz2, s); }
inline int wide_nicoll(const widechar * psz1, const widechar * psz2, strsize s) { return wd32_nicoll(psz1, psz2, s); }

inline strsize wd16_spn(const wd16char * psz1, const wd16char * psz2) { return __wd16spn(psz1, psz2); }
inline strsize wd32_spn(const wd32char * psz1, const wd32char * psz2) { return wcsspn(psz1, psz2); }
inline strsize wide_spn(const widechar * psz1, const widechar * psz2) { return wd32_spn(psz1, psz2); }

inline strsize wd16_cspn(const wd16char * psz1, const wd16char * psz2) { return __wd16cspn(psz1, psz2); }
inline strsize wd32_cspn(const wd32char * psz1, const wd32char * psz2) { return wcscspn(psz1, psz2); }
inline strsize wide_cspn(const widechar * psz1, const widechar * psz2) { return wd32_cspn(psz1, psz2); }


#else

#error "Not supported widechar size_i32"

#endif






