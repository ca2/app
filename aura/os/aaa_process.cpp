#include "framework.h"
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


CLASS_DECL_AURA bool is_command_line_param_true(string& strValue, const char* pszCommandLine, const char* pszParam, bool bDefault)
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


CLASS_DECL_AURA string process_platform_dir_name()
{

#if defined(_M_IX86)

   return "Win32";

#else

   return "x64";

#endif

}

CLASS_DECL_AURA string process_platform_dir_name2()
{

#if defined(_M_IX86)

   return "x86";

#else

   return "x64";

#endif

}


CLASS_DECL_AURA string process_version_dir_name()
{

   return framework_is_stage() ? "stage" : "basis";

}


//extern "C"
//{

   CLASS_DECL_AURA int_bool IsProcessRunning(::u32 pid)
   {

#ifdef WINDOWS

      HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);

      ::u32 ret = WaitForSingleObject(process, 0);

      CloseHandle(process);

      return ret == WAIT_TIMEOUT;

#else

      int i = kill(pid, 0);

      return (i == 0) || (i == -1 && errno == EPERM);

#endif

   }

//}


void prepare_argc_argv(int & argc, char ** argv, char * cmd_line)
{

   char * pPtr = nullptr;

   char * point;

   char * psz = cmd_line;

   enum e_state
   {

      state_initial,

      state_quote,

      state_non_space,

   };

   e_state e = state_initial;

   char quote = '\0';

   while(psz != nullptr && *psz != '\0')
   {

      if(e == state_initial)
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

            point = (char *) ::str::utf8_inc(psz);

            *psz = '\0';

            psz = point;

            e = state_initial;

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

            point = (char *) ::str::utf8_inc(psz);

            *psz = '\0';

            psz = point;

            e = state_initial;

         }
         else
         {

            psz = (char *) ::str::utf8_inc(psz);

         }

      }

   }

   argv[argc] = nullptr;

}


CLASS_DECL_AURA string executable_title_from_appid(string str)
{

   str.replace("-", "_");

   str.replace("/", "_");

   return str;

}


