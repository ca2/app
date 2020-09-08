#include "framework.h"





//CLASS_DECL_APEX const char* yoshi_strcat(const char* psz1, const char* psz2, bool bFree2 = false);


//char* ansi_copy(char* dest, const char* cat)
//{
//   if (dest == nullptr)
//      return nullptr;
//   if (cat == nullptr)
//      return nullptr;
//   return ansi_concatenate(dest, cat);
//   /*while(*dest != 0)
//      dest++;
//   while(*cat != 0)
//      *dest++ = *cat++;
//   *dest = '\0';*/
//}


//#ifdef __APPLE__
//
//i32 ansi_compare_ci(const char* sz1, const char* sz2)
//{
//   return ansi_compare_ci(sz1, sz2);
//}
//
//#endif


//i32 ansi_compare_ci(const char* sz1, const char* sz2)
//{
//   if (sz1 == nullptr)
//   {
//      if (sz2 == nullptr)
//         return 0;
//      else
//         return -1;
//   }
//   else if (sz2 == nullptr)
//   {
//      return 1;
//   }
//   i32 iCmp = 0;
//   while (*sz1 != '\0' && *sz2 != '\0')
//   {
//      iCmp = ansi_char_lower(*sz1) - ansi_char_lower(*sz2);
//      if (iCmp != 0)
//         return iCmp;
//      sz1++;
//      sz2++;
//   }
//   return ansi_char_lower(*sz1) - ansi_char_lower(*sz2);
//}

//i32 ansi_compare(const char* sz1, const char* sz2)
//{
//   if (sz1 == nullptr)
//   {
//      if (sz2 == nullptr)
//         return 0;
//      else
//         return -1;
//   }
//   else if (sz2 == nullptr)
//   {
//      return 1;
//   }
//   i32 iCmp;
//   while (*sz1 != '\0' && *sz2 != '\0')
//   {
//      iCmp = *sz1 - *sz2;
//      if (iCmp != 0)
//         return iCmp;
//      sz1++;
//      sz2++;
//   }
//   return *sz1 - *sz2;
//}

//i32 ansi_count_compare_ci(const char* sz1, const char* sz2, ::count iLen)
//{
//
//   if (iLen <= 0)
//   {
//
//      return 0; // equal
//
//   }
//
//   if (sz1 == nullptr)
//   {
//
//      if (sz2 == nullptr)
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (sz2 == nullptr)
//   {
//
//      return 1;
//
//   }
//
//   i32 iCmp = 0;
//
//   while (iLen > 0)
//   {
//
//      iCmp = ansi_char_lower(*sz1) - ansi_char_lower(*sz2);
//
//      if (iCmp != 0)
//      {
//
//         return iCmp;
//
//      }
//
//      if (*sz1 == '\0' || *sz2 == '\0')
//      {
//
//         return iCmp;
//
//      }
//
//      sz1++;
//
//      sz2++;
//
//      iLen--;
//
//   }
//
//   return iCmp;
//
//}

//i32 ansi_count_compare(const char* sz1, const char* sz2, ::count iLen)
//{
//   if (iLen <= 0)
//      return 0; // equal
//   if (sz1 == nullptr)
//   {
//      if (sz2 == nullptr)
//         return 0;
//      else
//         return -1;
//   }
//   else if (sz2 == nullptr)
//   {
//      return 1;
//   }
//   i32 iCmp = 0;
//   while (iLen > 0)
//   {
//      iCmp = *sz1 - *sz2;
//      if (iCmp != 0 || *sz1 == '\0' || *sz2 == '\0')
//         return iCmp;
//      sz1++;
//      sz2++;
//      iLen--;
//   }
//   return iCmp;
//}


