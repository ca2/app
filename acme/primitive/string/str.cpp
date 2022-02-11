#include "framework.h"
#include <stdio.h>


namespace hex
{


   u16 parse_u16_exc(const char * & psz, const char * pszEnd)
   {
      string strUni;
      const char * pszNext = psz;
      for (index i = 0; i < 4; i++)
      {
         psz = pszNext;
         pszNext = ::str::__utf8_inc(psz);
         if (pszNext > pszEnd)
         {
            throw ::exception(error_parsing, "hexadecimal digit expected, premature end");
            return -1;
         }
         if ((pszNext - psz == 1) && ((*psz >= '0' && *psz <= '9') || (*psz >= 'A' && *psz <= 'F') || (*psz >= 'a' && *psz <= 'f')))
         {
            strUni += *psz;
         }
         else
         {
            throw ::exception(error_parsing, "hexadecimal digit expect expected here");
            return -1;
         }
      }
      psz = pszNext;
      return ::hex::to_u32(strUni);

   }

}

#ifdef LINUX
////#include <ctype.h>
#endif
//bool is_high_surrogate(u16 u)
//{
//   return u >= 0xD800 && u <= 0xDBFF;
//
//}
//bool is_low_surrogate(u16 u)
//{
//   return u >= 0xDC00 && u <= 0xDFFF;
//}
//CLASS_DECL_ACME bool is_surrogated(u32 character)
//{
//   return 0x10000 <= character && character <= 0x10FFFF;
//}
CLASS_DECL_ACME void
encode_utf16_pair(u32 character, u16 *units)
{
   unsigned int code;
   ASSERT(utf32_is_surrogated(character));
   code = (character - 0x10000);
   units[0] = 0xD800 | (code >> 10);
   units[1] = 0xDC00 | (code & 0x3FF);
}

u32
decode_utf16_pair(u16 *units)
{
   u32 code;
   ASSERT(utf16_is_1st_surrogate(units[0]));
   ASSERT(utf16_is_2nd_surrogate(units[1]));
   code = 0x10000;
   code += (units[0] & 0x03FF) << 10;
   code += (units[1] & 0x03FF);
   return code;
}
namespace str
{

   CLASS_DECL_ACME e_err g_eerr = err_none;


//    const char trailingBytesForUTF8[256] =
//    {
//       (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//       2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
//    };

   //void          make_lower(char * psz)
   //{

   //   while (*psz)
   //   {
   //      *psz = tolower(*psz);
   //      psz++;
   //   }

   //}


   //void          make_upper(char * psz)
   //{

   //   while (*psz)
   //   {
   //      *psz = toupper(*psz);
   //      psz++;
   //   }

   //}


   i32  compare(const char * psz1, const char * psz2)
   {
      return strcmp(psz1, psz2);
   }

   i32  compare_ci(const char * psz1, const char * psz2)
   {
      return ansi_compare_ci(psz1, psz2);
   }

   bool equals(const char * psz1, const char * psz2)
   {
      return compare(psz1, psz2) == 0;
   }

   bool equals_ci(const char * psz1, const char * psz2)
   {
      return compare_ci(psz1, psz2) == 0;
   }

   string  equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   string  equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {

      return equals_ci(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;

   }


   bool begins(const char * pcsz, const char * pcszPrefix)
   {

      if(pcsz == nullptr || *pcsz == '\0')
      {

         if(pcszPrefix == nullptr || *pcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*pcsz == *pcszPrefix)

      {
         pcsz++;

         pcszPrefix++;

         if(*pcsz == '\0')

         {
            if(*pcszPrefix == '\0')

               return true;
            else
               return false;
         }
         else if(*pcszPrefix == '\0')

         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const char * pcsz, const char * pcszPrefix)

   {
      return begins(pcsz, pcszPrefix);

   }

   bool begins(const ::string & str, const char * pcszPrefix)

   {
      if(str.is_empty())
      {
         if(pcszPrefix == nullptr || *pcszPrefix == '\0')

         {
            return true;
         }
         else
         {
            return false;
         }
      }
      const char * pcsz = str;

      while(*pcsz == *pcszPrefix)

      {
         pcsz++;

         pcszPrefix++;

         if(*pcsz == '\0')

         {
            if(*pcszPrefix == '\0')

               return true;
            else
               return false;
         }
         else if(*pcszPrefix == '\0')

         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const ::string & str, const char * pcszPrefix)

   {
      return begins(str, pcszPrefix);

   }

   bool begins_ci(const char * pcsz, const char * pcszPrefix)

   {
      if(pcsz == nullptr || *pcsz == '\0')

      {
         if(pcszPrefix == nullptr || *pcszPrefix == '\0')

         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(tolower((ansichar) *pcsz) == tolower((ansichar)*pcszPrefix))

      {
         pcsz++;

         pcszPrefix++;

         if(*pcsz == '\0')

         {
            if(*pcszPrefix == '\0')

               return true;
            else
               return false;
         }
         else if(*pcszPrefix == '\0')

         {
            return true;
         }
      }
      return false;
   }


   bool begins_ci(const widechar * pcwsz, const widechar * pcwszPrefix)
   {

      if (pcwsz == nullptr || *pcwsz == '\0')
      {

         if (pcwszPrefix == nullptr || *pcwszPrefix == '\0')
         {

            return true;

         }
         else
         {

            return false;

         }

      }

      while (tolower(*pcwsz) == tolower(*pcwszPrefix))
      {
         pcwsz++;

         pcwszPrefix++;

         if (*pcwsz == '\0')
         {

            if (*pcwszPrefix == '\0')
            {

               return true;

            }
            else
            {

               return false;

            }

         }
         else if (*pcwszPrefix == '\0')
         {

            return true;

         }

      }

      return false;

   }


   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const char * pcsz, const char * pcszPrefix)
   {

      if(pcsz == nullptr || *pcsz == '\0')
      {

         if(pcszPrefix == nullptr || *pcszPrefix == '\0')
         {

            return true;

         }
         else
         {

            return false;

         }

      }
      while(*pcsz && ansi_char_is_space(*pcsz))

      pcsz++;

      if (!*pcsz)
      {

         return false;

      }

      while(ansi_char_lowered(*pcsz) == ansi_char_lowered(*pcszPrefix))
      {

         pcsz++;

         pcszPrefix++;

         if(*pcsz == '\0')
         {

            if (*pcszPrefix == '\0')
            {

               return true;

            }
            else
            {

               return false;

            }

         }
         else if(*pcszPrefix == '\0')
         {

            return true;

         }

      }

      return false;

   }


   bool begins_ci_iws(const ::string & str, const char * pcszPrefix)

   {
      return begins_ci_iws(str.c_str(), pcszPrefix);

   }


   bool eat_before(string & strBefore, const string & strSeparator, string & str, bool bEatEverythingIfNotFound)
   {

      ASSERT(&str != &strBefore);

      if (&str == &strBefore)
      {

         return false;

      }

      index iFind = str.find(strSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            strBefore = str;

            str.Empty();

         }

         return false;

      }

      strBefore = str.Left(iFind);

      str = str.Mid(iFind + strSeparator.length());

      return true;

   }


   bool eat_before_let_separator(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound)
   {

      ASSERT(&str != &strBefore);

      if (&str == &strBefore)
      {

         return false;

      }

      index iFind = str.find(strSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            strBefore = str;

            str = strSeparator;

         }

         return false;

      }

      strBefore = str.Left(iFind);

      str = str.Mid(iFind);

      return true;

   }


   bool eat_before(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound)
   {

      ASSERT(&wstr != &wstrBefore);

      if (&wstr == &wstrBefore)
      {

         return false;

      }

      index iFind = wstr.find(wstrSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            wstrBefore = wstr;

            wstr.Empty();

         }

         return false;

      }

      wstrBefore = wstr.Left(iFind);

      wstr = wstr.Mid(iFind + wstrSeparator.length());

      return true;

   }


   bool eat_before_let_separator(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound)
   {

      ASSERT(&wstr != &wstrBefore);

      if (&wstr == &wstrBefore)
      {

         return false;

      }

      index iFind = wstr.find(wstrSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            wstrBefore = wstr;

            wstr = wstrSeparator;

         }

         return false;

      }

      wstrBefore = wstr.Left(iFind);

      wstr = wstr.Mid(iFind);

      return true;

   }


//   bool begins_eat(string & str, const char * pcszPrefix)
//
//   {
//
//      string strPrefix(pcszPrefix);
//
//
//      strsize iLen = strPrefix.get_length();
//
//      if(str.Left(iLen) == pcszPrefix)
//
//      {
//         str = str.Mid(iLen);
//         return true;
//      }
//
//      return false;
//
//   }

//   bool begins_eat_ci(string & str, const char * pcszPrefix)
//
//   {
//
//      if(pcszPrefix == nullptr)
//
//         return true;
//
//      string strPrefix(pcszPrefix);
//
//
//      strsize iLen = strPrefix.get_length();
//
//      if(str.Left(iLen).compare_ci(pcszPrefix) == 0)
//
//      {
//         str = str.Mid(iLen);
//         return true;
//      }
//
//      return false;
//
//   }

//   bool begins_eat_ci(string & str, const char * pcszPrefix, const char * pszSeparator)
//   {
//
//      if(str.compare_ci(pcszPrefix) == 0)
//      {
//
//
//         str.Empty();
//         return true;
//      }
//      else
//      {
//         return begins_eat_ci(str, string(pcszPrefix) + pszSeparator);
//
//      }
//   }

   //bool ends(const char * pcsz, const char * pcszSuffix)

   //{
   //   if(pcsz == nullptr || *pcsz == '\0')

   //   {
   //      if(pcszSuffix == nullptr || *pcszSuffix == '\0')

