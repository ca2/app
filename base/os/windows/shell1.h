#pragma once

//
//#define WH_SHSTDAPI(type) type
//
//
//namespace windows
//{
//
//
//   class CLASS_DECL_AURA shell  
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
//      static DWORD WINAPI _GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      static BOOL WINAPI _GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         DWORD nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         DWORD nFileSystemNameSize);         // length of file system name buffer
//      static uptr __stdcall _SHGetFileInfo(      
//         const unichar * pszPath,
//         DWORD dwFileAttributes,
//         SHFILEINFOW *psfi,
//         UINT cbFileInfo,
//         UINT uFlags);
//      static BOOL __stdcall _GetStringTypeEx(      
//         LCID Locale,
//         DWORD dwInfoType,
//         const unichar * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//      static DWORD WINAPI  _GetTempPath(
//         DWORD nBufferLength,
//         unichar * pBuffer);
//
//      static UINT WINAPI _GetTempFileName(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         UINT uUnique,
//         unichar * pTempFileName);
//
//      static HANDLE WINAPI _CreateFile(
//         const unichar * pFileName,
//
//         DWORD dwDesiredAccess,
//         DWORD dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         DWORD dwCreationDisposition,
//         DWORD dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//      static DWORD WINAPI _GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         DWORD nSize
//         );
//      static BOOL WINAPI _GetClassInfo(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW pwndclass);
//
//      static ATOM WINAPI _RegisterClass(
//         CONST WNDCLASSW *pwndclass);
//
//
//      static oswindow WINAPI _CreateWindowEx(
//         DWORD dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         DWORD dwStyle,
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
//      DWORD (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      BOOL (WINAPI * m_pfnGetVolumeInformation)(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         DWORD nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         DWORD nFileSystemNameSize);         // length of file system name buffer
//
//      DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(      
//         const unichar * pszPath,
//         DWORD dwFileAttributes,
//         SHFILEINFOW *psfi,
//         UINT cbFileInfo,
//         UINT uFlags);
//      BOOL (__stdcall * m_pfnGetStringTypeEx)(      
//         LCID Locale,
//         DWORD dwInfoType,
//         const unichar * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//      DWORD (WINAPI * m_pfnGetTempPath)(
//         DWORD nBufferLength,
//         unichar * pBuffer);
//
//      UINT (WINAPI * m_pfnGetTempFileName)(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         UINT uUnique,
//         unichar * pTempFileName);
//
//      HANDLE (WINAPI * m_pfnCreateFile)(
//         const unichar * pFileName,
//
//         DWORD dwDesiredAccess,
//         DWORD dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         DWORD dwCreationDisposition,
//         DWORD dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//
//      DWORD (WINAPI * m_pfnGetModuleFileName)(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         DWORD nSize
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
//         CONST WNDCLASSW *pwndclass);
//
//
//      oswindow (WINAPI * m_pfnCreateWindowEx)(
//         DWORD dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         DWORD dwStyle,
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
//      static DWORD GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static bool GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         DWORD nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         DWORD nFileSystemNameSize);         // length of file system name buffer
//
//      static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
//         const unichar * pszPath,
//         DWORD dwFileAttributes,
//         SHFILEINFOW *psfi,
//         UINT cbFileInfo,
//         UINT uFlags);
//
//      static bool  GetStringTypeEx(      
//         LCID Locale,
//         DWORD dwInfoType,
//         const char * pSrcStr,
//
//         i32 cchSrc,
//         LPWORD pCharType);
//
//
//      static DWORD GetTempPathW(
//         DWORD nBufferLength,
//         unichar * pBuffer);
//
//
//      static UINT GetTempFileNameW(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         UINT uUnique,
//         unichar * pTempFileName);
//
//
//      static HANDLE CreateFile(
//         const unichar * pFileName,
//
//         DWORD dwDesiredAccess,
//         DWORD dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         DWORD dwCreationDisposition,
//         DWORD dwFlagsAndAttributes,
//         HANDLE hTemplateFile);
//
//      static DWORD WINAPI GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         DWORD nSize
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
//         CONST WNDCLASSW *pwndclass);
//
//
//      static oswindow WINAPI CreateWindowEx(
//         DWORD dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         DWORD dwStyle,
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
//      static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
//         const char * pszPath,
//         DWORD dwFileAttributes,
//         SHFILEINFO *psfi,
//         UINT cbFileInfo,
//         UINT uFlags);
//
//      static DWORD GetTempPath(string & str);
//
//      static UINT GetTempFileName(
//         const char * pszPath,
//
//         const char * pszPrefix,
//
//         UINT uUnique,
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
//         return FALSE;
//      }
//      ::str::international::unicode_to_utf8(str, pwszPath);
//      free(pwszPath);
//      return TRUE;
//   }
//
//
//   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
//   {
//      return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != FALSE;
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
//      return (*theWindowsShell.m_pfnFindNextFile)(handle, pdata) != FALSE;
//
//   }
//
//   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
//   {
//      return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
//   }
//
//   inline DWORD shell::GetFullPathName(const unichar * pFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
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
//      return (*theWindowsShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName) != FALSE;
//
//   }
//
//   inline bool shell::GetVolumeInformation(
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
//         nFileSystemNameSize) != FALSE;         // length of file system name buffer
//   }
//
//   inline DWORD shell::SHGetFileInfo(
//      const unichar * pszPath,
//      DWORD dwFileAttributes,
//      SHFILEINFOW *psfi,
//      UINT cbFileInfo,
//      UINT uFlags)
//   {
//      return (DWORD) (*theWindowsShell.m_pfnSHGetFileInfo)(
//         pszPath,
//         dwFileAttributes,
//         psfi,
//         cbFileInfo,
//         uFlags);
//   }
//
//   inline DWORD shell::GetTempPathW(
//      DWORD nBufferLength,
//      unichar * pBuffer)
//
//   {
//      return (*theWindowsShell.m_pfnGetTempPath)(
//         nBufferLength,
//         pBuffer);
//
//   }
//
//   inline UINT shell::GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      UINT uUnique,
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
//      DWORD dwDesiredAccess,
//      DWORD dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      DWORD dwCreationDisposition,
//      DWORD dwFlagsAndAttributes,
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
//   inline DWORD shell::GetModuleFileName(
//      HMODULE hModule,
//      unichar * pFilename,
//
//      DWORD nSize
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
//      return (*theWindowsShell.m_pfnGetClassInfo)(hInstance, pClassName, pwndclass) != FALSE;
//
//   }
//
//   inline ATOM shell::RegisterClass(
//      CONST WNDCLASSW *pwndclass)
//
//   {
//      return (*theWindowsShell.m_pfnRegisterClass)(
//         pwndclass);
//
//   }
//
//   inline oswindow shell::CreateWindowEx(
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
//   inline DWORD shell::GetTempPath(string & str)
//   {
//      unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//      DWORD dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//      ::str::international::unicode_to_utf8(str, pwsz);
//      free(pwsz);
//      return dwResult;
//   }
//
//   inline UINT shell::GetTempFileName(const char * pszPath, const char * pszPrefix, UINT uUnique, string & str)
//
//   {
//      wstring wstrPathName = ::str::international::utf8_to_unicode(pszPath);
//
//      wstring wstrPrefixString = ::str::international::utf8_to_unicode(pszPrefix);
//
//      wstring wstr;
//      wstr.get_buffer(MAX_PATH * 4);
//      UINT uiResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
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




