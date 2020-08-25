#include "framework.h"


#if 0


DWORD
WINAPI
FormatMessage(
              DWORD dwFlags,
              LPCVOID lpSource,
              DWORD dwMessageId,
              DWORD dwLanguageId,
              LPSTR lpBuffer,
              DWORD nSize,
              va_list *Arguments
              )
{


    return 0;


}


VOID
WINAPI
output_debug_string(
                   LPCSTR lpOutputString
                   )
{


    fprintf(stderr, "%s", lpOutputString);
    fflush(stderr);
    //printf("%s", lpOutputString);


}




VOID
WINAPI
output_debug_string(
                   LPCWSTR lpOutputString
                   )
{


    output_debug_string(string(lpOutputString));


}


#endif


