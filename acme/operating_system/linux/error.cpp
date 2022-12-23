#include "framework.h"
// #include "acme/primitive/string/string.h"


string get_error_message(::u32 dwError)
{
   char * pBuffer;

   string str;
//   FormatMessage(
//      FORMAT_MESSAGE_ALLOcaTE_BUFFER |
//      FORMAT_MESSAGE_FROM_SYSTEM,
//      nullptr,
//      dwError,
//      0,
//      (char *) &pBuffer,

//      1,
//      nullptr);
//      string str = pBuffer;

//   string str = unicode_to_utf8(pBuffer);

// xxx   LocalFree(pBuffer);

   return str;
}
