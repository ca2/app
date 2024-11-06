#pragma once





CLASS_DECL_ACME ::wd16_character               __wd16charlowered(int i);
CLASS_DECL_ACME ::wd16_character               __wd16charuppered(int i);
CLASS_DECL_ACME int                    __wd16charisdigit(int i);
CLASS_DECL_ACME int                    __wd16charisalpha(int i);
CLASS_DECL_ACME int                    __wd16charisalnum(int i);
CLASS_DECL_ACME int                    __wd16charisspace(int i);


CLASS_DECL_ACME int                    __wd16charisxdigit(int i);


CLASS_DECL_ACME character_count __wd16len(const ::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16cat(::wd16_character * pszTarget, const ::wd16_character * pszConcat);

CLASS_DECL_ACME ::wd16_character * __wd16cpy(::wd16_character * pszDst, const ::wd16_character * pszSrc);

CLASS_DECL_ACME ::wd16_character * __wd16ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len);

CLASS_DECL_ACME const ::wd16_character * __wd16chr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME ::wd16_character * __wd16pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind);

CLASS_DECL_ACME ::wd16_character * __wd16tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state);

CLASS_DECL_ACME const ::wd16_character * __wd16rchr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME int __wd16cmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd16_character * __wd16str(const ::wd16_character * psz, const ::wd16_character * pszFind);

CLASS_DECL_ACME ::wd16_character __wd16tolower(::wd16_character ch);

CLASS_DECL_ACME ::wd16_character __wd16toupper(::wd16_character ch);

CLASS_DECL_ACME ::wd16_character * __wd16lwr(::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16lwr_s(::wd16_character * psz, character_count s);

CLASS_DECL_ACME ::wd16_character * __wd16upr(::wd16_character * psz);

CLASS_DECL_ACME ::wd16_character * __wd16upr_s(::wd16_character * psz, character_count s);

CLASS_DECL_ACME const ::wd16_character * __wd16ichr(const ::wd16_character * psz1, ::wd16_character ch);

CLASS_DECL_ACME int __wd16icmp(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd16_character * __wd16istr(const ::wd16_character * psz, const ::wd16_character * pszFind);

CLASS_DECL_ACME ::wd16_character * __u64towd16(huge_natural u, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end);

CLASS_DECL_ACME ::wd16_character * __huge_integertowd16(huge_integer i, ::wd16_character * buf, int iBase, enum_digit_case edigitcase, ::wd16_character *& end);

CLASS_DECL_ACME ::wd16_character * overlap_safe_wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, character_count srclen);

CLASS_DECL_ACME int __wd16coll(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);

CLASS_DECL_ACME int __wd16icoll(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME int __wd16nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);

CLASS_DECL_ACME character_count __wd16spn(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME character_count __wd16cspn(const ::wd16_character * psz1, const ::wd16_character * psz2);

CLASS_DECL_ACME huge_integer __wd16toi64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME huge_natural __wd16tou64(const ::wd16_character * psz, ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int __wd16toi32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int __wd16tou32(const ::wd16_character * psz, ::wd16_character ** ppszEnd, int iBase);








