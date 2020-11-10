#include "framework.h"
#include "aura/os/windows_common/file.h"


#include <errno.h>
#include <io.h>
#include <fcntl.h>


namespace uwp
{

   stdio_file::stdio_file()
   {
      m_pStream = nullptr;
   }

   stdio_file::~stdio_file()
   {
      //   ASSERT_VALID(this);

      //   if (m_pStream != nullptr && m_bCloseOnDelete)
      //close();
      if (m_pStream != nullptr)
         close();
   }


   ::status::result stdio_file::open(const ::file::path & lpszFileName,::u32 nOpenFlags)
   {

      ASSERT(lpszFileName != nullptr);

      ASSERT(__is_valid_string(lpszFileName));

      if ((nOpenFlags & ::file::defer_create_directory) && (nOpenFlags & ::file::mode_write))
      {

         Context.dir().mk(lpszFileName.folder());

      }

      m_pFile = nullptr;

      m_pFile(!file::open(lpszFileName, (nOpenFlags & ~::file::type_text)))
      {

         return error_failed;

      }

      ASSERT(m_pFile != nullptr);
      ASSERT(m_bCloseOnDelete);

      char szMode[4]; // C-runtime open string
      int nMode = 0;

      // determine read/write mode depending on file_pointer mode
      if (nOpenFlags & ::file::mode_create)
      {
         if (nOpenFlags & ::file::mode_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (nOpenFlags & ::file::mode_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';

      // add '+' if necessary (when read/write modes mismatched)
      if (szMode[0] == 'r' && (nOpenFlags & ::file::mode_read_write) ||
            szMode[0] != 'r' && !(nOpenFlags & ::file::mode_write))
      {
         // ::file::seek_current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      int nFlags = _O_RDONLY|_O_TEXT;
      if (nOpenFlags & (::file::mode_write|::file::mode_read_write))
         nFlags ^= _O_RDONLY;

      if (nOpenFlags & ::file::type_binary)
         szMode[nMode++] = 'b', nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      int nHandle = _open_osfhandle(m_hFile, nFlags);

      // open a C-runtime stream from that handle
      if (nHandle != -1)
         m_pStream = _fdopen(nHandle, szMode);

      if (m_pStream == nullptr)
      {
         // an error somewhere along the way...
         //      if (pException != nullptr)
         //    {
         //         pException->m_lOsError = _doserrno;
         //         pException->m_cause = ::file::exception::OsErrorToException(_doserrno);
         //  }

         //file::Abort(); // close m_hFile

         close();

         return error_failed;

      }

      return ::success;

   }


   memsize stdio_file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount == 0)
         return 0;   // avoid Win32 "nullptr-read"

      ASSERT(__is_valid_address(lpBuf, nCount));

      memsize nRead = 0;

      if ((nRead = fread(lpBuf, sizeof(byte), nCount, m_pStream)) == 0 && !feof(m_pStream))
         ::file::throw_stdio_exception(::error_file, _doserrno, m_path);
      if (ferror(m_pStream))
      {
         clearerr(m_pStream);
         ::file::throw_stdio_exception(::error_file, _doserrno, m_path);
      }
      return nRead;
   }

   void stdio_file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
      ASSERT(__is_valid_address(lpBuf, nCount, FALSE));

      if (fwrite(lpBuf, sizeof(byte), nCount, m_pStream) != nCount)
         ::file::throw_status(error_file, _doserrno, m_path);
   }

   void stdio_file::write_string(const char * lpsz)
   {
      ASSERT(lpsz != nullptr);
      ASSERT(m_pStream != nullptr);

      if (fputs(lpsz, m_pStream) == _TEOF)
         ::file::throw_status(error_disk_full, _doserrno, m_path);
   }

   char * stdio_file::read_string(char * lpsz, ::u32 nMax)
   {
      ASSERT(lpsz != nullptr);
      ASSERT(__is_valid_address(lpsz, nMax));
      ASSERT(m_pStream != nullptr);

      char * lpszResult = fgets(lpsz, nMax, m_pStream);
      if (lpszResult == nullptr && !feof(m_pStream))
      {
         clearerr(m_pStream);
         ::file::throw_errno(_doserrno, m_path);
      }
      return lpszResult;
   }

   bool stdio_file::read_string(string & rString)
   {
      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const int nMaxSize = 128;
      char * lpsz = rString.get_string_buffer(nMaxSize);
      char * lpszResult;
      memsize nLen = 0;
      for (;;)
      {
         lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
         rString.release_string_buffer();

         // handle error/eof case
         if (lpszResult == nullptr && !feof(m_pStream))
         {
            clearerr(m_pStream);
            ::file::throw_status(error_file, _doserrno, m_path);
         }

         // if string is read completely or EOF
         if (lpszResult == nullptr ||
               (nLen = strlen(lpsz)) < nMaxSize ||
               lpsz[nLen-1] == '\n')
            break;

         nLen = rString.get_length();
         lpsz = rString.get_string_buffer(nMaxSize + nLen) + nLen;
      }

      // remov '\n' from ::file::seek_end of string if present
      lpsz = rString.get_string_buffer(0);
      nLen = rString.get_length();
      if (nLen != 0 && lpsz[nLen-1] == '\n')
         rString.get_string_buffer(nLen-1);

      return lpszResult != nullptr;
   }


   filesize stdio_file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      ASSERT_VALID(this);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(m_pStream != nullptr);

      if (fseek(m_pStream, (long)lOff, nFrom) != 0)
      {

         ::file::throw_status(error_bad_seek, _doserrno, m_path);

      }

      long pos = ftell(m_pStream);

      return pos;

   }


   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos == -1)
         ::file::throw_status(error_invalid_file, _doserrno,  m_path);
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
         ::file::throw_status(error_disk_full, _doserrno,  m_path);
   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      int nErr = 0;

      if (m_pStream != nullptr)
         nErr = fclose(m_pStream);

      m_hFile = (::u32) hFileNull;
      m_bCloseOnDelete = FALSE;
      m_pStream = nullptr;

      if (nErr != 0)
         ::file::throw_status(error_disk_full, _doserrno,  m_path);
   }

   void stdio_file::Abort()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && m_bCloseOnDelete)
         fclose(m_pStream);  // close but ignore errors
      m_hFile = (::u32) hFileNull;
      m_pStream = nullptr;
      m_bCloseOnDelete = FALSE;
   }


   __pointer(::file::file) stdio_file::Duplicate() const
   {

      ASSERT_VALID(this);

      ASSERT(m_pStream != nullptr);

      __throw(not_supported_exception());

      return nullptr;

   }


   void stdio_file::LockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      __throw(not_supported_exception());
   }

   void stdio_file::UnlockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      __throw(not_supported_exception());
   }


   void stdio_file::dump(dump_context & dumpcontext) const
   {
      file::dump(dumpcontext);

      dumpcontext << "m_pStream = " << (void *)m_pStream;
      dumpcontext << "\n";
   }




   filesize stdio_file::get_length() const
   {
      ASSERT_VALID(this);

      ::i32 nCurrent;
      ::i32 nLength;
      ::i32 nResult;

      nCurrent = ftell(m_pStream);
      if (nCurrent == -1)
         ::file::throw_status(error_invalid_file, _doserrno, m_path);

      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, _doserrno,  m_path);

      nLength = ftell(m_pStream);
      if (nLength == -1)
         ::file::throw_status(error_invalid_file, _doserrno,  m_path);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, _doserrno,   m_path);

      return nLength;
   }


} // namespace uwp




