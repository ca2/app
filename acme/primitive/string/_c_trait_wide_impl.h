

#ifdef WINDOWS_DESKTOP

#define WIDECHARTYPE wd16

#else

#define WIDECHARTYPE wd32

#endif

#define CONCAT_MID_WIDECHARTYPE(a, b) a ## WIDECHARTYPE ## b




inline widechar * overlap_safe_w32ncpy(widechar * pszDst, const widechar * pszSrc, strsize srclen)
{
   return CONCAT_MID_WIDECHARTYPE(overlap_safe_ , ncpy);
}


inline strsize __widelen(const widechar * psz)
{
   return CONCAT_MID_WIDECHARTYPE(__, len)(psz);
}

inline widechar * __widecpy(widechar * pszDst, const widechar * pszSrc)
{
   return CONCAT_MID_WIDECHARTYPE(__, len)(pszDst, pszSrc);
}


inline widechar * __widencpy(widechar * pszDst, const widechar * psz, strsize len)
{
   return CONCAT_MID_WIDECHARTYPE(__, len)(pszDst, psz, len);
}


inline const widechar * __widechr(const widechar * psz, widechar ch)
{
   return CONCAT_MID_WIDECHARTYPE(__, len)(psz, ch);
}


inline widechar * __widepbrk(widechar * psz, const widechar * pszFind)
{
   return CONCAT_MID_WIDECHARTYPE(__, pbrk)(psz, pszFind);
}


inline widechar * __widetok_r(widechar * psz, const widechar * sep, widechar ** state)
{
   return CONCAT_MID_WIDECHARTYPE(__, tok_r)(psz, sep, state);
}



inline const widechar * __widerchr(const widechar * psz, widechar ch)
{
   return CONCAT_MID_WIDECHARTYPE(__, rchr)(psz, ch);
}


inline int __widecmp(const widechar * psz1, const widechar * psz2)
{
   return CONCAT_MID_WIDECHARTYPE(__, cmp)(psz1, psz2);
}


inline int __widencmp(const widechar * psz1, const widechar * psz2, size_t s)
{
   return CONCAT_MID_WIDECHARTYPE(__, ncmp)(psz1, psz2, s);
}


inline const widechar * __widestr(const widechar * psz, const widechar * pszFind)
{

   return CONCAT_MID_WIDECHARTYPE(__, str)(psz, pszFind);
}



inline widechar __widetolower(widechar ch)
{

   return CONCAT_MID_WIDECHARTYPE(__, tolower)(ch);

}


inline widechar __widetoupper(widechar ch)
{

   return CONCAT_MID_WIDECHARTYPE(__, toupper)(ch);

}



inline widechar * __widelwr(widechar * psz)
{

   return CONCAT_MID_WIDECHARTYPE(__, lwr)(psz);
}


inline widechar * __widelwr_s(widechar * psz, strsize s)
{

   return CONCAT_MID_WIDECHARTYPE(__, lwr_s)(psz, s);
}


inline widechar * __wideupr(widechar * psz)
{
   return CONCAT_MID_WIDECHARTYPE(__, upr)(psz);
}


inline widechar * __wideupr_s(widechar * psz, strsize s)
{
   return CONCAT_MID_WIDECHARTYPE(__, upr_s)(psz, s);
}

inline const widechar * __wideichr(const widechar * psz, widechar ch)
{
   return CONCAT_MID_WIDECHARTYPE(__, ichr)(psz, ch);
}





inline int __wideicmp(const widechar * psz1, const widechar * psz2)
{
   return CONCAT_MID_WIDECHARTYPE(__, icmp)(psz1, psz2);
}


inline int __wideincmp(const widechar * psz1, const widechar * psz2, size_t s)
{
   return CONCAT_MID_WIDECHARTYPE(__, incmp)(psz1, psz2);
}


inline const widechar * __wideistr(const widechar * psz, const widechar * pszFind)
{
   return CONCAT_MID_WIDECHARTYPE(__, istr)(psz, pszFind);
}


inline int __widecoll(const widechar * psz1, const widechar * psz2) { return CONCAT_MID_WIDECHARTYPE(__, coll)(psz1, psz2); }

inline int __widencoll(const widechar * psz1, const widechar * psz2, size_t s) { return CONCAT_MID_WIDECHARTYPE(__, ncoll)(psz1, psz2, s); }

inline int __wideicoll(const widechar * psz1, const widechar * psz2) { return CONCAT_MID_WIDECHARTYPE(__, icoll)(psz1, psz2); }

inline int __widenicoll(const widechar * psz1, const widechar * psz2, size_t s) { return CONCAT_MID_WIDECHARTYPE(__, nicoll)(psz1, psz2, s); }

inline strsize __widespn(const widechar * psz1, const widechar * psz2)
{
   return CONCAT_MID_WIDECHARTYPE(__, spn)(psz1, psz2);
}

inline strsize __widecspn(const widechar * psz1, const widechar * psz2)
{
   return CONCAT_MID_WIDECHARTYPE(__, cspn)(psz1, psz2);
}





