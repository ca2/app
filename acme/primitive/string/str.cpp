#include "framework.h"
#include "hex.h"
#include "international.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
//#include "acme/filesystem/file/text_stream.h"
//#include "acme/primitive/collection/string_array.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/str.h"
#include "string.h"
#include <stdio.h>


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
// bool is_surrogated(u32 character)
//{
//   return 0x10000 <= character && character <= 0x10FFFF;
//}
// void str::encode_utf16_pair(u32 character, u16 *units)
//{
//   unsigned int code;
//   ASSERT(utf32_is_surrogated(character));
//   code = (character - 0x10000);
//   units[0] = 0xD800 | (code >> 10);
//   units[1] = 0xDC00 | (code & 0x3FF);
//}

u32 decode_utf16_pair(u16 * units)
{
   u32 code;
   ASSERT(utf16_is_1st_surrogate(units[0]));
   ASSERT(utf16_is_2nd_surrogate(units[1]));
   code = 0x10000;
   code += (units[0] & 0x03FF) << 10;
   code += (units[1] & 0x03FF);
   return code;
}
//namespace str
//{
//
//    enum_error g_eerror = ::str().e_error_none;


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


////template < >
//i32 str::compare(const ::string & str1, const ::string & str2)
//{
//
//   return strcmp(str1, str2);
//
//}
//
//
////template < >
//i32 str::case_insensitive_order(const ::string & str1, const ::string & str2)
//{
//
//   return ansi_compare_ci(str1, str2);
//
//}
//
//
////template < >
//bool str::equals(const ::string & str1, const ::string & str2)
//{
//
//   return compare(str1, str2) == 0;
//
//}

//
//template < >
//bool str::case_insensitive_equals(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//   return case_insensitive_order(psz1, psz2) == 0;
//}

////template < >
//string  str::equals_get(const ::string & str1, const ::string & str2, const ::string & strGetOnEqual, const ::string & strGetOnDifferent)
//{
//   return equals(str1, str2) ? strGetOnEqual : strGetOnDifferent;
//}
//
//
////template < >
//string  str::equals_ci_get(const ::string & str1, const ::string & str2, const ::string & strGetOnEqual, const ::string & strGetOnDifferent)
//{
//
//   return equals(str1, str2) ? strGetOnEqual : strGetOnDifferent;
//
//}


//template < >
//bool str::begins(const ::string & str, const ::string & strPrefix)
//{
//
//   if (str.is_empty())
//   {
//
//      if (strPrefix.is_empty())
//      {
//         return true;
//      }
//      else
//      {
//         return false;
//      }
//   }
//   const ::scoped_string & scopedstr = str;
//   const ::scoped_string & scopedstrPrefix = strPrefix;
//   while (*pcsz == *pcszPrefix)
//
//   {
//      pcsz++;
//
//      pcszPrefix++;
//
//      if (*pcsz == '\0')
//
//      {
//         if (*pcszPrefix == '\0')
//
//            return true;
//         else
//            return false;
//      }
//      else if (*pcszPrefix == '\0')
//
//      {
//         return true;
//      }
//   }
//   return false;
//}
//

//bool str::begins_with(const ::string & str, const ::string & strPrefix)
//{
//
//   return begins(str, strPrefix);
//
//}

//bool str::begins(const ::string & str, const ::scoped_string & scopedstrPrefix)

//{
//   if(str.is_empty())
//   {
//      if(pcszPrefix == nullptr || *pcszPrefix == '\0')

//      {
//         return true;
//      }
//      else
//      {
//         return false;
//      }
//   }
//   const ::scoped_string & scopedstr = str;

//   while(*pcsz == *pcszPrefix)

//   {
//      pcsz++;

//      pcszPrefix++;

//      if(*pcsz == '\0')

//      {
//         if(*pcszPrefix == '\0')

//            return true;
//         else
//            return false;
//      }
//      else if(*pcszPrefix == '\0')

//      {
//         return true;
//      }
//   }
//   return false;
//}

//bool str::begins_with(const ::string & str, const ::scoped_string & scopedstrPrefix)

//{
//   return begins(str, pcszPrefix);

//}

//template < >
//bool str::case_insensitive_begins(const ::string & str, const ::string & strPrefix)
//
//{
//   if (str.is_empty())
//
//   {
//      if (strPrefix.is_empty())
//
//      {
//         return true;
//      }
//      else
//      {
//         return false;
//      }
//   }
//   auto pcsz = str.c_str();
//   auto pcszPrefix = strPrefix.c_str();
//   while (tolower((::ansi_character)*pcsz) == tolower((::ansi_character)*pcszPrefix))
//
//   {
//      pcsz++;
//
//      pcszPrefix++;
//
//      if (*pcsz == '\0')
//
//      {
//         if (*pcszPrefix == '\0')
//
//            return true;
//         else
//            return false;
//      }
//      else if (*pcszPrefix == '\0')
//
//      {
//         return true;
//      }
//   }
//   return false;
//}
//

//template < >
//bool str::case_insensitive_begins(const wide_string & wstr, const wide_string & wstrPrefix)
//{
//
//   if (wstr.is_empty())
//   {
//
//      if (wstrPrefix.is_empty())
//      {
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }
//
//   }
//
//   auto pcsz = wstr.c_str();
//
//   auto pcszPrefix = wstrPrefix.c_str();
//
//   while (tolower(*pcsz) == tolower(*pcszPrefix))
//   {
//
//      pcsz++;
//
//      pcszPrefix++;
//
//      if (*pcsz == '\0')
//      {
//
//         if (*pcszPrefix == '\0')
//         {
//
//            return true;
//
//         }
//         else
//         {
//
//            return false;
//
//         }
//
//      }
//      else if (*pcszPrefix == '\0')
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}


// case insensitive, ignore white space - only in searched string
bool str::begins_ci_iws(const ::string & str, const ::string & strPrefix)
{

   if (str.is_empty())
   {

      if (strPrefix.is_empty())
      {

         return true;

      }
      else
      {

         return false;

      }

   }

   auto pcsz = str.c_str();

   while (*pcsz && ansi_char_isspace(*pcsz))

      pcsz++;

   if (!*pcsz)
   {

      return false;

   }

   auto pcszPrefix = strPrefix.c_str();

   while (ansi_char_tolower(*pcsz) == ansi_char_tolower(*pcszPrefix))
   {

      pcsz++;

      pcszPrefix++;

      if (*pcsz == '\0')
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
      else if (*pcszPrefix == '\0')
      {

         return true;

      }

   }

   return false;

}


//te
//bool str::begins_ci_iws(const ::string & str, const ::scoped_string & scopedstrPrefix)

//{
//   return begins_ci_iws(str.c_str(), pcszPrefix);

//}



//bool str::eat_before(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound)
//{
//
//   ASSERT(&wstr != &wstrBefore);
//
//   if (&wstr == &wstrBefore)
//   {
//
//      return false;
//
//   }
//
//   auto pFind = wstr.find(wstrSeparator);
//
//   if (::is_null(pFind))
//   {
//
//      if (bEatEverythingIfNotFound)
//      {
//
//         wstrBefore = wstr;
//
//         wstr.Empty();
//
//      }
//
//      return false;
//
//   }
//
//   wstrBefore = wstr(0, pFind);
//
//   wstr = wstr.Mid(iFind + wstrSeparator.length());
//
//   return true;
//
//}
//
//
//bool str::eat_before_let_separator(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound)
//{
//
//   ASSERT(&wstr != &wstrBefore);
//
//   if (&wstr == &wstrBefore)
//   {
//
//      return false;
//
//   }
//
//   auto pFind = wstr.find(wstrSeparator);
//
//   if (::is_null(pFind))
//   {
//
//      if (bEatEverythingIfNotFound)
//      {
//
//         wstrBefore = wstr;
//
//         wstr = wstrSeparator;
//
//      }
//
//      return false;
//
//   }
//
//   wstrBefore = wstr(0, pFind);
//
//   wstr = wstr(pFind);
//
//   return true;
//
//}


//   bool begins_eat(string & str, const ::scoped_string & scopedstrPrefix)
//
//   {
//
//      string strPrefix(pcszPrefix);
//
//
//      strsize iLen = strPrefix.length();
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

//   bool case_insensitive_begins_eat(string & str, const ::scoped_string & scopedstrPrefix)
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
//      strsize iLen = strPrefix.length();
//
//      if(str.Left(iLen).case_insensitive_order(pcszPrefix) == 0)
//
//      {
//         str = str.Mid(iLen);
//         return true;
//      }
//
//      return false;
//
//   }