//const char* ansi_find_char(const char* sz, char ch)
//{
//
//   if (sz == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if (*sz == '\0')
//   {
//
//      return nullptr;
//
//   }
//
//   while (true)
//   {
//
//      if (*sz == ch)
//      {
//
//         return sz;
//
//      }
//
//      if (*sz == '\0')
//      {
//
//         return nullptr;
//
//      }
//
//      sz++;
//
//   }
//
//}
//
//
//char* ansi_find_char_reverse(char* szStart, char ch)
//{
//   char* sz = szStart;
//   while (*sz != '\0')
//   {
//      sz++;
//   }
//   while (sz != szStart)
//   {
//      sz--;
//      if (*sz == ch)
//         return sz;
//   }
//   return nullptr;
//
//}
//
//char ansi_char_lower(i32 ch)
//{
//   if (ch >= 'A' && ch <= 'Z')
//   {
//      ch = ch - 'A' + 'a';
//   }
//   return ch;
//}


//
//char ansi_char_upper(i32 ch)
//{
//   if (ch >= 'a' && ch <= 'z')
//   {
//      ch = ch - 'a' + 'A';
//   }
//   return ch;
//}
//
//char* ansi_upper(char* pchParam)
//{
//   char* pch = pchParam;
//   while (*pch != '\0')
//   {
//      *pch = ansi_char_upper(*pch);
//      pch++;
//   }
//   return pchParam;
//}

//
//const char * ansi_find_string(const char* src, const char* find)
//{
//
//   if (src == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   while (*src != '\0')
//   {
//      const char* srcParse = src;
//      const char* findParse = find;
//      while (*srcParse != '\0' && *findParse != '\0')
//      {
//         if (*srcParse != *findParse)
//            break;
//         srcParse++;
//         findParse++;
//      }
//      if (*findParse == '\0')
//         return (char*)src;
//      src++;
//   }
//   return nullptr;
//}



//char* ansi_find_string_ci(const char* src, const char* find)
//{
//   while (*src != '\0')
//   {
//      const char* srcParse = src;
//      const char* findParse = find;
//      while (*srcParse != '\0' && *findParse != '\0')
//      {
//         if (ansi_char_lower(*srcParse) != ansi_char_lower(*findParse))
//            break;
//         srcParse++;
//         findParse++;
//      }
//      if (*findParse == '\0')
//         return (char*)src;
//      src++;
//   }
//   return nullptr;
//}

//char* ansi_count_find_string(const char* src, const char* find, iptr iLen)
//{
//   if (iLen == 0)
//      return (char*)src;
//   if (iLen > ansi_length(find))
//      return nullptr;
//   iptr c;
//   while (*src != '\0')
//   {
//      const char* srcParse = src;
//      const char* findParse = find;
//      c = iLen;
//      while (*srcParse != '\0' && *findParse != '\0')
//      {
//         if (*srcParse != *findParse)
//            break;
//         srcParse++;
//         findParse++;
//         c--;
//      }
//      if (c == 0 || *findParse == '\0')
//         return (char*)src;
//      src++;
//   }
//   return nullptr;
//}
//
//char* ansi_count_find_string_ci(const char* src, const char* find, iptr iLen)
//{
//   if (iLen == 0)
//      return (char*)src + strlen(src);
//   if (iLen > ansi_length(find))
//      return nullptr;
//   iptr c;
//   while (*src != '\0')
//   {
//      const char* srcParse = src;
//      const char* findParse = find;
//      c = iLen;
//      while (c > 0 && *srcParse != '\0' && *findParse != '\0')
//      {
//         if (ansi_char_lower(*srcParse) != ansi_char_lower(*findParse))
//            break;
//         srcParse++;
//         findParse++;
//         c--;
//      }
//      if (c == 0 || *findParse == '\0')
//         return (char*)src;
//      src++;
//   }
//   return nullptr;
//}
//
//
//void ansi_from_u64(char* sz, u64 ui, i32 iBase)
//{
//   if (ui == 0)
//   {
//      sz[0] = '0';
//      sz[1] = '\0';
//      return;
//   }
//   i32 iIndex = 0;
//   while (ui > 0)
//   {
//      i32 iDigit = (ui % iBase);
//      char ch;
//      if (iDigit <= 9)
//      {
//         ch = iDigit + '0';
//      }
//      else
//      {
//         ch = iDigit - 10 + 'a';
//      }
//      sz[iIndex] = ch;
//      ui = ui / iBase;
//      iIndex++;
//   }
//   sz[iIndex] = '\0';
//   ansi_reverse(sz);
//}
//


