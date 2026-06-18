#pragma once

//#define WH_SHSTDAPI(type) type
//
//
//namespace linux
//{
//
//
//   class CLASS_DECL_ACME shell
//   {
//   public:
//
//
//      shell();
//      virtual ~shell();
//
//
//      static shell theLinuxShell;
//
//      static bool Initialize();
//
//// xxx   static i32_bool WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath);
//// xxx   static HANDLE WINAPI _FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx   static i32_bool WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
///*   static i32_bool WINAPI _MoveFile(const wide_character * pExistingFileName, const wide_character * lpNewFileName);
//
//   static ::u32 WINAPI _GetFullPathName(const wide_character * pFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
//
//   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static i32_bool WINAPI _GetVolumeInformation(
//      const wide_character * pRootPathName,           // root directory
//
//      wide_character * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      wide_character * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//// xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
//      // xxx const wide_character * pszPath,
//      // xxx ::u32 dwFileAttributes,
//      // xxx SHFILEINFOW *psfi,
//      // xxx ::u32 cbFileInfo,
//      // xxx ::u32 uFlags);
//   static i32_bool __stdcall _GetStringTypeEx(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const wide_character * pSrcStr,
//
//      ::i32 cchSrc,
//      LPWORD pCharType);
//
//   static ::u32 WINAPI  _GetTempPath(
//      ::u32 nBufferLength,
//      wide_character * pBuffer);
//
//   static ::u32 WINAPI _GetTempFileName(
//      const wide_character * pszPath,
//
//      const wide_character * pszPrefix,
//
//      ::u32 uUnique,
//      wide_character * pTempFileName);
//
//   static HANDLE WINAPI _CreateFile(
//      const wide_character * pFileName,
//
//      ::u32 dwDesiredAccess,
//      ::u32 dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      ::u32 dwCreationDisposition,
//      ::u32 dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//   static ::u32 WINAPI _GetModuleFileName(
//       HMODULE hModule,
//       wide_character * pFilename,
//
//       ::u32 nSize
//       );
//// xxx    static i32_bool WINAPI _GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const wide_character * pClassName,
//
//// xxx        LPWNDCLASSW puserinteractionclass);
//
//// xxx    static ATOM WINAPI _RegisterClass(
//         // xxx const WNDCLASSW *puserinteractionclass);
//
//
//   static oswindow WINAPI _CreateWindowEx(
//      ::u32 dwExStyle,
//      const wide_character * pClassName,
//
//      const wide_character * pWindowName,
//
//      ::u32 dwStyle,
//      ::i32 x,
//      ::i32 y,
//      ::i32 nWidth,
//      ::i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//// xxx    i32_bool (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, wide_character * pszPath);
//// xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const wide_character * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    i32_bool (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   i32_bool (WINAPI * m_pfnMoveFile)(const wide_character * pExistingFileName, const wide_character * lpNewFileName);
//
//   WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   ::u32 (WINAPI * m_pfnGetFullPathName)(const wide_character * pFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
//
//   i32_bool (WINAPI * m_pfnGetVolumeInformation)(
//      const wide_character * pRootPathName,           // root directory
//
//      wide_character * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      wide_character * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//// xxx       const wide_character * pszPath,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//   i32_bool (__stdcall * m_pfnGetStringTypeEx)(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const wide_character * pSrcStr,
//
//      ::i32 cchSrc,
//      LPWORD pCharType);
//
//   ::u32 (WINAPI * m_pfnGetTempPath)(
//      ::u32 nBufferLength,
//      wide_character * pBuffer);
//
//   ::u32 (WINAPI * m_pfnGetTempFileName)(
//      const wide_character * pszPath,
//
//      const wide_character * pszPrefix,
//
//      ::u32 uUnique,
//      wide_character * pTempFileName);
//
//   HANDLE (WINAPI * m_pfnCreateFile)(
//      const wide_character * pFileName,
//
//      ::u32 dwDesiredAccess,
//      ::u32 dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      ::u32 dwCreationDisposition,
//      ::u32 dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//
//   ::u32 (WINAPI * m_pfnGetModuleFileName)(
//       HMODULE hModule,
//       wide_character * pFilename,
//
//       ::u32 nSize
//       );
//
//// xxx    i32_bool (WINAPI * m_pfnGetClassInfo)(
//       // xxx HINSTANCE hInstance ,
//// xxx        const wide_character * pClassName,
//
//// xxx        LPWNDCLASSW puserinteractionclass);
//
//
//   // xxx ATOM (WINAPI * m_pfnRegisterClass)(
//         // xxx const WNDCLASSW *puserinteractionclass);
//
//
//   oswindow (WINAPI * m_pfnCreateWindowEx)(
//      ::u32 dwExStyle,
//      const wide_character * pClassName,
//
//      const wide_character * pWindowName,
//
//      ::u32 dwStyle,
//      ::i32 x,
//      ::i32 y,
//      ::i32 nWidth,
//      ::i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//// xxx    static i32_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
//// xxx    static i32_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath);
//// xxx    static HANDLE FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    static i32_bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   static i32_bool MoveFile(const wide_character * pExistingFileName, const wide_character * lpNewFileName);
//
//   static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static ::u32 GetFullPathName(const wide_character * pFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
//
//   static i32_bool GetVolumeInformation(
//      const wide_character * pRootPathName,           // root directory
//
//      wide_character * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      wide_character * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
//// xxx       const wide_character * pszPath,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//
//   static i32_bool  GetStringTypeEx(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const_char_pointer pSrcStr,
//
//      ::i32 cchSrc,
//      LPWORD pCharType);
//
//
//   static ::u32 GetTempPathW(
//      ::u32 nBufferLength,
//      wide_character * pBuffer);
//
//
//   static ::u32 GetTempFileNameW(
//      const wide_character * pszPath,
//
//      const wide_character * pszPrefix,
//
//      ::u32 uUnique,
//      wide_character * pTempFileName);
//
//
//   static HANDLE CreateFile(
//      const wide_character * pFileName,
//
//      ::u32 dwDesiredAccess,
//      ::u32 dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      ::u32 dwCreationDisposition,
//      ::u32 dwFlagsAndAttributes,
//      HANDLE hTemplateFile);
//
//   static ::u32 WINAPI GetModuleFileName(
//       HMODULE hModule,
//        wide_character * pFilename,
//
//        ::u32 nSize
//       );
//
//// xxx    static i32_bool WINAPI GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const wide_character * pClassName,
//
//// xxx        LPWNDCLASSW puserinteractionclass);
//
//
//// xxx    static ATOM WINAPI RegisterClass(
//// xxx          const WNDCLASSW *puserinteractionclass);
//
//
//   static oswindow WINAPI CreateWindowEx(
//      ::u32 dwExStyle,
//      const wide_character * pClassName,
//
//      const wide_character * pWindowName,
//
//      ::u32 dwStyle,
//      ::i32 x,
//      ::i32 y,
//      ::i32 nWidth,
//      ::i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//
//// xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
//// xxx       const ::file::path & path,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFO *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//
//   static ::u32 GetTempPath(string & str);
//
//   static ::u32 GetTempFileName(
//      const ::file::path & path,
//
//      const ::scoped_string & scopedstrPrefix,
//
//      ::u32 uUnique,
//      string & str);
//
//   static i32_bool MoveFile(const_char_pointer pExistingFileName, const_char_pointer lpNewFileName);
//
//*/
//};
//
//
//
///*inline i32_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
//{
//   wide_character * pwszPath = (wide_character * ) malloc(sizeof(unichar) * MAX_PATH * 4);
//   if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
//   {
//      free(pwszPath);
//      return false;
//   }
//   unicode_to_utf8(str, pwszPath);
//   free(pwszPath);
//   return true;
//}
//*/
///*
//
//inline i32_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath)
//{
//   return (*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
//}
//*/
///*
//inline HANDLE shell::FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * pdata)
//
//{
//   return (*theLinuxShell.m_pfnFindFirstFile)(pcsz, pdata);
//
//}
//
//inline i32_bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)
//
//{
//   return (*theLinuxShell.m_pfnFindNextFile)(handle, pdata);
//
//}
//
//*/
//
///*
//inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
//{
//   return (*theLinuxShell.m_pfn_fullpath)(UserBuf, path, maxlen);
//}
//
//inline ::u32 shell::GetFullPathName(const wide_character * pFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart)
//
//{
//   return (*theLinuxShell.m_pfnGetFullPathName)(pFileName, nBufferLength, lpBuffer, lpFilePart);
//
//}
//
//
//inline i32_bool shell::MoveFile(const wide_character * pExistingFileName, const wide_character * lpNewFileName)
//
//{
//   return (*theLinuxShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName);
//
//}
//
//inline i32_bool shell::GetVolumeInformation(
//      const wide_character * pRootPathName,           // root directory
//
//      wide_character * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      wide_character * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize)         // length of file system name buffer
//{
//   return (*theLinuxShell.m_pfnGetVolumeInformation)(
//      pRootPathName,           // root directory
//
//      pVolumeNameBuffer,        // volume name buffer
//
//      nVolumeNameSize,            // length of name buffer
//      pVolumeSerialNumber,     // volume serial number
//
//      pMaximumComponentLength, // maximum file name length
//
//      pFileSystemFlags,        // file system options
//
//      pFileSystemNameBuffer,    // file system name buffer
//
//      nFileSystemNameSize);         // length of file system name buffer
//}
//
//*/
//
///*
//inline ::u32 shell::SHGetFileInfo(
//   const wide_character * pszPath,
//   ::u32 dwFileAttributes,
//   SHFILEINFOW *psfi,
//   ::u32 cbFileInfo,
//   ::u32 uFlags)
//{
//   return (*theLinuxShell.m_pfnSHGetFileInfo)(
//      pszPath,
//      dwFileAttributes,
//      psfi,
//      cbFileInfo,
//      uFlags);
//}
//*/
///*
//inline ::u32 shell::GetTempPathW(
//   ::u32 nBufferLength,
//   wide_character * pBuffer)
//
//{
//     return (*theLinuxShell.m_pfnGetTempPath)(
//      nBufferLength,
//      pBuffer);
//
//}
//
//inline ::u32 shell::GetTempFileNameW(
//   const wide_character * pszPath,
//
//   const wide_character * pszPrefix,
//
//   ::u32 uUnique,
//   wide_character * pTempFileName)
//
//{
//   return (*theLinuxShell.m_pfnGetTempFileName)(
//      pszPath,
//
//      pszPrefix,
//
//      uUnique,
//      pTempFileName);
//
//}
//
//inline HANDLE shell::CreateFile(
//   const wide_character * pFileName,
//
//   ::u32 dwDesiredAccess,
//   ::u32 dwShareMode,
//   LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//   ::u32 dwCreationDisposition,
//   ::u32 dwFlagsAndAttributes,
//   HANDLE hTemplateFile)
//{
//   return (*theLinuxShell.m_pfnCreateFile)(
//      pFileName,
//
//      dwDesiredAccess,
//      dwShareMode,
//      pSecurityAttributes,
//
//      dwCreationDisposition,
//      dwFlagsAndAttributes,
//      hTemplateFile);
//}
//
//inline ::u32 shell::GetModuleFileName(
//    HMODULE hModule,
//    wide_character * pFilename,
//
//    ::u32 nSize
//    )
//{
//   return (*theLinuxShell.m_pfnGetModuleFileName)(
//      hModule,
//      pFilename,
//
//      nSize);
//}
//
//*/
//
///*
//
//inline i32_bool shell::GetClassInfo(
//   HINSTANCE hInstance ,
//   const wide_character * pClassName,
//
//   LPWNDCLASSW puserinteractionclass)
//
//{
//   return (*theLinuxShell.m_pfnGetClassInfo)(
//      hInstance ,
//      pClassName,
//
//      puserinteractionclass);
//
//}
//
//inline ATOM shell::RegisterClass(
//   const WNDCLASSW *puserinteractionclass)
//
//{
//   return (*theLinuxShell.m_pfnRegisterClass)(
//      puserinteractionclass);
//
//}*/
///*
//inline oswindow shell::CreateWindowEx(
//   ::u32 dwExStyle,
//   const wide_character * pClassName,
//
//   const wide_character * pWindowName,
//
//   ::u32 dwStyle,
//   ::i32 x,
//   ::i32 y,
//   ::i32 nWidth,
//   ::i32 nHeight,
//   oswindow hWndParent,
//   HMENU hMenu,
//   HINSTANCE hInstance,
//   LPVOID pParam)
//
//{
//   return (*theLinuxShell.m_pfnCreateWindowEx)(
//      dwExStyle,
//      pClassName,
//
//      pWindowName,
//
//      dwStyle,
//      x,
//      y,
//      nWidth,
//      nHeight,
//      hWndParent,
//      hMenu,
//      hInstance,
//      pParam);
//
//
//}
//
//inline ::u32 shell::GetTempPath(string & str)
//{
//   wide_character * pwsz = (wide_character * ) malloc(sizeof(unichar) * MAX_PATH * 4);
//   ::u32 dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//   unicode_to_utf8(str, pwsz);
//   free(pwsz);
//   return dwResult;
//}
//
//inline ::u32 shell::GetTempFileName(const ::file::path & path, const ::scoped_string & scopedstrPrefix, ::u32 uUnique, string & str)
//
//{
//   wstring wstrPathName = utf8_to_unicode(scopedstrPath);
//
//   wstring wstrPrefixString = utf8_to_unicode(scopedstrPrefix);
//
//   wstring wstr;
//   wstr.get_buffer(MAX_PATH * 4);
//   ::u32 uResult = (*theLinuxShell.m_pfnGetTempFileName)(
//      wstrPathName,
//      wstrPrefixString,
//      uUnique,
//      wstr);
//   unicode_to_utf8(str, wstr);
//   return uiResult;
//}
//
//inline i32_bool shell::MoveFile(const_char_pointer pExistingFileName, const_char_pointer lpNewFileName)
//
//{
//   return MoveFile(utf8_to_unicode(pExistingFileName), utf8_to_unicode(lpNewFileName));
//
//}
//
//*/
//
//
//} // namespace linux
//
