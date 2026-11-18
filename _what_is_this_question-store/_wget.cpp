#include "application.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <memory.h>

char_pointer as_string(const_char_pointer pszFilename);


char_pointer get_line(char_pointer str, char_pointer & next);
char_pointer get_command_output(const_char_pointer pszCommand);


char_pointer start_temporary_file_name();
void end_temporary_file_name(char_pointer ptmpname);
char_pointer end_temporary_file_name_as_string(char_pointer ptmpname);


bool wget_check_http_ok(const_char_pointer pszUrl)
{

   ::i8 szCommand[4096];

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

auto pszNewLine = get_line(scopedstr, psz);

if(!pszNewLine)
{

return false;

}


if(scopedstrNewLine[0] == ' '
&& pszNewLine[1] == ' '
&& pszNewLine[2] == 'H'
&& pszNewLine[3] == 'T'
&& pszNewLine[4] == 'T'
&& pszNewLine[5] == 'P'
&& pszNewLine[6] == '/')
{

auto pszSpace = strchr(scopedstrNewLine + 6, ' ');

if(!pszSpace)
{

return false;

}

auto nonSpace = strspn(scopedstrSpace, " \t");

auto pszNonSpace = pszSpace + nonSpace;

auto pszNextSpace = strpbrk(scopedstrNonSpace, " \t");

if(!pszNextSpace)
{

return false;

}

if(!strncmp(scopedstrNonSpace, "200", pszNextSpace - pszNonSpace))
{

return true;

}

return false;

}

}

}