//void ansi_from_i64(char* sz, i64 i, i32 iBase)
//{
//   if (i == 0)
//   {
//      sz[0] = '0';
//      sz[1] = '\0';
//      return;
//   }
//   bool bNegative = false;
//   if (i < 0)
//   {
//      i = -i;
//      bNegative = true;
//   }
//   i32 iIndex = 0;
//   while (i > 0)
//   {
//      i32 iDigit = (i % iBase);
//      char ch;
//      if (iDigit <= 9)
//      {
//         ch = iDigit + '0';
//      }
//      else
//      {
//         ch = iDigit - 10 + 'a';
//      }
//      sz[iIndex] = ch;
//      i = i / iBase;
//      iIndex++;
//   }
//   if (bNegative)
//   {
//      sz[iIndex] = '-';
//      iIndex++;
//   }
//   sz[iIndex] = '\0';
//   ansi_reverse(sz);
//}
//
//

//void ansi_reverse(char* sz)
//{
//
//   reverse_memory(sz, ansi_length(sz));
//
//}

//void ansi_zero_pad(char* sz, ::count iPad)
//{
//
//   ::count iLen = ansi_length(sz);
//
//   ::count iZeroCount = iPad - iLen;
//
//   if (iZeroCount > 0)
//   {
//
//      ::count iEnd = iLen - 1;
//
//      ::count iFinalEnd = iEnd + iZeroCount;
//
//      sz[iFinalEnd + 1] = '\0';
//
//      for (; iEnd >= 0; iEnd--, iFinalEnd--)
//      {
//         sz[iFinalEnd] = sz[iEnd];
//      }
//
//      for (; iFinalEnd >= 0; iFinalEnd--)
//      {
//         sz[iFinalEnd] = '0';
//      }
//
//   }
//
//}
//
//char* str_begins_inc_dup(const char* sz1, const char* prefix)
//{
//   if (sz1 == nullptr)
//      return nullptr;
//   if (prefix == nullptr)
//      return (char*)sz1;
//   while (*sz1 != '\0' && *prefix != '\0')
//   {
//      if (*sz1 != *prefix)
//         return nullptr;
//      sz1++;
//      prefix++;
//   }
//   if (*prefix == '\0')
//      return (char*)sz1;
//   else
//      return nullptr;
//}
//

//i32 ansi_begins(const char* sz1, const char* prefix)
//{
//   if (sz1 == nullptr)
//      return FALSE;
//   if (prefix == nullptr)
//      return TRUE;
//   while (*sz1 != '\0' && *prefix != '\0')
//   {
//      if (*sz1 != *prefix)
//         return FALSE;
//      sz1++;
//      prefix++;
//   }
//   return *prefix == '\0';
//}
//
//i32 ansi_begins_ci(const char* sz1, const char* prefix)
//{
//   if (sz1 == nullptr)
//      return FALSE;
//   if (prefix == nullptr)
//      return TRUE;
//   while (*sz1 != '\0' && *prefix != '\0')
//   {
//      if (*sz1 != *prefix)
//         return FALSE;
//      sz1++;
//      prefix++;
//   }
//   return *prefix == '\0';
//}

