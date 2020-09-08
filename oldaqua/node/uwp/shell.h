#pragma once


#define WH_SHSTDAPI(type) type


namespace uwp
{


   class CLASS_DECL_AQUA shell  
   {
   public:
      shell();
      virtual ~shell();


      static shell theWindowsShell;

      static bool Initialize();

      /*
      static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      static DWORD WINAPI _GetFullPathName(const unichar * lpFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static BOOL WINAPI _GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer
      static dword_ptr __stdcall _SHGetFileInfo(      
      const unichar * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);
      static BOOL __stdcall _GetStringTypeEx(      
      LCID Locale,
      DWORD dwInfoType,
      const unichar * lpSrcStr,
      int cchSrc,
      LPWORD lpCharType);
      static DWORD WINAPI  _GetTempPath(
      DWORD nBufferLength,
      unichar * lpBuffer);
      static UINT WINAPI _GetTempFileName(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      UINT uUnique,
      unichar * lpTempFileName);
      static HANDLE WINAPI _CreateFile(
      const unichar * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
      static DWORD WINAPI _GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      DWORD nSize
      );
      static BOOL WINAPI _GetClassInfo(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);
      static ATOM WINAPI _RegisterClass(
      CONST WNDCLASSW *lpWndClass);

      static oswindow WINAPI _CreateWindowEx(
      DWORD dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      DWORD uStyle,
      int x,
      int y,
      int nWidth,
      int nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);

      */



