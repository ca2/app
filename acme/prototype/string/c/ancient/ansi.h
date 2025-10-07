#pragma once




CLASS_DECL_ACME ::ansi_character       __ansicharlowered(int i);
CLASS_DECL_ACME ::ansi_character       __ansicharuppered(int i);
CLASS_DECL_ACME int                    __ansicharisdigit(int i);
CLASS_DECL_ACME int                    __ansicharisalpha(int i);
CLASS_DECL_ACME int                    __ansicharisalnum(int i);
CLASS_DECL_ACME int                    __ansicharisspace(int i);
CLASS_DECL_ACME int                    __ansicharisxdigit(int i);


CLASS_DECL_ACME int                    __ansicharishexadecimal(int i);



CLASS_DECL_ACME character_count __ansilen(const_char_pointer psz);

CLASS_DECL_ACME ::ansi_character * __ansicat(::ansi_character * pszTarget, const_char_pointer pszConcat);

CLASS_DECL_ACME ::ansi_character * __ansicpy(::ansi_character * pszDst, const_char_pointer pszSrc);

CLASS_DECL_ACME ::ansi_character * __ansincpy(::ansi_character * pszDst, const_char_pointer psz, character_count len);

CLASS_DECL_ACME const_char_pointer __ansichr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansipbrk(::ansi_character * psz, const_char_pointer pszCharsToFind);

CLASS_DECL_ACME ::ansi_character * __ansitok_r(::ansi_character * psz, const_char_pointer sep, ::ansi_character ** state);

CLASS_DECL_ACME const_char_pointer __ansirchr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME int __ansicmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int __ansincmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer __ansistr(const_char_pointer psz, const_char_pointer pszFind);

CLASS_DECL_ACME ::ansi_character __ansitolower(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character __ansitoupper(::ansi_character ch);

//CLASS_DECL_ACME ::ansi_character __ansiisdigit(::ansi_character ch);

CLASS_DECL_ACME ::ansi_character * __ansilwr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansilwr_s(::ansi_character * psz, character_count s);

CLASS_DECL_ACME ::ansi_character * __ansiupr(::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * __ansiupr_s(::ansi_character * psz, character_count s);

CLASS_DECL_ACME const_char_pointer __ansiichr(const_char_pointer psz1, ::ansi_character ch);

CLASS_DECL_ACME int __ansiicmp(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int __ansinicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME const_char_pointer __ansiistr(const_char_pointer psz, const_char_pointer pszFind);


CLASS_DECL_ACME ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const_char_pointer pszSrc, character_count srclen);

CLASS_DECL_ACME int __ansicoll(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int __ansincoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME int __ansiicoll(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME int __ansinicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);

CLASS_DECL_ACME character_count __ansispn(const_char_pointer psz1, const_char_pointer psz2);

CLASS_DECL_ACME character_count __ansicspn(const_char_pointer psz1, const_char_pointer psz2);


CLASS_DECL_ACME long long __ansitoi64(const_char_pointer psz, ::ansi_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned long long __ansitou64(const_char_pointer psz, ::ansi_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int __ansitoi32(const_char_pointer psz, ::ansi_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int __ansitou32(const_char_pointer psz, ::ansi_character ** ppszEnd, int iBase);


CLASS_DECL_ACME ::ansi_character lower_char(int ch);
CLASS_DECL_ACME ::ansi_character upper_char(int ch);
CLASS_DECL_ACME void make_lower(::ansi_character * psz);



