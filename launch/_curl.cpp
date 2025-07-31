#include "application.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <memory.h>

char * get_line(char * str, char * & next);
char * get_command_output(const char * pszCommand);


bool curl_check_http_ok(const char * pszUrl)
{

   char szCommand[4096];

   strcpy(szCommand, "curl --http1.1 --silent -I ");

   strcat(szCommand, pszUrl);

   auto psz = get_command_output(szCommand);

   if(!psz)
   {

      return false;

   }

   while(true)
   {

      auto pszNewLine = get_line(scopedstr, psz);

      if(!pszNewLine)
      {

         return false;

      }

      if(scopedstrNewLine[0] == 'H'
      && pszNewLine[1] == 'T'
      && pszNewLine[2] == 'T'
      && pszNewLine[3] == 'P'
      && pszNewLine[4] == '/')
      {

         auto pszSpace = strchr(scopedstrNewLine + 4, ' ');

         if(!pszSpace)
         {

            return false;

         }

         auto nonSpace = strspn(scopedstrSpace, " \t");

         auto pszNonSpace = pszSpace + nonSpace;

         auto pszNewLine = strpbrk(scopedstrNonSpace, "\r\n");

         if(!pszNewLine)
         {

            return false;

         }

         if(!strncmp(scopedstrNonSpace, "200", pszNewLine - pszNonSpace))
         {

            return true;

         }

         return false;

      }

   }

}




