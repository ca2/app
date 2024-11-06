#include "framework.h"


/*HANDLE
WINAPI
create_file(
            const char * lpFileName,
            unsigned int dwDesiredAccess,
            unsigned int dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            unsigned int dwCreationDisposition,
            unsigned int dwFlagsAndAttributes,
            HANDLE hTemplateFile
            )
{

    FILE * pfile = fopen(lpFileName, "rw");

    if(pfile == nullptr)
        return INVALID_HANDLE_VALUE;

    HANDLE handle = aaa_primitive_new win_handle;

    handle->m_etype = win_handle::type_file;
    handle->m_file.m_pfile = pfile;


    return handle;


}

unsigned int
WINAPI
SetFilePointer(
               HANDLE hFile,
               int lDistanceToMove,
               PLONG lpDistanceToMoveHigh,
               unsigned int dwMoveMethod
               )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return -1;
    if(hFile->m_etype != win_handle::type_file)
        return -1;
    return fseek(hFile->m_file.m_pfile, lDistanceToMove, dwMoveMethod);
}


int_bool
WINAPI
WriteFile(
          HANDLE hFile,
          const void * lpBuffer,
          unsigned int nNumberOfBytesToWrite,
          LPDWORD lpNumberOfBytesWritten,
          LPOVERLAPPED lpOverlapped
          )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return false;
    if(hFile->m_etype != win_handle::type_file)
        return false;
    size_t sizeWritten = fwrite(lpBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);
    if(lpNumberOfBytesWritten != nullptr)
        *lpNumberOfBytesWritten = (unsigned int) sizeWritten;
    return true;
}

int_bool
WINAPI
ReadFile(
         HANDLE hFile,
         LPVOID lpBuffer,
         unsigned int nNumberOfBytesToRead,
         LPDWORD lpNumberOfBytesRead,
         LPOVERLAPPED lpOverlapped
         )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return false;
    if(hFile->m_etype != win_handle::type_file)
        return false;
    size_t sizeRead = fwrite(lpBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);
    if(lpNumberOfBytesRead != nullptr)
        *lpNumberOfBytesRead = (unsigned int)sizeRead;
    return true;
}

int_bool
WINAPI
FlushFileBuffers(
                 HANDLE hFile
                 )
{    if(hFile == INVALID_HANDLE_VALUE)
    return false;
    if(hFile->m_etype != win_handle::type_file)
        return false;
    return fflush(hFile->m_file.m_pfile) == 0;
}


int_bool
WINAPI
__win_CloseFile(
            HANDLE hFile
            )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return false;
    if(hFile->m_etype != win_handle::type_file)
        return false;
    return fclose(hFile->m_file.m_pfile) != false;
}

int_bool
WINAPI
CloseHandle(
            HANDLE hObject
            )
{
   if(hObject == INVALID_HANDLE_VALUE)
      return false;
   int_bool bOk = false;
   switch(hObject->m_etype)
   {
      case win_handle::type_file:
         bOk = __win_CloseFile(hObject);
      case win_handle::type_thread:
         bOk = __win_CloseThread(hObject);
      default:
         break;
   };
   delete hObject;
   return bOk;
}*/



