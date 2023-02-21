// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSørensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "command_line.h"
//#include "string.h"
//#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/string/str.h"


#define NULCHAR     '\0'
#define TABCHAR     '\t'
#define SLASHCHAR   '\\'
#define SPACECHAR   ' '
#define DQUOTECHAR  '\"'


void ansi_parse_command_line(char * cmdstart, char ** argv, char * args, i32 * numargs, i32 * numchars)
{


   char * p;
   char c;
   i32 inquote;                    /* 1 = inside quotes */
   i32 copychar;                   /* 1 = copy char to *args */
   u32 numslash;              /* num of backslashes seen */

   *numchars = 0;
   *numargs = 1;                   /* the program name at least */

   /* first scan the program name, copy it, and ::count the bytes */
   p = cmdstart;
   if (argv)
      *argv++ = args;

#ifdef WILDCARD
   /* To handle later wild card expansion, we prefix each entry by
   it's first character before quote handling.  This is done
   so _[w]cwild() knows whether to expand an entry or not. */
   if (args)
      *args++ = *p;
   ++ * numchars;

#endif  /* WILDCARD */

   /* A quoted program name is handled here. The handling is much
      simpler than for other arguments. Basically, whatever lies
      between the leading double-quote and next one, or a terminal nullptr
      character is simply accepted. Fancier handling is not required
      because the program name must be a legal NTFS/HPFS file name.
      Note that the double-quote characters are not copied, nor do they
      contribute to numchars. */
   if (*p == DQUOTECHAR)
   {
      /* scan from just past the first double-quote through the next
         double-quote, or up to a nullptr, whichever comes first */
      while ((*(++p) != DQUOTECHAR) && (*p != NULCHAR))
      {

         ++ * numchars;
         if (args)
            *args++ = *p;
      }
      /* append the terminating nullptr */
      ++ * numchars;
      if (args)
         *args++ = NULCHAR;

      /* if we stopped on a double-quote (usual case), skip over it */
      if (*p == DQUOTECHAR)
         p++;
   }
   else
   {
      /* Not a quoted program name */
      do
      {
         ++ * numchars;
         if (args)
            *args++ = *p;

         c = (char)*p++;


      } while (c != SPACECHAR && c != NULCHAR && c != TABCHAR);

      if (c == NULCHAR)
      {
         p--;
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

      if (*p)
      {
         while (*p == SPACECHAR || *p == TABCHAR)
            ++p;
      }

      if (*p == NULCHAR)
         break;              /* end of args */

      /* scan an argument */
      if (argv)
         *argv++ = args;     /* store ptr to arg */
      ++ * numargs;

#ifdef WILDCARD
      /* To handle later wild card expansion, we prefix each entry by
      it's first character before quote handling.  This is done
      so _[w]cwild() knows whether to expand an entry or not. */
      if (args)
         *args++ = *p;
      ++ * numchars;

#endif  /* WILDCARD */

      /* loop through scanning one argument */
      for (;;)
      {
         copychar = 1;
         /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
            2N+1 backslashes + " ==> N backslashes + literal "
            N backslashes ==> N backslashes */
         numslash = 0;
         while (*p == SLASHCHAR)
         {
            /* ::count number of backslashes for use below */
            ++p;
            ++numslash;
         }
         if (*p == DQUOTECHAR)
         {
            /* if 2N backslashes before, start/end quote, otherwise
                copy literally */
            if (numslash % 2 == 0)
            {
               if (inquote)
               {
                  if (p[1] == DQUOTECHAR)
                     p++;    /* Double quote inside quoted string */
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
            ++ * numchars;
         }

         /* if at end of arg, break loop */
         if (*p == NULCHAR || (!inquote && (*p == SPACECHAR || *p == TABCHAR)))
            break;

         if (copychar)
         {
            if (args)
               *args++ = *p;
            ++ * numchars;
         }
         ++p;
         //#endif  /* _MBCS */
      }

      /* nullptr-terminate the argument */

      if (args)
         *args++ = NULCHAR;          /* terminate string */
      ++ * numchars;
   }

   /* We put one last argument in -- a nullptr ptr */
   if (argv)
      *argv++ = nullptr;
   ++ * numargs;

}


string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const char ** pszEndPtr)
{

   if(scopedstrCommandLine.is_empty())
      return "";

   const char * psz = scopedstrCommandLine.begin();

   while(*psz && ansi_char_isspace(*psz))
      psz++;

   const char * pszStart;

   bool bQuoted = *psz == '\"';

   if(bQuoted)
   {
      psz++;
      pszStart = psz;
      while(*psz != '\0' && *psz != '\"')
         psz++;
   }
   else
   {
      pszStart = psz;
      while(*psz != '\0' &&!ansi_char_isspace(*psz))
         psz++;
   }

   const char * pszEnd = psz;

   if(pszEndPtr != nullptr)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(pszStart, pszEnd - pszStart);

}



//string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrIfParamValue, const ::scoped_string & scopedstrReplaceParam)
//{
//
//   string strValue;
//
//   get_command_line_parameter(strValue, pszCommandLine,pszParam);
//
//   if(strValue == pszIfParamValue)
//   {
//
//      string strReplace;
//
//      if(get_command_line_parameter(strReplace,pszCommandLine,pszReplaceParam) && strReplace.has_char())
//      {
//
//         strValue = strReplace;
//
//      }
//
//   }
//
//   ::str::_008Trim(strValue);
//
//   return strValue;
//
//}

//string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam)
//{
//
//   string strParam(pszParam);
//
//   strParam = strParam + "=";
//
//   string strValue;
//
//   const ::scoped_string & scopedstrValue = ansi_find_string(pszCommandLine, strParam);
//
//   if(pszValue == nullptr)
//      return "";
//
//   pszValue += strParam.length();
//
//
//   if(*pszValue == '"')
//   {
//
//      const ::scoped_string & scopedstrValueEnd = ansi_find_char(pszValue + 1, '"');
//
//      if(pszValueEnd == nullptr)
//      {
//         strValue = string(pszValue);
//      }
//      else
//      {
//         strValue = string(pszValue, pszValueEnd - pszValue + 1);
//      }
//
//   }
//   else
//   {
//
//      const ::scoped_string & scopedstrValueEnd = ansi_find_string(pszValue, " ");
//
//      if(pszValueEnd == nullptr)
//      {
//         strValue = string(pszValue);
//      }
//      else
//      {
//         strValue = string(pszValue, pszValueEnd - pszValue);
//      }
//
//   }
//
//   return ::str::trim_any_quotes(strValue.trimmed());
//
//
//}


bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDefault)
{

   if (!get_command_line_parameter(strValue, scopedstrCommandLine, scopedstrParam))
   {

      strValue = scopedstrDefault;

      return false;

   }

   return true;

}


string get_command_line_parameter(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrParam)
{

   string str;

   if(!get_command_line_parameter(str, scopedstr, scopedstrParam))
   {

      return "";

   }

   return str;

}


CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault)
{

   if (!get_command_line_parameter(strValue, scopedstrCommandLine, scopedstrParam))
   {

      return bDefault;

   }

   if (strValue.is_empty())
   {

      return true;

   }

   if (strValue.case_insensitive_order("true") == 0)
   {

      return true;

   }

   if (strValue.case_insensitive_order("yes") == 0)
   {

      return true;

   }

   if (strValue.case_insensitive_order("y") == 0)
   {

      return true;

   }

   if (atoi(strValue) > 0)
   {

      return true;

   }

   return false;

}


