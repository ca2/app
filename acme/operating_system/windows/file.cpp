// Created by camilo on 2023-03-14 09:48 <3ThomasBorregaardSorensen!!
#include "framework.h"


#include "acme/_operating_system.h"


namespace windows
{


   file::file(::file::path & path, ::windows_path & windowspath, ::file::e_open & eopen, HANDLE handleFile) :
      handle(handleFile),
      m_path(path),
      m_windowspath(windowspath),
      m_eopen(eopen)
   {
   
   }


   file::~file() 
   {
   
   }


   void file::create_file(const ::file::path & path, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
   {

      m_path = path;

      auto strWindowsPath = path.windows_path();

      m_windowspath = strWindowsPath;

#ifdef _UWP

      LPCREATEFILE2_EXTENDED_PARAMETERS pextendedparameters = nullptr;

      CREATEFILE2_EXTENDED_PARAMETERS extendedparameters;

      if (lpSecurityAttributes)
      {

         extendedparameters.lpSecurityAttributes = &securityattributes;

      }

      m_handle = ::CreateFile2(
         m_windowspath,
         dwDesiredAccess,
         dwShareMode,
         dwCreationDisposition,
         pextendedparameters);

#else

      m_handle = CreateFileW(
         m_windowspath,
         dwDesiredAccess,
         dwShareMode,
         lpSecurityAttributes,
         dwCreationDisposition,
         dwFlagsAndAttributes,
         hTemplateFile);

#endif

   }


   void file::_create_file(const ::file::path & path, const ::file::e_open & eopen)
   {

      m_eopen = eopen;

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      // map read/write mode
      ASSERT((::file::e_open_read | ::file::e_open_write | ::file::e_open_read_write) == 3);
      DWORD dwDesiredAccess = 0;
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwDesiredAccess = GENERIC_READ;
         break;
      case ::file::e_open_write:
         dwDesiredAccess = GENERIC_WRITE;
         break;
      case ::file::e_open_read_write:
         dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
         break;
      default:
         dwDesiredAccess = GENERIC_READ;
         break;
      }

      auto eopenShare = eopen & ::file::e_open_share_mask;

      // map share mode
      DWORD dwShareMode = 0;
      switch (eopenShare)    // map compatibility mode to exclusive
      {
      default:
         ASSERT(false);  // invalid share mode?
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
         dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
         break;
      }


      // Note: type_text and type_binary are used in derived classes only.

      LPSECURITY_ATTRIBUTES lpSecurityattributes{};

      // map modeNoInherit flag
      SECURITY_ATTRIBUTES securityattributes;

      if (eopen & ::file::e_open_no_inherit)
      {

         securityattributes.nLength = sizeof(securityattributes);

         securityattributes.lpSecurityDescriptor = nullptr;

         securityattributes.bInheritHandle = false;

         lpSecurityattributes = &securityattributes;

      }

      DWORD dwCreationDisposition;

      if (eopen & ::file::e_open_create)
      {

         if (eopen & ::file::e_open_no_truncate)
         {

            dwCreationDisposition = OPEN_ALWAYS;

         }
         else
         {

            dwCreationDisposition = CREATE_ALWAYS;

         }

      }
      else
      {

         dwCreationDisposition = OPEN_EXISTING;

      }

      create_file(path, dwDesiredAccess, dwShareMode, lpSecurityattributes, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);

   }


   void file::create_file(const ::file::path & path, const ::file::e_open & eopen)
   {

      _create_file(path, eopen);

      if (nok())
      {

         throw_exception();

      }

   }


   DWORD file::defer_write(const ::block & block, LPOVERLAPPED lpOverlapped)
   {

      DWORD dwWritten{};

      auto bytesToWrite = natural_minimum(block.size(), MAXDWORD);

      if (!::WriteFile(m_handle, block.data(), bytesToWrite, &dwWritten, lpOverlapped))
      {

         throw_exception();

      }

      return dwWritten;

   }


   void file::write(const ::block & block, LPOVERLAPPED lpOverlapped)
   {

      auto amountWritten = defer_write(block, lpOverlapped);

      if (amountWritten != block.size())
      {

         if (amountWritten < block.size())
         {

            throw_exception("nWritten < nCount - is disk full?", -1);

         }
         else
         {

            throw_exception("nWritten >= nCount", -1);

         }

      }

   }


