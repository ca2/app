#include "framework.h"

#ifdef WINDOWS
//#include <Shellapi.h>
#endif

extern int g_iCallStackLevel;

#define DUMP_FILE_EXCEPTION_BACK_TRACE 0

/////////////////////////////////////////////////////////////////////////////
// file_exception helpers

namespace file
{

   static const char* rgszFileExceptionCause[] =
   {
      "genericFileError",
      "fileNotFound",
      "badPath",
      "tooManyOpenFiles",
      "accessDenied",
      "invalidFile",
      "removeCurrentDir",
      "directoryFull",
      "badSeek",
      "hardIO",
      "sharingViolation",
      "lockViolation",
      "diskFull",
      "endOfFile",
   };



   const char* status_message(const ::estatus& estatus)
   {

      if (estatus < error_file ||
         ((i64)estatus.m_estatus) >= ((i64)error_file + (i64)(sizeof(rgszFileExceptionCause) / sizeof(rgszFileExceptionCause[0]))))
      {

         return nullptr;

      }

      return rgszFileExceptionCause[((i64)estatus.m_estatus) - (i64)error_file];

   }


   static const char szUnknown[] = "unknown";


      CLASS_DECL_ACME bool should_ignore_file_exception_callstack(const ::estatus& estatus)
      {

         if (estatus == error_file_not_found)
         {

            if (g_iCallStackLevel >= 3)
            {

               return true;

            }

         }

         if (estatus == error_bad_path)
         {

            if (g_iCallStackLevel >= 3)
            {

               return true;

            }

         }

         return false;

      }

      exception::exception(const ::estatus& estatus, LONG lOsError, int iErrNo, const ::file::path & path, const efileopen & efileopen) :
         ::io_exception(::error_io, nullptr, should_ignore_file_exception_callstack(estatus) ? SKIP_callstack : callstack_DEFAULT_SKIP)
      {

         m_estatus = estatus;

         m_lOsError = lOsError;

         m_iErrNo = iErrNo;

         m_efileopen = efileopen;

         m_path = path;

         m_bDumpBackTrace = DUMP_FILE_EXCEPTION_BACK_TRACE != 0 && !(m_efileopen & ::file::no_callstack);

         const char* psz = ::file::status_message(estatus);

         if (psz == NULL)
         {

            psz = ::file::status_message(error_file);

         }

         string strException;

#ifdef WINDOWS_DESKTOP

         strException.Format(":file(%hs(%" PRId64 "),%d,%s)", psz, estatus.m_estatus, lOsError, path.c_str());

#else

         strException.Format(":file(%s(%" PRId64 "),%d,%s)", psz, estatus.m_estatus, lOsError, path.c_str());

#endif

         cat_exception(strException);

      }


      exception::~exception()
      {

      }


      ::estatus exception::get_status()
      {

         return m_estatus;

      }


      LONG exception::get_os_error()
      {

         return m_lOsError;

      }


      string exception::get_file_path()
      {

         return m_path;

      }


      struct PROCESS_INFO_t
      {
         string csProcess;
         u32 dwImageListIndex;
      };


