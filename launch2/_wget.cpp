#include "application.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <memory.h>

char * as_string(const char * pszFilename);


char * get_line(char * str, char * & next);
char * get_command_output(const char * pszCommand);


char * start_temporary_file_name();
void end_temporary_file_name(char * ptmpname);
char * end_temporary_file_name_as_string(char * ptmpname);


bool wget_check_http_ok(const char * pszUrl)
{

   char szCommand[4096];

   auto ptmpname = start_temporary_file_name();

   sprintf(szCommand, "wget -o \"%s\" -S \"%s\"", ptmpname, pszUrl);

   ::system(szCommand);

   auto psz = end_temporary_file_name_as_string(ptmpname);

   if(!psz)
   {

      return false;

   }

while(true)
{

auto pszNewLine = get_line(psz, psz);

if(!pszNewLine)
{

return false;

}


if(pszNewLine[0] == ' '
&& pszNewLine[1] == ' '
&& pszNewLine[2] == 'H'
&& pszNewLine[3] == 'T'
&& pszNewLine[4] == 'T'
&& pszNewLine[5] == 'P'
&& pszNewLine[6] == '/')
{

auto pszSpace = strchr(pszNewLine + 6, ' ');

if(!pszSpace)
{

return false;

}

auto nonSpace = strspn(pszSpace, " \t");

auto pszNonSpace = pszSpace + nonSpace;

auto pszNextSpace = strpbrk(pszNonSpace, " \t");

if(!pszNextSpace)
{

return false;

}

if(!strncmp(pszNonSpace, "200", pszNextSpace - pszNonSpace))
{

return true;

}

return false;

}

}

}

