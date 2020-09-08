#include "framework.h"
#include "acme/node/windows/_windows.h"
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
//#include <errno.h>


namespace windows
{


   stdio_file::stdio_file()
   {

      m_pStream   = nullptr;
      m_iFile     = iFileNull;

   }


   stdio_file::~stdio_file()
   {

      if (m_pStream != nullptr)
         close();

   }


   ::status::result stdio_file::open(const ::file::path & pszFileName, const efileopen & eopen)

   {

      ASSERT(pszFileName != nullptr);


      ASSERT(__is_valid_string(pszFileName));


      if ((eopen & ::file::defer_create_directory) && (eopen & ::file::mode_write))
      {
         ::dir::mk(::dir::name(pszFileName));

      }

      m_pStream = nullptr;
//      if(!::windows::file::open(pszFileName,(eopen & ~::file::type_text)))

      //    {

      //     return failure;

      //}

      //ASSERT(m_hFile != hFileNull);

      char szMode[4]; // C-runtime open string
      i32 nMode = 0;

      // determine read/write mode depending on file_pointer mode
      if (eopen & ::file::mode_create)
      {
         if (eopen & ::file::mode_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (eopen & ::file::mode_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';

      // add '+' if necessary (when read/write modes mismatched)
      if (szMode[0] == 'r' && (eopen & ::file::mode_read_write) ||
            szMode[0] != 'r' && !(eopen & ::file::mode_write))
      {
         // ::file::seek_current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      i32 nFlags = _O_RDONLY|_O_TEXT;
      if (eopen & (::file::mode_write|::file::mode_read_write))
         nFlags ^= _O_RDONLY;

      if (eopen & ::file::type_binary)
         szMode[nMode++] = 'b', nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      int nHandle = _wopen(wstring(pszFileName), nFlags);


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

         Abort(); // close m_iFile

         return ::error_failed;

      }

      return ::success;

   }


   memsize stdio_file::read(void * pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(__is_valid_address(pdata, nCount));


      memsize nRead = 0;

      if ((nRead = fread(pdata, sizeof(BYTE), (size_t) nCount, m_pStream)) == 0 && !feof(m_pStream))
      {

         ::file::throw_status(error_file, _doserrno, m_path);

      }

      if (ferror(m_pStream))
      {

         clearerr(m_pStream);

         ::file::throw_status(error_file, _doserrno, m_path);

      }
      return nRead;
   }

   void stdio_file::write(const void * pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
      ASSERT(__is_valid_address(pdata, nCount, FALSE));


      if (fwrite(pdata, sizeof(BYTE), (size_t)nCount, m_pStream) != nCount)

         ::file::throw_status(error_file, _doserrno, m_path);
   }

   void stdio_file::write_string(const char * psz)

   {
      ASSERT(psz != nullptr);

      ASSERT(m_pStream != nullptr);

      if (fputs(psz, m_pStream) == _TEOF)

         ::file::throw_status(error_disk_full, _doserrno, m_path);
   }

   char * stdio_file::read_string(LPSTR psz, UINT nMax)

   {
      ASSERT(psz != nullptr);

      ASSERT(__is_valid_address(psz, nMax));

      ASSERT(m_pStream != nullptr);

      LPSTR pszResult = fgets(psz, nMax, m_pStream);

      if (pszResult == nullptr && !feof(m_pStream))

      {
         clearerr(m_pStream);
         ::file::throw_status(error_file, _doserrno, m_path);
      }
      return pszResult;

   }


   bool stdio_file::read_string(string & rString)
   {

      ASSERT_VALID(this);

      rString.Empty();

      const i32 nMaxSize = 128;

      char * psz = rString.get_string_buffer(nMaxSize);

      char * pszResult;

      memsize nLen = 0;

      for (;;)
      {

         pszResult = fgets(psz, nMaxSize+1, m_pStream);

         rString.release_string_buffer();

         // handle error/eof case
         if (pszResult == nullptr && !feof(m_pStream))
         {

            clearerr(m_pStream);

            ::file::throw_status(error_file, _doserrno,
                                 m_path);
         }

         // if string is read completely or EOF
         if (pszResult == nullptr || (nLen = strlen(psz)) < nMaxSize || psz[nLen - 1] == '\n')
         {

            break;

         }

         nLen = rString.get_length();

         psz = rString.get_string_buffer(nMaxSize + nLen) + nLen;

      }

      nLen = rString.get_length();

      if (nLen != 0 && psz[nLen - 1] == '\n')
      {

         rString.truncate(nLen - 1);

      }

      return pszResult != nullptr;

   }

   /*void stdio_file::write_string(const char * psz)

   {
   ASSERT(psz != nullptr);

   ASSERT(m_pStream != nullptr);

   if (fputws(psz, m_pStream) == _TEOF)

   ::file::throw_status(error_disk_full, _doserrno, m_path);
   }*/

   /*unichar * stdio_file::read_string(unichar * psz, UINT nMax)

   {
   ASSERT(psz != nullptr);

   ASSERT(__is_valid_address(psz, nMax));

   ASSERT(m_pStream != nullptr);

   unichar * pszResult = fgetws(psz, nMax, m_pStream);

   if (pszResult == nullptr && !feof(m_pStream))

   {
   clearerr(m_pStream);
   ::file::throw_status(error_generic, _doserrno, m_path);
   }
   return pszResult;

   }*/

   filesize stdio_file::seek(filesize lOff, ::file::e_seek nFrom)
   {
      ASSERT_VALID(this);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(m_pStream != nullptr);

      if (fseek(m_pStream, (long) lOff, nFrom) != 0)
         ::file::throw_status(error_bad_seek, _doserrno, m_path);

      long pos = ftell(m_pStream);
      return pos;
   }

   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos == -1)
         ::file::throw_status(error_invalid_file, _doserrno, m_path);
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
         ::file::throw_status(error_disk_full, _doserrno,
                              m_path);
   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      i32 nErr = 0;

      if(m_iFile != iFileNull)
         ::_close(m_iFile);

      if(m_pStream != nullptr)
      {
         fflush(m_pStream);
         nErr = fclose(m_pStream);
      }

      m_iFile = iFileNull;
      m_pStream = nullptr;

      if (nErr != 0)
         ::file::throw_status(error_disk_full, _doserrno,
                              m_path);
   }


   void stdio_file::Abort()
   {

      ASSERT_VALID(this);

      if(m_iFile != iFileNull)
         ::_close(m_iFile);

      if (m_pStream != nullptr)
         fclose(m_pStream);  // close but ignore errors

      m_iFile = iFileNull;

      m_pStream = nullptr;

   }


   file_pointer  stdio_file::Duplicate() const
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

      //::windows::file::dump(dumpcontext);

      dumpcontext << "m_iFile = " << m_iFile;
      dumpcontext << "m_pStream = " << (void *)m_pStream;
      dumpcontext << "\n";

   }


   filesize stdio_file::get_length() const
   {
      ASSERT_VALID(this);

      LONG nCurrent;
      LONG nLength;
      LONG nResult;

      nCurrent = ftell(m_pStream);
      if (nCurrent == -1)
         ::file::throw_status(error_invalid_file, _doserrno,
                              m_path);

      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, _doserrno,
                              m_path);

      nLength = ftell(m_pStream);
      if (nLength == -1)
         ::file::throw_status(error_invalid_file, _doserrno,
                              m_path);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, _doserrno,
                              m_path);

      return nLength;
   }


} // namespace windows



