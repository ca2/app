#include "framework.h"

#include <sys/stat.h>
//
//
//HANDLE
//WINAPI
//create_file(
//            char const * pFileName,

//            ::u32 dwDesiredAccess,
//            ::u32 dwShareMode,
//            LPSECURITY_ATTRIBUTES pSecurityAttributes,

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
//::u32
//WINAPI
//SetFilePointer(
//               HANDLE hFile,
//               ::i32 lDistanceToMove,
//               PLONG pDistanceToMoveHigh,

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
//          const void * pBuffer,

//          ::u32 nNumberOfBytesToWrite,
//          LPDWORD pNumberOfBytesWritten,

//          LPOVERLAPPED pOverlapped

//          )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
//    size_t sizeWritten = fwrite(pBuffer, nNumberOfBytesToWrite, 1, hFile->m_file.m_pfile);

//    if(pNumberOfBytesWritten != nullptr)

//        *pNumberOfBytesWritten = (u32) sizeWritten;

//    return true;
//}
//
//int_bool
//WINAPI
//ReadFile(
//         HANDLE hFile,
//         LPVOID pBuffer,

//         ::u32 nNumberOfBytesToRead,
//         LPDWORD pNumberOfBytesRead,

//         LPOVERLAPPED pOverlapped

//         )
//{
//    if(hFile == INVALID_HANDLE_VALUE)
//        return false;
//    if(hFile->m_etype != win_handle::type_file)
//        return false;
//    size_t sizeRead = fwrite(pBuffer, nNumberOfBytesToRead, 1, hFile->m_file.m_pfile);

//    if(pNumberOfBytesRead != nullptr)

//        *pNumberOfBytesRead = (u32)sizeRead;

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
//    LPWSTR pBuffer

//    )
//{
//
//   wstring wstr = "/::payload/aura/time/";
//
//   ::count iLen = minimum(nBufferLength, wstr.get_length());
//
//   unincpy(pBuffer, wstr, iLen);

//
//   if(nBufferLength > 0)
//   {
//      pBuffer[iLen] = '\0';

//   }
//
//   return (::u32) iLen;
//
//}


#ifndef WINDOWS


bool context::_os_resolve_alias(::file::path & path, const ::string & psz, bool bNoUI, bool bNoMount)
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


// CLASS_DECL_AURA bool context::os_resolve_alias(::file::path & path, const ::string & psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



// CLASS_DECL_AURA bool _os_may_have_alias(const ::string & psz)
// {

//    return true;

// }


#ifndef WINDOWS

CLASS_DECL_AURA bool context::os_is_alias(const ::string & path)
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





