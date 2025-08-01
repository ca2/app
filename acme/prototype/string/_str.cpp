#include "framework.h"
//#include "hex.h"
#include "international.h"
#include "acme/exception/parsing.h"
#include "acme/filesystem/file/file.h"
//#include "acme/filesystem/file/text_stream.h"
//#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/string/str.h"
//#include "string.h"
#include <stdio.h>
#include <string.h>


#ifdef LINUX
////#include <ctype.h>
#endif
//bool is_high_surrogate(unsigned short u)
//{
//   return u >= 0xD800 && u <= 0xDBFF;
//
//}
//bool is_low_surrogate(unsigned short u)
//{
//   return u >= 0xDC00 && u <= 0xDFFF;
//}
// bool is_surrogated(unsigned int character)
//{
//   return 0x10000 <= character && character <= 0x10FFFF;
//}
// void str::encode_utf16_pair(unsigned int character, unsigned short *units)
//{
//   unsigned int code;
//   ASSERT(utf32_is_surrogated(character));
//   code = (character - 0x10000);
//   units[0] = 0xD800 | (code >> 10);
//   units[1] = 0xDC00 | (code & 0x3FF);
//}

//namespace str
//{
//
//    enum_error g_eerror = ::str::e_error_none;


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
//int str::compare(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//
//   return strcmp(str1, str2);
//
//}
//
//
////template < >
//int str::case_insensitive_order(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//
//   return case_insensitive_ansi_compare(str1, str2);
//
//}
//
//
////template < >
//bool str::equals(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//
//   return compare(str1, str2) == 0;
//
//}

//
//template < >
//bool str::case_insensitive_equals(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//   return case_insensitive_order(scopedstr1, psz2) == 0;
//}

////template < >
//string  str::equals_get(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2, const ::scoped_string & scopedstrGetOnEqual, const ::scoped_string & scopedstrGetOnDifferent)
//{
//   return equals(str1, str2) ? strGetOnEqual : strGetOnDifferent;
//}
//
//
////template < >
//string  str::equals_ci_get(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2, const ::scoped_string & scopedstrGetOnEqual, const ::scoped_string & scopedstrGetOnDifferent)
//{
//
//   return equals(str1, str2) ? strGetOnEqual : strGetOnDifferent;
//
//}


//template < >
//bool str::begins(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)
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

//bool str::begins_with(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)
//{
//
//   return begins(str, strPrefix);
//
//}

//bool str::begins(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)

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

//bool str::begins_with(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)

//{
//   return begins(str, pcszPrefix);

//}