   //         return true;
   //      else
   //         return false;
   //   }
   //   else if(pcszSuffix == nullptr || *pcszSuffix == '\0')

   //   {
   //      return true;
   //   }
   //   const char * pcszEnd = pcsz;

   //   const char * pcszSuffixEnd = pcszSuffix;

   //   while(*pcszEnd)

   //      pcszEnd++;

   //   while(*pcszSuffixEnd)

   //      pcszSuffixEnd++;

   //   if((pcszSuffixEnd - pcszSuffix) > (pcszEnd - pcsz))

   //      return false;
   //   while(pcszSuffixEnd[-1] == pcszEnd[-1])

   //   {
   //      pcszSuffixEnd--;

   //      pcszEnd--;

   //      if(pcszSuffixEnd <= pcszSuffix)

   //         return true;
   //   }

   //   return false;
   //   /*      string str(pcsz);

   //   string strSuffix(pcszSuffix);

   //   i32 iLen = strSuffix.get_length();
   //   if(str.Right(iLen) == pcszSuffix)

   //   {
   //   return true;
   //   }
   //   return false;*/
   //}

   //bool ends_ci(const char * pcsz, const char * pcszSuffix)

   //{
   //   if(pcsz == nullptr || *pcsz == '\0')

   //   {
   //      if(pcszSuffix == nullptr || *pcszSuffix == '\0')

   //         return true;
   //      else
   //         return false;
   //   }
   //   else if(pcszSuffix == nullptr || *pcszSuffix == '\0')

   //   {
   //      return true;
   //   }
   //   const char * pcszEnd = pcsz;

   //   const char * pcszSuffixEnd = pcszSuffix;

   //   while(*pcszEnd)

   //      pcszEnd++;

   //   while(*pcszSuffixEnd)

   //      pcszSuffixEnd++;

   //   if((pcszSuffixEnd - pcszSuffix) > (pcszEnd - pcsz))

   //      return false;
   //   while(tolower(pcszSuffixEnd[-1]) == tolower(pcszEnd[-1]))

   //   {
   //      pcszSuffixEnd--;

   //      pcszEnd--;

   //      if(pcszSuffixEnd <= pcszSuffix)

   //         return true;
   //   }

   //   return false;

   //}


//   bool ends_ci(const ::string & str, const char * pcszSuffix)
//
//   {
//      if(str.is_empty())
//      {
//         if(pcszSuffix == nullptr || *pcszSuffix == '\0')
//
//            return true;
//         else
//            return false;
//      }
//      else if(pcszSuffix == nullptr || *pcszSuffix == '\0')
//
//      {
//         return true;
//      }
//      const char * pcsz = str;
//
//      const char * pcszEnd = pcsz + str.get_length();
//
//      const char * pcszSuffixEnd = pcszSuffix;
//
//      while(*pcszSuffixEnd)
//
//         pcszSuffixEnd++;
//
//      if((pcszSuffixEnd - pcszSuffix) > (pcszEnd - pcsz))
//
//         return false;
//      while(tolower(pcszSuffixEnd[-1]) == tolower(pcszEnd[-1]))
//
//      {
//         pcszSuffixEnd--;
//
//         pcszEnd--;
//
//         if(pcszSuffixEnd <= pcszSuffix)
//
//            return true;
//      }
//
//      return false;
//
//   }

//   bool ends_ci(const ::payload & payload, const char * pcszSuffix)
//
//   {
//      return ends_ci(payload.get_string(), pcszSuffix);
//
//   }


//   bool ends_eat_ci(string & str, const char * pcszSuffix)
//
//   {
//
//      string strSuffix(pcszSuffix);
//
//
//      strsize iLen = strSuffix.get_length();
//
//      if(str.Right(iLen).compare_ci(pcszSuffix) == 0)
//
//      {
//
//         str = str.Left(str.get_length() - iLen);
//         return true;
//
//      }
//
//      return false;
//
//   }

   void copy(string & str, const char * pcsz, i32 iCount)

   {
      string strCopy(pcsz, iCount);

      str = strCopy;
   }

   
   string replace_with(const char * pszOld, const char * pszNew, const char * psz, strsize iStart)
   {
      
      string str(psz);
      
      str.replace_with(pszOld, pszNew, iStart);

      return str;

   }


