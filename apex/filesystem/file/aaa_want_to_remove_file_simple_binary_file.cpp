#include "framework.h"
#include <stdio.h>

#if defined(APPLEOS)
#include <sys/stat.h>
#elif defined(LINUX)
#undef USE_MISC

#include <sys/stat.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#endif
//////#include <errno.h>
////#include <io.h>
////#include <fcntl.h>

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)

//
#define _doserrno errno
#define _fileno fileno
#define _fputts fputs
#define _TEOF EOF
#define _fgetts fgets
#define lstrlen strlen

#endif

namespace file
{


   simple_binary_file::simple_binary_file(::layered * pobjectContext) :
      object(pobject)
   {

      m_pfile = NULL;

   }


   simple_binary_file::~simple_binary_file()
   {

      if (m_pfile != NULL)
         close();

   }


   ::status::result simple_binary_file::open(const ::file::path & lpszFileName, UINT nOpenFlags)
   {

      ASSERT(lpszFileName.has_char());

      ASSERT(__is_valid_string(lpszFileName));

      if ((nOpenFlags & ::file::defer_create_directory) && (nOpenFlags & ::file::mode_write))
      {
         ::dir::mk(::dir::name(lpszFileName));
      }

      char szMode[4]; // C-runtime open string
      i32 nMode = 0;

      // determine read/write mode depending on file_pointer mode
      if (nOpenFlags & mode_create)
      {
         if (nOpenFlags & mode_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (nOpenFlags & mode_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';

      // add '+' if necessary (when read/write modes mismatched)
      if ((szMode[0] == 'r' && (nOpenFlags & mode_read_write)) ||
            (szMode[0] != 'r' && !(nOpenFlags & mode_write)))
      {
         // ::file::seek_current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      if (nOpenFlags & type_binary)
         szMode[nMode++] = 'b';
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime stream from that handle
      m_pfile = fopen(lpszFileName, szMode);

      if (m_pfile == NULL)
      {
         Abort();
         return failure;
      }

      return ::success;

   }

   memsize simple_binary_file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(__is_valid_address(lpBuf, nCount));

      memsize nRead = 0;


      if ((nRead = fread(lpBuf, sizeof(BYTE), nCount, m_pfile)) == 0 && !feof(m_pfile))
         throw_exception(::file::exception::type_generic, _doserrno, m_strFileName);
      if (ferror(m_pfile))
      {
         clearerr(m_pfile);
         throw_exception(::file::exception::type_generic, _doserrno, m_strFileName);
      }
      return nRead;
   }

   void simple_binary_file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);
      ASSERT(__is_valid_address(lpBuf, nCount, FALSE));

      if (fwrite(lpBuf, sizeof(BYTE), nCount, m_pfile) != nCount)
         throw_exception(::file::exception::type_generic, _doserrno, m_strFileName);
   }

   void simple_binary_file::write_string(const char * lpsz)
   {
      ASSERT(lpsz != NULL);
      ASSERT(m_pfile != NULL);
#if defined(_UWP)
      if (_fputts(wstring(lpsz), m_pfile) == _TEOF)
         throw_exception(::file::exception::diskFull, _doserrno, m_strFileName);
#else
      if (_fputts(lpsz, m_pfile) == _TEOF)
         throw_exception(::file::exception::diskFull, _doserrno, m_strFileName);
#endif
   }

   LPTSTR simple_binary_file::read_string(LPTSTR lpsz, UINT nMax)
   {
      ASSERT(lpsz != NULL);
      ASSERT(__is_valid_address(lpsz, nMax));
      ASSERT(m_pfile != NULL);

      LPTSTR lpszResult = _fgetts(lpsz, nMax, m_pfile);
      if (lpszResult == NULL && !feof(m_pfile))
      {
         clearerr(m_pfile);
         throw_exception(::file::exception::type_generic, _doserrno, m_strFileName);
      }
      return lpszResult;
   }

   bool simple_binary_file::read_string(string & rString)
   {
      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const i32 nMaxSize = 128;
      char * lpsz = rString.GetBuffer(nMaxSize);
      char * lpszResult;
      memsize nLen = 0;
      for (;;)
      {
         lpszResult = fgets(lpsz, nMaxSize+1, m_pfile);
         rString.ReleaseBuffer();

         // handle error/eof case
         if (lpszResult == NULL && !feof(m_pfile))
         {
            clearerr(m_pfile);
            throw_exception(::file::exception::type_generic, _doserrno,
                            m_strFileName);
         }

         // if string is read completely or EOF
         if (lpszResult == NULL ||
               (nLen = strlen(lpsz)) < nMaxSize ||
               lpsz[nLen-1] == '\n')
            break;

         nLen = rString.get_length();
         lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;
      }

      // remov '\n' from ::file::seek_end of string if present
      lpsz = rString.GetBuffer(0);
      nLen = rString.get_length();
      if (nLen != 0 && lpsz[nLen-1] == '\n')
         rString.GetBufferSetLength(nLen-1);

      return lpszResult != NULL;
   }

   /*void simple_binary_file::write_string(const char * lpsz)
   {
   ASSERT(lpsz != NULL);
   ASSERT(m_pfile != NULL);

   if (fputws(lpsz, m_pfile) == _TEOF)
   throw_exception(::file::exception::diskFull, _doserrno, m_strFileName);
   }*/

   /*unichar * simple_binary_file::read_string(unichar * lpsz, UINT nMax)
   {
   ASSERT(lpsz != NULL);
   ASSERT(__is_valid_address(lpsz, nMax));
   ASSERT(m_pfile != NULL);

   unichar * lpszResult = fgetws(lpsz, nMax, m_pfile);
   if (lpszResult == NULL && !feof(m_pfile))
   {
   clearerr(m_pfile);
   throw_exception(::file::exception::generic, _doserrno, m_strFileName);
   }
   return lpszResult;
   }*/

   filesize simple_binary_file::seek(filesize lOff, ::file::e_seek nFrom)
   {
      ASSERT_VALID(this);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(m_pfile != NULL);

      if (fseek(m_pfile, (long) lOff, nFrom) != 0)
         throw_exception(::file::exception::badSeek, _doserrno,
                         m_strFileName);

      long pos = ftell(m_pfile);
      return pos;
   }

   filesize simple_binary_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      long pos = ftell(m_pfile);
      if (pos == -1)
         throw_exception(::file::exception::invalidFile, _doserrno,
                         m_strFileName);
      return pos;
   }

