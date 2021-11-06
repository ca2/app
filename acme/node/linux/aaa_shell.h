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
//// xxx   static int_bool WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx   static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx   static int_bool WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
///*   static int_bool WINAPI _MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   static ::u32 WINAPI _GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static int_bool WINAPI _GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//// xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
//      // xxx const unichar * pszPath,
//      // xxx ::u32 dwFileAttributes,
//      // xxx SHFILEINFOW *psfi,
//      // xxx ::u32 cbFileInfo,
//      // xxx ::u32 uFlags);
//   static int_bool __stdcall _GetStringTypeEx(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const unichar * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//   static ::u32 WINAPI  _GetTempPath(
//      ::u32 nBufferLength,
//      unichar * pBuffer);
//
//   static ::u32 WINAPI _GetTempFileName(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      ::u32 uUnique,
//      unichar * pTempFileName);
//
//   static HANDLE WINAPI _CreateFile(
//      const unichar * pFileName,
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
//       unichar * pFilename,
//
//       ::u32 nSize
//       );
//// xxx    static int_bool WINAPI _GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
//
//// xxx        LPWNDCLASSW puserinteractionclass);
//
//// xxx    static ATOM WINAPI _RegisterClass(
//         // xxx const WNDCLASSW *puserinteractionclass);
//
//
//   static oswindow WINAPI _CreateWindowEx(
//      ::u32 dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      ::u32 dwStyle,
//      i32 x,
//      i32 y,
//      i32 nWidth,
//      i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//
//
//
//
//// xxx    int_bool (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    int_bool (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   int_bool (WINAPI * m_pfnMoveFile)(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   ::u32 (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   int_bool (WINAPI * m_pfnGetVolumeInformation)(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//// xxx       const unichar * pszPath,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//   int_bool (__stdcall * m_pfnGetStringTypeEx)(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const unichar * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//   ::u32 (WINAPI * m_pfnGetTempPath)(
//      ::u32 nBufferLength,
//      unichar * pBuffer);
//
//   ::u32 (WINAPI * m_pfnGetTempFileName)(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      ::u32 uUnique,
//      unichar * pTempFileName);
//
//   HANDLE (WINAPI * m_pfnCreateFile)(
//      const unichar * pFileName,
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
//       unichar * pFilename,
//
//       ::u32 nSize
//       );
//
//// xxx    int_bool (WINAPI * m_pfnGetClassInfo)(
//       // xxx HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
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
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      ::u32 dwStyle,
//      i32 x,
//      i32 y,
//      i32 nWidth,
//      i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//
//
//
//
//
//
//
//// xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
//// xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx    static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    static int_bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   static int_bool MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static ::u32 GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static int_bool GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
//// xxx       const unichar * pszPath,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//
//   static int_bool  GetStringTypeEx(
//      LCID Locale,
//      ::u32 dwInfoType,
//      const char * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//
//   static ::u32 GetTempPathW(
//      ::u32 nBufferLength,
//      unichar * pBuffer);
//
//
//   static ::u32 GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      ::u32 uUnique,
//      unichar * pTempFileName);
//
//
//   static HANDLE CreateFile(
//      const unichar * pFileName,
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
//        unichar * pFilename,
//
//        ::u32 nSize
//       );
//
//// xxx    static int_bool WINAPI GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
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
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      ::u32 dwStyle,
//      i32 x,
//      i32 y,
//      i32 nWidth,
//      i32 nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//
//// xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
//// xxx       const char * pszPath,
//// xxx       ::u32 dwFileAttributes,
//// xxx       SHFILEINFO *psfi,
//// xxx       ::u32 cbFileInfo,
//// xxx       ::u32 uFlags);
//
//   static ::u32 GetTempPath(string & str);
//
//   static ::u32 GetTempFileName(
//      const char * pszPath,
//
//      const char * pszPrefix,
//
//      ::u32 uUnique,
//      string & str);
//
//   static int_bool MoveFile(const char * pExistingFileName, const char * lpNewFileName);
//
//*/
//};
//
//
//
///*inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
//{
//   unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//   if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
//   {
//      free(pwszPath);
//      return false;
//   }
//   ::str::international::unicode_to_utf8(str, pwszPath);
//   free(pwszPath);
//   return true;
//}
//*/
///*
//
//inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
//{
//   return (*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
//}
//*/
///*
//inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata)
//
//{
//   return (*theLinuxShell.m_pfnFindFirstFile)(pcsz, pdata);
//
//}
//
//inline int_bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)
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
//inline ::u32 shell::GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
//
//{
//   return (*theLinuxShell.m_pfnGetFullPathName)(pFileName, nBufferLength, lpBuffer, lpFilePart);
//
//}
//
//
//inline int_bool shell::MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)
//
//{
//   return (*theLinuxShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName);
//
//}
//
//inline int_bool shell::GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      ::u32 nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
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
//   const unichar * pszPath,
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
//   unichar * pBuffer)
//
//{
//     return (*theLinuxShell.m_pfnGetTempPath)(
//      nBufferLength,
//      pBuffer);
//
//}
//
//inline ::u32 shell::GetTempFileNameW(
//   const unichar * pszPath,
//
//   const unichar * pszPrefix,
//
//   ::u32 uUnique,
//   unichar * pTempFileName)
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
//   const unichar * pFileName,
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
//    unichar * pFilename,
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
//inline int_bool shell::GetClassInfo(
//   HINSTANCE hInstance ,
//   const unichar * pClassName,
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
//   const unichar * pClassName,
//
//   const unichar * pWindowName,
//
//   ::u32 dwStyle,
//   i32 x,
//   i32 y,
//   i32 nWidth,
//   i32 nHeight,
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
//   unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//   ::u32 dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//   ::str::international::unicode_to_utf8(str, pwsz);
//   free(pwsz);
//   return dwResult;
//}
//
//inline ::u32 shell::GetTempFileName(const char * pszPath, const char * pszPrefix, ::u32 uUnique, string & str)
//
//{
//   wstring wstrPathName = ::str::international::utf8_to_unicode(pszPath);
//
//   wstring wstrPrefixString = ::str::international::utf8_to_unicode(pszPrefix);
//
//   wstring wstr;
//   wstr.get_buffer(MAX_PATH * 4);
//   ::u32 uResult = (*theLinuxShell.m_pfnGetTempFileName)(
//      wstrPathName,
//      wstrPrefixString,
//      uUnique,
//      wstr);
//   ::str::international::unicode_to_utf8(str, wstr);
//   return uiResult;
//}
//
//inline int_bool shell::MoveFile(const char * pExistingFileName, const char * lpNewFileName)
//
//{
//   return MoveFile(::str::international::utf8_to_unicode(pExistingFileName), ::str::international::utf8_to_unicode(lpNewFileName));
//
//}
//
//*/
//
//
//} // namespace linux
//