   index  find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart)
   {

      index iFind = -1;

      iFound = -1;

      for(index i = 0; i < straSearch.get_count(); i++)
      {

         if(straSearch[i].has_char())
         {

            index iSearch = str.find(straSearch[i], iStart);

            if(iSearch >= 0 && iSearch >= iStart && (iSearch < iFind || iFind < 0))
            {

               iFind = iSearch;
               iFound = i;

            }

         }

      }

      return iFind;

   }


   string  random_replace(::matter * pobject, const string_array & straNew, const string_array & straOld, const char * psz)
   {

      string str(psz);

      index iFind;

      index iFound;

      index iStart = 0;

      while((iFind = find_first(straOld, iFound, str, iStart)) >= 0)
      {

         if(iFind < iStart)
         {

            throw ::exception(error_parsing, "random replace error");

            return "";

         }

         index i = (index) (rand() % straNew.get_size());

         str = str.Left(iFind) + straNew[i] + str.Mid(iFind + straOld[iFound].get_length());

         iFind += straNew[i].get_length();

         iStart = iFind;

      }

      return str;
   }


   ::count utf8_replace_with(string & str, const char * pszNew, const char * pszOld, strsize iStart)
   {

      ::count c = 0;

      index iPos = iStart;

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = utf8_find(pszOld, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszNew);

         if(iFindLen < 0)
            iFindLen = strlen(pszOld);

         str = str.Left(iPos) + pszNew + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

         c++;

      }

      return c;

   }


   string utf8_replace_with(const char * pszNew, const char * pszOld, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = utf8_find(pszOld, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszNew);

         if(iFindLen < 0)
            iFindLen = strlen(pszOld);

         str = str.Left(iPos) + pszNew + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

      }

      return str;
   }


   string replace_with_ci(const char * pszNew, const char * pszOld, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = find_ci(pszOld, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszNew);

         if(iFindLen < 0)
            iFindLen = strlen(pszOld);

         str = str.Left(iPos) + pszNew + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

      }

      return str;
   }


   ::count replace_with_ci_count(const char * pszNew, const char * pszOld, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      ::count c = 0;

      while (true)
      {

         iPos = find_ci(pszOld, str, iPos);

         if (iPos < 0)
            break;

         if (iReplaceLen < 0)
            iReplaceLen = strlen(pszNew);

         if (iFindLen < 0)
            iFindLen = strlen(pszOld);

         str = str.Left(iPos) + pszNew + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

         c++;

      }

      return c;

   }


   index find_ci(const ::string & strFind, const ::string & str, index iStart)
   {

      if(strFind.get_length() > (str.get_length() - iStart))
         return -1;

      string strFindLow(&((const char *)strFind)[0], strFind.get_length()); // avoid optimized read only string copy

      strFindLow.make_lower();

      string strLow(&((const char *)str)[iStart], str.get_length() - iStart); // avoid optimized read only string copy

      strLow.make_lower();

      index iFind = strLow.find(strFindLow);

      if(iFind < 0)
         return -1;

      return iStart + iFind;

   }


   index find_ci(const ::string & strFind, const char * psz, index iStart)
   {

      ::count iFindLen = strFind.get_length();

      ::count iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         ::memcpy_dup(szFind, strFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            ::memcpy_dup(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            const char * pszOld = strstr(sz, szFind);

            if(pszOld == nullptr)
               return -1;

            return iStart + (pszOld - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

            strLow.make_lower();

            psz = strLow;

            const char * pszOld = strstr(psz, szFind);

            if(pszOld == nullptr)
               return -1;

            return iStart + (pszOld - psz);

         }

      }
      else
      {

         string strFindLow(&((const char *)strFind)[0], iFindLen); // avoid optimized read only string copy

         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }


   index find_ci(const char * pszOld, const ::string & str, index iStart)
   {

      ::count iFindLen = strlen(pszOld);

      index iLen = str.get_length() - iStart;

      if (iLen < iFindLen)
      {

         return -1;

      }

      ::i32 len1;
      ::i32 len2;

      const char * psz1 = str;

      psz1 += iStart;

      const char * psz2 = pszOld;

      while(true)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         const char * pszC1 = psz1;
         const char * pszC2 = psz2;

         while(true)
         {

            if(ch::to_lower_case(ch::uni_index_len(pszC1, len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
            {
               pszC1 += len1;
               pszC2 += len2;
               if(*pszC2 == '\0')
               {
                  return psz1 - (const char *) str;
               }
               if(*pszC1 == '\0')
               {
                  return -1;
               }
            }
            else
            {
               ch::uni_index_len(psz1,len1);
               psz1 += len1;
               break;
            }
         }

      }

      return -1;

   }


   index find_ci(const char * pszOld,const ::string & str,index iStart, index iLast)
   {

      ::count iFindLen = strlen(pszOld);

      index iLen = str.get_length() - iStart;

      if(iLast < 0)
         iLast +=iLen;

      ::i32 len1;
      ::i32 len2;

      const char * psz1 = str;
      const char * psz2 = pszOld;

      strsize iPos = 0;

      while(iPos <= iLast)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         const char * pszC1 = psz1;
         const char * pszC2 = psz2;

         while(true)
         {

            if(ch::to_lower_case(ch::uni_index_len(pszC1,len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
            {
               pszC1 += len1;
               pszC2 += len2;
               if(*pszC2 == '\0')
               {
                  return psz1 - (const char *)str;
               }
               if(*pszC1 == '\0')
               {
                  return -1;
               }
            }
            else
            {
               ch::uni_index_len(psz1,len1);
               psz1 += len1;
               iPos += len1;
               break;
            }
         }

      }

      return -1;

   }




   index find_file_extension(const char * pszOld,const ::string & str,index iStart, index iLast)
   {

      if(pszOld == nullptr || pszOld[0] == '\0') // do not search for empty Extensions
         return -1;

      // for dir::name_is (check if base name of a file is a directory, checking if there is a simple ansi '.', may be very good start point_i32 definitive false).
      // if there is a dot, it may still does not have a Latin dot, if the dot is inside a Multibyte UTF8 char, anyway, algo following should check it properly.

      index iLen = str.get_length() - iStart;

      if(iLast < 0)
         iLast += iLen;

      {

         const char * pszOkToContinue = strchr(str,'.');

         if(pszOkToContinue == nullptr || pszOkToContinue - (const char *)str >= iLast)
            return -1;

      }

      ::count iFindLen = strlen(pszOld);



      i32 len1;
      i32 len2;

      const char * psz1 = str;
      const char * psz2 = pszOld;

      strsize iPos = 0;
      strsize iPos2 = 0;

      while(iPos <= iLast)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         if(*psz1 != '.')
         {

            len1 = str_uni_len(psz1);

            psz1 += len1;

            iPos += len1;

         }
         else
         {

            psz1 += 1;

            iPos += 1;

            if(iPos > iLast)
               break;

            const char * pszC1 = psz1;
            const char * pszC2 = psz2;

            iPos2 = iPos;

            while(true)
            {

               if(ch::to_lower_case(ch::uni_index_len(pszC1,len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
               {
                  pszC1 += len1;
                  pszC2 += len2;
                  iPos2 += len1;
                  if(*pszC2 == '\0')
                  {
                     return (psz1 - (const char *)str) - 1; // "-1" because find file extension returns the index of the dot
                  }
                  if(*pszC1 == '\0' || iPos2 > iLast)
                  {
                     return -1;
                  }
               }
               else
               {
                  ch::uni_index_len(psz1,len1);
                  psz1 += len1;
                  iPos += len1;
                  break;
               }
            }

         }

      }

      return -1;

   }


   index utf8_find(const char * pszOld, const char * pszParam, index iStart)
   {
      if(pszOld == nullptr)
         return -1;

      if(*pszOld == '\0')
         return 0;

      if(pszParam == nullptr || *pszParam == '\0')
         return -1;

      const char * psz = &pszParam[iStart];
      const char * pSrc;
      const char * pFin = pszOld;
      i32 lenSrc;
      i32 lenFin;
      while(*psz)
      {
         pSrc = psz;
         while(ch::uni_index_len(pSrc, lenSrc) == ch::uni_index_len(pFin, lenFin) && lenSrc == lenFin)
         {
            pSrc+=lenSrc;
            pFin+=lenFin;
            if(*pSrc == '\0')
            {
               if(*pFin == '\0')
               {
                  return pSrc - pszParam;
               }
               else
               {
                  return -1;
               }
            }
            else if(*pFin == '\0')
            {

               break;

            }

         }

         psz+=lenSrc;
      }

      return -1;

   }


   index find_ci(const char * pszOld, const char * psz, index iStart)
   {

      index iFindLen = strlen(pszOld);

      index iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         ::memcpy_dup(szFind, pszOld, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            ::memcpy_dup(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            pszOld = strstr(sz, szFind);

            if(pszOld == nullptr)
               return -1;

            return iStart + (pszOld - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
            strLow.make_lower();

            psz = strLow;

            pszOld = strstr(psz, szFind);

            if(pszOld == nullptr)
               return -1;

            return iStart + (pszOld - psz);

         }

      }
      else
      {

         string strFindLow(pszOld, iFindLen); // avoid optimized read only string copy
         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }

   index find_wwci(const char * pszOld, const char * psz, index iStart)
   {

      string strFind(pszOld);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_ww(strFind, str, iStart);

   }

   index find_awwci(const char * pszOld, const char * psz, index iStart)
   {

      string strFind(pszOld);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_aww(strFind, str, iStart);

   }

   index find_ww(const char * pszOld, const char * psz, index iStart)
   {

      if(psz == nullptr)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == nullptr)
         return -1;

      string strFind(pszOld);

      while(*pszIter != '\0')
      {

         if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter_or_digit(pszIter + strFind.get_length())))
         {

            return pszIter - psz;

         }

         do
         {

            pszIter = ::str::utf8_inc(pszIter);

         }
         while(*pszIter != '\0' && ::str::ch::is_letter_or_digit(pszIter));

      }

      return -1;

   }

   index find_aww(const char * pszOld, const char * psz, index iStart)
   {

      if(psz == nullptr)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == nullptr)
         return -1;

      string strFind(pszOld);

      while(*pszIter != '\0')
      {

         if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter(pszIter + strFind.get_length())))
         {

            return pszIter - psz;

         }

         do
         {

            pszIter = ::str::utf8_inc(pszIter);

         }
         while(*pszIter != '\0' && ::str::ch::is_letter(pszIter));

      }

      return -1;

   }

   string has_char(const char * pszIfHasChar, const char * pszBefore, const char * pszAfter, const char * pszDoesnt)
   {

      string str;

      if (pszIfHasChar == nullptr)
      {

         if (pszDoesnt != nullptr)
         {

            return pszDoesnt;

         }
         else
         {

            return str;

         }

      }

      if(strlen(pszIfHasChar) == 0)
         return str;

      if(pszBefore != nullptr)
      {

         str = pszBefore;

      }

      str += pszIfHasChar;

      if(pszAfter != nullptr)
      {

         str += pszAfter;

      }

      return str;

   }


   bool has_upper(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper;

   }

   bool has_lower(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasLower;

   }

   bool has_digit(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasDigit;

   }

   void calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      bHasUpper = false;
      bHasLower = false;
      bHasDigit = false;

      while(true)
      {
         string qc = get_utf8_char(psz);
         if(qc.is_empty())
         {
            break;
         }
         else if(::str::ch::is_digit(qc))
         {
            bHasDigit = true;
         }
         else if(::str::ch::is_lower_case(qc))
         {
            bHasLower = true;
         }
         else if(::str::ch::is_upper_case(qc))
         {
            bHasUpper = true;
         }
         if(bHasUpper && bHasDigit && bHasLower)
         {
            // it is not necessary to evaluate more chars anymore
            break;
         }
         psz = utf8_inc(psz);
      }

   }

   bool has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper || bHasLower || bHasDigit;

   }

   bool has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper && bHasLower && bHasDigit;

   }

   bool has_all_v1(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      return has_all_v1(psz, bHasUpper, bHasLower, bHasDigit);

   }


   string if_null(const char * psz, const char * pszIfNull)
   {

      if(psz == nullptr)
         return pszIfNull;
      else
         return psz;

   }

   string get_word(
   const char * psz,
   const char * pszSeparator,
   bool bWithSeparator,
   bool bEndIsSeparator)
   {

      if(psz == nullptr)
         return string();

      if(pszSeparator == nullptr)
      {

         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      const char * pszOld = strstr(psz, pszSeparator);
      if(pszOld == nullptr)
      {
         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      if(bWithSeparator)
      {
         return string(psz, pszOld - psz + 1);
      }
      else
      {
         return string(psz, pszOld - psz);
      }
   }

//   bool to(i64 & i, const char * psz)
//   {
//
//      const char * pszEnd = nullptr;
//
//      i64 iConversion = ::ansi_to_i64(psz, &pszEnd);
//
//      if (pszEnd == psz)
//      {
//
//         return false;
//
//      }
//
//      i = iConversion;
//
//      return true;
//
//   }
//
//   i32 to(i32 & i, const char * psz, int iBase = 10) { return i = ::ansi_to_i32(psz, nullptr, iBase); }
//
//   bool to(i64 & i, const char * psz)
//   {
//
//      if(iBase < 0 || iBase == 1 || iBase > 36)
//         return false;
//
//      char * pszEnd;
//
//#ifdef WINDOWS
//
//      i64 iConversion = ::_strtoi64(psz, &pszEnd, iBase);
//
//#else
//
//      i64 iConversion = ::ansi_to_i64(psz, &pszEnd, iBase);
//
//#endif
//
//      if(pszEnd == psz)
//         return false;
//
//      i = iConversion;
//
//      return true;
//
//   }
//
//   bool to(i32 & i, i32 iBase, const char * psz)
//   {
//
//      if(iBase < 0 || iBase == 1 || iBase > 36)
//         return false;
//
//      char * pszEnd;
//
//#ifdef WINDOWS
//
//      i64 iConversion = ::_strtoi64(psz, &pszEnd, iBase);
//
//#else
//
//      i64 iConversion = ::ansi_to_i64(psz, &pszEnd, iBase);
//
//#endif
//
//      if(pszEnd == psz)
//         return false;
//
//      if(iConversion > numeric_info< i32 >::maximum ())
//         return false;
//
//      i = (i32) iConversion;
//
//      return true;
//
//   }
//
//   bool to(u64 & u, const char * psz)
//   {
//
//      char * pszEnd;
//
//      u64 uiConversion = ::ansi_to_i64(psz, &pszEnd);
//
//      if(pszEnd == psz)
//         return false;
//
//      u = uiConversion;
//
//      return true;
//
//   }
//
//   bool to(u32 & u, const char * psz)
//   {
//
//      char * pszEnd;
//
//      i64 uiConversion = ::ansi_to_u32(psz, &pszEnd);
//
//      if(pszEnd == psz)
//         return false;
//
//      if(uiConversion > numeric_info < u32 > ::maximum())
//         return false;
//
//      u = (u32) uiConversion;
//
//      return true;
//
//   }
//
//
//   bool to(u64 & u, i32 iBase, const char * psz)
//   {
//
//      if(iBase < 0 || iBase == 1 || iBase > 36)
//         return false;
//
//      char * pszEnd;
//
//      u64 uiConversion = ::ansi_to_u64(psz, &pszEnd, iBase);
//
//      if(pszEnd == psz)
//         return false;
//
//      u = uiConversion;
//
//      return true;
//
//   }
//
//   bool to(u32 & u, i32 iBase, const char * psz)
//   {
//
//      if(iBase < 0 || iBase == 1 || iBase > 36)
//         return false;
//
//      char * pszEnd;
//
//      u32 uiConversion = ::ansi_to_u32(psz, &pszEnd, iBase);
//
//      if(pszEnd == psz)
//         return false;
//
//      if(uiConversion > numeric_info< u32 >::maximum ())
//         return false;
//
//      u = uiConversion;
//
//      return true;
//
//   }
//
//   iptr to_iptr(const char * psz)
//   {
//
//#if defined(_LP64) || defined(_AMD64_)
//
//      return to_i64(psz);
//
//#else
//      return to_i32(psz);
//
//#endif
//
//   }
//
//
//

   string uni_to_utf8(i64 w)
   {

      string str;

      if(w < 0x0080 )
      {

         str += (char) w;

      }
      else if(w < 0x0800)
      {

         str = (char)(0xc0 | ((w) >> 6));

         str += (char)(0x80 | ((w) & 0x3f));

      }
      else
      {

         str = (char)(0xe0 | ((w) >> 12));

         str += (char)(0x80 | (((w) >> 6) & 0x3f));

         str += (char)(0x80 | ((w) & 0x3f));

      }

      return str;

   }


   const char * utf8_inc(const char * psz)
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      if (*psz == '\0')
      {

         return psz;

      }

      clear_err();

      char len =  1 + trailingBytesForUTF8(*psz);
      if(len == 0)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 1)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 2)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 3)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 4)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 5)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
      if(len == 6)      return psz;

      {
         set_err(err_invalid_utf8_character);
         return nullptr;
      }
   }


   const char * utf8_inc_slide(strsize * pslide, const char * psz)
   {
      char len =  1 + trailingBytesForUTF8(*psz);
      if(len == 0)
      {
         *pslide += 0;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 1)
      {
         *pslide += 1;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 2)
      {
         *pslide += 2;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 3)
      {
         *pslide += 3;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 4)
      {
         *pslide += 4;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 5)
      {
         *pslide += 5;
         return psz;
      }
      if(*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
      if(len == 6)
      {
         *pslide += 6;
         return psz;
      }
      throw ::exception(error_invalid_character, "invalid utf8 character");
   }


   const char * utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc)
   {

      strsize count = 0;

      ::str::utf8_inc_slide(&count, pchSrc);

      ::memcpy_dup(pchDst, pchSrc, count);

      pchSrc         += count;

      pchDst         += count;

      *pslideback    -= count;

      return pchSrc;

   }



   const char * uni_dec(const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         return nullptr;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            return nullptr;
         }
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            return nullptr;
         }
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            return nullptr;
         }
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            return nullptr;
         }
         return psz - 4;
      }
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            return nullptr;
         }
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            return nullptr;
         }
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         return nullptr;
      }
      return psz - 1;
   }


   const wd16char * uni_dec(const wd16char * pszBeg, const wd16char * psz)
   {

      if (psz <= pszBeg)
      {
         return nullptr;
      }

      if (utf16_is_2nd_surrogate(*(psz - 1)))
      {

         if (psz - 1 <= pszBeg)
         {

            return nullptr;

         }

         return psz - 2;

      }

      return psz - 1;

   }


   const wd32char * uni_dec(const wd32char * pszBeg, const wd32char * psz)
   {
      if (psz <= pszBeg)
      {
         return nullptr;
      }

      return psz - 1;

   }


   const char * utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         pchar->m_chLen = -1;
         return nullptr;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-1];
         pchar->m_sz[1] = '\0';
         pchar->m_chLen = 1;
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-2];
         pchar->m_sz[1] = psz[-1];
         pchar->m_sz[2] = '\0';
         pchar->m_chLen = 2;
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-3];
         pchar->m_sz[1] = psz[-2];
         pchar->m_sz[2] = psz[-1];
         pchar->m_sz[3] = '\0';
         pchar->m_chLen = 3;
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-4];
         pchar->m_sz[1] = psz[-3];
         pchar->m_sz[2] = psz[-2];
         pchar->m_sz[3] = psz[-1];
         pchar->m_sz[4] = '\0';
         pchar->m_chLen = 4;
         return psz - 4;
      }
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-5];
         pchar->m_sz[1] = psz[-4];
         pchar->m_sz[2] = psz[-3];
         pchar->m_sz[3] = psz[-2];
         pchar->m_sz[4] = psz[-1];
         pchar->m_sz[5] = '\0';
         pchar->m_chLen = 5;
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            pchar->m_chLen = -1;
            return nullptr;
         }
         pchar->m_sz[0] = psz[-6];
         pchar->m_sz[1] = psz[-5];
         pchar->m_sz[2] = psz[-4];
         pchar->m_sz[3] = psz[-3];
         pchar->m_sz[4] = psz[-2];
         pchar->m_sz[5] = psz[-1];
         pchar->m_sz[6] = '\0';
         pchar->m_chLen = 6;
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         pchar->m_chLen = -1;
         return nullptr;
      }
      pchar->m_sz[0] = psz[-1];
      pchar->m_sz[1] = '\0';
      pchar->m_chLen = 1;
      return psz - 1;
   }

   const char* utf8_dec(const char* pszBeg, const char* psz)
   {
      if (psz <= pszBeg)
      {
         return nullptr;
      }
      if ((*(psz - 1) & 0x80) == 0x00)
      {
         if ((psz - 1) < pszBeg)
         {
            return nullptr;
         }
         return psz - 1;
      }
      else if ((*(psz - 2) & 0xE0) == 0xC0)
      {
         if ((psz - 2) < pszBeg)
         {
            return nullptr;
         }
         return psz - 2;
      }
      else if ((*(psz - 3) & 0xF0) == 0xE0)
      {
         if ((psz - 3) < pszBeg)
         {
            return nullptr;
         }
         return psz - 3;
      }
      else if ((*(psz - 4) & 0xF8) == 0xF0)
      {
         if ((psz - 4) < pszBeg)
         {
            return nullptr;
         }
         return psz - 4;
      }
      else if ((*(psz - 5) & 0xFC) == 0xF8)
      {
         if ((psz - 5) < pszBeg)
         {
            return nullptr;
         }
         return psz - 5;
      }
      else if ((*(psz - 6) & 0xFE) == 0xFC)
      {
         if ((psz - 6) < pszBeg)
         {
            return nullptr;
         }
         return psz - 6;
      }
      if ((psz - 1) < pszBeg)
      {
         return nullptr;
      }
      return psz - 1;
   }


   string get_utf8_char(const char * psz)
   {
      ::str::utf8_char ch;
      i32 len = ch.parse(psz);
      if(len < 0)
         return "";
      return string(ch.m_sz);
   }


   string get_utf8_char(const char * psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
         return "";
      return string(psz, pszNext - psz);
   }

   bool get_utf8_char(string & str, const char * & psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
      {
         return false;
      }
      str = string(psz, pszNext - psz);
      psz = pszNext;
      return true;
   }

   string get_utf8_char(const char * pszBeg, const char * psz, index i)
   {

      if(i > 0)
      {
         while(i != 0)
         {
            psz = utf8_inc(psz);
            if(*psz == '\0')
            {
               return "";
            }
            i--;
         }
         return get_utf8_char(psz);
      }
      else
      {
         while(i != 0)
         {
            psz = uni_dec(pszBeg, psz);
            if(psz == nullptr)
            {
               return "";
            }
            else if(*psz == '\0')
            {
               return "";
            }
            i++;
         }
         return get_utf8_char(psz);
      }
   }

   string utf8_next_char(const char * pszBeg, const char * psz, index i)
   {
      return get_utf8_char(pszBeg, psz, i + 1);
   }

   string utf8_previous_char(const char * pszBeg, const char * psz, index i)
   {
      return utf8_next_char(pszBeg, psz, -i);
   }


   i32 get_escaped_char(const char * pcsz, strsize pos, strsize &retPos)

   {
      retPos = pos;
      if(pcsz[pos] == '\\')

      {
         retPos++;
         if(pcsz[pos+1] == 'x')

         {
            if(pcsz[pos+2] == '{')

            {
               string val;
               if(!get_curly_content(&pcsz[pos+2], val))

               {
                  return BAD_WCHAR;
               }
               i64 hex = ::hex::to_i64(val);
               strsize val_len = val.get_length();
               if(hex < 0 || hex > 0xFFFF)
               {
                  return BAD_WCHAR;
               }
               retPos += val_len + 2;
               return (i32) hex;
            }
            else
            {
               i64 hex = ::hex::to_i64(string(&pcsz[pos+2], 2));

               if(i64(strlen(pcsz)) <= pos + 2 || hex== -1)

               {
                  return BAD_WCHAR;
               }
               retPos += 2;
               return (i32) hex;
            }
         }
         return pcsz[pos+1];

      }
      return pcsz[pos];

   }

   bool get_curly_content(const char * psz, string & str)
   {
      if (psz[0] != '{') return false;
      const char * pszChar;
      for(pszChar = utf8_inc(psz); pszChar != nullptr; pszChar = utf8_inc(pszChar))
      {
         if (*pszChar == '}')
            break;
         /*  ECharCategory cc = Character::getCategory(str[pos]);

         // check for what??
         if (Character::isWhitespace(str[pos]) ||

         cc == CHAR_CATEGORY_Cn || cc == CHAR_CATEGORY_Cc ||
         cc == CHAR_CATEGORY_Cf || cc == CHAR_CATEGORY_Cs)
         return nullptr;*/
      };
      if (pszChar == nullptr || *pszChar == '\0')
         return false;
      str = string(&psz[1], pszChar - psz - 1);
      return true;
   }


   bool is_simple_natural(const char * pszCandidate, strsize iCount)
   {

      if(iCount == 0)
         return false;

      string str(pszCandidate);

      str.trim();

      const char * psz = str;

      if(*psz == '\0')
         return false;

      while(*psz != '\0' && iCount != 0)
      {
         if(!::str::ch::is_digit(psz))
            return false;
         psz = utf8_inc(psz);
         iCount--;
      }
      return true;
   }


   bool is_natural(const char * psz)
   {

      string str(psz);

      str.trim();

      for (index i = 0; i < str.get_length(); i++)
      {

         if (!ansi_char_is_digit(str[i]))
         {

            return false;

         }

      }

      return true;

   }


   bool is_integer(const char * psz)
   {

      string str(psz);

      str.trim();

      if (::str::begins_eat_ci(str, "-") || ::str::begins_eat_ci(str, "+"))
      {

         return is_natural(str);

      }
      else
      {

         return is_natural(str);

      }

   }


   void consume(const char * & pszParse, const char * psz)
   {

      index idx;

      strsize len = strlen(psz);

      for(idx = 0; idx < len; idx++)
      {

         if(pszParse[idx] != psz[idx])
         {

            throw ::exception(error_parsing, "Name does not match expected");

            break;

         }

      }

      pszParse += len;

   }


   bool eats(const char * & pszParse, const char * psz)
   {

      for (; *psz != '\0'; pszParse++, psz++)
      {

         if (*pszParse != *psz)
         {
            return false;

         }

      }

      return true;

   }


   bool eats_ci(const char * & pszParse, const char * psz)
   {

      for (; *psz != '\0'; pszParse++, psz++)
      {

         if (tolower(*pszParse) != tolower(*psz))
         {
            return false;

         }

      }

      return true;

   }


   void consume(const char * & pszParse, const char * psz, const char * pszEnd)
   {
      __UNREFERENCED_PARAMETER(pszEnd);
      strsize idx;
      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszParse[idx] != psz[idx])
         {
            throw ::exception(error_parsing, "Name does not match expected");
            break;
         }
      }
      pszParse += len;
   }

   void consume(const char * & pszParse, const char * psz, strsize len, const char * pszEnd)
   {
      __UNREFERENCED_PARAMETER(pszEnd);
      i32 idx;
      for(idx = 0; idx < len; idx++)
      {
         if(pszParse[idx] != psz[idx])
         {
            throw ::exception(error_parsing, "Name does not match expected");
            break;
         }
      }
      pszParse += len;
   }

   void consume_spaces(const char * & pszParse, ::count iMinimumCount)
   {
      const char * psz = pszParse;
      i32 i = 0;
      while(::str::ch::is_whitespace(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(i < iMinimumCount)
      {
         throw ::exception(error_parsing, "Space is required");
      }
      pszParse = psz;
   }


   u64 consume_natural(string & strParse, u64 uMax, u64 uMin)
   {

      const char * pszParse = strParse;

      auto u = consume_natural(pszParse, uMax, uMin);

      strParse = pszParse;

      return u;

   }


   u64 consume_natural(const char * & pszParse, u64 uMax, u64 uMin)
   {

      if(uMax < uMin)
      {

         throw ::exception(error_bad_argument, "maximum should be greater than minimum");

      }

      const char * psz = pszParse;

      i32 i = 0;

      u64 u;

      while(::str::ch::is_digit(psz))
      {

         psz = utf8_inc(psz);

         i++;

      }

      if(psz == pszParse)
      {

         throw ::exception(error_parsing, "empty natural found");

      }

      u = ::str::to_u32(string(pszParse, psz - pszParse));

      if(u < uMin)
      {

         throw ::exception(error_parsing, "natural less than minimum");

      }
      else if(u > uMax)
      {

         throw ::exception(error_parsing, "natural greater than maximum");

      }

      pszParse = psz;

      return u;

   }


   void consume_spaces(const char * & pszParse, ::count iMinimumCount, const char * pszEnd)
   {
      const char * psz = pszParse;
      i32 i = 0;
      while(::str::ch::is_whitespace(psz))
      {
         psz = __utf8_inc(psz);
         if(psz > pszEnd)
         {
            throw ::exception(error_parsing, "premature end");
            break;
         }
         i++;
      }
      if(i < iMinimumCount)
      {
         throw ::exception(error_parsing, "Space is required");
      }
      pszParse = psz;
   }


   string consume_non_spaces(string & strParse)
   {

      const char * pszParse = strParse;

      auto str = consume_non_spaces(pszParse, pszParse + strParse.get_length());

      strParse = pszParse;

      return str;

   }


   string consume_non_spaces(const char * & pszParse, const char * pszEnd)
   {

      const char * psz = pszParse;

      while(!::str::ch::is_whitespace(psz))
      {
         psz = __utf8_inc(psz);
         if(psz >= pszEnd)
         {
            break;
         }
      }
      string str(pszParse, psz - pszParse);
      pszParse = psz;
      return str;
   }

   string consume_hex(const char * & pszParse)
   {
      const char * psz = pszParse;
//      i32 i = 0;
      while(*psz != '\0')
      {
         i64 i = ::str::ch::uni_index(pszParse);
         if((i >= '0' && i <= '9') || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'))
         {
            psz = __utf8_inc(psz);
         }
      }
      if(psz == pszParse)
      {
         throw ::exception(error_parsing, "no hex consumed");
         return "";
      }
      string str(pszParse, psz - pszParse);
      pszParse = psz;
      return psz;
   }


   string consume_nc_name(const char * & pszParse)
   {
      const char * psz = pszParse;
      bool start = true;
      while(true)
      {
         const char * ca = psz;
         // first char
         if(start)
         {
            if(!::str::ch::is_letter(ca) || *ca == '\0')
            {
               throw ::exception(error_parsing, "NCName required here");
               return "";
            }
            start = false;
         }
         else
         {
            if(!::str::ch::is_letter_or_digit(ca) && *ca != '_' && *ca != '-')
            {
               break;
            }
            psz = ::str::utf8_inc(psz);
         }
      }
      string str(pszParse, psz - pszParse);
      pszParse = psz;
      return str;
   }

   //string consume_quoted_value(const char * & pszParse)
   //{

   //   ::str::utf8_char utf8char;

   //   const char * psz = pszParse;
   //   utf8char.parse(psz); // quote character
   //   if(utf8char.m_chLen != 1)
   //   {
   //      throw ::exception(error_parsing, "Quote character is required here");
   //      return "";
   //   }
   //   char qc = utf8char.m_sz[0];
   //   if(qc != '\"' && qc != '\\')
   //   {
   //      throw ::exception(error_parsing, "Quote character is required here");
   //      return "";
   //   }
   //   int iPos = utf8char.m_chLen;
   //   string str;
   //   int iPosStart = iPos;
   //   while(true)
   //   {
   //      iPos += utf8char.parse(&psz[iPos]);
   //      if(utf8char.m_chLen <= 0)
   //      {
   //         throw ::exception(error_parsing, "Quote character is required here, premature end");
   //         return "";
   //      }
   //      if(utf8char.m_chLen == 1 && utf8char.m_sz[0] == qc)
   //         break;

   //   }
   //   str = string(&psz[iPosStart], iPos - iPosStart - 1);
   //   pszParse = &psz[iPos];
   //   return str;
   //}


   string consume_quoted_value(const char * & pszParse, const char * pszEnd)
   {

      const char * psz = pszParse;

      pszEnd = psz + strlen(pszParse);

      if(*psz != '\"' && *psz != '\'')
      {

         throw ::exception(error_parsing, "Quote character is required here");

         return "";

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while(*psz != qc)
      {

skip:

         psz = uni_inc(psz);

         if(psz > pszEnd || *psz == '\0')
         {

            throw ::exception(error_parsing, "Quote character is required here, premature end");

            return "";

         }

         if(*psz == '\\')
         {

            psz = __utf8_inc(psz);

            if(psz > pszEnd)
            {

               throw ::exception(error_parsing, "Quote character is required here, premature end");

               return "";

            }

            goto skip;

         }

      }

      psz++;

      pszParse = psz;

      string str(pszValueStart, psz - pszValueStart - 1);

      auto p = str.get_string_buffer();

      auto pend = p + str.get_length();

      while(*p)
      {

         if(*p == '\\')
         {

            if(p[1] == '\\')
            {

               memmove(p, p + 1, pend - p);
            }
            else if(p[1] == '\"')
            {

               memmove(p, p + 1, pend - p);

            }

         }

         p++;

      }

      str.release_string_buffer();

      return str;

   }


   void no_escape_consume_quoted_value(const char * & pszParse, const char * pszEnd, char ** ppsz, strsize & iBufferSize)
   {

      const char * psz = pszParse;

      if (*psz != '\"' && *psz != '\\')
      {

         throw ::exception(error_parsing, "Quote character is required here");

         return;

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while (*psz != qc)
      {

         psz = __utf8_inc(psz);

         if (psz > pszEnd)
         {

            throw ::exception(error_parsing, "Quote character is required here, premature end");

            return;

         }

      }

      strsize iNewBufferSize = psz - pszValueStart;


      if (iNewBufferSize > iBufferSize)
      {

         *ppsz = (char *) memory_allocate(iNewBufferSize+1);

      }

      ansi_count_copy(*ppsz, pszValueStart, iNewBufferSize);

      (*ppsz)[iNewBufferSize] = '\0';

      iBufferSize = iNewBufferSize;

      psz++;

      pszParse = psz;

   }


   string no_escape_consume_quoted_value(const char *& pszParse, const char * pszEnd)
   {

      const char * psz = pszParse;

      if (*psz != '\"' && *psz != '\\')
      {

         throw ::exception(error_parsing, "Quote character is required here");

         return{};

      }

      char qc = *psz;

      psz++;

      const char * pszStart = psz;

      while (*psz != qc)
      {

         psz = __utf8_inc(psz);

         if (psz > pszEnd)
         {

            throw ::exception(error_parsing, "Quote character is required here, premature end");

            return{};

         }

      }

      string str(pszStart, psz - pszStart);

      psz++;

      pszParse = psz;

      return ::move(str);

   }


   void skip_quoted_value_ex2(const char * & pszParse, const char * pszEnd)
   {

      const char * psz = pszParse;

      if (*psz != '\"' && *psz != '\\')
      {

         throw ::exception(error_parsing, "Quote character is required here");

         return;

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while (*psz != qc)
      {

         psz = __utf8_inc(psz);

         if (psz > pszEnd)
         {

            throw ::exception(error_parsing, "Quote character is required here, premature end");

            return;

         }

      }

      memsize iNewBufferSize = psz - pszValueStart;

      psz++;

      pszParse = psz;

   }

   template < const strsize m_iSize = 1024 >
   class mini_str_buffer
   {
   public:


      strsize     m_iPos;
      char        m_sz[m_iSize];
      string      m_str;


      mini_str_buffer()
      {

         m_iPos = 0;

      }

      void append(char ch)
      {

         if (m_iPos + 1 > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

         }

         m_sz[m_iPos] = ch;

         m_iPos ++;


      }

      void append_uni(i64 w)
      {

         if (m_iPos + 3 > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

         }

         if (w < 0x0080)
         {

            m_sz[m_iPos] = char(w);
            m_iPos++;

         }
         else if (w < 0x0800)
         {
            m_sz[m_iPos] = (char)(0xc0 | ((w) >> 6));
            m_iPos++;
            m_sz[m_iPos] = (char)(0x80 | ((w) & 0x3f));
            m_iPos++;
         }
         else
         {
            m_sz[m_iPos] = (char)(0xe0 | ((w) >> 12));
            m_iPos++;
            m_sz[m_iPos] = (char)(0xc0 | (((w) >> 6) & 0x3f));
            m_iPos++;
            m_sz[m_iPos] = (char)(0x80 | ((w) & 0x3f));
            m_iPos++;
         }
      }

      void append(const char * psz, strsize iSize)
      {

         if (m_iPos + iSize > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

            if (iSize > m_iSize)
            {

               m_str.append(m_sz, iSize);

               return;

            }

         }

         ansi_count_copy(&m_sz[m_iPos], psz, iSize);

         m_iPos += iSize;

      }


      void update()
      {

         m_str.append(m_sz, m_iPos);

         m_iPos = 0;

      }

   };

   string consume_quoted_value_ex(const char * & pszParse,const char * pszEnd)
   {
      const char * psz = pszParse;
      char qc = *psz; // quote character
      if(qc != '\"' && qc != '\'')
      {
         throw ::exception(error_parsing, "Quote character is required here, premature end");
         return "";
      }
      psz++;
      const char * pszValueStart = psz;
      //const char * pszValueEnd = psz;
      const char * pszNext = psz;
      string str;
      while(true)
      {
         pszNext = __utf8_inc(psz);
         if(pszNext > pszEnd)
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return "";
         }
         if (*psz == '\0')
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return "";
         }
         else if(*psz == qc)
         {
            psz++;
            break;
         }
         else if(*psz == '\\')
         {
            psz = pszNext;
            pszNext = __utf8_inc(psz);
            if(pszNext > pszEnd)
            {
               throw ::exception(error_parsing, "Quote character is required here, premature end");
               return "";
            }
            if(*psz == 'n')
            {
               str += '\n';
            }
            else if(*psz == 't')
            {
               str+='\t';
            }
            else if(*psz == 'r')
            {
               str+='\r';
            }
            else if(*psz == 'u')
            {
               psz++;
               u16 u[2];
               u[0] = ::hex::parse_u16_exc(psz, pszEnd);
               if (utf16_is_1st_surrogate(u[0]))
               {
                  if (*psz != '\\')
                  {
                     throw ::exception(error_parsing, "expect back slash here (for low surrogate)");
                  }
                  psz++;
                  if (*psz != 'u' && *psz != 'U')
                  {
                     throw ::exception(error_parsing, "expect 'u' character here (for low surrogate)");
                  }
                  psz++;
                  u[1] = ::hex::parse_u16_exc(psz, pszEnd);

                  if (!utf16_is_2nd_surrogate(u[1]))
                  {

                     throw ::exception(error_parsing, "expect low surrogate");

                  }
                  else
                  {

                     wd32char uni = (wd32char)decode_utf16_pair(u);
                     string strUtf8 = wd32_to_ansi_str(&uni, 1);
                     str+=strUtf8;

                  }

               }
               else
               {

                  wd32char uni = u[0];
                  string strUtf8 = wd32_to_ansi_str(&uni, 1);
                  str += strUtf8;

               }
               pszNext = psz;
            }
            else if(*psz == '\"')
            {
               str+='\"';
            }
            else
            {
               str.append(psz,pszNext - psz);
            }
         }
         else
         {
            str.append(psz, pszNext - psz);
         }

         psz = pszNext;

         //pszValueEnd = psz;

      }

      pszParse = psz;

      return str;

   }

   void skip_quoted_value_ex(const char * & pszParse, const char * pszEnd)
   {
      const char * psz = pszParse;
      char qc = *pszParse; // quote character
      if (qc != '\"' && qc != '\'')
      {
         throw ::exception(error_parsing, "Quote character is required here, premature end");
         return;
      }
      psz++;
      const char * pszValueStart = psz;
      //const char * pszValueEnd = psz;
      const char * pszNext = psz;
      while (true)
      {
         pszNext = __utf8_inc(psz);
         if (pszNext > pszEnd)
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return;
         }
         if (*psz == '\0')
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return;
         }
         else if (*psz == '\"')
         {
            psz++;
            break;
         }
         else if (*psz == '\\')
         {
            psz = pszNext;
            pszNext = __utf8_inc(psz);
            if (pszNext > pszEnd)
            {
               throw ::exception(error_parsing, "Quote character is required here, premature end");
               return;
            }
            if (*psz == 'n')
            {
            }
            else if (*psz == 't')
            {
            }
            else if (*psz == 'r')
            {
            }
            else if (*psz == 'u')
            {
               string strUni;
               for (index i = 0; i < 4; i++)
               {
                  psz = pszNext;
                  pszNext = __utf8_inc(psz);
                  if (pszNext > pszEnd)
                  {
                     throw ::exception(error_parsing, "Quote character is required here, premature end");
                     return;
                  }
                  if ((pszNext - psz == 1) && ((*psz >= '0' && *psz <= '9') || (*psz >= 'A' && *psz <= 'F') || (*psz >= 'a' && *psz <= 'f')))
                  {
                  }
                  else
                  {
                     throw ::exception(error_parsing, "16 bit unicode expect here");
                     return;
                  }

               }
            }
            else if (*psz == '\"')
            {
            }
            else
            {
            }
         }
         else
         {
         }

         psz = pszNext;

         //pszValueEnd = psz;

      }

      pszParse = psz;

   }


   string consume_spaced_value(string & str)
   {

      strsize i = 0;

      while(i < str.length() && ansi_char_is_space(str[i]))
      {

         i++;

      }

      if(i >= str.length())
      {

         str.Empty();

         return "";

      }

      strsize iStart = i;

      while(i < str.length() && !ansi_char_is_space(str[i]))
      {
         i++;
      }

      string strResult = str.Mid(iStart, i - iStart);

      str = str.Mid(i);

      return strResult;


   }

   string consume_spaced_value(const char * & psz)
   {

      string str(psz);

      strsize iOldLen = str.length();

      string strResult = consume_spaced_value(str);

      psz += iOldLen - str.length();

      return strResult;

   }

   string consume_spaced_value(const char * & psz, const char * pszEnd)
   {

      string str(psz, pszEnd - psz);

      strsize iOldLen = str.length();

      string strResult = consume_spaced_value(str);

      psz += iOldLen - str.length();

      return strResult;

   }


   string consume_command_line_argument(string & str)
   {

      string strResult;

      strsize iFind1 = str.find('\"');

      strsize iFind2 = str.find('\'');

      strsize iFind = minimum_non_negative(iFind1, iFind2);

      if(iFind < 0)
      {

         strResult = consume_spaced_value(str);

      }
      else
      {

         char chSeparator = str[iFind];

         strsize i = 0;

         while(i < iFind && ansi_char_is_space(str[i]))
         {
            i++;
         }

         if(i < iFind)
         {

            strsize iStart = i;

            while(i < iFind && !ansi_char_is_space(str[i]))
            {
               i++;
            }

            strResult = str.Mid(iStart, i - iStart);

            str = str.Mid(i);

         }
         else
         {

            iFind++;

            strsize iFind2 = str.find(chSeparator,iFind);

            if(iFind2 < 0)
            {

               strsize iStart = iFind;

               i = iStart;

               while(i < str.length() && !ansi_char_is_space(str[i]))
               {
                  i++;
               }

               strResult = str.Mid(iStart, i - iStart);

               str = str.Mid(i);

            }
            else
            {

               strResult = str.Mid(iFind, iFind2 - iFind);

               str = str.Mid(iFind2 + 1);

            }

         }

      }

      return strResult;

   }


   string consume_command_line_argument(const char * & psz)
   {

      string str(psz);

      strsize iOldLen = str.length();

      string strResult = consume_command_line_argument(str);

      psz += iOldLen - str.length();

      return strResult;

   }

   string consume_command_line_argument(const char * & psz, const char * pszEnd)
   {

      string str(psz, pszEnd - psz);

      strsize iOldLen = str.length();

      string strResult = consume_command_line_argument(str);

      psz += iOldLen - str.length();

      return strResult;

   }


   string consume_c_quoted_value(const char * & pszParse, const char * pszEnd)
   {
      const char * psz = pszParse;

      if(pszEnd == nullptr)
      {

         pszEnd = pszParse + strlen(pszParse);

      }

      string strQuoteChar = get_utf8_char(psz);

      if(strQuoteChar != "\"" && strQuoteChar != "\\")
      {

         throw ::exception(error_parsing, "Quote character is required here");

         return "";

      }

      string strCurrentChar;
      string str;
      string strPreviousChar;
      while(psz < pszEnd)
      {
         psz = utf8_inc(psz);
         strPreviousChar = strCurrentChar;
         strCurrentChar = get_utf8_char(psz);
         //string str = ::str::international::utf8_to_unicode(qc2);
         if(strCurrentChar.is_empty())
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return "";
         }
         if(strPreviousChar == "\\")
         {
            str += strCurrentChar;
            strCurrentChar.Empty();
         }
         else if(strCurrentChar == "\\")
         {
         }
         else
         {
            if(strCurrentChar == strQuoteChar)
               break;
            str += strCurrentChar;
         }
      }
      psz = utf8_inc(psz);
      pszParse = psz;
      return str;
   }


   CLASS_DECL_ACME string token(string & str, const char * pszSeparatorText, bool bWithSeparator)
   {

      strsize iFind = str.find(pszSeparatorText);

      string strToken;

      if(iFind >= 0)
      {

         if(bWithSeparator)
         {

            iFind += strlen(pszSeparatorText);

            strToken = str.Left(iFind);

            str = str.Mid(iFind);

         }
         else
         {

            strToken = str.Left(iFind);

            iFind += strlen(pszSeparatorText);

            str = str.Mid(iFind);

         }

      }

      return strToken;

   }


   CLASS_DECL_ACME string line(string& str, bool bNewLine)
   {

      auto iFind1 = str.find('\r');

      auto iFind2 = str.find('\n');

      auto iFind = minimum_non_negative(iFind1, iFind2);

      string strToken;

      if (iFind < 0)
      {

         strToken = str;

         str.Empty();

      }
      else
      {

         auto iEnd = iFind;

         if (iFind1 == iFind && str[iFind1 + 1] == '\n')
         {

            iEnd += 2;

         }
         else
         {

            iEnd++;

         }

         if (bNewLine)
         {

            strToken = str.Left(iEnd);

         }
         else
         {

            strToken = str.Left(iFind);

         }

         str = str.Mid(iEnd);

      }

      return strToken;

   }


   bool begins_consume(const char * & pszParse, const char * psz)
   {
      strsize idx;
      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszParse[idx] != psz[idx])
         {
            return false;
         }
      }
      pszParse += len;
      return true;
   }

   bool xml_is_comment(const char * pszParse)
   {
      return pszParse[0] == '<' && pszParse[1] == '!' && pszParse[2] == '-';
   }

   string xml_consume_comment(const char * & pszParse)
   {
      string str;
      ::str::consume(pszParse, "<!--");
      while(pszParse[0] != '-' || pszParse[1] != '-' ||pszParse[2] != '>')
      {

         if(*pszParse == '\0')
         {
            break;
         }
         str += *pszParse;
         pszParse = ::str::utf8_inc(pszParse);
      }
      consume(pszParse, "-->");
      return str;
   }

   string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad)
   {
      string str;
      str = psz;
      if(pszPattern == nullptr || strlen(pszPattern) == 0)
         return str;
      i32 i = 0;
      if(epad == pad_left)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = pszPattern[i] + str;
            i++;
         }
      }
      else if(epad == pad_right)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = str + pszPattern[i];
            i++;
         }
      }
      return str;
   }

   ::payload ends_get(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == nullptr)
         return psz;
      if(psz == nullptr)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix) == pszSuffix)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }

   ::payload ends_get_ci(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == nullptr)
         return psz;
      if(psz == nullptr)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix).compare_ci(pszSuffix) == 0)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }
   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   /*
   Copyright (C) 2004-2007  Anders Hedstrom

   This library is made available under the terms of the GNU GPL.

   If you would like to use this library in a closed-source application,
   a separate license agreement is available. For information about
   the closed-source license agreement for the C++ sockets library,
   please visit http://www.alhem.net/Sockets/license.html and/or
   email license@alhem.net.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
   */
   /*   string l2string(long l)
      {
         string str;
         char tmp[100];
         sprintf(tmp,"%ld",l);
         str = tmp;
         return str;
      }


      string bigint2string(u64 l)
      {
         string str;
         u64 tmp = l;
         while (tmp)
         {
            u64 a = tmp % 10;
            str = (char)(a + 48) + str;
            tmp /= 10;
         }
         if (!str.get_length())
         {
            str = "0";
         }
         return str;
      }*/

   i32 to_i32(const char * psz)
   {
      return ansi_to_i32(psz);
   }

   u32 to_u32(const char * psz)
   {
      return (u32) ansi_to_i64(psz);
   }

   i64 to_i64(const ::string & str)
   {

      i32 i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      bool bNegative = str[i] == '-';

      if(bNegative)
         i++;

      u64 u = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         u = u * 10 + str[i] - 48;
      }

      if(bNegative)
         return -(i64) u;
      else
         return (i64) u;
   }

   i64 to_i64(const char * psz)
   {

      i32 i = 0;

      for (; *psz != '\0' && i < 30 && ansi_char_is_space(*psz); i++, psz++);

      bool bNegative = *psz == '-';

      if(bNegative)
         psz++;

      u64 u = 0;

      for(; *psz != '\0' && i < 30 && ansi_char_is_digit(*psz); psz++, i++)
      {
         u = u * 10 + *psz - 48;
      }

      if(bNegative)
         return -(i64) u;
      else
         return (i64) u;

   }

   u64 to_u64(const ::string & str)
   {

      i32 i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      u64 u = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         u = u * 10 + str[i] - 48;
      }

      return u;

   }

   u64 to_u64(const char * psz)
   {

      i32 i = 0;

      for (; *psz != '\0' && i < 30 && isspace(*psz); i++, psz++);

      u64 u = 0;

      for(; *psz != '\0' && i < 30 && isdigit(*psz); psz++, i++)
      {
         u = u * 10 + *psz - 48;
      }

      return u;

   }



   void increment_digit_letter(string & str)
   {
      strsize i = str.get_length() - 1;
      while(i >= 0)
      {
         if(str[i] >= '0' && str[i] <= '8')
         {
            str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == '9')
         {
            str = str.Left(i) + string((char)('a')) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] >= 'a' && str[i] <= 'y')
         {
            str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == 'z')
         {
            str = str.Left(i) + string((char)('0')) + str.Right(str.get_length() - i - 1);
            i--;
         }
      }
   }


   bool  while_begins_with_chars_eat(string & str, const char * pcszChars)

   {
      i32 i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(pcszChars, str[i]) == nullptr)

            break;
      }
      str = str.Mid(i);
      return i > 0;
   }

   bool  while_begins_with_chars_eat_ci(string & str, const char * pcszChars) // case insensitive

   {
      i32 i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(pcszChars, tolower(str[i])) == nullptr)

            break;
      }
      str = str.Mid(i);
      return i > 0;
   }


