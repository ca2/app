#include "framework.h"
#include "_android.h"

#include <fcntl.h>
#undef USE_MISC

#include <dlfcn.h>
#include <link.h>
#include <ctype.h>

#include <sys/stat.h>


bool CLASS_DECL_APEX windows_full_path(wstring& wstrFullPath, const wstring& wstrPath);

struct errentry
{
   unsigned long oscode;   /* OS return value */
   int sysv_errno;  /* ::apexacmesystem() V error code */
};
//#elif defined(MACOS)
////#include <dlfcn.h>
//#endif

//__STATIC inline bool IsDirSep(WCHAR ch)
//{
//
//   return (ch == '\\' || ch == '/');
//
//}


namespace android
{


   
   bool file_get_status(::file::file_status & rStatus, const ::file::path & path)
   {

      // attempt to fully qualify path first

      wstring wstrFullName;

      wstring wstrFileName;

      wstrFileName = utf8_to_unicode(path);

      if (!windows_full_path(wstrFullName, wstrFileName))
      {

         rStatus.m_strFullName.empty();

         return false;

      }

      unicode_to_utf8(rStatus.m_strFullName, wstrFullName);

      struct stat st;

      if (stat(path, &st) == -1)
      {

         return false;

      }
      //if (hFind == INVALID_HANDLE_VALUE)
      // return false;
      //VERIFY(FindClose(hFind));

      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      //rStatus.m_attribute = (unsigned char) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

      rStatus.m_attribute = 0;

      // get just the low ::u32 of the file size
      //ASSERT(findFileData.nFileSizeHigh == 0);
      //rStatus.m_size = (int)findFileData.nFileSizeLow;

      rStatus.m_size = st.st_size;

      // convert times as appropriate
      /*rStatus.m_ctime = ::earth::time(findFileData.ftCreationTime);
      rStatus.m_atime = ::earth::time(findFileData.ftLastAccessTime);
      rStatus.m_mtime = ::earth::time(findFileData.ftLastWriteTime);*/
      rStatus.m_ctime = ::earth::time(st.st_mtime);
      rStatus.m_atime = ::earth::time(st.st_atime);
      rStatus.m_mtime = ::earth::time(st.st_ctime);

      if (rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;

      if (rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;

      return true;

   }


   file::file()
   {

      m_iFile = (::u32) hFileNull;

   }

   //file::file(::particle * pparticle, i32 hFile) :
   //   ::object(pparticle)
   //{

   //   m_iFile = hFile;

   //}

   //file::file(::particle * pparticle, const char * lpszFileName, ::u32 nOpenFlags) :
   //   ::object(pparticle)
   //{

   //   ASSERT(is_string_ok(lpszFileName));

   //   if(!open(lpszFileName, nOpenFlags))
   //      throw ::exception(::file::exception(::error_none, -1, lpszFileName));

   //}

   file::~file()
   {

      if (m_iFile != hFileNull)
         close();

   }

   //file_pointer file::Duplicate() const
   //{
   //   ASSERT_VALID(this);
   //   ASSERT(m_iFile != hFileNull);

   //   i32 iNew = dup(m_iFile);

   //   if(iNew == -1)
   //      return nullptr;

   //   file* pFile = aaa_primitive_new file(get_app(), iNew);
   //   pFile->m_iFile = (::u32)iNew;
   //   ASSERT(pFile->m_iFile != hFileNull);
   //   return pFile;
   //}

   ::extended::status file::open(const ::file::path & lpszFileName, ::file::e_open eopen)
   {

      ::file::e_open eopen(efileopenParam);

      if (m_iFile != hFileNull)
         close();

      ASSERT_VALID(this);
      ASSERT(is_string_ok(lpszFileName));
      ASSERT(!(eopen & ::file::e_open_text));   // text mode not supported

      // file objects are always binary and CreateFile does not need flag
      eopen -= ::file::e_open_binary;


      if((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         pcontext->directory()->create(lpszFileName.folder());

      }

      m_iFile = (::u32)hFileNull;
      m_strFileName.empty();

      m_strFileName     = lpszFileName;

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      // ::collection::map read/write mode
      ASSERT((::file::e_open_read | ::file::e_open_write | ::file::e_open_read_write) == 3);
      ::u32 dwFlags =  0;
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwFlags |=  O_RDONLY;
         break;
      case ::file::e_open_write:
         dwFlags |=  O_WRONLY ;
         break;
      case ::file::e_open_read_write:
         dwFlags |=  O_RDWR;
         break;
      default:
         dwFlags |=  O_RDONLY;
         break;
      }

      // ::collection::map share mode
      //::u32 dwShareMode = 0;
      switch (eopen & 0x70)    // ::collection::map compatibility mode to exclusive
      {
      default:
         ASSERT(false);  // invalid share mode?
      case ::file::e_open_share_compat:
      case ::file::e_open_share_exclusive:
         //dwShareMode = 0;
         break;
      case ::file::e_open_share_deny_write:
         //dwFlags |= O_SHLOCK;
         break;
      case ::file::e_open_share_deny_read:
//         dwFlags |= O_EXLOCK;
         break;
      case ::file::e_open_share_deny_none:
         //dwFlags = FILE_SHARE_WRITE|FILE_SHARE_READ;
         break;
      }

      if(eopen & ::file::e_open_create)
      {
         dwFlags |= O_CREAT;
         if(!(eopen & ::file::e_open_no_truncate))
            dwFlags |= O_TRUNC;
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;

      // attempt file creation
      //HANDLE hFile = shell::CreateFile(utf8_to_unicode(m_strFileName), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      i32 hFile = ::open(m_strFileName, dwFlags, dwPermission); //::open(m_strFileName, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      if(hFile == -1)
      {

         static struct errentry errtable[] =
         {
            { ERROR_INVALID_FUNCTION,       EINVAL },  /* 1 */
            { ERROR_FILE_NOT_FOUND,         ENOENT },  /* 2 */
            { ERROR_PATH_NOT_FOUND,         ENOENT },  /* 3 */
            { ERROR_TOO_MANY_OPEN_FILES,    EMFILE },  /* 4 */
            { ERROR_ACCESS_DENIED,          EACCES },  /* 5 */
            { ERROR_INVALID_HANDLE,         EBADF },  /* 6 */
            { ERROR_ARENA_TRASHED,          ENOMEM },  /* 7 */
            { ERROR_NOT_ENOUGH_MEMORY,      ENOMEM },  /* 8 */
            { ERROR_INVALID_BLOCK,          ENOMEM },  /* 9 */
            { ERROR_BAD_ENVIRONMENT,        E2BIG },  /* 10 */
            { ERROR_BAD_FORMAT,             ENOEXEC },  /* 11 */
            { ERROR_INVALID_ACCESS,         EINVAL },  /* 12 */
            { ERROR_INVALID_DATA,           EINVAL },  /* 13 */
            { ERROR_INVALID_DRIVE,          ENOENT },  /* 15 */
            { ERROR_CURRENT_DIRECTORY,      EACCES },  /* 16 */
            { ERROR_NOT_SAME_DEVICE,        EXDEV },  /* 17 */
            { ERROR_NO_MORE_FILES,          ENOENT },  /* 18 */
            { ERROR_LOCK_VIOLATION,         EACCES },  /* 33 */
            { ERROR_BAD_NETPATH,            ENOENT },  /* 53 */
            { ERROR_NETWORK_ACCESS_DENIED,  EACCES },  /* 65 */
            { ERROR_BAD_NET_NAME,           ENOENT },  /* 67 */
            { ERROR_FILE_EXISTS,            EEXIST },  /* 80 */
            { ERROR_CANNOT_MAKE,            EACCES },  /* 82 */
            { ERROR_FAIL_I24,               EACCES },  /* 83 */
            { ERROR_INVALID_PARAMETER,      EINVAL },  /* 87 */
            { ERROR_NO_PROC_SLOTS,          EAGAIN },  /* 89 */
            { ERROR_DRIVE_LOCKED,           EACCES },  /* 108 */
            { ERROR_BROKEN_PIPE,            EPIPE },  /* 109 */
            { ERROR_DISK_FULL,              ENOSPC },  /* 112 */
            { ERROR_INVALID_TARGET_HANDLE,  EBADF },  /* 114 */
            { ERROR_INVALID_NAME,           ENOENT },  /* 123 */
            { ERROR_INVALID_HANDLE,         EINVAL },  /* 124 */
            { ERROR_WAIT_NO_CHILDREN,       ECHILD },  /* 128 */
            { ERROR_CHILD_NOT_COMPLETE,     ECHILD },  /* 129 */
            { ERROR_DIRECT_ACCESS_HANDLE,   EBADF },  /* 130 */
            { ERROR_NEGATIVE_SEEK,          EINVAL },  /* 131 */
            { ERROR_SEEK_ON_DEVICE,         EACCES },  /* 132 */
            { ERROR_DIR_NOT_EMPTY,          ENOTEMPTY },  /* 145 */
            { ERROR_NOT_LOCKED,             EACCES },  /* 158 */
            { ERROR_BAD_PATHNAME,           ENOENT },  /* 161 */
            { ERROR_MAX_THRDS_REACHED,      EAGAIN },  /* 164 */
            { ERROR_LOCK_FAILED,            EACCES },  /* 167 */
            { ERROR_ALREADY_EXISTS,         EEXIST },  /* 183 */
            { ERROR_FILENAME_EXCED_RANGE,   ENOENT },  /* 206 */
            { ERROR_NESTING_NOT_ALLOWED,    EAGAIN },  /* 215 */
            { ERROR_NOT_ENOUGH_QUOTA,       ENOMEM }    /* 1816 */
         };

         /* size of the table */
#define ERRTABLESIZE (sizeof(errtable)/sizeof(errtable[0]))
         set_last_error(-1);
         for (size_t u = 0; u < ERRTABLESIZE; u++)
         {
            if (errno == errtable[u].sysv_errno)
            {
               set_last_error(errtable[u].oscode);
               break;
            }
         }

         ::u32 dwLastError = ::get_last_error();

         if(dwLastError != ERROR_FILE_NOT_FOUND && dwLastError != ERROR_PATH_NOT_FOUND)
         {
            /*         if (pException != nullptr)
            {
            pException->create(this);
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = dwLastError;
            pfe->m_cause = ::win::file_exception::os_error_to_exception(pfe->m_lOsError);
            pfe->m_strFileName = lpszFileName;
            }
            return false;
            }
            else
            {*/


            //return __allocate ::file::exception(::error_os_error_to_exception(dwLastError), dwLastError, m_strFileName, nOpenFlags);
            return ::os_error_to_status(dwLastError);

            //}

         }

         /*try
         {
            get_app()->system()->m_spfilesystem.m_p->FullPath(m_wstrFileName, m_wstrFileName);
         }
         catch(...)
         {
            return false;
         }

         m_strFileName = unicode_to_utf8(m_wstrFileName);

         hFile = ::open(m_strFileName, nOpenFlags);*/

         if (hFile == -1)
         {
            /*if (pException != nullptr)
            {
            pException->create(this);
            ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
            if(pfe != nullptr)
            {
            pfe->m_lOsError = ::get_last_error();
            pfe->m_cause = ::win::file_exception::os_error_to_exception(pfe->m_lOsError);
            pfe->m_strFileName = lpszFileName;
            }
            return false;
            }
            else
            {*/


            ::u32 dwLastError = ::get_last_error();
            //return __allocate ::file::exception(::os_error_to_status(dwLastError), dwLastError, m_strFileName, nOpenFlags);
            return ::os_error_to_status(dwLastError);

            //}

         }

      }

      m_iFile = (i32)hFile;

      return ::success;

   }


   memsize file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(lpBuf != nullptr);
      ASSERT(is_memory_segment_ok(lpBuf, nCount));

      memsize pos = 0;
      memsize sizeRead = 0;
      memsize readNow;
      while(nCount > 0)
      {
         readNow = (size_t) minimum(I32_MAXIMUM, nCount);
         i32 iRead = ::read(m_iFile, &((unsigned char *)lpBuf)[pos], readNow);
         if(iRead < 0)
         {
            i32 iError = errno;
            if(iError == EAGAIN)
            {

            }
            ::throw ::file::exception(errno, m_path);
         }
         else if(iRead == 0)
         {
            break;
         }

         nCount -= iRead;
         pos += iRead;
         sizeRead += iRead;
      }

      return sizeRead;
   }

   void file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      if (nCount == 0)
         return;     // avoid Win32 "null-write" option

      ASSERT(lpBuf != nullptr);
      ASSERT(is_memory_segment_ok(lpBuf, nCount, false));

      memsize pos = 0;
      while(nCount > 0)
      {
         i32 iWrite = ::write(m_iFile, &((const unsigned char *)lpBuf)[pos], (size_t) minimum(I32_MAXIMUM, nCount));
         if(iWrite < 0)
            ::file::throw_os_error( (int)::get_last_error(), m_strFileName);
         nCount -= iWrite;
         pos += iWrite;
      }

      // Win32s will not return an error all the time (usually DISK_FULL)
      //if (iWrite != nCount)
      //vfxThrowFileexception(::error_disk_full, -1, m_strFileName);
   }

   filesize file::seek(filesize lOff, ::enum_seek eseek)
   {

      if (m_iFile == hFileNull)
      {

         throw ::file::exception(error_bad_argument, -1, m_path);

      }

      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);
      ASSERT(nFrom == ::e_seek_set || nFrom == ::e_seek_end || nFrom == ::e_seek_current);
      ASSERT(::e_seek_set == SEEK_SET && ::e_seek_end == SEEK_END && ::e_seek_current == SEEK_CUR);

      int lLoOffset = lOff & 0xffffffff;
      //int lHiOffset = (lOff >> 32) & 0xffffffff;

      filesize posNew = ::lseek64(m_iFile, lLoOffset, (::u32)nFrom);
//      posNew |= ((filesize) lHiOffset) << 32;
      if(posNew  == (filesize)-1)
         ::file::throw_os_error(::os_error_to_status((int)::get_last_error()));

      return posNew;
   }