//i32 ansi_ends(const char* psz, const char* pszSuffix)
//{
//
//   ::count iLen = ansi_length(psz);
//
//   ::count iLenSuffix = ansi_length(pszSuffix);
//
//   if (iLen < iLenSuffix)
//      return false;
//
//   return ansi_compare(&psz[iLen - iLenSuffix], pszSuffix) == 0;
//
//}
//
//
//i32 ansi_ends_ci(const char* psz, const char* pszSuffix)
//{
//
//   ::count iLen = ansi_length(psz);
//
//   ::count iLenSuffix = ansi_length(pszSuffix);
//
//   if (iLen < iLenSuffix)
//      return false;
//
//   return ansi_compare_ci(&psz[iLen - iLenSuffix], pszSuffix) == 0;
//
//}
//
//
//
//
//
//
//
//
//
//
//

#define NULCHAR     '\0'
#define TABCHAR     '\t'
#define SLASHCHAR   '\\'
#define SPACECHAR   ' '
#define DQUOTECHAR  '\"'


void ansi_parse_command_line(char* cmdstart, char** argv, char* args, i32* numargs, i32* numchars)
{
   char* point;
   char c;
   i32 inquote;                    /* 1 = inside quotes */
   i32 copychar;                   /* 1 = copy char to *args */
   u32 numslash;              /* num of backslashes seen */

   *numchars = 0;
   *numargs = 1;                   /* the program name at least */

   /* first scan the program name, copy it, and ::count the bytes */
   point = cmdstart;
   if (argv)
      *argv++ = args;

#ifdef WILDCARD
   /* To handle later wild card expansion, we prefix each entry by
   it's first character before quote handling.  This is done
   so _[w]cwild() knows whether to expand an entry or not. */
   if (args)
      *args++ = *point;
   ++* numchars;

#endif  /* WILDCARD */

   /* A quoted program name is handled here. The handling is much
      simpler than for other arguments. Basically, whatever lies
      between the leading double-quote and next one, or a terminal nullptr
      character is simply accepted. Fancier handling is not required
      because the program name must be a legal NTFS/HPFS file name.
      Note that the double-quote characters are not copied, nor do they
      contribute to numchars. */
   if (*point == DQUOTECHAR)
   {
      /* scan from just past the first double-quote through the next
         double-quote, or up to a nullptr, whichever comes first */
      while ((*(++point) != DQUOTECHAR) && (*point != NULCHAR))
      {

         ++* numchars;
         if (args)
            *args++ = *point;
      }
      /* append the terminating nullptr */
      ++* numchars;
      if (args)
         *args++ = NULCHAR;

      /* if we stopped on a double-quote (usual case), skip over it */
      if (*point == DQUOTECHAR)
         point++;
   }
   else
   {
      /* Not a quoted program name */
      do
      {
         ++* numchars;
         if (args)
            *args++ = *point;

         c = (char)*point++;


      } while (c != SPACECHAR && c != NULCHAR && c != TABCHAR);

      if (c == NULCHAR)
      {
         point--;
      }
      else
      {
         if (args)
            *(args - 1) = NULCHAR;
      }
   }

   inquote = 0;

   /* loop on each argument */
   for (;;)
   {

      if (*point)
      {
         while (*point == SPACECHAR || *point == TABCHAR)
            ++point;
      }

      if (*point == NULCHAR)
         break;              /* end of args */

      /* scan an argument */
      if (argv)
         *argv++ = args;     /* store ptr to arg */
      ++* numargs;

#ifdef WILDCARD
      /* To handle later wild card expansion, we prefix each entry by
      it's first character before quote handling.  This is done
      so _[w]cwild() knows whether to expand an entry or not. */
      if (args)
         *args++ = *point;
      ++* numchars;

#endif  /* WILDCARD */

      /* loop through scanning one argument */
      for (;;)
      {
         copychar = 1;
         /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
            2N+1 backslashes + " ==> N backslashes + literal "
            N backslashes ==> N backslashes */
         numslash = 0;
         while (*point == SLASHCHAR)
         {
            /* ::count number of backslashes for use below */
            ++point;
            ++numslash;
         }
         if (*point == DQUOTECHAR)
         {
            /* if 2N backslashes before, start/end quote, otherwise
                copy literally */
            if (numslash % 2 == 0)
            {
               if (inquote)
               {
                  if (point[1] == DQUOTECHAR)
                     point++;    /* Double quote inside quoted string */
                  else        /* skip first quote char and copy second */
                     copychar = 0;
               }
               else
                  copychar = 0;       /* don't copy quote */

               inquote = !inquote;
            }
            numslash /= 2;          /* divide numslash by two */
         }

         /* copy slashes */
         while (numslash--)
         {
            if (args)
               *args++ = SLASHCHAR;
            ++* numchars;
         }

         /* if at end of arg, break loop */
         if (*point == NULCHAR || (!inquote && (*point == SPACECHAR || *point == TABCHAR)))
            break;

         if (copychar)
         {
            if (args)
               *args++ = *point;
            ++* numchars;
         }
         ++point;
         //#endif  /* _MBCS */
      }

      /* nullptr-terminate the argument */

      if (args)
         *args++ = NULCHAR;          /* terminate string */
      ++* numchars;
   }

   /* We put one last argument in -- a nullptr ptr */
   if (argv)
      *argv++ = nullptr;
   ++* numargs;
}








