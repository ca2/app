#pragma once


#define WH_SHSTDAPI(type) type


namespace universal_windows
{


   class CLASS_DECL_ACME shell  
   {
   public:
      shell();
      virtual ~shell();


      static shell theWindowsShell;

      static bool Initialize();

      /*
      static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath);
      static HANDLE WINAPI _FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _MoveFile(const wide_character * lpExistingFileName, const wide_character * lpNewFileName);
      static ::u32 WINAPI _GetFullPathName(const wide_character * lpFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static BOOL WINAPI _GetVolumeInformation(
      const wide_character * lpRootPathName,           // root directory
      wide_character * lpVolumeNameBuffer,        // volume name buffer
      ::u32 nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wide_character * lpFileSystemNameBuffer,    // file system name buffer
      ::u32 nFileSystemNameSize);         // length of file system name buffer
      static dword_ptr __stdcall _SHGetFileInfo(
      const wide_character * pszPath,
      ::u32 dwFileAttributes,
      SHFILEINFOW *psfi,
      ::u32 cbFileInfo,
      ::u32 uFlags);
      static BOOL __stdcall _GetStringTypeEx(
      LCID Locale,
      ::u32 dwInfoType,
      const wide_character * lpSrcStr,
      ::i32 cchSrc,
      LPWORD lpCharType);
      static ::u32 WINAPI  _GetTempPath(
      ::u32 nBufferLength,
      wide_character * lpBuffer);
      static ::u32 WINAPI _GetTempFileName(
      const wide_character * lpPathName,
      const wide_character * lpPrefixString,
      ::u32 uUnique,
      wide_character * lpTempFileName);
      static HANDLE WINAPI _CreateFile(
      const wide_character * lpFileName,
      ::u32 dwDesiredAccess,
      ::u32 dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      ::u32 dwCreationDisposition,
      ::u32 dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
      static ::u32 WINAPI _GetModuleFileName(
      HMODULE hModule,
      wide_character * lpFilename,
      ::u32 nSize
      );
      static BOOL WINAPI _GetClassInfo(
      HINSTANCE hInstance ,
      const wide_character * lpClassName,
      LPWNDCLASSW lpWndClass);
      static ATOM WINAPI _RegisterClass(
      const WNDCLASSW *lpWndClass);

      static oswindow WINAPI _CreateWindowEx(
      ::u32 dwExStyle,
      const wide_character * lpClassName,
      const wide_character * lpWindowName,
      ::u32 uStyle,
      ::i32 x,
      ::i32 y,
      ::i32 nWidth,
      ::i32 nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);

      */



      //BOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, wide_character * pszPath);
      HANDLE (WINAPI * m_pfnFindFirstFile)(const wide_character * pcsz, WIN32_FIND_DATAW * lpdata);
      BOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      BOOL (WINAPI * m_pfnMoveFile)(const wide_character * lpExistingFileName, const wide_character * lpNewFileName);
      WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      ::u32 (WINAPI * m_pfnGetFullPathName)(const wide_character * lpFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
      BOOL (WINAPI * m_pfnGetVolumeInformation)(
         const wide_character * lpRootPathName,           // root directory
         wide_character * lpVolumeNameBuffer,        // volume name buffer
         ::u32 nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         wide_character * lpFileSystemNameBuffer,    // file system name buffer
         ::u32 nFileSystemNameSize);         // length of file system name buffer

      /*   dword_ptr (WINAPI * m_pfnSHGetFileInfo)(      
      const wide_character * pszPath,
      ::u32 dwFileAttributes,
      SHFILEINFOW *psfi,
      ::u32 cbFileInfo,
      ::u32 uFlags);*/
      BOOL (WINAPI * m_pfnGetStringTypeEx)(      
         LCID Locale,
         ::u32 dwInfoType,
         const wide_character * lpSrcStr,
         ::i32 cchSrc,
         LPWORD lpCharType);
      ::u32 (WINAPI * m_pfnGetTempPath)(
         ::u32 nBufferLength,
         wide_character * lpBuffer);
      ::u32 (WINAPI * m_pfnGetTempFileName)(
         const wide_character * lpPathName,
         const wide_character * lpPrefixString,
         ::u32 uUnique,
         wide_character * lpTempFileName);
      HANDLE (WINAPI * m_pfnCreateFile)(
         const wide_character * lpFileName,
         ::u32 dwDesiredAccess,
         ::u32 dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         ::u32 dwCreationDisposition,
         ::u32 dwFlagsAndAttributes,
         HANDLE hTemplateFile
         );

      ::u32 (WINAPI * m_pfnGetModuleFileName)(
         HMODULE hModule,
         wide_character * lpFilename,
         ::u32 nSize
         );

      /*   BOOL (WINAPI * m_pfnGetClassInfo)(
      HINSTANCE hInstance ,
      const wide_character * lpClassName,
      LPWNDCLASSW lpWndClass);

      ATOM (WINAPI * m_pfnRegisterClass)(
      const WNDCLASSW *lpWndClass);*/

      oswindow (WINAPI * m_pfnCreateWindowEx)(
         ::u32 dwExStyle,
         const wide_character * lpClassName,
         const wide_character * lpWindowName,
         ::u32 uStyle,
         ::i32 x,
         ::i32 y,
         ::i32 nWidth,
         ::i32 nHeight,
         oswindow hWndParent,
         HMENU hMenu,
         HINSTANCE hInstance,
         LPVOID lpParam);








      //   static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
      // static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath);
      static HANDLE FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * lpdata);
      static bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static bool MoveFile(const wide_character * lpExistingFileName, const wide_character * lpNewFileName);
      static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static ::u32 GetFullPathName(const wide_character * lpFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart);
      static bool GetVolumeInformation(
         const wide_character * lpRootPathName,           // root directory
         wide_character * lpVolumeNameBuffer,        // volume name buffer
         ::u32 nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         wide_character * lpFileSystemNameBuffer,    // file system name buffer
         ::u32 nFileSystemNameSize);         // length of file system name buffer