      //#ifdef WINDOWS_DESKTOP
      //
      //   void CALLBACK exception::CallBackFunc( OF_INFO_t OpenedFileInfo, uptr pUserContext )
      //   {
      //      ((exception*)pUserContext)->OnFileFound( OpenedFileInfo );
      //   }
      //
      //   void exception::OnFileFound(OF_INFO_t OpenedFileInfo )
      //   {
      //
      //      if(::file::path(OpenedFileInfo.pFile).name().compare_ci(m_path.name()) == 0)
      //
      //      {
      //
      //         PROCESS_INFO_t stInfo;
      //         //if( !m_stProcessInfo.lookup( OpenedFileInfo.dwPID, stInfo))
      //         {
      //            TCHAR tcFileName[MAX_PATH];
      //            string csModule;
      //            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, TRUE, OpenedFileInfo.dwPID );
      //            stInfo.dwImageListIndex = 0;
      //            if( !hProcess || !GetProcessImageFileName( hProcess, tcFileName, MAX_PATH ))
      //            {
      //               if( hProcess )
      //               {
      //                  CloseHandle( hProcess );
      //               }
      //
      //               if( OpenedFileInfo.dwPID == 4 )// system process
      //               {
      //                  stInfo.csProcess = L"System";
      //               }
      //               else
      //               {
      //                  stInfo.csProcess = L"Unknown Process";
      //               }
      //            }
      //            else
      //            {
      //               //GetDrive( tcFileName, csModule, false );
      //               //CloseHandle( hProcess );
      //               //LIBCALL(shlwapi,PathStripPathA)(tcFileName);
      //               //stInfo.csProcess = tcFileName;
      //               //SHFILEINFO stIcon = {0};
      //               /*          if( SHGetFileInfo( csModule, 0, &stIcon, sizeof( stIcon), SHGFI_ICON ))
      //               {
      //               stInfo.dwImageListIndex = m_imgListCtrl.add( stIcon.hIcon );
      //               DestroyIcon( stIcon.hIcon );
      //               }*/
      //            }
      //            // m_stProcessInfo[OpenedFileInfo.dwPID] = stInfo;
      //         }
      //         // Insert Process name, PID and file name
      //         //m_list.InsertItem( m_nCount, stInfo.csProcess, stInfo.dwImageListIndex );
      //         string csPid;
      //         csPid.Format( "%d ( 0x%x )", OpenedFileInfo.dwPID, OpenedFileInfo.dwPID );
      //         m_strAdd += "PID: " + csPid + " Process Name : " + stInfo.csProcess;
      //         //m_list.set_item_text( m_nCount, 2, OpenedFileInfo.pFile );
      //
      //         //m_list.SetItemData( m_nCount, (uptr)OpenedFileInfo.hFile );
      //
      //      }
      //
      //   }
      //
      //#endif

         /*
         string exception::get_friendly_message(PUINT pnHelpContext) const
         {

         string str;

         if(!get_friendly_error_message(str, pnHelpContext))
         return "";

         return str;

         }
         */

      bool exception::get_error_message(string& str, PUINT pnHelpContext)
      {

         // if (pnHelpContext != nullptr)
         //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

         string strMessage;

         string strFileName = m_path;

         if (strFileName.is_empty())
            strFileName = "IDS_UNNAMED_FILE";

         if (m_lOsError == ERROR_ACCESS_DENIED || m_lOsError == ERROR_SHARING_VIOLATION)
         {

            wstring wstr;

            wstr = ::str::international::utf8_to_unicode(m_path.name());

            // #ifdef WINDOWS_DESKTOP
            //          GetOpenedFiles(wstr, ALL_TYPES, &exception::CallBackFunc, (uptr)this);
            // #endif

            if (m_strAdd.has_char())
            {
               ((exception*)this)->m_strAdd = " Process Using the file = " + m_strAdd;
            }
            else
            {
               ((exception*)this)->m_strAdd = " Process Using the file Not Found ";
            }

         }

         string strExtra;

         strExtra = get_system_error_message(m_lOsError);

         strExtra += m_strAdd;

         strMessage.Format("file error number: %d - %s - file: %s", m_estatus.m_estatus, strExtra.c_str(), strFileName.c_str());

         str = strMessage;

         return TRUE;
      }


      /*
      bool exception::get_error_message(string & str, PUINT pnHelpContext) const
      {

      // if (pnHelpContext != nullptr)
      //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

      string strMessage;

      string strFileName = m_path;

      if(strFileName.is_empty())
      strFileName = "IDS_UNNAMED_FILE";

      string strExtra;

      strExtra = get_system_error_message(m_lOsError);

      strMessage.Format("file error number: %d - %s - file: %s", m_cause, strExtra, strFileName);

      str = strMessage;

      return TRUE;
      }
      */

      void exception::dump(dump_context& dumpcontext) const
      {
         UNREFERENCED_PARAMETER(dumpcontext);
         //matter::dump(dumpcontext);

         /*   dumpcontext << "m_cause = ";
         if (m_cause >= 0 && m_cause < _countof(rgszFileExceptionCause))
         dumpcontext << rgszFileExceptionCause[m_cause];
         else
         dumpcontext << szUnknown;
         dumpcontext << "\nm_lOsError = " << (void *)m_lOsError;

         dumpcontext << "\n";*/
      }














