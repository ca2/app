#include "framework.h"
#include "apex/os/windows_common/file.h"


namespace uwp
{


   __STATIC inline bool IsDirSep(WCHAR ch)
   {
      return (ch == '\\' || ch == '/');
   }


   file::file()
   {

      m_hFile = HFILE_NULL;

      m_bCloseOnDelete = TRUE;

   }



   file::~file()
   {

      if (m_hFile != HFILE_NULL && m_bCloseOnDelete)
         close();

   }

   //__pointer(::file::file) file::Duplicate() const
   //{
   //   ASSERT_VALID(this);
   //   ASSERT(m_hFile != (::u32)HFILE_NULL);

   //   __pointer(file) pFile = __new(file());
   //   HANDLE hFile;
   //   if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
   //                          ::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
   //   {
   //      delete pFile;
   //      //xxx      Ex1::file::throw_os_error((::i32)::get_last_error(), m_path);
   //      __throw(::exception::exception("integer_exception 1"));
   //   }
   //   pFile->m_hFile = (::u32)hFile;
   //   ASSERT(pFile->m_hFile != (::u32)HFILE_NULL);
   //   pFile->m_bCloseOnDelete = m_bCloseOnDelete;
   //   return pFile;
   //}


   ::status::result file::open(const ::file::path & path, const ::file::e_open & efileopenParam)
   {

      ::file::e_open eopen(efileopenParam);

      if (m_hFile != HFILE_NULL)
         close();

      ASSERT_VALID(this);
      ASSERT(__is_valid_string(path));
      ASSERT(!(eopen & ::file::e_open_text));   // text mode not supported

      // file objects are always binary and CreateFile does not need flag
      eopen -= ::file::e_open_binary;


      string strPath = path;

      str::begins_eat_ci(strPath,"image:\\\\");

      str::begins_eat_ci(strPath, "music:\\\\");

      str::begins_eat_ci(strPath, "video:\\\\");

      if (str::begins_eat_ci(strPath, "document:\\\\"))
      {

         output_debug_string("document:\\\\" + strPath);

      }


      ::file::path lpszFileName(strPath);
      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         Context.dir().mk(lpszFileName.folder());

      }

      m_bCloseOnDelete = FALSE;
      m_hFile = HFILE_NULL;
      m_path.Empty();

