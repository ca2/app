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


   void stdio_file::open(const ::file::path & path, const ::string & strAttributes, int iShare)
   {

#ifdef WINDOWS

      m_pfile = _wfsopen(pszFileName, strAttributes, _SH_DENYNO);

#else

      m_pfile = fopen(pszFileName, strAttributes);

#endif

      if(!m_pfile)
      {

         return error_io;

      }

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
//   ASSERT(fx_is_valid_address(pdata, nCount, false));


      if (fwrite(pdata, sizeof(byte), nCount, m_pStream) != nCount)

         ::file::throw_status(error_file, errno, m_path);
   }

   void stdio_file::write_string(const ::string & psz)

   {
      ASSERT(psz != nullptr);

      ASSERT(m_pStream != nullptr);

      if (fputs(psz, m_pStream) == EOF)

         ::file::throw_status(error_disk_full, errno, m_path);
   }

   char * stdio_file::read_string(char * psz, ::u32 nMax)

   {
      ASSERT(psz != nullptr);

//   ASSERT(fx_is_valid_address(psz, nMax));

      ASSERT(m_pStream != nullptr);

      char * pszResult = fgets(psz, nMax, m_pStream);

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

   /*void stdio_file::write_string(const ::string & psz)

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
      //m_bCloseOnDelete = false;
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
      //m_bCloseOnDelete = false;
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
