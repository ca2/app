#include "framework.h"
#include "apex/astr.h"


url_domain_axis::url_domain_axis()
{

   m_pszRadix     = nullptr;
   m_iLenRadix    = 0;
   m_pszSuffix    = nullptr;
   m_iLenSuffix   = 0;
   m_pszDomain    = nullptr;
   m_iLenDomain   = 0;
   m_pszPrefix    = nullptr;
   m_iLenPrefix   = 0;
   m_pszTopLevel  = nullptr;
   m_iLenTopLevel = 0;
   m_pszName      = nullptr;
   m_iLenName     = 0;

   m_iCount       = 0;
   m_bHasWww      = false;

}


void url_domain_axis::create(const char * pszServerName)
{

   m_strOriginalName = pszServerName;
   if(m_strOriginalName.is_empty())
      return;
   const char * psz = m_strOriginalName;
   m_iCount = 1;
   while(*psz != '\0')
   {
      if(*psz == '.')
         m_iCount++;
      psz++;
   }
   psz = m_strOriginalName;
   m_bHasWww = ::str::begins(pszServerName, astr.WwwDot);
   if(m_bHasWww)
   {
      psz += 4;
      m_iCount--;
   }
   const char * pszEnd = ((const char *) m_strOriginalName) + m_strOriginalName.get_length();
   m_pszTopLevel = pszEnd;
   while(m_pszTopLevel > psz && *m_pszTopLevel != '.')
   {
      m_pszTopLevel--;
      m_iLenTopLevel++;
   }
   if(*m_pszTopLevel == '.')
   {
      m_pszTopLevel++;
      m_iLenTopLevel--;
   }
   else
   {
      m_pszTopLevel     = nullptr;
      m_iLenTopLevel    = 0;
      m_pszRadix        = psz;
      m_iLenRadix       = m_strOriginalName.get_length();
      m_pszDomain       = psz;
      m_iLenDomain      = m_strOriginalName.get_length();
      m_pszName         = psz;
      m_iLenName        = m_strOriginalName.get_length();
      return;
   }
   if(m_iCount == 2)
   {
      m_pszSuffix       = m_pszTopLevel;
      m_iLenSuffix      = m_iLenTopLevel;
      m_pszRadix        = psz;
      m_iLenRadix       = (m_pszTopLevel - 1) - psz;
      m_pszDomain       = m_pszRadix;
      m_iLenDomain      = m_iLenRadix + 1 + m_iLenTopLevel;
      m_pszName         = m_pszDomain;
      m_iLenName        = m_iLenDomain;
      return;
   }
   const char * pszPreTopLevel = m_pszTopLevel - 2;
   i32 iLenPreTopLevel = 0;
   while(pszPreTopLevel > psz && *pszPreTopLevel != '.')
   {
      pszPreTopLevel--;
      iLenPreTopLevel++;
   }
   if(*pszPreTopLevel == '.')
   {
      pszPreTopLevel++;
   }
   else
   {
      __throw(::exception::exception("not_expected"));
   }
   const char * pszPreTopLevel2 = nullptr;
   i32 iLenPreTopLevel2 = 0;
   const char * pszPreTopLevel3 = nullptr;
   //      i32 iLenPreTopLevel3 = 0;
   if(m_iCount >= 4)
   {
      pszPreTopLevel2 = pszPreTopLevel - 2;
      while(pszPreTopLevel2 > psz && *pszPreTopLevel2 != '.')
      {
         pszPreTopLevel2--;
         iLenPreTopLevel2++;
      }
      if(*pszPreTopLevel2 == '.')
      {
         pszPreTopLevel2++;
      }
      else
      {
         __throw(::exception::exception("not_expected"));
      }
      if(m_iCount >= 5)
      {
         pszPreTopLevel3 = pszPreTopLevel2 - 2;
         while(pszPreTopLevel3 > psz && *pszPreTopLevel3 != '.')
         {
            pszPreTopLevel3--;
            iLenPreTopLevel2++;
         }
         if(*pszPreTopLevel3 == '.')
         {
            pszPreTopLevel3++;
         }
         else
         {
            __throw(::exception::exception("not_expected"));
         }
      }
   }
   if(m_iLenTopLevel == 2
      && m_pszTopLevel[0] == 'b'
      && m_pszTopLevel[1] == 'r'
      && iLenPreTopLevel == 3
      && pszPreTopLevel[0] == 'n'
      && pszPreTopLevel[1] == 'o'
      && pszPreTopLevel[2] == 'm'
      )
   {
      m_pszSuffix       = pszPreTopLevel;
      m_iLenSuffix      = pszEnd - pszPreTopLevel;
      if(m_iCount <= 4)
      {
         m_pszRadix     = psz;
         m_iLenRadix    = (pszPreTopLevel - 1) - psz;
      }
      else
      {
         m_pszRadix     = pszPreTopLevel3;
         m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel3;
         m_pszPrefix    = psz;
         m_iLenPrefix   = (pszPreTopLevel3 - 1) - psz;
      }
   }
   else if(m_iLenTopLevel == 2
      && m_pszTopLevel[0] == 'a'
      && m_pszTopLevel[1] == 'm'
      && iLenPreTopLevel == 5
      && ((pszPreTopLevel[0] == 'n'
      &&   pszPreTopLevel[2] == 'r') ||
      (pszPreTopLevel[0] == 's'
      &&   pszPreTopLevel[2] == 'u'))
      && pszPreTopLevel[1] == 'o'
      && pszPreTopLevel[3] == 't'
      && pszPreTopLevel[4] == 'h'
      )
   {
      m_pszSuffix       = pszPreTopLevel;
      m_iLenSuffix      = pszEnd - pszPreTopLevel;
      m_pszTopLevel     = pszPreTopLevel;
      m_iLenTopLevel    = pszEnd - pszPreTopLevel;
      if(m_iCount <= 3)
      {
         m_pszRadix     = psz;
         m_iLenRadix    = (pszPreTopLevel - 1) - psz;
         m_pszName      = m_pszRadix;
         m_iLenName     = pszEnd - m_pszName;
      }
      else
      {
         m_pszRadix     = pszPreTopLevel2;
         m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel2;
         m_pszPrefix    = psz;
         m_iLenPrefix   = (pszPreTopLevel2 - 1) - psz;
         m_pszName      = m_pszPrefix;
         m_iLenName     = pszEnd - m_pszPrefix;
      }
      m_pszDomain       = m_pszRadix;
      m_iLenDomain      = pszEnd - m_pszDomain;
      return;
   }
   else if(server_is_top_domain(m_pszTopLevel, m_iLenTopLevel, pszPreTopLevel, iLenPreTopLevel))
   {
      m_pszSuffix       = pszPreTopLevel;
      m_iLenSuffix      = pszEnd - pszPreTopLevel;
      if(m_iCount <= 3)
      {
         m_pszRadix     = psz;
         m_iLenRadix    = (pszPreTopLevel - 1) - psz;
      }
      else
      {
         m_pszRadix     = pszPreTopLevel2;
         m_iLenRadix    = (pszPreTopLevel - 1) - pszPreTopLevel2;
         m_pszPrefix    = psz;
         m_iLenPrefix   = (pszPreTopLevel2 - 1) - psz;
      }
   }
   else
   {
      m_pszSuffix       = m_pszTopLevel;
      m_iLenSuffix      = m_iLenTopLevel;
      m_pszRadix        = pszPreTopLevel;
      m_iLenRadix       = (m_pszTopLevel - 1) - pszPreTopLevel;
      m_pszPrefix       = psz;
      m_iLenPrefix      = (pszPreTopLevel - 1) - psz;
   }
   m_pszDomain       = m_pszRadix;
   m_iLenDomain      = pszEnd - m_pszDomain;
   if(m_pszPrefix != nullptr)
   {
      m_pszName      = m_pszPrefix;
      m_iLenName     = pszEnd - m_pszPrefix;
   }
   else
   {
      m_pszName      = m_pszDomain;
      m_iLenName     = m_iLenDomain;
   }
}


