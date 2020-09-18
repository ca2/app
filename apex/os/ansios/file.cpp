#include "framework.h"

#include <sys/stat.h>
//
//
//HANDLE
//WINAPI
//create_file(
//            char const * pFileName,

//            DWORD dwDesiredAccess,
//            DWORD dwShareMode,
//            LPSECURITY_ATTRIBUTES pSecurityAttributes,

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
//         pfile = fopen(pFileName, "w+");

//      }
//      else
//      {
//         pfile = fopen(pFileName, "w");

//      }
//
//   }
//   else
//   {
//
//      pfile = fopen(pFileName, "r");

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
//               PLONG pDistanceToMoveHigh,

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
//          LPCVOID pBuffer,

//          DWORD nNumberOfBytesToWrite,
//          LPDWORD pNumberOfBytesWritten,

//          LPOVERLAPPED pOverlapped

//          )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    size_t sizeWritten = fwrite(pBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);

//    if(pNumberOfBytesWritten != nullptr)

//        *pNumberOfBytesWritten = (u32) sizeWritten;

//    return TRUE;
//}
//
//int_bool
//WINAPI
//ReadFile(
//         HANDLE hFile,
//         LPVOID pBuffer,

//         DWORD nNumberOfBytesToRead,
//         LPDWORD pNumberOfBytesRead,

//         LPOVERLAPPED pOverlapped

//         )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return FALSE;
//    if(hFile->m_etype != win_handle::type_file)
//        return FALSE;
//    size_t sizeRead = fwrite(pBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);

//    if(pNumberOfBytesRead != nullptr)

//        *pNumberOfBytesRead = (u32)sizeRead;

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
//    LPWSTR pBuffer

//    )
//{
//
//   wstring wstr = "/var/apex/time/";
//
//   ::count iLen = min(nBufferLength, wstr.get_length());
//
//   unincpy(pBuffer, wstr, iLen);

//
//   if(nBufferLength > 0)
//   {
//      pBuffer[iLen] = '\0';

//   }
//
//   return (DWORD) iLen;
//
//}


#ifndef WINDOWS


bool context::_os_resolve_alias(::file::path & path, const char * psz, bool bNoUI, bool bNoMount)
{

   if (::is_null(psz))
   {

      return false;

   }




   char * pszRealPath = ::realpath(psz, NULL);

   if (pszRealPath == NULL)
   {

      return false;

   }

   if (strcmp(psz, pszRealPath) == 0)
   {

      ::free(pszRealPath);

      return false;

   }

   try
   {

      path = pszRealPath;

   }
   catch (...)
   {

   }

   ::free(pszRealPath);

   return true;

}

#endif


bool context::os_resolve_alias(::file::path & path, const char * psz, bool bNoUI, bool bNoMount)
{

   return _os_resolve_alias(path, psz, bNoUI, bNoMount);

}



// CLASS_DECL_APEX bool _os_may_have_alias(const char * psz)
// {

//    return true;

// }


#ifndef WINDOWS

CLASS_DECL_APEX bool context::os_is_alias(const char * path)
{

   if (is_null(path))
   {

      return false;

   }

   struct stat st;

   if (lstat(path, &st) == -1)
   {

      return false;

   }

   if (S_ISLNK(st.st_mode))
   {

      return true;

   }

   return false;

}

#endif





