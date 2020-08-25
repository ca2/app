#include "framework.h"


#if 0


DWORD
WINAPI
format_message(
              DWORD dwFlags,
              LPCVOID pSource,

              DWORD dwMessageId,
              DWORD dwLanguageId,
              LPSTR pBuffer,

              DWORD nSize,
              va_list *Arguments
              )
{


    return 0;


}


VOID
WINAPI
output_debug_string(
                   LPCSTR pOutputString

                   )
{


    fprintf(stderr, "%s", pOutputString);

    fflush(stderr);
    //printf("%s", pOutputString);



}




VOID
WINAPI
output_debug_string(
                   LPCWSTR pOutputString

                   )
{


    output_debug_string(string(pOutputString));



}


#endif


