//#include "framework.h"
//
//
//HANDLE
//WINAPI
//create_file(
//            char const * lpFileName,
//            DWORD dwDesiredAccess,
//            DWORD dwShareMode,
//            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//            DWORD dwCreationDisposition,
//            DWORD dwFlagsAndAttributes,
//            HANDLE hTemplateFile
//            )
//{
//
//   FILE * pfile;
//
//   if(dwDesiredAccess & GENERIC_WRITE)
//   {
//      if(dwDesiredAccess & GENERIC_READ)
//      {
//         pfile = fopen(lpFileName, "w+");
//      }
//      else
//      {
//         pfile = fopen(lpFileName, "w");
//      }
//
//   }
//   else
//   {
//
//      pfile = fopen(lpFileName, "r");
//   }
//
//
//
//    if(pfile == nullptr)
//        return INVALID_HANDLE_VALUE;
//
//    HANDLE handle = new win_handle;
//
//    handle->m_etype = win_handle::type_file;
//    handle->m_file.m_pfile = pfile;
//
//
//    return handle;
//
//
//}
//
//DWORD
//WINAPI
//SetFilePointer(
//               HANDLE hFile,
//               LONG lDistanceToMove,
//               PLONG lpDistanceToMoveHigh,
//               DWORD dwMoveMethod
//               )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return -1;
//    if(hFile->m_etype != win_handle::type_file)
//        return -1;
//    return fseek(hFile->m_file.m_pfile, lDistanceToMove, dwMoveMethod);
//}
//
//
//int_bool
//WINAPI
//WriteFile(
//          HANDLE hFile,
//          LPCVOID lpBuffer,
//          DWORD nNumberOfBytesToWrite,
//          LPDWORD lpNumberOfBytesWritten,
//          LPOVERLAPPED lpOverlapped
//          )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    size_t sizeWritten = fwrite(lpBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);
//    if(lpNumberOfBytesWritten != nullptr)
//        *lpNumberOfBytesWritten = (uint32_t) sizeWritten;
//    return TRUE;
//}
//
//int_bool
//WINAPI
//ReadFile(
//         HANDLE hFile,
//         LPVOID lpBuffer,
//         DWORD nNumberOfBytesToRead,
//         LPDWORD lpNumberOfBytesRead,
//         LPOVERLAPPED lpOverlapped
//         )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    size_t sizeRead = fwrite(lpBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);
//    if(lpNumberOfBytesRead != nullptr)
//        *lpNumberOfBytesRead = (uint32_t)sizeRead;
//    return TRUE;
//}
//
//int_bool
//WINAPI
//FlushFileBuffers(
//                 HANDLE hFile
//                 )
//{    if(hFile == INVALID_HANDLE_VALUE)
//    return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    return fflush(hFile->m_file.m_pfile) == 0;
//}
//
//
//int_bool
//WINAPI
//__win_CloseFile(
//            HANDLE hFile
//            )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    return fclose(hFile->m_file.m_pfile) != FALSE;
//}
//
//int_bool
//WINAPI
//CloseHandle(
//            HANDLE hObject
//            )
//{
//   if(hObject == INVALID_HANDLE_VALUE)
//      return FALSE;
//   int_bool bOk = FALSE;
//   switch(hObject->m_etype)
//   {
//      case win_handle::type_file:
//         bOk = __win_CloseFile(hObject);
///*      case win_handle::type_thread:
//         bOk = __win_CloseThread(hObject);*/
//      default:
//         break;
//   };
//   delete hObject;
//   return bOk;
//}
//
//
//
//DWORD
//WINAPI
//GetTempPathW(
//    DWORD nBufferLength,
//    LPWSTR lpBuffer
//    )
//{
//
//   wstring wstr = "/var/acme/time/";
//
//   ::count iLen = min(nBufferLength, wstr.get_length());
//
//   unincpy(lpBuffer, wstr, iLen);
//
//   if(nBufferLength > 0)
//   {
//      lpBuffer[iLen] = '\0';
//   }
//
//   return (DWORD) iLen;
//
//}