   filesize file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      int lLoOffset = 0;
//      int lHiOffset = 0;

      filesize pos = ::lseek64(m_iFile, lLoOffset, SEEK_CUR);
      //    pos |= ((filesize)lHiOffset) << 32;
      if(pos  == (filesize)-1)
         ::file::throw_os_error( (int)::get_last_error());

      return pos;
   }

   void file::flush()
   {

      /*      ::open
            ::read
            ::write

            access the system directly no buffering : direct I/O - efficient for large writes - innefficient for lots of single unsigned char writes

            */

      /*ASSERT_VALID(this);

      /*  if (m_iFile == hFileNull)
         return;

      if (!::FlushFileBuffers((HANDLE)m_iFile))
         ::file::throw_os_error( (int)::get_last_error());*/
   }

   void file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      bool bError = false;
      if (m_iFile != hFileNull)
         bError = ::close(m_iFile) == -1;

      m_iFile = (::u32) hFileNull;
      m_strFileName.empty();

      if (bError)
         ::file::throw_os_error( (int)::get_last_error());
   }


   //void file::Abort()
   //{
   //   ASSERT_VALID(this);
   //   if (m_iFile != hFileNull)
   //   {
   //      // close but ignore errors
   //      ::close(m_iFile);
   //      m_iFile = (::u32)hFileNull;
   //   }
   //   m_strFileName.empty();
   //}

   void file::lock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      /*if (!::LockFile((HANDLE)m_iFile, lower_u32(dwPos), upper_u32(dwPos), lower_u32(dwCount), upper_u32(dwCount)))
         ::file::throw_os_error( (int)::get_last_error());*/
   }

   void file::unlock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      /*      if (!::UnlockFile((HANDLE)m_iFile,  lower_u32(dwPos), upper_u32(dwPos), lower_u32(dwCount), upper_u32(dwCount)))
               ::file::throw_os_error( (int)::get_last_error());*/
   }

   void file::set_size(filesize dwNewLen)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != hFileNull);

      seek((int)dwNewLen, (::enum_seek)::e_seek_set);

