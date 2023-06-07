#pragma once





inline ::wd16_character               __wd16charlowered(i32 i);
inline ::wd16_character               __wd16charuppered(i32 i);
inline i32                    __wd16charisdigit(i32 i);
inline i32                    __wd16charisalpha(i32 i);
inline i32                    __wd16charisalnum(i32 i);
inline i32                    __wd16charisspace(i32 i);


inline i32                    __wd16charishexadecimal(i32 i);


inline strsize __wd16len(const ::wd16_character * psz);

inline ::wd16_character * __wd16cat(::wd16_character * pszTarget, const ::wd16_character * pszConcat);

inline ::wd16_character * __wd16cpy(::wd16_character * pszDst, const ::wd16_character * pszSrc);

inline ::wd16_character * __wd16ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len);

inline const ::wd16_character * __wd16chr(const ::wd16_character * psz1, ::wd16_character ch);

inline ::wd16_character * __wd16pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind);

inline ::wd16_character * __wd16tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state);

inline const ::wd16_character * __wd16rchr(const ::wd16_character * psz1, ::wd16_character ch);

inline int __wd16cmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

inline int __wd16ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

inline const ::wd16_character * __wd16str(const ::wd16_character * psz, const ::wd16_character * pszFind);

inline ::wd16_character __wd16tolower(::wd16_character ch);

inline ::wd16_character __wd16toupper(::wd16_character ch);

inline ::wd16_character * __wd16lwr(::wd16_character * psz);

inline ::wd16_character * __wd16lwr_s(::wd16_character * psz, strsize s);

inline ::wd16_character * __wd16upr(::wd16_character * psz);

inline ::wd16_character * __wd16upr_s(::wd16_character * psz, strsize s);

inline const ::wd16_character * __wd16ichr(const ::wd16_character * psz1, ::wd16_character ch);

inline int __wd16icmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

inline int __wd16nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

inline const ::wd16_character * __wd16istr(const ::wd16_character * psz, const ::wd16_character * pszFind);

CLASS_DECL_ACME ::wd16_character * __u64towd16(::u64 u, ::wd16_character * buf, int iBase, ::wd16_character chTen);

CLASS_DECL_ACME ::wd16_character * __i64towd16(::i64 i, ::wd16_character * buf, int iBase, ::wd16_character chTen);

inline ::wd16_character * overlap_safe_wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, strsize srclen);

inline int __wd16coll(const ::wd16_character * psz1, const ::wd16_character * psz2);

inline int __wd16ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

inline int __wd16icoll(const ::wd16_character * psz1, const ::wd16_character * psz2);

inline int __wd16nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

inline strsize __wd16spn(const ::wd16_character * psz1, const ::wd16_character * psz2);

inline strsize __wd16cspn(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME i64 __wd16toi64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __wd16tou64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __wd16toi32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __wd16tou32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);








