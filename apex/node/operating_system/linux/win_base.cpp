#include "framework.h"


//::u32
//WINAPI
//GetTempPathA(
//::u32 nBufferLength,
//char * pBuffer
//
//)
//{
//
//   const char * ptmpdir = getenv("TMPDIR");
//
//   if(ptmpdir != nullptr && *ptmpdir != '\0')
//   {
//      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
//
//      return strlen(ptmpdir);
//   }
//
//   ptmpdir = P_tmpdir;
//
//   if(ptmpdir != nullptr && *ptmpdir != '\0')
//   {
//      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
//
//      return strlen(ptmpdir);
//   }
//
//   ansi_count_copy(pBuffer, "/tmp", minimum(nBufferLength, 5));
//
//   return 5;
//
//
//}
//
