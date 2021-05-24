// argcargv.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"


//wchar_t* _argv[_MAX_CMD_LINE_ARGS + 1];
//static wchar_t* _rawCmd = 0;






#define new ACME_NEW


string_array get_c_args_from_string(const char * psz)
{

   string_array stra;

   if (psz == nullptr)
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   const char * pszEnd = psz + strlen(psz);

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

         str = ::str::consume_quoted_value(psz, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_quoted_value(psz, pszEnd);

      }
      else
      {

         const char * pszValueStart = psz;

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






// it was extracted from macOS code base
// it is prepared for a command line supplied by macOS*1?
// (*1.macOS:
//          proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
// return info.pbsd.pbi_comm;
// )
string_array command_arguments_from_command_line(const ::string & strCommandLine)
{

   string_array stra;

   string strArg;

   const char * psz = strCommandLine;

   string strChar;

   while(*psz != '\0')
   {

      strChar = ::str::get_utf8_char(psz);

      if(strChar.is_empty())
      {

         break;

      }

      psz += strChar.get_length();

      if(strChar == "\"")
      {

         while(*psz != '\0')
         {

            strChar = ::str::get_utf8_char(psz);

            if(strChar.is_empty())
            {

               goto end;

            }
            else if(strChar == "\"")
            {

               break;

            }

            psz += strChar.get_length();


            if(strChar == "\\")
            {

               strChar = ::str::get_utf8_char(psz);

               if(strChar.is_empty())
               {

                  goto end;

               }

               psz += strChar.get_length();

               if(strChar == "n")
               {

                  strArg += "\n";

               }
               else
               {

                  strArg += strChar;

               }

            }
            else
            {

               strArg += strChar;

            }

         }

         stra.add(strArg);

         strArg.Empty();

      }
      else if(strChar == " ")
      {

         stra.add(strArg);

         strArg.Empty();

      }
      else if(strChar == "\\")
      {

         strChar = ::str::get_utf8_char(psz);

         if(strChar.is_empty())
         {

            goto end;

         }

         psz += strChar.get_length();

         if(strChar == "n")
         {

            strArg += "\n";

         }
         else
         {

            strArg += strChar;

         }

      }
      else
      {

         strArg += strChar;

      }


   }

end:

   if(strArg.has_char())
   {

      stra.add(strArg);

   }

   return stra;

}


bool argcargv_find_parameter(int argc, char * argv[], const char * pszParameter)
{

   for(int i = 1; i < argc; i++)
   {

      if(!strcmp(argv[i], pszParameter))
      {

         return i;

      }

   }

   return -1;

}


bool argcargv_contains_parameter(int argc, char * argv[], const char * pszParameter)
{

   return argcargv_find_parameter(argc, argv, pszParameter) >= 0;

}