//i32 ansi_char_is_digit(i32 ch)
//{
//   return ch >= '0' && ch <= '9';
//}
//
//i32 ansi_char_is_hexadecimal(i32 ch)
//{
//   return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
//}
//
//i32 ansi_char_is_alphabetic(i32 ch)
//{
//   return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
//}
//
//i32 ansi_char_is_alphanumeric(i32 ch)
//{
//   return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
//}
//
//i32 ansi_char_is_space(i32 ch)
//{
//   return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\t';
//}



//char* ansi_scan(char* sz, const char* szFind)
//{
//   char* pszRet = nullptr;
//   while (*szFind != '\0')
//   {
//      char* psz = (char*)ansi_find_char(sz, *szFind);
//      if (psz != nullptr && (pszRet == nullptr || psz < pszRet))
//      {
//         pszRet = psz;
//      }
//      szFind++;
//   }
//   return pszRet;
//}





//char* strtok_r_dup(char* s1, const char* s2, char** lasts)
//{
//   char* ret;
//
//   if (s1 == nullptr)
//      s1 = *lasts;
//   while (*s1 && ansi_find_char(s2, *s1))
//      ++s1;
//   if (*s1 == '\0')
//      return nullptr;
//   ret = s1;
//   while (*s1 && !ansi_find_char(s2, *s1))
//      ++s1;
//   if (*s1)
//      *s1++ = '\0';
//   *lasts = s1;
//   return ret;
//}







//void ansi_zero_pad(string& str, ::count iPad)
//{
//
//   while (str.length() < iPad)
//   {
//
//      str = "0" + str;
//
//   }
//
//}

