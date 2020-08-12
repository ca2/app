#include "framework.h"
//#include "aura/node/ansios/ansios.h"
#include "_linux.h"

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


//WCHAR * __cdecl _wgetdcwd (
//        i32 drive,
//        WCHAR *pnbuf,
//        i32 maxlen
//        )
//{
//        WCHAR *point;
//        WCHAR dirbuf[_MAX_PATH];
//        WCHAR drvstr[4];
//        i32 len;
//        WCHAR *pname; only used as argument to GetFullPathName
//
//
// GetCurrentDirectory only works for the default drive in Win32
//
//      if ( drive != 0 ) {
//
//           Not the default drive - make sure it's valid.
//
//        if ( !_validdrive(drive) ) {
//            _doserrno = ERROR_INVALID_DRIVE;
////                errno = EACCES;
//            return nullptr;
//        }
//
//                 get the current directory string on that drive and its length
//
//      drvstr[0] = (char) ('A' - 1 + drive);
//      drvstr[1] = ':';
//      drvstr[2] = '.';
//      drvstr[3] = '\0';
//      len = shell::GetFullPathName( drvstr,
//                             sizeof(dirbuf) / sizeof(_TSCHAR),
//                             dirbuf,
//                             &pname );
//
//  } else {
//
//
//        get the current directory string and its length
//
//            len = GetCurrentDirectory( sizeof(dirbuf) / sizeof(_TSCHAR),
//                                       (LPTSTR)dirbuf );
//        }
//
//         API call failed, or buffer not large enough
//      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
//          return nullptr;
//
//             Set up the buffer.
//
//    if ( (point = pnbuf) == nullptr ) {
//
//         allocate a buffer for the ::account::user.
//
//      if ( (point = (WCHAR *)malloc(__max(len, maxlen) * sizeof(WCHAR)))
//           == nullptr )
//      {
////                errno = ENOMEM;
//          return nullptr;
//      }
//  }
//  else if ( len > maxlen ) {
//
//       Won't fit in the ::account::user-supplied buffer!
//
////            errno = ERANGE;  Won't fit in ::account::user buffer
//    return nullptr;
//}
//
//
// Place the current directory string into the ::account::user buffer
//
//
//        return wcscpy(point, dirbuf);
//}

//#ifndef WPRFLAG
//
//
//i32 _validdrive( unsigned drive ) -
//
//Purpose: returns non zero if drive is a valid drive number.
//
//Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
//
//Exit:  0 => drive does not exist.
//
//Exceptions:
//


//i32 __cdecl _validdrive (
//    unsigned drive
//    )
//{
//        unsigned retcode;
//        char drvstr[4];
//
//        if ( drive == 0 )
//            return 1;
//
//        drvstr[0] = 'A' + drive - 1;
//        drvstr[1] = ':';
//        drvstr[2] = '\\';
//        drvstr[3] = '\0';
//
//        if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
//             (retcode == DRIVE_NO_ROOT_DIR) )
//            return 0;
//
//        return 1;
//}
//

//namespace linux
//{
//
//
//   shell shell::theLinuxShell;
//
////////////////////////////////////////////////////////////////////////
//// Construction/Destruction
////////////////////////////////////////////////////////////////////////
//
//   shell::shell()
//   {
//
//   }
//
//   shell::~shell()
//   {
//
//   }
//
//   bool shell::Initialize()
//   {
//      return true;
//   }
//
//
//} // namespace linux
//
//
//
//
//CLASS_DECL_CORE ::estatus os_shell_initialize()
//{
//
//   return ::linux::shell::theLinuxShell.Initialize();
//
//}