//template < >
//bool str::case_insensitive_begins(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)
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
bool str::begins_ci_iws(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)
{

   if (scopedstr.is_empty())
   {

      if (scopedstrPrefix.is_empty())
      {

         return true;

      }
      else
      {

         return false;

      }

   }

   ::string str(scopedstr);

   auto pcsz = str.c_str();

   while (*pcsz && ansi_char_isspace(*pcsz))

      pcsz++;

   if (!*pcsz)
   {

      return false;

   }

   auto pcszPrefix = scopedstrPrefix.c_str();

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
//bool str::begins_ci_iws(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPrefix)

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
//         wstr.empty();
//
//      }
//
//      return false;
//
//   }
//
//   wstrBefore = wstr(0, pFind);
//
//   wstr = wstr.substr(iFind + wstrSeparator.length());
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
//      character_count iLen = strPrefix.length();
//
//      if(str.left(iLen) == pcszPrefix)
//
//      {
//         str = str.substr(iLen);
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
//      character_count iLen = strPrefix.length();
//
//      if(str.left(iLen).case_insensitive_order(pcszPrefix) == 0)
//
//      {
//         str = str.substr(iLen);
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
//         str.empty();
//         return true;
//      }
//      else
//      {
//         return case_insensitive_begins_eat(str, string(pcszPrefix) + pszSeparator);
//
//      }
//   }

   //bool ends(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSuffix)

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

   //   int iLen = strSuffix.length();
   //   if(str.right(iLen) == pcszSuffix)

   //   {
   //   return true;
   //   }
   //   return false;*/
   //}

   //bool case_insensitive_ends(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSuffix)

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


//   bool case_insensitive_ends(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSuffix)
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
//      character_count iLen = strSuffix.length();
//
//      if(str.right(iLen).case_insensitive_order(pcszSuffix) == 0)
//
//      {
//
//         str = str.left(str.length() - iLen);
//         return true;
//
//      }
//
//      return false;
//
//   }

   //void str::copy(string & str, const ::scoped_string & scopedstr, int iCount)
   //{

   //   string strCopy(pcsz, iCount);

   //   str = strCopy;
   //}


string str::replace_with(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrParam, character_count iStart)
{

   string str(scopedstrParam);

   str.replace_with(scopedstrOld, scopedstrNew, iStart);

   return str;

}


::collection::index  str::find_first(const string_array & straSearch, ::collection::index & iFound, const ::scoped_string & scopedstr, ::collection::index iStart)
{

   ::collection::index iFind = -1;

   iFound = -1;

   for (::collection::index i = 0; i < straSearch.get_count(); i++)
   {

      if (straSearch[i].has_character())
      {

         ::collection::index iSearch = scopedstr.find_index(straSearch[i], iStart);

         if (iSearch >= 0 && iSearch >= iStart && (iSearch < iFind || ::not_found(iFind)))
         {

            iFind = iSearch;
            iFound = i;

         }

      }

   }

   return iFind;

}


string str::random_replace(::particle * pparticle, const string_array & straNew, const string_array & straOld, const ::scoped_string & scopedstrParam)
{

   string str(scopedstrParam);

   ::collection::index iFind;

   ::collection::index iFound;

   ::collection::index iStart = 0;

   while ((iFind = find_first(straOld, iFound, str, iStart)) >= 0)
   {

      if (iFind < iStart)
      {

         throw ::parsing_exception("random replace error");

         return "";

      }

      ::collection::index i = (::collection::index)(rand() % straNew.get_size());

      str = str(0, iFind) + straNew[i] + str.substr(iFind + straOld[iFound].length());

      iFind += straNew[i].length();

      iStart = iFind;

   }

   return str;
}


::collection::count str::utf8_replace_with(string & str, const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrOld, character_count iStart)
{

   ::collection::count c = 0;

   ::collection::index iPos = iStart;

   ::collection::count iReplaceLen = -1;

   ::collection::count iFindLen = -1;

   while (true)
   {

      iPos = utf8_find(scopedstrOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = scopedstrNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = scopedstrOld.length();

      }

      str = str.left(iPos) + scopedstrNew + str.substr(iPos + iFindLen);

      iPos += iReplaceLen;

      c++;

   }

   return c;

}


string str::utf8_replace_with(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, character_count iStart)
{

   ::collection::index iPos = iStart;

   string str(scopedstrParam);

   ::collection::count iReplaceLen = -1;

   ::collection::count iFindLen = -1;

   while (true)
   {

      iPos = utf8_find(scopedstrOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = scopedstrNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = scopedstrOld.length();

      }

      str = str.left(iPos) + scopedstrNew + str.substr(iPos + iFindLen);

      iPos += iReplaceLen;

   }

   return str;
}


string str::case_insensitive_replace_with(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, character_count iStart)
{

   ::collection::index iPos = iStart;

   string str(scopedstrParam);

   ::collection::count iReplaceLen = -1;

   ::collection::count iFindLen = -1;

   while (true)
   {

      iPos = case_insensitive_find(scopedstrOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = scopedstrNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = scopedstrOld.length();

      }

      str = str.left(iPos) + scopedstrNew + str.substr(iPos + iFindLen);

      iPos += iReplaceLen;

   }

   return str;
}


::collection::count str::replace_with_ci_count(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, character_count iStart)
{

   ::collection::index iPos = iStart;

   string str(scopedstrParam);

   ::collection::count iReplaceLen = -1;

   ::collection::count iFindLen = -1;

   ::collection::count c = 0;

   while (true)
   {

      iPos = case_insensitive_find(scopedstrOld, str, iPos);

      if (iPos < 0)
      {

         break;

      }

      if (iReplaceLen < 0)
      {

         iReplaceLen = scopedstrNew.length();

      }

      if (iFindLen < 0)
      {

         iFindLen = scopedstrOld.length();

      }

      str = str.left(iPos) + scopedstrNew + str.substr(iPos + iFindLen);

      iPos += iReplaceLen;

      c++;

   }

   return c;

}


::collection::index str::case_insensitive_find(const ::scoped_string & scopedstrFind, const ::scoped_string & scopedstr, ::collection::index iStart)
{

   if (scopedstrFind.length() > (scopedstr.length() - iStart))
   {

      return -1;

   }

   string strFindLow(&((const_char_pointer )scopedstrFind)[0], scopedstrFind.length()); // avoid optimized read only string copy

   strFindLow.make_lower();

   string strLow(&((const_char_pointer )scopedstr)[iStart], scopedstr.length() - iStart); // avoid optimized read only string copy

   strLow.make_lower();

   auto iFind = strLow.find_index(strFindLow);

   if (::not_found(iFind))
   {

      return -1;

   }

   return iStart + iFind;

}


//index str::case_insensitive_find(const ::scoped_string & scopedstrFind, const ::scoped_string & scopedstrParam, ::collection::index iStart)
//{

//   ::collection::count iFindLen = scopedstrFind.length();

//   ::collection::count iLen = strlen(&psz[iStart]);

//   if (iFindLen > iLen)
//   {

//      return -1;

//   }

//   if(iFindLen < 256)
//   {

//      char szFind[256];

//      ::memory_copy(szFind, scopedstrFind, iFindLen + 1);

//      make_lower(szFind);

//      if(iLen < 256)
//      {

//         char sz[256];

//         ::memory_copy(sz, &psz[iStart], iLen + 1);

//         make_lower(sz);

//         const ::scoped_string & scopedstrOld = strstr(sz, szFind);

//         if (scopedstrOld == nullptr)
//         {

//            return -1;

//         }

//         return iStart + (scopedstrOld - sz);

//      }
//      else
//      {

//         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

//         strLow.make_lower();

//         psz = strLow;

//         const ::scoped_string & scopedstrOld = strstr(scopedstr, szFind);

//         if (scopedstrOld == nullptr)
//         {

//            return -1;

//         }

//         return iStart + (scopedstrOld - psz);

//      }

//   }
//   else
//   {

//      string strFindLow(&((const_char_pointer )scopedstrFind)[0], iFindLen); // avoid optimized read only string copy

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


//index str::case_insensitive_find(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstr, ::collection::index iStart)
//{

//   ::collection::count iFindLen = scopedstrOld.length();

//   index iLen = str.length() - iStart;

//   if (iLen < iFindLen)
//   {

//      return -1;

//   }

//   int len1;
//   int len2;

//   const ::scoped_string & scopedstr1 = str;

//   psz1 += iStart;

//   const ::scoped_string & scopedstr2 = scopedstrOld;

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

//         if(ch().to_lower_case(ch().uni_index_len(scopedstrC1, len1)) == ch().to_lower_case(ch().uni_index_len(scopedstrC2, len2)))
//         {

//            pszC1 += len1;
//            pszC2 += len2;
//            if(*pszC2 == '\0')
//            {
//               return psz1 - (const_char_pointer ) str;
//            }
//            if(*pszC1 == '\0')
//            {
//               return -1;
//            }
//         }
//         else
//         {
//            ch().uni_index_len(scopedstr1,len1);
//            psz1 += len1;
//            break;
//         }
//      }

//   }

//   return -1;

//}


//index str::case_insensitive_find(const ::scoped_string & scopedstrOld,const ::scoped_string & scopedstr, ::collection::index iStart, ::collection::index iLast)
//{

//   ::collection::count iFindLen = strlen(scopedstrOld);

//   index iLen = str.length() - iStart;

//   if(iLast < 0)
//      iLast +=iLen;

//   int len1;
//   int len2;

//   const ::scoped_string & scopedstr1 = str;
//   const ::scoped_string & scopedstr2 = pszOld;

//   character_count iPos = 0;

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

//         if(ch().to_lower_case(ch().uni_index_len(scopedstrC1,len1)) == ch().to_lower_case(ch().uni_index_len(scopedstrC2,len2)))
//         {
//            pszC1 += len1;
//            pszC2 += len2;
//            if(*pszC2 == '\0')
//            {
//               return psz1 - (const_char_pointer )str;
//            }
//            if(*pszC1 == '\0')
//            {
//               return -1;
//            }
//         }
//         else
//         {
//            ch().uni_index_len(scopedstr1,len1);
//            psz1 += len1;
//            iPos += len1;
//            break;
//         }
//      }

//   }

//   return -1;

//}


::collection::index str::find_file_extension(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstr, ::collection::index iStart, ::collection::index iLast)
{

   if (scopedstrOld.is_empty()) // do not search for empty Extensions
   {

      return -1;

   }

   // for dir::name_is (check if base name of a file is a directory, checking if there is a simple ansi '.', may be very good start int_point definitive false).
   // if there is a dot, it may still does not have a Latin dot, if the dot is inside a Multibyte UTF8 char, anyway, algo following should check it properly.

   ::collection::index iLen = scopedstr.length() - iStart;

   if (iLast < 0)
   {

      iLast += iLen;

   }

   {

      const ::ansi_character * pszOkToContinue = strchr(scopedstr, '.');

      if (pszOkToContinue == nullptr || pszOkToContinue - (const_char_pointer )scopedstr >= iLast)
      {

         return -1;

      }

   }

   ::collection::count iFindLen = scopedstrOld.length();

   int len1;

   int len2;

   const ::ansi_character * psz1 = scopedstr;

   const ::ansi_character * psz2 = scopedstrOld;

   character_count iPos = 0;

   character_count iPos2 = 0;

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

                  return (psz1 - (const_char_pointer )scopedstr) - 1; // "-1" because find file extension returns the index of the dot

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


::collection::index str::utf8_find(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstr, ::collection::index iStart)
{

 if (scopedstrOld.is_empty())
 {

    return 0;

 }

 if (scopedstr.is_empty())
 {

    return -1;

 }

 auto psz = &scopedstr[iStart];

 const_char_pointer  pSrc;

 const_char_pointer  pFin = scopedstrOld;

 int lenSrc;

 int lenFin;

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


//index str::case_insensitive_find(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstr, ::collection::index iStart)
//{
//
//  index iFindLen = scopedstrOld.length();
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
//     ::memory_copy(szFind, scopedstrOld, iFindLen + 1);
//
//     make_lower(szFind);
//
//     if(iLen < 256)
//     {
//
//        char sz[256];
//
//        ::memory_copy(sz, &str[iStart], iLen + 1);
//
//        make_lower(sz);
//
//        auto pszOld = strstr(sz, szFind);
//
//        if (scopedstrOld == nullptr)
//        {
//
//           return -1;
//
//        }
//
//        return iStart + (scopedstrOld - sz);
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
//        auto pszOld = strstr(scopedstr, szFind);
//
//        if (scopedstrOld == nullptr)
//        {
//
//           return -1;
//
//        }
//
//        return iStart + (scopedstrOld - psz);
//
//     }
//
//  }
//  else
//  {
//
//     string strFindLow(scopedstrOld, iFindLen); // avoid optimized read only string copy
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


::collection::index str::find_wwci(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, ::collection::index iStart)
{

   string strFind(scopedstrOld);

   strFind.make_lower();

   string str(scopedstrParam);

   str.make_lower();

   return find_ww(strFind, str, iStart);

}


::collection::index str::find_awwci(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, ::collection::index iStart)
{

   string strFind(scopedstrOld);

   strFind.make_lower();

   string str(scopedstrParam);

   str.make_lower();

   return find_aww(strFind, str, iStart);

}


character_count str::find_ww(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, ::collection::index iStart)
{

   if (scopedstrParam.is_empty())
   {

      return -1;

   }

   auto psz = scopedstrParam.c_str();

   const ::ansi_character * pszIter = &scopedstrParam[iStart];

   if (pszIter == nullptr)
   {

      return -1;

   }

   string strFind(scopedstrOld);

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


character_count str::find_aww(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrParam, ::collection::index iStart)
{

   if (scopedstrParam.is_empty())
   {

      return -1;

   }

   auto psz = scopedstrParam.c_str();

   const ::ansi_character * pszIter = &psz[iStart];

   if (pszIter == nullptr)
   {

      return -1;

   }

   string strFind(scopedstrOld);

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


string str::has_character(const ::scoped_string & scopedstrIfHasChar, const ::scoped_string & scopedstrBefore, const ::scoped_string & scopedstrAfter, const ::scoped_string & scopedstrDoesnt)
{

   string str;

   if (strIfHasChar.is_empty())
   {

      if (strDoesnt.has_character())
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

   if (strBefore.has_character())
   {

      str = strBefore;

   }

   str += strIfHasChar;

   if (strAfter.has_character())
   {

      str += strAfter;

   }

   return str;

}


bool str::has_upper(const ::scoped_string & scopedstr)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper;

}


bool str::has_lower(const ::scoped_string & scopedstr)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasLower;

}


bool str::has_digit(const ::scoped_string & scopedstr)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasDigit;

}


void str::calc_v1(const ::scoped_string & scopedstrParam, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   auto psz = scopedstrParam.c_str();

   bHasUpper = false;
   bHasLower = false;
   bHasDigit = false;

   while (true)
   {

      string strUtf8Char = get_utf8_char(scopedstr);

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
      
      unicode_increment(scopedstr);

   }

}


bool str::has_one_v1(const ::scoped_string & scopedstr, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper || bHasLower || bHasDigit;

}


bool str::has_all_v1(const ::scoped_string & scopedstr, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
{

   calc_v1(str, bHasUpper, bHasLower, bHasDigit);

   return bHasUpper && bHasLower && bHasDigit;

}


bool str::has_all_v1(const ::scoped_string & scopedstr)
{

   bool bHasUpper;
   bool bHasLower;
   bool bHasDigit;

   return has_all_v1(str, bHasUpper, bHasLower, bHasDigit);

}


string str::if_null(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrIfNull)
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


string str::get_word(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSeparator, bool bWithSeparator, bool bEndIsSeparator)
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

   const ::ansi_character * pszOld = strstr(scopedstr, strSeparator);

   if (scopedstrOld == nullptr)
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

      return string(scopedstr, pszOld - psz + 1);

   }
   else
   {

      return string(scopedstr, pszOld - psz);

   }

}

// GitHub MightyPork / utf8_encode.c

utf8_character unicode_to_utf8(long long i)
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
      // 2-unsigned char unicode
      out[0] = (char)(((i >> 6) & 0x1F) | 0xC0);
      out[1] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[2] = 0;
      utf8character.m_end = utf8character.m_begin + 2;
   }
   else if (i <= 0xFFFF) {
      // 3-unsigned char unicode
      out[0] = (char)(((i >> 12) & 0x0F) | 0xE0);
      out[1] = (char)(((i >> 6) & 0x3F) | 0x80);
      out[2] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[3] = 0;
      utf8character.m_end = utf8character.m_begin + 3;
   }
   else if (i <= 0x10FFFF) {
      // 4-unsigned char unicode
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


character_count unicode_to_utf8_length(long long i)
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




//const_char_pointer  str::utf8_next_add_length(character_count * paddlength, const ::ansi_character * psz)
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


//const_char_pointer  str::utf8_inc_copy_slide_back(character_count * pslideback, char * pchDst, const_char_pointer  pchSrc)
//{
//
//   character_count count = 0;
//
//   ::str::utf8_inc_slide(&count, pchSrc);
//
//   ::memory_copy(pchDst, pchSrc, count);
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



//const_char_pointer  str::utf8_dec(const character & character, const ::ansi_character * pszBeg, const ::ansi_character * psz)
//{
//
//   if (scopedstr <= pszBeg)
//   {
//
//      pchar->m_chLen = -1;
//
//      return nullptr;
//
//   }
//
//   if ((*(scopedstr - 1) & 0x80) == 0x00)
//   {
//
//      if ((scopedstr - 1) < pszBeg)
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
//   else if ((*(scopedstr - 2) & 0xE0) == 0xC0)
//   {
//
//      if ((scopedstr - 2) < pszBeg)
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
//   else if ((*(scopedstr - 3) & 0xF0) == 0xE0)
//   {
//
//      if ((scopedstr - 3) < pszBeg)
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
//   else if ((*(scopedstr - 4) & 0xF8) == 0xF0)
//   {
//
//      if ((scopedstr - 4) < pszBeg)
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
//   else if ((*(scopedstr - 5) & 0xFC) == 0xF8)
//   {
//
//      if ((scopedstr - 5) < pszBeg)
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
//   else if ((*(scopedstr - 6) & 0xFE) == 0xFC)
//   {
//
//      if ((scopedstr - 6) < pszBeg)
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
//   if ((scopedstr - 1) < pszBeg)
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


const_char_pointer  utf8_dec(const ::ansi_character * pszBeg, const ::ansi_character * psz)
{

   if (scopedstr <= pszBeg)
   {

      return nullptr;

   }

   if ((*(scopedstr - 1) & 0x80) == 0x00)
   {

      if ((scopedstr - 1) < pszBeg)
      {

         return nullptr;

      }

      return psz - 1;

   }
   else if ((*(scopedstr - 2) & 0xE0) == 0xC0)
   {

      if ((scopedstr - 2) < pszBeg)
      {

         return nullptr;

      }

      return psz - 2;

   }
   else if ((*(scopedstr - 3) & 0xF0) == 0xE0)
   {

      if ((scopedstr - 3) < pszBeg)
      {

         return nullptr;

      }

      return psz - 3;

   }
   else if ((*(scopedstr - 4) & 0xF8) == 0xF0)
   {

      if ((scopedstr - 4) < pszBeg)
      {

         return nullptr;

      }

      return psz - 4;

   }
   else if ((*(scopedstr - 5) & 0xFC) == 0xF8)
   {

      if ((scopedstr - 5) < pszBeg)
      {

         return nullptr;

      }

      return psz - 5;

   }
   else if ((*(scopedstr - 6) & 0xFE) == 0xFC)
   {

      if ((scopedstr - 6) < pszBeg)
      {

         return nullptr;

      }

      return psz - 6;

   }

   if ((scopedstr - 1) < pszBeg)
   {

      return nullptr;

   }

   return psz - 1;

}


string get_utf8_char(const ::ansi_character * psz)
{

   int iLength;
   
   auto iIndex = unicode_index_length(scopedstr, iLength);

   if (iLength < 0)
   {

      return "";

   }

   return string(scopedstr, iLength);

}


string get_utf8_char(const ::ansi_character * psz, const ::ansi_character * pszEnd)
{

   const ::ansi_character * pszNext = unicode_next(scopedstr);

   if (scopedstrNext > pszEnd)
   {

      return "";

   }

   return string(scopedstr, pszNext - psz);

}


bool get_utf8_char(string & strChar, const_char_pointer & psz, const ::ansi_character * pszEnd)
{

   const ::ansi_character * pszNext = unicode_next(scopedstr);

   if (scopedstrNext > pszEnd)
   {

      return false;

   }

   strChar = string(scopedstr, pszNext - psz);

   psz = pszNext;

   return true;

}


string get_utf8_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, ::collection::index i)
{

   if (i > 0)
   {

      while (i != 0)
      {

         unicode_increment(scopedstr);

         if (*psz == '\0')
         {

            return "";

         }

         i--;

      }

      return get_utf8_char(scopedstr);

   }
   else
   {

      while (i != 0)
      {

         psz = unicode_prior(scopedstrBeg, psz);

         if (scopedstr == nullptr)
         {

            return "";

         }
         else if (*psz == '\0')
         {

            return "";

         }

         i++;

      }

      return get_utf8_char(scopedstr);

   }

}


string utf8_next_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, ::collection::index i)
{

   return get_utf8_char(scopedstrBeg, psz, i + 1);

}


