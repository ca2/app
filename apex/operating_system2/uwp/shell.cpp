#include "framework.h"
//#include "universal_windows.h"

/***
*int _validdrive( unsigned drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/
#ifdef WINDOWS_DESKTOP
int __cdecl _validdrive (
unsigned drive
)
{
   unsigned retcode;
   char drvstr[4];

   if ( drive == 0 )
      return 1;

   drvstr[0] = (char) ('A' + drive - 1);
   drvstr[1] = ':';
   drvstr[2] = '\\';
   drvstr[3] = '\0';

   if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
         (retcode == DRIVE_NO_ROOT_DIR) )
      return 0;

   return 1;
}
#endif
/*WCHAR * __cdecl _wgetdcwd (
int drive,
WCHAR *pnbuf,
int maxlen
);

*/
/***
*_TSCHAR *_getcwd(pnbuf, maxlen) - get current working directory of default drive
*
*Purpose:
*       _getcwd gets the current working directory for the ::account::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then nullptr is returned.  If pnbuf = nullptr, maxlen is ignored.
*       An entry int_point "_getdcwd()" is defined with takes the above
*       parameters, plus a drive number.  "_getcwd()" is implemented
*       as a call to "_getcwd()" with the default drive (0).
*
*       If pnbuf = nullptr, maxlen is ignored, and a buffer is automatically
*       allocated using malloc() -- a pointer to which is returned by
*       _getcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       _TSCHAR *pnbuf = pointer to a buffer maintained by the ::account::user;
*       int maxlen = length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the ca.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/

/*WCHAR * __cdecl _wgetcwd (
WCHAR *pnbuf,
int maxlen
)
{
WCHAR *retval;


retval = _wgetdcwd(0, pnbuf, maxlen);

return retval;
}*/


/***
*_TSCHAR *_getdcwd(drive, pnbuf, maxlen) - get ca.w.d. for given drive
*
*Purpose:
*       _getdcwd gets the current working directory for the ::account::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then nullptr is returned.  If pnbuf = nullptr, maxlen is ignored,
*       and a buffer is automatically allocated using malloc() --
*       a pointer to which is returned by _getdcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       int drive   - number of the drive being inquired about
*                     0 = default, 1 = 'a:', 2 = 'b:', etc.
*       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::account::user;
*       int maxlen  - length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the ca.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/


/*WCHAR * __cdecl _wgetdcwd (
int drive,
WCHAR *pnbuf,
int maxlen
)
{
WCHAR *p;
WCHAR dirbuf[_MAX_PATH];
WCHAR drvstr[4];
int len;
WCHAR *pname; /* only used as argument to GetFullPathName */

/*
* GetCurrentDirectory only works for the default drive in Win32
*/
/*      if ( drive != 0 ) {
/*
* Not the default drive - make sure it's valid.
*/
/*        if ( !_validdrive(drive) ) {
_doserrno = ERROR_INVALID_DRIVE;
//                errno = EACCES;
return nullptr;
}

/*
* get the current directory string on that drive and its length
*/
/*      drvstr[0] = (char) ('A' - 1 + drive);
drvstr[1] = ':';
drvstr[2] = '.';
drvstr[3] = '\0';
len = shell::GetFullPathName( drvstr,
sizeof(dirbuf) / sizeof(_TSCHAR),
dirbuf,
&pname );

} else {

/*
* get the current directory string and its length
*/
/*            len = GetCurrentDirectory( sizeof(dirbuf) / sizeof(_TSCHAR),
(char *)dirbuf );
}

/* API call failed, or buffer not large enough */
/*      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
return nullptr;

/*
* Set up the buffer.
*/
/*    if ( (p = pnbuf) == nullptr ) {
/*
* allocate a buffer for the ::account::user.
*/
/*      if ( (p = (WCHAR *)malloc(maximum(len, maxlen) * sizeof(WCHAR)))
== nullptr )
{
//                errno = ENOMEM;
return nullptr;
}
}
else if ( len > maxlen ) {
/*
* Won't fit in the ::account::user-supplied buffer!
*/
//            errno = ERANGE; /* Won't fit in ::account::user buffer */
/*    return nullptr;
}

/*
* Place the current directory string into the ::account::user buffer
*/
/*
return wcscpy(p, dirbuf);
}

/*#ifndef WPRFLAG

/***
*int _validdrive( unsigned drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/

/*int __cdecl _validdrive (
unsigned drive
)
{
unsigned retcode;
char drvstr[4];

if ( drive == 0 )
return 1;

drvstr[0] = 'A' + drive - 1;
drvstr[1] = ':';
drvstr[2] = '\\';
drvstr[3] = '\0';

if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
(retcode == DRIVE_NO_ROOT_DIR) )
return 0;

return 1;
}*/


