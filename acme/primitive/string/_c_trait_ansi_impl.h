





inline ansichar __ansicharlowered(i32 i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
inline ansichar __ansicharuppered(i32 i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
inline i32 __ansicharisdigit(i32 i) { return i >= L'0' && i <= L'9'; }
inline i32 __ansicharishexadecimal(i32 i) { return ansi_char_is_digit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }
inline i32 __ansicharisalphabetic(i32 i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
inline i32 __ansicharisalphanumeric(i32 i) { return ansi_char_is_alphabetic(i) || ansi_char_is_digit(i); }
inline i32 __ansicharisspace(i32 ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }


inline ansichar * overlap_safe_ansincpy(ansichar * pszDst, const ansichar * pszSrc, strsize srclen)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, srclen * sizeof(ansichar)))
      {

         memmove(pszDst, pszSrc, srclen * sizeof(ansichar));

      }
      else
      {

         strncpy(pszDst, pszSrc, srclen);

      }


   }

   return pszDst;

}



inline strsize __ansilen(const ansichar * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}




inline ansichar * __ansicpy(ansichar * pszDst, const ansichar * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}




inline ansichar * __ansincpy(ansichar * pszDst, const ansichar * psz, strsize len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}




inline const ansichar * __ansichr(const ansichar * psz, ansichar ch)
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



inline ansichar * __ansipbrk(ansichar * psz, const ansichar * pszFind)
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



inline ansichar * __ansitok_r(ansichar * psz, const ansichar * sep, ansichar ** state)
{

   if (!psz)
   {

      psz = *state;

      if (!psz)
      {

         return nullptr;

      }

   }

   auto p = strpbrk(psz, sep);

   if (p)
   {

      *p = (ansichar)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}




inline const ansichar * __ansirchr(const ansichar * psz, ansichar ch)
{

   auto p = psz + __ansilen(psz) - 1;

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



inline int __ansicmp(const ansichar * psz1, const ansichar * psz2)
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



inline int __ansincmp(const ansichar * psz1, const ansichar * psz2, size_t s)
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




inline const ansichar * __ansistr(const ansichar * psz, const ansichar * pszFind)
{

   auto lenFind = __ansilen(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = __ansichr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (__ansincmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = __ansichr(psz, *pszFind);

   } while (p);

   return nullptr;

}



inline ansichar __ansitolower(ansichar ch)
{

   return (ch >= (ansichar)L'A' && ch <= (ansichar)L'Z') ? (ch - (ansichar)L'A') + (ansichar)L'a' : ch;

}


inline ansichar __ansitoupper(ansichar ch)
{

   return (ch >= (ansichar)L'a' && ch <= (ansichar)L'z') ? (ch - (ansichar)L'a') + (ansichar)L'A' : ch;

}


inline ansichar __ansiisdigit(ansichar ch)
{

   return (ch >= (ansichar)L'0' && ch <= (ansichar)L'9');

}


inline ansichar * __ansilwr(ansichar * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_tolower(*p);

      p++;

   }

   return psz;

}


inline ansichar * __ansilwr_s(ansichar * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = ansi_tolower(*p);

      p++;

      s--;

   }

   return psz;

}


inline ansichar * __ansiupr(ansichar * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_toupper(*p);

      p++;

   }

   return psz;

}


inline ansichar * __ansiupr_s(ansichar * psz, strsize s)
{

   auto p = psz;

   while (*p && s > 0)
   {

      *p = ansi_toupper(*p);

      p++;

      s--;

   }

   return psz;

}


inline const ansichar * __ansiichr(const ansichar * psz, ansichar ch)
{

   ch = ansi_tolower(ch);

   while (*psz)
   {

      if (ansi_tolower(*psz) == ch)
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}







inline int __ansiicmp(const ansichar * psz1, const ansichar * psz2)
{

   int iCompare = 0;

   while (*psz1 && *psz2)
   {

      iCompare = ansi_tolower(*psz1) - ansi_tolower(*psz2);

      psz1++;

      psz2++;

   }

   return iCompare;

}


inline int __ansiincmp(const ansichar * psz1, const ansichar * psz2, size_t s)
{

   int iCompare = 0;

   while (*psz1 && *psz2 && s > 0)
   {

      iCompare = ansi_tolower(*psz1) - ansi_tolower(*psz2);

      psz1++;

      psz2++;

      s--;

   }

   return iCompare;

}




inline const ansichar * __ansiistr(const ansichar * psz, const ansichar * pszFind)
{

   auto lenFind = ansi_len(pszFind);

   if (lenFind <= 0)
   {

      return psz;

   }

   auto p = ansi_ichr(psz, *pszFind);

   if (lenFind == 1)
   {

      return p;

   }

   do
   {

      if (ansi_nicmp(p + 1, pszFind + 1, lenFind - 1) == 0)
      {

         return p;

      }

      psz++;

      p = ansi_ichr(psz, *pszFind);

   } while (p);

   return nullptr;

}


inline int __ansicoll(const ansichar * psz1, const ansichar * psz2) { return __ansicmp(psz1, psz2); }

inline int __ansincoll(const ansichar * psz1, const ansichar * psz2, size_t s) { return __ansincmp(psz1, psz2, s); }

inline int __ansiicoll(const ansichar * psz1, const ansichar * psz2) { return __ansiicmp(psz1, psz2); }

inline int __ansinicoll(const ansichar * psz1, const ansichar * psz2, size_t s) { return __ansiincmp(psz1, psz2, s); }

inline strsize __ansispn(const ansichar * psz1, const ansichar * psz2)
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


inline strsize __ansicspn(const ansichar * psz1, const ansichar * psz2)
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






