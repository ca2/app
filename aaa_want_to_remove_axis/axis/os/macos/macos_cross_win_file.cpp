#include "framework.h"


/*HANDLE
WINAPI
create_file(
            LPCSTR lpFileName,
            DWORD dwDesiredAccess,
            DWORD dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDisposition,
            DWORD dwFlagsAndAttributes,
            HANDLE hTemplateFile
            )
{
    
    FILE * pfile = fopen(lpFileName, "rw");
    
    if(pfile == nullptr)
        return INVALID_HANDLE_VALUE;
    
    HANDLE handle = new win_handle;
    
    handle->m_etype = win_handle::type_file;
    handle->m_file.m_pfile = pfile;

    
    return handle;
    
    
}

DWORD
WINAPI
SetFilePointer(
               HANDLE hFile,
               LONG lDistanceToMove,
               PLONG lpDistanceToMoveHigh,
               DWORD dwMoveMethod
               )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return -1;
    if(hFile->m_etype != win_handle::type_file)
        return -1;
    return fseek(hFile->m_file.m_pfile, lDistanceToMove, dwMoveMethod);
}


WINBOOL
WINAPI
WriteFile(
          HANDLE hFile,
          LPCVOID lpBuffer,
          DWORD nNumberOfBytesToWrite,
          LPDWORD lpNumberOfBytesWritten,
          LPOVERLAPPED lpOverlapped
          )
{    
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    size_t sizeWritten = fwrite(lpBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);
    if(lpNumberOfBytesWritten != nullptr)
        *lpNumberOfBytesWritten = (u32) sizeWritten;
    return TRUE;
}

WINBOOL
WINAPI
ReadFile(
         HANDLE hFile,
         LPVOID lpBuffer,
         DWORD nNumberOfBytesToRead,
         LPDWORD lpNumberOfBytesRead,
         LPOVERLAPPED lpOverlapped
         )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    size_t sizeRead = fwrite(lpBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);
    if(lpNumberOfBytesRead != nullptr)
        *lpNumberOfBytesRead = (u32)sizeRead;
    return TRUE;
}

WINBOOL
WINAPI
FlushFileBuffers(
                 HANDLE hFile
                 )
{    if(hFile == INVALID_HANDLE_VALUE)
    return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    return fflush(hFile->m_file.m_pfile) == 0;
}


WINBOOL
WINAPI
__win_CloseFile(
            HANDLE hFile
            )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    return fclose(hFile->m_file.m_pfile) != FALSE;
}

WINBOOL
WINAPI
CloseHandle(
            HANDLE hObject
            )
{
   if(hObject == INVALID_HANDLE_VALUE)
      return FALSE;
   WINBOOL bOk = FALSE;
   switch(hObject->m_etype)
   {
      case win_handle::type_file:
         bOk = __win_CloseFile(hObject);
/*      case win_handle::type_thread:
         bOk = __win_CloseThread(hObject);*/
 /*     default:
         break;
   };
   delete hObject;
   return bOk;
}*/



