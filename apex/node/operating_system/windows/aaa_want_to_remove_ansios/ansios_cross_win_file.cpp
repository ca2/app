//#include "framework.h"
//
//
//HANDLE
//WINAPI
//create_file(
//            char const * lpFileName,
//            ::u32 dwDesiredAccess,
//            ::u32 dwShareMode,
//            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//            ::u32 dwCreationDisposition,
//            ::u32 dwFlagsAndAttributes,
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
//::u32
//WINAPI
//SetFilePointer(
//               HANDLE hFile,
//               ::i32 lDistanceToMove,
//               PLONG lpDistanceToMoveHigh,
//               ::u32 dwMoveMethod
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
//          const void * lpBuffer,
//          ::u32 nNumberOfBytesToWrite,
//          LPDWORD lpNumberOfBytesWritten,
//          LPOVERLAPPED lpOverlapped
//          )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
//    size_t sizeWritten = fwrite(lpBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);
//    if(lpNumberOfBytesWritten != nullptr)
//        *lpNumberOfBytesWritten = (::u32) sizeWritten;
//    return true;
//}
//
//int_bool
//WINAPI
//ReadFile(
//         HANDLE hFile,
//         LPVOID lpBuffer,
//         ::u32 nNumberOfBytesToRead,
//         LPDWORD lpNumberOfBytesRead,
//         LPOVERLAPPED lpOverlapped
//         )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
//    size_t sizeRead = fwrite(lpBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);
//    if(lpNumberOfBytesRead != nullptr)
//        *lpNumberOfBytesRead = (::u32)sizeRead;
//    return true;
//}
//
//int_bool
//WINAPI
//FlushFileBuffers(
//                 HANDLE hFile
//                 )
//{    if(hFile == INVALID_HANDLE_VALUE)
//    return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
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
//        return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
//    return fclose(hFile->m_file.m_pfile) != false;
//}
//
//int_bool
//WINAPI
//CloseHandle(
//            HANDLE hObject
//            )
//{
//   if(hObject == INVALID_HANDLE_VALUE)
//      return false;
//   int_bool bOk = false;
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
//::u32
//WINAPI
//GetTempPathW(
//    ::u32 nBufferLength,
//    LPWSTR lpBuffer
//    )
//{
//
//   wstring wstr = "/::payload/apex/time/";
//
//   ::count iLen = minimum(nBufferLength, wstr.get_length());
//
//   unincpy(lpBuffer, wstr, iLen);
//
//   if(nBufferLength > 0)
//   {
//      lpBuffer[iLen] = '\0';
//   }
//
//   return (::u32) iLen;
//
//}