bool get_command_line_parameter(string & wstrValue,const ::scoped_string & scopedstr,const ::scoped_string & scopedstrParam)
{

   string wstr(scopedstr);

   string wstrParam(scopedstrParam);

   auto iFind = wstr.find_index(wstrParam + "=");

   if(not_found(iFind))
   {

      iFind = wstr.find_index(wstrParam + " ");

      if (not_found(iFind))
      {

         iFind = wstr.find_index(wstrParam);

         if (not_found(iFind))
         {

            return false;

         }
         else if(iFind == wstr.length() - wstrParam.length())
         {

            wstrValue = "";

            return true;

         }
         else
         {

            return false;

         }

      }
      else
      {

         wstrValue = "";

         return true;

      }

   }

   auto iEnd = wstr.find_index(" ",iFind);

   if (not_found(iEnd))
   {

      wstrValue = wstr.substr(iFind + wstrParam.length() + 1);

   }
   else
   {

      wstrValue = wstr.substr(iFind + wstrParam.length() + 1,iEnd - iFind - wstrParam.length() - 1);

   }

   ::str::trim_any_quotes(wstrValue);

   return true;

}





//CLASS_DECL_ACME string process_platform_name()
//{
//
//#if defined(_M_IX86)
//
//   return "x86";
//
//#else
//
//   return "x64";
//
//#endif
//
//}