//   bool case_insensitive_begins_eat(string & str, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSeparator)
//   {
//
//      if(str.case_insensitive_order(pcszPrefix) == 0)
//      {
//
//
//         str.Empty();
//         return true;
//      }
//      else
//      {
//         return case_insensitive_begins_eat(str, string(pcszPrefix) + pszSeparator);
//
//      }
//   }

   //bool ends(const ::string & str, const ::scoped_string & scopedstrSuffix)

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
   //   const ::ansi_character * pszEnd = pcsz;

   //   const ::scoped_string & scopedstrSuffixEnd = pcszSuffix;

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

   //   i32 iLen = strSuffix.length();
   //   if(str.Right(iLen) == pcszSuffix)

   //   {
   //   return true;
   //   }
   //   return false;*/
   //}

   //bool case_insensitive_ends(const ::string & str, const ::scoped_string & scopedstrSuffix)

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
   //   const ::ansi_character * pszEnd = pcsz;

   //   const ::scoped_string & scopedstrSuffixEnd = pcszSuffix;

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


//   bool case_insensitive_ends(const ::string & str, const ::scoped_string & scopedstrSuffix)
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
//      const ::scoped_string & scopedstr = str;
//
//      const ::ansi_character * pszEnd = pcsz + str.length();
//
//      const ::scoped_string & scopedstrSuffixEnd = pcszSuffix;
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

//   bool case_insensitive_ends(const ::payload & payload, const ::scoped_string & scopedstrSuffix)
//
//   {
//      return case_insensitive_ends(payload.get_string(), pcszSuffix);
//
//   }


//   bool case_insensitive_ends_eat(string & str, const ::scoped_string & scopedstrSuffix)
//
//   {
//
//      string strSuffix(pcszSuffix);
//
//
//      strsize iLen = strSuffix.length();
//
//      if(str.Right(iLen).case_insensitive_order(pcszSuffix) == 0)
//
//      {
//
//         str = str.Left(str.length() - iLen);
//         return true;
//
//      }
//
//      return false;
//
//   }

   //void str::copy(string & str, const ::scoped_string & scopedstr, i32 iCount)
   //{

   //   string strCopy(pcsz, iCount);

   //   str = strCopy;
   //}


string str::replace_with(const ::string & strOld, const ::string & strNew, const ::string & strParam, strsize iStart)
{

   string str(strParam);

   str.replace_with(strOld, strNew, iStart);

   return str;

}


index  str::find_first(const string_array & straSearch, index & iFound, const ::string & str, index iStart)
{

   auto pFind = -1;

   iFound = -1;

   for (index i = 0; i < straSearch.get_count(); i++)
   {

      if (straSearch[i].has_char())
      {

         index iSearch = str.find(straSearch[i], iStart);

         if (iSearch >= 0 && iSearch >= iStart && (iSearch < iFind || ::is_null(pFind)))
         {

            iFind = iSearch;
            iFound = i;

         }

      }

   }

   return iFind;

}


string str::random_replace(::particle * pparticle, const string_array & straNew, const string_array & straOld, const ::string & strParam)
{

   string str(strParam);

   index iFind;

   index iFound;

   index iStart = 0;

   while ((iFind = find_first(straOld, iFound, str, iStart)) >= 0)
   {

      if (iFind < iStart)
      {

         throw ::exception(error_parsing, "random replace error");

         return "";

      }

      index i = (index)(rand() % straNew.get_size());

      str = str(0, pFind) + straNew[i] + str.Mid(iFind + straOld[iFound].get_length());

      iFind += straNew[i].get_length();

      iStart = iFind;

   }

   return str;
}


::count str::utf8_replace_with(string & str, const ::string & strNew, const ::string & strOld, strsize iStart)
{

   ::count c = 0;

   index iPos = iStart;

   ::count iReplaceLen = -1;

   ::count iFindLen = -1;

   while (true)
   {

      iPos = utf8_find(strOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = strNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = strOld.length();

      }

      str = str.Left(iPos) + strNew + str.Mid(iPos + iFindLen);

      iPos += iReplaceLen;

      c++;

   }

   return c;

}


string str::utf8_replace_with(const ::string & strNew, const ::string & strOld, const ::string & strParam, strsize iStart)
{

   index iPos = iStart;

   string str(strParam);

   ::count iReplaceLen = -1;

   ::count iFindLen = -1;

   while (true)
   {

      iPos = utf8_find(strOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = strNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = strOld.length();

      }

      str = str.Left(iPos) + strNew + str.Mid(iPos + iFindLen);

      iPos += iReplaceLen;

   }

   return str;
}


string str::case_insensitive_replace_with(const ::string & strNew, const ::string & strOld, const ::string & strParam, strsize iStart)
{

   index iPos = iStart;

   string str(strParam);

   ::count iReplaceLen = -1;

   ::count iFindLen = -1;

   while (true)
   {

      iPos = case_insensitive_find(strOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = strNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = strOld.length();

      }

      str = str.Left(iPos) + strNew + str.Mid(iPos + iFindLen);

      iPos += iReplaceLen;

   }

   return str;
}


::count str::replace_with_ci_count(const ::string & strNew, const ::string & strOld, const ::string & strParam, strsize iStart)
{

   index iPos = iStart;

   string str(strParam);

   ::count iReplaceLen = -1;

   ::count iFindLen = -1;

   ::count c = 0;

   while (true)
   {

      iPos = case_insensitive_find(strOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = strNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = strOld.length();

      }

      str = str.Left(iPos) + strNew + str.Mid(iPos + iFindLen);

      iPos += iReplaceLen;

      c++;

   }

   return c;

}


index str::case_insensitive_find(const ::string & strFind, const ::string & str, index iStart)
{

   if (strFind.length() > (str.length() - iStart))
   {

      return -1;

   }

   string strFindLow(&((const char *)strFind)[0], strFind.length()); // avoid optimized read only string copy

   strFindLow.make_lower();

   string strLow(&((const char *)str)[iStart], str.length() - iStart); // avoid optimized read only string copy

   strLow.make_lower();

   auto pFind = strLow.find(strFindLow);

   if (::is_null(pFind))
   {

      return -1;

   }

   return iStart + iFind;

}


//index str::case_insensitive_find(const ::string & strFind, const ::string & strParam, index iStart)
//{

//   ::count iFindLen = strFind.length();

//   ::count iLen = strlen(&psz[iStart]);

//   if (iFindLen > iLen)
//   {

//      return -1;

//   }

//   if(iFindLen < 256)
//   {

//      char szFind[256];

//      ::memcpy_dup(szFind, strFind, iFindLen + 1);

//      make_lower(szFind);

//      if(iLen < 256)
//      {

//         char sz[256];

//         ::memcpy_dup(sz, &psz[iStart], iLen + 1);

//         make_lower(sz);

//         const ::scoped_string & scopedstrOld = strstr(sz, szFind);

//         if (pszOld == nullptr)
//         {

//            return -1;

//         }

//         return iStart + (pszOld - sz);

//      }
//      else
//      {

//         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

//         strLow.make_lower();

//         psz = strLow;

//         const ::scoped_string & scopedstrOld = strstr(psz, szFind);

//         if (pszOld == nullptr)
//         {

//            return -1;

//         }

//         return iStart + (pszOld - psz);

//      }

//   }
//   else
//   {

//      string strFindLow(&((const char *)strFind)[0], iFindLen); // avoid optimized read only string copy

//      strFindLow.make_lower();

//      string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

//      strLow.make_lower();

//      auto pFind = strLow.find(strFindLow);

//      if (::is_null(pFind))
//      {

//         return -1;

//      }

//      return iStart + iFind;

//   }

//}


//index str::case_insensitive_find(const ::string & strOld, const ::string & str, index iStart)
//{

//   ::count iFindLen = strOld.length();

//   index iLen = str.length() - iStart;

//   if (iLen < iFindLen)
//   {

//      return -1;

//   }

//   ::i32 len1;
//   ::i32 len2;

//   const ::scoped_string & scopedstr1 = str;

//   psz1 += iStart;

//   const ::scoped_string & scopedstr2 = strOld;

//   while(true)
//   {

//      if(*psz1 == '\0')
//      {

//         break;

//      }

//      if(*psz2 == '\0')
//      {

//         break;

//      }

//      const ::scoped_string & scopedstrC1 = psz1;

//      const ::scoped_string & scopedstrC2 = psz2;

//      while(true)
//      {

//         if(ch().to_lower_case(ch().uni_index_len(pszC1, len1)) == ch().to_lower_case(ch().uni_index_len(pszC2, len2)))
//         {

//            pszC1 += len1;
//            pszC2 += len2;
//            if(*pszC2 == '\0')
//            {
//               return psz1 - (const char *) str;
//            }
//            if(*pszC1 == '\0')
//            {
//               return -1;
//            }
//         }
//         else
//         {
//            ch().uni_index_len(psz1,len1);
//            psz1 += len1;
//            break;
//         }
//      }

//   }

//   return -1;

//}


//index str::case_insensitive_find(const ::scoped_string & scopedstrOld,const ::string & str,index iStart, index iLast)
//{

