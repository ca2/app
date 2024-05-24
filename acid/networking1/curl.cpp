#include "framework.h"
#include "acid/process/process.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <memory.h>

//char * get_line(char * str, char * & next);
//char * get_command_output(const char * pszCommand);


   bool application::_curl_check_http_ok(const char * pszUrl)
   {

      char szCommand[4096];

      strcpy(szCommand, "curl --silent -I ");

      strcat(szCommand, pszUrl);

      auto str = ::shell::command_output(szCommand);

      if(!str)
      {

         return false;

      }

      auto psz = str();

      while(true)
      {

         auto strNewLine = get_line(psz, psz);

         if(!strNewLine)
         {

            return false;

         }

         if(strNewLine[0] == 'H'
         && strNewLine[1] == 'T'
         && strNewLine[2] == 'T'
         && strNewLine[3] == 'P'
         && strNewLine[4] == '/')
         {

            auto pszSpace = strNewLine.find_character(' ', 4);

            if(!pszSpace)
            {

               return false;

            }

            auto pszNonSpace = pszSpace.skip_any_not_in( " \t");

            auto pszNewLine = pszNonSpace.find_any_in("\r\n");

            if(!pszNewLine)
            {

               return false;

            }

            if(!strncmp(pszNonSpace, "200", pszNewLine - pszNonSpace))
            {

               return true;

            }

            return false;

         }

      }

   }


   void curl_http_download(const char * pszFile, const char *pszUrl)
   {

      ::acid::string strDownloadCommand;

      strDownloadCommand = "curl ";
      strDownloadCommand += pszUrl;
      strDownloadCommand += " > ";
      strDownloadCommand += pszFile;

      ::system(strDownloadCommand);

   }


} // namespace acid



