// From ../coupling.h by camilo on 2026-09-26 16:44 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
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
CLASS_DECL_ACME ::i32 ansi_cmp(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME ::i32 ansi_ncmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_str(const_char_pointer psz, const_char_pointer pszFind);
CLASS_DECL_ACME ::ansi_character ansi_tolower(::ansi_character ch);
CLASS_DECL_ACME ::ansi_character ansi_toupper(::ansi_character ch);
CLASS_DECL_ACME ::ansi_character * ansi_lwr(::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_lwr_s(::ansi_character * psz, character_count s);
CLASS_DECL_ACME ::ansi_character * ansi_upr(::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_upr_s(::ansi_character * psz, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_ichr(const_char_pointer psz1, ::ansi_character ch);
CLASS_DECL_ACME ::i32 ansi_icmp(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME ::i32 ansi_nicmp(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME const_char_pointer ansi_istr(const_char_pointer psz, const_char_pointer pszFind);
CLASS_DECL_ACME ::i32 ansi_coll(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME ::i32 ansi_ncoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME ::i32 ansi_icoll(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME ::i32 ansi_nicoll(const_char_pointer psz1, const_char_pointer psz2, character_count s);
CLASS_DECL_ACME character_count ansi_spn(const_char_pointer psz1, const_char_pointer psz2);
CLASS_DECL_ACME character_count ansi_cspn(const_char_pointer psz1, const_char_pointer psz2);