namespace universal_windows
{

   /*
   shell shell::theWindowsShell;

   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   shell::shell()
   {

   }

   shell::~shell()
   {

   }

   bool shell::Initialize()
   {
      /*
      unsigned int dwVersion = GetVersion();

      // get the Windows version.

      unsigned int dwWindowsMajorVersion =  (unsigned int)(lower_byte(LOWORD(dwVersion)));
      //   unsigned int dwWindowsMinorVersion =  (unsigned int)(higher_byte(LOWORD(dwVersion)));

      // get the build number.

      unsigned int dwBuild;

      if (dwVersion < I32_MINIMUM)              // Windows NT
         dwBuild = (unsigned int)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (unsigned int)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild =  0;

      bool bNativeUnicode;
      if (dwVersion < I32_MINIMUM)              // Windows NT
         bNativeUnicode = true;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         bNativeUnicode = false;
      else                                     // Windows Me/98/95
         bNativeUnicode = false;


   //      if(bNativeUnicode)
      {
         theWindowsShell.m_pfnSHGetPathFromIDList = ::SHGetPathFromIDListW;
         theWindowsShell.m_pfnFindFirstFile = ::FindFirstFileW;
         theWindowsShell.m_pfnFindNextFile = ::FindNextFileW;
         theWindowsShell.m_pfnMoveFile = ::MoveFileW;
         theWindowsShell.m_pfn_fullpath = ::_wfullpath;
         theWindowsShell.m_pfnGetFullPathName = ::GetFullPathNameW;
         theWindowsShell.m_pfnGetVolumeInformation = ::GetVolumeInformationW;
         theWindowsShell.m_pfnSHGetFileInfo = ::SHGetFileInfoW;
         theWindowsShell.m_pfnGetStringTypeEx = ::GetStringTypeExW;
         theWindowsShell.m_pfnGetTempPath = ::GetTempPathW;
         theWindowsShell.m_pfnGetTempFileName = ::GetTempFileNameW;
         theWindowsShell.m_pfnCreateFile = ::CreateFileW;
         theWindowsShell.m_pfnGetModuleFileName = ::GetModuleFileNameW;
         theWindowsShell.m_pfnGetClassInfo = ::GetClassInfoW;
         theWindowsShell.m_pfnRegisterClass = ::RegisterClassW;
         theWindowsShell.m_pfnCreateWindowEx = ::CreateWindowExW;
      }
   /*    else
      {
         theWindowsShell.m_pfnSHGetPathFromIDList = _SHGetPathFromIDList;
         theWindowsShell.m_pfnFindFirstFile = _FindFirstFile;
         theWindowsShell.m_pfnFindNextFile = _FindNextFile;
         theWindowsShell.m_pfnMoveFile = _MoveFile;
         theWindowsShell.m_pfn_fullpath = __fullpath;
         theWindowsShell.m_pfnGetFullPathName = _GetFullPathName;
         theWindowsShell.m_pfnGetVolumeInformation = _GetVolumeInformation;
         theWindowsShell.m_pfnSHGetFileInfo = _SHGetFileInfo;
         theWindowsShell.m_pfnGetStringTypeEx = _GetStringTypeEx;
         theWindowsShell.m_pfnGetTempPath = _GetTempPath;
         theWindowsShell.m_pfnGetTempFileName = _GetTempFileName;
         theWindowsShell.m_pfnCreateFile = _CreateFile;
         theWindowsShell.m_pfnGetModuleFileName = _GetModuleFileName;
         theWindowsShell.m_pfnGetClassInfo = _GetClassInfo;
         theWindowsShell.m_pfnRegisterClass = _RegisterClass;
         theWindowsShell.m_pfnCreateWindowEx = _CreateWindowEx;
      }*/