   /* Error Codes */

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#ifndef __APPLE__
#define EAGAIN          11
#endif
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34

#if defined(WINDOWS)

#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

#endif

/*
* Support EDEADLOCK for compatibiity with older MS-C versions.
*/
#ifndef EDEADLOCK
#define EDEADLOCK       EDEADLK
#endif

      void throw_exception(const ::estatus& estatus, LONG lOsError, int iErrNo, const ::file::path& path, const ::efileopen& efileopen)
      {

         __throw(exception(estatus, lOsError, iErrNo, path, efileopen));

      }


      void throw_status(const ::estatus& estatus, LONG lOsError, const ::file::path& path)
      {

         throw_exception(estatus, lOsError, -1, path, 0);

      }


      void throw_stdio_exception(const ::estatus& estatus, LONG lDOSError, const ::file::path& path)
      {

         throw_status(estatus, ::file::dos_to_os_error(lDOSError), path);

      }


      void throw_os_error(LONG lOsError, const ::file::path& path)
      {

         throw_status(os_error_to_status(lOsError), lOsError, path);

      }


      void  throw_errno(int iErrNo, const ::file::path& path)
      {

         throw_exception(errno_to_status(iErrNo), -1, iErrNo, path, 0);

      }


      ::estatus os_error_to_status(LONG lOsErr)
      {
         // NT Error codes
         switch ((UINT)lOsErr)
         {
         case NO_ERROR:
            return error_file;
         case ERROR_FILE_NOT_FOUND:
            return error_file_not_found;
         case ERROR_PATH_NOT_FOUND:
            return error_bad_path;
         case ERROR_TOO_MANY_OPEN_FILES:
            return error_too_many_open_files;
         case ERROR_ACCESS_DENIED:
            return error_file_access_denied;
         case ERROR_INVALID_HANDLE:
            return error_file_not_found;
         case ERROR_BAD_FORMAT:
            return error_invalid_file;
         case ERROR_INVALID_ACCESS:
            return error_file_access_denied;
         case ERROR_INVALID_DRIVE:
            return error_bad_path;
         case ERROR_CURRENT_DIRECTORY:
            return error_remove_current_dir;
         case ERROR_NOT_SAME_DEVICE:
            return error_bad_path;
         case ERROR_NO_MORE_FILES:
            return error_file_not_found;
         case ERROR_WRITE_PROTECT:
            return error_file_access_denied;
         case ERROR_BAD_UNIT:
            return error_hard_io;
         case ERROR_NOT_READY:
            return error_hard_io;
         case ERROR_BAD_COMMAND:
            return error_hard_io;
         case ERROR_CRC:
            return error_hard_io;
         case ERROR_BAD_LENGTH:
            return error_bad_seek;
         case ERROR_SEEK:
            return error_bad_seek;
         case ERROR_NOT_DOS_DISK:
            return error_invalid_file;
         case ERROR_SECTOR_NOT_FOUND:
            return error_bad_seek;
         case ERROR_WRITE_FAULT:
            return error_file_access_denied;
         case ERROR_READ_FAULT:
            return error_bad_seek;
         case ERROR_SHARING_VIOLATION:
            return error_file_sharing_violation;
         case ERROR_LOCK_VIOLATION:
            return error_file_lock_violation;
         case ERROR_WRONG_DISK:
            return error_bad_path;
         case ERROR_SHARING_BUFFER_EXCEEDED:
            return error_too_many_open_files;
         case ERROR_HANDLE_EOF:
            return error_end_of_file;
         case ERROR_HANDLE_DISK_FULL:
            return error_disk_full;
         case ERROR_DUP_NAME:
            return error_bad_path;
         case ERROR_BAD_NETPATH:
            return error_bad_path;
         case ERROR_NETWORK_BUSY:
            return error_file_access_denied;
         case ERROR_DEV_NOT_EXIST:
            return error_bad_path;
         case ERROR_ADAP_HDW_ERR:
            return error_hard_io;
         case ERROR_BAD_NET_RESP:
            return error_file_access_denied;
         case ERROR_UNEXP_NET_ERR:
            return error_hard_io;
         case ERROR_BAD_REM_ADAP:
            return error_invalid_file;
         case ERROR_NO_SPOOL_SPACE:
            return error_directory_full;
         case ERROR_NETNAME_DELETED:
            return error_file_access_denied;
         case ERROR_NETWORK_ACCESS_DENIED:
            return error_file_access_denied;
         case ERROR_BAD_DEV_TYPE:
            return error_invalid_file;
         case ERROR_BAD_NET_NAME:
            return error_bad_path;
         case ERROR_TOO_MANY_NAMES:
            return error_too_many_open_files;
         case ERROR_SHARING_PAUSED:
            return error_bad_path;
         case ERROR_REQ_NOT_ACCEP:
            return error_file_access_denied;
         case ERROR_FILE_EXISTS:
            return error_file_access_denied;
         case ERROR_CANNOT_MAKE:
            return error_file_access_denied;
         case ERROR_ALREADY_ASSIGNED:
            return error_bad_path;
         case ERROR_INVALID_PASSWORD:
            return error_file_access_denied;
         case ERROR_NET_WRITE_FAULT:
            return error_hard_io;
         case ERROR_DISK_CHANGE:
            return error_file_not_found;
         case ERROR_DRIVE_LOCKED:
            return error_file_lock_violation;
         case ERROR_BUFFER_OVERFLOW:
            return error_bad_path;
         case ERROR_DISK_FULL:
            return error_disk_full;
         case ERROR_NO_MORE_SEARCH_HANDLES:
            return error_too_many_open_files;
         case ERROR_INVALID_TARGET_HANDLE:
            return error_invalid_file;
         case ERROR_INVALID_CATEGORY:
            return error_hard_io;
         case ERROR_INVALID_NAME:
            return error_bad_path;
         case ERROR_INVALID_LEVEL:
            return error_bad_path;
         case ERROR_NO_VOLUME_LABEL:
            return error_bad_path;
         case ERROR_NEGATIVE_SEEK:
            return error_bad_seek;
         case ERROR_SEEK_ON_DEVICE:
            return error_bad_seek;
         case ERROR_DIR_NOT_ROOT:
            return error_bad_path;
         case ERROR_DIR_NOT_EMPTY:
            return error_remove_current_dir;
         case ERROR_LABEL_TOO_LONG:
            return error_bad_path;
         case ERROR_BAD_PATHNAME:
            return error_bad_path;
         case ERROR_LOCK_FAILED:
            return error_file_lock_violation;
         case ERROR_BUSY:
            return error_file_access_denied;
         case ERROR_INVALID_ORDINAL:
            return error_invalid_file;
         case ERROR_ALREADY_EXISTS:
            return error_file_access_denied;
         case ERROR_INVALID_EXE_SIGNATURE:
            return error_invalid_file;
         case ERROR_BAD_EXE_FORMAT:
            return error_invalid_file;
         case ERROR_FILENAME_EXCED_RANGE:
            return error_bad_path;
         case ERROR_META_EXPANSION_TOO_LONG:
            return error_bad_path;
         case ERROR_DIRECTORY:
            return error_bad_path;
         case ERROR_OPERATION_ABORTED:
            return error_hard_io;
         case ERROR_IO_INCOMPLETE:
            return error_hard_io;
         case ERROR_IO_PENDING:
            return error_hard_io;
         case ERROR_SWAPERROR:
            return error_file_access_denied;
         default:
            return error_file;
         }
      }


