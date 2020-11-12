#include "framework.h"

string get_error_message(::u32 dwError)
{
   //char * lpBuffer;
   //FormatMessage(
   //   FORMAT_MESSAGE_ALLOCATE_BUFFER |
   //   FORMAT_MESSAGE_FROM_SYSTEM,
   //   nullptr,
   //   dwError,
   //   0,
   //   (char *) &lpBuffer,
   //   1,
   //   nullptr);
//   string str = lpBuffer;
   string str = "Error: " + __str(dwError);
//   string str = ::str::international::unicode_to_utf8(lpBuffer);
// xxx   LocalFree(lpBuffer);
   return str;
}
