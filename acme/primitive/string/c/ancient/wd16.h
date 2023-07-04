#pragma once





CLASS_DECL_ACME ::wd16_character               __wd16charlowered(i32 i);
CLASS_DECL_ACME ::wd16_character               __wd16charuppered(i32 i);
CLASS_DECL_ACME i32                    __wd16charisdigit(i32 i);
CLASS_DECL_ACME i32                    __wd16charisalpha(i32 i);
CLASS_DECL_ACME i32                    __wd16charisalnum(i32 i);
CLASS_DECL_ACME i32                    __wd16charisspace(i32 i);


CLASS_DECL_ACME i32                    __wd16charishexadecimal(i32 i);


CLASS_DECL_ACME strsize __wd16len(const ::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16cat(::wd16_character * pszTarget, const ::wd16_character * pszConcat);

CLASS_DECL_ACME ::wd16_character * __wd16cpy(::wd16_character * pszDst, const ::wd16_character * pszSrc);

CLASS_DECL_ACME ::wd16_character * __wd16ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len);

CLASS_DECL_ACME const ::wd16_character * __wd16chr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME ::wd16_character * __wd16pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind);

CLASS_DECL_ACME ::wd16_character * __wd16tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state);

CLASS_DECL_ACME const ::wd16_character * __wd16rchr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME int __wd16cmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

CLASS_DECL_ACME const ::wd16_character * __wd16str(const ::wd16_character * psz, const ::wd16_character * pszFind);

CLASS_DECL_ACME ::wd16_character __wd16tolower(::wd16_character ch);

CLASS_DECL_ACME ::wd16_character __wd16toupper(::wd16_character ch);

CLASS_DECL_ACME ::wd16_character * __wd16lwr(::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16lwr_s(::wd16_character * psz, strsize s);

CLASS_DECL_ACME ::wd16_character * __wd16upr(::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16upr_s(::wd16_character * psz, strsize s);

CLASS_DECL_ACME const ::wd16_character * __wd16ichr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME int __wd16icmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

CLASS_DECL_ACME const ::wd16_character * __wd16istr(const ::wd16_character * psz, const ::wd16_character * pszFind);

CLASS_DECL_ACME ::wd16_character * __u64towd16(::u64 u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end);

CLASS_DECL_ACME ::wd16_character * __i64towd16(::i64 i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end);

CLASS_DECL_ACME ::wd16_character * overlap_safe_wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, strsize srclen);

CLASS_DECL_ACME int __wd16coll(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

CLASS_DECL_ACME int __wd16icoll(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);

CLASS_DECL_ACME strsize __wd16spn(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME strsize __wd16cspn(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME i64 __wd16toi64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __wd16tou64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __wd16toi32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __wd16tou32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, i32 iBase);