      int dos_to_os_error(int lDosErr)
      {

         // !!todo

         return lDosErr;

      }


   //void throw_exception(::estatus estatus, LONG lOsError, int iErrNo, const ::file::path & path, const ::efileopen & efileopen)
   //{

   //   __throw(::file::exception(estatus, lOsError, iErrNo, path, efileopen));

   //}

//   void throw_status(const ::estatus& estatus, LONG lOsError, const ::file::path& path)
//   {
//
//#ifdef __DEBUG
//
//      const char* psz = ::file:status_message(estatus);
//
//      string strFormat;
//
//      strFormat.Format("file exception: %hs, file %s, App error information = %s (%ld).\n", psz, (path.is_empty()) ? "Unknown" : path.c_str(), FormatMessageFromSystem(lOsError).c_str(), lOsError);
//
//      ::acme::application* papp = ::get_context_application();
//
//      TRACE(strFormat);
//
//#endif // __DEBUG
//
//
//      __throw(::file::exception(estatus, lOsError, pszFileName, 0));
//
//
//   }


   //void throw_errno(i32 nErrno, const char* pszFileName /* = nullptr */)

   //{

   //   if (nErrno != 0)
   //   {

   //      ::file::throw_exception(errno_to_status(nErrno), -1, errno, pszFileName);


