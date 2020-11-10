#pragma once


#define WH_SHSTDAPI(type) type


namespace android
{


   class CLASS_DECL_ACME shell
   {
   public:


      static shell theLinuxShell;


      shell();
      virtual ~shell();


      static bool Initialize();

      // xxx   static int_bool WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      // xxx   static HANDLE WINAPI _FindFirstFile(const unichar * lpcsz, WIN32_FIND_DATAW * lpdata);
      // xxx   static int_bool WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      /*   static int_bool WINAPI _MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      static ::u32 WINAPI _GetFullPathName(const unichar * lpFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static int_bool WINAPI _GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      ::u32 nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      ::u32 nFileSystemNameSize);         // length of file system name buffer
      // xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
      // xxx const unichar * pszPath,
      // xxx ::u32 dwFileAttributes,
      // xxx SHFILEINFOW *psfi,
      // xxx ::u32 cbFileInfo,
      // xxx ::u32 uFlags);
      static int_bool __stdcall _GetStringTypeEx(
      LCID Locale,
      ::u32 dwInfoType,
      const unichar * lpSrcStr,
      i32 cchSrc,
      LPWORD lpCharType);
      static ::u32 WINAPI  _GetTempPath(
      ::u32 nBufferLength,
      unichar * lpBuffer);
      static ::u32 WINAPI _GetTempFileName(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      ::u32 uUnique,
      unichar * lpTempFileName);
      static HANDLE WINAPI _CreateFile(
      const unichar * lpFileName,
      ::u32 dwDesiredAccess,
      ::u32 dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      ::u32 dwCreationDisposition,
      ::u32 dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
      static ::u32 WINAPI _GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      ::u32 nSize
      );
      // xxx    static int_bool WINAPI _GetClassInfo(
      // xxx        HINSTANCE hInstance ,
      // xxx        const unichar * lpClassName,
      // xxx        LPWNDCLASSW lpWndClass);
      // xxx    static ATOM WINAPI _RegisterClass(
      // xxx CONST WNDCLASSW *lpWndClass);

      static oswindow WINAPI _CreateWindowEx(
      ::u32 dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      ::u32 dwStyle,
      i32 x,
      i32 y,
      i32 nWidth,
      i32 nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);





      // xxx    int_bool (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
      // xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * lpcsz, WIN32_FIND_DATAW * lpdata);
      // xxx    int_bool (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      int_bool (WINAPI * m_pfnMoveFile)(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      ::u32 (WINAPI * m_pfnGetFullPathName)(const unichar * lpFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      int_bool (WINAPI * m_pfnGetVolumeInformation)(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      ::u32 nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      ::u32 nFileSystemNameSize);         // length of file system name buffer

      // xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
      // xxx       const unichar * pszPath,
      // xxx       ::u32 dwFileAttributes,
      // xxx       SHFILEINFOW *psfi,
      // xxx       ::u32 cbFileInfo,
      // xxx       ::u32 uFlags);
      int_bool (__stdcall * m_pfnGetStringTypeEx)(
      LCID Locale,
      ::u32 dwInfoType,
      const unichar * lpSrcStr,
      i32 cchSrc,
      LPWORD lpCharType);
      ::u32 (WINAPI * m_pfnGetTempPath)(
      ::u32 nBufferLength,
      unichar * lpBuffer);
      ::u32 (WINAPI * m_pfnGetTempFileName)(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      ::u32 uUnique,
      unichar * lpTempFileName);
      HANDLE (WINAPI * m_pfnCreateFile)(
      const unichar * lpFileName,
      ::u32 dwDesiredAccess,
      ::u32 dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      ::u32 dwCreationDisposition,
      ::u32 dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );

      ::u32 (WINAPI * m_pfnGetModuleFileName)(
      HMODULE hModule,
      unichar * lpFilename,
      ::u32 nSize
      );

      // xxx    int_bool (WINAPI * m_pfnGetClassInfo)(
      // xxx HINSTANCE hInstance ,
      // xxx        const unichar * lpClassName,
      // xxx        LPWNDCLASSW lpWndClass);

      // xxx ATOM (WINAPI * m_pfnRegisterClass)(
      // xxx CONST WNDCLASSW *lpWndClass);

      oswindow (WINAPI * m_pfnCreateWindowEx)(
      ::u32 dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      ::u32 dwStyle,
      i32 x,
      i32 y,
      i32 nWidth,
      i32 nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);








      // xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
      // xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      // xxx    static HANDLE FindFirstFile(const unichar * lpcsz, WIN32_FIND_DATAW * lpdata);
      // xxx    static int_bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static int_bool MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static ::u32 GetFullPathName(const unichar * lpFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static int_bool GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      ::u32 nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      ::u32 nFileSystemNameSize);         // length of file system name buffer

      // xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
      // xxx       const unichar * pszPath,
      // xxx       ::u32 dwFileAttributes,
      // xxx       SHFILEINFOW *psfi,
      // xxx       ::u32 cbFileInfo,
      // xxx       ::u32 uFlags);

      static int_bool  GetStringTypeEx(
      LCID Locale,
      ::u32 dwInfoType,
      const char * lpSrcStr,
      i32 cchSrc,
      LPWORD lpCharType);

      static ::u32 GetTempPathW(
      ::u32 nBufferLength,
      unichar * lpBuffer);

      static ::u32 GetTempFileNameW(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      ::u32 uUnique,
      unichar * lpTempFileName);

      static HANDLE CreateFile(
      const unichar * lpFileName,
      ::u32 dwDesiredAccess,
      ::u32 dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      ::u32 dwCreationDisposition,
      ::u32 dwFlagsAndAttributes,
      HANDLE hTemplateFile);

      static ::u32 WINAPI GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      ::u32 nSize
      );

      // xxx    static int_bool WINAPI GetClassInfo(
      // xxx        HINSTANCE hInstance ,
      // xxx        const unichar * lpClassName,
      // xxx        LPWNDCLASSW lpWndClass);

      // xxx    static ATOM WINAPI RegisterClass(
      // xxx          CONST WNDCLASSW *lpWndClass);

      static oswindow WINAPI CreateWindowEx(
      ::u32 dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      ::u32 dwStyle,
      i32 x,
      i32 y,
      i32 nWidth,
      i32 nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);


      // xxx    static WH_SHSTDAPI(::u32) SHGetFileInfo(
      // xxx       const char * pszPath,
      // xxx       ::u32 dwFileAttributes,
      // xxx       SHFILEINFO *psfi,
      // xxx       ::u32 cbFileInfo,
      // xxx       ::u32 uFlags);

      static ::u32 GetTempPath(string & str);

      static ::u32 GetTempFileName(
      const char * lpPathName,
      const char * lpPrefixString,
      ::u32 uUnique,
      string & str);

