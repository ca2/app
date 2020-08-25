#include "framework.h"

string get_error_message(DWORD dwError)
{
   LPCSTR lpBuffer = "";
//   FormatMessage(
//                 FORMAT_MESSAGE_ALLOCATE_BUFFER |
//                 FORMAT_MESSAGE_FROM_SYSTEM,
//                 nullptr,
////                 dwError,
//                 0,
//                 (LPSTR) &lpBuffer,
//                 1,
//                 nullptr);
   string str = lpBuffer;
   //   string str = ::str::international::unicode_to_utf8(lpBuffer);
   // xxx   LocalFree(lpBuffer);
   return str;
}