      //BOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
      HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
      BOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      BOOL (WINAPI * m_pfnMoveFile)(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      DWORD (WINAPI * m_pfnGetFullPathName)(const unichar * lpFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      BOOL (WINAPI * m_pfnGetVolumeInformation)(
         const unichar * lpRootPathName,           // root directory
         unichar * lpVolumeNameBuffer,        // volume name buffer
         DWORD nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         unichar * lpFileSystemNameBuffer,    // file system name buffer
         DWORD nFileSystemNameSize);         // length of file system name buffer

      /*   dword_ptr (WINAPI * m_pfnSHGetFileInfo)(      
      const unichar * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);*/
      BOOL (WINAPI * m_pfnGetStringTypeEx)(      
         LCID Locale,
         DWORD dwInfoType,
         const unichar * lpSrcStr,
         int cchSrc,
         LPWORD lpCharType);
      DWORD (WINAPI * m_pfnGetTempPath)(
         DWORD nBufferLength,
         unichar * lpBuffer);
      UINT (WINAPI * m_pfnGetTempFileName)(
         const unichar * lpPathName,
         const unichar * lpPrefixString,
         UINT uUnique,
         unichar * lpTempFileName);
      HANDLE (WINAPI * m_pfnCreateFile)(
         const unichar * lpFileName,
         DWORD dwDesiredAccess,
         DWORD dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         DWORD dwCreationDisposition,
         DWORD dwFlagsAndAttributes,
         HANDLE hTemplateFile
         );

      DWORD (WINAPI * m_pfnGetModuleFileName)(
         HMODULE hModule,
         unichar * lpFilename,
         DWORD nSize
         );

      /*   BOOL (WINAPI * m_pfnGetClassInfo)(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);

      ATOM (WINAPI * m_pfnRegisterClass)(
      CONST WNDCLASSW *lpWndClass);*/

      oswindow (WINAPI * m_pfnCreateWindowEx)(
         DWORD dwExStyle,
         const unichar * lpClassName,
         const unichar * lpWindowName,
         DWORD uStyle,
         int x,
         int y,
         int nWidth,
         int nHeight,
         oswindow hWndParent,
         HMENU hMenu,
         HINSTANCE hInstance,
         LPVOID lpParam);








      //   static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
      // static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
      static bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static bool MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static DWORD GetFullPathName(const unichar * lpFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static bool GetVolumeInformation(
         const unichar * lpRootPathName,           // root directory
         unichar * lpVolumeNameBuffer,        // volume name buffer
         DWORD nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         unichar * lpFileSystemNameBuffer,    // file system name buffer
         DWORD nFileSystemNameSize);         // length of file system name buffer

      /*   static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
      const unichar * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);
      */

      static bool  GetStringTypeEx(      
         LCID Locale,
         DWORD dwInfoType,
         const char * lpSrcStr,
         int cchSrc,
         LPWORD lpCharType);

      static DWORD GetTempPathW(
         DWORD nBufferLength,
         unichar * lpBuffer);

      static UINT GetTempFileNameW(
         const unichar * lpPathName,
         const unichar * lpPrefixString,
         UINT uUnique,
         unichar * lpTempFileName);

      static HANDLE CreateFile(
         const unichar * lpFileName,
         DWORD dwDesiredAccess,
         DWORD dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         DWORD dwCreationDisposition,
         DWORD dwFlagsAndAttributes,
         HANDLE hTemplateFile);

      static DWORD WINAPI GetModuleFileName(
         HMODULE hModule,
         unichar * lpFilename,
         DWORD nSize
         );

      /*   static bool WINAPI GetClassInfo(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);
      */


      /*   static ATOM WINAPI RegisterClass(
      CONST WNDCLASSW *lpWndClass);
      */

      static oswindow WINAPI CreateWindowEx(
         DWORD dwExStyle,
         const unichar * lpClassName,
         const unichar * lpWindowName,
         DWORD uStyle,
         int x,
         int y,
         int nWidth,
         int nHeight,
         oswindow hWndParent,
         HMENU hMenu,
         HINSTANCE hInstance,
         LPVOID lpParam);

      /*
      static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
      const char * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFO *psfi,
      UINT cbFileInfo,
      UINT uFlags);

      */

      static DWORD GetTempPath(string & str);

      static UINT GetTempFileName(
         const char * lpPathName,
         const char * lpPrefixString,
         UINT uUnique,
         string & str);

      static bool MoveFile(const char * lpExistingFileName, const char * lpNewFileName);

   };

   /*inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
   {
   unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
   if(!(*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
   {
   free(pwszPath);
   return FALSE;
   }
   ::str::international::unicode_to_utf8(str, pwszPath);
   free(pwszPath);
   return TRUE;
   }
   */

   /*
   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
   {
   return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != FALSE;
   }
   */

   inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata)
   {
      return (*theWindowsShell.m_pfnFindFirstFile)(pcsz, lpdata);
   }

   inline bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
   {
      return (*theWindowsShell.m_pfnFindNextFile)(handle, lpdata) != FALSE;
   }

   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
   {
      return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
   }

   inline DWORD shell::GetFullPathName(const unichar * lpFileName, DWORD nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
   {
      return (*theWindowsShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
   }


   inline bool shell::MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
   {
      return (*theWindowsShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName) != FALSE;
   }

   inline bool shell::GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize)         // length of file system name buffer
   {
      return (*theWindowsShell.m_pfnGetVolumeInformation)(
         lpRootPathName,           // root directory
         lpVolumeNameBuffer,        // volume name buffer
         nVolumeNameSize,            // length of name buffer
         lpVolumeSerialNumber,     // volume serial number
         lpMaximumComponentLength, // maximum file name length
         lpFileSystemFlags,        // file system options
         lpFileSystemNameBuffer,    // file system name buffer
         nFileSystemNameSize) != FALSE;         // length of file system name buffer
   }

   /*
   inline DWORD shell::SHGetFileInfo(
   const unichar * pszPath,
   DWORD dwFileAttributes,
   SHFILEINFOW *psfi,
   UINT cbFileInfo,
   UINT uFlags)
   {
   return (DWORD) (*theWindowsShell.m_pfnSHGetFileInfo)(
   pszPath,
   dwFileAttributes,
   psfi,
   cbFileInfo,
   uFlags);
   }
   */


   inline DWORD shell::GetTempPathW(
      DWORD nBufferLength,
      unichar * lpBuffer)
   {
      return (*theWindowsShell.m_pfnGetTempPath)(
         nBufferLength,
         lpBuffer);
   }

   inline UINT shell::GetTempFileNameW(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      UINT uUnique,
      unichar * lpTempFileName)
   {
      return (*theWindowsShell.m_pfnGetTempFileName)(
         lpPathName,
         lpPrefixString,
         uUnique,
         lpTempFileName);
   }

   inline HANDLE shell::CreateFile(
      const unichar * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile)
   {
      return (*theWindowsShell.m_pfnCreateFile)(
         lpFileName,
         dwDesiredAccess,
         dwShareMode,
         lpSecurityAttributes,
         dwCreationDisposition,
         dwFlagsAndAttributes,
         hTemplateFile);
   }

   inline DWORD shell::GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      DWORD nSize
      )
   {
      return (*theWindowsShell.m_pfnGetModuleFileName)(
         hModule,
         lpFilename,
         nSize);
   }

   /*
   inline bool shell::GetClassInfo(
   HINSTANCE hInstance ,
   const unichar * lpClassName,
   LPWNDCLASSW lpWndClass)
   {
   return (*theWindowsShell.m_pfnGetClassInfo)(hInstance, lpClassName, lpWndClass) != FALSE;
   }

   inline ATOM shell::RegisterClass(
   CONST WNDCLASSW *lpWndClass)
   {
   return (*theWindowsShell.m_pfnRegisterClass)(
   lpWndClass);
   }
   */


   inline oswindow shell::CreateWindowEx(
      DWORD dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      DWORD uStyle,
      int x,
      int y,
      int nWidth,
      int nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam)
   {
      return (*theWindowsShell.m_pfnCreateWindowEx)(
         dwExStyle,
         lpClassName,
         lpWindowName,
         uStyle,
         x,
         y,
         nWidth,
         nHeight,
         hWndParent,
         hMenu,
         hInstance,
         lpParam);

   }

   inline DWORD shell::GetTempPath(string & str)
   {
      unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
      DWORD dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
      ::str::international::unicode_to_utf8(str, pwsz);
      free(pwsz);
      return dwResult;
   }

   inline UINT shell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, UINT uUnique, string & str)
   {
      wstring wstrPathName = ::str::international::utf8_to_unicode(lpPathName);
      wstring wstrPrefixString = ::str::international::utf8_to_unicode(lpPrefixString);
      wstring wstr;
      wstr.get_buffer(MAX_PATH * 4);
      UINT uiResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
      ::str::international::unicode_to_utf8(str, wstr);
      return uiResult;
   }

   inline bool shell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
   {
      return MoveFile(::str::international::utf8_to_unicode(lpExistingFileName), ::str::international::utf8_to_unicode(lpNewFileName));
   }


} // namespace uwp




