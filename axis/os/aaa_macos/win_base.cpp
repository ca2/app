#include "framework.h"

#include <string.h>


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
      ansi_count_copy(pBuffer, ptmpdir, min(nBufferLength, strlen(ptmpdir) + 1));

      return (DWORD) strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, min(nBufferLength, strlen(ptmpdir) + 1));

      return (DWORD) strlen(ptmpdir);
   }

   ansi_count_copy(pBuffer, "/tmp", min(nBufferLength, 5));

   return 5;


}