string utf8_previous_char(const ::ansi_character * pszBeg, const ::ansi_character * psz, ::collection::index i)
{

   return utf8_next_char(scopedstrBeg, psz, -i);

}


int str::get_escaped_char(const ::ansi_character * psz, character_count pos, character_count & retPos)
{

   retPos = pos;

   if (scopedstr[pos] == '\\')
   {

      retPos++;

      if (scopedstr[pos + 1] == 'x')
      {

         if (scopedstr[pos + 2] == '{')
         {

            string val;

            if (!get_curly_content(&psz[pos + 2], val))
            {

               return BAD_WCHAR;

            }

            long long hex = ::hex::to_long_long(val);

            character_count val_len = val.length();

            if (hex < 0 || hex > 0xFFFF)
            {

               return BAD_WCHAR;

            }

            retPos += val_len + 2;

            return (int)hex;

         }
         else
         {

            long long hex = ::hex::to_long_long(string(&psz[pos + 2], 2));

            if ((long long)(strlen(scopedstr)) <= pos + 2 || hex == -1)
            {

               return BAD_WCHAR;

            }

            retPos += 2;

            return (int)hex;

         }

      }

      return psz[pos + 1];

   }

   return psz[pos];

}


bool str::get_curly_content(const ::ansi_character * psz, string & str)
{

   if (scopedstr[0] != '{') return false;

   const ::ansi_character * pszChar;

   for (scopedstrChar = unicode_next(scopedstr); pszChar != nullptr; unicode_increment(scopedstrChar))
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
   if (scopedstrChar == nullptr || *pszChar == '\0')
      return false;
   str = string(&psz[1], pszChar - psz - 1);
   return true;
}


