#include "framework.h"


unsigned int
WINAPI
GetTempPathA(
unsigned int nBufferLength,
char * lpBuffer
)
{

   const char * ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
      return strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
      return strlen(ptmpdir);
   }

   strncpy(lpBuffer, "/tmp", minimum(nBufferLength, 5));
   return 5;


}

