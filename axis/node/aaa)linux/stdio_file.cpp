#include "framework.h"
#include "_linux.h"

#include <fcntl.h>

namespace linux
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


   ::status::result stdio_file::open(const ::file::path & pszFileName, const cflag < ::file::e_open > & eopen)
   {

      ASSERT(pszFileName.has_char());

      if ((eopen & ::file::defer_create_directory) && (eopen & ::file::mode_write))
      {

         Context.dir().mk(pszFileName.folder());


      }

      m_pStream = nullptr;
      //if (!::linux::file::open(pszFileName, (nOpenFlags & ~::file::type_text)))

      // return FALSE;

//   ASSERT(m_hFile != hFileNull);
      // ASSERT(m_bCloseOnDelete);

      char szMode[4]; // C-runtime open string
      i32 nMode = 0;

      // determine read/write mode depending on ::ca2::filesp mode
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
      if ((szMode[0] == 'r' && (eopen & ::file::mode_read_write)) ||
            (szMode[0] != 'r' && !(eopen & ::file::mode_write)))
      {
         // current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      i32 nFlags = O_RDONLY;
      if (eopen & (::file::mode_write | ::file::mode_read_write))
         nFlags ^= O_RDONLY;

      if (eopen & ::file::type_binary)
         szMode[nMode++] = 'b'; // , nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      //i32 nHandle = _open_osfhandle(m_hFile, nFlags);

      // open a C-runtime stream from that handle
      //if (nHandle != -1)
      m_pStream = fopen(pszFileName, szMode);



      if (m_pStream == nullptr)
      {
         ::file::throw_status(error_file, errno, m_path);
         // an error somewhere along the way...
         //if (pException != nullptr)
         {
//         pException->m_lOsError = errno;
//         pException->m_cause = ::file::exception::OsErrorToException(errno);
         }

         ::linux::file::Abort(); // close m_hFile
         //return ::fesp(get_context_application(), ::file::exception::none);
         return ::error_io;
      }

      m_path = pszFileName;


      return ::success;

   }


   memsize stdio_file::read(void * pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

//   ASSERT(fx_is_valid_address(pdata, nCount));


      ::u32 nRead = 0;

      if ((nRead = fread(pdata, sizeof(byte), nCount, m_pStream)) == 0 && !feof(m_pStream))

         ::file::throw_status(error_file, errno, m_path);
      if (ferror(m_pStream))
      {
         clearerr(m_pStream);
         ::file::throw_status(error_file, errno, m_path);
      }
      return nRead;
   }

   void stdio_file::write(const void * pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
//   ASSERT(fx_is_valid_address(pdata, nCount, FALSE));


      if (fwrite(pdata, sizeof(byte), nCount, m_pStream) != nCount)

         ::file::throw_status(error_file, errno, m_path);
   }

   void stdio_file::write_string(const char * psz)

   {
      ASSERT(psz != nullptr);

      ASSERT(m_pStream != nullptr);

      if (fputs(psz, m_pStream) == EOF)

         ::file::throw_status(error_disk_full, errno, m_path);
   }

   LPTSTR stdio_file::read_string(LPTSTR psz, ::u32 nMax)

   {
      ASSERT(psz != nullptr);

//   ASSERT(fx_is_valid_address(psz, nMax));

      ASSERT(m_pStream != nullptr);

      LPTSTR pszResult = fgets(psz, nMax, m_pStream);

      if (pszResult == nullptr && !feof(m_pStream))

      {
         clearerr(m_pStream);
         ::file::throw_status(error_file, errno, m_path);
      }
      return pszResult;

   }


   bool stdio_file::read_string(string & rString)
   {

      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const i32 nMaxSize = 128;
      char * psz = rString.get_string_buffer(nMaxSize);

      char * pszResult;

      i32 nLen = 0;
      for (;;)
      {
         pszResult = fgets(psz, nMaxSize+1, m_pStream);

         rString.release_string_buffer();

         // handle error/eof case
         if (pszResult == nullptr && !feof(m_pStream))

         {
            clearerr(m_pStream);
            ::file::throw_status(error_file, errno, m_path);
         }

         // if string is read completely or EOF
         if (pszResult == nullptr ||

               (nLen = strlen(psz)) < nMaxSize ||

               psz[nLen-1] == '\n')

            break;

         nLen = rString.get_length();

         psz = rString.get_string_buffer(nMaxSize + nLen) + nLen;

      }

      // remov '\n' from end of string if present
      psz = rString.get_string_buffer(0);

      nLen = rString.get_length();
      if (nLen != 0 && psz[nLen-1] == '\n')

         rString.get_string_buffer(nLen-1);

      return pszResult != nullptr;

   }

   /*void stdio_file::write_string(const char * psz)

   {
      ASSERT(psz != nullptr);

      ASSERT(m_pStream != nullptr);

      if (fputws(psz, m_pStream) == _TEOF)

         ::file::throw_status(error_diskFull, errno, m_path);
   }*/

   /*unichar * stdio_file::read_string(unichar * psz, ::u32 nMax)

   {
      ASSERT(psz != nullptr);

      ASSERT(fx_is_valid_address(psz, nMax));

      ASSERT(m_pStream != nullptr);

      unichar * pszResult = fgetws(psz, nMax, m_pStream);

      if (pszResult == nullptr && !feof(m_pStream))

      {
         clearerr(m_pStream);
         ::file::throw_status(error_type_generic, errno, m_path);
      }
      return pszResult;

   }*/

   filesize stdio_file::seek(filesize lOff, ::file::e_seek eseek)
   {
      ASSERT_VALID(this);
      ASSERT(eseek == ::file::seek_begin || eseek== ::file::seek_end || eseek== ::file::seek_current);
      ASSERT(m_pStream != nullptr);

      i32 nFrom;
      switch(eseek)
      {
      case ::file::seek_begin:
         nFrom = SEEK_SET;
         break;
      case ::file::seek_end:
         nFrom = SEEK_END;
         break;
      case ::file::seek_current:
         nFrom = SEEK_CUR;
         break;
      default:
         ::file::throw_status(error_bad_seek, -1, m_path);
      }

      if (fseek(m_pStream, lOff, nFrom) != 0)
         ::file::throw_status(error_bad_seek, errno, m_path);

      long pos = ftell(m_pStream);
      return pos;
   }

   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos == -1)
         ::file::throw_status(error_invalid_file, errno, m_path);
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
      {

         ::file::throw_status(error_disk_full, errno, m_path);

      }

   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      i32 nErr = 0;

      if (m_pStream != nullptr)
         nErr = fclose(m_pStream);

//   m_hFile = (::u32) hFileNull;
      //m_bCloseOnDelete = FALSE;
      m_pStream = nullptr;

      if (nErr != 0)
         ::file::throw_status(error_disk_full, errno, m_path);
   }

   void stdio_file::Abort()
   {
      ASSERT_VALID(this);

//   if (m_pStream != nullptr && m_bCloseOnDelete)
      if (m_pStream != nullptr)
         fclose(m_pStream);  // close but ignore errors
//   m_hFile = (::u32) hFileNull;
      m_pStream = nullptr;
      //m_bCloseOnDelete = FALSE;
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

      ::linux::file::dump(dumpcontext);

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
         ::file::throw_status(error_invalid_file, errno, m_path);

      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, errno, m_path);

      nLength = ftell(m_pStream);
      if (nLength == -1)
         ::file::throw_status(error_invalid_file, errno,
                               m_path);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         ::file::throw_status(error_bad_seek, errno,
                               m_path);

      return nLength;
   }


} // namespace linux
