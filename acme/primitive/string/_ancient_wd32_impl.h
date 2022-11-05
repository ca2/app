




inline wd32char __wd32charlowered(i32 i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
inline wd32char __wd32charuppered(i32 i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
inline i32 __wd32charisdigit(i32 i) { return i >= L'0' && i <= L'9'; }
inline i32 __wd32charisalpha(i32 i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
inline i32 __wd32charisalnum(i32 i) { return wd32_char_isalpha(i) || wd32_char_isdigit(i); }
inline i32 __wd32charisspace(i32 ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }

inline i32 __wd32charishexadecimal(i32 i) { return wd32_char_isdigit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }


inline wd32char * overlap_safe_wd32ncpy(wd32char * pszDst, const wd32char * pszSrc, strsize srclen)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, srclen * sizeof(wd32char)))
      {

         memmove(pszDst, pszSrc, srclen * sizeof(wd32char));

      }
      else
      {

         wd32_ncpy(pszDst, pszSrc, srclen);

      }


   }

   return pszDst;

}


inline strsize __wd32len(const wd32char * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}


inline wd32char * __wd32cat(wd32char * pszTarget, const wd32char * pszConcat)
{

   __wd32cpy(pszTarget + wd32_len(pszTarget), pszConcat);

   return pszTarget;

}



inline wd32char * __wd32cpy(wd32char * pszDst, const wd32char * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}


inline wd32char * __wd32ncpy(wd32char * pszDst, const wd32char * psz, strsize len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}


inline const wd32char * __wd32chr(const wd32char * psz, wd32char ch)
{

   while (*psz)
   {

      if (*psz == ch)
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


inline wd32char * __wd32pbrk(wd32char * psz, const wd32char * pszFind)
{

   while (*psz)
   {

      auto p = pszFind;

      while (*p)
      {

         if (*psz == *p)
         {

            return psz;

         }

         p++;

      }

      psz++;

   }

   return nullptr;

}


inline wd32char * __wd32tok_r(wd32char * psz, const wd32char * sep, wd32char ** state)
{

   if (!psz)
   {

      psz = *state;

      if (!psz)
      {

         return nullptr;

      }

   }

   auto p = wd32_pbrk(psz, sep);

   if (p)
   {

      *p = (wd32char)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}



inline const wd32char * __wd32rchr(const wd32char * psz, wd32char ch)
{

   auto p = psz + wd32_len(psz) - 1;

   while (p >= psz)
   {

      if (*psz == ch)
      {

         return psz;

      }

      p--;

   }

   return nullptr;

}


inline int __wd32cmp(const wd32char * psz1, const wd32char * psz2)
{

   int iCompare = 0;

   while (*psz1 && *psz2)
   {

      iCompare = *psz1 - *psz2;

      psz1++;

      psz2++;

   }

   return iCompare;

}


inline int __wd32ncmp(const wd32char * psz1, const wd32char * psz2, size_t s)
{

   int iCompare = 0;

   while (*psz1 && *psz2 && s > 0)
   {

      iCompare = *psz1 - *psz2;

      psz1++;

      psz2++;

      s--;

   }

   return iCompare;

}


inline const wd32char * __wd32str(const wd32char * psz, const wd32char * pszFind)
{

   auto lenFind = wd32_len(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = wd32_chr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (wd32_ncmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = wd32_chr(psz, *pszFind);

   } while (p);

   return nullptr;

}



inline wd32char __wd32tolower(wd32char ch)
{

   return (ch >= (wd32char)L'A' && ch <= (wd32char)L'Z') ? (ch - (wd32char)L'A') + (wd32char)L'a' : ch;

}


inline wd32char __wd32toupper(wd32char ch)
{

   return (ch >= (wd32char)L'a' && ch <= (wd32char)L'z') ? (ch - (wd32char)L'a') + (wd32char)L'A' : ch;

}



inline wd32char * __wd32lwr(wd32char * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd32_tolower(*p);

      p++;

   }

   return psz;

}


inline wd32char * __wd32lwr_s(wd32char * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = wd32_tolower(*p);

      p++;

      s--;

   }

   return psz;

}


inline wd32char * __wd32upr(wd32char * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd32_toupper(*p);

      p++;

   }

   return psz;

}


inline wd32char * __wd32upr_s(wd32char * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = wd32_toupper(*p);

      p++;

      s--;

   }

   return psz;

}

inline const wd32char * __wd32ichr(const wd32char * psz, wd32char ch)
{

   ch = wd32_tolower(ch);

   while (*psz)
   {

      if (wd32_tolower(*psz) == ch)
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}





inline int __wd32icmp(const wd32char * psz1, const wd32char * psz2)
{

   int iCompare = 0;

   while (*psz1 && *psz2)
   {

      iCompare = wd32_tolower(*psz1) - wd32_tolower(*psz2);

      psz1++;

      psz2++;

   }

   return iCompare;

}


inline int __wd32nicmp(const wd32char * psz1, const wd32char * psz2, size_t s)
{

   int iCompare = 0;

   while (*psz1 && *psz2 && s > 0)
   {

      iCompare = wd32_tolower(*psz1) - wd32_tolower(*psz2);

      psz1++;

      psz2++;

      s--;

   }

   return iCompare;

}


inline const wd32char * __wd32istr(const wd32char * psz, const wd32char * pszFind)
{

   auto lenFind = wd32_len(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = wd32_ichr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (wd32_nicmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = wd32_ichr(psz, *pszFind);

   } while (p);

   return nullptr;

}


inline int __wd32coll(const wd32char * psz1, const wd32char * psz2) { return wd32_cmp(psz1, psz2); }

inline int __wd32ncoll(const wd32char * psz1, const wd32char * psz2, size_t s) { return wd32_ncmp(psz1, psz2, s); }

inline int __wd32icoll(const wd32char * psz1, const wd32char * psz2) { return wd32_icmp(psz1, psz2); }

inline int __wd32nicoll(const wd32char * psz1, const wd32char * psz2, size_t s) { return wd32_nicmp(psz1, psz2, s); }

inline strsize __wd32spn(const wd32char * psz1, const wd32char * psz2)
{

   auto pszStart = psz1;

   while (*psz1)
   {

      auto p = psz2;

      while (*p)
      {

         if (*p == *psz1)
         {

            break;

         }

         p++;

      }

      if (!*p)
      {

         break;

      }

      psz1++;

   }

   return psz1 - pszStart;

}

inline strsize __wd32cspn(const wd32char * psz1, const wd32char * psz2)
{

   auto pszStart = psz1;

   while (*psz1)
   {

      auto p = psz2;

      while (*p)
      {

         if (*p == *psz1)
         {

            break;

         }

         p++;

      }

      if (*p)
      {

         break;

      }

      psz1++;

   }

   return psz1 - pszStart;

}







inline void make_upper(wd32char * psz)
{

   while (*psz)
   {
      *psz = upper_char(*psz);
      psz++;
   }

}