//   ::count iFindLen = strlen(pszOld);

//   index iLen = str.length() - iStart;

//   if(iLast < 0)
//      iLast +=iLen;

//   ::i32 len1;
//   ::i32 len2;

//   const ::scoped_string & scopedstr1 = str;
//   const ::scoped_string & scopedstr2 = pszOld;

//   strsize iPos = 0;

//   while(iPos <= iLast)
//   {

//      if(*psz1 == '\0')
//      {
//         break;
//      }

//      if(*psz2 == '\0')
//      {
//         break;
//      }

//      const ::scoped_string & scopedstrC1 = psz1;
//      const ::scoped_string & scopedstrC2 = psz2;

//      while(true)
//      {

//         if(ch().to_lower_case(ch().uni_index_len(pszC1,len1)) == ch().to_lower_case(ch().uni_index_len(pszC2,len2)))
//         {
//            pszC1 += len1;
//            pszC2 += len2;
//            if(*pszC2 == '\0')
//            {
//               return psz1 - (const char *)str;
//            }
//            if(*pszC1 == '\0')
//            {
//               return -1;
//            }
//         }
//         else
//         {
//            ch().uni_index_len(psz1,len1);
//            psz1 += len1;
//            iPos += len1;
//            break;
//         }
//      }

//   }

//   return -1;

//}


index str::find_file_extension(const ::string & strOld, const ::string & str, index iStart, index iLast)
{

   if (strOld.is_empty()) // do not search for empty Extensions
   {

      return -1;

   }

   // for dir::name_is (check if base name of a file is a directory, checking if there is a simple ansi '.', may be very good start point_i32 definitive false).
   // if there is a dot, it may still does not have a Latin dot, if the dot is inside a Multibyte UTF8 char, anyway, algo following should check it properly.

   index iLen = str.length() - iStart;

   if (iLast < 0)
   {

      iLast += iLen;

   }

   {

      const ::ansi_character * pszOkToContinue = strchr(str, '.');

      if (pszOkToContinue == nullptr || pszOkToContinue - (const char *)str >= iLast)
      {

         return -1;

      }

   }

   ::count iFindLen = strOld.length();

   i32 len1;

   i32 len2;

   const ::ansi_character * psz1 = str;

   const ::ansi_character * psz2 = strOld;

   strsize iPos = 0;

   strsize iPos2 = 0;

   while (iPos <= iLast)
   {

      if (*psz1 == '\0')
      {

         break;

      }

      if (*psz2 == '\0')
      {

         break;

      }

      if (*psz1 != '.')
      {

         len1 = utf8_unicode_length(*psz1);

         psz1 += len1;

         iPos += len1;

      }
      else
      {

         psz1 += 1;

         iPos += 1;

         if (iPos > iLast)
         {

            break;

         }

         const ::ansi_character * pszC1 = psz1;

         const ::ansi_character * pszC2 = psz2;

         iPos2 = iPos;

         while (true)
         {

            if (unicode_to_lower_case(unicode_index_length(pszC1, len1)) == unicode_to_lower_case(unicode_index_length(pszC2, len2)))
            {

               pszC1 += len1;

               pszC2 += len2;

               iPos2 += len1;

               if (*pszC2 == '\0')
               {

                  return (psz1 - (const char *)str) - 1; // "-1" because find file extension returns the index of the dot

               }

               if (*pszC1 == '\0' || iPos2 > iLast)
               {

                  return -1;

               }

            }
            else
            {

               unicode_index_length(psz1, len1);

               psz1 += len1;

               iPos += len1;

               break;

            }

         }

      }

   }

   return -1;

}


index str::utf8_find(const ::string & strOld, const ::string & str, index iStart)
{

 if (strOld.is_empty())
 {

    return 0;

 }

 if (str.is_empty())
 {

    return -1;

 }

 auto psz = &str[iStart];

 const char * pSrc;

 const char * pFin = strOld;

 i32 lenSrc;

 i32 lenFin;

 while(*psz)
 {

    pSrc = psz;

    while(unicode_index_length(pSrc, lenSrc) == unicode_index_length(pFin, lenFin) && lenSrc == lenFin)
    {

       pSrc+=lenSrc;

       pFin+=lenFin;

       if(*pSrc == '\0')
       {

          if(*pFin == '\0')
          {

             return pSrc - psz;

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


//index str::case_insensitive_find(const ::string & strOld, const ::string & str, index iStart)
//{
//
//  index iFindLen = strOld.length();
//
//  index iLen = strlen(&str[iStart]);
//
//  if (iFindLen > iLen)
//  {
//
//     return -1;
//
//  }
//
//  if(iFindLen < 256)
//  {
//
//     char szFind[256];
//
//     ::memcpy_dup(szFind, strOld, iFindLen + 1);
//
//     make_lower(szFind);
//
//     if(iLen < 256)
//     {
//
//        char sz[256];
//
//        ::memcpy_dup(sz, &str[iStart], iLen + 1);
//
//        make_lower(sz);
//
//        auto pszOld = strstr(sz, szFind);
//
//        if (pszOld == nullptr)
//        {
//
//           return -1;
//
//        }
//
//        return iStart + (pszOld - sz);
//
//     }
//     else
//     {
//
//        string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
//        
//        strLow.make_lower();
//
//        psz = strLow;
//
//        auto pszOld = strstr(psz, szFind);
//
//        if (pszOld == nullptr)
//        {
//
//           return -1;
//
//        }
//
//        return iStart + (pszOld - psz);
//
//     }
//
//  }
//  else
//  {
//
//     string strFindLow(strOld, iFindLen); // avoid optimized read only string copy
//
//     strFindLow.make_lower();
//
//     string strLow(&str[iStart], iLen); // avoid optimized read only string copy
//
//     strLow.make_lower();
//
//     auto pFind = strLow.find(strFindLow);
//
//     if (::is_null(pFind))
//     {
//
//        return -1;
//
//     }
//
//     return iStart + iFind;
//
//  }
//
//}


index str::find_wwci(const ::string & strOld, const ::string & strParam, index iStart)
{

   string strFind(strOld);

   strFind.make_lower();

   string str(strParam);

   str.make_lower();

   return find_ww(strFind, str, iStart);

}


index str::find_awwci(const ::string & strOld, const ::string & strParam, index iStart)
{

   string strFind(strOld);

   strFind.make_lower();

   string str(strParam);

   str.make_lower();

   return find_aww(strFind, str, iStart);

}


strsize str::find_ww(const ::string & strOld, const ::string & strParam, index iStart)
{

   if (strParam.is_empty())
   {

      return -1;

   }

   auto psz = strParam.c_str();

   const ::ansi_character * pszIter = &strParam[iStart];

   if (pszIter == nullptr)
   {

      return -1;

   }

   string strFind(strOld);

   while (*pszIter != '\0')
   {

      if (strFind == string(pszIter, strFind.length())
         && (strlen(pszIter) == (size_t)strFind.length() || !unicode_is_letter_or_digit(pszIter + strFind.length())))
      {

         return pszIter - psz;

      }

      do
      {

         unicode_increment(pszIter);

      } while (*pszIter != '\0' && unicode_is_letter_or_digit(pszIter));

   }

   return -1;

}


strsize str::find_aww(const ::string & strOld, const ::string & strParam, index iStart)
{

   if (strParam.is_empty())
   {

      return -1;

   }

   auto psz = strParam.c_str();

   const ::ansi_character * pszIter = &psz[iStart];

   if (pszIter == nullptr)
   {

      return -1;

   }

   string strFind(strOld);

   while (*pszIter != '\0')
   {

      if (strFind == string(pszIter, strFind.length())
         && (strlen(pszIter) == (size_t)strFind.length() || !unicode_is_letter(pszIter + strFind.length())))
      {

         return pszIter - psz;

      }

      do
      {

         unicode_increment(pszIter);

      } while (*pszIter != '\0' && unicode_is_letter(pszIter));

   }

   return -1;

}


string str::has_char(const ::string & strIfHasChar, const ::string & strBefore, const ::string & strAfter, const ::string & strDoesnt)
{

   string str;

   if (strIfHasChar.is_empty())
   {

      if (strDoesnt.has_char())
      {

         return strDoesnt;

      }
      else
      {

         return str;

      }

   }

   if (strIfHasChar.is_empty())
   {

      return str;

   }

   if (strBefore.has_char())
   {

      str = strBefore;

   }

   str += strIfHasChar;

   if (strAfter.has_char())
   {

      str += strAfter;

   }

   return str;

}


bool str::has_upper(const ::string & str)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper;

}


bool str::has_lower(const ::string & str)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasLower;

}


bool str::has_digit(const ::string & str)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasDigit;

}


void str::calc_v1(const ::string & strParam, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   auto psz = strParam.c_str();

   bHasUpper = false;
   bHasLower = false;
   bHasDigit = false;

   while (true)
   {

      string strUtf8Char = get_utf8_char(psz);

      if (strUtf8Char.is_empty())
      {

         break;

      }
      else if (unicode_is_digit(strUtf8Char))
      {
         
         bHasDigit = true;

      }
      else if (unicode_is_lower_case(strUtf8Char))
      {
         
         bHasLower = true;

      }
      else if (unicode_is_upper_case(strUtf8Char))
      {

         bHasUpper = true;

      }
      if (bHasUpper && bHasDigit && bHasLower)
      {
         // it is not necessary to evaluate more chars anymore
         break;
      }
      
      unicode_increment(psz);

   }

}


bool str::has_one_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper || bHasLower || bHasDigit;

}


bool str::has_all_v1(const ::string & str, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper && bHasLower && bHasDigit;

}


bool str::has_all_v1(const ::string & str)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   return has_all_v1(str, bHasUpper, bHasLower, bHasDigit);

}


