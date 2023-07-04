#pragma once


inline ::ansi_character * ansi_dup(const ::ansi_character * psz);
inline strsize ansi_len(const ::ansi_character * psz);
inline ::ansi_character * ansi_cat(::ansi_character * pszDst, const ::ansi_character * psz);
inline ::ansi_character * ansi_cpy(::ansi_character * pszDst, const ::ansi_character * psz);
inline ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const ::ansi_character * psz, strsize len);
inline const ::ansi_character * ansi_chr(const ::ansi_character * psz1, ::ansi_character ch);
inline ::ansi_character * ansi_pbrk(::ansi_character * psz, const ::ansi_character * pszCharsToFind);
inline ::ansi_character * ansi_tok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state);
inline ::ansi_character * ansi_token(::ansi_character * psz, const ::ansi_character * separators);
inline const ::ansi_character * ansi_rchr(const ::ansi_character * psz1, ::ansi_character ch);
inline int ansi_cmp(const ::ansi_character * psz1, const ::ansi_character * psz2);
inline int ansi_ncmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);
inline const ::ansi_character * ansi_str(const ::ansi_character * psz, const ::ansi_character * pszFind);
inline ::ansi_character ansi_tolower(::ansi_character ch);
inline ::ansi_character ansi_toupper(::ansi_character ch);
inline ::ansi_character * ansi_lwr(::ansi_character * psz);
inline ::ansi_character * ansi_lwr_s(::ansi_character * psz, strsize s);
inline ::ansi_character * ansi_upr(::ansi_character * psz);
inline ::ansi_character * ansi_upr_s(::ansi_character * psz, strsize s);
inline const ::ansi_character * ansi_ichr(const ::ansi_character * psz1, ::ansi_character ch);
CLASS_DECL_ACME int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2);
CLASS_DECL_ACME int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);
inline const ::ansi_character * ansi_istr(const ::ansi_character * psz, const ::ansi_character * pszFind);
//inline ::ansi_character * u64toansi(::u64 u, ::ansi_character * buf, int iBase);
//inline ::ansi_character * i64toansi(::u64 u, ::ansi_character * buf, int iBase);
inline int ansi_coll(const ::ansi_character * psz1, const ::ansi_character * psz2);
inline int ansi_ncoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);
CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2);
CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);
inline strsize ansi_spn(const ::ansi_character * psz1, const ::ansi_character * psz2);
inline strsize ansi_cspn(const ::ansi_character * psz1, const ::ansi_character * psz2);


inline strsize wd16_len(const ::wd16_character * psz);
inline strsize wd32_len(const ::wd32_character * psz);

inline ::wd16_character * wd16_cat(::wd16_character * pszDst, const ::wd16_character * psz);
inline ::wd32_character * wd32_cat(::wd32_character * pszDst, const ::wd32_character * psz);

inline ::wd16_character * wd16_cpy(::wd16_character * pszDst, const ::wd16_character * psz);
inline ::wd32_character * wd32_cpy(::wd32_character * pszDst, const ::wd32_character * psz);

inline ::wd16_character * wd16_ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len);
inline ::wd32_character * wd32_ncpy(::wd32_character * pszDst, const ::wd32_character * psz, strsize len);

inline const ::wd16_character * wd16_chr(const ::wd16_character * psz1, ::wd16_character ch);
inline const ::wd32_character * wd32_chr(const ::wd32_character * psz1, ::wd32_character ch);

inline ::wd16_character * wd16_pbrk(::wd16_character * psz, const ::wd16_character * pszCharsToFind);
inline ::wd32_character * wd32_pbrk(::wd32_character * psz, const ::wd32_character * pszCharsToFind);

inline ::wd16_character * wd16_tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state);
inline ::wd32_character * wd32_tok_r(::wd32_character * psz, const ::wd32_character * sep, ::wd32_character ** state);
inline ::wide_character * wide_tok_r(::wide_character * psz, const ::wide_character * sep, ::wide_character ** state);

inline const ::wd16_character * wd16_rchr(const ::wd16_character * psz1, ::wd16_character ch);
inline const ::wd32_character * wd32_rchr(const ::wd32_character * psz1, ::wd32_character ch);

inline int wd16_cmp(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline int wd32_cmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int wd16_ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);
inline int wd32_ncmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);

inline const ::wd16_character * wd16_str(const ::wd16_character * psz, const ::wd16_character * pszFind);
inline const ::wd32_character * wd32_str(const ::wd32_character * psz, const ::wd32_character * pszFind);

inline ::wd16_character wd16_tolower(::wd16_character ch);
inline ::wd32_character wd32_tolower(::wd32_character ch);

inline ::wd32_character wd16_toupper(::wd16_character ch);
inline ::wd32_character wd32_toupper(::wd32_character ch);


inline ::wd16_character * wd16_lwr(::wd16_character * psz);
inline ::wd32_character * wd32_lwr(::wd32_character * psz);


inline ::wd16_character * wd16_lwr_s(::wd16_character * psz, strsize s);
inline ::wd32_character * wd32_lwr_s(::wd32_character * psz, strsize s);


inline ::wd16_character * wd16_upr(::wd16_character * psz);
inline ::wd32_character * wd32_upr(::wd32_character * psz);


inline ::wd16_character * wd16_upr_s(::wd16_character * psz, strsize s);
inline ::wd32_character * wd32_upr_s(::wd32_character * psz, strsize s);


inline const ::wd16_character * wd16_ichr(const ::wd16_character * psz1, ::wd16_character ch);
inline const ::wd32_character * wd32_ichr(const ::wd32_character * psz1, ::wd32_character ch);

inline int wd16_icmp(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline int wd32_icmp(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline int wd16_nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);
inline int wd32_nicmp(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);
inline int wide_nicmp(const ::wide_character * psz1, const ::wide_character * psz2, strsize s);

inline const ::wd16_character * wd16_istr(const ::wd16_character * psz, const ::wd16_character * pszFind);
inline const ::wd32_character * wd32_istr(const ::wd32_character * psz, const ::wd32_character * pszFind);

inline int wd16_coll(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline int wd32_coll(const ::wd32_character * psz1, const ::wd32_character * psz2);
inline int wide_coll(const ::wide_character * psz1, const ::wide_character * psz2);

inline int wd16_ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);
inline int wd32_ncoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);
inline int wide_ncoll(const ::wide_character * psz1, const ::wide_character * psz2, strsize s);

inline int wd16_icoll(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline int wd32_icoll(const ::wd32_character * psz1, const ::wd32_character * psz2);
inline int wide_icoll(const ::wide_character * psz1, const ::wide_character * psz2);

inline int wd16_nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s);
inline int wd32_nicoll(const ::wd32_character * psz1, const ::wd32_character * psz2, strsize s);
inline int wide_nicoll(const ::wide_character * psz1, const ::wide_character * psz2, strsize s);

inline strsize wd16_spn(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline strsize wd32_spn(const ::wd32_character * psz1, const ::wd32_character * psz2);

inline strsize wd16_cspn(const ::wd16_character * psz1, const ::wd16_character * psz2);
inline strsize wd32_cspn(const ::wd32_character * psz1, const ::wd32_character * psz2);