   //return true;
   //}

///*   BOOL shell::_SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
//   {
//      char pszPathA[MAX_PATH * 2];
//      if(!::SHGetPathFromIDListA(pidl, pszPathA))
//         return false;
//      return ACPToUnicode(scopedstrPath, MAX_PATH * 2, pszPathA) ? true : false;
//   }*/
//
///*   BOOL shell::_MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
//   {
//      string str1, str2;
//      UnicodeToACP(str1, lpExistingFileName);
//      UnicodeToACP(str2, lpNewFileName);
//      return ::MoveFileA(str1, str2);
//   }
//
//   HANDLE shell::_FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata)
//   {
//      char pszPathA[MAX_PATH * 2];
//      UnicodeToACP(scopedstrPathA, MAX_PATH * 2, pcsz);
//      WIN32_FIND_DATAA data;
//      HANDLE handle = ::FindFirstFileA(scopedstrPathA, &data);
//      if(handle == INVALID_HANDLE_VALUE)
//         return INVALID_HANDLE_VALUE;
//
//      lpdata->dwFileAttributes = data.dwFileAttributes;
//      lpdata->ftCreationTime = data.ftCreationTime;
//      lpdata->ftLastAccessTime = data.ftLastAccessTime;
//      lpdata->ftLastWriteTime = data.ftLastWriteTime;
//      lpdata->nFileSizeHigh = data.nFileSizeHigh;
//      lpdata->nFileSizeLow = data.nFileSizeLow;
//      lpdata->dwReserved0 = data.dwReserved0;
//      lpdata->dwReserved1 = data.dwReserved1;
//      ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
//      ACPToUnicode(lpdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);
//
//      return handle;
//   }
//
//
//   BOOL shell::_FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
//   {
//      WIN32_FIND_DATAA data;
//      bool b = ::FindNextFileA(handle, &data) != false;
//      if(b == false)
//         return false;
//
//      lpdata->dwFileAttributes = data.dwFileAttributes;
//      lpdata->ftCreationTime = data.ftCreationTime;
//      lpdata->ftLastAccessTime = data.ftLastAccessTime;
//      lpdata->ftLastWriteTime = data.ftLastWriteTime;
//      lpdata->nFileSizeHigh = data.nFileSizeHigh;
//      lpdata->nFileSizeLow = data.nFileSizeLow;
//      lpdata->dwReserved0 = data.dwReserved0;
//      lpdata->dwReserved1 = data.dwReserved1;
//      ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
//      ACPToUnicode(lpdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);
//
//      return b;
//   }
//
//
//   WCHAR * __cdecl shell::__fullpath (
//      WCHAR *UserBuf,
//      const WCHAR *path,
//      size_t maxlen
//      )
//   {
//      WCHAR *buf;
//      WCHAR *pfname;
//      unsigned long count;
//
//
//      if ( !path || !*path )  /* no work to do */
//         return( _wgetcwd( UserBuf, (int) maxlen ) );
//
//      /* allocate buffer if necessary */
//
//      if ( !UserBuf )
//         if ( !(buf = (WCHAR *) malloc(_MAX_PATH * sizeof(WCHAR))) ) {
//            //                errno = ENOMEM;
//            return( nullptr );
//         }
//         else
//            maxlen = _MAX_PATH;
//      else
//         buf = UserBuf;
//
//      count = GetFullPathName ( path,
//         (int) maxlen,
//         buf,
//         &pfname );
//
//      if ( count >= maxlen ) {
//         if ( !UserBuf )
//            free(buf);
//         //errno = ERANGE;
//         return( nullptr );
//      }
//      else if ( count == 0 ) {
//         if ( !UserBuf )
//            free(buf);
//         //_dosmaperr( get_last_error() );
//         return( nullptr );
//      }
//
//      return( buf );
//
//   }
//
//
//   unsigned int WINAPI shell::_GetFullPathName(
//      const unichar * lpFileName,
//      unsigned int nBufferLength,
//      unichar * lpBuffer,
//      unichar ** lpFilePart)
//   {
//      char pszPathA[MAX_PATH * 2];
//      UnicodeToACP(scopedstrPathA, MAX_PATH * 2, lpFileName);
//      string str;
//      char * lpsz = str.GetBuffer(nBufferLength * 2);
//      char * lpszFilePart;
//      unsigned int dw = ::GetFullPathName(scopedstrPathA, nBufferLength, lpsz, &lpszFilePart);
//      str.ReleaseBuffer();
//      ACPToUnicode(lpBuffer, nBufferLength, str);
//      *lpFilePart = lpBuffer + ((int) (lpszFilePart - lpsz));
//      return dw;
//   }
//
//   BOOL WINAPI shell::_GetVolumeInformation(
//      const unichar * lpRootPathName,           // root directory
//      unichar * lpVolumeNameBuffer,        // volume name buffer
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD lpVolumeSerialNumber,     // volume serial number
//      LPDWORD lpMaximumComponentLength, // maximum file name length
//      LPDWORD lpFileSystemFlags,        // file system options
//      unichar * lpFileSystemNameBuffer,    // file system name buffer
//      unsigned int nFileSystemNameSize)         // length of file system name buffer
//   {
//      string strRootPathName;
//      string strVolumeNameBuffer;
//      string strFileSystemNameBuffer;
//      UnicodeToACP(strRootPathName, lpRootPathName);
//      bool b = ::GetVolumeInformation(
//         strRootPathName,
//         strVolumeNameBuffer.GetBuffer(nVolumeNameSize),
//         nVolumeNameSize,
//         lpVolumeSerialNumber,
//         lpMaximumComponentLength,
//         lpFileSystemFlags,
//         strFileSystemNameBuffer.GetBuffer(nFileSystemNameSize),
//         nFileSystemNameSize) != false;
//
//      strVolumeNameBuffer.ReleaseBuffer();
//      strFileSystemNameBuffer.ReleaseBuffer();
//      ACPToUnicode(
//         lpVolumeNameBuffer,
//         nVolumeNameSize,
//         strVolumeNameBuffer);
//      ACPToUnicode(
//         lpFileSystemNameBuffer,
//         nFileSystemNameSize,
//         strFileSystemNameBuffer);
//      return b;
//   }
//
//   dword_ptr shell::_SHGetFileInfo(
//      const unichar * pszPath,
//      unsigned int dwFileAttributes,
//      SHFILEINFOW *psfi,
//      unsigned int cbFileInfo,
//      unsigned int uFlags)
//   {
//      __UNREFERENCED_PARAMETER(cbFileInfo);
//      string strPath;
//      UnicodeToACP(strPath, pszPath);
//      SHFILEINFOA shia;
//      if(!::SHGetFileInfoA(strPath, dwFileAttributes,
//         &shia,
//         sizeof(shia),
//         uFlags))
//         return false;
//      ACPToUnicode(
//         psfi->szDisplayName,
//         sizeof(psfi->szDisplayName) / sizeof(WCHAR),
//         shia.szDisplayName);
//      ACPToUnicode(
//         psfi->szTypeName,
//         sizeof(psfi->szTypeName) / sizeof(WCHAR),
//         shia.szTypeName);
//      return true;
//   }
//
//
//   BOOL shell::_GetStringTypeEx(
//      LCID uCodePage,
//      unsigned int dwInfoType,
//      const unichar * lpSrcStr,
//      int cchSrc,
//      LPWORD lpCharType)
//   {
//      character_count iCount = cchSrc;
//      if(iCount < 0)
//         iCount = unicode_to_multibyte_count(uCodePage, lpSrcStr);
//      string str;
//      char * lpsz = str.GetBuffer(iCount);
//      if(unicode_to_multibyte(uCodePage, lpsz, iCount, lpSrcStr))
//      {
//         //str.ReleaseBuffer();
//         //return true;
//      }
//      else
//      {
//         return false;
//      }
//      if(!GetStringTypeA(uCodePage, dwInfoType, lpsz, (int) iCount, lpCharType))
//      {
//         return false;
//      }
//      return true;
//   }
//
//
//   unsigned int shell::_GetTempPath(
//      unsigned int nBufferLength,
//      unichar * lpBuffer)
//   {
//      string str;
//      unsigned int dw = ::GetTempPathA(nBufferLength, str.GetBuffer(nBufferLength * 2));
//      str.ReleaseBuffer();
//      ACPToUnicode(lpBuffer, nBufferLength, str);
//      return dw;
//   }
//
//   unsigned int shell::_GetTempFileName(
//      const unichar * lpPathName,
//      const unichar * lpPrefixString,
//      unsigned int uUnique,
//      unichar * lpTempFileName)
//   {
//      string strPathName;
//      string strPrefixString;
//      string strTempFileName;
//      UnicodeToACP(strPathName, lpPathName);
//      UnicodeToACP(strPrefixString, lpPrefixString);
//      unsigned int user = ::GetTempFileNameA(
//         strPathName,
//         strPrefixString,
//         uUnique,
//         strTempFileName.GetBuffer(MAX_PATH));
//      if(user == 0)
//      {
//         return 0;
//      }
//      strTempFileName.ReleaseBuffer();
//      ACPToUnicode(
//         lpTempFileName,
//         MAX_PATH,
//         strTempFileName);
//      return user;
//   }
//
//
//   HANDLE shell::_CreateFile(
//      const unichar * lpFileName,
//      unsigned int dwDesiredAccess,
//      unsigned int dwShareMode,
//      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//      unsigned int dwCreationDisposition,
//      unsigned int dwFlagsAndAttributes,
//      HANDLE hTemplateFile
//      )
//   {
//      string strFileName;
//      UnicodeToACP(strFileName, lpFileName);
//      HANDLE handle = ::CreateFileA(
//         strFileName,
//         dwDesiredAccess,
//         dwShareMode,
//         lpSecurityAttributes,
//         dwCreationDisposition,
//         dwFlagsAndAttributes,
//         hTemplateFile);
//      return handle;
//   }
//
//
//   unsigned int shell::_GetModuleFileName(
//      HMODULE hModule,
//      unichar * lpFilename,
//      unsigned int nSize
//      )
//   {
//      string str;
//      unsigned int dw = ::GetModuleFileNameA(hModule, str.GetBuffer(nSize * 2), nSize * 2);
//      str.ReleaseBuffer();
//      ACPToUnicode(lpFilename, nSize, str);
//      return dw;
//   }
//
//   BOOL shell::_GetClassInfo(HINSTANCE hInstance , const unichar * lpClassName, LPWNDCLASSW lpWndClass)
//   {
//      WNDCLASS wndclass;
//
//      string strClassName;
//      const_char_pointer lpszClassName;
//      if(((unsigned int) lpClassName) >> 16 == 0)
//      {
//         lpszClassName = (const_char_pointer )lpClassName;
//      }
//      else
//      {
//         strClassName = lpClassName;
//         lpszClassName = strClassName;
//      }
//      if(!::GetClassInfoA(hInstance, lpszClassName, &wndclass))
//         return false;
//
//      lpWndClass->style = wndclass.style;
//      lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
//      lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
//      lpWndClass->cbClsExtra = wndclass.cbClsExtra;
//      lpWndClass->cbWndExtra = wndclass.cbWndExtra;
//      lpWndClass->hInstance = wndclass.hInstance;
//      lpWndClass->hIcon = wndclass.hIcon;
//      lpWndClass->hCursor = wndclass.hCursor;
//      lpWndClass->hbrBackground = wndclass.hbrBackground;
//
//      /*   if(((unsigned int) wndclass) >> 16 == 0)
//      {
//      lpszClassName = (const_char_pointer )lpClassName;
//      }
//      else
//      {
//      strClassName = lpClassName;
//      lpszClassName = strClassName
//      }
//      string strMenuName;*/
//      //strMenuName = wndclass->lpszMenuName;
//      lpWndClass->lpszMenuName = (const unichar *) wndclass.lpszMenuName;
//
//      lpWndClass->lpszClassName = (const unichar *) wndclass.lpszClassName;
//
//      return true;
//
//   }
//   ATOM shell::_RegisterClass(
//      const WNDCLASSW *lpWndClass)
//   {
//      WNDCLASS wndclass;
//
//      wndclass.style = lpWndClass->style;
//      wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
//      wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
//      wndclass.cbClsExtra = lpWndClass->cbClsExtra;
//      wndclass.cbWndExtra = lpWndClass->cbWndExtra;
//      wndclass.hInstance = lpWndClass->hInstance;
//      wndclass.hIcon = lpWndClass->hIcon;
//      wndclass.hCursor = lpWndClass->hCursor;
//      wndclass.hbrBackground = lpWndClass->hbrBackground;
//
//      string strMenuName;
//      strMenuName = lpWndClass->lpszMenuName;
//      wndclass.lpszMenuName = strMenuName;
//
//      string strClassName;
//      strClassName = lpWndClass->lpszClassName;
//      wndclass.lpszClassName = strClassName;
//
//      return ::RegisterClassA(&wndclass);
//   }
//
//
//   oswindow shell::_CreateWindowEx(
//      unsigned int dwExStyle,
//      const unichar * lpClassName,
//      const unichar * lpWindowName,
//      unsigned int uStyle,
//      int x,
//      int y,
//      int nWidth,
//      int nHeight,
//      oswindow hWndParent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID lpParam)
//   {
//      string strClassName;
//      const_char_pointer lpszClassName;
//      if(((unsigned int) lpClassName) >> 16 == 0)
//      {
//         lpszClassName = (const_char_pointer )lpClassName;
//      }
//      else
//      {
//         strClassName = lpClassName;
//         lpszClassName = strClassName;
//      }
//
//      string strWindowName;
//      strWindowName = lpWindowName;
//
//      return ::CreateWindowExA(
//         dwExStyle,
//         lpszClassName,
//         strWindowName,
//         uStyle,
//         x,
//         y,
//         nWidth,
//         nHeight,
//         hWndParent,
//         hMenu,
//         hInstance,
//         lpParam);
//
//   }
//
//
//
} // namespace universal_windows



