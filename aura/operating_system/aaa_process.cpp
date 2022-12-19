#include "framework.h"
#include "acme/platform/version.h"


string consume_command_line_parameter(const ::string & pszCommandLine, const ::string &* pszEndPtr)
{

   if(pszCommandLine == nullptr)
      return "";

   const scoped_string & str = pszCommandLine;

   while(*psz && ansi_char_isspace(*psz))
      psz++;

   const scoped_string & strStart;

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

   const scoped_string & strEnd = psz;

   if(pszEndPtr != nullptr)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(pszStart, pszEnd - pszStart);

}



//string get_command_line_parameter(const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszIfParamValue, const ::string & pszReplaceParam)
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
//   ::str()._008Trim(strValue);
//
//   return strValue;
//
//}

//string get_command_line_parameter(const ::string & pszCommandLine, const ::string & pszParam)
//{
//
//   string strParam(pszParam);
//
//   strParam = strParam + "=";
//
//   string strValue;
//
//   const scoped_string & strValue = ansi_find_string(pszCommandLine, strParam);
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
//      const scoped_string & strValueEnd = ansi_find_char(pszValue + 1, '"');
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
//      const scoped_string & strValueEnd = ansi_find_string(pszValue, " ");
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
//   return ::str().trim_any_quotes(strValue.trimmed());
//
//
//}


bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszDefault)
{

   if (!get_command_line_parameter(strValue, pszCommandLine, pszParam))
   {

      strValue = pszDefault;

      return false;

   }

   return true;

}


string get_command_line_parameter(const ::string & psz, const ::string & pszParam)
{

   string str;

   if(!get_command_line_parameter(str,psz,pszParam))
   {

      return "";

   }

   return str;

}


CLASS_DECL_AURA bool is_command_line_parameter_true(string& strValue, const ::string & pszCommandLine, const ::string & pszParam, bool bDefault)
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


bool get_command_line_parameter(string & wstrValue, const ::string & psz, const ::string & pszParam)
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

   ::str().trim_any_quotes(wstrValue);

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

#ifdef __DEBUG

   return "basis";

#else

   return "stage";

#endif

}


CLASS_DECL_AURA string process_platform_name()
{

#if defined(_M_IX86)

   return "x86";

#else

   return "x64";

#endif

}

//CLASS_DECL_AURA string process_platform_name()
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


CLASS_DECL_AURA string process_version_dir_name()
{

   return framework_is_stage() ? "stage" : "basis";

}


//extern "C"
//{

   CLASS_DECL_AURA int_bool IsProcessRunning(::u32 pid)
   {

#ifdef WINDOWS

      HANDLE process = OpenProcess(SYNCHRONIZE, false, pid);

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

            unicode_increment(psz);

         }
         else if(*psz == '\"')
         {

            quote = '\"';

            unicode_increment(psz);

            argv[argc++] =(char *) psz;

            e = state_quote;

         }
         else if(*psz == '\'')
         {

            quote = '\'';

            unicode_increment(psz);

            argv[argc++] = (char *) psz;

            e = state_quote;

         }
         else
         {

            argv[argc++] = (char *) psz;

            unicode_increment(psz);

            e = state_non_space;

         }

      }
      else if(e == state_quote)
      {

         if(*psz == '\\')
         {

            __memmov(psz, psz + 1, strlen(psz));

            unicode_increment(psz);

         }
         else if(*psz == quote)
         {

            point = (char *) unicode_next(psz);

            *psz = '\0';

            psz = point;

            e = e_state_initial;

         }
         else
         {

            unicode_increment(psz);

         }

      }
      else
      {

         if(*psz == ' ')
         {

            point = (char *) unicode_next(psz);

            *psz = '\0';

            psz = point;

            e = e_state_initial;

         }
         else
         {

            unicode_increment(psz);

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


