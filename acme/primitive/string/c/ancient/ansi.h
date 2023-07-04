#pragma once




CLASS_DECL_ACME ::ansi_character       __ansicharlowered(i32 i);
CLASS_DECL_ACME ::ansi_character       __ansicharuppered(i32 i);
CLASS_DECL_ACME i32                    __ansicharisdigit(i32 i);
CLASS_DECL_ACME i32                    __ansicharisalpha(i32 i);
CLASS_DECL_ACME i32                    __ansicharisalnum(i32 i);
CLASS_DECL_ACME i32                    __ansicharisspace(i32 i);


CLASS_DECL_ACME i32                    __ansicharishexadecimal(i32 i);



CLASS_DECL_ACME strsize __ansilen(const ::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansicat(::ansi_character * pszTarget, const ::ansi_character * pszConcat);

CLASS_DECL_ACME ::ansi_character * __ansicpy(::ansi_character * pszDst, const ::ansi_character * pszSrc);

CLASS_DECL_ACME ::ansi_character * __ansincpy(::ansi_character * pszDst, const ::ansi_character * psz, strsize len);

CLASS_DECL_ACME const ::ansi_character * __ansichr(const ::ansi_character * psz1, ::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansipbrk(::ansi_character * psz, const ::ansi_character * pszCharsToFind);

CLASS_DECL_ACME ::ansi_character * __ansitok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state);

CLASS_DECL_ACME const ::ansi_character * __ansirchr(const ::ansi_character * psz1, ::ansi_character ch);

CLASS_DECL_ACME int __ansicmp(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int __ansincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);

CLASS_DECL_ACME const ::ansi_character * __ansistr(const ::ansi_character * psz, const ::ansi_character * pszFind);

CLASS_DECL_ACME ::ansi_character __ansitolower(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character __ansitoupper(::ansi_character ch);

//CLASS_DECL_ACME ::ansi_character __ansiisdigit(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansilwr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansilwr_s(::ansi_character * psz, strsize s);

CLASS_DECL_ACME ::ansi_character * __ansiupr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansiupr_s(::ansi_character * psz, strsize s);

CLASS_DECL_ACME const ::ansi_character * __ansiichr(const ::ansi_character * psz1, ::ansi_character ch);

CLASS_DECL_ACME int __ansiicmp(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int __ansinicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);

CLASS_DECL_ACME const ::ansi_character * __ansiistr(const ::ansi_character * psz, const ::ansi_character * pszFind);


CLASS_DECL_ACME ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const ::ansi_character * pszSrc, strsize srclen);

CLASS_DECL_ACME int __ansicoll(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int __ansincoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);

CLASS_DECL_ACME int __ansiicoll(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int __ansinicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);

CLASS_DECL_ACME strsize __ansispn(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME strsize __ansicspn(const ::ansi_character * psz1, const ::ansi_character * psz2);


CLASS_DECL_ACME i64 __ansitoi64(const ::ansi_character * psz, ::ansi_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 __ansitou64(const ::ansi_character * psz, ::ansi_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 __ansitoi32(const ::ansi_character * psz, ::ansi_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 __ansitou32(const ::ansi_character * psz, ::ansi_character ** ppszEnd, i32 iBase);


CLASS_DECL_ACME ::ansi_character lower_char(i32 ch);
CLASS_DECL_ACME ::ansi_character upper_char(i32 ch);
CLASS_DECL_ACME void make_lower(::ansi_character * psz);



