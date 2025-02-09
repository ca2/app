#pragma once






CLASS_DECL_ACME ::wd32_character               __wd32charlowered(int i);
CLASS_DECL_ACME ::wd32_character               __wd32charuppered(int i);
CLASS_DECL_ACME int                    __wd32charisdigit(int i);
CLASS_DECL_ACME int                    __wd32charisalpha(int i);
CLASS_DECL_ACME int                    __wd32charisalnum(int i);
CLASS_DECL_ACME int                    __wd32charisspace(int i);



CLASS_DECL_ACME int                    __wd32charisxdigit(int i);


CLASS_DECL_ACME character_count __wd32len(const ::wd32_character * psz);

CLASS_DECL_ACME ::wd32_character * __wd32cat(::wd32_character * pszTarget, const ::wd32_character * pszConcat);

CLASS_DECL_ACME ::wd32_character * __wd32cpy(::wd32_character * pszDst, const ::wd32_character * pszSrc);

CLASS_DECL_ACME ::wd32_character * __wd32ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len);

CLASS_DECL_ACME const ::wd32_character * __wd32chr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME ::wd32_character * __wd32pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind);

CLASS_DECL_ACME ::wd32_character * __wd32tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state);

CLASS_DECL_ACME const ::wd32_character * __wd32rchr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME int __wd32cmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int __wd32ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd32_character * __wd32str(const ::wd32_character * psz, const ::wd32_character * pszFind);

CLASS_DECL_ACME ::wd32_character __wd32tolower(::wd32_character ch);

CLASS_DECL_ACME ::wd32_character __wd32toupper(::wd32_character ch);

CLASS_DECL_ACME ::wd32_character * __wd32lwr(::wd32_character * psz);

CLASS_DECL_ACME ::wd32_character * __wd32lwr_s(::wd32_character * psz, character_count s);

CLASS_DECL_ACME ::wd32_character * __wd32upr(::wd32_character * psz);

CLASS_DECL_ACME ::wd32_character * __wd32upr_s(::wd32_character * psz, character_count s);

CLASS_DECL_ACME const ::wd32_character * __wd32ichr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME int __wd32icmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int __wd32nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd32_character * __wd32istr(const ::wd32_character * psz, const ::wd32_character * pszFind);

CLASS_DECL_ACME ::wd32_character * __u64towd32(unsigned long long u, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character *& end);

CLASS_DECL_ACME ::wd32_character * __long_longtowd32(long long i, ::wd32_character * buf, int iBase, enum_digit_case edigitcase, ::wd32_character *& end);

CLASS_DECL_ACME ::wd32_character * overlap_safe_wd32ncpy(::wd32_character * pszDst, const ::wd32_character * pszSrc, character_count srclen);

CLASS_DECL_ACME int __wd32coll(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int __wd32ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);

CLASS_DECL_ACME int __wd32icoll(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int __wd32nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);

CLASS_DECL_ACME character_count __wd32spn(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME character_count __wd32cspn(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME long long __wd32toi64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned long long __wd32tou64(const ::wd32_character * psz, ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int __wd32toi32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int __wd32tou32(const ::wd32_character * psz, ::wd32_character ** ppszEnd, int iBase);






