




inline wd16char __wd16charlowered(i32 i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
inline wd16char __wd16charuppered(i32 i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
inline i32 __wd16charisdigit(i32 i) { return i >= L'0' && i <= L'9'; }
inline i32 __wd16charishexadecimal(i32 i) { return wd16_char_is_digit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }
inline i32 __wd16charisalphabetic(i32 i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
inline i32 __wd16charisalphanumeric(i32 i) { return wd16_char_is_alphabetic(i) || wd16_char_is_digit(i); }
inline i32 __wd16charisspace(i32 ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }


inline wd16char * overlap_safe_w16ncpy(wd16char * pszDst, const wd16char * pszSrc, strsize srclen)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, srclen * sizeof(wd16char)))
      {

         memmove(pszDst, pszSrc, srclen * sizeof(wd16char));

      }
      else
      {

         wd16_ncpy(pszDst, pszSrc, srclen);

      }


   }

   return pszDst;

}



inline strsize __wd16len(const wd16char * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}


inline wd16char * __wd16cat(wd16char * pszTarget, const wd16char * pszConcat)
{

   __wd16cpy(pszTarget + wd16_len(pszTarget), pszConcat);

   return pszTarget;

}


inline wd16char * __wd16cpy(wd16char * pszDst, const wd16char * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}




inline wd16char * __wd16ncpy(wd16char * pszDst, const wd16char * psz, strsize len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}




inline const wd16char * __wd16chr(const wd16char * psz, wd16char ch)
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



inline wd16char * __wd16pbrk(wd16char * psz, const wd16char * pszFind)
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



inline wd16char * __wd16tok_r(wd16char * psz, const wd16char * sep, wd16char ** state)
{

   if (!psz)
   {

      psz = *state;

      if (!psz)
      {

         return nullptr;

      }

   }

   auto p = wd16_pbrk(psz, sep);

   if (p)
   {

      *p = (wd16char)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}




inline const wd16char * __wd16rchr(const wd16char * psz, wd16char ch)
{

   auto p = psz + __wd16len(psz) - 1;

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



inline int __wd16cmp(const wd16char * psz1, const wd16char * psz2)
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



inline int __wd16ncmp(const wd16char * psz1, const wd16char * psz2, size_t s)
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




inline const wd16char * __wd16str(const wd16char * psz, const wd16char * pszFind)
{

   auto lenFind = __wd16len(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = __wd16chr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (__wd16ncmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = __wd16chr(psz, *pszFind);

   } while (p);

   return nullptr;

}


inline wd16char __wd16tolower(wd16char ch)
{

   return (ch >= (wd16char)L'A' && ch <= (wd16char)L'Z') ? (ch - (wd16char)L'A') + (wd16char)L'a' : ch;

}

inline wd16char __wd16toupper(wd16char ch)
{

   return (ch >= (wd16char)L'a' && ch <= (wd16char)L'z') ? (ch - (wd16char)L'a') + (wd16char)L'A' : ch;

}


inline wd16char * __wd16lwr(wd16char * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd16_tolower(*p);

      p++;

   }

   return psz;

}


inline wd16char * __wd16lwr_s(wd16char * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = wd16_tolower(*p);

      p++;

      s--;

   }

   return psz;

}


inline wd16char * __wd16upr(wd16char * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd16_toupper(*p);

      p++;

   }

   return psz;

}


inline wd16char * __wd16upr_s(wd16char * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = wd16_toupper(*p);

      p++;

      s--;

   }

   return psz;

}

inline const wd16char * __wd16ichr(const wd16char * psz, wd16char ch)
{

   ch = wd16_tolower(ch);

   while (*psz)
   {

      if (wd16_tolower(*psz) == ch)
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}







inline int __wd16icmp(const wd16char * psz1, const wd16char * psz2)
{

   int iCompare = 0;

   while (*psz1 && *psz2)
   {

      iCompare = wd16_tolower(*psz1) - wd16_tolower(*psz2);

      psz1++;

      psz2++;

   }

   return iCompare;

}


inline int __wd16nicmp(const wd16char * psz1, const wd16char * psz2, size_t s)
{

   int iCompare = 0;

   while (*psz1 && *psz2 && s > 0)
   {

      iCompare = wd16_tolower(*psz1) - wd16_tolower(*psz2);

      psz1++;

      psz2++;

      s--;

   }

   return iCompare;

}




inline const wd16char * __wd16istr(const wd16char * psz, const wd16char * pszFind)
{

   auto lenFind = wd16_len(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = wd16_ichr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (wd16_nicmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = wd16_ichr(psz, *pszFind);

   } while (p);

   return nullptr;

}

inline int __wd16coll(const wd16char * psz1, const wd16char * psz2) { return wd16_cmp(psz1, psz2); }

inline int __wd16ncoll(const wd16char * psz1, const wd16char * psz2, size_t s) { return wd16_ncmp(psz1, psz2, s); }

inline int __wd16icoll(const wd16char * psz1, const wd16char * psz2) { return wd16_icmp(psz1, psz2); }

inline int __wd16nicoll(const wd16char * psz1, const wd16char * psz2, size_t s) { return wd16_nicmp(psz1, psz2, s); }


inline strsize __wd16spn(const wd16char * psz1, const wd16char * psz2)
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


inline strsize __wd16cspn(const wd16char * psz1, const wd16char * psz2)
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





