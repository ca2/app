#include "framework.h"
#include "aura/node/windows/_windows.h"


/***
*i32 _validdrive( u32 drive ) -
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

i32 __cdecl _validdrive (
u32 drive
)
{
   u32 retcode;
   wchar_t drvstr[4];

   if ( drive == 0 )
      return 1;

   drvstr[0] = (char) ('A' + drive - 1);
   drvstr[1] = ':';
   drvstr[2] = '\\';
   drvstr[3] = '\0';

   if ( ((retcode = GetDriveTypeW( drvstr )) == DRIVE_UNKNOWN) ||
         (retcode == DRIVE_NO_ROOT_DIR) )
      return 0;

   return 1;
}

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
*       Returns pointer to the buffer containing the ca.w.d. name
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
*       i32 drive   - number of the drive being inquired about
*                     0 = default, 1 = 'a:', 2 = 'b:', etc.
*       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::account::user;
*       i32 maxlen  - length of the buffer pointed to by pnbuf;
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
i32 drive,
WCHAR *pnbuf,
i32 maxlen
)
{
WCHAR *point;
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
(LPTSTR)dirbuf );
}

/* API call failed, or buffer not large enough */
/*      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
return nullptr;

/*
* set up the buffer.
*/
/*    if ( (point = pnbuf) == nullptr ) {
/*
* allocate a buffer for the ::account::user.
*/
/*      if ( (point = (WCHAR *)malloc(__max(len, maxlen) * sizeof(WCHAR)))
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
return wcscpy(point, dirbuf);
}

/*#ifndef WPRFLAG

/***
*i32 _validdrive( u32 drive ) -
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
u32 drive
)
{
u32 retcode;
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

namespace windows
{

   shell shell::theWindowsShell;


   shell::shell()
   {

   }

   shell::~shell()
   {

   }

   bool shell::Initialize()
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
      return true;
   }

   /*   BOOL shell::_SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
      {
         CHAR pszPathA[MAX_PATH * 2];
         if(!::SHGetPathFromIDListA(pidl, pszPathA))
            return FALSE;
         return ::str::international::utf8_to_unicode(pszPath, MAX_PATH * 2, pszPathA) ? TRUE : FALSE;
      }

      BOOL shell::_MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)

      {
         string str1, str2;
         ::str::international::unicode_to_utf8(str1, pExistingFileName);

         ::str::international::unicode_to_utf8(str2, pNewFileName);

         return ::MoveFileA(str1, str2);
      }

      HANDLE shell::_FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata)

      {
         string
         ::str::international::unicode_to_utf8(pszPathA, MAX_PATH * 2, pcsz);

         WIN32_FIND_DATAA data;
         HANDLE handle = ::FindFirstFileA(pszPathA, &data);
         if(handle == INVALID_HANDLE_VALUE)
            return INVALID_HANDLE_VALUE;

         pdata->dwFileAttributes = data.dwFileAttributes;

         pdata->ftCreationTime = data.ftCreationTime;

         pdata->ftLastAccessTime = data.ftLastAccessTime;

         pdata->ftLastWriteTime = data.ftLastWriteTime;

         pdata->nFileSizeHigh = data.nFileSizeHigh;

         pdata->nFileSizeLow = data.nFileSizeLow;

         pdata->dwReserved0 = data.dwReserved0;

         pdata->dwReserved1 = data.dwReserved1;

         ::str::international::ACPToUnicode(pdata->cFileName, MAX_PATH, data.cFileName);

         ::str::international::ACPToUnicode(pdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);


         return handle;
      }


      BOOL shell::_FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)

      {
         WIN32_FIND_DATAA data;
         bool b = ::FindNextFileA(handle, &data) != FALSE;
         if(b == FALSE)
            return FALSE;

         pdata->dwFileAttributes = data.dwFileAttributes;

         pdata->ftCreationTime = data.ftCreationTime;

         pdata->ftLastAccessTime = data.ftLastAccessTime;

         pdata->ftLastWriteTime = data.ftLastWriteTime;

         pdata->nFileSizeHigh = data.nFileSizeHigh;

         pdata->nFileSizeLow = data.nFileSizeLow;

         pdata->dwReserved0 = data.dwReserved0;

         pdata->dwReserved1 = data.dwReserved1;

         ::str::international::ACPToUnicode(pdata->cFileName, MAX_PATH, data.cFileName);

         ::str::international::ACPToUnicode(pdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);


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
   /*         return( _wgetcwd( UserBuf, (i32) maxlen ) );

         /* allocate buffer if necessary */

   //   if ( !UserBuf )
   //      if ( !(buf = (WCHAR *) malloc(_MAX_PATH * sizeof(WCHAR))) ) {
   //         //                errno = ENOMEM;
   //         return( nullptr );
   //      }
   //      else
   //         maxlen = _MAX_PATH;
   //   else
   //      buf = UserBuf;

   //   count = GetFullPathName ( path,
   //      (i32) maxlen,
   //      buf,
   //      &pfname );

   //   if ( count >= maxlen ) {
   //      if ( !UserBuf )
   //         free(buf);
   //      //errno = ERANGE;
   //      return( nullptr );
   //   }
   //   else if ( count == 0 ) {
   //      if ( !UserBuf )
   //         free(buf);
   //      //_dosmaperr( get_last_error() );
   //      return( nullptr );
   //   }

   //   return( buf );

   //}


   //::u32 WINAPI shell::_GetFullPathName(
   //   const unichar * pFileName,

   //   ::u32 nBufferLength,
   //   unichar * pBuffer,

   //   unichar ** pFilePart)

   //{
   //   CHAR pszPathA[MAX_PATH * 2];
   //   ::str::international::UnicodeToACP(pszPathA, MAX_PATH * 2, pFileName);

   //   string str;
   //   LPTSTR psz = str.GetBuffer(nBufferLength * 2);

   //   LPTSTR pszFilePart;

   //   ::u32 dw = ::GetFullPathName(pszPathA, nBufferLength, psz, &pszFilePart);

   //   str.ReleaseBuffer();
   //   ::str::international::ACPToUnicode(pBuffer, nBufferLength, str);

   //   *pFilePart = lpBuffer + ((i32) (pszFilePart - psz));

   //   return dw;
   //}

   //BOOL WINAPI shell::_GetVolumeInformation(
   //   const unichar * pRootPathName,           // root directory

   //   unichar * pVolumeNameBuffer,        // volume name buffer

   //   ::u32 nVolumeNameSize,            // length of name buffer
   //   LPDWORD pVolumeSerialNumber,     // volume serial number

   //   LPDWORD pMaximumComponentLength, // maximum file name length

   //   LPDWORD pFileSystemFlags,        // file system options

   //   unichar * pFileSystemNameBuffer,    // file system name buffer

   //   ::u32 nFileSystemNameSize)         // length of file system name buffer
   //{
   //   string strRootPathName;
   //   string strVolumeNameBuffer;
   //   string strFileSystemNameBuffer;
   //   ::str::international::UnicodeToACP(strRootPathName, pRootPathName);

   //   bool b = ::GetVolumeInformation(
   //      strRootPathName,
   //      strVolumeNameBuffer.GetBuffer(nVolumeNameSize),
   //      nVolumeNameSize,
   //      pVolumeSerialNumber,

   //      pMaximumComponentLength,

   //      pFileSystemFlags,

   //      strFileSystemNameBuffer.GetBuffer(nFileSystemNameSize),
   //      nFileSystemNameSize) != FALSE;

   //   strVolumeNameBuffer.ReleaseBuffer();
   //   strFileSystemNameBuffer.ReleaseBuffer();
   //   ::str::international::ACPToUnicode(
   //      pVolumeNameBuffer,

   //      nVolumeNameSize,
   //      strVolumeNameBuffer);
   //   ::str::international::ACPToUnicode(
   //      pFileSystemNameBuffer,

   //      nFileSystemNameSize,
   //      strFileSystemNameBuffer);
   //   return b;
   //}

   //uptr shell::_SHGetFileInfo(
   //   const unichar * pszPath,
   //   ::u32 dwFileAttributes,
   //   SHFILEINFOW *psfi,
   //   ::u32 cbFileInfo,
   //   ::u32 uFlags)
   //{
   //   UNREFERENCED_PARAMETER(cbFileInfo);
   //   string strPath;
   //   ::str::international::UnicodeToACP(strPath, pszPath);
   //   SHFILEINFOA shia;
   //   if(!::SHGetFileInfoA(strPath, dwFileAttributes,
   //      &shia,
   //      sizeof(shia),
   //      uFlags))
   //      return FALSE;
   //   ::str::international::ACPToUnicode(
   //      psfi->szDisplayName,
   //      sizeof(psfi->szDisplayName) / sizeof(WCHAR),
   //      shia.szDisplayName);
   //   ::str::international::ACPToUnicode(
   //      psfi->szTypeName,
   //      sizeof(psfi->szTypeName) / sizeof(WCHAR),
   //      shia.szTypeName);
   //   return TRUE;
   //}


   //BOOL shell::_GetStringTypeEx(
   //   LCID uCodePage,
   //   ::u32 dwInfoType,
   //   const unichar * pSrcStr,

   //   i32 cchSrc,
   //   LPWORD pCharType)

   //{
   //   strsize iCount = cchSrc;
   //   if(iCount < 0)
   //      iCount = ::str::international::UnicodeToMultiByteCount(uCodePage, pSrcStr);

   //   string str;
   //   LPTSTR psz = str.GetBuffer(iCount);

   //   if(::str::international::UnicodeToMultiByte(uCodePage, psz, iCount, lpSrcStr))

   //   {
   //      //str.ReleaseBuffer();
   //      //return true;
   //   }
   //   else
   //   {
   //      return false;
   //   }
   //   if(!GetStringTypeA(uCodePage, dwInfoType, psz, (i32) iCount, lpCharType))

   //   {
   //      return FALSE;
   //   }
   //   return TRUE;
   //}


   //::u32 shell::_GetTempPath(
   //   ::u32 nBufferLength,
   //   unichar * pBuffer)

   //{
   //   string str;
   //   ::u32 dw = ::GetTempPathA(nBufferLength, str.GetBuffer(nBufferLength * 2));
   //   str.ReleaseBuffer();
   //   ::str::international::ACPToUnicode(pBuffer, nBufferLength, str);

   //   return dw;
   //}

   //::u32 shell::_GetTempFileName(
   //   const unichar * pszPath,

   //   const unichar * pszPrefix,

   //   ::u32 uUnique,
   //   unichar * pTempFileName)

   //{
   //   string strPathName;
   //   string strPrefixString;
   //   string strTempFileName;
   //   ::str::international::UnicodeToACP(strPathName, pszPath);

   //   ::str::international::UnicodeToACP(strPrefixString, pszPrefix);

   //   ::u32 user = ::GetTempFileNameA(
   //      strPathName,
   //      strPrefixString,
   //      uUnique,
   //      strTempFileName.GetBuffer(MAX_PATH));
   //   if(user == 0)
   //   {
   //      return 0;
   //   }
   //   strTempFileName.ReleaseBuffer();
   //   ::str::international::ACPToUnicode(
   //      pTempFileName,

   //      MAX_PATH,
   //      strTempFileName);
   //   return user;
   //}


   //HANDLE shell::_CreateFile(
   //   const unichar * pFileName,

   //   ::u32 dwDesiredAccess,
   //   ::u32 dwShareMode,
   //   LPSECURITY_ATTRIBUTES pSecurityAttributes,

   //   ::u32 dwCreationDisposition,
   //   ::u32 dwFlagsAndAttributes,
   //   HANDLE hTemplateFile
   //   )
   //{
   //   string strFileName;
   //   ::str::international::UnicodeToACP(strFileName, pFileName);

   //   HANDLE handle = ::CreateFileA(
   //      strFileName,
   //      dwDesiredAccess,
   //      dwShareMode,
   //      pSecurityAttributes,

   //      dwCreationDisposition,
   //      dwFlagsAndAttributes,
   //      hTemplateFile);
   //   return handle;
   //}


   //::u32 shell::_GetModuleFileName(
   //   HMODULE hModule,
   //   unichar * pFilename,

   //   ::u32 nSize
   //   )
   //{
   //   string str;
   //   ::u32 dw = ::GetModuleFileNameA(hModule, str.GetBuffer(nSize * 2), nSize * 2);
   //   str.ReleaseBuffer();
   //   ::str::international::ACPToUnicode(pFilename, nSize, str);

   //   return dw;
   //}

   //BOOL shell::_GetClassInfo(HINSTANCE hInstance , const unichar * pClassName, LPWNDCLASSW pwndclass)

   //{
   //   WNDCLASS wndclass;

   //   string strClassName;
   //   const char * pszClassName;

   //   if(((::u32) pClassName) >> 16 == 0)

   //   {
   //      pszClassName = (const char *) lpClassName;

   //   }
   //   else
   //   {
   //      strClassName = pClassName;

   //      pszClassName = strClassName;

   //   }
   //   if(!::GetClassInfoA(hInstance, pszClassName, &wndclass))

   //      return FALSE;

   //   pwndclass->style = wndclass.style;

   //   pwndclass->lpfnWndProc = wndclass.lpfnWndProc;

   //   pwndclass->lpfnWndProc = wndclass.lpfnWndProc;

   //   pwndclass->cbClsExtra = wndclass.cbClsExtra;

   //   pwndclass->cbWndExtra = wndclass.cbWndExtra;

   //   pwndclass->hInstance = wndclass.hInstance;

   //   pwndclass->hIcon = wndclass.hIcon;

   //   pwndclass->hCursor = wndclass.hCursor;

   //   pwndclass->hbrBackground = wndclass.hbrBackground;


   //   /*   if(((::u32) wndclass) >> 16 == 0)
   //   {
   //   pszClassName = (const char *) lpClassName;

   //   }
   //   else
   //   {
   //   strClassName = pClassName;

   //   pszClassName = strClassName

   //   }
   //   string strMenuName;*/
   //   //strMenuName = wndclass->pszMenuName;

   //   pwndclass->pszMenuName = (const unichar *) wndclass.pszMenuName;


   //   pwndclass->pszClassName = (const unichar *) wndclass.pszClassName;


   //   return TRUE;

   //}
   //ATOM shell::_RegisterClass(
   //   CONST WNDCLASSW *pwndclass)

   //{
   //   WNDCLASS wndclass;

   //   wndclass.style = pwndclass->style;

   //   wndclass.pfnWndProc = pwndclass->lpfnWndProc;

   //   wndclass.pfnWndProc = pwndclass->lpfnWndProc;

   //   wndclass.cbClsExtra = pwndclass->cbClsExtra;

   //   wndclass.cbWndExtra = pwndclass->cbWndExtra;

   //   wndclass.hInstance = pwndclass->hInstance;

   //   wndclass.hIcon = pwndclass->hIcon;

   //   wndclass.hCursor = pwndclass->hCursor;

   //   wndclass.hbrBackground = pwndclass->hbrBackground;


   //   string strMenuName;
   //   strMenuName = pwndclass->pszMenuName;

   //   wndclass.pszMenuName = strMenuName;


   //   string strClassName;
   //   strClassName = pwndclass->pszClassName;

   //   wndclass.pszClassName = strClassName;


   //   return ::RegisterClassA(&wndclass);
   //}


   //oswindow shell::_CreateWindowEx(
   //   ::u32 dwExStyle,
   //   const unichar * pClassName,

   //   const unichar * pWindowName,

   //   ::u32 dwStyle,
   //   i32 x,
   //   i32 y,
   //   i32 nWidth,
   //   i32 nHeight,
   //   oswindow oswindow_Parent,
   //   HMENU hMenu,
   //   HINSTANCE hInstance,
   //   LPVOID pParam)

   //{
   //   string strClassName;
   //   const char * pszClassName;

   //   if(((::u32) pClassName) >> 16 == 0)

   //   {
   //      pszClassName = (const char *) lpClassName;

   //   }
   //   else
   //   {
   //      strClassName = pClassName;

   //      pszClassName = strClassName;

   //   }

   //   string strWindowName;
   //   strWindowName = pWindowName;


   //   return ::CreateWindowExA(
   //      dwExStyle,
   //      pszClassName,

   //      strWindowName,
   //      dwStyle,
   //      x,
   //      y,
   //      nWidth,
   //      nHeight,
   //      oswindow_Parent,
   //      hMenu,
   //      hInstance,
   //      pParam);


   //}
   //*/

} // namespace windows