      m_path     = lpszFileName;
//      m_wstrFileName    = ::str::international::utf8_to_unicode(m_path);

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      // ::map read/write mode
      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
      ::u32 dwAccess = 0;
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwAccess = GENERIC_READ;
         break;
      case ::file::e_open_write:
         dwAccess = GENERIC_WRITE;
         break;
      case ::file::e_open_read_write:
         dwAccess = GENERIC_READ|GENERIC_WRITE;
         break;
      default:
         dwAccess = GENERIC_READ;
         break;
      }

      // ::map share mode
      ::u32 dwShareMode = 0;
      switch (eopen & 0x70)    // ::map compatibility mode to exclusive
      {
      default:
         ASSERT(FALSE);  // invalid share mode?
      case ::file::e_open_share_compat:
      case ::file::e_open_share_exclusive:
         dwShareMode = 0;
         break;
      case ::file::e_open_share_deny_write:
         dwShareMode = FILE_SHARE_READ;
         break;
      case ::file::e_open_share_deny_read:
         dwShareMode = FILE_SHARE_WRITE;
         break;
      case ::file::e_open_share_deny_none:
         dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
         break;
      }

      // Note: type_text and type_binary are used in derived classes only.

      // ::map mode_no_inherit flag
      SECURITY_ATTRIBUTES sa;
      sa.nLength = sizeof(sa);
      sa.lpSecurityDescriptor = nullptr;
      sa.bInheritHandle = !(eopen & ::file::e_open_no_inherit);

      // ::map creation flags
      ::u32 dwCreateFlag;
      if (eopen & ::file::e_open_create)
      {
         if (eopen & ::file::e_open_no_truncate)
            dwCreateFlag = OPEN_ALWAYS;
         else
            dwCreateFlag = CREATE_ALWAYS;
      }
      else
         dwCreateFlag = OPEN_EXISTING;

      // attempt file creation
      //HANDLE hFile = shell::CreateFile(::str::international::utf8_to_unicode(m_path), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      HANDLE hFile = ::create_file(m_path, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (hFile == INVALID_HANDLE_VALUE)
      {
         ::u32 dwLastError = ::get_last_error();

         if(dwLastError != ERROR_FILE_NOT_FOUND && dwLastError != ERROR_PATH_NOT_FOUND)
         {
            /*         if (pException != nullptr)
            {
            pException->create(get_object());
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = dwLastError;
            pfe->m_cause = WinFileException::OsErrorToException(pfe->m_lOsError);
            pfe->m_path = lpszFileName;
            }
            return FALSE;
            }
            else
            {*/


            return ::os_error_to_status(dwLastError);

            //}

         }

         try
         {
//            m_psystem->m_spfilesystem.m_p->FullPath(m_path, m_path);
         }
         catch(...)
         {
            return error_failed;
         }

         //m_path = ::str::international::unicode_to_utf8(m_wstrFileName);

         hFile = ::create_file("\\\\?\\" + m_path, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);

         if (hFile == INVALID_HANDLE_VALUE)
         {
            /*if (pException != nullptr)
            {
            pException->create(get_object());
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = ::get_last_error();
            pfe->m_cause = WinFileException::OsErrorToException(pfe->m_lOsError);
            pfe->m_path = lpszFileName;
            }
            return FALSE;
            }
            else
            {*/


            ::u32 dwLastError = ::get_last_error();
            return ::os_error_to_status(dwLastError);


            //}

         }

      }

      m_hFile = hFile;

      m_bCloseOnDelete = TRUE;

      return ::success;

   }


   memsize file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_hFile != HFILE_NULL);

      if (nCount == 0)
         return 0;   // avoid Win32 "nullptr-read"

      ASSERT(lpBuf != nullptr);
      ASSERT(__is_valid_address(lpBuf, nCount));

      ::u32 dwRead;
      if (!::ReadFile((HANDLE)m_hFile, lpBuf, (::u32) nCount, &dwRead, nullptr))
         ::file::throw_os_error((::i32)::get_last_error(), m_path);

      return (::u32)dwRead;
   }

   void file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_hFile != HFILE_NULL);

      if (nCount == 0)
         return;     // avoid Win32 "nullptr-write" option

      ASSERT(lpBuf != nullptr);
      ASSERT(__is_valid_address(lpBuf, nCount, FALSE));

      ::u32 nWritten;
      if (!::WriteFile((HANDLE)m_hFile, lpBuf, (::u32) nCount, &nWritten, nullptr))
         ::file::throw_os_error((::i32)::get_last_error(), m_path);

      // Win32s will not return an error all the time (usually DISK_FULL)
      if (nWritten < (::u32) nCount)
      {

         ::file::throw_status(error_disk_full, -1, m_path);

      }

   }

   filesize file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      if(m_hFile == HFILE_NULL)
         ::file::throw_os_error((::i32)0, m_path);

      ASSERT_VALID(this);
      ASSERT(m_hFile != HFILE_NULL);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      ::i32 lLoOffset = lOff & 0xffffffff;
      ::i32 lHiOffset = (lOff >> 32) & 0xffffffff;

      filesize posNew = ::SetFilePointer((HANDLE)m_hFile, lLoOffset, &lHiOffset, (::u32)nFrom);
      posNew |= ((filesize) lHiOffset) << 32;
      if(posNew  == (filesize)-1)
         ::file::throw_os_error((::i32)::get_last_error(), m_path);

      return posNew;
   }

   filesize file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_hFile != HFILE_NULL);

      ::i32 lLoOffset = 0;
      ::i32 lHiOffset = 0;

      filesize pos = ::SetFilePointer((HANDLE)m_hFile, lLoOffset, &lHiOffset, FILE_CURRENT);
      pos |= ((filesize)lHiOffset) << 32;
      if(pos  == (filesize)-1)
         ::file::throw_os_error((::i32)::get_last_error(), m_path);

      return pos;
   }

   
   void file::flush()
   {

      ASSERT_VALID(this);

      if (m_hFile == HFILE_NULL)
         return;

      if (!::FlushFileBuffers((HANDLE)m_hFile))
         ::file::throw_os_error((::i32)::get_last_error(), m_path);
   }


   void file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_hFile != HFILE_NULL);

      bool bError = FALSE;
      if (m_hFile != HFILE_NULL)
         bError = !::CloseHandle((HANDLE)m_hFile);

      m_hFile = HFILE_NULL;
      m_bCloseOnDelete = FALSE;
      m_path.Empty();

      if (bError)
         ::file::throw_os_error((::i32)::get_last_error(), m_path);
   }

   //void file::Abort()
   //{
   //   ASSERT_VALID(this);
   //   if (m_hFile != (::u32)HFILE_NULL)
   //   {
   //      // close but ignore errors
   //      ::CloseHandle((HANDLE)m_hFile);
   //      m_hFile = (::u32)HFILE_NULL;
   //   }
   //   m_path.Empty();
   //}

   
   void file::lock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);

      ASSERT(m_hFile != HFILE_NULL);

   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {

      ASSERT_VALID(this);

      ASSERT(m_hFile != HFILE_NULL);

   }


   void file::set_size(filesize dwNewLen)
   {

      ASSERT_VALID(this);

      ASSERT(m_hFile != HFILE_NULL);


      seek((::i32)dwNewLen, (::file::e_seek)::file::seek_begin);

      if (!::SetEndOfFile((HANDLE)m_hFile))
      {

         ::file::throw_os_error((::i32)::get_last_error(), m_path);

      }

   }


   filesize file::get_size() const
   {
      
      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      file* pFile = (file*)this;

      dwCur = pFile->seek(0L, ::file::seek_current);

      dwLen = pFile->seek_to_end();

      VERIFY(dwCur == (u64)pFile->seek((filesize) dwCur, ::file::seek_begin));

      return (filesize) dwLen;

   }


   string CLASS_DECL_APEX vfxStringFromCLSID(REFCLSID rclsid)
   {

      char szCLSID[256];

      sprintf(szCLSID, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
              rclsid.Data1, rclsid.Data2, rclsid.Data3,
              rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3],
              rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);

      return szCLSID;

   }


   bool CLASS_DECL_APEX vfxGetInProcServer(const char * lpszCLSID, string & str)
   {

      bool b = FALSE;

#ifdef WINDOWS_DESKTOP

      HKEY hKey = nullptr;

      if (RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hKey) == ERROR_SUCCESS)
      {
         HKEY hKeyCLSID = nullptr;
         if (RegOpenKey(hKey, lpszCLSID, &hKeyCLSID) == ERROR_SUCCESS)
         {
            HKEY hKeyInProc = nullptr;
            if (RegOpenKey(hKeyCLSID, "InProcServer32", &hKeyInProc) ==
                  ERROR_SUCCESS)
            {
               char * lpsz = str.GetBuffer(_MAX_PATH);
               ::u32 dwSize = _MAX_PATH * sizeof(char);
               ::u32 dwType;
               ::i32 lRes = ::RegQueryValueEx(hKeyInProc, "",
                                             nullptr, &dwType, (byte*)lpsz, &dwSize);
               str.ReleaseBuffer();
               b = (lRes == ERROR_SUCCESS);
               RegCloseKey(hKeyInProc);
            }
            RegCloseKey(hKeyCLSID);
         }
         RegCloseKey(hKey);
      }