//   void begin(wstring & wstr, const unichar * pcszPrefix)
//   {
//
//      strsize iPrefixLen = wide_length(pcszPrefix);
//
//      if(wstr.get_storage_size_in_bytes() >= ((wstr.get_length() + iPrefixLen + 1) * __sizeof(unichar)))
//      {
//
//         __memmov(&wstr[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
//
//         memcpy_dup(wstr, pcszPrefix, iPrefixLen);
//
//      }
//      else
//      {
//         wstring wstrNew;
//         wstrNew.get_buffer((wstr.get_length() + iPrefixLen + 1) * sizeof(unichar));
//         memcpy_dup(&wstrNew[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
//         memcpy_dup(wstrNew, pcszPrefix, iPrefixLen * sizeof(unichar));
//
//         wstr.attach(wstrNew.detach());
//      }
//
//   }


//   bool begins(const unichar * pcsz, const unichar * pcszPrefix)
//
//   {
//      if(pcsz == nullptr || *pcsz == L'\0')
//
//      {
//         if(pcszPrefix == nullptr || *pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      while(*pcsz == *pcszPrefix)
//
//      {
//         pcsz++;
//
//         pcszPrefix++;
//
//         if(*pcsz == L'\0')
//
//         {
//            if(*pcszPrefix == L'\0')
//
//               return true;
//            else
//               return false;
//         }
//         else if(*pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//      }
//      return false;
//   }

