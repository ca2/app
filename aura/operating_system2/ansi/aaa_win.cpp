#include "framework.h"


#if 0


::u32
WINAPI
format_message(
              ::u32 dwFlags,
              const void * pSource,

              ::u32 dwMessageId,
              ::u32 dwLanguageId,
              char * pBuffer,

              ::u32 nSize,
              va_list *Arguments
              )
{


    return 0;


}


VOID
WINAPI
information(
                   const char * pOutputString

                   )
{


    fprintf(stderr, "%s", pOutputString);

    fflush(stderr);
    //printf("%s", pOutputString);



}




VOID
WINAPI
information(
                   const ::wide_character * pOutputString

                   )
{


    information(string(pOutputString));



}


#endif


