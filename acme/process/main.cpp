#include "framework.h"
#include "acme/operating_system.h"
#include "acme/platform/version.h"


string consume_param(const char * pszCommandLine, const char ** pszEndPtr)
{

   if(pszCommandLine == nullptr)
      return "";

   const char * psz = pszCommandLine;

   while(*psz && ansi_char_is_space(*psz))
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
      while(*psz != '\0' &&!ansi_char_is_space(*psz))
         psz++;
   }

   const char * pszEnd = psz;

   if(pszEndPtr != nullptr)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(pszStart, pszEnd - pszStart);

}



//string get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam)
//{
//
//   string strValue;
//
//   get_command_line_param(strValue, pszCommandLine,pszParam);
//
//   if(strValue == pszIfParamValue)
//   {
//
//      string strReplace;
//
//      if(get_command_line_param(strReplace,pszCommandLine,pszReplaceParam) && strReplace.has_char())
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

//string get_command_line_param(const char * pszCommandLine, const char * pszParam)
//{
//
//   string strParam(pszParam);
//
//   strParam = strParam + "=";
//
//   string strValue;
//
//   const char * pszValue = ansi_find_string(pszCommandLine, strParam);
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
//      const char * pszValueEnd = ansi_find_char(pszValue + 1, '"');
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
//      const char * pszValueEnd = ansi_find_string(pszValue, " ");
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


bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam, const char * pszDefault)
{

   if (!get_command_line_param(strValue, pszCommandLine, pszParam))
   {

      strValue = pszDefault;

      return false;

   }

   return true;

}


string get_command_line_param(const char * psz,const char * pszParam)
{

   string str;

   if(!get_command_line_param(str,psz,pszParam))
   {

      return "";

   }

   return str;

}


CLASS_DECL_ACME bool is_command_line_param_true(string& strValue, const char* pszCommandLine, const char* pszParam, bool bDefault)
{

   if (!get_command_line_param(strValue, pszCommandLine, pszParam))
   {

      return bDefault;

   }

   if (strValue.is_empty())
   {

      return true;

   }

   if (strValue.compare_ci("true") == 0)
   {

      return true;

   }

   if (strValue.compare_ci("yes") == 0)
   {

      return true;

   }

   if (strValue.compare_ci("y") == 0)
   {

      return true;

   }

   if (atoi(strValue) > 0)
   {

      return true;

   }

   return false;

}


bool get_command_line_param(string & wstrValue,const char * psz,const char * pszParam)
{

   string wstr(psz);

   string wstrParam(pszParam);

   auto iFind = wstr.find(wstrParam + "=");

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

string process_configuration_dir_name()
{

#ifdef __DEBUG

   return "basis";

#else

   return "stage";

#endif

}


CLASS_DECL_ACME string process_platform_dir_name()
{

#if defined(_M_IX86)

   return "Win32";

#else

   return "x64";

#endif

}

CLASS_DECL_ACME string process_platform_dir_name2()
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

   while(psz != nullptr && *psz != '\0')
   {

      if(e == e_state_initial)
      {

         if(*psz == ' ')
         {

            psz = (char *) ::str::utf8_inc(psz);

         }
         else if(*psz == '\"')
         {

            quote = '\"';

            psz = (char *) ::str::utf8_inc(psz);

            argv[argc++] =(char *) psz;

            e = state_quote;

         }
         else if(*psz == '\'')
         {

            quote = '\'';

            psz = (char *) ::str::utf8_inc(psz);

            argv[argc++] = (char *) psz;

            e = state_quote;

         }
         else
         {

            argv[argc++] = (char *) psz;

            psz = (char *) ::str::utf8_inc(psz);

            e = state_non_space;

         }

      }
      else if(e == state_quote)
      {

         if(*psz == '\\')
         {

            __memmov(psz, psz + 1, strlen(psz));

            psz = (char *) ::str::utf8_inc(psz);

         }
         else if(*psz == quote)
         {

            p = (char *) ::str::utf8_inc(psz);

            *psz = '\0';

            psz = p;

            e = e_state_initial;

         }
         else
         {

            psz = (char *) ::str::utf8_inc(psz);

         }

      }
      else
      {

         if(*psz == ' ')
         {

            p = (char *) ::str::utf8_inc(psz);

            *psz = '\0';

            psz = p;

            e = e_state_initial;

         }
         else
         {

            psz = (char *) ::str::utf8_inc(psz);

         }

      }

   }

   argv[argc] = nullptr;

}


CLASS_DECL_ACME string executable_title_from_appid(string str)
{

   str.replace("-", "_");

   str.replace("/", "_");

   return str;

}




#define new ACME_NEW


//string_array get_c_args_from_string(const char* psz)
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
//   const char* pszEnd = psz + strlen(psz);
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
//         const char* pszValueStart = psz;
//
//         while (!::str::ch::is_whitespace(psz))
//         {
//
//            psz = str::utf8_inc(psz);
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


string_array get_c_args_from_c(const char* psz)
{

   string_array stra;

   if (psz == nullptr)
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   const char* pszEnd = psz + strlen(psz);

   string str;

   int i = 0;

   bool bColon = false;

   while (psz < pszEnd)
   {

      ::str::consume_spaces(psz, 0, pszEnd);

      if (psz >= pszEnd)
      {

         break;

      }
      if (*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(psz, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(psz, pszEnd);

      }
      else
      {

         const char* pszValueStart = psz;

         while (!::str::ch::is_whitespace(psz))
         {

            psz = str::utf8_inc(psz);

            if (psz >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(psz, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(psz, pszEnd);

            }

         }

         str = string(pszValueStart, psz - pszValueStart);

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


string_array get_c_args_for_c(const char* psz)
{

   string_array stra;

   if (psz == nullptr)
   {

      return stra;

   }

   const char* pszEnd = psz + strlen(psz);

   string str;

   while (psz < pszEnd)
   {

      ::str::consume_spaces(psz, 0, pszEnd);

      if (psz >= pszEnd)
      {

         break;

      }

      if (*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(psz, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(psz, pszEnd);

      }
      else
      {

         const char* pszValueStart = psz;

         while (!::str::ch::is_whitespace(psz))
         {

            psz = str::utf8_inc(psz);

            if (psz >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(psz, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(psz, pszEnd);

            }

         }

         str = string(pszValueStart, psz - pszValueStart);

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


string transform_to_c_arg(const char* psz)
{

   bool bNeedQuote = false;

   const char* pszParse = psz;

   char chQuote = '\0';

   while (*pszParse)
   {

      if (chQuote != '\0')
      {

         if (*pszParse == '\\')
         {

            pszParse = ::str::utf8_inc(pszParse);

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
      else if (::str::ch::is_whitespace(pszParse)
         || isspace((unsigned char)*pszParse)
         || *pszParse == ':')
      {

         bNeedQuote = true;

         break;

      }

      pszParse = ::str::utf8_inc(pszParse);

   }

   if (bNeedQuote)
   {

      return string("\"") + ::str::replace("\"", "\\\"", psz) + "\"";

   }
   else
   {

      return psz;

   }

}


string transform_to_quoted_value(const char* psz)
{

   string str(psz);

   str.replace("\\", "\\\\");

   str.replace("\"", "\\\"");

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

            if (str.begins_eat_ci("app="))
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



