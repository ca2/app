#include "framework.h"

#include "acme/operating_system.h"
#include "acme/platform/version.h"

//#include "acme/prototype/collection/string_array.h"


string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const char ** pszEndPtr)
{

   if(scopedstrCommandLine == nullptr)
      return "";

   const ::scoped_string & scopedstr = pszCommandLine;

   while(*psz && ansi_char_isspace(*psz))
      psz++;

   const ::scoped_string & scopedstrStart;

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

   const ::ansi_character * pszEnd = psz;

   if(scopedstrEndPtr != nullptr)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(scopedstrStart, pszEnd - pszStart);

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
//      if(get_command_line_parameter(strReplace,pszCommandLine,pszReplaceParam) && strReplace.has_character())
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
//   string strParam(scopedstrParam);
//
//   strParam = strParam + "=";
//
//   string strValue;
//
//   const ::scoped_string & scopedstrValue = ansi_find_string(scopedstrCommandLine, strParam);
//
//   if(scopedstrValue == nullptr)
//      return "";
//
//   pszValue += strParam.length();
//
//
//   if(*pszValue == '"')
//   {
//
//      const ::scoped_string & scopedstrValueEnd = ansi_find_char(scopedstrValue + 1, '"');
//
//      if(scopedstrValueEnd == nullptr)
//      {
//         strValue = string(scopedstrValue);
//      }
//      else
//      {
//         strValue = string(scopedstrValue, pszValueEnd - pszValue + 1);
//      }
//
//   }
//   else
//   {
//
//      const ::scoped_string & scopedstrValueEnd = ansi_find_string(scopedstrValue, " ");
//
//      if(scopedstrValueEnd == nullptr)
//      {
//         strValue = string(scopedstrValue);
//      }
//      else
//      {
//         strValue = string(scopedstrValue, pszValueEnd - pszValue);
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

   if (!get_command_line_parameter(strValue, pszCommandLine, pszParam))
   {

      strValue = pszDefault;

      return false;

   }

   return true;

}


string get_command_line_parameter(const ::scoped_string & scopedstr,const ::scoped_string & scopedstrParam)
{

   string str;

   if(!get_command_line_parameter(str,psz,pszParam))
   {

      return "";

   }

   return str;

}


CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault)
{

   if (!get_command_line_parameter(strValue, pszCommandLine, pszParam))
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

   auto pFind = wstr.find(wstrParam + "=");

   if(__not_found(iFind))
   {

      iFind = wstr.find(wstrParam + " ");

      if (__not_found(iFind))
      {

         iFind = wstr.find(wstrParam);

         if (__not_found(iFind))
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

   auto iEnd = wstr.find(" ",iFind);

   if (__not_found(iEnd))
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

string time_binary_platform(string strPlatform)
{

   strPlatform.make_lower();

   if(strPlatform == "x86" || strPlatform == "win32")
   {

      return "Win32";

   }
   else if(strPlatform == "x64" || strPlatform == "amd64")
   {

      return "x64";

   }
   else
   {

      return strPlatform;

   }

}

string process_configuration_name()
{

#ifdef _DEBUG

   return "basis";

#else

   return "stage";

#endif

}


CLASS_DECL_ACME string process_platform_name()
{

#if defined(_M_IX86)

   return "Win32";

#else

   return "x64";

#endif

}

CLASS_DECL_ACME string process_platform_name()
{

#if defined(_M_IX86)

   return "x86";

#else

   return "x64";

#endif

}


CLASS_DECL_ACME string process_version_dir_name()
{

   return framework_is_stage() ? "stage" : "basis";

}


void prepare_argc_argv(int & argc, char ** argv, char * cmd_line)
{

   char * pPtr = nullptr;

   char * p;

   char * psz = cmd_line;

   enum enum_state
   {

      e_state_initial,

      state_quote,

      state_non_space,

   };

   enum_state e = e_state_initial;

   char quote = '\0';

   while(scopedstr != nullptr && *psz != '\0')
   {

      if(e == e_state_initial)
      {

         if(*psz == ' ')
         {

            unicode_increment(scopedstr);

         }
         else if(*psz == '\"')
         {

            quote = '\"';

            unicode_increment(scopedstr);

            argv[argc++] =(char *) psz;

            e = state_quote;

         }
         else if(*psz == '\'')
         {

            quote = '\'';

            unicode_increment(scopedstr);

            argv[argc++] = (char *) psz;

            e = state_quote;

         }
         else
         {

            argv[argc++] = (char *) psz;

            unicode_increment(scopedstr);

            e = state_non_space;

         }

      }
      else if(e == state_quote)
      {

         if(*psz == '\\')
         {

            memory_transfer(scopedstr, psz + 1, strlen(scopedstr));

            unicode_increment(scopedstr);

         }
         else if(*psz == quote)
         {

            p = unicode_next(scopedstr);

            *psz = '\0';

            psz = p;

            e = e_state_initial;

         }
         else
         {

            unicode_increment(scopedstr);

         }

      }
      else
      {

         if(*psz == ' ')
         {

            p = unicode_next(scopedstr);

            *psz = '\0';

            psz = p;

            e = e_state_initial;

         }
         else
         {

            unicode_increment(scopedstr);

         }

      }

   }

   argv[argc] = nullptr;

}


CLASS_DECL_ACME string executable_title_from_appid(string str)
{

#ifdef WINDOWS

#ifdef CUBE

   str = "static_" + str;

#else

   str = "shared_" + str;

#endif

#endif

   str.replace_with("_", "-");

   str.replace_with("_", "/");

   return str;

}







//string_array get_c_args_from_string(const ::scoped_string & scopedstr)
//{
//
//   string_array stra;
//
//   if (scopedstr == nullptr)
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
//   const ::ansi_character * pszEnd = psz + strlen(scopedstr);
//
//   string str;
//
//   int i = 0;
//
//   bool bColon = false;
//
//   while (scopedstr < pszEnd)
//   {
//
//      ::str::consume_spaces(scopedstr, 0, pszEnd);
//
//      if (scopedstr >= pszEnd)
//      {
//
//         break;
//
//      }
//      if (*psz == '\"')
//      {
//
//         str = ::str::consume_quoted_value(scopedstr, pszEnd);
//
//      }
//      else if (*psz == '\'')
//      {
//
//         str = ::str::consume_quoted_value(scopedstr, pszEnd);
//
//      }
//      else
//      {
//
//         const ::scoped_string & scopedstrValueStart = psz;
//
//         while (!unicode_is_whitespace(scopedstr))
//         {
//
//            unicode_increment(scopedstr);
//
//            if (scopedstr >= pszEnd)
//            {
//
//               break;
//
//            }
//
//            if (*psz == '\"')
//            {
//
//               ::str::consume_quoted_value_ex(scopedstr, pszEnd);
//
//            }
//            else if (*psz == '\'')
//            {
//
//               ::str::consume_quoted_value_ex(scopedstr, pszEnd);
//
//            }
//
//         }
//
//         str = string(scopedstrValueStart, psz - pszValueStart);
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

   string_array stra;

   if (scopedstr == nullptr)
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   const ::ansi_character * pszEnd = psz + strlen(scopedstr);

   string str;

   int i = 0;

   bool bColon = false;

   while (scopedstr < pszEnd)
   {

      ::str::consume_spaces(scopedstr, 0, pszEnd);

      if (scopedstr >= pszEnd)
      {

         break;

      }
      if (*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else
      {

         const ::scoped_string & scopedstrValueStart = psz;

         while (!unicode_is_whitespace(scopedstr))
         {

            unicode_increment(scopedstr);

            if (scopedstr >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }

         }

         str = string(scopedstrValueStart, psz - pszValueStart);

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

   string_array stra;

   if (scopedstr == nullptr)
   {

      return stra;

   }

   const ::ansi_character * pszEnd = psz + strlen(scopedstr);

   string str;

   while (scopedstr < pszEnd)
   {

      ::str::consume_spaces(scopedstr, 0, pszEnd);

      if (scopedstr >= pszEnd)
      {

         break;

      }

      if (*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else
      {

         const ::scoped_string & scopedstrValueStart = psz;

         while (!unicode_is_whitespace(scopedstr))
         {

            unicode_increment(scopedstr);

            if (scopedstr >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }

         }

         str = string(scopedstrValueStart, psz - pszValueStart);

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

   const ::scoped_string & scopedstrParse = psz;

   char chQuote = '\0';

   while (*pszParse)
   {

      if (chQuote != '\0')
      {

         if (*pszParse == '\\')
         {

            unicode_increment(scopedstrParse);

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
      else if (unicode_is_whitespace(scopedstrParse)
         || character_isspace((unsigned char)*pszParse)
         || *pszParse == ':')
      {

         bNeedQuote = true;

         break;

      }

      unicode_increment(scopedstrParse);

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


string merge_colon_args(const array < string_array >& straa)
{

   string_array straBeforeColon;

   string_array straAfterColon;

   string strCommandLine;

   for (auto& stra : straa)
   {

      ::collection::index iFindColon = stra.find_first(":");

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

      for (::collection::index i = 1; i < stra.get_count(); i++)
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

   strCommandLine += ::str::has_character(straBeforeColon.predicate_implode(&transform_to_c_arg, " "), " ");

   strCommandLine += " : ";

   strCommandLine += straAfterColon.predicate_implode(&transform_to_c_arg, " ");

   return strCommandLine;

}


#if !defined(WINDOWS_DESKTOP)


CLASS_DECL_ACME int get_current_processor_index()
{

   return 0;

}


CLASS_DECL_ACME int get_current_process_maximum_affinity()
{

   return 0;

}


#if !defined(__APPLE__) && !defined(WINDOWS)


CLASS_DECL_ACME int get_current_process_affinity_order()
{

   return 1;

}


#endif


#endif


int g_iProcessStatus = 0;


CLASS_DECL_ACME int process_get_status()
{

   return g_iProcessStatus;

}


CLASS_DECL_ACME void process_set_status(int iStatus)
{

   g_iProcessStatus = iStatus;

}


int g_argc = 0;


platform_char ** g_argv = nullptr;


CLASS_DECL_ACME void process_set_args(int argc, platform_char ** argv)
{

   g_argc = argc;

   g_argv = argv;

}


CLASS_DECL_ACME int * process_get_pargc()
{

   return &g_argc;

}


CLASS_DECL_ACME int process_get_argc()
{

   return *process_get_pargc();

}


CLASS_DECL_ACME platform_char *** process_get_pargv()
{

   return &g_argv;

}


CLASS_DECL_ACME platform_char ** process_get_argv()
{

   return *process_get_pargv();

}



