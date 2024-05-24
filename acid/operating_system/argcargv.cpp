// argcargv.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
//#include "acid/primitive/collection/string_array.h"
#include "acid/exception/parsing.h"
#include "acid/primitive/string/str.h"
//#include "acid/primitive/string/ch12.h"
////#include "acid/exception/exception.h"
//wchar_t* _argv[_MAX_CMD_LINE_ARGS + 1];
//static wchar_t* _rawCmd = 0;









string_array get_c_args_from_string(const ::scoped_string & scopedstr)
{

   string_array stra;

   if (scopedstr.is_empty())
   {

      return stra;

   }
   
   auto range = scopedstr();

   string str;

   int i = 0;

   while (range.has_char())
   {

      range.consume_spaces(0);

      if (range.is_empty())
      {

         break;

      }
      if (*range.m_begin == '\"')
      {

         str = range.consume_quoted_value();

      }
      else if (*range.m_begin == '\'')
      {

         str = range.consume_quoted_value();

      }
      else
      {

         const char * pszValueStart = range.begin();

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

      stra.add(str);

      i++;

   }

   return stra;

}


string_array no_escape_get_c_args_from_string(const ::scoped_string & scopedstr)
{

   string_array stra;

   if (scopedstr.is_empty())
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   auto range = scopedstr();

   string str;

   int i = 0;

   bool bColon = false;

   while (range.is_empty())
   {

      range.consume_spaces(0);

      if (range.is_empty())
      {

         break;

      }
      if (*range.m_begin == '\"')
      {

         str = range.no_escape_consume_quoted_value();

      }
      else if (*range.m_begin == '\'')
      {

         str = range.no_escape_consume_quoted_value();

      }
      else
      {

         const char * pszValueStart = range.m_begin;

         char chQuote = '\0';

         while (!unicode_is_whitespace(range.m_begin))
         {

            unicode_increment(range.m_begin);

            if (range.is_empty())
            {

               break;

            }

            if (*range.m_begin == '\"')
            {

               if (chQuote == '\"')
               {



               }
               else if (chQuote == '\0')
               {

                  chQuote = '\"';

               }
               else
               {

                  //::str::no_escape_consume_quoted_value(psz, pszEnd);

                  throw ::parsing_exception("Quote character not expected here");

               }

            }
            else if (*range.m_begin == '\'')
            {

               if (chQuote == '\'')
               {



               }
               else if (chQuote == '\0')
               {

                  chQuote = '\'';

               }
               else
               {

                  //::str::no_escape_consume_quoted_value(psz, pszEnd);

                  throw ::parsing_exception("Quote character not expected here");

               }

               ////::str::no_escape_consume_quoted_value(psz, pszEnd);

               //throw ::parsing_exception("Quote character not expected here");

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

   const char * psz = strCommandLine.begin();

   string strChar;

   while(*psz != '\0')
   {

      strChar = get_utf8_char(psz);

      if(strChar.is_empty())
      {

         break;

      }

      psz += strChar.length();

      if(strChar == "\"")
      {

         while(*psz != '\0')
         {

            strChar = get_utf8_char(psz);

            if(strChar.is_empty())
            {

               goto end;

            }

            psz += strChar.length();

            if(strChar == "\"")
            {

               break;

            }
            else if(strChar == "\\")
            {

               strChar = get_utf8_char(psz);

               if(strChar.is_empty())
               {

                  goto end;

               }

               psz += strChar.length();

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

         strArg.empty();

      }
      else if(strChar == " ")
      {
      
      	 strArg.trim();
      	 
      	 if(strArg.has_char())
      	 {

	    stra.add(strArg);

	    strArg.empty();
	         
	 }

      }
      else if(strChar == "\\")
      {

         strChar = get_utf8_char(psz);

         if(strChar.is_empty())
         {

            goto end;

         }

         psz += strChar.length();

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

   strArg.trim();

   if(strArg.has_char())
   {
   
      stra.add(strArg);

   }

   return stra;

}


int argcargv_find_parameter(int argc, char * argv[], const ::scoped_string & scopedstrParameter)
{

   for(int i = 1; i < argc; i++)
   {

      if(scopedstrParameter == argv[i])
      {

         return i;

      }

   }

   return -1;

}


bool argcargv_contains_parameter(int argc, char * argv[], const ::scoped_string & scopedstrParameter)
{

   return argcargv_find_parameter(argc, argv, scopedstrParameter) >= 0;

}