//   bool begins_with(const unichar * pcsz, const unichar * pcszPrefix)
//
//   {
//      return begins(pcsz, pcszPrefix);
//
//   }
//
//   bool begins(const wstring & str, const unichar * pcszPrefix)
//
//   {
//      if(str.is_empty())
//      {
//         if(pcszPrefix == nullptr || *pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      const unichar * pcsz = str;
//
//      while(*pcsz == *pcszPrefix)
//
//      {
//         pcsz++;
//
//         pcszPrefix++;
//
//         if(*pcsz == L'\0')
//
//         {
//            if(*pcszPrefix == L'\0')
//
//               return true;
//            else
//               return false;
//         }
//         else if(*pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//      }
//      return false;
//   }

//   bool begins_with(const wstring & str, const unichar * pcszPrefix)
//
//   {
//      return begins(str, pcszPrefix);
//
//   }



//   ///
//   /// \lparam[in] pcsz Parsed string.
//
//   /// \lparam[in] pcszPrefix Candidate prefix string.
//
//   /// \return True if \point_i32 pcsz is prefixed with \point_i32 pcszPrefix.
//
//   /// \note Case insensitive.
//   ///
//   bool begins_ci(const unichar * pcsz, const unichar * pcszPrefix)
//
//   {
//      if(pcsz == nullptr || *pcsz == L'\0')
//
//      {
//         if(pcszPrefix == nullptr || *pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      while(::str::ch::to_lower_case(*pcsz) == ::str::ch::to_lower_case(*pcszPrefix))
//
//      {
//         pcsz++;
//
//         pcszPrefix++;
//
//         if(*pcsz == L'\0')
//
//         {
//            if(*pcszPrefix == L'\0')
//
//               return true;
//            else
//               return false;
//         }
//         else if(*pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//      }
//      return false;
//   }
//
//   bool begins_ci(const wstring & wstr, const unichar * pcszPrefix)
//
//   {
//      return begins_ci_iws((const unichar *) wstr, pcszPrefix);
//
//   }
//
//   // case insensitive, ignore white space - only in searched string
//   bool begins_ci_iws(const unichar * pcsz, const unichar * pcszPrefix)
//
//   {
//      if(pcsz == nullptr || *pcsz == L'\0')
//
//      {
//         if(pcszPrefix == nullptr || *pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      while(*pcsz && ::str::ch::is_space_char(*pcsz))
//
//         pcsz++;
//
//      if(!*pcsz)
//
//         return false;
//      while(::str::ch::to_lower_case(*pcsz) == ::str::ch::to_lower_case(*pcszPrefix))
//
//      {
//         pcsz++;
//
//         pcszPrefix++;
//
//         if(*pcsz == L'\0')
//
//         {
//            if(*pcszPrefix == L'\0')
//
//               return true;
//            else
//               return false;
//         }
//         else if(*pcszPrefix == L'\0')
//
//         {
//            return true;
//         }
//      }
//      return false;
//   }
//
//   bool begins_ci_iws(const wstring & wstr, const unichar * pcszPrefix)
//
//   {
//      return begins_ci_iws((const unichar *) wstr, pcszPrefix);
//
//   }
//

   string          ansi_lower(const char * psz)
   {

      return string(psz).make_lower();

   }


   string          ansi_upper(const char * psz)
   {

      return string(psz).make_upper();

   }


   /** End \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/


   bool simple_escaped(const ::string & str, strsize pos)
   {

      if(pos == 0)
         return false;

      return str[pos - 1] == '\\' && !simple_escaped(str, pos - 1);

   }


   CLASS_DECL_ACME  bool           trim(string & str)
   {

      strsize iLen = str.length();

      str.trim();

      return iLen != str.length();

   }

   CLASS_DECL_ACME  bool         _008Trim(string & str)
   {

      ::count c = 1;

      bool bTrim = false;

      while(c > 0)
      {

         c = 0;

         if(trim_any_quotes(str))
         {

            c++;

            bTrim = true;

         }

         if(trim(str))
         {

            c++;

            bTrim = true;

         }

      }

      return bTrim;

   }


   CLASS_DECL_ACME  bool         trim_any_quotes(string & strParam)
   {

      string str(strParam);

      bool bTrim = false;

      while(paired_trim(str,'\'') || paired_trim(str,'\"'))
      {
         bTrim = true;
      }

      return bTrim;

   }

   CLASS_DECL_ACME  bool paired_trim(string & str,char ch)
   {

      if(str.get_length() <= 1)
      {

         return false;

      }

      if(str[0] != ch || str.last_char() != ch)
      {

         return false;

      }

      str = str.Mid(1,str.get_length() - 2);

      return true;

   }


   ///
   /// q(between quotes :-) )-valid string
   /// from:http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
   /// more invalid strings to test: http://stackoverflow.com/questions/1301402/example-invalid-utf8-string
   ///
   CLASS_DECL_ACME bool utf8_check_is_valid(const string& string)
   {
      strsize i, c, ix, n, j;
      for (i = 0, ix = string.length(); i < ix; i++)
      {
         c = (unsigned char)string[i];
         //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
         if (0x00 <= c && c <= 0x7f) n = 0; // 0bbbbbbb
         else if ((c & 0xE0) == 0xC0) n = 1; // 110bbbbb
         else if (c == 0xed && i < (ix - 1) && ((unsigned char)string[i + 1] & 0xa0) == 0xa0) return false; //U+d800 to U+dfff
         else if ((c & 0xF0) == 0xE0) n = 2; // 1110bbbb
         else if ((c & 0xF8) == 0xF0) n = 3; // 11110bbb
         //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
         //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
         else return false;
         for (j = 0; j < n && i < ix; j++)   // n bytes matching 10bbbbbb follow ?
         {
            if ((++i == ix) || (((unsigned char)string[i] & 0xC0) != 0x80))
               return false;
         }
      }
      return true;

   }


   ///
   /// q(between quotes :-) )-valid string
   ///
   CLASS_DECL_ACME string q_valid(string str)
   {

      if (str.is_empty())
      {

         return str;

      }

      if (!utf8_check_is_valid(str))
      {

         str = ::str::international::multibyte_to_utf8(::str::international::CodePageAnsi, str);

         if (!utf8_check_is_valid(str))
         {

            return "";

         }

      }

      return str;

   }


   string signed_double(double d)
   {

      if (d > 0.0)
      {

         return "+" + __string(d);

      }
      else if (d < 0.0)
      {

         return __string(d);

      }
      else
      {

         return "0.0";

      }

   }

   string signed_int(int i)
   {

      if (i > 0)
      {

         return "+" + __string(i);

      }
      else if (i < 0)
      {

         return __string(i);

      }
      else
      {

         return "0";

      }

   }


   CLASS_DECL_ACME bool is_true(string str)
   {

      str.trim();

      if (str.is_empty())
      {

         return false;

      }

      if (str.compare_ci("yes") == 0)
      {

         return true;

      }

      if (str.compare_ci("true") == 0)
      {

         return true;

      }

      if (str.compare_ci("on") == 0)
      {

         return true;

      }

      if (str.compare_ci("enable") == 0)
      {

         return true;

      }

      if (str.compare_ci("enabled") == 0)
      {

         return true;

      }

      if (str.compare_ci("check") == 0)
      {

         return true;

      }

      if (str.compare_ci("checked") == 0)
      {

         return true;

      }

      for (index i = 0; i < str.get_length(); i++)
      {

         if (i == 0 && (str[i] == '+' || str[i] == '-'))
         {

         }
         else if (!ansi_char_is_digit(str[i]))
         {

            return false;

         }

      }

      if (ansi_to_i32(str) == 0)
      {

         return false;

      }

      return true;

   }


   CLASS_DECL_ACME void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab, array < strsize * > intptra)
   {

      const char * psz = strParam;

      string str;

      string strTab;

      while (*psz)
      {

         string strChar = ::str::get_utf8_char(psz);

         if (strChar.is_empty())
         {

            break;

         }
         else if (strChar == "\t")
         {

            strTab = string(' ', iWidth - (iOffset % iWidth));

            for (auto pi : intptra)
            {

               if (*pi > iOffset)
               {

                  (*pi) += strTab.get_length() - 1;

               }

            }

            str += strTab;

            iOffset += strTab.get_length();

            if (piaTab != nullptr)
            {

               piaTab->add(strTab.get_length());

            }

         }
         else
         {

            str += strChar;

            iOffset++;

         }

         psz += strChar.get_length();

      }

      strParam = str;

   }


   CLASS_DECL_ACME void replace_tab(strsize iOffset, string & strParam, int iWidth, ::array < strsize * > iaTab)
   {

      return replace_tab(iOffset, strParam, iWidth, nullptr, iaTab);

   }


   CLASS_DECL_ACME string block(char ch, i32 iSize)
   {
      string str;
      for (i32 i = 0; i < iSize; i++)
      {
         str += ch;
      }
      return str;
   }


   CLASS_DECL_ACME void fill(string & str, char ch)
   {

      str = block(ch, (i32)str.get_length());

   }


} // namespace str


CLASS_DECL_ACME void to_string(string & str, const float & f)
{

   char sz[256];

   sprintf(sz, "%f", f);

   str = sz;

   str.replace_with(".", ",");

}


CLASS_DECL_ACME void to_string(string & str, const double & d)
{

   char sz[256];

   sprintf(sz, "%f", d);

   str = sz;

   str.replace_with(".", ",");

}


CLASS_DECL_ACME string _002Underscore(string str)
{

   str.replace_with("_",  "-");

   str.replace_with("_", "/");

   str.replace_with("_", "\\");

   return str;

}


namespace str
{


   void fix_eol(string & str)
   {

      str.replace_with("\n", "\r\n");

      str.replace_with("\n", "\n\r");

      str.replace_with("\n", "\r");

#ifdef WINDOWS

      str.replace_with("\r\n", "\n");

#endif

   }


   CLASS_DECL_ACME string & zero_pad(string & str, strsize lenPad)
   {

      ::ansi_zero_pad(str.get_string_buffer(str.length() + lenPad), lenPad);

      str.release_string_buffer();

      return str;

   }


   CLASS_DECL_ACME string zero_padded(const ::string & strSrc, strsize lenPad)
   {

      string str(strSrc);

      if (lenPad > str.get_length())
      {

         ::ansi_zero_pad(str.get_string_buffer(lenPad), lenPad);

         str.release_string_buffer(lenPad);

      }

      return str;

   }


} // namespace str



void to_string(string & str, const ::string_stream & strstream)
{

   str = strstream.get_string();

}


void to_string(string & str, const ::text_stream & strstream)
{

   str = strstream.get_string();

}