string url_domain_axis::get_name(const char * pszServerName)
{

   url_domain_axis domainaxis;

   domainaxis.create(pszServerName);

   if(domainaxis.m_pszName != nullptr)
      return string(domainaxis.m_pszName, domainaxis.m_iLenName);
   else
      return "";

}

void url_domain::create(const char * pszServerName)
{

   url_domain_axis::create(pszServerName);

   if(m_pszRadix != nullptr)
   {
      
      m_strRadix.assign(m_pszRadix, m_iLenRadix);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

   if(m_pszSuffix != nullptr)
   {

      m_strSuffix.assign(m_pszSuffix, m_iLenSuffix);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

   if(m_pszDomain != nullptr)
   {

      m_strDomain.assign(m_pszDomain, m_iLenDomain);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

   if(m_pszPrefix != nullptr)
   {

      m_strPrefix.assign(m_pszPrefix, m_iLenPrefix);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

   if(m_pszTopLevel != nullptr)
   {

      m_strTopLevel.assign(m_pszTopLevel, m_iLenTopLevel);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

   if(m_pszName != nullptr)
   {

      m_strName.assign(m_pszName, m_iLenName);

      m_strTextRadix = ::url::department::from_punycode(m_strRadix);

   }

}


bool CLASS_DECL_APEX server_is_top_domain(const char * pszTop1, strsize blen, const char * pszTop2, strsize alen)
{
   char a1;
   char a2;
   char a3;
   char a4;
   char b1;
   char b2;
   char b3;
   if(blen >= 1)
   {
      b1 = pszTop1[0];
      if(blen >= 2)
      {
         b2 = pszTop1[1];
         if(blen >= 3)
         {
            b3 = pszTop1[2];
         }
         else
         {
            b3 = '\0';
         }
      }
      else
      {
         b2 = '\0';
         b3 = '\0';
      }
   }
   else
   {
      b1 = '\0';
      b2 = '\0';
      b3 = '\0';
   }
   if(alen >= 1)
   {
      a1 = pszTop2[0];
      if(alen >= 2)
      {
         a2 = pszTop2[1];
         if(alen >= 3)
         {
            a3 = pszTop2[2];
            if(alen >= 4)
            {
               a4 = pszTop2[3];
            }
            else
            {
               a4 = '\0';
            }
         }
         else
         {
            a3 = '\0';
            a4 = '\0';
         }
      }
      else
      {
         a2 = '\0';
         a3 = '\0';
         a4 = '\0';
      }
   }
   else
   {
      a1 = '\0';
      a2 = '\0';
      a3 = '\0';
      a4 = '\0';
   }

   if(alen == 3 && a1 == 'c' && a2 == 'o' && a3 == 'm')
      return true;
   if(alen == 2 && a1 == 'c' && a2 == 'o')
      return true;
   if(blen == 2)
   {
      if(b1 == 'a')
      {
         if(b2 == 'r')
         {
         }
         else if(b2 == 't')
         {
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'b')
      {
        // br
         if(b2 == 'r')
         {
            if(alen == 2)
            {
               if(a1 == 't' && a2 == 'v')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'e')
               {
                  if(a2 == 'c' && a3 == 'o')
                  {
                     return true;
                  }
                  else if(a2 == 'm' && a3 == 'p')
                  {
                     return true;
                  }
                  else if(a2 == 'n' && a3 == 'g')
                  {
                     return true;
                  }
                  else if(a2 == 't' && a3 == 'c')
                  {
                     return true;
                  }
               }
               else if(a1 == 'i')
               {
                  if(a2 == 'n')
                  {
                     if(a3 == 'd')
                     {
                        return true;
                     }
                     else if(a3 == 'f')
                     {
                        return true;
                     }
                  }
               }
               else if(a1 == 'm')
               {
                  if(a2 == 'u' && a3 == 's')
                  {
                     return true;
                  }
                  else if(a2 == 'e' && a3 == 'd')
                  {
                     return true;
                  }
               }
               else if(a1 == 'n')
               {
                  if(a2 == 'e' && a3 == 't')
                  {
                     return true;
                  }
                  else if(a2 == 'o' && a3 == 'm')
                  {
                     return true;
                  }
               }
               else if(a1 == 'p' && a2 == 'r' && a3 == 'o')
               {
                  return true;
               }
               else if(a1 == 's')
               {
                  if(a2 == 'r' && a3 == 'v')
                  {
                     return true;
                  }
               }
            }
            else if(alen == 4)
            {
               if(a2 == 'l' && a3 == 'o' && a4 == 'g')
               {
                  if(a1 == 'b' || a1 == 'f' || a1 == 'v')
                  {
                     return true;
                  }
               }
               else if(a1 == 'w' && a2 == 'i' && a3 == 'k' && a4 == 'i')
               {
                  return true;
               }
            }
            else if(alen == 5)
            {
               if(ansi_count_compare(pszTop2, "radio", 5) == 0)
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'c')
      {
         if(b2 == 'c')
         {
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'c')
               {
                  return true;
               }
               else if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'n')
         {
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'o')
         {
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'e')
      {
         if(b2 == 's')
         {
            // es
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'e')
         {
            // ee
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'g')
      {
         if(b2 == 't')
         {
            // gt
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'h')
      {
         if(b2 == 't')
         {
            // ht
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'u')
         {
            // hu
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'i')
      {
         if(b2 == 'l')
         {
            // il
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
         if(b2 == 'n')
         {
            // in
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'g' && a2 == 'e' && a3 == 'n')
               {
                  return true;
               }
               else if(a1 == 'i' && a2 == 'n' && a3 == 'd')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
            else if(alen == 4)
            {
               if(a1 == 'f' && a2 == 'i' && a3 == 'r' && a4 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'j')
      {
         if(b2 == 'p')
         {
            // jp
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
               else if(a1 == 'g' && a2 == 'r')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'l')
      {
         if(b2 == 'v')
         {
            // lv
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'm')
      {
         if(b2 == 'x')
         {
            // mx
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'n')
      {
         if(b2 == 'l')
         {
            // nl
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'z')
         {
            // nz
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'p')
      {
         if(b2 == 't')
         {
            // point_i32
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'l')
         {
            // pl
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
               else if(a1 == 'b' && a2 == 'i' && a3 == 'z')
               {
                  return true;
               }
               else if(a1 == 'w' && a2 == 'a' && a3 == 'w')
               {
                  return true;
               }
            }
            else if(alen == 4)
            {
               if(a1 == 'i' && a2 == 'n' && a3 == 'f' && a4 == 'o')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'r')
      {
         if(b2 == 'u')
         {
            // ru
            if(alen == 2)
            {
               if(a1 == 'p' && a2 == 'p')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'm' && a2 == 's' && a3 == 'k')
               {
                  return true;
               }
               else if(a1 == 's' && a2 == 'p' && a3 == 'b')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'o' && a3 == 'v')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 's')
      {
         if(b2 == 'o')
         {
            // so
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'u')
         {
            // su
            if(alen == 2)
            {
               if(a1 == 'p' && a2 == 'p')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'm' && a2 == 's' && a3 == 'k')
               {
                  return true;
               }
               else if(a1 == 's' && a2 == 'p' && a3 == 'b')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'o' && a3 == 'v')
               {
                  return true;
               }
               else if(a1 == 'n' && a2 == 'e' && a3 == 't')
               {
                  return true;
               }
               else if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 't')
      {
         if(b2 == 'r')
         {
            // tr
            if(alen == 2)
            {
               if(a1 == 't' && a2 == 'v')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
               else if(a1 == 'w' && a2 == 'e' && a3 == 'b')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'w')
         {
            // tw
            if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
      }
      else if(b1 == 'u')
      {
         if(b2 == 'a')
         {
            // ua
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'c' && a2 == 'o' && a3 == 'm')
               {
                  return true;
               }
            }
         }
         else if(b2 == 'k')
         {
            // uk
            if(alen == 2)
            {
               if(a1 == 'c' && a2 == 'o')
               {
                  return true;
               }
               else if(a1 == 'm' && a2 == 'e')
               {
                  return true;
               }
            }
            else if(alen == 3)
            {
               if(a1 == 'o' && a2 == 'r' && a3 == 'g')
               {
                  return true;
               }
            }
         }
      }
   }
   else if(blen == 3)
   {
      if(b1 == 'c')
      {
         if(b2 == 'o')
         {
            if(b3 == 'm')
            {
               if(alen == 2)
               {
                  /*                  || strTop2 == "de"
                  || strTop2 == "eu"
                  || strTop2 == "uk"
                  */
                  return true;
               }
               else if(alen == 4)
               {
                  if(a1 == 'a' && a2 == 's' && a3 == 'i' && a4 == 'a')
                  {
                     return true;
                  }
               }
            }
         }
      }
   }
   else if(blen == 10)
   {
        if(ansi_count_compare(pszTop1, "xn--fiqs8s", 10))
        {
            return true;
        }
   }
   return false;
}

/*      bool url_domain_in(string str, string url)
{
i32 iPos = url.reverse_find('.');
if(iPos < 0)
return false;
i32 iLen = str.get_length();
if(url.get_length() < iLen + 1)
return false;
if(url[iLen] != '.')
return false;
if(iPos == 0)
return true;
if(url[iPos - 1] == '.')
return true;
else
return false;
}

void url_domain_prefix(string suffix, string url, string & prefix)
{
i32 iLen = url.get_length();
i32 iSufLen = suffix.get_length();
if(iLen < iSufLen)
return false;
i32 iPos = iLen - iSufLen;
if(strsubstr($str, $pos) != $suffix)
return false;
if($pos == 0)
return true;
if($pos == 1)
return false;
if($url[$pos - 1] != '.')
return false;
$prefix = substr($url, 0, $pos - 1);
return true;
}*/




