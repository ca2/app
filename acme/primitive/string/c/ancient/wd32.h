#pragma once






inline ::wd32_character               __wd32charlowered(i32 i);
inline ::wd32_character               __wd32charuppered(i32 i);
inline i32                    __wd32charisdigit(i32 i);
inline i32                    __wd32charisalpha(i32 i);
inline i32                    __wd32charisalnum(i32 i);
inline i32                    __wd32charisspace(i32 i);



inline i32                    __wd32charishexadecimal(i32 i);


inline strsize __wd32len(const ::wd32_character * psz);

inline ::wd32_character * __wd32cat(::wd32_character * pszTarget, const ::wd32_character * pszConcat);

inline ::wd32_character * __wd32cpy(::wd32_character * pszDst, const ::wd32_character * pszSrc);

inline ::wd32_character * __wd32ncpy(::wd32_character * pszDst, const ::wd32_character * psz, strsize len);

inline const ::wd32_character * __wd32chr(const ::wd32_character * psz1, ::wd32_character ch);

inline ::wd32_character * __wd32pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind);

inline ::wd32_character * __wd32tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state);

inline const ::wd32_character * __wd32rchr(const ::wd32_character * psz1, ::wd32_character ch);

inline int __wd32cmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int __wd32ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);

inline const ::wd32_character * __wd32str(const ::wd32_character * psz, const ::wd32_character * pszFind);

inline ::wd32_character __wd32tolower(::wd32_character ch);

inline ::wd32_character __wd32toupper(::wd32_character ch);

inline ::wd32_character * __wd32lwr(::wd32_character * psz);

inline ::wd32_character * __wd32lwr_s(::wd32_character * psz, strsize s);

inline ::wd32_character * __wd32upr(::wd32_character * psz);

inline ::wd32_character * __wd32upr_s(::wd32_character * psz, strsize s);

inline const ::wd32_character * __wd32ichr(const ::wd32_character * psz1, ::wd32_character ch);

inline int __wd32icmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int __wd32nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);

inline const ::wd32_character * __wd32istr(const ::wd32_character * psz, const ::wd32_character * pszFind);

CLASS_DECL_ACME ::wd32_character * __u64towd32(::u64 u, ::wd32_character * buf, int iBase, char chTen);

CLASS_DECL_ACME ::wd32_character * __i64towd32(::i64 i, ::wd32_character * buf, int iBase, char chTen);

inline ::wd32_character * overlap_safe_wd32ncpy(::wd32_character * pszDst, const ::wd32_character * pszSrc, strsize srclen);

inline int __wd32coll(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int __wd32ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);

inline int __wd32icoll(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int __wd32nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);

inline strsize __wd32spn(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline strsize __wd32cspn(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME i64 __wd32toi64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __wd32tou64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __wd32toi32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __wd32tou32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, i32 iBase);