//#define memory_new ACME_NEW


//string_array get_c_args_from_string(const ::scoped_string & scopedstr)
//{
//
//   string_array stra;
//
//   if (psz == nullptr)
//   {
//
//      return stra;
//
//   }
//
//   string_array straBeforeColon;
//
//   string_array straAfterColon;
//
//   const ::ansi_character * pszEnd = psz + strlen(psz);
//
//   string str;
//
//   int i = 0;
//
//   bool bColon = false;
//
//   while (psz < pszEnd)
//   {
//
//      ::str::consume_spaces(psz, 0, pszEnd);
//
//      if (psz >= pszEnd)
//      {
//
//         break;
//
//      }
//      if (*psz == '\"')
//      {
//
//         str = ::str::consume_quoted_value(psz, pszEnd);
//
//      }
//      else if (*psz == '\'')
//      {
//
//         str = ::str::consume_quoted_value(psz, pszEnd);
//
//      }
//      else
//      {
//
//         const ::scoped_string & scopedstrValueStart = psz;
//
//         while (!unicode_is_whitespace(psz))
//         {
//
//            unicode_increment(psz);
//
//            if (psz >= pszEnd)
//            {
//
//               break;
//
//            }
//
//            if (*psz == '\"')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//            else if (*psz == '\'')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//
//         }
//
//         str = string(pszValueStart, psz - pszValueStart);
//
//      }
//
//      if (str == ":")
//      {
//
//         bColon = true;
//
//      }
//      else if (!bColon && (i == 0 || str[0] != '-'))
//      {
//
//         straBeforeColon.add(str);
//
//      }
//      else
//      {
//
//         straAfterColon.add(str);
//
//      }
//
//      i++;
//
//   }
//
//   stra = straBeforeColon;
//
//   if (straAfterColon.has_elements())
//   {
//
//      stra.add(":");
//
//      stra += straAfterColon;
//
//   }
//
//   return stra;
//
//}


