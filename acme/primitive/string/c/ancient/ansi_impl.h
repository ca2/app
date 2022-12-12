





inline ::ansi_character __ansicharlowered(i32 i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
inline ::ansi_character __ansicharuppered(i32 i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
inline i32 __ansicharisdigit(i32 i) { return i >= L'0' && i <= L'9'; }
inline i32 __ansicharisalpha(i32 i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
inline i32 __ansicharisalnum(i32 i) { return ansi_char_isalpha(i) || ansi_char_isdigit(i); }
inline i32 __ansicharisspace(i32 ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }


inline i32 __ansicharishexadecimal(i32 i) { return ansi_char_isdigit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }


inline ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const ::ansi_character * pszSrc, strsize srclen)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, srclen * sizeof(::ansi_character)))
      {

         memmove(pszDst, pszSrc, srclen * sizeof(::ansi_character));

      }
      else
      {

         strncpy(pszDst, pszSrc, srclen);

      }


   }

   return pszDst;

}



inline strsize __ansilen(const ::ansi_character * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}




inline ::ansi_character * __ansicpy(::ansi_character * pszDst, const ::ansi_character * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}




inline ::ansi_character * __ansincpy(::ansi_character * pszDst, const ::ansi_character * psz, strsize len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}




inline const ::ansi_character * __ansichr(const ::ansi_character * psz, ::ansi_character ch)
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



inline ::ansi_character * __ansipbrk(::ansi_character * psz, const ::ansi_character * pszFind)
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



inline ::ansi_character * __ansitok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state)
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

      *p = (::ansi_character)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}




inline const ::ansi_character * __ansirchr(const ::ansi_character * psz, ::ansi_character ch)
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



inline int __ansicmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
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



inline int __ansincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
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




inline const ::ansi_character * __ansistr(const ::ansi_character * psz, const ::ansi_character * pszFind)
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



inline ::ansi_character __ansitolower(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'A' && ch <= (::ansi_character)L'Z') ? (ch - (::ansi_character)L'A') + (::ansi_character)L'a' : ch;

}


inline ::ansi_character __ansitoupper(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'a' && ch <= (::ansi_character)L'z') ? (ch - (::ansi_character)L'a') + (::ansi_character)L'A' : ch;

}


inline ::ansi_character __ansiisdigit(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'0' && ch <= (::ansi_character)L'9');

}


inline ::ansi_character * __ansilwr(::ansi_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_tolower(*p);

      p++;

   }

   return psz;

}


inline ::ansi_character * __ansilwr_s(::ansi_character * psz, strsize s)
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


inline ::ansi_character * __ansiupr(::ansi_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_toupper(*p);

      p++;

   }

   return psz;

}


inline ::ansi_character * __ansiupr_s(::ansi_character * psz, strsize s)
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


inline const ::ansi_character * __ansiichr(const ::ansi_character * psz, ::ansi_character ch)
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







inline int __ansiicmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


inline int __ansiincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
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




inline const ::ansi_character * __ansiistr(const ::ansi_character * psz, const ::ansi_character * pszFind)
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


inline int __ansicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return __ansicmp(psz1, psz2); }

inline int __ansincoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return __ansincmp(psz1, psz2, s); }

inline int __ansiicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return __ansiicmp(psz1, psz2); }

inline int __ansinicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return __ansiincmp(psz1, psz2, s); }

inline strsize __ansispn(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


inline strsize __ansicspn(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


inline  ::ansi_character lower_char(i32 ch)
{
   if (ch >= 'A' && ch <= 'Z')
   {
      ch = ch - 'A' + 'a';
   }
   return ch;
}


inline ::ansi_character upper_char(i32 ch)
{
   if (ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }
   return ch;
}






inline void make_lower(::ansi_character * psz)
{

   while (*psz)
   {
      *psz = lower_char(*psz);
      psz++;
   }

}


inline void make_upper(::ansi_character * psz)
{

   while (*psz)
   {
      *psz = upper_char(*psz);
      psz++;
   }

}