bool str::is_simple_natural(const ::ansi_character * pszCandidate, character_count iCount)
{

   if (iCount == 0)
   {

      return false;

   }

   string str(scopedstrCandidate);

   str.trim();

   auto psz = str.c_str();

   if (*psz == '\0')
   {

      return false;

   }

   while (*psz != '\0' && iCount != 0)
   {

      if (!unicode_is_digit(scopedstr))
      {

         return false;

      }

      unicode_increment(scopedstr);

      iCount--;

   }

   return true;

}


bool str::is_natural(const ::scoped_string & scopedstrParam)
{

   string str(scopedstrParam);

   str.trim();

   for (::collection::index i = 0; i < str.length(); i++)
   {

      if (!ansi_char_isdigit(str[i]))
      {

         return false;

      }

   }

   return true;

}


bool str::is_integer(const ::scoped_string & scopedstrParam)
{

   string str(scopedstrParam);

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




template < const character_count m_iSize = 1024 >
class mini_str_buffer
{
public:


   character_count     m_iPos;
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

   void append_uni(long long w)
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

   void append(const ::ansi_character * psz, character_count iSize)
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





string str::token(string & str, const ::scoped_string & scopedstrSeparatorText, bool bWithSeparator)
{

   auto pFind = str.find(strSeparatorText);

   string strToken;

   if (::is_set(pFind))
   {

      if (bWithSeparator)
      {

         pFind += strSeparatorText.size();

         strToken = str(0, pFind);

         str.begin(pFind);

      }
      else
      {

         strToken = str(0, pFind);

         str.begin(pFind + strSeparatorText.size());

      }

   }

   return strToken;

}


string str::line(string & str, bool bNewLine)
{

   auto iFind1 = str.find_index('\r');

   auto iFind2 = str.find_index('\n');

   auto iFind = minimum_non_negative(iFind1, iFind2);

   string strToken;

   if (::not_found(iFind))
   {

      strToken = str;

      str.empty();

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

         strToken = str.left(iEnd);

      }
      else
      {

         strToken = str(0, iFind);

      }

      str = str.substr(iEnd);

   }

   return strToken;

}


//bool str::begins_consume(::const_ansi_range & range, const ::scoped_string & scopedstr)
//{
//
//   //character_count idx;
//
//   character_count len = str.length();
//
//   if (strncmp(scopedstrParse, str, len) != 0)
//   {
//
//      return false;
//
//   }
//
//   pszParse += len;
//
//   return true;
//
//}




string str::pad(const ::scoped_string & scopedstrParam, ::collection::count iLen, const ::scoped_string & scopedstrPattern, enum_pad epad)
{

   string str(scopedstrParam);

   if (scopedstrPattern.is_empty())
   {

      return str;

   }

   int i = 0;

   if (epad == e_pad_left)
   {

      while (str.length() < iLen)
      {

         if (scopedstrPattern[i] == '\0')
         {

            i = 0;

         }

         str = scopedstrPattern[i] + str;

         i++;

      }

   }
   else if (epad == e_pad_right)
   {

      while (str.length() < iLen)
      {

         if (scopedstrPattern[i] == '\0')
         {

            i = 0;

         }

         str = str + scopedstrPattern[i];

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


   string bigint2string(unsigned long long l)
   {
      string str;
      unsigned long long tmp = l;
      while (tmp)
      {
         unsigned long long a = tmp % 10;
         str = (char)(a + 48) + str;
         tmp /= 10;
      }
      if (!str.length())
      {
         str = "0";
      }
      return str;
   }*/


int str::to_int(const ::scoped_string & scopedstr)
{

   return ansi_to_int(str);

}


unsigned int str::to_unsigned_int(const ::scoped_string & scopedstr)
{

   return (unsigned int)ansi_to_long_long(scopedstr);

}


long long str::to_long_long(const ::scoped_string & scopedstr)
{

   int i = 0;

   for (; i < str.length() && character_isspace(str[i]); i++);

   bool bNegative = str[i] == '-';

   if (bNegative)
   {

      i++;

   }

   unsigned long long u = 0;

   for (; i < str.length() && character_isdigit(str[i]); i++)
   {

      u = u * 10 + str[i] - 48;

   }

   if (bNegative)
   {

      return -(long long)u;

   }
   else
   {

      return (long long)u;

   }

}


//long long to_long_long(const ::scoped_string & scopedstr)
//{

//   int i = 0;

//   for (; *psz != '\0' && i < 30 && ansi_char_isspace(*psz); i++, psz++);

//   bool bNegative = *psz == '-';

//   if(bNegative)
//      psz++;

//   unsigned long long u = 0;

//   for(; *psz != '\0' && i < 30 && ansi_char_isdigit(*psz); psz++, i++)
//   {
//      u = u * 10 + *psz - 48;
//   }

//   if(bNegative)
//      return -(long long) u;
//   else
//      return (long long) u;

//}

unsigned long long str::to_unsigned_long_long(const ::scoped_string & scopedstr)
{

   int i = 0;

   for (; i < str.length() && character_isspace(str[i]); i++);

   unsigned long long u = 0;

   for (; i < str.length() && character_isdigit(str[i]); i++)
   {
      u = u * 10 + str[i] - 48;
   }

   return u;

}

//unsigned long long to_unsigned_long_long(const ::scoped_string & scopedstrParam)
//{

//   int i = 0;

//   for (; *psz != '\0' && i < 30 && character_isspace(*psz); i++, psz++);

//   unsigned long long u = 0;

//   for(; *psz != '\0' && i < 30 && isdigit(*psz); psz++, i++)
//   {
//      u = u * 10 + *psz - 48;
//   }

//   return u;

//}



void str::increment_digit_letter(string & str)
{

   character_count i = str.length() - 1;

   while (i >= 0)
   {

      if (str[i] >= '0' && str[i] <= '8')
      {
         str = str.left(i) + string((char)(str[i] + 1)) + str.right(str.length() - i - 1);
         break;
      }
      else if (str[i] == '9')
      {
         str = str.left(i) + string((char)('a')) + str.right(str.length() - i - 1);
         break;
      }
      else if (str[i] >= 'a' && str[i] <= 'y')
      {
         str = str.left(i) + string((char)(str[i] + 1)) + str.right(str.length() - i - 1);
         break;
      }
      else if (str[i] == 'z')
      {
         str = str.left(i) + string((char)('0')) + str.right(str.length() - i - 1);
         i--;
      }
   }
}


//bool str::while_begins_with_chars_eat(string & str, const ::ansi_character * pszChars)
//{
//
//   int i = 0;
//   for (i = 0; i < str.length(); i++)
//   {
//      if (strchr(pcszChars, str[i]) == nullptr)
//
//         break;
//   }
//   str = str.substr(i);
//   return i > 0;
//
//}
//
//
//bool str::case_insensitive_while_begins_with_chars_eat(string & str, const ::ansi_character * pszChars) // case insensitive
//{
//
//   int i = 0;
//   for (i = 0; i < str.length(); i++)
//   {
//      if (strchr(pcszChars, tolower(str[i])) == nullptr)
//
//         break;
//   }
//   str = str.substr(i);
//   return i > 0;
//}


//   void begin(wstring & wstr, const unichar * pcszPrefix)
//   {
//
//      character_count iPrefixLen = wide_length(pcszPrefix);
//
//      if(wstr.get_storage_size_in_bytes() >= ((wstr.get_length() + iPrefixLen + 1) * __sizeof(unichar)))
//      {
//
//         memory_transfer(&wstr[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
//
//         memory_copy(wstr, pcszPrefix, iPrefixLen);
//
//      }
//      else
//      {
//         wstring wstrNew;
//         wstrNew.get_buffer((wstr.get_length() + iPrefixLen + 1) * sizeof(unichar));
//         memory_copy(&wstrNew[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
//         memory_copy(wstrNew, pcszPrefix, iPrefixLen * sizeof(unichar));
//
//         wstr.attach(wstrNew.detach());
//      }
//
//   }


//bool str::replace_prefix(::string & str, const ::ansi_character * pszPrefixReplacement, const ::ansi_character * pszPrefix)
//{
//
//   if (!str.begins_eat(scopedstrPrefix))
//   {
//
//      return false;
//
//   }
//
//   str = ::string(scopedstrPrefixReplacement) + str;
//
//   return true;
//
//}
//
//
//bool str::case_insensitive_replace_prefix(::string & str, const ::ansi_character * pszPrefixReplacement, const ::ansi_character * pszPrefix)
//{
//
//   if (!str.case_insensitive_begins_eat(scopedstrPrefix))
//   {
//
//      return false;
//
//   }
//
//   str = ::string(scopedstrPrefixReplacement) + str;
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
//   /// \return True if \int_point pcsz is prefixed with \int_point pcszPrefix.
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

string str::ansi_lower(const ::scoped_string & scopedstr)
{

   return str.lowered();

}


string str::ansi_upper(const ::scoped_string & scopedstr)
{

   return str.uppered();

}


/** End \file Utility.cpp
**   \date  2004-02-13
**   \author grymse@alhem.net
**/


bool str::simple_escaped(const ::scoped_string & scopedstr, character_count pos)
{

   if (pos == 0)
   {

      return false;

   }

   return str[pos - 1] == '\\' && !simple_escaped(str, pos - 1);

}


bool str::trim(string & str)
{

   character_count iLen = str.length();

   str.trim();

   return iLen != str.length();

}


bool str::_008Trim(string & str)
{

   ::collection::count c = 1;

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

   str = str.substr(1, str.length() - 2);

   return true;

}


///
/// q(between quotes :-) )-valid string
/// from:http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
/// more invalid strings to test: http://stackoverflow.com/questions/1301402/example-invalid-utf8-string
///
bool str::utf8_check_is_valid(const ::scoped_string & scopedstring)
{

   character_count i, c, ix, n, j;

   for (i = 0, ix = string.length(); i < ix; i++)
   {

      c = (unsigned char)string[i];

      //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
      if (0x00 <= c && c <= 0x7f) n = 0; // 0bbbbbbb
      else if ((c & 0xE0) == 0xC0) n = 1; // 110bbbbb
      else if (c == 0xed && i < (ix - 1) && ((unsigned char)string[i + 1] & 0xa0) == 0xa0) return false; //U+d800 to U+dfff
      else if ((c & 0xF0) == 0xE0) n = 2; // 1110bbbb
      else if ((c & 0xF8) == 0xF0) n = 3; // 11110bbb
      //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //unsigned char 5, unnecessary in 4 unsigned char UTF-8
      //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //unsigned char 6, unnecessary in 4 unsigned char UTF-8
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

   for (::collection::index i = 0; i < str.length(); i++)
   {

      if (i == 0 && (str[i] == '+' || str[i] == '-'))
      {

      }
      else if (!ansi_char_isdigit(str[i]))
      {

         return false;

      }

   }

   if (ansi_to_int(str) == 0)
   {

      return false;

   }

   return true;

}




string str::block(char ch, int iSize)
{

   string str;

   auto psz = str.get_buffer(iSize);

   for (int i = 0; i < iSize; i++)
   {

      psz[i] = ch;

   }

   str.release_buffer(iSize);

   return str;

}


void str::fill(string & str, char ch)
{

   auto len = str.length();

   auto psz = str.get_buffer();

   for (int i = 0; i < len; i++)
   {

      psz[i] = ch;

   }

   str.release_buffer(len);

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


string & str::zero_pad(string & str, character_count lenPad)
{

   ::ansi_zero_pad(str.get_buffer(str.length() + lenPad), lenPad);

   str.release_buffer();

   return str;

}


string str::zero_padded(const ::scoped_string & scopedstrSrc, character_count lenPad)
{

   string str(strSrc);

   if (lenPad > str.length())
   {

      ::ansi_zero_pad(str.get_buffer(lenPad), lenPad);

      str.release_buffer(lenPad);

   }

   return str;

}


void str::get_lines(::string & str, bool bFinal, const ::function < void(const ::scoped_string&, bool bCarriage) > & functionNewLine)
{

   auto iLimitN = str.rear_find_index("\n");
   auto iLimitR = str.rear_find_index("\r");

   auto iLimit = maximum(iLimitN, iLimitR);

   if (not_found(iLimit))
   {

      if(bFinal)
      {

         auto range = str();

         if(str.has_character())
         {

            functionNewLine(str, false);

         }

         str.clear();

      }

      return;

   }

   character_count iLast = -1;

   while(true)
   {

      auto iFindN = str.find_index('\n', iLast + 1);
      auto iFindR = str.find_index('\r', iLast + 1);
      auto iFindNext = minimum_non_negative(iFindN, iFindR);

      if(iFindNext < 0)
      {

         if(bFinal)
         {

            auto range = str();

            if(str.has_character())
            {

               functionNewLine(str, false);

            }

            str.clear();

         }

         return;

      }
      else if(iFindNext > iLimit)
      {

         break;

      }

      int iLess = 0;

      if (iFindN > 0 && iFindN == iFindR + 1)
      {

         iLess = 1;

         iFindNext = iFindN;

      }

      auto range = str(iLast + 1, iFindNext - iLast - 1 - iLess);

      functionNewLine(range, iFindNext == iFindR);

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

   str.erase(iLimit + 1);

}


void str::get_lines(::string_array & stra, ::string & str, const ::scoped_string & scopedstrPrefix, bool bFinal, ::particle * pparticleSynchronization, ::file::file * pfileLog)
{

   auto functionNewLine = [&](auto & range, bool bCarriage)
   {

      string strPrefixedLine;

      strPrefixedLine = strPrefix + range;

      if (::is_set(pparticleSynchronization))
      {

         pparticleSynchronization->_lock();

      }

      stra.add(strPrefixedLine.c_str());

      if (::is_set(pparticleSynchronization))
      {

         pparticleSynchronization->unlock();

      }

      if (::is_set(pfileLog) && pfileLog->has_ok_flag())
      {

         try
         {

            pfileLog->write(strPrefixedLine + (bCarriage? "\r": "\n"));

         }
         catch (...)
         {

         }

      }

   };

   get_lines(str, bFinal, functionNewLine);

}


character_count str::x_find_index(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrSearchedTerm)
{

   character_count start = 0;

   while (auto found = scopedstr.case_insensitive_find_index(scopedstrSearchedTerm, start))
   {

      if (found < 0)
      {

         break;

      }

      if ((found == 0 || !ansi_char_isalpha(scopedstr[found - 1]))
         && ((found + scopedstrSearchedTerm.size()) >= scopedstr.size() ||
            !ansi_char_isalpha(scopedstr[found + scopedstrSearchedTerm.size()]))
         )
      {

         return found;

      }

      start = found + scopedstrSearchedTerm.size();

   }

   return -1;

}


bool str::x_contains(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrSearchedTerm)
{

   auto found = x_find_index(scopedstr, scopedstrSearchedTerm);

   return found >= 0;

}


bool str::x_contains(const ::scoped_string& scopedstr, const ::string_array& straSearchedTerm)
{

   for (auto& strSearchedTerm : straSearchedTerm)
   {

      if (x_contains(scopedstr, strSearchedTerm))
      {

         return true;

      }

   }

   return false;

}

//::string as_string(const ::string_stream & strstream)
//{
//
//   return strstream.as_string();
//
//}


//// template < typename FILE >
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

   template < > class get_char_type < const_char_pointer  > { public: using CHAR_TYPE = char; };
   template < > class get_char_type < char * > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < const char[n] > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < char[n] > { public: using CHAR_TYPE = char; };


//bool str::begins_eat(::payload & payload, const ::scoped_string & scopedstrPrefix)
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
//bool str::case_insensitive_begins_eat(::payload & payload, const ::scoped_string & scopedstrPrefix)
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
//bool str::begins_eat(property & property, const ::scoped_string & scopedstrPrefix)
//{
//
//   return begins_eat((::payload &)property, strPrefix);
//
//}
//
//
//bool str::case_insensitive_begins_eat(property & property, const ::scoped_string & scopedstrPrefix)
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

