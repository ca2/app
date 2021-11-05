#pragma once





inline ansichar * ansi_dup(const ansichar * psz);
inline strsize ansi_len(const ansichar * psz);
inline ansichar * ansi_cat(ansichar * pszDst, const ansichar * psz);
inline ansichar * ansi_cpy(ansichar * pszDst, const ansichar * psz);
inline ansichar * ansi_ncpy(ansichar * pszDst, const ansichar * psz, strsize len);
inline const ansichar * ansi_chr(const ansichar * psz1, ansichar ch);
inline ansichar * ansi_pbrk(ansichar * psz, const ansichar * pszCharsToFind);
inline ansichar * ansi_tok_r(ansichar * psz, const ansichar * sep, ansichar ** state);
inline const ansichar * ansi_rchr(const ansichar * psz1, ansichar ch);
inline int ansi_cmp(const ansichar * psz1, const ansichar * psz2);
inline int ansi_ncmp(const ansichar * psz1, const ansichar * psz2, strsize s);
inline const ansichar * ansi_str(const ansichar * psz, const ansichar * pszFind);
inline ansichar ansi_tolower(ansichar ch);
inline ansichar ansi_toupper(ansichar ch);
inline ansichar * ansi_lwr(ansichar * psz);
inline ansichar * ansi_lwr_s(ansichar * psz, strsize s);
inline ansichar * ansi_upr(ansichar * psz);
inline ansichar * ansi_upr_s(ansichar * psz, strsize s);
inline const ansichar * ansi_ichr(const ansichar * psz1, ansichar ch);
inline int ansi_icmp(const ansichar * psz1, const ansichar * psz2);
inline int ansi_nicmp(const ansichar * psz1, const ansichar * psz2, strsize s);
inline const ansichar * ansi_istr(const ansichar * psz, const ansichar * pszFind);
//inline ansichar * u64toansi(::u64 u, ansichar * buf, int iBase);
//inline ansichar * i64toansi(::u64 u, ansichar * buf, int iBase);
inline int ansi_coll(const ansichar * psz1, const ansichar * psz2);
inline int ansi_ncoll(const ansichar * psz1, const ansichar * psz2, strsize s);
inline int ansi_icoll(const ansichar * psz1, const ansichar * psz2);
inline int ansi_nicoll(const ansichar * psz1, const ansichar * psz2, strsize s);
inline strsize ansi_spn(const ansichar * psz1, const ansichar * psz2);
inline strsize ansi_cspn(const ansichar * psz1, const ansichar * psz2);


inline strsize wd16_len(const wd16char * psz);
inline strsize wd32_len(const wd32char * psz);

inline wd16char * wd16_cat(wd16char * pszDst, const wd16char * psz);
inline wd32char * wd32_cat(wd32char * pszDst, const wd32char * psz);

inline wd16char * wd16_cpy(wd16char * pszDst, const wd16char * psz);
inline wd32char * wd32_cpy(wd32char * pszDst, const wd32char * psz);

inline wd16char * wd16_ncpy(wd16char * pszDst, const wd16char * psz, strsize len);
inline wd32char * wd32_ncpy(wd32char * pszDst, const wd32char * psz, strsize len);

inline const wd16char * wd16_chr(const wd16char * psz1, wd16char ch);
inline const wd32char * wd32_chr(const wd32char * psz1, wd32char ch);

inline wd16char * wd16_pbrk(wd16char * psz, const wd16char * pszCharsToFind);
inline wd32char * wd32_pbrk(wd32char * psz, const wd32char * pszCharsToFind);

inline wd16char * wd16_tok_r(wd16char * psz, const wd16char * sep, wd16char ** state);
inline wd32char * wd32_tok_r(wd32char * psz, const wd32char * sep, wd32char ** state);
inline widechar * wide_tok_r(widechar * psz, const widechar * sep, widechar ** state);

inline const wd16char * wd16_rchr(const wd16char * psz1, wd16char ch);
inline const wd32char * wd32_rchr(const wd32char * psz1, wd32char ch);

