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
//   static unsigned int WINAPI _GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//   static int_bool WINAPI _GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      unsigned int nFileSystemNameSize);         // length of file system name buffer
//// xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
//      // xxx const unichar * pszPath,
//      // xxx unsigned int dwFileAttributes,
//      // xxx SHFILEINFOW *psfi,
//      // xxx unsigned int cbFileInfo,
//      // xxx unsigned int uFlags);
//   static int_bool __stdcall _GetStringTypeEx(
//      LCID Locale,
//      unsigned int dwInfoType,
//      const unichar * pSrcStr,
//
//      int cchSrc,
//      LPWORD pCharType);
//
//   static unsigned int WINAPI  _GetTempPath(
//      unsigned int nBufferLength,
//      unichar * pBuffer);
//
//   static unsigned int WINAPI _GetTempFileName(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      unsigned int uUnique,
//      unichar * pTempFileName);
//
//   static HANDLE WINAPI _CreateFile(
//      const unichar * pFileName,
//
//      unsigned int dwDesiredAccess,
//      unsigned int dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      unsigned int dwCreationDisposition,
//      unsigned int dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//   static unsigned int WINAPI _GetModuleFileName(
//       HMODULE hModule,
//       unichar * pFilename,
//
//       unsigned int nSize
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
//      unsigned int dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      unsigned int dwStyle,
//      int x,
//      int y,
//      int nWidth,
//      int nHeight,
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
//   unsigned int (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   int_bool (WINAPI * m_pfnGetVolumeInformation)(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      unsigned int nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//// xxx       const unichar * pszPath,
//// xxx       unsigned int dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       unsigned int cbFileInfo,
//// xxx       unsigned int uFlags);
//   int_bool (__stdcall * m_pfnGetStringTypeEx)(
//      LCID Locale,
//      unsigned int dwInfoType,
//      const unichar * pSrcStr,
//
//      int cchSrc,
//      LPWORD pCharType);
//
//   unsigned int (WINAPI * m_pfnGetTempPath)(
//      unsigned int nBufferLength,
//      unichar * pBuffer);
//
//   unsigned int (WINAPI * m_pfnGetTempFileName)(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      unsigned int uUnique,
//      unichar * pTempFileName);
//
//   HANDLE (WINAPI * m_pfnCreateFile)(
//      const unichar * pFileName,
//
//      unsigned int dwDesiredAccess,
//      unsigned int dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      unsigned int dwCreationDisposition,
//      unsigned int dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      );
//
//   unsigned int (WINAPI * m_pfnGetModuleFileName)(
//       HMODULE hModule,
//       unichar * pFilename,
//
//       unsigned int nSize
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
//      unsigned int dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      unsigned int dwStyle,
//      int x,
//      int y,
//      int nWidth,
//      int nHeight,
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
//   static unsigned int GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//   static int_bool GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      unsigned int nFileSystemNameSize);         // length of file system name buffer
//
//// xxx    static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
//// xxx       const unichar * pszPath,
//// xxx       unsigned int dwFileAttributes,
//// xxx       SHFILEINFOW *psfi,
//// xxx       unsigned int cbFileInfo,
//// xxx       unsigned int uFlags);
//
//   static int_bool  GetStringTypeEx(
//      LCID Locale,
//      unsigned int dwInfoType,
//      const char * pSrcStr,
//
//      int cchSrc,
//      LPWORD pCharType);
//
//
//   static unsigned int GetTempPathW(
//      unsigned int nBufferLength,
//      unichar * pBuffer);
//
//
//   static unsigned int GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      unsigned int uUnique,
//      unichar * pTempFileName);
//
//
//   static HANDLE CreateFile(
//      const unichar * pFileName,
//
//      unsigned int dwDesiredAccess,
//      unsigned int dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      unsigned int dwCreationDisposition,
//      unsigned int dwFlagsAndAttributes,
//      HANDLE hTemplateFile);
//
//   static unsigned int WINAPI GetModuleFileName(
//       HMODULE hModule,
//        unichar * pFilename,
//
//        unsigned int nSize
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
//      unsigned int dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      unsigned int dwStyle,
//      int x,
//      int y,
//      int nWidth,
//      int nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam);
//
//
//
//// xxx    static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
//// xxx       const ::file::path & path,
//// xxx       unsigned int dwFileAttributes,
//// xxx       SHFILEINFO *psfi,
//// xxx       unsigned int cbFileInfo,
//// xxx       unsigned int uFlags);
//
//   static unsigned int GetTempPath(string & str);
//
//   static unsigned int GetTempFileName(
//      const ::file::path & path,
//
//      const ::scoped_string & scopedstrPrefix,
//
//      unsigned int uUnique,
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
//   unicode_to_utf8(str, pwszPath);
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
//inline unsigned int shell::GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
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
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      unsigned int nFileSystemNameSize)         // length of file system name buffer
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
//inline unsigned int shell::SHGetFileInfo(
//   const unichar * pszPath,
//   unsigned int dwFileAttributes,
//   SHFILEINFOW *psfi,
//   unsigned int cbFileInfo,
//   unsigned int uFlags)
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
//inline unsigned int shell::GetTempPathW(
//   unsigned int nBufferLength,
//   unichar * pBuffer)
//
//{
//     return (*theLinuxShell.m_pfnGetTempPath)(
//      nBufferLength,
//      pBuffer);
//
//}
//
//inline unsigned int shell::GetTempFileNameW(
//   const unichar * pszPath,
//
//   const unichar * pszPrefix,
//
//   unsigned int uUnique,
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
//   unsigned int dwDesiredAccess,
//   unsigned int dwShareMode,
//   LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//   unsigned int dwCreationDisposition,
//   unsigned int dwFlagsAndAttributes,
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
//inline unsigned int shell::GetModuleFileName(
//    HMODULE hModule,
//    unichar * pFilename,
//
//    unsigned int nSize
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
//   unsigned int dwExStyle,
//   const unichar * pClassName,
//
//   const unichar * pWindowName,
//
//   unsigned int dwStyle,
//   int x,
//   int y,
//   int nWidth,
//   int nHeight,
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
//inline unsigned int shell::GetTempPath(string & str)
//{
//   unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//   unsigned int dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//   unicode_to_utf8(str, pwsz);
//   free(pwsz);
//   return dwResult;
//}
//
//inline unsigned int shell::GetTempFileName(const ::file::path & path, const ::scoped_string & scopedstrPrefix, unsigned int uUnique, string & str)
//
//{
//   wstring wstrPathName = utf8_to_unicode(scopedstrPath);
//
//   wstring wstrPrefixString = utf8_to_unicode(scopedstrPrefix);
//
//   wstring wstr;
//   wstr.get_buffer(MAX_PATH * 4);
//   unsigned int uResult = (*theLinuxShell.m_pfnGetTempFileName)(
//      wstrPathName,
//      wstrPrefixString,
//      uUnique,
//      wstr);
//   unicode_to_utf8(str, wstr);
//   return uiResult;
//}
//
//inline int_bool shell::MoveFile(const char * pExistingFileName, const char * lpNewFileName)
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
