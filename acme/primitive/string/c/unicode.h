// Created from _unicode by camilo on 2022-11-07 09:21 <3ThomasBorregaardSorensen!!
#pragma once



inline const ::ansi_character * unicode_next(const ::ansi_character * psz);
inline const ::wd16_character * unicode_next(const ::wd16_character * psz);
inline const ::wd32_character * unicode_next(const ::wd32_character * psz);

inline ::ansi_character * unicode_next(::ansi_character * psz) { return (::ansi_character *)unicode_next((const ::ansi_character *)psz); }
inline ::wd16_character * unicode_next(::wd16_character * psz) { return (::wd16_character *)unicode_next((const ::wd16_character *)psz); }
inline ::wd32_character * unicode_next(::wd32_character * psz) { return (::wd32_character *)unicode_next((const ::wd32_character *)psz); }

inline const ::ansi_character * unicode_increment(const ::ansi_character *& psz) { return psz = unicode_next(psz); }
inline const ::wd16_character * unicode_increment(const ::wd16_character *& psz) { return psz = unicode_next(psz); }
inline const ::wd32_character * unicode_increment(const ::wd32_character *& psz) { return psz = unicode_next(psz); }

inline ::ansi_character * unicode_increment(::ansi_character *& psz) { return (::ansi_character *)unicode_increment((const ::ansi_character *&)psz); }
inline ::wd16_character * unicode_increment(::wd16_character *& psz) { return (::wd16_character *)unicode_increment((const ::wd16_character *&)psz); }
inline ::wd32_character * unicode_increment(::wd32_character *& psz) { return (::wd32_character *)unicode_increment((const ::wd32_character *&)psz); }


inline const ::ansi_character * unicode_prior(const ::ansi_character * psz, const ::ansi_character * pszBeg);
inline const ::wd16_character * unicode_prior(const ::wd16_character * psz, const ::wd16_character * pszBeg);
inline const ::wd32_character * unicode_prior(const ::wd32_character * psz, const ::wd32_character * pszBeg);


inline const ::index unicode_prior_index(::index i, const ::ansi_character * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const ::wd16_character * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const ::wd32_character * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }

inline ::ansi_character * unicode_prior(::ansi_character * psz, const ::ansi_character * pszBeg) { return (::ansi_character *)unicode_prior((const ::ansi_character *&)psz, pszBeg); }
inline ::wd16_character * unicode_prior(::wd16_character * psz, const ::wd16_character * pszBeg) { return (::wd16_character *)unicode_prior((const ::wd16_character *&)psz, pszBeg); }
inline ::wd32_character * unicode_prior(::wd32_character * psz, const ::wd32_character * pszBeg) { return (::wd32_character *)unicode_prior((const ::wd32_character *&)psz, pszBeg); }

inline const strsize unicode_decrement(strsize & i, const ::ansi_character * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const ::wd16_character * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const ::wd32_character * pszBeg) { return i = unicode_prior_index(i, pszBeg); }

inline const ::ansi_character * unicode_decrement(const ::ansi_character *& psz, const ::ansi_character * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const ::wd16_character * unicode_decrement(const ::wd16_character *& psz, const ::wd16_character * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const ::wd32_character * unicode_decrement(const ::wd32_character *& psz, const ::wd32_character * pszBeg) { return psz = unicode_prior(psz, pszBeg); }


inline ::ansi_character * unicode_decrement(::ansi_character *& psz, const ::ansi_character * pszBeg = nullptr)
{

   return (::ansi_character *)unicode_decrement((const ::ansi_character *&)psz, pszBeg);

}


inline ::wd16_character * unicode_decrement(::wd16_character *& psz, const ::wd16_character * pszBeg = nullptr)
{

   return (::wd16_character *)unicode_decrement((const ::wd16_character *&)psz, pszBeg);

}


inline ::wd32_character * unicode_decrement(::wd32_character *& psz, const ::wd32_character * pszBeg = nullptr)
{

   return (::wd32_character *)unicode_decrement((const ::wd32_character *&)psz, pszBeg);

}



//CLASS_DECL_ACME bool _str_safe_precmp(int & i, const ::ansi_character * pszA, const ::ansi_character * pszB);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::ansi_character * psource, strsize srclen);


// template <  >
CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::wd16_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::ansi_character * psource, strsize srclen);



CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::wd32_character * psource, strsize srclen);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::ansi_character * psource, strsize srclen);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::ansi_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::wd16_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::ansi_character *, const ::wd32_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd16_character *, const ::ansi_character * psource);


CLASS_DECL_ACME strsize utf_to_utf_length(const ::wd32_character *, const ::ansi_character * psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::ansi_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::ansi_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::ansi_character * psource, strsize srclen);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::ansi_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource);


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::ansi_character * psource);


CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::ansi_character * psource);



