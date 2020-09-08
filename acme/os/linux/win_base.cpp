#include "framework.h"


DWORD
WINAPI
GetTempPathA(
DWORD nBufferLength,
LPSTR pBuffer

)
{

   const char * ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, MIN(nBufferLength, strlen(ptmpdir) + 1));

      return strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, MIN(nBufferLength, strlen(ptmpdir) + 1));

      return strlen(ptmpdir);
   }

   ansi_count_copy(pBuffer, "/tmp", MIN(nBufferLength, 5));

   return 5;


}

