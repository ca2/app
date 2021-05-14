//
//  process.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//
#include "framework.h"


void process_get_os_priority(i32 * piOsPriority,  i32 nCa2Priority)
{

   int iOsPriority;

   int iCa2Min;

   int iCa2Max;

   int iOsMax = 20;

   int iOsMin = -20;

   if(nCa2Priority == ::priority_normal)
   {

      iOsPriority = 0;

   }
   else if(nCa2Priority > ::priority_normal)
   {

      iCa2Min = (int) ::priority_normal;

      iCa2Max = 99;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }
   else
   {

      iCa2Min = 0;

      iCa2Max = (int) ::priority_normal;

      iOsPriority = (iOsMin + iOsMax) / 2;

   }

   *piOsPriority = iOsPriority;

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
