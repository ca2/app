#include "framework.h"
//#include "text_stream.h"
#include "exception.h"


CLASS_DECL_ACME void get_message(::string & strMessage, const ::error_code & errorcode);


#define DUMP_FILE_EXCEPTION_BACK_TRACE 0

/////////////////////////////////////////////////////////////////////////////
// file_exception helpers

namespace file
{

   static const_char_pointer rgszFileExceptionCause[] =
   {
      "genericFileError",
      "fileNotFound",
      "badPath",
      "tooManyOpenFiles",
      "accessDenied",
      "invalidFile",
      "eraseCurrentDir",
      "directoryFull",
      "badSeek",
      "hardIO",
      "sharingViolation",
      "lockViolation",
      "diskFull",
      "endOfFile",
   };



   const_char_pointer status_short_description(const ::e_status & estatus)
   {

      if (estatus < error_file ||
         (estatus.as_long_long()) >= ((long long)error_file + (long long)(sizeof(rgszFileExceptionCause) / sizeof(rgszFileExceptionCause[0]))))
      {

         return nullptr;

      }

      return rgszFileExceptionCause[estatus.as_long_long() - (long long)error_file];

   }


   static const char szUnknown[] = "unknown";


      //CLASS_DECL_ACME bool should_ignore_file_exception_callstack(const ::e_status & estatus)
      //{

      //   if (estatus == error_file_not_found)
      //   {

      //      if (g_iCallStackLevel >= 3)
      //      {

      //         return true;

      //      }

      //   }

      //   if (estatus == error_bad_path)
      //   {

      //      if (g_iCallStackLevel >= 3)
      //      {

      //         return true;

      //      }

      //   }

      //   return false;

      //}

      exception::exception(const ::e_status & estatus, const ::error_code & errorcode, const ::file::path & path, ::file::e_open eopen, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails) :
         ::exception(estatus, scopedstrMessage, scopedstrDetails)
         //::io_exception(::error_io, nullptr, should_ignore_file_exception_callstack(estatus) ? SKIP_CALLSTACK : CALLSTACK_DEFAULT_SKIP)
      {

         m_estatus = estatus;

         m_errorcodea.add(errorcode);

//         m_iErrNo = iErrNo;

//         m_eopen = eopen;

  //       m_path = path;

         //m_bDumpBackTrace = DUMP_FILE_EXCEPTION_BACK_TRACE != 0 && !(m_eopen & ::file::e_open_no_callstack);

         const_char_pointer psz = ::file::status_short_description(estatus);

         if (psz == NULL)
         {

            psz = ::file::status_short_description(error_file);

         }
         
         string strErrorCodeMessage;
         
         ::get_message(strErrorCodeMessage, errorcode);

         string strException;

         strException.formatf("path = \"%s\"\nstatus = \"%s\"\nstatus_code = (%" PRId64 ")\nos_error = \"%s\"", path.c_str(), psz, estatus.as_long_long(), strErrorCodeMessage.c_str());

         m_strMessage += strException;

      }


      exception::exception(const ::file::exception & exception) :
         ::exception(exception)
      {


      }



      exception::~exception()
      {

      }


      ::pointer < ::subparticle > exception::clone()
      {

         auto pexception = __allocate ::file::exception(*this);

         return pexception;

      }



    /*  void exception::get_status()
      {

         return m_estatus;

      }*/


      //int exception::get_os_error()
      //{

      //   return m_lOsError;

      //}


      //string exception::get_file_path()
      //{

      //   return m_path;

      //}


      struct PROCESS_INFO_t
      {
         string csProcess;
         unsigned int dwImageListIndex;
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
      //      if(::file::path(OpenedFileInfo.pFile).name().case_insensitive_order(m_path.name()) == 0)
      //
      //      {
      //
      //         PROCESS_INFO_t stInfo;
      //         //if( !m_stProcessInfo.lookup( OpenedFileInfo.dwPID, stInfo))
      //         {
      //            TCHAR tcFileName[MAX_PATH];
      //            string csModule;
      //            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, true, OpenedFileInfo.dwPID );
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
      //                  stInfo.csProcess = L"system()";
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
         string exception::get_friendly_message(Punsigned int pnHelpContext) const
         {

         string str;

         if(!get_friendly_error_message(str, pnHelpContext))
         return "";

         return str;

         }
         */



