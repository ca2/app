#pragma once

//#define WH_SHSTDAPI(type) type
//
//
//namespace linux
//{
//
//
//   class CLASS_DECL_CORE shell
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
//// xxx   static WINBOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx   static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx   static WINBOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
///*   static WINBOOL WINAPI _MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   static DWORD WINAPI _GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static WINBOOL WINAPI _GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      DWORD nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      DWORD nFileSystemNameSize);         // length of file system name buffer
//// xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
//      // xxx const unichar * pszPath,
//      // xxx DWORD dwFileAttributes,
//      // xxx SHFILEINFOW *psfi,
//      // xxx UINT cbFileInfo,
//      // xxx UINT uFlags);
//   static WINBOOL __stdcall _GetStringTypeEx(
//      LCID Locale,
//      DWORD dwInfoType,
//      const unichar * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//   static DWORD WINAPI  _GetTempPath(
//      DWORD nBufferLength,
//      unichar * pBuffer);
//
//   static UINT WINAPI _GetTempFileName(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      UINT uUnique,
//      unichar * pTempFileName);
//
//   static HANDLE WINAPI _CreateFile(
//      const unichar * pFileName,
//
//      DWORD dwDesiredAccess,
//      DWORD dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      DWORD dwCreationDisposition,
//      DWORD dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//   static DWORD WINAPI _GetModuleFileName(
//       HMODULE hModule,
//       unichar * pFilename,
//
//       DWORD nSize
//       );
//// xxx    static WINBOOL WINAPI _GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
//
//// xxx        LPWNDCLASSW pwndclass);
//
//// xxx    static ATOM WINAPI _RegisterClass(
//         // xxx CONST WNDCLASSW *pwndclass);
//
//
//   static oswindow WINAPI _CreateWindowEx(
//      DWORD dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      DWORD dwStyle,
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
//// xxx    WINBOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    WINBOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   WINBOOL (WINAPI * m_pfnMoveFile)(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   DWORD (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   WINBOOL (WINAPI * m_pfnGetVolumeInformation)(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      DWORD nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      DWORD nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//// xxx       const unichar * pszPath,
//// xxx       DWORD dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       UINT cbFileInfo,
//// xxx       UINT uFlags);
//   WINBOOL (__stdcall * m_pfnGetStringTypeEx)(
//      LCID Locale,
//      DWORD dwInfoType,
//      const unichar * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//   DWORD (WINAPI * m_pfnGetTempPath)(
//      DWORD nBufferLength,
//      unichar * pBuffer);
//
//   UINT (WINAPI * m_pfnGetTempFileName)(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      UINT uUnique,
//      unichar * pTempFileName);
//
//   HANDLE (WINAPI * m_pfnCreateFile)(
//      const unichar * pFileName,
//
//      DWORD dwDesiredAccess,
//      DWORD dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      DWORD dwCreationDisposition,
//      DWORD dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//
//   DWORD (WINAPI * m_pfnGetModuleFileName)(
//       HMODULE hModule,
//       unichar * pFilename,
//
//       DWORD nSize
//       );
//
//// xxx    WINBOOL (WINAPI * m_pfnGetClassInfo)(
//       // xxx HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
//
//// xxx        LPWNDCLASSW pwndclass);
//
//
//   // xxx ATOM (WINAPI * m_pfnRegisterClass)(
//         // xxx CONST WNDCLASSW *pwndclass);
//
//
//   oswindow (WINAPI * m_pfnCreateWindowEx)(
//      DWORD dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      DWORD dwStyle,
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
//// xxx    static WINBOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
//// xxx    static WINBOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//// xxx    static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//// xxx    static WINBOOL WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//   static WINBOOL MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//   static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static DWORD GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static WINBOOL GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      DWORD nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      DWORD nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    static WH_SHSTDAPI(DWORD) SHGetFileInfo(
//// xxx       const unichar * pszPath,
//// xxx       DWORD dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       UINT cbFileInfo,
//// xxx       UINT uFlags);
//
//   static WINBOOL  GetStringTypeEx(
//      LCID Locale,
//      DWORD dwInfoType,
//      const char * pSrcStr,
//
//      i32 cchSrc,
//      LPWORD pCharType);
//
//
//   static DWORD GetTempPathW(
//      DWORD nBufferLength,
//      unichar * pBuffer);
//
//
//   static UINT GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      UINT uUnique,
//      unichar * pTempFileName);
//
//
//   static HANDLE CreateFile(
//      const unichar * pFileName,
//
//      DWORD dwDesiredAccess,
//      DWORD dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      DWORD dwCreationDisposition,
//      DWORD dwFlagsAndAttributes,
//      HANDLE hTemplateFile);
//
//   static DWORD WINAPI GetModuleFileName(
//       HMODULE hModule,
//        unichar * pFilename,
//
//        DWORD nSize
//       );
//
//// xxx    static WINBOOL WINAPI GetClassInfo(
//// xxx        HINSTANCE hInstance ,
//// xxx        const unichar * pClassName,
//
//// xxx        LPWNDCLASSW pwndclass);
//
//
//// xxx    static ATOM WINAPI RegisterClass(
//// xxx          CONST WNDCLASSW *pwndclass);
//
//
//   static oswindow WINAPI CreateWindowEx(
//      DWORD dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      DWORD dwStyle,
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
//// xxx    static WH_SHSTDAPI(DWORD) SHGetFileInfo(
//// xxx       const char * pszPath,
//// xxx       DWORD dwFileAttributes,
//// xxx       SHFILEINFO *psfi,
//// xxx       UINT cbFileInfo,
//// xxx       UINT uFlags);
//
//   static DWORD GetTempPath(string & str);
//
//   static UINT GetTempFileName(
//      const char * pszPath,
//
//      const char * pszPrefix,
//
//      UINT uUnique,
//      string & str);
//
//   static WINBOOL MoveFile(const char * pExistingFileName, const char * lpNewFileName);
//
//*/
//};
//
//
//
///*inline WINBOOL shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
//{
//   unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//   if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
//   {
//      free(pwszPath);
//      return FALSE;
//   }
//   ::str::international::unicode_to_utf8(str, pwszPath);
//   free(pwszPath);
//   return TRUE;
//}
//*/
///*
//
//inline WINBOOL shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
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
//inline WINBOOL shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)
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
//inline DWORD shell::GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
//
//{
//   return (*theLinuxShell.m_pfnGetFullPathName)(pFileName, nBufferLength, lpBuffer, lpFilePart);
//
//}
//
//
//inline WINBOOL shell::MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)
//
//{
//   return (*theLinuxShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName);
//
//}
//
//inline WINBOOL shell::GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      DWORD nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      DWORD nFileSystemNameSize)         // length of file system name buffer
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
//inline DWORD shell::SHGetFileInfo(
//   const unichar * pszPath,
//   DWORD dwFileAttributes,
//   SHFILEINFOW *psfi,
//   UINT cbFileInfo,
//   UINT uFlags)
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
//inline DWORD shell::GetTempPathW(
//   DWORD nBufferLength,
//   unichar * pBuffer)
//
//{
//     return (*theLinuxShell.m_pfnGetTempPath)(
//      nBufferLength,
//      pBuffer);
//
//}
//
//inline UINT shell::GetTempFileNameW(
//   const unichar * pszPath,
//
//   const unichar * pszPrefix,
//
//   UINT uUnique,
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
//   DWORD dwDesiredAccess,
//   DWORD dwShareMode,
//   LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//   DWORD dwCreationDisposition,
//   DWORD dwFlagsAndAttributes,
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
//inline DWORD shell::GetModuleFileName(
//    HMODULE hModule,
//    unichar * pFilename,
//
//    DWORD nSize
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
//inline WINBOOL shell::GetClassInfo(
//   HINSTANCE hInstance ,
//   const unichar * pClassName,
//
//   LPWNDCLASSW pwndclass)
//
//{
//   return (*theLinuxShell.m_pfnGetClassInfo)(
//      hInstance ,
//      pClassName,
//
//      pwndclass);
//
//}
//
//inline ATOM shell::RegisterClass(
//   CONST WNDCLASSW *pwndclass)
//
//{
//   return (*theLinuxShell.m_pfnRegisterClass)(
//      pwndclass);
//
//}*/
///*
//inline oswindow shell::CreateWindowEx(
//   DWORD dwExStyle,
//   const unichar * pClassName,
//
//   const unichar * pWindowName,
//
//   DWORD dwStyle,
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
//inline DWORD shell::GetTempPath(string & str)
//{
//   unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//   DWORD dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//   ::str::international::unicode_to_utf8(str, pwsz);
//   free(pwsz);
//   return dwResult;
//}
//
//inline UINT shell::GetTempFileName(const char * pszPath, const char * pszPrefix, UINT uUnique, string & str)
//
//{
//   wstring wstrPathName = ::str::international::utf8_to_unicode(pszPath);
//
//   wstring wstrPrefixString = ::str::international::utf8_to_unicode(pszPrefix);
//
//   wstring wstr;
//   wstr.get_buffer(MAX_PATH * 4);
//   UINT uiResult = (*theLinuxShell.m_pfnGetTempFileName)(
//      wstrPathName,
//      wstrPrefixString,
//      uUnique,
//      wstr);
//   ::str::international::unicode_to_utf8(str, wstr);
//   return uiResult;
//}
//
//inline WINBOOL shell::MoveFile(const char * pExistingFileName, const char * lpNewFileName)
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