#endif
      return b;
   }
   //#endif  //!___NO_OLE_SUPPORT




   // turn a file, relative path or other into an absolute path
   bool CLASS_DECL_APEX vfxFullPath(unichar * lpszPathOut, const unichar * lpszFileIn)
   // lpszPathOut = buffer of _MAX_PATH
   // lpszFileIn = file, relative path or absolute path
   // (both in ANSI character set)
   {

      ASSERT(__is_valid_address(lpszPathOut, _MAX_PATH));

      wcscpy(lpszPathOut, lpszFileIn);

      return true;

   }


   void CLASS_DECL_APEX vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
   {
      
      __throw(todo());

   }


   void file::assert_valid() const
   {

      ::file::file::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes

   }


   void file::dump(dump_context & dumpcontext) const
   {
      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_hFile;
      dumpcontext << " and name \"" << m_path << "\"";
      dumpcontext << "\n";
   }



   // IMPLEMENT_DYNAMIC(file, ::object)

   /////////////////////////////////////////////////////////////////////////////

#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

   void CLASS_DECL_APEX vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath)
   {
      //   ASSERT(lpszPath != nullptr);
      // determine the root name of the volume
      wstrRoot = wstrPath;
      unichar * lpszRoot = wstrRoot;
      unichar * lpsz;
      for (lpsz = lpszRoot; *lpsz != L'\0'; lpsz = _wcsinc(lpsz))
      {
         // find first double slash and stop
         if (IsDirSep(lpsz[0]) && IsDirSep(lpsz[1]))
            break;
      }
      if (*lpsz != '\0')
      {
         // it is a UNC name, find second slash past '\\'
         ASSERT(IsDirSep(lpsz[0]));
         ASSERT(IsDirSep(lpsz[1]));
         lpsz += 2;
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         if (*lpsz != '\0')
            lpsz = _wcsinc(lpsz);
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         // terminate it just after the UNC root (ie. '\\server\share\')
         if (*lpsz != '\0')
            lpsz[1] = '\0';
      }
      else
      {
         // not a UNC, look for just the first slash
         lpsz = lpszRoot;
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         // terminate it just after root (ie. 'x:\')
         if (*lpsz != '\0')
            lpsz[1] = '\0';
      }
      wstrRoot.release_string_buffer();
   }


   void CLASS_DECL_APEX vfxGetRoot(const unichar * lpszPath, string& strRoot)
   {
      ASSERT(lpszPath != nullptr);
      wstring wstrRoot;
      // determine the root name of the volume
      unichar * lpszRoot = wstrRoot.get_string_buffer(_MAX_PATH * 4);
      __memset(lpszRoot, 0, _MAX_PATH * 4);
      wcsncpy(lpszRoot, lpszPath, _MAX_PATH * 4);
      unichar * lpsz;
      for (lpsz = lpszRoot; *lpsz != '\0'; lpsz = _wcsinc(lpsz))
      {
         // find first double slash and stop
         if (IsDirSep(lpsz[0]) && IsDirSep(lpsz[1]))
            break;
      }
      if (*lpsz != '\0')
      {
         // it is a UNC name, find second slash past '\\'
         ASSERT(IsDirSep(lpsz[0]));
         ASSERT(IsDirSep(lpsz[1]));
         lpsz += 2;
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         if (*lpsz != '\0')
            lpsz = _wcsinc(lpsz);
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         // terminate it just after the UNC root (ie. '\\server\share\')
         if (*lpsz != '\0')
            lpsz[1] = '\0';
      }
      else
      {
         // not a UNC, look for just the first slash
         lpsz = lpszRoot;
         while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
            lpsz = _wcsinc(lpsz);
         // terminate it just after root (ie. 'x:\')
         if (*lpsz != '\0')
            lpsz[1] = '\0';
      }
      ::str::international::unicode_to_utf8(strRoot, wstrRoot);
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
#define EAGAIN          11
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
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

   /*
   * Support EDEADLOCK for compatibiity with older MS-C versions.
   */
#define EDEADLOCK       EDEADLK


   /////////////////////////////////////////////////////////////////////////////
   // file name handlers

   //string file::GetFileName() const
   //{

   //   ASSERT_VALID(this);

   //   ::file::file_status status;

   //   GetStatus(status);

   //   string wstrResult;

   //   wstrResult = status.m_strFullName.name();

   //   return wstrResult;

   //}


   //string file::GetFileTitle() const
   //{

   //   ASSERT_VALID(this);

   //   ::file::file_status status;

   //   GetStatus(status);

   //   string wstrResult;

   //   wstrResult = status.m_strFullName.title();

   //   return wstrResult;

   //}


   ::file::path file::get_file_path() const
   {
      ASSERT_VALID(this);

  /*    ::file::file_status status;
      GetStatus(status);
      return status.m_strFullName;*/
      return m_path;

   }


   //::u32 CLASS_DECL_APEX vfxGetFileName(const unichar * lpszPathName, unichar * lpszTitle, ::u32 nMax)
   //{
   //   ASSERT(lpszTitle == nullptr ||
   //          __is_valid_address(lpszTitle, _MAX_FNAME));
   //   ASSERT(__is_valid_string(lpszPathName));

   //   // always capture the complete file name including extension (if present)
   //   unichar * lpszTemp = (unichar *)lpszPathName;
   //   for (const unichar * lpsz = lpszPathName; *lpsz != '\0'; lpsz = _wcsinc(lpsz))
   //   {
   //      // remember last directory/drive separator
   //      if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
   //         lpszTemp = (unichar *)_wcsinc(lpsz);
   //   }

   //   // lpszTitle can be nullptr which just returns the number of bytes
   //   if (lpszTitle == nullptr)
   //      return wcslen(lpszTemp)+1;

   //   // otherwise copy it into the buffer provided
   //   wcsncpy(lpszTitle, lpszTemp, nMax);
   //   return 0;
   //}


   /////////////////////////////////////////////////////////////////////////////
   // FileException




   //void WinFileException::ThrowOsError(::object * pobject, ::i32 lOsError, const char * lpszFileName /* = nullptr */)
   //{
   //   if (lOsError != 0)
   //      ::file::throw_os_error(pobject, WinFileException::OsErrorToException(lOsError), lOsError, ::error_io, lpszFileName);
   //}

   //void WinFileException::ThrowErrno(::object * pobject, int nErrno, const char * lpszFileName /* = nullptr */)
   //{
   //   if (nErrno != 0)
   //      ::file::throw_os_error(pobject, WinFileException::ErrnoToException(nErrno), _doserrno, ::error_io, lpszFileName);
   //}



   /////////////////////////////////////////////////////////////////////////////
   // WinFileException helpers

   //void CLASS_DECL_APEX throw_exception(__pointer(::apex::application) papp, int cause, ::i32 lOsError, const char * lpszFileName /* == nullptr */)
   //{

   //   __throw(::file::exception(WinFileException::OsErrorToException(lOsError),lOsError,lpszFileName));

   //}


   //::e_status WinFileException::ErrnoToException(int nErrno)
   //{
   //   switch(nErrno)
   //   {
   //   case EPERM:
   //   case EACCES:
   //      return ::file::exception::accessDenied;
   //   case EBADF:
   //      return ::file::exception::invalidFile;
   //   case EDEADLOCK:
   //      return ::file::exception::sharingViolation;
   //   case EMFILE:
   //      return ::file::exception::tooManyOpenFiles;
   //   case ENOENT:
   //   case ENFILE:
   //      return ::file::exception::fileNotFound;
   //   case ENOSPC:
   //      return ::file::exception::diskFull;
   //   case EINVAL:
   //   case EIO:
   //      return ::file::exception::hardIO;
   //   default:
   //      return ::file::exception::type_generic;
   //   }
   //}

   //::e_status WinFileException::OsErrorToException(::i32 lOsErr)
   //{
   //   // NT Error codes
   //   switch ((::u32)lOsErr)
   //   {
   //   case NO_ERROR:
   //      return ::file::exception::none;
   //   case ERROR_FILE_NOT_FOUND:
   //      return ::file::exception::fileNotFound;
   //   case ERROR_PATH_NOT_FOUND:
   //      return ::file::exception::badPath;
   //   case ERROR_TOO_MANY_OPEN_FILES:
   //      return ::file::exception::tooManyOpenFiles;
   //   case ERROR_ACCESS_DENIED:
   //      return ::file::exception::accessDenied;
   //   case ERROR_INVALID_HANDLE:
   //      return ::file::exception::fileNotFound;
   //   case ERROR_BAD_FORMAT:
   //      return ::file::exception::invalidFile;
   //   case ERROR_INVALID_ACCESS:
   //      return ::file::exception::accessDenied;
   //   case ERROR_INVALID_DRIVE:
   //      return ::file::exception::badPath;
   //   case ERROR_CURRENT_DIRECTORY:
   //      return ::file::exception::removeCurrentDir;
   //   case ERROR_NOT_SAME_DEVICE:
   //      return ::file::exception::badPath;
   //   case ERROR_NO_MORE_FILES:
   //      return ::file::exception::fileNotFound;
   //   case ERROR_WRITE_PROTECT:
   //      return ::file::exception::accessDenied;
   //   case ERROR_BAD_UNIT:
   //      return ::file::exception::hardIO;
   //   case ERROR_NOT_READY:
   //      return ::file::exception::hardIO;
   //   case ERROR_BAD_COMMAND:
   //      return ::file::exception::hardIO;
   //   case ERROR_CRC:
   //      return ::file::exception::hardIO;
   //   case ERROR_BAD_LENGTH:
   //      return ::file::exception::badSeek;
   //   case ERROR_SEEK:
   //      return ::file::exception::badSeek;
   //   case ERROR_NOT_DOS_DISK:
   //      return ::file::exception::invalidFile;
   //   case ERROR_SECTOR_NOT_FOUND:
   //      return ::file::exception::badSeek;
   //   case ERROR_WRITE_FAULT:
   //      return ::file::exception::accessDenied;
   //   case ERROR_READ_FAULT:
   //      return ::file::exception::badSeek;
   //   case ERROR_SHARING_VIOLATION:
   //      return ::file::exception::sharingViolation;
   //   case ERROR_LOCK_VIOLATION:
   //      return ::file::exception::lockViolation;
   //   case ERROR_WRONG_DISK:
   //      return ::file::exception::badPath;
   //   case ERROR_SHARING_BUFFER_EXCEEDED:
   //      return ::file::exception::tooManyOpenFiles;
   //   case ERROR_HANDLE_EOF:
   //      return ::file::exception::endOfFile;
   //   case ERROR_HANDLE_DISK_FULL:
   //      return ::file::exception::diskFull;
   //   case ERROR_DUP_NAME:
   //      return ::file::exception::badPath;
   //   case ERROR_BAD_NETPATH:
   //      return ::file::exception::badPath;
   //   case ERROR_NETWORK_BUSY:
   //      return ::file::exception::accessDenied;
   //   case ERROR_DEV_NOT_EXIST:
   //      return ::file::exception::badPath;
   //   case ERROR_ADAP_HDW_ERR:
   //      return ::file::exception::hardIO;
   //   case ERROR_BAD_NET_RESP:
   //      return ::file::exception::accessDenied;
   //   case ERROR_UNEXP_NET_ERR:
   //      return ::file::exception::hardIO;
   //   case ERROR_BAD_REM_ADAP:
   //      return ::file::exception::invalidFile;
   //   case ERROR_NO_SPOOL_SPACE:
   //      return ::file::exception::directoryFull;
   //   case ERROR_NETNAME_DELETED:
   //      return ::file::exception::accessDenied;
   //   case ERROR_NETWORK_ACCESS_DENIED:
   //      return ::file::exception::accessDenied;
   //   case ERROR_BAD_DEV_TYPE:
   //      return ::file::exception::invalidFile;
   //   case ERROR_BAD_NET_NAME:
   //      return ::file::exception::badPath;
   //   case ERROR_TOO_MANY_NAMES:
   //      return ::file::exception::tooManyOpenFiles;
   //   case ERROR_SHARING_PAUSED:
   //      return ::file::exception::badPath;
   //   case ERROR_REQ_NOT_ACCEP:
   //      return ::file::exception::accessDenied;
   //   case ERROR_FILE_EXISTS:
   //      return ::file::exception::accessDenied;
   //   case ERROR_CANNOT_MAKE:
   //      return ::file::exception::accessDenied;
   //   case ERROR_ALREADY_ASSIGNED:
   //      return ::file::exception::badPath;
   //   case ERROR_INVALID_PASSWORD:
   //      return ::file::exception::accessDenied;
   //   case ERROR_NET_WRITE_FAULT:
   //      return ::file::exception::hardIO;
   //   case ERROR_DISK_CHANGE:
   //      return ::file::exception::fileNotFound;
   //   case ERROR_DRIVE_LOCKED:
   //      return ::file::exception::lockViolation;
   //   case ERROR_BUFFER_OVERFLOW:
   //      return ::file::exception::badPath;
   //   case ERROR_DISK_FULL:
   //      return ::file::exception::diskFull;
   //   case ERROR_NO_MORE_SEARCH_HANDLES:
   //      return ::file::exception::tooManyOpenFiles;
   //   case ERROR_INVALID_TARGET_HANDLE:
   //      return ::file::exception::invalidFile;
   //   case ERROR_INVALID_CATEGORY:
   //      return ::file::exception::hardIO;
   //   case ERROR_INVALID_NAME:
   //      return ::file::exception::badPath;
   //   case ERROR_INVALID_LEVEL:
   //      return ::file::exception::badPath;
   //   case ERROR_NO_VOLUME_LABEL:
   //      return ::file::exception::badPath;
   //   case ERROR_NEGATIVE_SEEK:
   //      return ::file::exception::badSeek;
   //   case ERROR_SEEK_ON_DEVICE:
   //      return ::file::exception::badSeek;
   //   case ERROR_DIR_NOT_ROOT:
   //      return ::file::exception::badPath;
   //   case ERROR_DIR_NOT_EMPTY:
   //      return ::file::exception::removeCurrentDir;
   //   case ERROR_LABEL_TOO_LONG:
   //      return ::file::exception::badPath;
   //   case ERROR_BAD_PATHNAME:
   //      return ::file::exception::badPath;
   //   case ERROR_LOCK_FAILED:
   //      return ::file::exception::lockViolation;
   //   case ERROR_BUSY:
   //      return ::file::exception::accessDenied;
   //   case ERROR_INVALID_ORDINAL:
   //      return ::file::exception::invalidFile;
   //   case ERROR_ALREADY_EXISTS:
   //      return ::file::exception::accessDenied;
   //   case ERROR_INVALID_EXE_SIGNATURE:
   //      return ::file::exception::invalidFile;
   //   case ERROR_BAD_EXE_FORMAT:
   //      return ::file::exception::invalidFile;
   //   case ERROR_FILENAME_EXCED_RANGE:
   //      return ::file::exception::badPath;
   //   case ERROR_META_EXPANSION_TOO_LONG:
   //      return ::file::exception::badPath;
   //   case ERROR_DIRECTORY:
   //      return ::file::exception::badPath;
   //   case ERROR_OPERATION_ABORTED:
   //      return ::file::exception::hardIO;
   //   case ERROR_IO_INCOMPLETE:
   //      return ::file::exception::hardIO;
   //   case ERROR_IO_PENDING:
   //      return ::file::exception::hardIO;
   //   case ERROR_SWAPERROR:
   //      return ::file::exception::accessDenied;
   //   default:
   //      return ::file::exception::type_generic;
   //   }
   //}


   // IMPLEMENT_DYNAMIC(WinFileException, ::exception::apex)

   /////////////////////////////////////////////////////////////////////////////




   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool file::get_status(::file::file_status& rStatus) const
   {
      ASSERT_VALID(this);

      //__memset(&rStatus, 0, sizeof(::file::file_status));

      // copy file name from cached m_path
      rStatus.m_strFullName = m_path;

      return TRUE;

   }


//   bool file::GetStatus(const ::file::path & lpszFileName, ::file::file_status& rStatus)
//   {
//
//#ifdef WINDOWS_DESKTOP
//      // attempt to fully qualify path first
//      wstring wstrFullName;
//      wstring wstrFileName;
//      wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
//      if (!vfxFullPath(wstrFullName, wstrFileName))
//      {
//         rStatus.m_strFullName.Empty();
//         return FALSE;
//      }
//      ::str::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);
//
//      WIN32_FIND_DATA findFileData;
//      HANDLE hFind = FindFirstFile((char *)lpszFileName, &findFileData);
//      if (hFind == INVALID_HANDLE_VALUE)
//         return FALSE;
//      VERIFY(FindClose(hFind));
//
//      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
//      rStatus.m_attribute = (byte) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);
//
//      // get just the low ::u32 of the file size
//      ASSERT(findFileData.nFileSizeHigh == 0);
//      rStatus.m_size = (::i32)findFileData.nFileSizeLow;
//
//      // convert times as appropriate
//      rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
//      rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
//      rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);
//
//      if (rStatus.m_ctime.get_time() == 0)
//         rStatus.m_ctime = rStatus.m_mtime;
//
//      if (rStatus.m_atime.get_time() == 0)
//         rStatus.m_atime = rStatus.m_mtime;
//#endif
//      return TRUE;
//   }


   bool file::is_opened() const
   {

      return m_hFile != HFILE_NULL;

   }


   void file::set_file_path(const ::file::path&  lpszNewName)
   {

      ASSERT_VALID(this);

      ASSERT(__is_valid_string(lpszNewName));

      m_path = lpszNewName;

   }


   file::operator HANDLE() const
   { 
      
      return m_hFile; 
      
   }


   u64 file::ReadHuge(void * lpBuffer, u64 dwCount)
   { 
      
      return (u64) read(lpBuffer, (::u32)dwCount);
      
   }


   void file::WriteHuge(const void * lpBuffer, u64 dwCount)
   {
      
      write(lpBuffer, (::u32)dwCount);
      
   }


} // namespace uwp



