#include "framework.h"
//#include "aura/node/ansios/ansios.h"
#include "_linux.h"


#include <fcntl.h>
#undef USE_MISC
#include <unistd.h>


#include <link.h>


#include <ctype.h>
#include <sys/stat.h>

//#elif defined(MACOS)
//#include <dlfcn.h>
//#endif

/*__STATIC inline bool IsDirSep(WCHAR ch)
{

   return (ch == '\\' || ch == '/');

}*/


namespace linux
{


   file::file()
   {

      m_iFile = INVALID_FILE;

   }


//   file::file(::object * pobject, int iFile) :
//      ::object(pobject)
//   {
//
//      m_iFile = iFile;
//
//   }
//
//
//   file::file(::object * pobject, const ::file::path & pszFileName, const enumeration < ::file::e_open > & eopen) :
//      ::object(pobject)
//   {
//
//      m_iFile = INVALID_FILE;
//
//      if(!open(pszFileName, eopen))
//      {
//
//         __throw(::file::exception(::error_file, -1, pszFileName));
//
//      }
//
//
//   }


   file::~file()
   {

      if (m_iFile != INVALID_FILE)
         close();

   }

//   __pointer(::file::file) file::Duplicate() const
//
//   {
//
//      i32 iNew = dup(m_iFile);
//
//      if(iNew == INVALID_FILE)
//         return nullptr;
//
//      auto pFile  = __new(file(get_context_application(), iNew));
//      pFile->m_iFile = (::u32)iNew;
//      ASSERT(pFile->m_iFile != INVALID_FILE);
//      return pFile;
//
//   }
//

   ::status::result file::open(const ::file::path & pszFileName, const enumeration < ::file::e_open > & openParam)
   {

      if (m_iFile != INVALID_FILE)
      {

         close();

      }


      auto eopen = openParam;


      ASSERT(__is_valid_string(pszFileName));


      // file objects are always binary and CreateFile does not need flag
      eopen -= ::file::e_open_binary;


      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         Context.dir().mk(pszFileName.folder());


      }

      m_iFile = INVALID_FILE;
      m_path.Empty();

      m_path     = pszFileName;


      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      // ::collection::map read/write mode
      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
      ::u32 dwFlags =  0;
      switch (eopen & ::file::e_open_read_write)
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
      ::u32 dwShareMode = 0;
      switch (eopen & ::file::e_open_share_mask)    // ::collection::map compatibility mode to exclusive
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
      else if(eopen & ::file::e_open_truncate)
      {
         dwFlags |= O_TRUNC;
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;
      dwPermission |= S_IROTH | S_IROTH;

      // attempt file creation
      //HANDLE hFile = shell::CreateFile(::str::international::utf8_to_unicode(m_path), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);
      int iFile = ::open(m_path, dwFlags, dwPermission); //::open(m_path, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);

      if(iFile == INVALID_FILE)
      {

         int iError = errno;

         ::u32 dwLastError = ::get_last_error();

         //return //::fesp(get_context_application(), file_exception::os_error_to_exception(dwLastError), dwLastError, m_path);

         return ::file::errno_to_status(iError);

      }

      m_iFile = iFile;

      return ::success;

   }


   memsize file::read(void * pdata, memsize nCount)