   void simple_binary_file::flush()
   {
      ASSERT_VALID(this);

      if (m_pfile != NULL && fflush(m_pfile) != 0)
         throw_exception(::file::exception::diskFull, _doserrno, m_strFileName);
   }

   void simple_binary_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      i32 nErr = 0;

      if (m_pfile != NULL)
         nErr = fclose(m_pfile);

      m_pfile = NULL;

      if (nErr != 0)
         throw_exception(::file::exception::diskFull, _doserrno, m_strFileName);
   }

   void simple_binary_file::Abort()
   {
      ASSERT_VALID(this);

      if (m_pfile != NULL)
         fclose(m_pfile);  // close but ignore errors
      m_pfile = NULL;
   }

   file_pointer  simple_binary_file::Duplicate() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      __throw(not_supported_exception());
      return NULL;
   }

   void simple_binary_file::LockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      __throw(not_supported_exception());
   }

   void simple_binary_file::UnlockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pfile != NULL);

      __throw(not_supported_exception());
   }



   filesize simple_binary_file::get_length() const
   {
      ASSERT_VALID(this);

      LONG nCurrent;
      LONG nLength;
      LONG nResult;

      nCurrent = (LONG) ftell(m_pfile);
      if (nCurrent == -1)
         throw_exception(::file::exception::invalidFile, _doserrno, m_strFileName);

      nResult = fseek(m_pfile, 0, SEEK_END);
      if (nResult != 0)
         throw_exception(::file::exception::badSeek, _doserrno, m_strFileName);

      nLength = (LONG) ftell(m_pfile);
      if (nLength == -1)
         throw_exception(::file::exception::invalidFile, _doserrno, m_strFileName);

      nResult = fseek(m_pfile, nCurrent, SEEK_SET);
      if (nResult != 0)
         throw_exception(::file::exception::badSeek, _doserrno, m_strFileName);

      return nLength;
   }

   void simple_binary_file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }

/////////////////////////////////////////////////////////////////////////////
   // FileException helpers