bool CLASS_DECL_APEX vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
{

   wstrFullPath = wstrPath;

   return true;

}



bool CLASS_DECL_APEX vfxResolveShortcut(string & strTarget, const char * pszSource, ::user::primitive * puiMessageParentOptional)
{

#ifdef WINDOWS_DESKTOP

   ::user::interaction * pinteraction = puiMessageParentOptional;

   wstring wstrFileOut;
   wstring wstrFileIn = ::str::international::utf8_to_unicode(pszSource);

   ::u32 dwVersion = GetVersion();

   // get the Windows version.

   ::u32 dwWindowsMajorVersion =  (::u32)(LOBYTE(LOWORD(dwVersion)));
   ::u32 dwWindowsMinorVersion =  (::u32)(HIBYTE(LOWORD(dwVersion)));

   // get the build number.

   ::u32 dwBuild;

   if (dwVersion < 0x80000000)              // Windows NT
      dwBuild = (::u32)(HIWORD(dwVersion));
   else if (dwWindowsMajorVersion < 4)      // Win32s
      dwBuild = (::u32)(HIWORD(dwVersion) & ~0x8000);
   else                                     // Windows Me/98/95
      dwBuild =  0;

   bool bNativeUnicode;
   if (dwVersion < 0x80000000)              // Windows NT
      bNativeUnicode = TRUE;
   else if (dwWindowsMajorVersion < 4)      // Win32s
      bNativeUnicode = FALSE;
   else                                     // Windows Me/98/95
      bNativeUnicode = FALSE;


   //   __COM com;
   IShellLinkW* psl;
   wstrFileOut = L"";

   SHFILEINFOW info;
   if ((shell::SHGetFileInfo(wstrFileIn, 0, &info, sizeof(info),
                             SHGFI_ATTRIBUTES) == 0) || !(info.dwAttributes & SFGAO_LINK))
   {
      return FALSE;
   }

   HRESULT hr ;
   if (FAILED(hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                    (LPVOID*)&psl)))
   {
      return FALSE;
   }

   IPersistFile *ppf;
   if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf)))
   {
      if (SUCCEEDED(ppf->Load(wstrFileIn, STGM_READ)))
      {
         /* Resolve the link, this may post UI to find the link */
         if (SUCCEEDED(psl->Resolve(pinteraction == nullptr ? nullptr : (oswindow) pinteraction->get_os_data(),
                                    SLR_ANY_MATCH | (pinteraction == nullptr ? (SLR_NO_UI | (8400 << 16)) : 0))))
         {
            wstrFileOut.alloc(MAX_PATH);
            bool bOk;
            if(SUCCEEDED(psl->GetPath(wstrFileOut, MAX_PATH, nullptr, 0)))
            {
               bOk = true;
               wstrFileOut.release_string_buffer();
               strTarget = ::str::international::unicode_to_utf8((const widechar *) wstrFileOut);
            }
            else
            {
               bOk = false;
            }
            ppf->Release();
            psl->Release();
            return bOk;
         }
      }
      ppf->Release();
   }
   psl->Release();
   return FALSE;

#else

   __throw(todo());


#endif

}


