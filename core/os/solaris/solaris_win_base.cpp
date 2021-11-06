#include "framework.h"


::u32
WINAPI
GetTempPathA(
    ::u32 nBufferLength,
    char * lpBuffer
    )
{

    const char * ptmpdir = getenv("TMPDIR");

    if(ptmpdir != nullptr && *ptmpdir != '\0')
    {
        strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
        return strlen(ptmpdir);
    }

    ptmpdir = P_tmpdir;

    if(ptmpdir != nullptr && *ptmpdir != '\0')
    {
        strncpy(lpBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));
        return strlen(ptmpdir);
    }

    strncpy(lpBuffer, "/tmp", minimum(nBufferLength, 5));
    return 5;


}