#ifdef _DEBUG
   static const char * rgszFileExceptionCause[] =
   {
      "none",
      "generic",
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
   static const char szUnknown[] = "unknown";
#endif

   void CLASS_DECL_APEX throw_exception(::object * pobject,::estatus cause,LONG lOsError,const char * lpszFileName /* == NULL */)
   {
      //#ifdef _DEBUG
      //   const char * lpsz;
      //   if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
      //      lpsz = rgszFileExceptionCause[cause];
      //   else
      //      lpsz = szUnknown;
      //   //   TRACE3("file exception: %hs, file %s, App error information = %ld.\n", lpsz, (lpszFileName == NULL) ? "Unknown" : lpszFileName, lOsError);
      //#endif
      __throw(::file::exception(cause, lOsError, lpszFileName));
   }

   string simple_binary_file::GetFileName() const
   {
      ASSERT_VALID(this);

      ::file::file_status status;
      GetStatus(status);
      return file_name_dup(status.m_strFullName);
   }

   string simple_binary_file::GetFileTitle() const
   {
      ASSERT_VALID(this);

      ::file::file_status status;
      GetStatus(status);
      return file_title_dup(status.m_strFullName);
   }

   string simple_binary_file::GetFilePath() const
   {
      ASSERT_VALID(this);

      ::file::file_status status;
      GetStatus(status);
      return status.m_strFullName;
   }

   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool simple_binary_file::GetStatus(::file::file_status& rStatus) const
   {
      ASSERT_VALID(this);

      //__memset(&rStatus, 0, sizeof(::file::file_status));

      // copy file name from cached m_strFileName
      rStatus.m_strFullName = m_strFileName;

      if (m_pfile != NULL)
      {
         struct stat st;
         if(fstat(_fileno(m_pfile), &st) == -1)
            return FALSE;
         // get time ::file::seek_current file size
         /*FILETIME ftCreate, ftAccess, ftModify;
         if (!::GetFileTime((HANDLE)m_iFile, &ftCreate, &ftAccess, &ftModify))
            return FALSE;*/

         rStatus.m_size = st.st_size;

         //if ((rStatus.m_size = ::GetFileSize((HANDLE)m_iFile, NULL)) == (DWORD)-1L)
         // return FALSE;


         //if (m_strFileName.is_empty())
         // __throw(todo());
         rStatus.m_attribute = 0;
         /*         else
                  {
                     DWORD dwAttribute = ::GetFileAttributesW(::apex::international::utf8_to_unicode(m_strFileName));

                     // don't return an error for this because previous versions of apex API didn't
                     if (dwAttribute == 0xFFFFFFFF)
                        rStatus.m_attribute = 0;
                     else
                     {
                        rStatus.m_attribute = (BYTE) dwAttribute;
         #ifdef _DEBUG
                        // apex API BUG: m_attribute is only a BYTE wide
                        if (dwAttribute & ~0xFF)
                           TRACE0("Warning: file::GetStatus() returns m_attribute without high-order flags.\n");
         #endif
                     }
                  }*/

         // convert times as appropriate
         //rStatus.m_ctime = ::datetime::time(ftCreate);
         //rStatus.m_atime = ::datetime::time(ftAccess);
         //rStatus.m_mtime = ::datetime::time(ftModify);
         rStatus.m_ctime = ::datetime::time(st.st_mtime);
         rStatus.m_atime = ::datetime::time(st.st_atime);
         rStatus.m_mtime = ::datetime::time(st.st_ctime);

         if (rStatus.m_ctime.get_time() == 0)
            rStatus.m_ctime = rStatus.m_mtime;

         if (rStatus.m_atime.get_time() == 0)
            rStatus.m_atime = rStatus.m_mtime;
      }
      return TRUE;
   }


//   bool simple_binary_file::GetStatus(const char * lpszFileName, ::file::file_status& rStatus)
//   {
//      // attempt to fully qualify path first
///*      wstring wstrFullName;
//      wstring wstrFileName;
//      wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
//      if (!vfxFullPath(wstrFullName, wstrFileName))
//      {
//         rStatus.m_strFullName.Empty();
//         return FALSE;
//      }
//      ::apex::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);*/
//
//      rStatus.m_strFullName = lpszFileName;
//
//      struct stat st;
//      if(stat(lpszFileName, &st) == -1)
//         return false;
//      //if (hFind == INVALID_HANDLE_VALUE)
//        // return FALSE;
//      //VERIFY(FindClose(hFind));
//
//      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
//      //rStatus.m_attribute = (BYTE) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);
//
//      rStatus.m_attribute = 0;
//
//      // get just the low DWORD of the file size
//      //ASSERT(findFileData.nFileSizeHigh == 0);
//      //rStatus.m_size = (LONG)findFileData.nFileSizeLow;
//
//      rStatus.m_size = st.st_size;
//
//      // convert times as appropriate
//      /*rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
//      rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
//      rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);*/
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
//      return TRUE;
//   }
//
//   void simple_binary_file::SetStatus(const char * lpszFileName, const ::file::file_status& status)
//   {
//      ::exception::throw_not_implemented();
//   }

   bool simple_binary_file::IsOpened()
   {
      return m_pfile != NULL && _fileno(m_pfile) != -1;
   }


   string simple_binary_file::get_location() const
   {
      return GetFilePath();
   }

   /////////////////////////////////////////////////////////////////////////////
   // file diagnostics

   void simple_binary_file::assert_valid() const
   {
      object::assert_valid();
      // we permit the descriptor m_iFile to be any value for derived classes
   }

   void simple_binary_file::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "with handle " << (iptr)m_pfile;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }

   void simple_binary_file::set_length(filesize dwNewLen)
   {

      ASSERT_VALID(this);

      ASSERT(m_pfile != NULL);

      seek((LONG)dwNewLen, ::file::seek_begin);

      if (!::ftruncate(_fileno(m_pfile), dwNewLen))
         throw_exception(::file::exception::invalidFile, _doserrno, m_strFileName);

   }


} // namespace file



