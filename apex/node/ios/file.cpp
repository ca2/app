#include "framework.h"
#include "_ios.h"

#include <fcntl.h>

#ifdef LINUX
#include <dlfcn.h>
#include <link.h>
#include <ctype.h>
#elif defined(__APPLE__)
#include <dlfcn.h>
#include <sys/stat.h>
#endif

//__STATIC inline bool IsDirSep(WCHAR ch)
//{
//
//   return (ch == '\\' || ch == '/');
//
//}


namespace ios
{


   file::file()
   {

      m_iFile = (::u32) hFileNull;

   }

//   file::file(::object * pobject, i32 hFile) :
//      ::object(pobject)
//   {
//
//      m_iFile = hFile;
//
////      m_bCloseOnDelete = true;
//
//   }
//
//   file::file(::object * pobject, const char * lpszFileName, ::u32 nOpenFlags) :
//      ::object(pobject)
//   {
//
//      ASSERT(__is_valid_string(lpszFileName));
//
//      if(!open(lpszFileName, nOpenFlags))
//         __throw(::file::exception(::file::exception::none, -1, lpszFileName));
//
//   }

   file::~file()
   {

//      if (m_iFile != (::u32)hFileNull && m_bCloseOnDelete)
      //       close();
      if (m_iFile != (::u32)hFileNull)
      {
       
         close();
      
      }

   }

//   __pointer(::file::file) file::Duplicate() const
//   {
//      ASSERT_VALID(this);
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      i32 iNew = dup(m_iFile);
//
//      if(iNew == -1)
//         return nullptr;
//
//      file* pFile = new file(get_application(), iNew);
//      pFile->m_iFile = (::u32)iNew;
//      ASSERT(pFile->m_iFile != (::u32)hFileNull);
////      pFile->m_bCloseOnDelete = m_bCloseOnDelete;
//      return pFile;
//   }

   ::extended::status file::open(const ::file::path& path, const ::file::e_open & eopenParam)
   {

      if (m_iFile != (::u32)hFileNull)
      {
         
         close();
         
      }
      
      auto eopen = eopenParam;

      ASSERT_VALID(this);
      ASSERT(!(eopen & ::file::e_open_text) );   // text mode not supported

      // file objects are always binary and CreateFile does not need flag
      eopen -= ::file::e_open_binary;


      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         if(!pcontext->m_papexcontext->dir().mk(path.folder()))
         {

            return { __new(::file::exception(::error_file_not_found, -1, -1, path, eopenParam)) };

         }

      }

      m_iFile = (::u32)hFileNull;
      
      m_strFileName.Empty();

      m_strFileName = path;
      
      m_wstrFileName = ::str::international::utf8_to_unicode(m_strFileName);

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      
      ASSERT(::file::e_open_share_compat == 0);

      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
      
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

      switch (eopen & 0x70)
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

