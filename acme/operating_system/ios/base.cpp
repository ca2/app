#include "framework.h"

#include <string.h>
#include <stdio.h>

unsigned int
//rWINAPI
GetTempPathA(
unsigned int nBufferLength,
char * lpBuffer
)
{

   const_char_pointer  ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
      return (unsigned int) strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
      return (unsigned int) strlen(ptmpdir);
   }

   strncpy(lpBuffer, "/tmp", minimum(nBufferLength, 5));
   return 5;


}