      static int_bool MoveFile(const char * lpExistingFileName, const char * lpNewFileName);
      */
   };



   /*inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
   {
   unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
   if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
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

   inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
   {
   return (*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
   }
   */
   /*
   inline HANDLE shell::FindFirstFile(const unichar * lpcsz, WIN32_FIND_DATAW * lpdata)
   {
   return (*theLinuxShell.m_pfnFindFirstFile)(lpcsz, lpdata);
   }

   inline int_bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
   {
   return (*theLinuxShell.m_pfnFindNextFile)(handle, lpdata);
   }

   */

   /*
   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
   {
   return (*theLinuxShell.m_pfn_fullpath)(UserBuf, path, maxlen);
   }

   inline ::u32 shell::GetFullPathName(const unichar * lpFileName, ::u32 nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
   {
   return (*theLinuxShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
   }


   inline int_bool shell::MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
   {
   return (*theLinuxShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName);
   }

   inline int_bool shell::GetVolumeInformation(
   const unichar * lpRootPathName,           // root directory
   unichar * lpVolumeNameBuffer,        // volume name buffer
   ::u32 nVolumeNameSize,            // length of name buffer
   LPDWORD lpVolumeSerialNumber,     // volume serial number
   LPDWORD lpMaximumComponentLength, // maximum file name length
   LPDWORD lpFileSystemFlags,        // file system options
   unichar * lpFileSystemNameBuffer,    // file system name buffer
   ::u32 nFileSystemNameSize)         // length of file system name buffer
   {
   return (*theLinuxShell.m_pfnGetVolumeInformation)(
   lpRootPathName,           // root directory
   lpVolumeNameBuffer,        // volume name buffer
   nVolumeNameSize,            // length of name buffer
   lpVolumeSerialNumber,     // volume serial number
   lpMaximumComponentLength, // maximum file name length
   lpFileSystemFlags,        // file system options
   lpFileSystemNameBuffer,    // file system name buffer
   nFileSystemNameSize);         // length of file system name buffer
   }

   /*
   inline ::u32 shell::SHGetFileInfo(
   const unichar * pszPath,
   ::u32 dwFileAttributes,
   SHFILEINFOW *psfi,
   ::u32 cbFileInfo,
   ::u32 uFlags)
   {
   return (*theLinuxShell.m_pfnSHGetFileInfo)(
   pszPath,
   dwFileAttributes,
   psfi,
   cbFileInfo,
   uFlags);
   }
   */
   /*
   inline ::u32 shell::GetTempPathW(
   ::u32 nBufferLength,
   unichar * lpBuffer)
   {
   return (*theLinuxShell.m_pfnGetTempPath)(
   nBufferLength,
   lpBuffer);
   }

   inline ::u32 shell::GetTempFileNameW(
   const unichar * lpPathName,
   const unichar * lpPrefixString,
   ::u32 uUnique,
   unichar * lpTempFileName)
   {
   return (*theLinuxShell.m_pfnGetTempFileName)(
   lpPathName,
   lpPrefixString,
   uUnique,
   lpTempFileName);
   }

   inline HANDLE shell::CreateFile(
   const unichar * lpFileName,
   ::u32 dwDesiredAccess,
   ::u32 dwShareMode,
   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
   ::u32 dwCreationDisposition,
   ::u32 dwFlagsAndAttributes,
   HANDLE hTemplateFile)
   {
   return (*theLinuxShell.m_pfnCreateFile)(
   lpFileName,
   dwDesiredAccess,
   dwShareMode,
   lpSecurityAttributes,
   dwCreationDisposition,
   dwFlagsAndAttributes,
   hTemplateFile);
   }

   inline ::u32 shell::GetModuleFileName(
   HMODULE hModule,
   unichar * lpFilename,
   ::u32 nSize
   )
   {
   return (*theLinuxShell.m_pfnGetModuleFileName)(
   hModule,
   lpFilename,
   nSize);
   }

   /*inline int_bool shell::GetClassInfo(
   HINSTANCE hInstance ,
   const unichar * lpClassName,
   LPWNDCLASSW lpWndClass)
   {
   return (*theLinuxShell.m_pfnGetClassInfo)(
   hInstance ,
   lpClassName,
   lpWndClass);
   }

   inline ATOM shell::RegisterClass(
   CONST WNDCLASSW *lpWndClass)
   {
   return (*theLinuxShell.m_pfnRegisterClass)(
   lpWndClass);
   }*/
   /*
   inline oswindow shell::CreateWindowEx(
   ::u32 dwExStyle,
   const unichar * lpClassName,
   const unichar * lpWindowName,
   ::u32 dwStyle,
   i32 x,
   i32 y,
   i32 nWidth,
   i32 nHeight,
   oswindow hWndParent,
   HMENU hMenu,
   HINSTANCE hInstance,
   LPVOID lpParam)
   {
   return (*theLinuxShell.m_pfnCreateWindowEx)(
   dwExStyle,
   lpClassName,
   lpWindowName,
   dwStyle,
   x,
   y,
   nWidth,
   nHeight,
   hWndParent,
   hMenu,
   hInstance,
   lpParam);

   }

   inline ::u32 shell::GetTempPath(string & str)
   {
   unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
   ::u32 dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
   ::str::international::unicode_to_utf8(str, pwsz);
   free(pwsz);
   return dwResult;
   }

   inline ::u32 shell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, ::u32 uUnique, string & str)
   {
   wstring wstrPathName = ::str::international::utf8_to_unicode(lpPathName);
   wstring wstrPrefixString = ::str::international::utf8_to_unicode(lpPrefixString);
   wstring wstr;
   wstr.get_buffer(MAX_PATH * 4);
   ::u32 uResult = (*theLinuxShell.m_pfnGetTempFileName)(
   wstrPathName,
   wstrPrefixString,
   uUnique,
   wstr);
   ::str::international::unicode_to_utf8(str, wstr);
   return uiResult;
   }

   inline int_bool shell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
   {
   return MoveFile(::str::international::utf8_to_unicode(lpExistingFileName), ::str::international::utf8_to_unicode(lpNewFileName));
   }

   */


} // namespace android