#ifdef __LP64
      int iError = ::ftruncate64(m_iFile, dwNewLen);
      if (iError == -1)
         ::file::throw_os_error( (int)::get_last_error());
#else
      int iError = ::ftruncate(m_iFile, dwNewLen);
      if (iError == -1)
         ::file::throw_os_error( (int)::get_last_error());
#endif
   }

   filesize file::get_size() const
   {
      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      file* pFile = (file*)this;
      dwCur = pFile->seek(0L, ::e_seek_current);
      dwLen = pFile->seek_to_end();
      VERIFY(dwCur == (u64)pFile->seek((filesize) dwCur, ::e_seek_set));

      return (filesize) dwLen;
   }

   //// file does not support direct buffering (CMemFile does)
   //u64 file::GetBufferPtr(::u32 nCommand, u64 /*nCount*/,
   //                            void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   //{
   //   ASSERT(nCommand == bufferCheck);
   //   __UNREFERENCED_PARAMETER(nCommand);    // not used in retail build

   //   return 0;   // no support
   //}

   /*
   void PASCAL file::Rename(const char * lpszOldName, const char * lpszNewName)
   {
   if (!::MoveFile((char *)lpszOldName, (char *)lpszNewName))
   ::win::file::throw_os_error( (int)::get_last_error());
   }

   void PASCAL file::erase(const char * lpszFileName)
   {
   if (!::DeleteFile((char *)lpszFileName))
   ::win::file::throw_os_error( (int)::get_last_error());
   }
   */





   /////////////////////////////////////////////////////////////////////////////
   // file diagnostics


   void file::assert_ok() const
   {
      ::file::file::assert_ok();
      // we permit the descriptor m_iFile to be any value for derived classes
   }

   void file::dump(dump_context & dumpcontext) const
   {
      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_iFile;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }





   //string file::GetFileName() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return status.m_strFullName.name();
   //}

   //string file::GetFileTitle() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return status.m_strFullName.title();
   //}

   ::file::path file::get_file_path() const
   {
      
      ASSERT_VALID(this);
      
      ::file::file_status status;
      
      get_status(status);

      return status.m_strFullName;

   }




   /////////////////////////////////////////////////////////////////////////////
   // FileException




   //void PASCAL ::file::throw_os_error(::particle * pparticle, int lOsError, const char * lpszFileName /* = nullptr */)
   //{
   //   if (lOsError != 0)
   //      vfxThrowFileexception(file_exception::os_error_to_exception(lOsError), lOsError, lpszFileName);
   //}

   //void PASCAL file_exception::ThrowErrno(::particle * pparticle, i32 nErrno, const char * lpszFileName /* = nullptr */)
   //{
   //   if (nErrno != 0)
   //      vfxThrowFileexception(file_exception::errno_status(nErrno), errno, lpszFileName);
   //}





   // IMPLEMENT_DYNAMIC(WinFileException, ::exception)

   /////////////////////////////////////////////////////////////////////////////




   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool file::get_status(::file::file_status& rStatus) const
   {
      ASSERT_VALID(this);

      //memory_set(&rStatus, 0, sizeof(::file::file_status));

      // copy file name from cached m_strFileName
      rStatus.m_strFullName = m_strFileName;

      if (m_iFile != hFileNull)
      {
         struct stat st;
         if(fstat(m_iFile, &st) == -1)
            return false;
         // get time ::e_seek_current file size
         /*FILETIME ftCreate, ftAccess, ftModify;
         if (!::GetFileTime((HANDLE)m_iFile, &ftCreate, &ftAccess, &ftModify))
            return false;*/

         rStatus.m_size = st.st_size;

         rStatus.m_attribute = 0;

         rStatus.m_ctime = ::earth::time(st.st_mtime);
         rStatus.m_atime = ::earth::time(st.st_atime);
         rStatus.m_mtime = ::earth::time(st.st_ctime);

         if (rStatus.m_ctime.get_time() == 0)
            rStatus.m_ctime = rStatus.m_mtime;

         if (rStatus.m_atime.get_time() == 0)
            rStatus.m_atime = rStatus.m_mtime;
      }
      return true;
   }





   bool file::is_opened() const
   {
      return m_iFile != hFileNull;
   }


   void file::set_file_path(const ::file::path & path)
   {

      m_strFileName = path;

   }

   //u64 file::ReadHuge(void * lpBuffer, u64 dwCount)
   //{

   //   return  read(lpBuffer, dwCount);

   //}

   //void file::WriteHuge(const void * lpBuffer, u64 dwCount)
   //{

   //   write(lpBuffer, dwCount);

   //}



} // namespace win




#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)




// turn a file, relative path or other into an absolute path
bool CLASS_DECL_APEX windows_full_path(wstring & wstrFullPath, const wstring & wstrPath)
{

   wstrFullPath = wstrPath;

   return true;

}

//
//void CLASS_DECL_APEX vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, int lOsError, const char * lpszFileName /* == nullptr */)
//{
//
//   throw ::exception(::file::exception(ecause, lOsError, lpszFileName));
//
//}


namespace android
{

   void PASCAL file_errno_to_exception(i32 nErrno)
   {
      switch(nErrno)
      {
      case EPERM:
      case EACCES:
         return ::error_file_access_denied;
      case EBADF:
         return ::error_invalid_file;
      case EDEADLOCK:
         return ::error_file_sharing_violation;
      case EMFILE:
         return ::error_too_many_open_files;
      case ENOENT:
      case ENFILE:
         return ::error_file_not_found;
      case ENOSPC:
         return ::error_disk_full;
      case EINVAL:
      case EIO:
         return ::error_hard_io;
      default:
         return ::error_file;
      }

   }


} // namespace android