const char* wildcard_next_stop(const char* pszCriteria)
{

   if (pszCriteria == nullptr)
      return nullptr;


   const char* pszAsterisk = ansi_find_string(pszCriteria, "*");
   const char* pszQuestion = ansi_find_string(pszCriteria, "?");

   if (pszAsterisk == nullptr && pszQuestion == nullptr)
      return nullptr;

   if (pszAsterisk == nullptr)
      return pszQuestion;
   else if (pszQuestion == nullptr)
      return pszAsterisk;
   else if (pszAsterisk < pszQuestion)
      return pszAsterisk;
   else
      return pszQuestion;

}





   CLASS_DECL_APEX int_bool matches_wildcard_criteria_dup(const char* pszCriteriaParam, const char* pszValue)
   {

      string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

      const char* pszCriteria = strCriteria;

      const char* pszFind;
      const char* pszStop;

      iptr iLen;

      while (true)
      {

         pszFind = wildcard_next_stop(pszCriteria);

         if (pszFind == nullptr)
            break;

         iLen = pszFind - pszCriteria;

         if (*pszFind == '?')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            if (*pszValue == '\0')
               return false;

            pszCriteria++;
            pszValue++;

         }
         else if (*pszFind == '*')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            pszStop = wildcard_next_stop(pszFind + 1);

            if (pszStop == nullptr)
            {
               return ::str::ends(pszValue, pszFind + 1);
            }

            iLen = pszStop - (pszFind + 1);

            pszValue = ansi_count_find_string(pszValue, pszFind + 1, iLen);

            if (pszValue == nullptr)
               return false;

            pszValue = pszValue + iLen;
            pszCriteria = pszStop;

         }
         else
         {
            __throw(::exception::exception("not_expected, check wildcard_next_stop function"));
         }


      }

      if (strcmp(pszValue, pszCriteria) != 0)
         return false;

      return true;

   }

   CLASS_DECL_APEX int_bool matches_wildcard_criteria_ci(const ansichar * pszCriteriaParam, const ansichar * pszValue)
   {

      string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

      const char* pszCriteria = strCriteria;

      const char* pszFind;
      const char* pszStop;

      iptr iLen;

      while (true)
      {

         pszFind = wildcard_next_stop(pszCriteria);

         if (pszFind == nullptr)
            break;

         iLen = pszFind - pszCriteria;

         if (*pszFind == '?')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare_ci(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            if (*pszValue == '\0')
               return false;

            pszCriteria++;
            pszValue++;

         }
         else if (*pszFind == '*')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare_ci(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            pszStop = wildcard_next_stop(pszFind + 1);

            if (pszStop == nullptr)
               pszStop = pszFind + ansi_length(pszFind);

            iLen = pszStop - (pszFind + 1);

            pszValue = ansi_count_find_string_ci(pszValue, pszFind + 1, iLen);

            if (pszValue == nullptr)
               return false;

            pszValue = pszValue + iLen;
            pszCriteria = pszStop;

         }
         else
         {
            __throw(::exception::exception("not_expected, check wildcard_next_stop function"));
         }


      }

      if (ansi_compare_ci(pszValue, pszCriteria) != 0)
         return false;

      return true;

   }


   CLASS_DECL_APEX int_bool matches_wildcard_criteria(const ansichar * pszCriteriaParam, const ansichar * pszValue)
   {

      string strCriteria(normalize_wildcard_criteria(pszCriteriaParam));

      const char* pszCriteria = strCriteria;

      const char* pszFind;
      const char* pszStop;

      iptr iLen;

      while (true)
      {

         pszFind = wildcard_next_stop(pszCriteria);

         if (pszFind == nullptr)
            break;

         iLen = pszFind - pszCriteria;

         if (*pszFind == '?')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            if (*pszValue == '\0')
               return false;

            pszCriteria++;
            pszValue++;

         }
         else if (*pszFind == '*')
         {

            if (pszFind > pszCriteria)
            {
               if (ansi_count_compare(pszValue, pszCriteria, iLen) != 0)
                  return false;
               pszValue += iLen;
               pszCriteria += iLen;
            }

            pszStop = wildcard_next_stop(pszFind + 1);

            if (pszStop == nullptr)
               pszStop = pszFind + ansi_length(pszFind);

            iLen = pszStop - (pszFind + 1);

            pszValue = ansi_count_find_string(pszValue, pszFind + 1, iLen);

            if (pszValue == nullptr)
               return false;

            pszValue = pszValue + iLen;
            pszCriteria = pszStop;

         }
         else
         {
            __throw(::exception::exception("not_expected, check wildcard_next_stop function"));
         }


      }

      if (ansi_compare(pszValue, pszCriteria) != 0)
         return false;

      return true;

   }




   //CLASS_DECL_APEX const char* ansi_concatenate_and_duplicate(const char* psz1, const char* psz2)
   //{

   //   return yoshi_strcat(psz1, psz2, false);

   //}

   //CLASS_DECL_APEX const char* strcat_and_dup2(const char* psz1, const char* psz2)
   //{

   //   return yoshi_strcat(psz1, psz2, true);

   //}