   {

      ASSERT(m_iFile != INVALID_FILE);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(pdata != nullptr);

      ASSERT(__is_valid_address(pdata, nCount));


      memsize pos = 0;
      memsize sizeRead = 0;
      memsize readNow;
      while(nCount > 0)
      {
         readNow = (size_t) min(0x7fffffff, nCount);
         i32 iRead = ::read(m_iFile, &((u8 *)pdata)[pos], readNow);

         if(iRead < 0)
         {
            i32 iError = errno;
            if(iError == EAGAIN)
            {

            }
            ::file::throw_errno( errno);
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

   void file::write(const void * pdata, memsize nCount)

   {

      ASSERT(m_iFile != INVALID_FILE);

      if (nCount == 0)
         return;     // avoid Win32 "null-write" option

      ASSERT(pdata != nullptr);

      ASSERT(__is_valid_address(pdata, nCount, false));


      memsize pos = 0;
      while(nCount > 0)
      {
         i32 iWrite = ::write(m_iFile, &((const u8 *)pdata)[pos], (size_t) min(0x7fffffff, nCount));

         if(iWrite < 0)
            throw_errno(errno, m_path);
         nCount -= iWrite;
         pos += iWrite;
      }

      // Win32s will not return an error all the time (usually DISK_FULL)
      //if (iWrite != nCount)
      //vfxThrowFileexception(::file::exception::diskFull, -1, m_path);
   }

   filesize file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      if(m_iFile == INVALID_FILE)
         throw_errno(errno, m_path);


      ASSERT(m_iFile != INVALID_FILE);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == SEEK_SET && ::file::seek_end == SEEK_END && ::file::seek_current == SEEK_CUR);

      ::i32 lLoOffset = lOff & 0xffffffff;
      //::i32 lHiOffset = (lOff >> 32) & 0xffffffff;

      filesize posNew = ::lseek64(m_iFile, lLoOffset, (::u32)nFrom);
//      posNew |= ((filesize) lHiOffset) << 32;
      if(posNew  == (filesize)-1)
         throw_errno(errno, m_path);

      return posNew;
   }

   filesize file::get_position() const
   {

      ASSERT(m_iFile != INVALID_FILE);

      ::i32 lLoOffset = 0;
//      ::i32 lHiOffset = 0;

      filesize pos = ::lseek64(m_iFile, lLoOffset, SEEK_CUR);
      //    pos |= ((filesize)lHiOffset) << 32;
      if(pos  == (filesize)-1)
         throw_errno(errno, m_path);

      return pos;
   }

   void file::Flush()
   {

      /*      ::open
            ::read
            ::write

            access the system directly no buffering : direct I/O - efficient for large writes - innefficient for lots of single byte writes

            */

//      if (m_iFile == INVALID_FILE)
//         return;
//
//      if (!::FlushFileBuffers((HANDLE)m_iFile))
//         throw_errno(errno, m_path);
   }

   void file::close()
   {

      bool bError = false;

      if (m_iFile != INVALID_FILE)
         bError = ::close(m_iFile) == -1;

      m_iFile = INVALID_FILE;

      m_path.Empty();

      if (bError)
         throw_errno(errno, m_path);

   }


   void file::Abort()
   {

      if (m_iFile != INVALID_FILE)
      {

         ::close(m_iFile);

         m_iFile = INVALID_FILE;

      }

      m_path.Empty();

   }


   void file::LockRange(filesize dwPos, filesize dwCount)
   {

      ASSERT(m_iFile != INVALID_FILE);

   }


   void file::UnlockRange(filesize dwPos, filesize dwCount)
   {

      ASSERT(m_iFile != INVALID_FILE);

   }


   void file::set_size(filesize dwNewLen)
   {

      ASSERT(m_iFile != INVALID_FILE);

      seek((::i32)dwNewLen, (::file::e_seek)::file::seek_begin);

      if (::ftruncate64(m_iFile, dwNewLen) == -1)
      {

         throw_errno(errno, m_path);

      }

   }


   filesize file::get_size() const
   {

      filesize dwLen, dwCur;

      // seek is a non const operation
      file* pFile = (file*)this;
      dwCur = pFile->seek(0L, ::file::seek_current);
      dwLen = pFile->seek_to_end();
      VERIFY(dwCur == (u64)pFile->seek((filesize) dwCur, ::file::seek_begin));

      return (filesize) dwLen;

   }


   // file does not support direct buffering (CMemFile does)
   u64 file::GetBufferPtr(::u32 /*nCommand*/, u64 /*nCount*/, void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   {

      //ASSERT(nCommand == bufferCheck);

      //UNUSED(nCommand);    // not used in retail build

      return 0;   // no support

   }


   void file::assert_valid() const
   {

      ::file::file::assert_valid();

   }


   void file::dump(dump_context & dumpcontext) const
   {

      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_iFile;
      dumpcontext << " and name \"" << m_path << "\"";
      dumpcontext << "\n";

   }



   string file::GetFileName() const
   {



      ::file::file_status status;

      GetStatus(status);

      return status.m_strFullName.name();

   }


   string file::GetFileTitle() const
   {



      ::file::file_status status;

      GetStatus(status);

      return status.m_strFullName.title();

   }


   string file::GetFilePath() const
   {


      ::file::file_status status;
      GetStatus(status);
      return status.m_strFullName;
   }




   /////////////////////////////////////////////////////////////////////////////
   // FileException




//   void PASCAL file_exception::throw_os_error(::i32 lOsError, const char * pszFileName /* = nullptr */)

//   {
//      if (lOsError != 0)
//         ::file::throw_os_error(file_exception::os_error_to_exception(lOsError), lOsError, pszFileName);

//   }

//   void PASCAL file_exception::ThrowErrno(i32 nErrno, const char * pszFileName /* = nullptr */)

//   {
//      if (nErrno != 0)
//         vfxThrowFileexception(file_exception::errno_to_status(nErrno), errno, pszFileName);

//   }



//   ::e_status PASCAL file_exception::os_error_to_exception(::i32 lOsErr)
//   {
//      // NT Error codes
//      switch ((::u32)lOsErr)
//      {
//      case NO_ERROR:
//         return ::file::exception::undefined;
//      case ERROR_FILE_NOT_FOUND:
//         return ::file::exception::fileNotFound;
//      case ERROR_PATH_NOT_FOUND:
//         return ::file::exception::badPath;
//      case ERROR_TOO_MANY_OPEN_FILES:
//         return ::file::exception::tooManyOpenFiles;
//      case ERROR_ACCESS_DENIED:
//         return ::file::exception::accessDenied;
//      case ERROR_INVALID_HANDLE:
//         return ::file::exception::fileNotFound;
//      case ERROR_BAD_FORMAT:
//         return ::file::exception::invalidFile;
//      case ERROR_INVALID_ACCESS:
//         return ::file::exception::accessDenied;
//      case ERROR_INVALID_DRIVE:
//         return ::file::exception::badPath;
//      case ERROR_CURRENT_DIRECTORY:
//         return ::file::exception::removeCurrentDir;
//      case ERROR_NOT_SAME_DEVICE:
//         return ::file::exception::badPath;
//      case ERROR_NO_MORE_FILES:
//         return ::file::exception::fileNotFound;
//      case ERROR_WRITE_PROTECT:
//         return ::file::exception::accessDenied;
//      case ERROR_BAD_UNIT:
//         return ::file::exception::hardIO;
//      case ERROR_NOT_READY:
//         return ::file::exception::hardIO;
//      case ERROR_BAD_COMMAND:
//         return ::file::exception::hardIO;
//      case ERROR_CRC:
//         return ::file::exception::hardIO;
//      case ERROR_BAD_LENGTH:
//         return ::file::exception::badSeek;
//      case ERROR_SEEK:
//         return ::file::exception::badSeek;
//      case ERROR_NOT_DOS_DISK:
//         return ::file::exception::invalidFile;
//      case ERROR_SECTOR_NOT_FOUND:
//         return ::file::exception::badSeek;
//      case ERROR_WRITE_FAULT:
//         return ::file::exception::accessDenied;
//      case ERROR_READ_FAULT:
//         return ::file::exception::badSeek;
//      case ERROR_SHARING_VIOLATION:
//         return ::file::exception::sharingViolation;
//      case ERROR_LOCK_VIOLATION:
//         return ::file::exception::lockViolation;
//      case ERROR_WRONG_DISK:
//         return ::file::exception::badPath;
//      case ERROR_SHARING_BUFFER_EXCEEDED:
//         return ::file::exception::tooManyOpenFiles;
//      case ERROR_HANDLE_EOF:
//         return ::file::exception::endOfFile;
//      case ERROR_HANDLE_DISK_FULL:
//         return ::file::exception::diskFull;
//      case ERROR_DUP_NAME:
//         return ::file::exception::badPath;
//      case ERROR_BAD_NETPATH:
//         return ::file::exception::badPath;
//      case ERROR_NETWORK_BUSY:
//         return ::file::exception::accessDenied;
//      case ERROR_DEV_NOT_EXIST:
//         return ::file::exception::badPath;
//      case ERROR_ADAP_HDW_ERR:
//         return ::file::exception::hardIO;
//      case ERROR_BAD_NET_RESP:
//         return ::file::exception::accessDenied;
//      case ERROR_UNEXP_NET_ERR:
//         return ::file::exception::hardIO;
//      case ERROR_BAD_REM_ADAP:
//         return ::file::exception::invalidFile;
//      case ERROR_NO_SPOOL_SPACE:
//         return ::file::exception::directoryFull;
//      case ERROR_NETNAME_DELETED:
//         return ::file::exception::accessDenied;
//      case ERROR_NETWORK_ACCESS_DENIED:
//         return ::file::exception::accessDenied;
//      case ERROR_BAD_DEV_TYPE:
//         return ::file::exception::invalidFile;
//      case ERROR_BAD_NET_NAME:
//         return ::file::exception::badPath;
//      case ERROR_TOO_MANY_NAMES:
//         return ::file::exception::tooManyOpenFiles;
//      case ERROR_SHARING_PAUSED:
//         return ::file::exception::badPath;
//      case ERROR_REQ_NOT_ACCEP:
//         return ::file::exception::accessDenied;
//      case ERROR_FILE_EXISTS:
//         return ::file::exception::accessDenied;
//      case ERROR_CANNOT_MAKE:
//         return ::file::exception::accessDenied;
//      case ERROR_ALREADY_ASSIGNED:
//         return ::file::exception::badPath;
//      case ERROR_INVALID_PASSWORD:
//         return ::file::exception::accessDenied;
//      case ERROR_NET_WRITE_FAULT:
//         return ::file::exception::hardIO;
//      case ERROR_DISK_CHANGE:
//         return ::file::exception::fileNotFound;
//      case ERROR_DRIVE_LOCKED:
//         return ::file::exception::lockViolation;
//      case ERROR_BUFFER_OVERFLOW:
//         return ::file::exception::badPath;
//      case ERROR_DISK_FULL:
//         return ::file::exception::diskFull;
//      case ERROR_NO_MORE_SEARCH_HANDLES:
//         return ::file::exception::tooManyOpenFiles;
//      case ERROR_INVALID_TARGET_HANDLE:
//         return ::file::exception::invalidFile;
//      case ERROR_INVALID_CATEGORY:
//         return ::file::exception::hardIO;
//      case ERROR_INVALID_NAME:
//         return ::file::exception::badPath;
//      case ERROR_INVALID_LEVEL:
//         return ::file::exception::badPath;
//      case ERROR_NO_VOLUME_LABEL:
//         return ::file::exception::badPath;
//      case ERROR_NEGATIVE_SEEK:
//         return ::file::exception::badSeek;
//      case ERROR_SEEK_ON_DEVICE:
//         return ::file::exception::badSeek;
//      case ERROR_DIR_NOT_ROOT:
//         return ::file::exception::badPath;
//      case ERROR_DIR_NOT_EMPTY:
//         return ::file::exception::removeCurrentDir;
//      case ERROR_LABEL_TOO_LONG:
//         return ::file::exception::badPath;
//      case ERROR_BAD_PATHNAME:
//         return ::file::exception::badPath;
//      case ERROR_LOCK_FAILED:
//         return ::file::exception::lockViolation;
//      case ERROR_BUSY:
//         return ::file::exception::accessDenied;
//      case ERROR_INVALID_ORDINAL:
//         return ::file::exception::invalidFile;
//      case ERROR_ALREADY_EXISTS:
//         return ::file::exception::accessDenied;
//      case ERROR_INVALID_EXE_SIGNATURE:
//         return ::file::exception::invalidFile;
//      case ERROR_BAD_EXE_FORMAT:
//         return ::file::exception::invalidFile;
//      case ERROR_FILENAME_EXCED_RANGE:
//         return ::file::exception::badPath;
//      case ERROR_META_EXPANSION_TOO_LONG:
//         return ::file::exception::badPath;
//      case ERROR_DIRECTORY:
//         return ::file::exception::badPath;
//      case ERROR_OPERATION_ABORTED:
//         return ::file::exception::hardIO;
//      case ERROR_IO_INCOMPLETE:
//         return ::file::exception::hardIO;
//      case ERROR_IO_PENDING:
//         return ::file::exception::hardIO;
//      case ERROR_SWAPERROR:
//         return ::file::exception::accessDenied;
//      default:
//         return ::file::exception::type_generic;
//      }
//   }
//

   // IMPLEMENT_DYNAMIC(WinFileException, ::exception::aura)

   /////////////////////////////////////////////////////////////////////////////




   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool file::GetStatus(::file::file_status& rStatus) const
   {


      //__memset(&rStatus, 0, sizeof(::file::file_status));

      // copy file name from cached m_path
      rStatus.m_strFullName = m_path;

      if (m_iFile != INVALID_FILE)
      {
         struct stat st;
         if(fstat(m_iFile, &st) == -1)
            return false;

         rStatus.m_size = st.st_size;

         rStatus.m_attribute = 0;

         rStatus.m_ctime = ::datetime::time(st.st_mtime);
         rStatus.m_atime = ::datetime::time(st.st_atime);
         rStatus.m_mtime = ::datetime::time(st.st_ctime);

         if (rStatus.m_ctime.get_time() == 0)
            rStatus.m_ctime = rStatus.m_mtime;

         if (rStatus.m_atime.get_time() == 0)
            rStatus.m_atime = rStatus.m_mtime;
      }
      return true;
   }



   bool file::IsOpened()
   {
      return m_iFile != INVALID_FILE;
   }


   void file::SetFilePath(const char * pszNewName)

   {


      m_path = pszNewName;

   }

   u64 file::ReadHuge(void * pBuffer, u64 dwCount)

   {

      return  read(pBuffer, dwCount);


   }

   void file::WriteHuge(const void * pBuffer, u64 dwCount)

   {

      write(pBuffer, dwCount);


   }



} // namespace linux




#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)




// turn a file, relative path or other into an absolute path
bool CLASS_DECL_AXIS vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
// pszPathOut = buffer of _MAX_PATH

// pszFileIn = file, relative path or absolute path

// (both in ANSI character set)
{


   wstrFullPath = wstrPath;


   return true;
}

CLASS_DECL_AXIS void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{

   link_map * plm;

   dlinfo(hInst, RTLD_DI_LINKMAP, &plm);

   strShortName = plm->l_name;


}


CLASS_DECL_AXIS bool vfxResolveShortcut(string & strTarget, const char * pszSource, __pointer(::user::primitive) puiMessageParentOptional)
{



   char realname[_POSIX_PATH_MAX * 4];
   i32 rc = 0;

   if(realpath(pszSource, realname) == 0)
      return false;

   strTarget = realname;

   return true;

}