      /*   static WH_SHSTDAPI(::u32) SHGetFileInfo(
      const wide_character * pszPath,
      ::u32 dwFileAttributes,
      SHFILEINFOW *psfi,
      ::u32 cbFileInfo,
      ::u32 uFlags);
      */

      static bool  GetStringTypeEx(      
         LCID Locale,
         ::u32 dwInfoType,
         const_char_pointer lpSrcStr,
         ::i32 cchSrc,
         LPWORD lpCharType);

      static ::u32 GetTempPathW(
         ::u32 nBufferLength,
         wide_character * lpBuffer);

      static ::u32 GetTempFileNameW(
         const wide_character * lpPathName,
         const wide_character * lpPrefixString,
         ::u32 uUnique,
         wide_character * lpTempFileName);

      static HANDLE CreateFile(
         const wide_character * lpFileName,
         ::u32 dwDesiredAccess,
         ::u32 dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         ::u32 dwCreationDisposition,
         ::u32 dwFlagsAndAttributes,
         HANDLE hTemplateFile);

      static ::u32 WINAPI GetModuleFileName(
         HMODULE hModule,
         wide_character * lpFilename,
         ::u32 nSize
         );

      /*   static bool WINAPI GetClassInfo(
      HINSTANCE hInstance ,
      const wide_character * lpClassName,
      LPWNDCLASSW lpWndClass);
      */


      /*   static ATOM WINAPI RegisterClass(
      const WNDCLASSW *lpWndClass);
      */

      static oswindow WINAPI CreateWindowEx(
         ::u32 dwExStyle,
         const wide_character * lpClassName,
         const wide_character * lpWindowName,
         ::u32 uStyle,
         ::i32 x,
         ::i32 y,
         ::i32 nWidth,
         ::i32 nHeight,
         oswindow hWndParent,
         HMENU hMenu,
         HINSTANCE hInstance,
         LPVOID lpParam);

      /*
      static WH_SHSTDAPI(::u32) SHGetFileInfo(
      const ::file::path & path,
      ::u32 dwFileAttributes,
      SHFILEINFO *psfi,
      ::u32 cbFileInfo,
      ::u32 uFlags);

      */

      static ::u32 GetTempPath(string & str);

      static ::u32 GetTempFileName(
         const_char_pointer lpPathName,
         const_char_pointer lpPrefixString,
         ::u32 uUnique,
         string & str);

      static bool MoveFile(const_char_pointer lpExistingFileName, const_char_pointer lpNewFileName);

   };

   /*inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
   {
   wide_character * pwszPath = (wide_character * ) malloc(sizeof(unichar) * MAX_PATH * 4);
   if(!(*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
   {
   free(pwszPath);
   return false;
   }
   unicode_to_utf8(str, pwszPath);
   free(pwszPath);
   return true;
   }
   */

   /*
   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, wide_character * pszPath)
   {
   return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != false;
   }
   */

   inline HANDLE shell::FindFirstFile(const wide_character * pcsz, WIN32_FIND_DATAW * lpdata)
   {
      return (*theWindowsShell.m_pfnFindFirstFile)(pcsz, lpdata);
   }