      if (eopen & ::file::e_open_create)
      {
         
         dwFlags |= O_CREAT;
         
         if(!(eopen & ::file::e_open_no_truncate))
         {
            
            dwFlags |= O_TRUNC;
            
         }
         
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;

      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;

      i32 hFile = ::open(m_strFileName, dwFlags, dwPermission);
      
      if(hFile == hFileNull)
      {

         int iErrNo = errno;

         if(iErrNo != ENOENT && iErrNo != ENFILE)
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


            //            vfxThrowFileexception(::macos::file_exception::os_error_to_exception(dwLastError), dwLastError, m_strFileName);
            return { __new(::file::exception(::file::errno_to_status(iErrNo), -1, -1, path, eopen)) };

            //}

         }

         /*try
          {
          get_application()->m_psystem->m_spfilesystem.m_p->FullPath(m_wstrFileName, m_wstrFileName);
          }
          catch(...)
          {
          return false;
          }

          m_strFileName = ::str::international::unicode_to_utf8(m_wstrFileName);

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


            //            vfxThrowFileexception(::macos::file_exception::os_error_to_exception(dwLastError), dwLastError, m_strFileName);

            return { __new(::file::exception(::file::errno_to_status(iErrNo), -1, -1, path, eopen)) };

            //}

         }

      }

      m_iFile = (i32)hFile;

      //      m_bCloseOnDelete = true;

      return ::success;

   }

   memsize file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(lpBuf != nullptr);
      ASSERT(__is_valid_address(lpBuf, nCount));

      memsize pos = 0;
      memsize sizeRead = 0;
      memsize readNow;
      while(nCount > 0)
      {
         
         readNow = (size_t) minimum(0x7fffffff, nCount);
         
         size_t iRead = ::read(m_iFile, &((byte *)lpBuf)[pos], readNow);
         
         if(iRead == -1)
         {
            
            i32 iError = errno;
            
            if(iError == EAGAIN)
            {

            }
            
            ::file::throw_os_error(iError, m_path);
            
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
      
      ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
      {
         
         return;     // avoid Win32 "null-write" option
         
      }

      ASSERT(lpBuf != nullptr);
      
      ASSERT(__is_valid_address(lpBuf, nCount, false));

      memsize pos = 0;
      
      while(nCount > 0)
      {
         
         size_t iWrite = ::write(m_iFile, &((const byte *)lpBuf)[pos], (size_t) minimum(0x7fffffff, nCount));
         
         if(iWrite == -1)
         {
            
            ::file::throw_os_error( (::i32)::get_last_error(), m_strFileName);
            
         }
         
         nCount -= iWrite;
         
         pos += iWrite;
         
      }

   }


   filesize file::seek(filesize lOff, ::enum_seek eseek)
   {

      if(m_iFile == (::u32)hFileNull)
         ::file::throw_os_error( (::i32)0);

      ASSERT_VALID(this);
      ASSERT(m_iFile != (::u32)hFileNull);
      ASSERT(nFrom == ::e_seek_set || nFrom == ::e_seek_end || nFrom == ::e_seek_current);
      ASSERT(::e_seek_set == SEEK_SET && ::e_seek_end == SEEK_END && ::e_seek_current == SEEK_CUR);

      ::i32 lLoOffset = lOff & 0xffffffff;
      //::i32 lHiOffset = (lOff >> 32) & 0xffffffff;

      filesize posNew = ::lseek(m_iFile, lLoOffset, (::u32)nFrom);
      //      posNew |= ((filesize) lHiOffset) << 32;
      if(posNew  == (filesize)-1)
         ::file::throw_os_error( (::i32)::get_last_error());

      return posNew;
   }

   filesize file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (::u32)hFileNull);

      ::i32 lLoOffset = 0;
      //      ::i32 lHiOffset = 0;

      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);
      //    pos |= ((filesize)lHiOffset) << 32;
      if(pos  == (filesize)-1)
         ::file::throw_os_error( (::i32)::get_last_error());

      return pos;
   }

//   void file::Flush()
//   {
//
//      /*      ::open
//       ::read
//       ::write
//
//       access the system directly no buffering : direct I/O - efficient for large writes - innefficient for lots of single byte writes
//
//       */
//
//      /*ASSERT_VALID(this);
//
//       if (m_iFile == (::u32)hFileNull)
//       return;
//
//       if (!::FlushFileBuffers((HANDLE)m_iFile))
//       ::macos::file_exception::throw_os_error( (::i32)::get_last_error());*/
//   }

//   filesize file::get_position() const
//   {
//      ASSERT_VALID(this);
//      ASSERT(m_iFile != (::u32)hFileNull);
//
//      ::i32 lLoOffset = 0;
//      //      ::i32 lHiOffset = 0;
//
//      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);
//      //    pos |= ((filesize)lHiOffset) << 32;
//      if(pos  == (filesize)-1)
//         ::file::throw_os_error( (::i32)::get_last_error());
//
//      return pos;
//   }
//
   void file::flush()
   {
//
//      /*      ::open
//       ::read
//       ::write
//
//       access the system directly no buffering : direct I/O - efficient for large writes - innefficient for lots of single byte writes
//
//       */
//
//      /*ASSERT_VALID(this);
//
         if (m_iFile == (::u32)hFileNull)
       return;
      
      //::flush(m_iFile);
      
//
//       if (!::FlushFileBuffers((HANDLE)m_iFile))
//       ::file::throw_os_error( (::i32)::get_last_error());*/
   }

   void file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (::u32)hFileNull);

      bool bError = false;
      if (m_iFile != (::u32)hFileNull)
         bError = ::close(m_iFile) != 0;

      m_iFile = (::u32) hFileNull;
      //      m_bCloseOnDelete = false;
      m_strFileName.Empty();

      if (bError)
         ::file::throw_os_error( (::i32)::get_last_error());
   }

//   void file::Abort()
//   {
//      ASSERT_VALID(this);
//      if (m_iFile != (::u32)hFileNull)
//      {
//         // close but ignore errors
//         ::close(m_iFile);
//         m_iFile = (::u32)hFileNull;
//      }
//      m_strFileName.Empty();
//   }
//
   

   void file::lock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      /*if (!::LockFile((HANDLE)m_iFile, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
       ::macos::file_exception::throw_os_error( (::i32)::get_last_error());*/
      
   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      /*      if (!::UnlockFile((HANDLE)m_iFile,  LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
       ::macos::file_exception::throw_os_error( (::i32)::get_last_error());*/
      
   }


   void file::set_size(filesize dwNewLen)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      seek((::i32)dwNewLen, (::enum_seek)::e_seek_set);

      if (::ftruncate(m_iFile, dwNewLen) == -1)
      {
         
         ::file::throw_os_error( (::i32)::get_last_error());
         
      }
      
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


   void file::assert_valid() const
   {
      
      ::file::file::assert_valid();
      
   }


   void file::dump(dump_context & dumpcontext) const
   {
      
      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_iFile;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
      
   }


