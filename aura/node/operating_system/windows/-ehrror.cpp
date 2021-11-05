#include "framework.h"

string get_error_message(::u32 dwError)
{
   LPWSTR pBuffer;

   FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      nullptr,
      dwError,
      0,
      (LPWSTR) &pBuffer,

      1,
      nullptr);
   string str = ::str::international::unicode_to_utf8(pBuffer);

   LocalFree(pBuffer);

   return str;
}