string str::if_null(const ::string & str, const ::string &strIfNull)
{

   if (str.is_empty())
   {
    
      return strIfNull;

   }
   else
   {

      return str;

   }

}


string str::get_word(const ::string & str, const ::string & strSeparator, bool bWithSeparator, bool bEndIsSeparator)
{

   if (str.is_empty())
      return {};

   if (strSeparator.is_empty())
   {

      if (bEndIsSeparator)
      {

         return str;

      }
      else
      {

         return {};

      }

   }

   auto psz = str.c_str();

   const ::ansi_character * pszOld = strstr(psz, strSeparator);

   if (pszOld == nullptr)
   {

      if (bEndIsSeparator)
      {

         return str;

      }
      else
      {

         return {};

      }

   }

   if (bWithSeparator)
   {

      return string(psz, pszOld - psz + 1);

   }
   else
   {

      return string(psz, pszOld - psz);

   }

}

// GitHub MightyPork / utf8_encode.c

utf8_character unicode_to_utf8(::i64 i)
{

   utf8_character utf8character;
   auto & out = utf8character.m_sz;
   if (i <= 0x7F) {
      // Plain ASCII
      out[0] = (char)i;
      out[1] = 0;
      utf8character.m_end = utf8character.m_begin + 1;
   }
   else if (i <= 0x07FF) {
      // 2-byte unicode
      out[0] = (char)(((i >> 6) & 0x1F) | 0xC0);
      out[1] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[2] = 0;
      utf8character.m_end = utf8character.m_begin + 2;
   }
   else if (i <= 0xFFFF) {
      // 3-byte unicode
      out[0] = (char)(((i >> 12) & 0x0F) | 0xE0);
      out[1] = (char)(((i >> 6) & 0x3F) | 0x80);
      out[2] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[3] = 0;
      utf8character.m_end = utf8character.m_begin + 3;
   }
   else if (i <= 0x10FFFF) {
      // 4-byte unicode
      out[0] = (char)(((i >> 18) & 0x07) | 0xF0);
      out[1] = (char)(((i >> 12) & 0x3F) | 0x80);
      out[2] = (char)(((i >> 6) & 0x3F) | 0x80);
      out[3] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[4] = 0;
      utf8character.m_end = utf8character.m_begin + 4;
   }
   else {
      // error - use replacement character
      out[0] = (char)0xEF;
      out[1] = (char)0xBF;
      out[2] = (char)0xBD;
      out[3] = 0;
      utf8character.m_end = utf8character.m_begin + 3;
   }

   return utf8character;

}


strsize unicode_to_utf8_length(::i64 i)
{
   if (i <0)
   {
      return -1;
   }
   else if (i <= 0x7F)
   {
      return 1;
   }
   else if (i <= 0x07FF)
   {
      return 2;
   }
   else if (i <= 0xFFFF) 
   {
      return 3;
   }
   else if (i <= 0x10FFFF) 
   {
      return 4;
   }
   else
   {
      return -1;
   }
}




//const char * str::utf8_next_add_length(strsize * paddlength, const ::ansi_character * psz)
//{
//
//   char len = 1 + trailingBytesForUTF8(*psz);
//
//   if (len == 0)
//   {
//      *paddlength += 0;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 1)
//   {
//      *paddlength += 1;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 2)
//   {
//      *paddlength += 2;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 3)
//   {
//      *paddlength += 3;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 4)
//   {
//      *paddlength += 4;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 5)
//   {
//      *paddlength += 5;
//      return psz;
//   }
//   if (*psz++ == 0)   throw ::exception(error_invalid_character, "invalid utf8 character");
//   if (len == 6)
//   {
//      *paddlength += 6;
//      return psz;
//   }
//   throw ::exception(error_invalid_character, "invalid utf8 character");
//}


//const char * str::utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc)
//{
//
//   strsize count = 0;
//
//   ::str().utf8_inc_slide(&count, pchSrc);
//
//   ::memcpy_dup(pchDst, pchSrc, count);
//
//   pchSrc += count;
//
//   pchDst += count;
//
//   *pslideback -= count;
//
//   return pchSrc;
//
//}



//const char * str::utf8_dec(const character & character, const ::ansi_character * pszBeg, const ::ansi_character * psz)
//{
//
//   if (psz <= pszBeg)
//   {
//
//      pchar->m_chLen = -1;
//
//      return nullptr;
//
//   }
//
//   if ((*(psz - 1) & 0x80) == 0x00)
//   {
//
//      if ((psz - 1) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-1];
//      pchar->m_sz[1] = '\0';
//      pchar->m_chLen = 1;
//
//      return psz - 1;
//
//   }
//   else if ((*(psz - 2) & 0xE0) == 0xC0)
//   {
//
//      if ((psz - 2) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-2];
//      pchar->m_sz[1] = psz[-1];
//      pchar->m_sz[2] = '\0';
//      pchar->m_chLen = 2;
//
//      return psz - 2;
//
//   }
//   else if ((*(psz - 3) & 0xF0) == 0xE0)
//   {
//
//      if ((psz - 3) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-3];
//      pchar->m_sz[1] = psz[-2];
//      pchar->m_sz[2] = psz[-1];
//      pchar->m_sz[3] = '\0';
//      pchar->m_chLen = 3;
//
//      return psz - 3;
//
//   }
//   else if ((*(psz - 4) & 0xF8) == 0xF0)
//   {
//
//      if ((psz - 4) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-4];
//      pchar->m_sz[1] = psz[-3];
//      pchar->m_sz[2] = psz[-2];
//      pchar->m_sz[3] = psz[-1];
//      pchar->m_sz[4] = '\0';
//      pchar->m_chLen = 4;
//
//      return psz - 4;
//
//   }
//   else if ((*(psz - 5) & 0xFC) == 0xF8)
//   {
//
//      if ((psz - 5) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-5];
//      pchar->m_sz[1] = psz[-4];
//      pchar->m_sz[2] = psz[-3];
//      pchar->m_sz[3] = psz[-2];
//      pchar->m_sz[4] = psz[-1];
//      pchar->m_sz[5] = '\0';
//      pchar->m_chLen = 5;
//
//      return psz - 5;
//
//   }
//   else if ((*(psz - 6) & 0xFE) == 0xFC)
//   {
//
//      if ((psz - 6) < pszBeg)
//      {
//
//         pchar->m_chLen = -1;
//
//         return nullptr;
//
//      }
//
//      pchar->m_sz[0] = psz[-6];
//      pchar->m_sz[1] = psz[-5];
//      pchar->m_sz[2] = psz[-4];
//      pchar->m_sz[3] = psz[-3];
//      pchar->m_sz[4] = psz[-2];
//      pchar->m_sz[5] = psz[-1];
//      pchar->m_sz[6] = '\0';
//      pchar->m_chLen = 6;
//
//      return psz - 6;
//
//   }
//
//   if ((psz - 1) < pszBeg)
//   {
//
//      pchar->m_chLen = -1;
//
//      return nullptr;
//
//   }
//
//   pchar->m_sz[0] = psz[-1];
//   pchar->m_sz[1] = '\0';
//   pchar->m_chLen = 1;
//
//   return psz - 1;
//
//}


const char * utf8_dec(const ::ansi_character * pszBeg, const ::ansi_character * psz)
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


string get_utf8_char(const ::ansi_character * psz)
{

   i32 iLength;
   
   auto iIndex = unicode_index_length(psz, iLength);

   if (iLength < 0)
   {

      return "";

   }

   return string(psz, iLength);

}


string get_utf8_char(const ::ansi_character * psz, const ::ansi_character * pszEnd)
{

   const ::ansi_character * pszNext = unicode_next(psz);

   if (pszNext > pszEnd)
   {

      return "";

   }

   return string(psz, pszNext - psz);

}


bool get_utf8_char(string & strChar, const char *& psz, const ::ansi_character * pszEnd)
{

   const ::ansi_character * pszNext = unicode_next(psz);

   if (pszNext > pszEnd)
   {

      return false;

   }

   strChar = string(psz, pszNext - psz);

   psz = pszNext;

   return true;

}