inline int wd16_cmp(const wd16char * psz1, const wd16char * psz2);
inline int wd32_cmp(const wd32char * psz1, const wd32char * psz2);

inline int wd16_ncmp(const wd16char * psz1, const wd16char * psz2, strsize s);
inline int wd32_ncmp(const wd32char * psz1, const wd32char * psz2, strsize s);

inline const wd16char * wd16_str(const wd16char * psz, const wd16char * pszFind);
inline const wd32char * wd32_str(const wd32char * psz, const wd32char * pszFind);

inline wd16char wd16_tolower(wd16char ch);
inline wd32char wd32_tolower(wd32char ch);

inline wd32char wd16_toupper(wd16char ch);
inline wd32char wd32_toupper(wd32char ch);


inline wd16char * wd16_lwr(wd16char * psz);
inline wd32char * wd32_lwr(wd32char * psz);


inline wd16char * wd16_lwr_s(wd16char * psz, strsize s);
inline wd32char * wd32_lwr_s(wd32char * psz, strsize s);


inline wd16char * wd16_upr(wd16char * psz);
inline wd32char * wd32_upr(wd32char * psz);


inline wd16char * wd16_upr_s(wd16char * psz, strsize s);
inline wd32char * wd32_upr_s(wd32char * psz, strsize s);


inline const wd16char * wd16_ichr(const wd16char * psz1, wd16char ch);
inline const wd32char * wd32_ichr(const wd32char * psz1, wd32char ch);

inline int wd16_icmp(const wd16char * psz1, const wd16char * psz2);
inline int wd32_icmp(const wd32char * psz1, const wd32char * psz2);

inline int wd16_nicmp(const wd16char * psz1, const wd16char * psz2, strsize s);
inline int wd32_nicmp(const wd32char * psz1, const wd32char * psz2, strsize s);
inline int wide_nicmp(const widechar * psz1, const widechar * psz2, strsize s);

inline const wd16char * wd16_istr(const wd16char * psz, const wd16char * pszFind);
inline const wd32char * wd32_istr(const wd32char * psz, const wd32char * pszFind);

//inline wd16char * u64towd16(::u64 u, wd16char * buf, int iBase);
//inline wd32char * u64towd32(::u64 u, wd32char * buf, int iBase);
//inline widechar * u64towide(::u64 u, widechar * buf, int iBase);

//inline wd16char * i64towd16(::i64 i, wd16char * buf, int iBase);
//inline wd32char * i64towd32(::i64 i, wd32char * buf, int iBase);
//inline wd32char * i64towide(::i64 i, widechar * buf, int iBase);

inline int wd16_coll(const wd16char * psz1, const wd16char * psz2);
inline int wd32_coll(const wd32char * psz1, const wd32char * psz2);
inline int wide_coll(const widechar * psz1, const widechar * psz2);

inline int wd16_ncoll(const wd16char * psz1, const wd16char * psz2, strsize s);
inline int wd32_ncoll(const wd32char * psz1, const wd32char * psz2, strsize s);
inline int wide_ncoll(const widechar * psz1, const widechar * psz2, strsize s);

inline int wd16_icoll(const wd16char * psz1, const wd16char * psz2);
inline int wd32_icoll(const wd32char * psz1, const wd32char * psz2);
inline int wide_icoll(const widechar * psz1, const widechar * psz2);

inline int wd16_nicoll(const wd16char * psz1, const wd16char * psz2, strsize s);
inline int wd32_nicoll(const wd32char * psz1, const wd32char * psz2, strsize s);
inline int wide_nicoll(const widechar * psz1, const widechar * psz2, strsize s);

inline strsize wd16_spn(const wd16char * psz1, const wd16char * psz2);
inline strsize wd32_spn(const wd32char * psz1, const wd32char * psz2);

inline strsize wd16_cspn(const wd16char * psz1, const wd16char * psz2);
inline strsize wd32_cspn(const wd32char * psz1, const wd32char * psz2);





