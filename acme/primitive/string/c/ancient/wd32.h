#pragma once






inline wd32char               __wd32charlowered(i32 i);
inline wd32char               __wd32charuppered(i32 i);
inline i32                    __wd32charisdigit(i32 i);
inline i32                    __wd32charisalpha(i32 i);
inline i32                    __wd32charisalnum(i32 i);
inline i32                    __wd32charisspace(i32 i);



inline i32                    __wd32charishexadecimal(i32 i);


inline strsize __wd32len(const wd32char * psz);

inline wd32char * __wd32cat(wd32char * pszTarget, const wd32char * pszConcat);

inline wd32char * __wd32cpy(wd32char * pszDst, const wd32char * pszSrc);

inline wd32char * __wd32ncpy(wd32char * pszDst, const wd32char * psz, strsize len);

inline const wd32char * __wd32chr(const wd32char * psz1, wd32char ch);

inline wd32char * __wd32pbrk(wd32char * psz, const wd32char * pszCharsToFind);

inline wd32char * __wd32tok_r(wd32char * psz, const wd32char * sep, wd32char ** state);

inline const wd32char * __wd32rchr(const wd32char * psz1, wd32char ch);

inline int __wd32cmp(const wd32char * psz1, const wd32char * psz2);

inline int __wd32ncmp(const wd32char * psz1, const wd32char * psz2, strsize s);

inline const wd32char * __wd32str(const wd32char * psz, const wd32char * pszFind);

inline wd32char __wd32tolower(wd32char ch);

inline wd32char __wd32toupper(wd32char ch);

inline wd32char * __wd32lwr(wd32char * psz);

inline wd32char * __wd32lwr_s(wd32char * psz, strsize s);

inline wd32char * __wd32upr(wd32char * psz);

inline wd32char * __wd32upr_s(wd32char * psz, strsize s);

inline const wd32char * __wd32ichr(const wd32char * psz1, wd32char ch);

inline int __wd32icmp(const wd32char * psz1, const wd32char * psz2);

inline int __wd32nicmp(const wd32char * psz1, const wd32char * psz2, strsize s);

inline const wd32char * __wd32istr(const wd32char * psz, const wd32char * pszFind);

CLASS_DECL_ACME wd32char * __u64towd32(::u64 u, wd32char * buf, int iBase, char chTen);

CLASS_DECL_ACME wd32char * __i64towd32(::i64 i, wd32char * buf, int iBase, char chTen);

inline wd32char * overlap_safe_wd32ncpy(wd32char * pszDst, const wd32char * pszSrc, strsize srclen);

inline int __wd32coll(const wd32char * psz1, const wd32char * psz2);

inline int __wd32ncoll(const wd32char * psz1, const wd32char * psz2, strsize s);

inline int __wd32icoll(const wd32char * psz1, const wd32char * psz2);

inline int __wd32nicoll(const wd32char * psz1, const wd32char * psz2, strsize s);

inline strsize __wd32spn(const wd32char * psz1, const wd32char * psz2);

inline strsize __wd32cspn(const wd32char * psz1, const wd32char * psz2);

CLASS_DECL_ACME i64 __wd32toi64(const wd32char * psz, wd32char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __wd32tou64(const wd32char * psz, wd32char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __wd32toi32(const wd32char * psz, wd32char ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __wd32tou32(const wd32char * psz, wd32char ** ppszEnd, i32 iBase);






