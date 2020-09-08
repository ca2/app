#pragma once





inline strsize __widelen(const widechar * psz);

inline widechar * __widecat(widechar * pszTarget, const widechar * pszConcat);

inline widechar * __widecpy(widechar * pszDst, const widechar * pszSrc);

inline widechar * __widencpy(widechar * pszDst, const widechar * psz, strsize len);

inline const widechar * __widechr(const widechar * psz1, widechar ch);

inline widechar * __widepbrk(widechar * psz, const widechar * pszCharsToFind);

inline widechar * __widetok_r(widechar * psz, const widechar * sep, widechar ** state);

inline const widechar * __widerchr(const widechar * psz1, widechar ch);

inline int __widecmp(const widechar * psz1, const widechar * psz2);

inline int __widencmp(const widechar * psz1, const widechar * psz2, size_t s);

inline const widechar * __widestr(const widechar * psz, const widechar * pszFind);

inline widechar __widetolower(widechar ch);

inline widechar __widetoupper(widechar ch);

inline widechar * __widelwr(widechar * psz);

inline widechar * __widelwr_s(widechar * psz, strsize s);

inline widechar * __wideupr(widechar * psz);

inline widechar * __wideupr_s(widechar * psz, strsize s);

inline const widechar * __wideichr(const widechar * psz1, widechar ch);

inline int __wideicmp(const widechar * psz1, const widechar * psz2);

inline int __widenicmp(const widechar * psz1, const widechar * psz2, size_t s);

inline const widechar * __wideistr(const widechar * psz, const widechar * pszFind);

CLASS_DECL_APEX widechar * __u64towide(::u64 u, widechar * buf, int iBase);

CLASS_DECL_APEX widechar * __i64towide(::i64 i, widechar * buf, int iBase);

inline widechar * overlap_safe_widencpy(widechar * pszDst, const widechar * pszSrc, strsize srclen);

inline int __widecoll(const widechar * psz1, const widechar * psz2);

inline int __widencoll(const widechar * psz1, const widechar * psz2, size_t s);

inline int __wideicoll(const widechar * psz1, const widechar * psz2);

inline int __widenicoll(const widechar * psz1, const widechar * psz2, size_t s);

inline strsize __widespn(const widechar * psz1, const widechar * psz2);

inline strsize __widecspn(const widechar * psz1, const widechar * psz2);