string get_utf8_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, index i)
{

   if (i > 0)
   {

      while (i != 0)
      {

         unicode_increment(psz);

         if (*psz == '\0')
         {

            return "";

         }

         i--;

      }

      return get_utf8_char(psz);

   }
   else
   {

      while (i != 0)
      {

         psz = unicode_prior(pszBeg, psz);

         if (psz == nullptr)
         {

            return "";

         }
         else if (*psz == '\0')
         {

            return "";

         }

         i++;

      }

      return get_utf8_char(psz);

   }

}


string utf8_next_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, index i)
{

   return get_utf8_char(pszBeg, psz, i + 1);

}


string utf8_previous_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, index i)
{

   return utf8_next_char(pszBeg, psz, -i);

}


i32 str::get_escaped_char(const ::ansi_character * psz, strsize pos, strsize & retPos)
{

   retPos = pos;

   if (psz[pos] == '\\')
   {

      retPos++;

      if (psz[pos + 1] == 'x')
      {

         if (psz[pos + 2] == '{')
         {

            string val;

            if (!get_curly_content(&psz[pos + 2], val))
            {

               return BAD_WCHAR;

            }

            i64 hex = ::hex::to_i64(val);

            strsize val_len = val.get_length();

            if (hex < 0 || hex > 0xFFFF)
            {

               return BAD_WCHAR;

            }

            retPos += val_len + 2;

            return (i32)hex;

         }
         else
         {

            i64 hex = ::hex::to_i64(string(&psz[pos + 2], 2));

            if (i64(strlen(psz)) <= pos + 2 || hex == -1)
            {

               return BAD_WCHAR;

            }

            retPos += 2;

            return (i32)hex;

         }

      }

      return psz[pos + 1];

   }

   return psz[pos];

}


