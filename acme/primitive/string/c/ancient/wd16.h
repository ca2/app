#pragma once





inline wd16char               __wd16charlowered(i32 i);
inline wd16char               __wd16charuppered(i32 i);
inline i32                    __wd16charisdigit(i32 i);
inline i32                    __wd16charisalpha(i32 i);
inline i32                    __wd16charisalnum(i32 i);
inline i32                    __wd16charisspace(i32 i);


inline i32                    __wd16charishexadecimal(i32 i);


inline strsize __wd16len(const wd16char * psz);

inline wd16char * __wd16cat(wd16char * pszTarget, const wd16char * pszConcat);

inline wd16char * __wd16cpy(wd16char * pszDst, const wd16char * pszSrc);

inline wd16char * __wd16ncpy(wd16char * pszDst, const wd16char * psz, strsize len);

inline const wd16char * __wd16chr(const wd16char * psz1, wd16char ch);

inline wd16char * __wd16pbrk(wd16char * psz, const wd16char * pszCharsToFind);

inline wd16char * __wd16tok_r(wd16char * psz, const wd16char * sep, wd16char ** state);

inline const wd16char * __wd16rchr(const wd16char * psz1, wd16char ch);

inline int __wd16cmp(const wd16char * psz1, const wd16char * psz2);

inline int __wd16ncmp(const wd16char * psz1, const wd16char * psz2, strsize s);

inline const wd16char * __wd16str(const wd16char * psz, const wd16char * pszFind);

inline wd16char __wd16tolower(wd16char ch);

inline wd16char __wd16toupper(wd16char ch);

inline wd16char * __wd16lwr(wd16char * psz);

inline wd16char * __wd16lwr_s(wd16char * psz, strsize s);

inline wd16char * __wd16upr(wd16char * psz);

inline wd16char * __wd16upr_s(wd16char * psz, strsize s);

inline const wd16char * __wd16ichr(const wd16char * psz1, wd16char ch);

inline int __wd16icmp(const wd16char * psz1, const wd16char * psz2);

inline int __wd16nicmp(const wd16char * psz1, const wd16char * psz2, strsize s);

inline const wd16char * __wd16istr(const wd16char * psz, const wd16char * pszFind);

CLASS_DECL_ACME wd16char * __u64towd16(::u64 u, wd16char * buf, int iBase, wd16char chTen);

CLASS_DECL_ACME wd16char * __i64towd16(::i64 i, wd16char * buf, int iBase, wd16char chTen);

inline wd16char * overlap_safe_wd16ncpy(wd16char * pszDst, const wd16char * pszSrc, strsize srclen);

inline int __wd16coll(const wd16char * psz1, const wd16char * psz2);

inline int __wd16ncoll(const wd16char * psz1, const wd16char * psz2, strsize s);

inline int __wd16icoll(const wd16char * psz1, const wd16char * psz2);

inline int __wd16nicoll(const wd16char * psz1, const wd16char * psz2, strsize s);

inline strsize __wd16spn(const wd16char * psz1, const wd16char * psz2);

inline strsize __wd16cspn(const wd16char * psz1, const wd16char * psz2);

CLASS_DECL_ACME i64 __wd16toi64(const wd16char * psz, wd16char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __wd16tou64(const wd16char * psz, wd16char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __wd16toi32(const wd16char * psz, wd16char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __wd16tou32(const wd16char * psz, wd16char ** ppszEnd, i32 iBase);








