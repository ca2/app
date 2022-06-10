#include "framework.h"
//#include "android.h"

/***
*i32 _validdrive( unsigned drive ) -
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
/*
i32 __cdecl _validdrive (
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
}*/

/*WCHAR * __cdecl _wgetdcwd (
        i32 drive,
        WCHAR *pnbuf,
        i32 maxlen
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
*       An entry point "_getdcwd()" is defined with takes the above
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
*       i32 maxlen = length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the c.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/

/*WCHAR * __cdecl _wgetcwd (
        WCHAR *pnbuf,
        i32 maxlen
        )
{
        WCHAR *retval;


        retval = _wgetdcwd(0, pnbuf, maxlen);

        return retval;
}*/


/***
*_TSCHAR *_getdcwd(drive, pnbuf, maxlen) - get c.w.d. for given drive
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
*       i32 drive   - number of the drive being inquired about
*                     0 = default, 1 = 'a:', 2 = 'b:', etc.
*       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::account::user;
*       i32 maxlen  - length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the c.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/


/*WCHAR * __cdecl _wgetdcwd (
        i32 drive,
        WCHAR *pnbuf,
        i32 maxlen
        )
{
        WCHAR *p;
        WCHAR dirbuf[_MAX_PATH];
        WCHAR drvstr[4];
        i32 len;
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
*i32 _validdrive( unsigned drive ) -
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

/*i32 __cdecl _validdrive (
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

namespace android
{


   shell shell::theLinuxShell;

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
      ::u32 dwVersion = GetVersion();

      // get the Windows version.

      ::u32 dwWindowsMajorVersion =  (::u32)(__LOBYTE(LOWORD(dwVersion)));
      //   ::u32 dwWindowsMinorVersion =  (::u32)(HIBYTE(LOWORD(dwVersion)));

      // get the build number.

      ::u32 dwBuild;

      if (dwVersion < 0x80000000)              // Windows NT
          dwBuild = (::u32)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
          dwBuild = (::u32)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
          dwBuild =  0;

      int_bool bNativeUnicode;
      if (dwVersion < 0x80000000)              // Windows NT
          bNativeUnicode = true;
      else if (dwWindowsMajorVersion < 4)      // Win32s
          bNativeUnicode = false;
      else                                     // Windows Me/98/95
          bNativeUnicode = false;


      if(bNativeUnicode)
      {
         theLinuxShell.m_pfnSHGetPathFromIDList = ::SHGetPathFromIDListW;
         theLinuxShell.m_pfnFindFirstFile = ::FindFirstFileW;
         theLinuxShell.m_pfnFindNextFile = ::FindNextFileW;
         theLinuxShell.m_pfnMoveFile = ::MoveFileW;
         theLinuxShell.m_pfn_fullpath = ::_wfullpath;
         theLinuxShell.m_pfnGetFullPathName = ::GetFullPathNameW;
         theLinuxShell.m_pfnGetVolumeInformation = ::GetVolumeInformationW;
         theLinuxShell.m_pfnSHGetFileInfo = ::SHGetFileInfoW;
         theLinuxShell.m_pfnGetStringTypeEx = ::GetStringTypeExW;
         theLinuxShell.m_pfnGetTempPath = ::GetTempPathW;
         theLinuxShell.m_pfnGetTempFileName = ::GetTempFileNameW;
         theLinuxShell.m_pfnCreateFile = ::CreateFileW;
         theLinuxShell.m_pfnGetModuleFileName = ::GetModuleFileNameW;
         theLinuxShell.m_pfnGetClassInfo = ::GetClassInfoW;
         theLinuxShell.m_pfnRegisterClass = ::RegisterClassW;
         theLinuxShell.m_pfnCreateWindowEx = ::CreateWindowExW;
      }
      else
      {
         theLinuxShell.m_pfnSHGetPathFromIDList = _SHGetPathFromIDList;
         theLinuxShell.m_pfnFindFirstFile = _FindFirstFile;
         theLinuxShell.m_pfnFindNextFile = _FindNextFile;
         theLinuxShell.m_pfnMoveFile = _MoveFile;
         theLinuxShell.m_pfn_fullpath = __fullpath;
         theLinuxShell.m_pfnGetFullPathName = _GetFullPathName;
         theLinuxShell.m_pfnGetVolumeInformation = _GetVolumeInformation;
         theLinuxShell.m_pfnSHGetFileInfo = _SHGetFileInfo;
         theLinuxShell.m_pfnGetStringTypeEx = _GetStringTypeEx;
         theLinuxShell.m_pfnGetTempPath = _GetTempPath;
         theLinuxShell.m_pfnGetTempFileName = _GetTempFileName;
         theLinuxShell.m_pfnCreateFile = _CreateFile;
         theLinuxShell.m_pfnGetModuleFileName = _GetModuleFileName;
         theLinuxShell.m_pfnGetClassInfo = _GetClassInfo;
         theLinuxShell.m_pfnRegisterClass = _RegisterClass;
         theLinuxShell.m_pfnCreateWindowEx = _CreateWindowEx;
      }
      */
      return true;
   }

   /*
   int_bool shell::_SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
   {
      char pszPathA[MAX_PATH * 2];
      if(!::SHGetPathFromIDListA(pidl, pszPathA))
         return false;
      return ACPToUnicode(pszPath, MAX_PATH * 2, pszPathA) ? true : false;
   }

   int_bool shell::_MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
   {
      string str1, str2;
      UnicodeToACP(str1, lpExistingFileName);
      UnicodeToACP(str2, lpNewFileName);
      return ::MoveFileA(str1, str2);
   }

   HANDLE shell::_FindFirstFile(const unichar * lpcsz, WIN32_FIND_DATAW * lpdata)
   {
      char pszPathA[MAX_PATH * 2];
      UnicodeToACP(pszPathA, MAX_PATH * 2, lpcsz);
      WIN32_FIND_DATAA data;
      HANDLE handle = ::FindFirstFileA(pszPathA, &data);
      if(handle == INVALID_HANDLE_VALUE)
         return INVALID_HANDLE_VALUE;

      lpdata->dwFileAttributes = data.dwFileAttributes;
      lpdata->ftCreationTime = data.ftCreationTime;
      lpdata->ftLastAccessTime = data.ftLastAccessTime;
      lpdata->ftLastWriteTime = data.ftLastWriteTime;
      lpdata->nFileSizeHigh = data.nFileSizeHigh;
      lpdata->nFileSizeLow = data.nFileSizeLow;
      lpdata->dwReserved0 = data.dwReserved0;
      lpdata->dwReserved1 = data.dwReserved1;
      ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
      ACPToUnicode(lpdata->calternateFileName, MAX_PATH, data.calternateFileName);

      return handle;
   }

   int_bool shell::_FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
   {
      WIN32_FIND_DATAA data;
      int_bool b = ::FindNextFileA(handle, &data);
      if(b == false)
         return false;

      lpdata->dwFileAttributes = data.dwFileAttributes;
      lpdata->ftCreationTime = data.ftCreationTime;
      lpdata->ftLastAccessTime = data.ftLastAccessTime;
      lpdata->ftLastWriteTime = data.ftLastWriteTime;
      lpdata->nFileSizeHigh = data.nFileSizeHigh;
      lpdata->nFileSizeLow = data.nFileSizeLow;
      lpdata->dwReserved0 = data.dwReserved0;
      lpdata->dwReserved1 = data.dwReserved1;
      ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
      ACPToUnicode(lpdata->calternateFileName, MAX_PATH, data.calternateFileName);

      return b;
   }


   WCHAR * __cdecl shell::__fullpath (
           WCHAR *UserBuf,
           const WCHAR *path,
           size_t maxlen
           )
   {
           WCHAR *buf;
           WCHAR *pfname;
           unsigned long count;


           if ( !path || !*path )  /* no work to do */
   /*          return( _wgetcwd( UserBuf, maxlen ) );

         /* allocate buffer if necessary */

   /*    if ( !UserBuf )
           if ( !(buf = (WCHAR *) malloc(_MAX_PATH * sizeof(WCHAR))) ) {
   //                errno = ENOMEM;
               return( nullptr );
           }
           else
               maxlen = _MAX_PATH;
       else
           buf = UserBuf;

       count = GetFullPathName ( path,
                                 maxlen,
                                 buf,
                                 &pfname );

       if ( count >= maxlen ) {
           if ( !UserBuf )
               free(buf);
           //errno = ERANGE;
           return( nullptr );
       }
       else if ( count == 0 ) {
           if ( !UserBuf )
               free(buf);
           //_dosmaperr( get_last_error() );
           return( nullptr );
       }

       return( buf );

   }


   ::u32 WINAPI shell::_GetFullPathName(
   const unichar * lpFileName,
   ::u32 nBufferLength,
   unichar * lpBuffer,
   unichar ** lpFilePart)
   {
   char pszPathA[MAX_PATH * 2];
   UnicodeToACP(pszPathA, MAX_PATH * 2, lpFileName);
   string str;
   char * lpsz = str.GetBuffer(nBufferLength * 2);
   char * lpszFilePart;
   ::u32 dw = ::GetFullPathName(pszPathA, nBufferLength, lpsz, &lpszFilePart);
   str.ReleaseBuffer();
   ACPToUnicode(lpBuffer, nBufferLength, str);
   *lpFilePart = lpBuffer + ((i32) (lpszFilePart - lpsz));
   return dw;
   }

   int_bool WINAPI shell::_GetVolumeInformation(
     const unichar * lpRootPathName,           // root directory
     unichar * lpVolumeNameBuffer,        // volume name buffer
     ::u32 nVolumeNameSize,            // length of name buffer
     LPDWORD lpVolumeSerialNumber,     // volume serial number
     LPDWORD lpMaximumComponentLength, // maximum file name length
     LPDWORD lpFileSystemFlags,        // file system options
     unichar * lpFileSystemNameBuffer,    // file system name buffer
     ::u32 nFileSystemNameSize)         // length of file system name buffer
   {
   string strRootPathName;
   string strVolumeNameBuffer;
   string strFileSystemNameBuffer;
   UnicodeToACP(strRootPathName, lpRootPathName);
   int_bool b = ::GetVolumeInformation(
     strRootPathName,
     strVolumeNameBuffer.GetBuffer(nVolumeNameSize),
     nVolumeNameSize,
     lpVolumeSerialNumber,
     lpMaximumComponentLength,
     lpFileSystemFlags,
     strFileSystemNameBuffer.GetBuffer(nFileSystemNameSize),
     nFileSystemNameSize);

   strVolumeNameBuffer.ReleaseBuffer();
   strFileSystemNameBuffer.ReleaseBuffer();
   ACPToUnicode(
     lpVolumeNameBuffer,
     nVolumeNameSize,
     strVolumeNameBuffer);
   ACPToUnicode(
     lpFileSystemNameBuffer,
     nFileSystemNameSize,
     strFileSystemNameBuffer);
   return b;
   }

   DWORD_PTR shell::_SHGetFileInfo(
   const unichar * pszPath,
   ::u32 dwFileAttributes,
   SHFILEINFOW *psfi,
   ::u32 cbFileInfo,
   ::u32 uFlags)
   {
   __UNREFERENCED_PARAMETER(cbFileInfo);
   string strPath;
   UnicodeToACP(strPath, pszPath);
   SHFILEINFOA shia;
   if(!::SHGetFileInfoA(strPath, dwFileAttributes,
     &shia,
     sizeof(shia),
     uFlags))
     return false;
   ACPToUnicode(
     psfi->szDisplayName,
     sizeof(psfi->szDisplayName) / sizeof(WCHAR),
     shia.szDisplayName);
   ACPToUnicode(
     psfi->szTypeName,
     sizeof(psfi->szTypeName) / sizeof(WCHAR),
     shia.szTypeName);
   return true;
   }


   int_bool shell::_GetStringTypeEx(
   LCID uCodePage,
   ::u32 dwInfoType,
   const unichar * lpSrcStr,
   i32 cchSrc,
   LPWORD lpCharType)
   {
   i32 iCount = cchSrc;
   if(iCount < 0)
     iCount = unicode_to_multibyte_count(uCodePage, lpSrcStr);
   string str;
   char * lpsz = str.GetBuffer(iCount);
   if(unicode_to_multibyte(uCodePage, lpsz, iCount, lpSrcStr))
   {
     //str.ReleaseBuffer();
     //return true;
   }
   else
   {
     return false;
   }
   if(!GetStringTypeA(uCodePage, dwInfoType, lpsz, iCount, lpCharType))
   {
     return false;
   }
   return true;
   }


   ::u32 shell::_GetTempPath(
     ::u32 nBufferLength,
     unichar * lpBuffer)
   {
   string str;
   ::u32 dw = ::GetTempPathA(nBufferLength, str.GetBuffer(nBufferLength * 2));
   str.ReleaseBuffer();
   ACPToUnicode(lpBuffer, nBufferLength, str);
   return dw;
   }

   ::u32 shell::_GetTempFileName(
   const unichar * lpPathName,
   const unichar * lpPrefixString,
   ::u32 uUnique,
   unichar * lpTempFileName)
   {
   string strPathName;
   string strPrefixString;
   string strTempFileName;
   UnicodeToACP(strPathName, lpPathName);
   UnicodeToACP(strPrefixString, lpPrefixString);
   ::u32 user = ::GetTempFileNameA(
     strPathName,
     strPrefixString,
     uUnique,
     strTempFileName.GetBuffer(MAX_PATH));
   if(user == 0)
   {
     return 0;
   }
   strTempFileName.ReleaseBuffer();
   ACPToUnicode(
     lpTempFileName,
     MAX_PATH,
     strTempFileName);
   return user;
   }


   HANDLE shell::_CreateFile(
   const unichar * lpFileName,
   ::u32 dwDesiredAccess,
   ::u32 dwShareMode,
   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
   ::u32 dwCreationDisposition,
   ::u32 dwFlagsAndAttributes,
   HANDLE hTemplateFile
   )
   {
   string strFileName;
   UnicodeToACP(strFileName, lpFileName);
   HANDLE handle = ::CreateFileA(
     strFileName,
     dwDesiredAccess,
     dwShareMode,
     lpSecurityAttributes,
     dwCreationDisposition,
     dwFlagsAndAttributes,
     hTemplateFile);
   return handle;
   }


   ::u32 shell::_GetModuleFileName(
   HMODULE hModule,
   unichar * lpFilename,
   ::u32 nSize
   )
   {
   string str;
   ::u32 dw = ::GetModuleFileNameA(hModule, str.GetBuffer(nSize * 2), nSize * 2);
   str.ReleaseBuffer();
   ACPToUnicode(lpFilename, nSize, str);
   return dw;
   }

   int_bool shell::_GetClassInfo(
   HINSTANCE hInstance ,
   const unichar * lpClassName,
   LPWNDCLASSW lpWndClass)
   {
   WNDCLASS wndclass;

   string strClassName;
   const char * lpszClassName;
   if(((::u32) lpClassName) >> 16 == 0)
   {
     lpszClassName = (const char *) lpClassName;
   }
   else
   {
     strClassName = lpClassName;
     lpszClassName = strClassName;
   }
   if(!::GetClassInfoA(hInstance, lpszClassName, &wndclass))
     return false;

   lpWndClass->style = wndclass.style;
   lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
   lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
   lpWndClass->cbClsExtra = wndclass.cbClsExtra;
   lpWndClass->cbWndExtra = wndclass.cbWndExtra;
   lpWndClass->hInstance = wndclass.hInstance;
   lpWndClass->hIcon = wndclass.hIcon;
   lpWndClass->hCursor = wndclass.hCursor;
   lpWndClass->hbrBackground = wndclass.hbrBackground;

   /*   if(((::u32) wndclass) >> 16 == 0)
   {
     lpszClassName = (const char *) lpClassName;
   }
   else
   {
     strClassName = lpClassName;
     lpszClassName = strClassName
   }
   string strMenuName;*/
   //strMenuName = wndclass->lpszMenuName;
   /*   lpWndClass->lpszMenuName = (const unichar *) wndclass.lpszMenuName;

      lpWndClass->lpszClassName = (const unichar *) wndclass.lpszClassName;

      return true;

   }
   ATOM shell::_RegisterClass(
      const WNDCLASSW *lpWndClass)
   {
      WNDCLASS wndclass;

      wndclass.style = lpWndClass->style;
      wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
      wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
      wndclass.cbClsExtra = lpWndClass->cbClsExtra;
      wndclass.cbWndExtra = lpWndClass->cbWndExtra;
      wndclass.hInstance = lpWndClass->hInstance;
      wndclass.hIcon = lpWndClass->hIcon;
      wndclass.hCursor = lpWndClass->hCursor;
      wndclass.hbrBackground = lpWndClass->hbrBackground;

      string strMenuName;
      strMenuName = lpWndClass->lpszMenuName;
      wndclass.lpszMenuName = strMenuName;

      string strClassName;
      strClassName = lpWndClass->lpszClassName;
      wndclass.lpszClassName = strClassName;

      return ::RegisterClassA(&wndclass);
   }


   oswindow shell::_CreateWindowEx(
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
      string strClassName;
      const char * lpszClassName;
      if(((::u32) lpClassName) >> 16 == 0)
      {
         lpszClassName = (const char *) lpClassName;
      }
      else
      {
         strClassName = lpClassName;
         lpszClassName = strClassName;
      }

      string strWindowName;
      strWindowName = lpWindowName;

      return ::CreateWindowExA(
         dwExStyle,
         lpszClassName,
         strWindowName,
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
   */


} // namespace android








// CLASS_DECL_ACME void os_shell_initialize()
// {

//    return ::android::shell::theLinuxShell.Initialize();

// }
