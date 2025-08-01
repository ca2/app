#include "framework.h"

#include <string.h>
#include <stdio.h>

unsigned int
//WINAPI
GetTempPathA(
unsigned int nBufferLength,
char * pBuffer

)
{

   const_char_pointer  ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (unsigned int) strlen(ptmpdir);
   }
   

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (unsigned int) strlen(ptmpdir);
   }

   ansi_count_copy(pBuffer, "/tmp", minimum(nBufferLength, 5));

   return 5;


}

