#include "framework.h"

#include <string.h>


::u32 GetTempPathA(
::u32 nBufferLength,
char * pBuffer

)
{

   const char * ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (::u32) strlen(ptmpdir);
   }

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (::u32) strlen(ptmpdir);
   }

   ansi_count_copy(pBuffer, "/tmp", minimum(nBufferLength, 5));

   return 5;


}

