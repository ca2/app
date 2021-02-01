#pragma once

//
//#define WH_SHSTDAPI(type) type
//
//
//namespace windows
//{
//
//
//   class CLASS_DECL_ACME shell  
//   {
//   public:
//
//
//      static shell theWindowsShell;
//
//
//      shell();
//      virtual ~shell();
//
//
//      static bool Initialize();
///*      static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//      static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      static BOOL WINAPI _MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      static ::u32 WINAPI _GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      static BOOL WINAPI _GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         ::u32 nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         ::u32 nFileSystemNameSize);         // length of file system name buffer
//      static uptr __stdcall _SHGetFileInfo(
//         const unichar * pszPath,
//         ::u32 dwFileAttributes,
//         SHFILEINFOW *psfi,
//         ::u32 cbFileInfo,
//         ::u32 uFlags);
//      static BOOL __stdcall _GetStringTypeEx(
//         LCID Locale,
//         ::u32 dwInfoType,
//         const unichar * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//      static ::u32 WINAPI  _GetTempPath(
//         ::u32 nBufferLength,
//         unichar * pBuffer);
//
//      static ::u32 WINAPI _GetTempFileName(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         ::u32 uUnique,
//         unichar * pTempFileName);
//
//      static HANDLE WINAPI _CreateFile(
//         const unichar * pFileName,
//
//         ::u32 dwDesiredAccess,
//         ::u32 dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         ::u32 dwCreationDisposition,
//         ::u32 dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//      static ::u32 WINAPI _GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         ::u32 nSize
//         );
//      static BOOL WINAPI _GetClassInfo(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW pwndclass);
//
//      static ATOM WINAPI _RegisterClass(
//         const WNDCLASSW *pwndclass);
//
//
//      static oswindow WINAPI _CreateWindowEx(
//         ::u32 dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         ::u32 dwStyle,
//         i32 x,
//         i32 y,
//         i32 nWidth,
//         i32 nHeight,
//         oswindow oswindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);*/
//
//
//
//
//
//
//      BOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
//      HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      BOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      BOOL (WINAPI * m_pfnMoveFile)(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      ::u32 (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      BOOL (WINAPI * m_pfnGetVolumeInformation)(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         ::u32 nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//      DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//         const unichar * pszPath,
//         ::u32 dwFileAttributes,
//         SHFILEINFOW *psfi,
//         ::u32 cbFileInfo,
//         ::u32 uFlags);
//      BOOL (__stdcall * m_pfnGetStringTypeEx)(
//         LCID Locale,
//         ::u32 dwInfoType,
//         const unichar * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//      ::u32 (WINAPI * m_pfnGetTempPath)(
//         ::u32 nBufferLength,
//         unichar * pBuffer);
//
//      ::u32 (WINAPI * m_pfnGetTempFileName)(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         ::u32 uUnique,
//         unichar * pTempFileName);
//
//      HANDLE (WINAPI * m_pfnCreateFile)(
//         const unichar * pFileName,
//
//         ::u32 dwDesiredAccess,
//         ::u32 dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         ::u32 dwCreationDisposition,
//         ::u32 dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//
//      ::u32 (WINAPI * m_pfnGetModuleFileName)(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         ::u32 nSize
//         );
//
//      BOOL (WINAPI * m_pfnGetClassInfo)(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW pwndclass);
//
//
//      ATOM (WINAPI * m_pfnRegisterClass)(
//         const WNDCLASSW *pwndclass);
//
//
//      oswindow (WINAPI * m_pfnCreateWindowEx)(
//         ::u32 dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         ::u32 dwStyle,
//         i32 x,
//         i32 y,
//         i32 nWidth,
//         i32 nHeight,
//         oswindow oswindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);
//
//
//
//
//
//
//
//
//
//      static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
//      static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//      static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      static bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      static bool MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      static ::u32 GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static bool GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         ::u32 nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         ::u32 nFileSystemNameSize);         // length of file system name buffer
//
//      static WH_SHSTDAPI(::u32) SHGetFileInfo(
//         const unichar * pszPath,
//         ::u32 dwFileAttributes,
//         SHFILEINFOW *psfi,
//         ::u32 cbFileInfo,
//         ::u32 uFlags);
//
//      static bool  GetStringTypeEx(      
//         LCID Locale,
//         ::u32 dwInfoType,
//         const char * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//
//      static ::u32 GetTempPathW(
//         ::u32 nBufferLength,
//         unichar * pBuffer);
//
//
//      static ::u32 GetTempFileNameW(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         ::u32 uUnique,
//         unichar * pTempFileName);
//
//
//      static HANDLE CreateFile(
//         const unichar * pFileName,
//
//         ::u32 dwDesiredAccess,
//         ::u32 dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         ::u32 dwCreationDisposition,
//         ::u32 dwFlagsAndAttributes,
//         HANDLE hTemplateFile);
//
//      static ::u32 WINAPI GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         ::u32 nSize
//         );
//
//      static bool WINAPI GetClassInfo(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW pwndclass);
//
//
//      static ATOM WINAPI RegisterClass(
//         const WNDCLASSW *pwndclass);
//
//
//      static oswindow WINAPI CreateWindowEx(
//         ::u32 dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         ::u32 dwStyle,
//         i32 x,
//         i32 y,
//         i32 nWidth,
//         i32 nHeight,
//         oswindow oswindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);
//
//
//
//      static WH_SHSTDAPI(::u32) SHGetFileInfo(
//         const char * pszPath,
//         ::u32 dwFileAttributes,
//         SHFILEINFO *psfi,
//         ::u32 cbFileInfo,
//         ::u32 uFlags);
//
//      static ::u32 GetTempPath(string & str);
//
//      static ::u32 GetTempFileName(
//         const char * pszPath,
//
//         const char * pszPrefix,
//
//         ::u32 uUnique,
//         string & str);
//
//      static bool MoveFile(const char * pExistingFileName, const char * lpNewFileName);
//
//
//   };
//
//   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
//   {
//      unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//      if(!(*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
//      {
//         free(pwszPath);
//         return false;
//      }
//      ::str::international::unicode_to_utf8(str, pwszPath);
//      free(pwszPath);
//      return true;
//   }
//
//
//   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
//   {
//      return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != false;
//   }
//
//   inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata)
//
//   {
//      return (*theWindowsShell.m_pfnFindFirstFile)(pcsz, pdata);
//
//   }
//
//   inline bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)
//
//   {
//      return (*theWindowsShell.m_pfnFindNextFile)(handle, pdata) != false;
//
//   }
//
//   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
//   {
//      return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
//   }
//
//   inline ::u32 shell::GetFullPathName(const unichar * pFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
//
//   {
//      return (*theWindowsShell.m_pfnGetFullPathName)(pFileName, nBufferLength, lpBuffer, lpFilePart);
//
//   }
//
//
//   inline bool shell::MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)
//
//   {
//      return (*theWindowsShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName) != false;
//
//   }
//
//   inline bool shell::GetVolumeInformation(
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
//   {
//      return (*theWindowsShell.m_pfnGetVolumeInformation)(
//         pRootPathName,           // root directory
//
//         pVolumeNameBuffer,        // volume name buffer
//
//         nVolumeNameSize,            // length of name buffer
//         pVolumeSerialNumber,     // volume serial number
//
//         pMaximumComponentLength, // maximum file name length
//
//         pFileSystemFlags,        // file system options
//
//         pFileSystemNameBuffer,    // file system name buffer
//
//         nFileSystemNameSize) != false;         // length of file system name buffer
//   }
//
//   inline ::u32 shell::SHGetFileInfo(
//      const unichar * pszPath,
//      ::u32 dwFileAttributes,
//      SHFILEINFOW *psfi,
//      ::u32 cbFileInfo,
//      ::u32 uFlags)
//   {
//      return (::u32) (*theWindowsShell.m_pfnSHGetFileInfo)(
//         pszPath,
//         dwFileAttributes,
//         psfi,
//         cbFileInfo,
//         uFlags);
//   }
//
//   inline ::u32 shell::GetTempPathW(
//      ::u32 nBufferLength,
//      unichar * pBuffer)
//
//   {
//      return (*theWindowsShell.m_pfnGetTempPath)(
//         nBufferLength,
//         pBuffer);
//
//   }
//
//   inline ::u32 shell::GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      ::u32 uUnique,
//      unichar * pTempFileName)
//
//   {
//      return (*theWindowsShell.m_pfnGetTempFileName)(
//         pszPath,
//
//         pszPrefix,
//
//         uUnique,
//         pTempFileName);
//
//   }
//
//   inline HANDLE shell::CreateFile(
//      const unichar * pFileName,
//
//      ::u32 dwDesiredAccess,
//      ::u32 dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      ::u32 dwCreationDisposition,
//      ::u32 dwFlagsAndAttributes,
//      HANDLE hTemplateFile)
//   {
//      return (*theWindowsShell.m_pfnCreateFile)(
//         pFileName,
//
//         dwDesiredAccess,
//         dwShareMode,
//         pSecurityAttributes,
//
//         dwCreationDisposition,
//         dwFlagsAndAttributes,
//         hTemplateFile);
//   }
//
//   inline ::u32 shell::GetModuleFileName(
//      HMODULE hModule,
//      unichar * pFilename,
//
//      ::u32 nSize
//      )
//   {
//      return (*theWindowsShell.m_pfnGetModuleFileName)(
//         hModule,
//         pFilename,
//
//         nSize);
//   }
//
//   inline bool shell::GetClassInfo(
//      HINSTANCE hInstance ,
//      const unichar * pClassName,
//
//      LPWNDCLASSW pwndclass)
//
//   {
//      return (*theWindowsShell.m_pfnGetClassInfo)(hInstance, pClassName, pwndclass) != false;
//
//   }
//
//   inline ATOM shell::RegisterClass(
//      const WNDCLASSW *pwndclass)
//
//   {
//      return (*theWindowsShell.m_pfnRegisterClass)(
//         pwndclass);
//
//   }
//
//   inline oswindow shell::CreateWindowEx(
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
//      oswindow oswindow_Parent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam)
//
//   {
//      return (*theWindowsShell.m_pfnCreateWindowEx)(
//         dwExStyle,
//         pClassName,
//
//         pWindowName,
//
//         dwStyle,
//         x,
//         y,
//         nWidth,
//         nHeight,
//         oswindow_Parent,
//         hMenu,
//         hInstance,
//         pParam);
//
//
//   }
//
//   inline ::u32 shell::GetTempPath(string & str)
//   {
//      unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//      ::u32 dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//      ::str::international::unicode_to_utf8(str, pwsz);
//      free(pwsz);
//      return dwResult;
//   }
//
//   inline ::u32 shell::GetTempFileName(const char * pszPath, const char * pszPrefix, ::u32 uUnique, string & str)
//
//   {
//      wstring wstrPathName = ::str::international::utf8_to_unicode(pszPath);
//
//      wstring wstrPrefixString = ::str::international::utf8_to_unicode(pszPrefix);
//
//      wstring wstr;
//      wstr.get_buffer(MAX_PATH * 4);
//      ::u32 uResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
//      ::str::international::unicode_to_utf8(str, wstr);
//      return uiResult;
//   }
//
//   inline bool shell::MoveFile(const char * pExistingFileName, const char * lpNewFileName)
//
//   {
//      return MoveFile(::str::international::utf8_to_unicode(pExistingFileName), ::str::international::utf8_to_unicode(lpNewFileName));
//
//   }
//
//
//} // namespace windows