string_array get_c_args_from_c(const ::scoped_string & scopedstr)
{
   
   if (scopedstr.is_empty())
   {

      return {};

   }

   auto range = scopedstr();

   string_array stra;

   string_array straBeforeColon;

   string_array straAfterColon;

   string str;

   int i = 0;

   bool bColon = false;

   while (range.has_char())
   {

      range.consume_spaces(0);

      if (range.is_empty())
      {

         break;

      }
      if (*range.m_begin == '\"')
      {

         str = range.consume_c_quoted_value();

      }
      else if (*range.m_begin == '\'')
      {

         str = range.consume_c_quoted_value();

      }
      else
      {

         const char * pszValueStart = range.m_begin;

         while (!unicode_is_whitespace(range.m_begin))
         {

            unicode_increment(range.m_begin);

            if (range.is_empty())
            {

               break;

            }

            if (*range.m_begin == '\"')
            {

               range.consume_quoted_value_ex();

            }
            else if (*range.m_begin == '\'')
            {

               range.consume_quoted_value_ex();

            }

         }

         str = string(pszValueStart, range.m_begin - pszValueStart);

      }

      if (str == ":")
      {

         bColon = true;

      }
      else if (!bColon && (i == 0 || str[0] != '-'))
      {

         straBeforeColon.add(str);

      }
      else
      {

         straAfterColon.add(str);

      }

      i++;

   }

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


string_array get_c_args_for_c(const ::scoped_string & scopedstr)
{

   auto range = scopedstr();

   string_array stra;

   string str;

   while (range.has_char())
   {

      range.consume_spaces(0);

      if (range.is_empty())
      {

         break;

      }

      if (*range.m_begin == '\"')
      {

         str = range.consume_c_quoted_value();

      }
      else if (*range.m_begin == '\'')
      {

         str = range.consume_c_quoted_value();

      }
      else
      {

         const char * pszValueStart = range.m_begin;

         while (!unicode_is_whitespace(range.m_begin))
         {

            unicode_increment(range.m_begin);

            if (range.is_empty())
            {

               break;

            }

            if (*range.m_begin == '\"')
            {

               range.consume_quoted_value_ex();

            }
            else if (*range.m_begin == '\'')
            {

               range.consume_quoted_value_ex();

            }

         }

         str.assign(pszValueStart, range.m_begin - pszValueStart);

      }

      stra.add(str);

   }

   return stra;

}


string_array get_c_args(int argc, char** argv)
{

   string_array straBeforeColon;

   string_array straAfterColon;

   if (argc > 0)
   {

      straBeforeColon.add(argv[0]);

   }

   bool bColon = false;

   for (int i = 1; i < argc; i++)
   {

      if (strcmp(argv[i], ":") == 0)
      {
         bColon = true;
      }
#ifdef WINDOWS
         else if (bColon || straAfterColon.has_elements() || argv[i][0] == '-' || (argv[i][0] == '/' && strlen(argv[i]) == 2))
#else
      else if (bColon || straAfterColon.has_elements() || argv[i][0] == '-')
#endif
      {

         straAfterColon.add(argv[i]);

      }
      else
      {

         straBeforeColon.add(argv[i]);

      }

   }

   string_array stra;

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


typedef size_t FN_GET_STRING(char* psz, size_t s);


typedef FN_GET_STRING* PFN_GET_STRING;

//
//#ifdef __APPLE__
//
//
//
//
//#endif


string transform_to_c_arg(const ::scoped_string & scopedstr)
{

   bool bNeedQuote = false;

   const char * psz = scopedstr.begin();

   const char * pszParse = psz;

   char chQuote = '\0';

   while (*pszParse)
   {

      if (chQuote != '\0')
      {

         if (*pszParse == '\\')
         {

            unicode_increment(pszParse);

         }
         else if (*pszParse == chQuote)
         {

            chQuote = '\0';

         }

      }
      else if (*pszParse == '\'')
      {

         chQuote = '\'';

      }
      else if (*pszParse == '\"')
      {

         chQuote = '\"';

      }
      else if (unicode_is_whitespace(pszParse) || *pszParse == ':')
      {

         bNeedQuote = true;

         break;

      }

      unicode_increment(pszParse);

   }

   if (bNeedQuote)
   {

      return string("\"") + ::str::replace_with("\\\"", "\"", psz) + "\"";

   }
   else
   {

      return psz;

   }

}


string transform_to_quoted_value(const ::scoped_string & scopedstr)
{

   string str(scopedstr);

   str.replace_with("\\\\", "\\");

   str.replace_with("\\\"", "\"");

   return "\"" + str + "\"";

}


string merge_colon_args(const array < string_array >& str2a)
{

   string_array straBeforeColon;

   string_array straAfterColon;

   string strCommandLine;

   for (auto& stra : str2a)
   {

      index iFindColon = stra.find_first(":");

      if (stra.get_size() > 0 && iFindColon != 0)
      {

         if (strCommandLine.is_empty())
         {

            string strArg = stra[0];

            strCommandLine = transform_to_quoted_value(strArg);

         }

      }

      if (iFindColon < 0)
      {

         iFindColon = stra.get_size();

      }

      for (index i = 1; i < stra.get_count(); i++)
      {

         string str = stra[i];

         if (i < iFindColon)
         {

            string strArg = str;

            string strQuotedValue = transform_to_quoted_value(strArg);

            straBeforeColon.add(strQuotedValue);

         }
         else if (i > iFindColon)
         {

            if (str.case_insensitive_begins_eat("app="))
            {

               if (straAfterColon.find_first_begins("app=") >= 0) // fixed case when added below :D..O
               {

                  straAfterColon.add("fallback_app=" + str);

               }
               else
               {

                  straAfterColon.add("app=" + str); // fixed case :) (excuses, excuses...)

               }

            }
            else
            {

               straAfterColon.add(str);

            }

         }

      }

   }

   strCommandLine += ::str::has_char(straBeforeColon.predicate_implode(&transform_to_c_arg, " "), " ");

   strCommandLine += " : ";

   strCommandLine += straAfterColon.predicate_implode(&transform_to_c_arg, " ");

   return strCommandLine;

}


#if !defined(WINDOWS_DESKTOP)


CLASS_DECL_ACME i32 get_current_processor_index()
{

   return 0;

}


CLASS_DECL_ACME i32 get_current_process_maximum_affinity()
{

   return 0;

}


#if !defined(__APPLE__) && !defined(WINDOWS)


CLASS_DECL_ACME i32 get_current_process_affinity_order()
{

   return 1;

}


#endif


#endif