//   string file::get_file_name() const
//   {
//
//      ASSERT_VALID(this);
//
//      ::file::file_status status;
//
//      get_status(status);
//
//      return status.m_strFullName.name();
//
//   }


//   string file::get_file_title() const
//   {
//
//      ASSERT_VALID(this);
//
//      ::file::file_status status;
//
//      get_status(status);
//
//      return status.m_strFullName.title();
//
//   }


   ::file::path file::get_file_path() const
   {
      
      return m_path;
      
   }


   bool file::get_status(::file::file_status & status) const
   {
      
      ASSERT_VALID(this);

      if (m_iFile != hFileNull)
      {
         
         struct ::stat st;
         
         if(fstat(m_iFile, &st) == -1)
         {
            
            return false;
            
         }

         status.m_size = st.st_size;

         status.m_attribute = 0;

         status.m_ctime = ::datetime::time(st.st_mtime);
         status.m_atime = ::datetime::time(st.st_atime);
         status.m_mtime = ::datetime::time(st.st_ctime);

         if (status.m_ctime.get_time() == 0)
            status.m_ctime = status.m_mtime;

         if (status.m_atime.get_time() == 0)
            status.m_atime = status.m_mtime;
         
         status.m_strFullName = m_path;

      }
      
      return true;
      
   }


//   bool PASCAL file::GetStatus(const char * lpszFileName, ::file::file_status& rStatus)
//   {
//      // attempt to fully qualify path first
//      wstring wstrFullName;
//      wstring wstrFileName;
//      wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
//      //      if (!vfxFullPath(wstrFullName, wstrFileName))
//      //    {
//      //     rStatus.m_strFullName.Empty();
//      //   return false;
//      //}
//
//      wstrFullName = wstrFileName;
//
//      ::str::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);
//
//      struct ::stat st;
//      if(stat(lpszFileName, &st) == -1)
//         return false;
//      //if (hFind == INVALID_HANDLE_VALUE)
//      // return false;
//      //VERIFY(FindClose(hFind));
//
//      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
//      //rStatus.m_attribute = (byte) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);
//
//      rStatus.m_attribute = 0;
//
//      // get just the low ::u32 of the file size_i32
//      //ASSERT(findFileData.nFileSizeHigh == 0);
//      //rStatus.m_size = (::i32)findFileData.nFileSizeLow;
//
//      rStatus.m_size = st.st_size;
//
//      // convert times as appropriate
//      /*rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
//       rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
//       rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);*/
//      rStatus.m_ctime = ::datetime::time(st.st_mtime);
//      rStatus.m_atime = ::datetime::time(st.st_atime);
//      rStatus.m_mtime = ::datetime::time(st.st_ctime);
//
//      if (rStatus.m_ctime.get_time() == 0)
//         rStatus.m_ctime = rStatus.m_mtime;
//
//      if (rStatus.m_atime.get_time() == 0)
//         rStatus.m_atime = rStatus.m_mtime;
//
//      return true;
//   }


   bool file::is_opened() const
   {
      
      return m_iFile != hFileNull;
      
   }


   void file::set_file_path(const ::file::path & path)
   {

      m_strFileName = path;
      
   }


} // namespace win


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)


#define _wcsinc(_pc)    ((_pc)+1)


// turn a file, relative path or other into an absolute path
bool CLASS_DECL_APEX vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
// lpszPathOut = buffer of _MAX_PATH
// lpszFileIn = file, relative path or absolute path
// (both in ANSI character set)
{


   wstrFullPath = wstrPath;


   return true;

}


CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{

   __throw(todo);

}


//void CLASS_DECL_APEX vfxThrowFileException(::object * pobject, ::e_status cause, ::i32 lOsError, const char * lpszFileName /* == nullptr */)
//{
//
//   __throw(::file::exception(cause, lOsError, lpszFileName));
//
//}
//
//
//::file::exception * CLASS_DECL_APEX get_FileException(::object * pobject, ::e_status cause, ::i32 lOsError, const char * lpszFileName /* == nullptr */)
//{
//
//   return __new(::file::exception(cause, lOsError, lpszFileName));
//
//}


//namespace ios
//{
//
//
//   namespace file_exception
//   {
//
//      ::e_status ErrnoToException(i32 nErrno)
//      {
//         switch(nErrno)
//         {
//         case EPERM:
//         case EACCES:
//            return ::file::exception::accessDenied;
//         case EBADF:
//            return ::file::exception::invalidFile;
//         case EMFILE:
//            return ::file::exception::tooManyOpenFiles;
//         case ENOENT:
//         case ENFILE:
//            return ::file::exception::fileNotFound;
//         case ENOSPC:
//            return ::file::exception::diskFull;
//         case EINVAL:
//         case EIO:
//            return ::file::exception::hardIO;
//         default:
//            return ::file::exception::type_generic;
//         }
//
//      }
//
//
//   } // namespace file_exception
//
//
//} // namespace ios




CLASS_DECL_APEX bool _os_may_have_alias(const char * psz)
{

   return true;

}



