#include "framework.h"


CLASS_DECL_ACID ::wd16_character __wd16charlowered(i32 i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
CLASS_DECL_ACID ::wd16_character __wd16charuppered(i32 i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
CLASS_DECL_ACID i32 __wd16charisdigit(i32 i) { return i >= L'0' && i <= L'9'; }
CLASS_DECL_ACID i32 __wd16charisalpha(i32 i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
CLASS_DECL_ACID i32 __wd16charisalnum(i32 i) { return wd16_char_isalpha(i) || wd16_char_isdigit(i); }
CLASS_DECL_ACID i32 __wd16charisspace(i32 ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }


CLASS_DECL_ACID i32 __wd16charisxdigit(i32 i) { return wd16_char_isdigit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }


CLASS_DECL_ACID ::wd16_character * overlap_safe_wd16ncpy(::wd16_character * pszDst, const ::wd16_character * pszSrc, strsize srclen)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, srclen * sizeof(::wd16_character)))
      {

         memory_transfer(pszDst, pszSrc, srclen * sizeof(::wd16_character));

      }
      else
      {

         wd16_ncpy(pszDst, pszSrc, srclen);

      }


   }

   return pszDst;

}



CLASS_DECL_ACID strsize __wd16len(const ::wd16_character * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}


CLASS_DECL_ACID ::wd16_character * __wd16cat(::wd16_character * pszTarget, const ::wd16_character * pszConcat)
{

   __wd16cpy(pszTarget + wd16_len(pszTarget), pszConcat);

   return pszTarget;

}


CLASS_DECL_ACID ::wd16_character * __wd16cpy(::wd16_character * pszDst, const ::wd16_character * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}




CLASS_DECL_ACID ::wd16_character * __wd16ncpy(::wd16_character * pszDst, const ::wd16_character * psz, strsize len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}




CLASS_DECL_ACID const ::wd16_character * __wd16chr(const ::wd16_character * psz, ::wd16_character ch)
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



CLASS_DECL_ACID ::wd16_character * __wd16pbrk(::wd16_character * psz, const ::wd16_character * pszFind)
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



CLASS_DECL_ACID ::wd16_character * __wd16tok_r(::wd16_character * psz, const ::wd16_character * sep, ::wd16_character ** state)
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

      *p = (::wd16_character)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}




CLASS_DECL_ACID const ::wd16_character * __wd16rchr(const ::wd16_character * psz, ::wd16_character ch)
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



CLASS_DECL_ACID int __wd16cmp(const ::wd16_character * psz1, const ::wd16_character * psz2)
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



CLASS_DECL_ACID int __wd16ncmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s)
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




CLASS_DECL_ACID const ::wd16_character * __wd16str(const ::wd16_character * psz, const ::wd16_character * pszFind)
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


CLASS_DECL_ACID ::wd16_character __wd16tolower(::wd16_character ch)
{

   return (ch >= (::wd16_character)L'A' && ch <= (::wd16_character)L'Z') ? (ch - (::wd16_character)L'A') + (::wd16_character)L'a' : ch;

}

CLASS_DECL_ACID ::wd16_character __wd16toupper(::wd16_character ch)
{

   return (ch >= (::wd16_character)L'a' && ch <= (::wd16_character)L'z') ? (ch - (::wd16_character)L'a') + (::wd16_character)L'A' : ch;

}


CLASS_DECL_ACID ::wd16_character * __wd16lwr(::wd16_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd16_tolower(*p);

      p++;

   }

   return psz;

}


CLASS_DECL_ACID ::wd16_character * __wd16lwr_s(::wd16_character * psz, strsize s)
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


CLASS_DECL_ACID ::wd16_character * __wd16upr(::wd16_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = wd16_toupper(*p);

      p++;

   }

   return psz;

}


CLASS_DECL_ACID ::wd16_character * __wd16upr_s(::wd16_character * psz, strsize s)
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

CLASS_DECL_ACID const ::wd16_character * __wd16ichr(const ::wd16_character * psz, ::wd16_character ch)
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







CLASS_DECL_ACID int __wd16icmp(const ::wd16_character * psz1, const ::wd16_character * psz2)
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


CLASS_DECL_ACID int __wd16nicmp(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s)
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




CLASS_DECL_ACID const ::wd16_character * __wd16istr(const ::wd16_character * psz, const ::wd16_character * pszFind)
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

CLASS_DECL_ACID int __wd16coll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wd16_cmp(psz1, psz2); }

CLASS_DECL_ACID int __wd16ncoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return wd16_ncmp(psz1, psz2, s); }

CLASS_DECL_ACID int __wd16icoll(const ::wd16_character * psz1, const ::wd16_character * psz2) { return wd16_icmp(psz1, psz2); }

CLASS_DECL_ACID int __wd16nicoll(const ::wd16_character * psz1, const ::wd16_character * psz2, strsize s) { return wd16_nicmp(psz1, psz2, s); }


CLASS_DECL_ACID strsize __wd16spn(const ::wd16_character * psz1, const ::wd16_character * psz2)
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


CLASS_DECL_ACID strsize __wd16cspn(const ::wd16_character * psz1, const ::wd16_character * psz2)
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







CLASS_DECL_ACID strsize wd16_to_ansi_char_len(::wd16_character wch) { return utf_to_utf_length((char *)nullptr, &wch, 1); }
CLASS_DECL_ACID void wd16_to_ansi_char(char * psz, ::wd16_character wch) { utf_to_utf(psz, &wch, 1); }



CLASS_DECL_ACID void make_upper(::wd16_character * psz)
{

   while (*psz)
   {
      *psz = upper_char(*psz);
      psz++;
   }

}