    /*
      bool exception::get_error_message(string & str, Punsigned int pnHelpContext) const
      {

      // if (pnHelpContext != nullptr)
      //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

      string strMessage;

      string strFileName = m_path;

      if(strFileName.is_empty())
      strFileName = "IDS_UNNAMED_FILE";

      string strExtra;

      strExtra = get_last_error_message(m_lOsError);

      strMessage.formatf("file error number: %d - %s - file: %s", m_cause, strExtra, strFileName);

      str = strMessage;

      return true;
      }
      */

      //void exception::dump(dump_context& dumpcontext) const
      //{
      //   __UNREFERENCED_PARAMETER(dumpcontext);
      //   //matter::dump(dumpcontext);

      //   /*   dumpcontext << "m_cause = ";
      //   if (m_cause >= 0 && m_cause < _countof(rgszFileExceptionCause))
      //   dumpcontext << rgszFileExceptionCause[m_cause];
      //   else
      //   dumpcontext << szUnknown;
      //   dumpcontext << "\nm_lOsError = " << (void *)m_lOsError;

      //   dumpcontext << "\n";*/
      //}














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
#if !defined(__APPLE__) && !defined(__BSD__)
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

      //void throw_exception(const ::e_status & estatus, int lOsError, int iErrNo, const ::file::path& path, ::file::e_open eopen)
      //{

      //   throw ::exception(estatus, lOsError, iErrNo, path, eopen);

      //}


      //void throw ::exception(const ::e_status & estatus, int lOsError, const ::file::path& path)
      //{

      //   throw ::exception(estatus, lOsError, -1, path, e_null);

      //}


      //void throw_stdio_exception(const ::e_status & estatus, int lDOSError, const ::file::path& path)
      //{

      //   throw ::exception(estatus,
      //                   0, ::file::dos_to_os_error(lDOSError), path);

      //}


#ifdef WINDOWS


      //void throw_os_error(DWORD dwLastError, const ::file::path& path)
      //{

      //   throw ::exception(os_error_to_status(dwLastError), dwLastError, path);

      //}


#endif


      //void  throw ::file::exception(errno_status(errno), (int iErrNo, const ::file::path& path)
      //{

      //   throw _exception(errno_status(iErrNo), -1, iErrNo, path, e_null);

      //}




      int dos_to_os_error(int lDosErr)
      {

         // !!todo

         return lDosErr;

      }


   //void throw_exception(::e_status estatus, int lOsError, int iErrNo, const ::file::path & path, ::file::e_open eopen)
   //{

   //   throw ::exception(::file::exception(estatus, lOsError, iErrNo, path, eopen));

   //}

//   void throw ::exception(const ::e_status & estatus, int lOsError, const ::file::path& path)
//   {
//
//#ifdef _DEBUG
//
//      const ::scoped_string & scopedstr = ::file:status_short_description(estatus);
//
//      string strFormat;
//
//      strFormat.formatf("file exception: %hs, file %s, App error information = %s (%ld).\n", psz, (path.is_empty()) ? "Unknown" : path.c_str(), FormatMessageFromSystem(lOsError).c_str(), lOsError);
//
//      ::platform::application* papp = ::get_app();
//
//      information(strFormat);
//
//#endif // __DEBUG
//
//
//      throw ::exception(::file::exception(estatus, lOsError, pszFileName, 0));
//
//
//   }


   //void throw ::file::exception(errno_status(errno), (int nErrno, const ::file::path & path /* = nullptr */)

   //{

   //   if (nErrno != 0)
   //   {

   //      ::file::throw_exception(errno_status(nErrno), -1, errno, pszFileName);


   //   }

   //}








} // namespace file

