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
      static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      static BOOL WINAPI _MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
      static unsigned int WINAPI _GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
      static BOOL WINAPI _GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      unsigned int nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      unsigned int nFileSystemNameSize);         // length of file system name buffer
      static dword_ptr __stdcall _SHGetFileInfo(
      const unichar * pszPath,
      unsigned int dwFileAttributes,
      SHFILEINFOW *psfi,
      unsigned int cbFileInfo,
      unsigned int uFlags);
      static BOOL __stdcall _GetStringTypeEx(
      LCID Locale,
      unsigned int dwInfoType,
      const unichar * lpSrcStr,
      int cchSrc,
      LPWORD lpCharType);
      static unsigned int WINAPI  _GetTempPath(
      unsigned int nBufferLength,
      unichar * lpBuffer);
      static unsigned int WINAPI _GetTempFileName(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      unsigned int uUnique,
      unichar * lpTempFileName);
      static HANDLE WINAPI _CreateFile(
      const unichar * lpFileName,
      unsigned int dwDesiredAccess,
      unsigned int dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      unsigned int dwCreationDisposition,
      unsigned int dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
      static unsigned int WINAPI _GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      unsigned int nSize
      );
      static BOOL WINAPI _GetClassInfo(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);
      static ATOM WINAPI _RegisterClass(
      const WNDCLASSW *lpWndClass);

      static oswindow WINAPI _CreateWindowEx(
      unsigned int dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      unsigned int uStyle,
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
      unsigned int (WINAPI * m_pfnGetFullPathName)(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      BOOL (WINAPI * m_pfnGetVolumeInformation)(
         const unichar * lpRootPathName,           // root directory
         unichar * lpVolumeNameBuffer,        // volume name buffer
         unsigned int nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         unichar * lpFileSystemNameBuffer,    // file system name buffer
         unsigned int nFileSystemNameSize);         // length of file system name buffer

      /*   dword_ptr (WINAPI * m_pfnSHGetFileInfo)(      
      const unichar * pszPath,
      unsigned int dwFileAttributes,
      SHFILEINFOW *psfi,
      unsigned int cbFileInfo,
      unsigned int uFlags);*/
      BOOL (WINAPI * m_pfnGetStringTypeEx)(      
         LCID Locale,
         unsigned int dwInfoType,
         const unichar * lpSrcStr,
         int cchSrc,
         LPWORD lpCharType);
      unsigned int (WINAPI * m_pfnGetTempPath)(
         unsigned int nBufferLength,
         unichar * lpBuffer);
      unsigned int (WINAPI * m_pfnGetTempFileName)(
         const unichar * lpPathName,
         const unichar * lpPrefixString,
         unsigned int uUnique,
         unichar * lpTempFileName);
      HANDLE (WINAPI * m_pfnCreateFile)(
         const unichar * lpFileName,
         unsigned int dwDesiredAccess,
         unsigned int dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         unsigned int dwCreationDisposition,
         unsigned int dwFlagsAndAttributes,
         HANDLE hTemplateFile
         );

      unsigned int (WINAPI * m_pfnGetModuleFileName)(
         HMODULE hModule,
         unichar * lpFilename,
         unsigned int nSize
         );

      /*   BOOL (WINAPI * m_pfnGetClassInfo)(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);

      ATOM (WINAPI * m_pfnRegisterClass)(
      const WNDCLASSW *lpWndClass);*/

      oswindow (WINAPI * m_pfnCreateWindowEx)(
         unsigned int dwExStyle,
         const unichar * lpClassName,
         const unichar * lpWindowName,
         unsigned int uStyle,
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
      static unsigned int GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
      static bool GetVolumeInformation(
         const unichar * lpRootPathName,           // root directory
         unichar * lpVolumeNameBuffer,        // volume name buffer
         unsigned int nVolumeNameSize,            // length of name buffer
         LPDWORD lpVolumeSerialNumber,     // volume serial number
         LPDWORD lpMaximumComponentLength, // maximum file name length
         LPDWORD lpFileSystemFlags,        // file system options
         unichar * lpFileSystemNameBuffer,    // file system name buffer
         unsigned int nFileSystemNameSize);         // length of file system name buffer

      /*   static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
      const unichar * pszPath,
      unsigned int dwFileAttributes,
      SHFILEINFOW *psfi,
      unsigned int cbFileInfo,
      unsigned int uFlags);
      */

      static bool  GetStringTypeEx(      
         LCID Locale,
         unsigned int dwInfoType,
         const char * lpSrcStr,
         int cchSrc,
         LPWORD lpCharType);

      static unsigned int GetTempPathW(
         unsigned int nBufferLength,
         unichar * lpBuffer);

      static unsigned int GetTempFileNameW(
         const unichar * lpPathName,
         const unichar * lpPrefixString,
         unsigned int uUnique,
         unichar * lpTempFileName);

      static HANDLE CreateFile(
         const unichar * lpFileName,
         unsigned int dwDesiredAccess,
         unsigned int dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         unsigned int dwCreationDisposition,
         unsigned int dwFlagsAndAttributes,
         HANDLE hTemplateFile);

      static unsigned int WINAPI GetModuleFileName(
         HMODULE hModule,
         unichar * lpFilename,
         unsigned int nSize
         );

      /*   static bool WINAPI GetClassInfo(
      HINSTANCE hInstance ,
      const unichar * lpClassName,
      LPWNDCLASSW lpWndClass);
      */


      /*   static ATOM WINAPI RegisterClass(
      const WNDCLASSW *lpWndClass);
      */

      static oswindow WINAPI CreateWindowEx(
         unsigned int dwExStyle,
         const unichar * lpClassName,
         const unichar * lpWindowName,
         unsigned int uStyle,
         int x,
         int y,
         int nWidth,
         int nHeight,
         oswindow hWndParent,
         HMENU hMenu,
         HINSTANCE hInstance,
         LPVOID lpParam);

      /*
      static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
      const ::file::path & path,
      unsigned int dwFileAttributes,
      SHFILEINFO *psfi,
      unsigned int cbFileInfo,
      unsigned int uFlags);

      */

      static unsigned int GetTempPath(string & str);

      static unsigned int GetTempFileName(
         const char * lpPathName,
         const char * lpPrefixString,
         unsigned int uUnique,
         string & str);

      static bool MoveFile(const char * lpExistingFileName, const char * lpNewFileName);

   };

   /*inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
   {
   unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
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
   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
   {
   return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != false;
   }
   */

   inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata)
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

   inline unsigned int shell::GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
   {
      return (*theWindowsShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
   }


   inline bool shell::MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
   {
      return (*theWindowsShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName) != false;
   }

   inline bool shell::GetVolumeInformation(
      const unichar * lpRootPathName,           // root directory
      unichar * lpVolumeNameBuffer,        // volume name buffer
      unsigned int nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      unichar * lpFileSystemNameBuffer,    // file system name buffer
      unsigned int nFileSystemNameSize)         // length of file system name buffer
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
   inline unsigned int shell::SHGetFileInfo(
   const unichar * pszPath,
   unsigned int dwFileAttributes,
   SHFILEINFOW *psfi,
   unsigned int cbFileInfo,
   unsigned int uFlags)
   {
   return (unsigned int) (*theWindowsShell.m_pfnSHGetFileInfo)(
   pszPath,
   dwFileAttributes,
   psfi,
   cbFileInfo,
   uFlags);
   }
   */


   inline unsigned int shell::GetTempPathW(
      unsigned int nBufferLength,
      unichar * lpBuffer)
   {
      return (*theWindowsShell.m_pfnGetTempPath)(
         nBufferLength,
         lpBuffer);
   }

   inline unsigned int shell::GetTempFileNameW(
      const unichar * lpPathName,
      const unichar * lpPrefixString,
      unsigned int uUnique,
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
      unsigned int dwDesiredAccess,
      unsigned int dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      unsigned int dwCreationDisposition,
      unsigned int dwFlagsAndAttributes,
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

   inline unsigned int shell::GetModuleFileName(
      HMODULE hModule,
      unichar * lpFilename,
      unsigned int nSize
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
      unsigned int dwExStyle,
      const unichar * lpClassName,
      const unichar * lpWindowName,
      unsigned int uStyle,
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

   inline unsigned int shell::GetTempPath(string & str)
   {
      unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
      unsigned int dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
      unicode_to_utf8(str, pwsz);
      free(pwsz);
      return dwResult;
   }

   inline unsigned int shell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, unsigned int uUnique, string & str)
   {
      wstring wstrPathName = utf8_to_unicode(lpPathName);
      wstring wstrPrefixString = utf8_to_unicode(lpPrefixString);
      wstring wstr;
      wstr.get_buffer(MAX_PATH * 4);
      unsigned int uResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
      unicode_to_utf8(str, wstr);
      return uiResult;
   }

   inline bool shell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
   {
      return MoveFile(utf8_to_unicode(lpExistingFileName), utf8_to_unicode(lpNewFileName));
   }


} // namespace universal_windows




