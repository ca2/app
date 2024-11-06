#include "framework.h"


#if 0


unsigned int
WINAPI
FormatMessage(
              unsigned int dwFlags,
              const void * lpSource,
              unsigned int dwMessageId,
              unsigned int dwLanguageId,
              char * lpBuffer,
              unsigned int nSize,
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


