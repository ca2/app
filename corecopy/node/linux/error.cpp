#include "framework.h"

string get_error_message(DWORD dwError)
{
   LPSTR pBuffer;

   string str;
//   FormatMessage(
//      FORMAT_MESSAGE_ALLOcaTE_BUFFER |
//      FORMAT_MESSAGE_FROM_SYSTEM,
//      nullptr,
//      dwError,
//      0,
//      (LPSTR) &pBuffer,

//      1,
//      nullptr);
//      string str = pBuffer;

//   string str = ::str::international::unicode_to_utf8(pBuffer);

// xxx   LocalFree(pBuffer);

   return str;
}
