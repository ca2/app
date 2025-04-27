#include "framework.h"
#include <string.h>


CLASS_DECL_ACME ::ansi_character __ansicharlowered(int i) { return i >= 'A' && i <='Z' ? i - 'A' + 'a' : i; }
CLASS_DECL_ACME ::ansi_character __ansicharuppered(int i) { return i >= 'a' && i <='z' ? i - 'a' + 'A' : i; }
CLASS_DECL_ACME int __ansicharisdigit(int i) { return i >= L'0' && i <= L'9'; }
CLASS_DECL_ACME int __ansicharisalpha(int i) { return (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'); }
CLASS_DECL_ACME int __ansicharisalnum(int i) { return ansi_char_isalpha(i) || ansi_char_isdigit(i); }
CLASS_DECL_ACME int __ansicharisspace(int ch) { return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' '; }
CLASS_DECL_ACME int __ansicharisxdigit(int i) { return ansi_char_isdigit(i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'); }


CLASS_DECL_ACME int __ansicharishexadecimal(int i) { return __ansicharisxdigit(i); }


CLASS_DECL_ACME ::ansi_character * overlap_safe_ansincpy(::ansi_character * pszDst, const ::ansi_character * pszSrc, character_count len)
{

   if (pszDst != pszSrc)
   {

      if (address_overlaps(pszDst, pszSrc, len))
      {

         memory_transfer(pszDst, pszSrc, len);

      }
      else
      {

         ansi_ncpy(pszDst, pszSrc, len);

      }


   }

   return pszDst;

}



CLASS_DECL_ACME character_count __ansilen(const ::ansi_character * psz)
{

   auto pszStart = psz;

   while (*psz) psz++;

   return psz - pszStart;

}




CLASS_DECL_ACME ::ansi_character * __ansicpy(::ansi_character * pszDst, const ::ansi_character * pszSrc)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *pszSrc++; } while (*pszSrc);

   return pszStart;

}




CLASS_DECL_ACME ::ansi_character * __ansincpy(::ansi_character * pszDst, const ::ansi_character * psz, character_count len)
{

   auto pszStart = pszDst;

   do { *pszDst++ = *psz++; len--; } while (*psz && len >= 0);

   while (len > 0) { *pszDst++ = *psz++; len--; };

   return pszStart;

}




CLASS_DECL_ACME const ::ansi_character * __ansichr(const ::ansi_character * psz, ::ansi_character ch)
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



CLASS_DECL_ACME ::ansi_character * __ansipbrk(::ansi_character * psz, const ::ansi_character * pszFind)
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



CLASS_DECL_ACME ::ansi_character * __ansitok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state);




CLASS_DECL_ACME const ::ansi_character * __ansirchr(const ::ansi_character * psz, ::ansi_character ch)
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



CLASS_DECL_ACME int __ansicmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
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



CLASS_DECL_ACME int __ansincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s)
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




CLASS_DECL_ACME const ::ansi_character * __ansistr(const ::ansi_character * psz, const ::ansi_character * pszFind)
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



CLASS_DECL_ACME ::ansi_character __ansitolower(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'A' && ch <= (::ansi_character)L'Z') ? (ch - (::ansi_character)L'A') + (::ansi_character)L'a' : ch;

}


CLASS_DECL_ACME ::ansi_character __ansitoupper(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'a' && ch <= (::ansi_character)L'z') ? (ch - (::ansi_character)L'a') + (::ansi_character)L'A' : ch;

}


CLASS_DECL_ACME ::ansi_character __ansiisdigit(::ansi_character ch)
{

   return (ch >= (::ansi_character)L'0' && ch <= (::ansi_character)L'9');

}


CLASS_DECL_ACME ::ansi_character * __ansilwr(::ansi_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_tolower(*p);

      p++;

   }

   return psz;

}


CLASS_DECL_ACME ::ansi_character * __ansilwr_s(::ansi_character * psz, character_count s)
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


CLASS_DECL_ACME ::ansi_character * __ansiupr(::ansi_character * psz)
{

   auto p = psz;

   while (*p)
   {

      *p = ansi_toupper(*p);

      p++;

   }

   return psz;

}


CLASS_DECL_ACME ::ansi_character * __ansiupr_s(::ansi_character * psz, character_count s)
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


CLASS_DECL_ACME const ::ansi_character * __ansiichr(const ::ansi_character * psz, ::ansi_character ch)
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







CLASS_DECL_ACME int __ansiicmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


CLASS_DECL_ACME int __ansiincmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s)
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




CLASS_DECL_ACME const ::ansi_character * __ansiistr(const ::ansi_character * psz, const ::ansi_character * pszFind)
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


CLASS_DECL_ACME int __ansicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return __ansicmp(psz1, psz2); }

CLASS_DECL_ACME int __ansincoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s) { return __ansincmp(psz1, psz2, s); }

CLASS_DECL_ACME int __ansiicoll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return __ansiicmp(psz1, psz2); }

CLASS_DECL_ACME int __ansinicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s) { return __ansiincmp(psz1, psz2, s); }

CLASS_DECL_ACME character_count __ansispn(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


CLASS_DECL_ACME character_count __ansicspn(const ::ansi_character * psz1, const ::ansi_character * psz2)
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


CLASS_DECL_ACME  ::ansi_character lower_char(int ch)
{
   if (ch >= 'A' && ch <= 'Z')
   {
      ch = ch - 'A' + 'a';
   }
   return ch;
}


CLASS_DECL_ACME ::ansi_character upper_char(int ch)
{
   if (ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }
   return ch;
}






CLASS_DECL_ACME void make_lower(::ansi_character * psz)
{

   while (*psz)
   {
      *psz = lower_char(*psz);
      psz++;
   }

}


CLASS_DECL_ACME void make_upper(::ansi_character * psz)
{

   while (*psz)
   {
      *psz = upper_char(*psz);
      psz++;
   }

}



