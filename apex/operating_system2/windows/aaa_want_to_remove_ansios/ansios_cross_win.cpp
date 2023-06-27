#include "framework.h"


#if 0


::u32
WINAPI
FormatMessage(
              ::u32 dwFlags,
              const void * lpSource,
              ::u32 dwMessageId,
              ::u32 dwLanguageId,
              char * lpBuffer,
              ::u32 nSize,
              va_list *Arguments
              )
{


    return 0;


}


VOID
WINAPI
information(
                   const char * lpOutputString
                   )
{


    fprintf(stderr, "%s", lpOutputString);
    fflush(stderr);
    //printf("%s", lpOutputString);


}




VOID
WINAPI
information(
                   const ::wide_character * lpOutputString
                   )
{


    information(string(lpOutputString));


}


#endif