   [[nodiscard ]] memsize file::read(const ::block& block, LPOVERLAPPED lpOverlapped)
   {

      memsize totalRead = 0;

      DWORD dwRead{};

      auto p = block.data();

      auto s = block.size();

      while (s > 0)
      {

         auto amountToRead = ::minimum(s, MAXDWORD);

         if (!::ReadFile(m_handle, p, amountToRead, &dwRead, lpOverlapped))
         {

            throw_exception();

         }

         if (dwRead <= 0)
         {

            break;

         }

         p += dwRead;

         totalRead += dwRead;

         s -= dwRead;

      }

      return totalRead;

   }


   void file::flush_file_buffers()
   {

      if (!::FlushFileBuffers(m_handle))
      {

         auto lasterror = ::GetLastError();

         if (lasterror == ERROR_INVALID_HANDLE || lasterror == ERROR_ACCESS_DENIED)
         {

         }
         else if (lasterror == ERROR_NO_SYSTEM_RESOURCES)
         {

            ::output_debug_string("Insufficient system resources exist to complete the requested service. (::windows::file::flush_file_buffers())");

         }
         else
         {

            throw_exception();

         }

      }

   }


   ::i64 file::get_file_size() const
   {

      LARGE_INTEGER largeintegerFileSize{};

      if (!::GetFileSizeEx(m_handle, &largeintegerFileSize))
      {

         throw_exception();

      }

      return largeintegerFileSize.QuadPart;

   }


   void file::ensure_file_size(i64 iSize)
   {

      auto iSizeCurrent = get_file_size();

      if (iSizeCurrent != iSize)
      {

         set_file_size(iSize);

      }

   }


   void file::set_file_size(::i64 iSize)
   {

      set_file_pointer_ex(iSize, nullptr, SEEK_SET);

      set_end_of_file();

   }


   void file::set_file_pointer_ex(::i64 iOffset, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod)
   {

      LARGE_INTEGER largeinteger{.QuadPart = iOffset };

      if (!::SetFilePointerEx(m_handle, largeinteger, lpNewFilePointer, dwMoveMethod))
      {

         throw_exception();

      }

   }


   void file::set_file_pointer(::i64 iOffset, DWORD dwMoveMethod)
   {

      set_file_pointer_ex(iOffset, nullptr, dwMoveMethod);

   }


   ::i64 file::get_file_pointer() const
   {

      LARGE_INTEGER largeinteger{};

      ((file *)this)->set_file_pointer_ex(0, &largeinteger, FILE_CURRENT);

      return largeinteger.QuadPart;

   }


   void file::set_end_of_file()
   {

      if (!::SetEndOfFile(m_handle))
      {

         throw_exception();

      }

   }


   void file::lock_file(::i64 iOffset, ::i64 iCount)
   {

      if (!::LockFile(m_handle, LODWORD(iOffset), HIDWORD(iOffset), LODWORD(iCount), HIDWORD(iCount)))
      {

         throw_exception();

      }

   }


   void file::unlock_file(::i64 iOffset, ::i64 iCount)
   {

      if (!::UnlockFile(m_handle, LODWORD(iOffset), HIDWORD(iOffset), LODWORD(iCount), HIDWORD(iCount)))
      {

         throw_exception();

      }

   }


   void file::set_file_time(const FILETIME * lpCreationTime, const FILETIME * lpLastAccessTime, const FILETIME * lpLastWriteTime)
   {

      if (!::SetFileTime(m_handle, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
      {

         throw_exception();

      }

   }


   void file::get_file_time(LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
   {

      if (!::GetFileTime(m_handle, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
      {

         throw_exception();

      }

   }


   void file::get_file_information(BY_HANDLE_FILE_INFORMATION & information) const
   {

      if (!::GetFileInformationByHandle(m_handle, &information))
      {

         throw_exception();

      }

   }


   [[ noreturn ]] void file::throw_exception(const ::scoped_string & scopedstrMessage, DWORD lasterror) const
   {

      if (!lasterror)
      {

         lasterror = ::GetLastError();

      }

      auto estatus = ::windows::last_error_status(lasterror);

      auto errorcode = ::windows::last_error_error_code(lasterror);

      throw ::file::exception(estatus, errorcode, m_path, m_eopen, scopedstrMessage);

   }


} // namespace windows



