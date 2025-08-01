#pragma once


CLASS_DECL_ACME ::ansi_character * ansi_dup(const_char_pointer psz);
CLASS_DECL_ACME character_count ansi_len(const_char_pointer psz);
CLASS_DECL_ACME character_count ansi_nlen(const_char_pointer psz, memsize len);
CLASS_DECL_ACME ::ansi_character * ansi_cat(::ansi_character * pszDst, const_char_pointer psz);
CLASS_DECL_ACME ::ansi_character * ansi_cpy(::ansi_character * pszDst, const_char_pointer psz);
CLASS_DECL_ACME ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const_char_pointer psz, character_count len);
CLASS_DECL_ACME const_char_pointer ansi_chr(const_char_pointer psz1, ::ansi_character ch);
CLASS_DECL_ACME const_char_pointer ansi_pbrk(const_char_pointer psz, const_char_pointer pszCharsToFind);
CLASS_DECL_ACME ::ansi_character * ansi_tok_r(::ansi_character * psz, const_char_pointer sep, ::ansi_character ** state);
CLASS_DECL_ACME ::ansi_character * ansi_token(::ansi_character * psz, const_char_pointer separators);
CLASS_DECL_ACME const_char_pointer ansi_rchr(const_char_pointer psz1, ::ansi_character ch);
CLASS_DECL_ACME int ansi_cmp(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME int ansi_ncmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_str(const_char_pointer psz, const_char_pointer pszFind);
CLASS_DECL_ACME ::ansi_character ansi_tolower(::ansi_character ch);
CLASS_DECL_ACME ::ansi_character ansi_toupper(::ansi_character ch);
CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s);
CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_ichr(const_char_pointer psz1, ::ansi_character ch);
CLASS_DECL_ACME int ansi_icmp(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME int ansi_nicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_istr(const_char_pointer psz, const_char_pointer pszFind);
//CLASS_DECL_ACME ::ansi_character * u64toansi(unsigned long long u, ::ansi_character * buf, int iBase);
//CLASS_DECL_ACME ::ansi_character * i64toansi(unsigned long long u, ::ansi_character * buf, int iBase);
CLASS_DECL_ACME int ansi_coll(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME int ansi_ncoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME int ansi_icoll(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME int ansi_nicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME character_count ansi_spn(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME character_count ansi_cspn(const_char_pointer psz1, const_char_pointer psz2);


CLASS_DECL_ACME character_count wd16_len(const ::wd16_character * psz);
CLASS_DECL_ACME character_count wd32_len(const ::wd32_character * psz);

CLASS_DECL_ACME ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz);
CLASS_DECL_ACME ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz);

CLASS_DECL_ACME ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz);
CLASS_DECL_ACME ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz);

CLASS_DECL_ACME ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, character_count len);
CLASS_DECL_ACME ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, character_count len);

CLASS_DECL_ACME const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch);
CLASS_DECL_ACME const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind);
CLASS_DECL_ACME ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind);

CLASS_DECL_ACME ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state);
CLASS_DECL_ACME ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state);
CLASS_DECL_ACME ::wide_character * wide_tok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state);

CLASS_DECL_ACME const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch);
CLASS_DECL_ACME const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);
CLASS_DECL_ACME int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind);
CLASS_DECL_ACME const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind);

CLASS_DECL_ACME ::wd16_character wd16_tolower(::wd16_character ch);
CLASS_DECL_ACME ::wd32_character wd32_tolower(::wd32_character ch);

CLASS_DECL_ACME ::wd32_character wd16_toupper(::wd16_character ch);
CLASS_DECL_ACME ::wd32_character wd32_toupper(::wd32_character ch);


CLASS_DECL_ACME ::wd16_character * wd16_lwr(::wd16_character * psz);
CLASS_DECL_ACME ::wd32_character * wd32_lwr(::wd32_character * psz);


CLASS_DECL_ACME ::wd16_character * wd16_lwr_s(::wd16_character * psz, character_count s);
CLASS_DECL_ACME ::wd32_character * wd32_lwr_s(::wd32_character * psz, character_count s);


CLASS_DECL_ACME ::wd16_character * wd16_upr(::wd16_character * psz);
CLASS_DECL_ACME ::wd32_character * wd32_upr(::wd32_character * psz);


CLASS_DECL_ACME ::wd16_character * wd16_upr_s(::wd16_character * psz, character_count s);
CLASS_DECL_ACME ::wd32_character * wd32_upr_s(::wd32_character * psz, character_count s);


CLASS_DECL_ACME const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch);
CLASS_DECL_ACME const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch);

CLASS_DECL_ACME int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);
CLASS_DECL_ACME int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);
CLASS_DECL_ACME int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, character_count s);

CLASS_DECL_ACME const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind);
CLASS_DECL_ACME const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind);

CLASS_DECL_ACME int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2);
CLASS_DECL_ACME int wide_coll(const ::wide_character * psz1, const ::wide_character * psz2);

CLASS_DECL_ACME int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);
CLASS_DECL_ACME int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);
CLASS_DECL_ACME int wide_ncoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s);

CLASS_DECL_ACME int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2);
CLASS_DECL_ACME int wide_icoll(const ::wide_character * psz1, const ::wide_character * psz2);

CLASS_DECL_ACME int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, character_count s);
CLASS_DECL_ACME int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, character_count s);
CLASS_DECL_ACME int wide_nicoll(const ::wide_character * psz1, const ::wide_character * psz2, character_count s);

CLASS_DECL_ACME character_count wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME character_count wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2);

CLASS_DECL_ACME character_count wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2);
CLASS_DECL_ACME character_count wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2);





