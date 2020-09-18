#include "framework.h"


DWORD
WINAPI
GetTempPathA(
DWORD nBufferLength,
LPSTR lpBuffer
)
{

   const char * ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, min(nBufferLength, strlen(ptmpdir) + 1));
      return strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      strncpy(lpBuffer, ptmpdir, min(nBufferLength, strlen(ptmpdir) + 1));
      return strlen(ptmpdir);
   }

   strncpy(lpBuffer, "/tmp", min(nBufferLength, 5));
   return 5;


}