   //   }

   //}



   ::estatus errno_to_status(i32 nErrno)
   {

      switch (nErrno)
      {
      case EPERM:
      case EACCES:
         return error_file_access_denied;
      case EBADF:
         return error_invalid_file;
         //      case EDEADLOCK:
         //       return ::file::exception::sharingViolation;
      case EMFILE:
         return error_too_many_open_files;
      case ENOENT:
      case ENFILE:
         return error_file_not_found;
      case ENOSPC:
         return error_disk_full;
      case EINVAL:
      case EIO:
         return error_hard_io;
      default:
         return error_file;
      }

   }


   //::estatus os_error_to_status(LONG lOsErr)
   //{
   //   // NT Error codes
   //   switch ((UINT)lOsErr)
   //   {
   //   case NO_ERROR:
   //      return ::success;
   //   case ERROR_FILE_NOT_FOUND:
   //      return ::error_file_not_found;
   //   case ERROR_PATH_NOT_FOUND:
   //      return ::error_bad_path;
   //   case ERROR_TOO_MANY_OPEN_FILES:
   //      return ::error_too_many_open_files;
   //   case ERROR_ACCESS_DENIED:
   //      return ::error_file_access_denied;
   //   case ERROR_INVALID_HANDLE:
   //      return ::error_file_not_found;
   //   case ERROR_BAD_FORMAT:
   //      return ::error_invalid_file;
   //   case ERROR_INVALID_ACCESS:
   //      return ::error_file_access_denied;
   //   case ERROR_INVALID_DRIVE:
   //      return ::error_bad_path;
   //   case ERROR_CURRENT_DIRECTORY:
   //      return ::error_remove_current_dir;
   //   case ERROR_NOT_SAME_DEVICE:
   //      return ::error_bad_path;
   //   case ERROR_NO_MORE_FILES:
   //      return ::error_file_not_found;
   //   case ERROR_WRITE_PROTECT:
   //      return ::error_file_access_denied;
   //   case ERROR_BAD_UNIT:
   //      return ::error_hard_io;
   //   case ERROR_NOT_READY:
   //      return ::error_hard_io;
   //   case ERROR_BAD_COMMAND:
   //      return ::error_hard_io;
   //   case ERROR_CRC:
   //      return ::error_hard_io;
   //   case ERROR_BAD_LENGTH:
   //      return ::error_bad_seek;
   //   case ERROR_SEEK:
   //      return ::error_bad_seek;
   //   case ERROR_NOT_DOS_DISK:
   //      return ::error_invalid_file;
   //   case ERROR_SECTOR_NOT_FOUND:
   //      return ::error_bad_seek;
   //   case ERROR_WRITE_FAULT:
   //      return ::error_file_access_denied;
   //   case ERROR_READ_FAULT:
   //      return ::error_bad_seek;
   //   case ERROR_SHARING_VIOLATION:
   //      return ::error_file_sharing_violation;
   //   case ERROR_LOCK_VIOLATION:
   //      return ::error_file_lock_violation;
   //   case ERROR_WRONG_DISK:
   //      return ::error_bad_path;
   //   case ERROR_SHARING_BUFFER_EXCEEDED:
   //      return ::error_too_many_open_files;
   //   case ERROR_HANDLE_EOF:
   //      return ::error_end_of_file;
   //   case ERROR_HANDLE_DISK_FULL:
   //      return ::error_disk_full;
   //   case ERROR_DUP_NAME:
   //      return ::error_bad_path;
   //   case ERROR_BAD_NETPATH:
   //      return ::error_bad_path;
   //   case ERROR_NETWORK_BUSY:
   //      return ::error_file_access_denied;
   //   case ERROR_DEV_NOT_EXIST:
   //      return ::error_bad_path;
   //   case ERROR_ADAP_HDW_ERR:
   //      return ::error_hard_io;
   //   case ERROR_BAD_NET_RESP:
   //      return ::error_file_access_denied;
   //   case ERROR_UNEXP_NET_ERR:
   //      return ::error_hard_io;
   //   case ERROR_BAD_REM_ADAP:
   //      return ::error_invalid_file;
   //   case ERROR_NO_SPOOL_SPACE:
   //      return ::error_directory_full;
   //   case ERROR_NETNAME_DELETED:
   //      return ::error_file_access_denied;
   //   case ERROR_NETWORK_ACCESS_DENIED:
   //      return ::error_file_access_denied;
   //   case ERROR_BAD_DEV_TYPE:
   //      return ::error_invalid_file;
   //   case ERROR_BAD_NET_NAME:
   //      return ::error_bad_path;
   //   case ERROR_TOO_MANY_NAMES:
   //      return ::error_too_many_open_files;
   //   case ERROR_SHARING_PAUSED:
   //      return ::error_bad_path;
   //   case ERROR_REQ_NOT_ACCEP:
   //      return ::error_file_access_denied;
   //   case ERROR_FILE_EXISTS:
   //      return ::error_file_access_denied;
   //   case ERROR_CANNOT_MAKE:
   //      return ::error_file_access_denied;
   //   case ERROR_ALREADY_ASSIGNED:
   //      return ::error_bad_path;
   //   case ERROR_INVALID_PASSWORD:
   //      return ::error_file_access_denied;
   //   case ERROR_NET_WRITE_FAULT:
   //      return ::error_hard_io;
   //   case ERROR_DISK_CHANGE:
   //      return ::error_file_not_found;
   //   case ERROR_DRIVE_LOCKED:
   //      return ::error_file_lock_violation;
   //   case ERROR_BUFFER_OVERFLOW:
   //      return ::error_bad_path;
   //   case ERROR_DISK_FULL:
   //      return ::error_disk_full;
   //   case ERROR_NO_MORE_SEARCH_HANDLES:
   //      return ::error_too_many_open_files;
   //   case ERROR_INVALID_TARGET_HANDLE:
   //      return ::error_invalid_file;
   //   case ERROR_INVALID_CATEGORY:
   //      return ::error_hard_io;
   //   case ERROR_INVALID_NAME:
   //      return ::error_bad_path;
   //   case ERROR_INVALID_LEVEL:
   //      return ::error_bad_path;
   //   case ERROR_NO_VOLUME_LABEL:
   //      return ::error_bad_path;
   //   case ERROR_NEGATIVE_SEEK:
   //      return ::error_bad_seek;
   //   case ERROR_SEEK_ON_DEVICE:
   //      return ::error_bad_seek;
   //   case ERROR_DIR_NOT_ROOT:
   //      return ::error_bad_path;
   //   case ERROR_DIR_NOT_EMPTY:
   //      return ::error_remove_current_dir;
   //   case ERROR_LABEL_TOO_LONG:
   //      return ::error_bad_path;
   //   case ERROR_BAD_PATHNAME:
   //      return ::error_bad_path;
   //   case ERROR_LOCK_FAILED:
   //      return ::error_file_lock_violation;
   //   case ERROR_BUSY:
   //      return ::error_file_access_denied;
   //   case ERROR_INVALID_ORDINAL:
   //      return ::error_invalid_file;
   //   case ERROR_ALREADY_EXISTS:
   //      return ::error_file_access_denied;
   //   case ERROR_INVALID_EXE_SIGNATURE:
   //      return ::error_invalid_file;
   //   case ERROR_BAD_EXE_FORMAT:
   //      return ::error_invalid_file;
   //   case ERROR_FILENAME_EXCED_RANGE:
   //      return ::error_bad_path;
   //   case ERROR_META_EXPANSION_TOO_LONG:
   //      return ::error_bad_path;
   //   case ERROR_DIRECTORY:
   //      return ::error_bad_path;
   //   case ERROR_OPERATION_ABORTED:
   //      return ::error_hard_io;
   //   case ERROR_IO_INCOMPLETE:
   //      return ::error_hard_io;
   //   case ERROR_IO_PENDING:
   //      return ::error_hard_io;
   //   case ERROR_SWAPERROR:
   //      return ::error_file_access_denied;
   //   default:
   //      return ::error_file;
   //   }
   //}



} // namespace file




