#include "framework.h"

#include <fcntl.h>

namespace ios
{



   stdio_file::stdio_file(::object * pobject) :
      ::object(pobject),
      ::ios::file(pobject)
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

   ::extended::status stdio_file::open(const ::file::path & lpszFileName, ::u32 nOpenFlags)
   {
      //      ASSERT(lpszFileName != nullptr);
      //ASSERT(AfxIsValidString(lpszFileName));

      if ((nOpenFlags & ::file::e_open_defer_create_directory) && (nOpenFlags & ::file::e_open_write))
      {
         pcontext->m_papexcontext->dir().mk(::file::path(lpszFileName).folder());
      }

      m_pStream = nullptr;
      //if (!::lnx::file::open(lpszFileName, (nOpenFlags & ~::file::e_open_text)))
      // return false;

      //   ASSERT(m_hFile != hFileNull);
      // ASSERT(m_bCloseOnDelete);

      char szMode[4]; // C-runtime open string
      i32 nMode = 0;

      // determine read/write mode depending on ::ca2::filesp mode
      if (nOpenFlags & ::file::e_open_create)
      {
         if (nOpenFlags & ::file::e_open_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (nOpenFlags & ::file::e_open_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';

      // add '+' if necessary (when read/write modes mismatched)
      if ((szMode[0] == 'r' && (nOpenFlags & ::file::e_open_read_write)) ||
            (szMode[0] != 'r' && !(nOpenFlags & ::file::e_open_write)))
      {
         // current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      i32 nFlags = O_RDONLY;
      if (nOpenFlags & (::file::e_open_write | ::file::e_open_read_write))
         nFlags ^= O_RDONLY;

      if (nOpenFlags & ::file::e_open_binary)
         szMode[nMode++] = 'b'; // , nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      //i32 nHandle = _open_osfhandle(m_hFile, nFlags);

      // open a C-runtime stream from that handle
      //if (nHandle != -1)
      m_pStream = fopen(lpszFileName, szMode);


      if (m_pStream == nullptr)
      {
         ::file::exception * pexception = get_Fileexception(::file::exception::type_generic, errno, m_strFileName);
         // an error somewhere along the way...
         //if (pException != nullptr)
         {
            //         pException->m_lOsError = errno;
            //         pException->m_cause = ::file::exception::OsErrorToException(errno);
         }

         ::ios::file::Abort(); // close m_hFile
         return pexception;
      }

      m_strFileName = lpszFileName;

      return ::success;
   }

   uptr stdio_file::read(void * lpBuf, uptr nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      //   ASSERT(fx_is_valid_address(lpBuf, nCount));

      size_t nRead = 0;

      if ((nRead = fread(lpBuf, sizeof(byte), nCount, m_pStream)) == 0 && !feof(m_pStream))
         vfxThrowFileexception(::file::exception::type_generic, errno, m_strFileName);
      if (ferror(m_pStream))
      {
         clearerr(m_pStream);
         vfxThrowFileexception(::file::exception::type_generic, errno, m_strFileName);
      }
      return nRead;
   }

   void stdio_file::write(const void * lpBuf, uptr nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
      //   ASSERT(fx_is_valid_address(lpBuf, nCount, false));

      if (fwrite(lpBuf, sizeof(byte), nCount, m_pStream) != nCount)
         vfxThrowFileexception(::file::exception::type_generic, errno, m_strFileName);
   }

   void stdio_file::write_string(const ::string & lpsz)
   {
      ASSERT(lpsz != nullptr);
      ASSERT(m_pStream != nullptr);

      if (fputs(lpsz, m_pStream) == EOF)
         vfxThrowFileexception(::file::exception::diskFull, errno, m_strFileName);
   }

   char * stdio_file::read_string(char * lpsz, ::u32 nMax)
   {
      ASSERT(lpsz != nullptr);
      //   ASSERT(fx_is_valid_address(lpsz, nMax));
      ASSERT(m_pStream != nullptr);

      char * lpszResult = fgets(lpsz, nMax, m_pStream);
      if (lpszResult == nullptr && !feof(m_pStream))
      {
         clearerr(m_pStream);
         vfxThrowFileexception(::file::exception::type_generic, errno, m_strFileName);
      }

      return lpszResult;
   }


   bool stdio_file::read_string(string & rString)
   {

      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const i32 nMaxSize = 128;
      char * lpsz = rString.GetBuffer(nMaxSize);
      char * lpszResult;
      strsize nLen = 0;
      for (;;)
      {
         lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
         rString.ReleaseBuffer();

         // handle error/eof case
         if (lpszResult == nullptr && !feof(m_pStream))
         {
            clearerr(m_pStream);
            vfxThrowFileexception(::file::exception::type_generic, errno,
                                  m_strFileName);
         }

         // if string is read completely or EOF
         if (lpszResult == nullptr ||
               (nLen = strlen(lpsz)) < nMaxSize ||
               lpsz[nLen-1] == '\n')
            break;

         nLen = rString.get_length();
         lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;
      }

      // remov '\n' from end of string if present
      lpsz = rString.GetBuffer(0);
      nLen = rString.get_length();
      if (nLen != 0 && lpsz[nLen-1] == '\n')
         rString.get_string_buffer(nLen-1);

      return lpszResult != nullptr;
   }

   /*void stdio_file::write_string(const ::string & lpsz)
    {
    ASSERT(lpsz != nullptr);
    ASSERT(m_pStream != nullptr);

    if (fputws(lpsz, m_pStream) == _TEOF)
    vfxThrowFileexception(::file::exception::diskFull, errno, m_strFileName);
    }*/

   /*unichar * stdio_file::read_string(unichar * lpsz, ::u32 nMax)
    {
    ASSERT(lpsz != nullptr);
    ASSERT(fx_is_valid_address(lpsz, nMax));
    ASSERT(m_pStream != nullptr);

    unichar * lpszResult = fgetws(lpsz, nMax, m_pStream);
    if (lpszResult == nullptr && !feof(m_pStream))
    {
    clearerr(m_pStream);
    vfxThrowFileexception(::file::exception::type_generic, errno, m_strFileName);
    }
    return lpszResult;
    }*/

   filesize stdio_file::seek(filesize lOff, ::enum_seek eseek)
   {
      ASSERT_VALID(this);
      ASSERT(eseek == ::e_seek_set || eseek== ::e_seek_end || eseek== ::e_seek_current);
      ASSERT(m_pStream != nullptr);

      i32 nFrom;
      switch(eseek)
      {
      case ::e_seek_set:
         nFrom = SEEK_SET;
         break;
      case ::e_seek_end:
         nFrom = SEEK_END;
         break;
      case ::e_seek_current:
         nFrom = SEEK_CUR;
         break;
      default:
         vfxThrowFileexception(::file::exception::badSeek, -1, m_strFileName);
      }

      if (fseek(m_pStream, lOff, nFrom) != 0)
         vfxThrowFileexception(::file::exception::badSeek, errno,
                               m_strFileName);

      long pos = ftell(m_pStream);
      return pos;
   }

   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos == -1)
         vfxThrowFileexception(::file::exception::invalidFile, errno,
                               m_strFileName);
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
         vfxThrowFileexception(::file::exception::diskFull, errno,
                               m_strFileName);
   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      i32 nErr = 0;

      if (m_pStream != nullptr)
         nErr = fclose(m_pStream);

      //   m_hFile = (::u32) hFileNull;
      //      m_bCloseOnDelete = false;
      m_pStream = nullptr;

      if (nErr != 0)
         vfxThrowFileexception(::file::exception::diskFull, errno,
                               m_strFileName);
   }

   void stdio_file::Abort()
   {
      ASSERT_VALID(this);

      //      if (m_pStream != nullptr && m_bCloseOnDelete)
      if (m_pStream != nullptr)
         fclose(m_pStream);  // close but ignore errors
      //   m_hFile = (::u32) hFileNull;
      m_pStream = nullptr;
      //      m_bCloseOnDelete = false;
   }

   __pointer(::file::file) stdio_file::Duplicate() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      __throw(error_not_supported);
      return nullptr;
   }

   void stdio_file::LockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      __throw(error_not_supported);
   }

   void stdio_file::UnlockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      __throw(error_not_supported);
   }


   void stdio_file::dump(dump_context & dumpcontext) const
   {

      ::ios::file::dump(dumpcontext);

      dumpcontext << "m_pStream = " << (void *)m_pStream;

      dumpcontext << "\n";
      
   }


   filesize stdio_file::get_length() const
   {
      ASSERT_VALID(this);

      long nCurrent;
      long nLength;
      long nResult;

      nCurrent = ftell(m_pStream);
      if (nCurrent == -1)
         vfxThrowFileexception(::file::exception::invalidFile, errno,
                               m_strFileName);

      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         vfxThrowFileexception(::file::exception::badSeek, errno,
                               m_strFileName);

      nLength = ftell(m_pStream);
      if (nLength == -1)
         vfxThrowFileexception(::file::exception::invalidFile, errno,
                               m_strFileName);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         vfxThrowFileexception(::file::exception::badSeek, errno,
                               m_strFileName);

      return nLength;
   }


} // namespace ios





