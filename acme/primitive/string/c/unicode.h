// Created from _unicode by camilo on 2022-11-07 09:21 <3ThomasBorregaardSorensen!!
#pragma once



inline const ansichar * unicode_next(const ansichar * psz);
inline const wd16char * unicode_next(const wd16char * psz);
inline const wd32char * unicode_next(const wd32char * psz);

inline ansichar * unicode_next(ansichar * psz) { return (ansichar *)unicode_next((const ansichar *)psz); }
inline wd16char * unicode_next(wd16char * psz) { return (wd16char *)unicode_next((const wd16char *)psz); }
inline wd32char * unicode_next(wd32char * psz) { return (wd32char *)unicode_next((const wd32char *)psz); }

inline const ansichar * unicode_increment(const ansichar *& psz) { return psz = unicode_next(psz); }
inline const wd16char * unicode_increment(const wd16char *& psz) { return psz = unicode_next(psz); }
inline const wd32char * unicode_increment(const wd32char *& psz) { return psz = unicode_next(psz); }


inline ansichar * unicode_increment(ansichar *& psz) { return (ansichar *)unicode_increment((const ansichar *&)psz); }
inline wd16char * unicode_increment(wd16char *& psz) { return (wd16char *)unicode_increment((const wd16char *&)psz); }
inline wd32char * unicode_increment(wd32char *& psz) { return (wd32char *)unicode_increment((const wd32char *&)psz); }


const ansichar * unicode_prior(const ansichar * psz, const ansichar * pszBeg);
const wd16char * unicode_prior(const wd16char * psz, const wd16char * pszBeg);
const wd32char * unicode_prior(const wd32char * psz, const wd32char * pszBeg);


inline const ::index unicode_prior_index(::index i, const ansichar * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const wd16char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }
inline const ::index unicode_prior_index(::index i, const wd32char * pszBeg) { auto p = unicode_prior(&pszBeg[i], pszBeg); return ::is_null(p) ? -1 : p - pszBeg; }


inline ansichar * unicode_prior(ansichar * psz, const ansichar * pszBeg) { return (ansichar *)unicode_prior((const ansichar *&)psz, pszBeg); }
inline wd16char * unicode_prior(wd16char * psz, const wd16char * pszBeg) { return (wd16char *)unicode_prior((const wd16char *&)psz, pszBeg); }
inline wd32char * unicode_prior(wd32char * psz, const wd32char * pszBeg) { return (wd32char *)unicode_prior((const wd32char *&)psz, pszBeg); }


inline const strsize unicode_decrement(strsize & i, const ansichar * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const wd16char * pszBeg) { return i = unicode_prior_index(i, pszBeg); }
inline const strsize unicode_decrement(strsize & i, const wd32char * pszBeg) { return i = unicode_prior_index(i, pszBeg); }


inline const ansichar * unicode_decrement(const ansichar *& psz, const ansichar * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const wd16char * unicode_decrement(const wd16char *& psz, const wd16char * pszBeg) { return psz = unicode_prior(psz, pszBeg); }
inline const wd32char * unicode_decrement(const wd32char *& psz, const wd32char * pszBeg) { return psz = unicode_prior(psz, pszBeg); }


inline ansichar * unicode_decrement(ansichar *& psz, const ansichar * pszBeg = nullptr)
{

   return (ansichar *)unicode_decrement((const ansichar *&)psz, pszBeg);

}


inline wd16char * unicode_decrement(wd16char *& psz, const wd16char * pszBeg = nullptr)
{

   return (wd16char *)unicode_decrement((const wd16char *&)psz, pszBeg);

}


inline wd32char * unicode_decrement(wd32char *& psz, const wd32char * pszBeg = nullptr)
{

   return (wd32char *)unicode_decrement((const wd32char *&)psz, pszBeg);

}



inline bool _str_safe_precmp(int & i, const ansichar * pszA, const ansichar * pszB);


inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource, strsize srclen);


// template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource, strsize srclen);



inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource, strsize srclen);



inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource, strsize srclen);



inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource, strsize srclen);



inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource, strsize srclen);



inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource, strsize srclen);



inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource, strsize srclen);


inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource, strsize srclen);


inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource);


inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource);


inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource);


inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource);


inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource);


inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource);


inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource);


inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource);


inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource);


inline void utf_to_utf(ansichar * ptarget, const ansichar * psource, strsize srclen);


inline void utf_to_utf(wd16char * ptarget, const wd16char * psource, strsize srclen);


inline void utf_to_utf(wd16char * ptarget, const wd32char * psource, strsize srclen);


inline void utf_to_utf(wd32char * ptarget, const wd32char * psource, strsize srclen);


inline void utf_to_utf(wd32char * ptarget, const wd16char * psource, strsize srclen);


inline void utf_to_utf(ansichar * ptarget, const wd16char * psource, strsize srclen);


inline void utf_to_utf(ansichar * ptarget, const wd32char * psource, strsize srclen);


inline void utf_to_utf(wd16char * ptarget, const ansichar * psource, strsize srclen);


inline void utf_to_utf(wd32char * ptarget, const ansichar * psource, strsize srclen);


inline void utf_to_utf(ansichar * ptarget, const ansichar * psource);


inline void utf_to_utf(wd16char * ptarget, const wd16char * psource);


inline void utf_to_utf(wd32char * ptarget, const wd16char * psource);


inline void utf_to_utf(wd32char * ptarget, const wd32char * psource);


inline void utf_to_utf(wd16char * ptarget, const wd32char * psource);


inline void utf_to_utf(ansichar * ptarget, const wd16char * psource);


inline void utf_to_utf(ansichar * ptarget, const wd32char * psource);


inline void utf_to_utf(wd16char * ptarget, const ansichar * psource);


inline void utf_to_utf(wd32char * ptarget, const ansichar * psource);