   inline bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
   {
      return (*theWindowsShell.m_pfnFindNextFile)(handle, lpdata) != false;
   }

   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
   {
      return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
   }

   inline ::u32 shell::GetFullPathName(const wide_character * lpFileName, ::u32 nBufferLength, wide_character * lpBuffer, wide_character * * lpFilePart)
   {
      return (*theWindowsShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
   }


   inline bool shell::MoveFile(const wide_character * lpExistingFileName, const wide_character * lpNewFileName)
   {
      return (*theWindowsShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName) != false;
   }

   inline bool shell::GetVolumeInformation(
      const wide_character * lpRootPathName,           // root directory
      wide_character * lpVolumeNameBuffer,        // volume name buffer
      ::u32 nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wide_character * lpFileSystemNameBuffer,    // file system name buffer
      ::u32 nFileSystemNameSize)         // length of file system name buffer
   {
      return (*theWindowsShell.m_pfnGetVolumeInformation)(
         lpRootPathName,           // root directory
         lpVolumeNameBuffer,        // volume name buffer
         nVolumeNameSize,            // length of name buffer
         lpVolumeSerialNumber,     // volume serial number
         lpMaximumComponentLength, // maximum file name length
         lpFileSystemFlags,        // file system options
         lpFileSystemNameBuffer,    // file system name buffer
         nFileSystemNameSize) != false;         // length of file system name buffer
   }

   /*
   inline ::u32 shell::SHGetFileInfo(
   const wide_character * pszPath,
   ::u32 dwFileAttributes,
   SHFILEINFOW *psfi,
   ::u32 cbFileInfo,
   ::u32 uFlags)
   {
   return (::u32) (*theWindowsShell.m_pfnSHGetFileInfo)(
   pszPath,
   dwFileAttributes,
   psfi,
   cbFileInfo,
   uFlags);
   }
   */


   inline ::u32 shell::GetTempPathW(
      ::u32 nBufferLength,
      wide_character * lpBuffer)
   {
      return (*theWindowsShell.m_pfnGetTempPath)(
         nBufferLength,
         lpBuffer);
   }

   inline ::u32 shell::GetTempFileNameW(
      const wide_character * lpPathName,
      const wide_character * lpPrefixString,
      ::u32 uUnique,
      wide_character * lpTempFileName)
   {
      return (*theWindowsShell.m_pfnGetTempFileName)(
         lpPathName,
         lpPrefixString,
         uUnique,
         lpTempFileName);
   }

   inline HANDLE shell::CreateFile(
      const wide_character * lpFileName,
      ::u32 dwDesiredAccess,
      ::u32 dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      ::u32 dwCreationDisposition,
      ::u32 dwFlagsAndAttributes,
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

   inline ::u32 shell::GetModuleFileName(
      HMODULE hModule,
      wide_character * lpFilename,
      ::u32 nSize
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
   const wide_character * lpClassName,
   LPWNDCLASSW lpWndClass)
   {
   return (*theWindowsShell.m_pfnGetClassInfo)(hInstance, lpClassName, lpWndClass) != false;
   }

   inline ATOM shell::RegisterClass(
   const WNDCLASSW *lpWndClass)
   {
   return (*theWindowsShell.m_pfnRegisterClass)(
   lpWndClass);
   }
   */


   inline oswindow shell::CreateWindowEx(
      ::u32 dwExStyle,
      const wide_character * lpClassName,
      const wide_character * lpWindowName,
      ::u32 uStyle,
      ::i32 x,
      ::i32 y,
      ::i32 nWidth,
      ::i32 nHeight,
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

   inline ::u32 shell::GetTempPath(string & str)
   {
      wide_character * pwsz = (wide_character * ) malloc(sizeof(unichar) * MAX_PATH * 4);
      ::u32 dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
      unicode_to_utf8(str, pwsz);
      free(pwsz);
      return dwResult;
   }

   inline ::u32 shell::GetTempFileName(const_char_pointer lpPathName, const_char_pointer lpPrefixString, ::u32 uUnique, string & str)
   {
      wstring wstrPathName = utf8_to_unicode(lpPathName);
      wstring wstrPrefixString = utf8_to_unicode(lpPrefixString);
      wstring wstr;
      wstr.get_buffer(MAX_PATH * 4);
      ::u32 uResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
      unicode_to_utf8(str, wstr);
      return uiResult;
   }

   inline bool shell::MoveFile(const_char_pointer lpExistingFileName, const_char_pointer lpNewFileName)
   {
      return MoveFile(utf8_to_unicode(lpExistingFileName), utf8_to_unicode(lpNewFileName));
   }


} // namespace universal_windows




