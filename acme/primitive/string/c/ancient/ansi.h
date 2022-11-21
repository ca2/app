#pragma once




inline ansichar               __ansicharlowered(i32 i);
inline ansichar               __ansicharuppered(i32 i);
inline i32                    __ansicharisdigit(i32 i);
inline i32                    __ansicharisalpha(i32 i);
inline i32                    __ansicharisalnum(i32 i);
inline i32                    __ansicharisspace(i32 i);


inline i32                    __ansicharishexadecimal(i32 i);



inline strsize __ansilen(const ansichar * psz);

inline ansichar * __ansicat(ansichar * pszTarget, const ansichar * pszConcat);

inline ansichar * __ansicpy(ansichar * pszDst, const ansichar * pszSrc);

inline ansichar * __ansincpy(ansichar * pszDst, const ansichar * psz, strsize len);

inline const ansichar * __ansichr(const ansichar * psz1, ansichar ch);

inline ansichar * __ansipbrk(ansichar * psz, const ansichar * pszCharsToFind);

inline ansichar * __ansitok_r(ansichar * psz, const ansichar * sep, ansichar ** state);

inline const ansichar * __ansirchr(const ansichar * psz1, ansichar ch);

inline int __ansicmp(const ansichar * psz1, const ansichar * psz2);

inline int __ansincmp(const ansichar * psz1, const ansichar * psz2, strsize s);

inline const ansichar * __ansistr(const ansichar * psz, const ansichar * pszFind);

inline ansichar __ansitolower(ansichar ch);

inline ansichar __ansitoupper(ansichar ch);

inline ansichar __ansiisdigit(ansichar ch);

inline ansichar * __ansilwr(ansichar * psz);

inline ansichar * __ansilwr_s(ansichar * psz, strsize s);

inline ansichar * __ansiupr(ansichar * psz);

inline ansichar * __ansiupr_s(ansichar * psz, strsize s);

inline const ansichar * __ansiichr(const ansichar * psz1, ansichar ch);

inline int __ansiicmp(const ansichar * psz1, const ansichar * psz2);

inline int __ansiincmp(const ansichar * psz1, const ansichar * psz2, strsize s);

inline const ansichar * __ansiistr(const ansichar * psz, const ansichar * pszFind);


inline ansichar * overlap_safe_ansincpy(ansichar * pszDst, const ansichar * pszSrc, strsize srclen);

inline int __ansicoll(const ansichar * psz1, const ansichar * psz2);

inline int __ansincoll(const ansichar * psz1, const ansichar * psz2, strsize s);

inline int __ansiicoll(const ansichar * psz1, const ansichar * psz2);

inline int __ansinicoll(const ansichar * psz1, const ansichar * psz2, strsize s);

inline strsize __ansispn(const ansichar * psz1, const ansichar * psz2);

inline strsize __ansicspn(const ansichar * psz1, const ansichar * psz2);


CLASS_DECL_ACME i64 __ansitoi64(const ansichar * psz, ansichar ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __ansitou64(const ansichar * psz, ansichar ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __ansitoi32(const ansichar * psz, ansichar ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __ansitou32(const ansichar * psz, ansichar ** ppszEnd, i32 iBase);


inline ansichar lower_char(i32 ch);
inline ansichar upper_char(i32 ch);
inline void make_lower(ansichar * psz);