bool str::get_curly_content(const ::ansi_character * psz, string & str)
{

   if (psz[0] != '{') return false;

   const ::ansi_character * pszChar;

   for (pszChar = unicode_next(psz); pszChar != nullptr; unicode_increment(pszChar))
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


bool str::is_simple_natural(const ::ansi_character * pszCandidate, strsize iCount)
{

   if (iCount == 0)
   {

      return false;

   }

   string str(pszCandidate);

   str.trim();

   auto psz = str.c_str();

   if (*psz == '\0')
   {

      return false;

   }

   while (*psz != '\0' && iCount != 0)
   {

      if (!unicode_is_digit(psz))
      {

         return false;

      }

      unicode_increment(psz);

      iCount--;

   }

   return true;

}


bool str::is_natural(const ::string & strParam)
{

   string str(strParam);

   str.trim();

   for (index i = 0; i < str.length(); i++)
   {

      if (!ansi_char_isdigit(str[i]))
      {

         return false;

      }

   }

   return true;

}


bool str::is_integer(const ::string & strParam)
{

   string str(strParam);

   str.trim();

   if (str.case_insensitive_begins_eat("-") || str.case_insensitive_begins_eat("+"))
   {

      return is_natural(str);

   }
   else
   {

      return is_natural(str);

   }

}


void str::consume(const char *& pszParse, const ::string & strToConsume)
{

   strsize len = strToConsume.length();

   if (strncmp(pszParse, strToConsume, len) != 0)
   {

      throw ::exception(error_parsing, "Name does not match expected");

   }

   pszParse += len;

}


bool str::eats(const char *& pszParse, const ::string & strParam)
{

   if (strncmp(pszParse, strParam, strParam.length()) != 0)
   {

      return false;

   }

   pszParse += strParam.length();

   return true;

}


bool str::eats_ci(const char *& pszParse, const ::string & strParam)
{

   if (strnicmp(pszParse, strParam, strParam.length()) != 0)
   {

      return false;

   }

   pszParse += strParam.length();

   return true;

}


void str::consume(const char *& pszParse, const ::ansi_character * psz, const ::ansi_character * pszEnd)
{

   __UNREFERENCED_PARAMETER(pszEnd);
   strsize idx;
   strsize len = strlen(psz);
   for (idx = 0; idx < len; idx++)
   {
      if (pszParse[idx] != psz[idx])
      {
         throw ::exception(error_parsing, "Name does not match expected");
         break;
      }
   }

   pszParse += len;

}


void str::consume(const char *& pszParse, const ::ansi_character * psz, strsize len, const ::ansi_character * pszEnd)
{

   __UNREFERENCED_PARAMETER(pszEnd);

   i32 idx;

   for (idx = 0; idx < len; idx++)
   {

      if (pszParse[idx] != psz[idx])
      {

         throw ::exception(error_parsing, "Name does not match expected");

         break;

      }

   }

   pszParse += len;

}


void str::consume_spaces(const char *& pszParse, ::count iMinimumCount)
{

   auto psz = pszParse;

   i32 i = 0;

   while (unicode_is_whitespace(psz))
   {

      unicode_increment(psz);

      i++;

   }

   if (i < iMinimumCount)
   {

      throw ::exception(error_parsing, "Space is required");

   }

   pszParse = psz;

}


u64 str::consume_natural(string & strParse, u64 uMax, u64 uMin)
{

   const ::ansi_character * pszParse = strParse;

   auto u = consume_natural(pszParse, uMax, uMin);

   strParse = pszParse;

   return u;

}


u64 str::consume_natural(const char *& pszParse, u64 uMax, u64 uMin)
{

   if (uMax < uMin)
   {

      throw ::exception(error_bad_argument, "maximum should be greater than minimum");

   }

   auto psz = pszParse;

   i32 i = 0;

   u64 u;

   while (unicode_is_digit(psz))
   {

      unicode_increment(psz);

      i++;

   }

   if (psz == pszParse)
   {

      throw ::exception(error_parsing, "empty natural found");

   }

   u = ::str().to_u32(string(pszParse, psz - pszParse));

   if (u < uMin)
   {

      throw ::exception(error_parsing, "natural less than minimum");

   }
   else if (u > uMax)
   {

      throw ::exception(error_parsing, "natural greater than maximum");

   }

   pszParse = psz;

   return u;

}


void str::consume_spaces(const char *& pszParse, ::count iMinimumCount, const ::ansi_character * pszEnd)
{

   auto psz = pszParse;

   i32 i = 0;

   while (unicode_is_whitespace(psz))
   {

      unicode_increment(psz);

      if (psz > pszEnd)
      {

         throw ::exception(error_parsing, "premature end");

         break;

      }

      i++;

   }

   if (i < iMinimumCount)
   {

      throw ::exception(error_parsing, "Space is required");

   }

   pszParse = psz;

}


string str::consume_non_spaces(const ::ansi_character *& psz)
{

   return consume_non_spaces(psz, psz + strlen(psz));

}


string str::consume_non_spaces(const ::ansi_character *& pszParse, const ::ansi_character * pszEnd)
{

   auto psz = pszParse;

   while (!unicode_is_whitespace(psz))
   {
      
      unicode_increment(psz);

      if (psz >= pszEnd)
      {

         break;

      }

   }

   string str(pszParse, psz - pszParse);

   pszParse = psz;

   return str;

}


string str::consume_hex(const char *& pszParse)
{
   auto psz = pszParse;
   //      i32 i = 0;
   while (*psz != '\0')
   {
      
      i64 i = unicode_index(pszParse);

      if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'))
      {

         unicode_increment(psz);

      }

   }

   if (psz == pszParse)
   {
      throw ::exception(error_parsing, "no hex consumed");
      return "";
   }
   string str(pszParse, psz - pszParse);
   pszParse = psz;
   return psz;
}


string str::consume_nc_name(const char *& pszParse)
{
   auto psz = pszParse;
   bool start = true;
   while (true)
   {
      const char * ca = psz;
      // first char
      if (start)
      {
         if (!unicode_is_letter(ca) || *ca == '\0')
         {
            throw ::exception(error_parsing, "NCName required here");
            return "";
         }
         start = false;
      }
      else
      {
         if (!unicode_is_letter_or_digit(ca) && *ca != '_' && *ca != '-')
         {
            break;
         }
         unicode_increment(psz);
      }
   }
   string str(pszParse, psz - pszParse);
   pszParse = psz;
   return str;
}

//string consume_quoted_value(const char * & pszParse)
//{

//   ::str().utf8_char utf8char;

//   auto psz = pszParse;
//   utf8char.parse(psz); // quote character
//   if(utf8char.m_chLen != 1)
//   {
//      throw ::exception(error_parsing, "Quote character is required here");
//      return "";
//   }
//   char strUtf8Char = utf8char.m_sz[0];
//   if(strUtf8Char != '\"' && strUtf8Char != '\\')
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
//      if(utf8char.m_chLen == 1 && utf8char.m_sz[0] == strUtf8Char)
//         break;

//   }
//   str = string(&psz[iPosStart], iPos - iPosStart - 1);
//   pszParse = &psz[iPos];
//   return str;
//}


string str::consume_quoted_value(const char *& pszParse, const ::ansi_character * pszEnd)
{

   auto psz = pszParse;

   pszEnd = psz + strlen(pszParse);

   if (*psz != '\"' && *psz != '\'')
   {

      throw ::exception(error_parsing, "Quote character is required here");

      return "";

   }

   char qc = *psz;

   psz++;

   const ::ansi_character * pszValueStart = psz;

   while (*psz != qc)
   {

   skip:

      unicode_increment(psz);

      if (psz > pszEnd || *psz == '\0')
      {

         throw ::exception(error_parsing, "Quote character is required here, premature end");

         return "";

      }

      if (*psz == '\\')
      {

         unicode_increment(psz);

         if (psz > pszEnd)
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

   auto pend = p + str.length();

   while (*p)
   {

      if (*p == '\\')
      {

         if (p[1] == '\\')
         {

            memmove(p, p + 1, pend - p);
         }
         else if (p[1] == '\"')
         {

            memmove(p, p + 1, pend - p);

         }

      }

      p++;

   }

   str.release_string_buffer();

   return str;

}


void str::no_escape_consume_quoted_value(const char *& pszParse, const ::ansi_character * pszEnd, char ** ppsz, strsize & iBufferSize)
{

   const ::ansi_character * psz = pszParse;

   if (*psz != '\"' && *psz != '\\')
   {

      throw ::exception(error_parsing, "Quote character is required here");

      return;

   }

   char qc = *psz;

   psz++;

   const ::ansi_character * pszValueStart = psz;

   while (*psz != qc)
   {

      unicode_increment(psz);

      if (psz > pszEnd)
      {

         throw ::exception(error_parsing, "Quote character is required here, premature end");

         return;

      }

   }

   strsize iNewBufferSize = psz - pszValueStart;

   if (iNewBufferSize > iBufferSize)
   {

      *ppsz = (char *)memory_allocate(iNewBufferSize + 1);

   }

   ansi_count_copy(*ppsz, pszValueStart, iNewBufferSize);

   (*ppsz)[iNewBufferSize] = '\0';

   iBufferSize = iNewBufferSize;

   psz++;

   pszParse = psz;

}


string str::no_escape_consume_quoted_value(const char *& pszParse, const ::ansi_character * pszEnd)
{

   const ::ansi_character * psz = pszParse;

   if (*psz != '\"' && *psz != '\\')
   {

      throw ::exception(error_parsing, "Quote character is required here");

      return{};

   }

   char qc = *psz;

   psz++;

   const ::ansi_character * pszStart = psz;

   while (*psz != qc)
   {

      unicode_increment(psz);

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


void str::skip_quoted_value_ex2(const char *& pszParse, const ::ansi_character * pszEnd)
{

   auto psz = pszParse;

   if (*psz != '\"' && *psz != '\\')
   {

      throw ::exception(error_parsing, "Quote character is required here");

      return;

   }

   char qc = *psz;

   psz++;

   const ::ansi_character * pszValueStart = psz;

   while (*psz != qc)
   {

      unicode_increment(psz);

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

      m_iPos++;


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

   void append(const ::ansi_character * psz, strsize iSize)
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

string str::consume_quoted_value_ex(const char *& pszParse, const ::ansi_character * pszEnd)
{
   auto psz = pszParse;
   char qc = *psz; // quote character
   if (qc != '\"' && qc != '\'')
   {
      throw ::exception(error_parsing, "Quote character is required here, premature end");
      return "";
   }
   psz++;
   const ::ansi_character * pszValueStart = psz;
   //const ::ansi_character * pszValueEnd = psz;
   const ::ansi_character * pszNext = psz;
   string str;
   while (true)
   {
      pszNext = unicode_next(psz);
      if (pszNext > pszEnd)
      {
         throw ::exception(error_parsing, "Quote character is required here, premature end");
         return "";
      }
      if (*psz == '\0')
      {
         throw ::exception(error_parsing, "Quote character is required here, premature end");
         return "";
      }
      else if (*psz == qc)
      {
         psz++;
         break;
      }
      else if (*psz == '\\')
      {
         psz = pszNext;
         pszNext = unicode_next(psz);
         if (pszNext > pszEnd)
         {
            throw ::exception(error_parsing, "Quote character is required here, premature end");
            return "";
         }
         if (*psz == 'n')
         {
            str += '\n';
         }
         else if (*psz == 't')
         {
            str += '\t';
         }
         else if (*psz == 'r')
         {
            str += '\r';
         }
         else if (*psz == 'u')
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

                  ::wd32_character uni = (::wd32_character)decode_utf16_pair(u);
                  string strUtf8 = wd32_to_ansi_str(&uni, 1);
                  str += strUtf8;

               }

            }
            else
            {

               ::wd32_character uni = u[0];
               string strUtf8 = wd32_to_ansi_str(&uni, 1);
               str += strUtf8;

            }
            pszNext = psz;
         }
         else if (*psz == '\"')
         {
            str += '\"';
         }
         else
         {
            str.append(psz, pszNext - psz);
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

void str::skip_quoted_value_ex(const char *& pszParse, const ::ansi_character * pszEnd)
{
   auto psz = pszParse;
   char qc = *pszParse; // quote character
   if (qc != '\"' && qc != '\'')
   {
      throw ::exception(error_parsing, "Quote character is required here, premature end");
      return;
   }
   psz++;
   const ::ansi_character * pszValueStart = psz;
   //const ::ansi_character * pszValueEnd = psz;
   const ::ansi_character * pszNext = psz;
   while (true)
   {
      pszNext = unicode_next(psz);
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
         pszNext = unicode_next(psz);
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
               pszNext = unicode_next(psz);
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


string str::consume_spaced_value(string & str)
{

   strsize i = 0;

   while (i < str.length() && ansi_char_isspace(str[i]))
   {

      i++;

   }

   if (i >= str.length())
   {

      str.Empty();

      return "";

   }

   strsize iStart = i;

   while (i < str.length() && !ansi_char_isspace(str[i]))
   {
      i++;
   }

   string strResult = str.Mid(iStart, i - iStart);

   str = str.Mid(i);

   return strResult;


}

string str::consume_spaced_value(const char *& psz)
{

   string str(psz);

   strsize iOldLen = str.length();

   string strResult = consume_spaced_value(str);

   psz += iOldLen - str.length();

   return strResult;

}

string str::consume_spaced_value(const char *& psz, const ::ansi_character * pszEnd)
{

   string str(psz, pszEnd - psz);

   strsize iOldLen = str.length();

   string strResult = consume_spaced_value(str);

   psz += iOldLen - str.length();

   return strResult;

}


string str::consume_command_line_argument(string & str)
{

   string strResult;

   strsize iFind1 = str.find('\"');

   strsize iFind2 = str.find('\'');

   auto pFind = minimum_non_negative(iFind1, iFind2);

   if (::is_null(pFind))
   {

      strResult = consume_spaced_value(str);

   }
   else
   {

      char chSeparator = str[iFind];

      strsize i = 0;

      while (i < iFind && ansi_char_isspace(str[i]))
      {
         i++;
      }

      if (i < iFind)
      {

         strsize iStart = i;

         while (i < iFind && !ansi_char_isspace(str[i]))
         {
            i++;
         }

         strResult = str.Mid(iStart, i - iStart);

         str = str.Mid(i);

      }
      else
      {

         iFind++;

         strsize iFind2 = str(pFind).find(chSeparator);

         if (iFind2 < 0)
         {

            strsize iStart = iFind;

            i = iStart;

            while (i < str.length() && !ansi_char_isspace(str[i]))
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


string str::consume_command_line_argument(const char *& psz)
{

   string str(psz);

   strsize iOldLen = str.length();

   string strResult = consume_command_line_argument(str);

   psz += iOldLen - str.length();

   return strResult;

}

string str::consume_command_line_argument(const char *& psz, const ::ansi_character * pszEnd)
{

   string str(psz, pszEnd - psz);

   strsize iOldLen = str.length();

   string strResult = consume_command_line_argument(str);

   psz += iOldLen - str.length();

   return strResult;

}


string str::consume_c_quoted_value(const char *& pszParse, const ::ansi_character * pszEnd)
{

   auto psz = pszParse;

   if (pszEnd == nullptr)
   {

      pszEnd = pszParse + strlen(pszParse);

   }

   string strQuoteChar = get_utf8_char(psz);

   if (strQuoteChar != "\"" && strQuoteChar != "\\")
   {

      throw ::exception(error_parsing, "Quote character is required here");

      return "";

   }

   string strCurrentChar;

   string str;

   string strPreviousChar;

   while (psz < pszEnd)
   {

      unicode_increment(psz);

      strPreviousChar = strCurrentChar;

      strCurrentChar = get_utf8_char(psz);

      //string str = utf8_to_unicode(qc2);

      if (strCurrentChar.is_empty())
      {

         throw ::exception(error_parsing, "Quote character is required here, premature end");

         return "";

      }

      if (strPreviousChar == "\\")
      {

         str += strCurrentChar;

         strCurrentChar.Empty();

      }
      else if (strCurrentChar == "\\")
      {

      }
      else
      {

         if (strCurrentChar == strQuoteChar)
         {

            break;

         }

         str += strCurrentChar;

      }

   }

   unicode_increment(psz);

   pszParse = psz;

   return str;

}


string str::token(string & str, const ::string & strSeparatorText, bool bWithSeparator)
{

   auto pFind = str.find(strSeparatorText);

   string strToken;

   if (::is_set(pFind))
   {

      if (bWithSeparator)
      {

         iFind += strlen(strSeparatorText);

         strToken = str(0, pFind);

         str = str(pFind);

      }
      else
      {

         strToken = str(0, pFind);

         iFind += strlen(strSeparatorText);

         str = str(pFind);

      }

   }

   return strToken;

}


string str::line(string & str, bool bNewLine)
{

   auto iFind1 = str.find('\r');

   auto iFind2 = str.find('\n');

   auto pFind = minimum_non_negative(iFind1, iFind2);

   string strToken;

   if (::is_null(pFind))
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

         strToken = str(0, pFind);

      }

      str = str.Mid(iEnd);

   }

   return strToken;

}


bool str::begins_consume(const char *& pszParse, const ::string & str)
{

   //strsize idx;

   strsize len = str.length();

   if (strncmp(pszParse, str, len) != 0)
   {

      return false;

   }

   pszParse += len;

   return true;

}


bool str::xml_is_comment(const ::string & strParse)
{

   return strParse[0] == '<' && strParse[1] == '!' && strParse[2] == '-';

}


string str::xml_consume_comment(const char *& pszParse)
{

   string str;

   ::str().consume(pszParse, "<!--");

   while (pszParse[0] != '-' || pszParse[1] != '-' || pszParse[2] != '>')
   {

      if (*pszParse == '\0')
      {

         break;

      }

      str += *pszParse;

      unicode_increment(pszParse);

   }

   consume(pszParse, "-->");

   return str;

}


string str::pad(const ::string & strParam, ::count iLen, const ::string & strPattern, enum_pad epad)
{

   string str(strParam);

   if (strPattern.is_empty())
   {

      return str;

   }

   i32 i = 0;

   if (epad == e_pad_left)
   {

      while (str.length() < iLen)
      {

         if (strPattern[i] == '\0')
         {

            i = 0;

         }

         str = strPattern[i] + str;

         i++;

      }

   }
   else if (epad == e_pad_right)
   {

      while (str.length() < iLen)
      {

         if (strPattern[i] == '\0')
         {

            i = 0;

         }

         str = str + strPattern[i];

         i++;

      }

   }

   return str;

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
      if (!str.length())
      {
         str = "0";
      }
      return str;
   }*/


i32 str::to_i32(const ::string & str)
{

   return ansi_to_i32(str);

}


u32 str::to_u32(const ::string & str)
{

   return (u32)ansi_to_i64(str);

}


i64 str::to_i64(const ::string & str)
{

   i32 i = 0;

   for (; i < str.length() && character_isspace(str[i]); i++);

   bool bNegative = str[i] == '-';

   if (bNegative)
   {

      i++;

   }

   u64 u = 0;

   for (; i < str.length() && isdigit(str[i]); i++)
   {

      u = u * 10 + str[i] - 48;

   }

   if (bNegative)
   {

      return -(i64)u;

   }
   else
   {

      return (i64)u;

   }

}


//i64 to_i64(const ::string & str)
//{

//   i32 i = 0;

//   for (; *psz != '\0' && i < 30 && ansi_char_isspace(*psz); i++, psz++);

//   bool bNegative = *psz == '-';

//   if(bNegative)
//      psz++;

//   u64 u = 0;

//   for(; *psz != '\0' && i < 30 && ansi_char_isdigit(*psz); psz++, i++)
//   {
//      u = u * 10 + *psz - 48;
//   }

//   if(bNegative)
//      return -(i64) u;
//   else
//      return (i64) u;

//}

u64 str::to_u64(const ::string & str)
{

   i32 i = 0;

   for (; i < str.length() && character_isspace(str[i]); i++);

   u64 u = 0;

   for (; i < str.length() && isdigit(str[i]); i++)
   {
      u = u * 10 + str[i] - 48;
   }

   return u;

}

//u64 to_u64(const ::string & strParam)
//{

//   i32 i = 0;

//   for (; *psz != '\0' && i < 30 && character_isspace(*psz); i++, psz++);

//   u64 u = 0;

//   for(; *psz != '\0' && i < 30 && isdigit(*psz); psz++, i++)
//   {
//      u = u * 10 + *psz - 48;
//   }

//   return u;

//}



void str::increment_digit_letter(string & str)
{

   strsize i = str.length() - 1;

   while (i >= 0)
   {

      if (str[i] >= '0' && str[i] <= '8')
      {
         str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.length() - i - 1);
         break;
      }
      else if (str[i] == '9')
      {
         str = str.Left(i) + string((char)('a')) + str.Right(str.length() - i - 1);
         break;
      }
      else if (str[i] >= 'a' && str[i] <= 'y')
      {
         str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.length() - i - 1);
         break;
      }
      else if (str[i] == 'z')
      {
         str = str.Left(i) + string((char)('0')) + str.Right(str.length() - i - 1);
         i--;
      }
   }
}


//bool str::while_begins_with_chars_eat(string & str, const ::ansi_character * pszChars)
//{
//
//   i32 i = 0;
//   for (i = 0; i < str.length(); i++)
//   {
//      if (strchr(pcszChars, str[i]) == nullptr)
//
//         break;
//   }
//   str = str.Mid(i);
//   return i > 0;
//
//}
//
//
//bool str::while_begins_with_chars_eat_ci(string & str, const ::ansi_character * pszChars) // case insensitive
//{
//
//   i32 i = 0;
//   for (i = 0; i < str.length(); i++)
//   {
//      if (strchr(pcszChars, tolower(str[i])) == nullptr)
//
//         break;
//   }
//   str = str.Mid(i);
//   return i > 0;
//}


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


//bool str::replace_prefix(::string & str, const ::ansi_character * pszPrefixReplacement, const ::ansi_character * pszPrefix)
//{
//
//   if (!str.begins_eat(pszPrefix))
//   {
//
//      return false;
//
//   }
//
//   str = ::string(pszPrefixReplacement) + str;
//
//   return true;
//
//}
//
//
//bool str::replace_prefix_ci(::string & str, const ::ansi_character * pszPrefixReplacement, const ::ansi_character * pszPrefix)
//{
//
//   if (!str.case_insensitive_begins_eat(pszPrefix))
//   {
//
//      return false;
//
//   }
//
//   str = ::string(pszPrefixReplacement) + str;
//
//   return true;
//
//}


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
//   bool case_insensitive_begins(const unichar * pcsz, const unichar * pcszPrefix)
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
//      while(ch().to_lower_case(*pcsz) == ch().to_lower_case(*pcszPrefix))
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
//   bool case_insensitive_begins(const wstring & wstr, const unichar * pcszPrefix)
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
//      while(*pcsz && ch().is_space_char(*pcsz))
//
//         pcsz++;
//
//      if(!*pcsz)
//
//         return false;
//      while(ch().to_lower_case(*pcsz) == ch().to_lower_case(*pcszPrefix))
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

string str::ansi_lower(const ::string & str)
{

   return str.lowered();

}


string str::ansi_upper(const ::string & str)
{

   return str.uppered();

}


/** End \file Utility.cpp
**   \date  2004-02-13
**   \author grymse@alhem.net
**/


bool str::simple_escaped(const ::string & str, strsize pos)
{

   if (pos == 0)
   {

      return false;

   }

   return str[pos - 1] == '\\' && !simple_escaped(str, pos - 1);

}


bool str::trim(string & str)
{

   strsize iLen = str.length();

   str.trim();

   return iLen != str.length();

}


bool str::_008Trim(string & str)
{

   ::count c = 1;

   bool bTrim = false;

   while (c > 0)
   {

      c = 0;

      if (trim_any_quotes(str))
      {

         c++;

         bTrim = true;

      }

      if (trim(str))
      {

         c++;

         bTrim = true;

      }

   }

   return bTrim;

}


bool str::trim_any_quotes(string & str)
{

   bool bTrim = false;

   while (paired_trim(str, '\'') || paired_trim(str, '\"'))
   {

      bTrim = true;

   }

   return bTrim;

}


bool str::paired_trim(string & str, char ch)
{

   if (str.length() <= 1)
   {

      return false;

   }

   if (str[0] != ch || str.last_char() != ch)
   {

      return false;

   }

   str = str.Mid(1, str.length() - 2);

   return true;

}


///
/// q(between quotes :-) )-valid string
/// from:http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
/// more invalid strings to test: http://stackoverflow.com/questions/1301402/example-invalid-utf8-string
///
bool str::utf8_check_is_valid(const string & string)
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
string str::q_valid(string str)
{

   if (str.is_empty())
   {

      return str;

   }

   if (!utf8_check_is_valid(str))
   {

      str = multibyte_to_utf8(CodePageAnsi, str);

      if (!utf8_check_is_valid(str))
      {

         return "";

      }

   }

   return str;

}


string str::signed_double(double d)
{

   if (d > 0.0)
   {

      return "+" + as_string(d);

   }
   else if (d < 0.0)
   {

      return as_string(d);

   }
   else
   {

      return "0.0";

   }

}

string str::signed_int(int i)
{

   if (i > 0)
   {

      return "+" + as_string(i);

   }
   else if (i < 0)
   {

      return as_string(i);

   }
   else
   {

      return "0";

   }

}


bool str::is_true(string str)
{

   str.trim();

   if (str.is_empty())
   {

      return false;

   }

   if (str.case_insensitive_order("yes") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("true") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("on") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("enable") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("enabled") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("check") == 0)
   {

      return true;

   }

   if (str.case_insensitive_order("checked") == 0)
   {

      return true;

   }

   for (index i = 0; i < str.length(); i++)
   {

      if (i == 0 && (str[i] == '+' || str[i] == '-'))
      {

      }
      else if (!ansi_char_isdigit(str[i]))
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




string str::block(char ch, i32 iSize)
{

   string str;

   auto psz = str.get_string_buffer(iSize);

   for (i32 i = 0; i < iSize; i++)
   {

      psz[i] = ch;

   }

   str.release_string_buffer(iSize);

   return str;

}


void str::fill(string & str, char ch)
{

   auto len = str.length();

   auto psz = str.get_string_buffer();

   for (i32 i = 0; i < len; i++)
   {

      psz[i] = ch;

   }

   str.release_string_buffer(len);

}
//
//
//} // namespace str

//
//::string as_string(const float & f)
//{
//
//   char sz[256];
//
//   sprintf(sz, "%f", f);
//
//   str = sz;
//
//   str.replace_with(".", ",");
//
//}
//
//
//::string as_string(const double & d)
//{
//
//   char sz[256];
//
//   sprintf(sz, "%f", d);
//
//   str = sz;
//
//   str.replace_with(".", ",");
//
//}
//
//


//namespace str
//{


void str::fix_eol(string & str)
{

   str.replace_with("\n", "\r\n");

   str.replace_with("\n", "\n\r");

   str.replace_with("\n", "\r");

#ifdef WINDOWS

   str.replace_with("\r\n", "\n");

#endif

}


string & str::zero_pad(string & str, strsize lenPad)
{

   ::ansi_zero_pad(str.get_string_buffer(str.length() + lenPad), lenPad);

   str.release_string_buffer();

   return str;

}


string str::zero_padded(const ::string & strSrc, strsize lenPad)
{

   string str(strSrc);

   if (lenPad > str.length())
   {

      ::ansi_zero_pad(str.get_string_buffer(lenPad), lenPad);

      str.release_string_buffer(lenPad);

   }

   return str;

}


void str::get_lines(::string_array & stra, ::string & str, const ::string & strPrefix, bool bFinal, ::particle * pparticleSynchronization, ::file::file * pfileLog)
{

   auto iLimit = str.rear_find("\n");

   if (iLimit < 0)
   {

      if(bFinal)
      {

         iLimit = str.length();

         if(iLimit <= 0)
         {

            return;

         }

      }
      else
      {

         return;

      }

   }

   strsize iLast = -1;

   while(true)
   {

      strsize iFindNext = str.find('\n', iLast + 1);

      if(iFindNext < 0)
      {

         if(bFinal)
         {

            iFindNext = str.length();

            if(iFindNext >= iLast)
            {

               break;

            }

         }
         else
         {

            break;

         }

      }
      else if(iFindNext > iLimit)
      {

         break;

      }

      string strLine = str.Mid(iLast + 1, iFindNext - iLast - 1);

      string strPrefixedLine;

      strPrefixedLine = strPrefix + strLine;

      if (::is_set(pparticleSynchronization))
      {

         pparticleSynchronization->_lock();

      }

      stra.add(strPrefixedLine.c_str());

      if(::is_set(pparticleSynchronization))
      {

         pparticleSynchronization->unlock();

      }

      if(::is_set(pfileLog) && pfileLog->has_ok_flag())
      {

         try
         {

            pfileLog->write(strPrefixedLine + "\n");

         }
         catch(...)
         {

         }

      }

      if(iFindNext >= iLimit)
      {

         break;

      }

      iLast = iFindNext;

      if(iLast >= iLimit)
      {

         break;

      }

   }

   str.erase(0, iLimit + 1);

}


//::string as_string(const ::string_stream & strstream)
//{
//
//   return strstream.as_string();
//
//}


//template < typename FILE >
//::string as_string(const ::text_stream < FILE > & strstream)
//{
//
//   return strstream.as_string();
//
//}


//ansi_string & str::assign(ansi_string & ansistrDst, const property & property)
//{
//
//   ansistrDst.assign(property.string());
//
//   return ansistrDst;
//
//}
//
//
//
//
//


//namespace str
//{

template < typename TYPE >
class get_char_type
{
public:

   using CHAR_TYPE = typename TYPE::CHAR_TYPE;

};

   template < > class get_char_type < const char * > { public: using CHAR_TYPE = char; };
   template < > class get_char_type < char * > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < const char[n] > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < char[n] > { public: using CHAR_TYPE = char; };


//bool str::begins_eat(::payload & payload, const ::string & strPrefix)
//{
//
//   string str = payload.string();
//
//   if (!begins_eat(str, strPrefix))
//   {
//
//      return false;
//
//   }
//
//   payload = str;
//
//   return true;
//
//}
//
//
//bool str::case_insensitive_begins_eat(::payload & payload, const ::string & strPrefix)
//{
//
//   string str = payload.string();
//
//   if (!case_insensitive_begins_eat(str, strPrefix))
//   {
//
//      return false;
//
//   }
//
//   payload = str;
//
//   return true;
//
//}
//
//
//bool str::begins_eat(property & property, const ::string & strPrefix)
//{
//
//   return begins_eat((::payload &)property, strPrefix);
//
//}
//
//
//bool str::case_insensitive_begins_eat(property & property, const ::string & strPrefix)
//{
//
//   return case_insensitive_begins_eat((::payload &)property, strPrefix);
//
//}


//ansi_string & str::assign(ansi_string & ansistrDst, const atom & atom)
//{
//
//   ansistrDst.assign(atom);
//
//   return ansistrDst;
//
//}
//
//
//wd16_string & str::assign(wd16_string & widestrDst, const atom & atom)
//{
//
//   widestrDst.assign(atom);
//
//   return widestrDst;
//
//}
//
//
//wd32_string & str::assign(wd32_string & widestrDst, const atom & atom)
//{
//
//   widestrDst.assign(atom);
//
//   return widestrDst;
//
//}
//
//
//
//
//
//ansi_string & str::assign(ansi_string & ansistrDst, const ::payload & payload)
//{
//
//   ansistrDst.assign(payload);
//
//   return ansistrDst;
//
//}
//
//
//wd16_string & str::assign(wd16_string & widestrDst, const property & property)
//{
//
//   widestrDst.assign(property.string());
//
//   return widestrDst;
//
//}
//
//
//wd32_string & str::assign(wd32_string & widestrDst, const property & property)
//{
//
//   widestrDst.assign(property.string());
//
//   return widestrDst;
//
//}
//
//
//
//
//wd16_string & str::assign(wd16_string & widestrDst, const ::payload & payload)
//{
//
//   widestrDst.assign(payload.string());
//
//   return widestrDst;
//
//}
//
//
//wd32_string & str::assign(wd32_string & widestrDst, const ::payload & payload)
//{
//
//   widestrDst.assign(payload.string());
//
//   return widestrDst;
//
//}
//
//
//ansi_string & str::assign(ansi_string & ansistrDst, const type & type)
//{
//
//   ansistrDst.assign(type);
//
//   return ansistrDst;
//
//}
//
//
//wd16_string & str::assign(wd16_string & widestrDst, const type & type)
//{
//
//   widestrDst.assign(type);
//
//   return widestrDst;
//
//}
//
//
//wd32_string & str::assign(wd32_string & widestrDst, const type & type)
//{
//
//   widestrDst.assign(type);
//
//   return widestrDst;
//
//}
//
//

