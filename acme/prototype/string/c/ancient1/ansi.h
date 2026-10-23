#pragma once




CLASS_DECL_ACME ::ansi_character       __ansicharlowered(::i32 i);
CLASS_DECL_ACME ::ansi_character       __ansicharuppered(::i32 i);
CLASS_DECL_ACME ::i32                    __ansicharisdigit(::i32 i);
CLASS_DECL_ACME ::i32                    __ansicharisalpha(::i32 i);
CLASS_DECL_ACME ::i32                    __ansicharisalnum(::i32 i);
CLASS_DECL_ACME ::i32                    __ansicharisspace(::i32 i);
CLASS_DECL_ACME ::i32                    __ansicharisxdigit(::i32 i);


CLASS_DECL_ACME ::i32                    __ansicharishexadecimal(::i32 i);



CLASS_DECL_ACME character_count __ansilen(const_char_pointer psz);

CLASS_DECL_ACME ::ansi_character * __ansicat(::ansi_character * pszTarget, const_char_pointer pszConcat);

CLASS_DECL_ACME ::ansi_character * __ansicpy(::ansi_character * pszDst, const_char_pointer pszSrc);

CLASS_DECL_ACME ::ansi_character * __ansincpy(::ansi_character * pszDst, const_char_pointer psz, character_count len);

CLASS_DECL_ACME const_char_pointer __ansichr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansipbrk(::ansi_character * psz, const_char_pointer pszCharsToFind);

CLASS_DECL_ACME ::ansi_character * __ansitok_r(::ansi_character * psz, const_char_pointer sep, ::ansi_character ** state);

CLASS_DECL_ACME const_char_pointer __ansirchr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME ::i32 __ansicmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME ::i32 __ansincmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer __ansistr(const_char_pointer psz, const_char_pointer pszFind);

CLASS_DECL_ACME ::ansi_character __ansitolower(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character __ansitoupper(::ansi_character ch);

//CLASS_DECL_ACME ::ansi_character __ansiisdigit(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansilwr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansilwr_s(::ansi_character * psz, character_count s);

CLASS_DECL_ACME ::ansi_character * __ansiupr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansiupr_s(::ansi_character * psz, character_count s);

CLASS_DECL_ACME const_char_pointer __ansiichr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME ::i32 __ansiicmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME ::i32 __ansinicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer __ansiistr(const_char_pointer psz, const_char_pointer pszFind);


CLASS_DECL_ACME ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const_char_pointer pszSrc, character_count srclen);

CLASS_DECL_ACME ::i32 __ansicoll(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME ::i32 __ansincoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME ::i32 __ansiicoll(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME ::i32 __ansinicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME character_count __ansispn(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME character_count __ansicspn(const_char_pointer psz1, const_char_pointer psz2);


CLASS_DECL_ACME ::i64 __ansitoi64(const_char_pointer psz, ::ansi_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::u64 __ansitou64(const_char_pointer psz, ::ansi_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::i32 __ansitoi32(const_char_pointer psz, ::ansi_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::u32 __ansitou32(const_char_pointer psz, ::ansi_character ** ppszEnd, ::i32 iBase);


CLASS_DECL_ACME ::ansi_character lower_char(::i32 ch);
CLASS_DECL_ACME ::ansi_character upper_char(::i32 ch);
CLASS_DECL_ACME void make_lower(::ansi_character * psz);



