#include "framework.h"

#include <sys/stat.h>

#ifdef __APPLE__


#include <unistd.h>


#endif

#if defined(FREEBSD) || defined(OPENBSD)
#include <unistd.h>
#endif

//
//
//HANDLE
//WINAPI
//create_file(
//            char const * pFileName,

//            unsigned int dwDesiredAccess,
//            unsigned int dwShareMode,
//            LPSECURITY_ATTRIBUTES pSecurityAttributes,

//            unsigned int dwCreationDisposition,
//            unsigned int dwFlagsAndAttributes,
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
//    HANDLE handle = __allocate win_handle();
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
//unsigned int
//WINAPI
//SetFilePointer(
//               HANDLE hFile,
//               int lDistanceToMove,
//               PLONG pDistanceToMoveHigh,

//               unsigned int dwMoveMethod
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

//          unsigned int nNumberOfBytesToWrite,
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

//        *pNumberOfBytesWritten = (unsigned int) sizeWritten;

//    return true;
//}
//
//int_bool
//WINAPI
//ReadFile(
//         HANDLE hFile,
//         LPVOID pBuffer,

//         unsigned int nNumberOfBytesToRead,
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

//        *pNumberOfBytesRead = (unsigned int)sizeRead;

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
//unsigned int
//WINAPI
//GetTempPathW(
//    unsigned int nBufferLength,
//    LPWSTR pBuffer

//    )
//{
//
//   wstring wstr = "/::payload/acme/time/";
//
//   ::collection::count iLen = minimum(nBufferLength, wstr.get_length());
//
//   unincpy(pBuffer, wstr, iLen);

//
//   if(nBufferLength > 0)
//   {
//      pBuffer[iLen] = '\0';

//   }
//
//   return (unsigned int) iLen;
//
//}


//#ifndef WINDOWS
//
//
//bool context::_os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, bool bNoUI, bool bNoMount)
//{
//
//   if (::is_null(scopedstr))
//   {
//
//      return false;
//
//   }
//
//
//
//
//   char * pszRealPath = ::realpath(scopedstr, NULL);
//
//   if (scopedstrRealPath == NULL)
//   {
//
//      return false;
//
//   }
//
//   if (strcmp(scopedstr, pszRealPath) == 0)
//   {
//
//      ::free(scopedstrRealPath);
//
//      return false;
//
//   }
//
//   try
//   {
//
//      path = pszRealPath;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   ::free(scopedstrRealPath);
//
//   return true;
//
//}
//
//#endif


// CLASS_DECL_ACME bool context::os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



// CLASS_DECL_ACME bool _os_may_have_alias(const ::scoped_string & scopedstr)
// {

//    return true;

// }


//#ifndef WINDOWS
//
//CLASS_DECL_ACME bool context::os_is_alias(const ::file::path & path)
//{
//
//   if (is_null(path))
//   {
//
//      return false;
//
//   }
//
//   struct stat st;
//
//   if (lstat(path, &st) == -1)
//   {
//
//      return false;
//
//   }
//
//   if (S_ISLNK(st.st_mode))
//   {
//
//      return true;
//
//   }
//
//   return false;
//
//}
//
//#endif
//
//



