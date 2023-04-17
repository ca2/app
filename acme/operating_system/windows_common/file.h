// Created by camilo on 2023-03-14 09:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/windows_common/handle.h"


namespace windows
{


   class CLASS_DECL_ACME file :
      public ::windows::handle
   {
   public:


      ::file::path &       m_path;
      ::windows_path &     m_windowspath;
      ::file::e_open &     m_eopen;


      file(::file::path & path, ::windows_path & windowspath, ::file::e_open & eopen, HANDLE handleFile = INVALID_HANDLE_VALUE);
      ~file();


      bool safe_create_file(const ::file::path & path, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

      void _create_file(const ::file::path & path, ::file::e_open eopen);

      void create_file(const ::file::path & path, ::file::e_open eopen);


      /// @brief 
      /// @param block 
      /// @param lpOverlapped 
      /// @return number of bytes written 
      [[nodiscard ]] DWORD defer_write(const void * p, ::memsize s, LPOVERLAPPED lpOverlapped = nullptr);

      void write(const void * p, ::memsize s, LPOVERLAPPED lpOverlapped = nullptr);

      /// @brief 
      /// @param block 
      /// @param lpOverlapped 
      /// @return number of bytes read 
      [[nodiscard ]] ::memsize read(void * p, ::memsize s, LPOVERLAPPED lpOverlapped = nullptr);

      void flush_file_buffers();

      ::i64 get_file_size() const;

      void ensure_file_size(::i64 iSize);

      void set_file_size(::i64 iSize);

      void set_file_pointer_ex(::i64 iOffset, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod);

      void set_file_pointer(::i64 iOffset, DWORD dwMoveMethod);

      ::i64 get_file_pointer() const;

      void set_end_of_file();

      void lock_file(::i64 iOffset, ::i64 iCount);

      void unlock_file(::i64 iOffset, ::i64 iCount);

      void set_file_time(const FILETIME * lpCreationTime, const FILETIME * lpLastAccessTime, const FILETIME * lpLastWriteTime);

      void get_file_time(LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

      void get_file_information(BY_HANDLE_FILE_INFORMATION & information) const;

      [[nodiscard]] ::file::path get_final_path_by_handle() const;

      [[ noreturn ]] void throw_last_error_exception(const ::scoped_string & scopedstrErrorMessage = nullptr, DWORD lasterror = 0) const;


   };


   class CLASS_DECL_ACME file_instance :
      public ::windows::file
   {
   public:


      ::file::path m_pathInstance;
      ::windows_path m_windowspathInstance;
      ::file::e_open m_eopenInstance;


      file_instance() : 
         file(m_pathInstance, m_windowspathInstance, m_eopenInstance)
      {
      
         m_eopenInstance = ::file::e_open_none;
      
      }


      ~file_instance() {}


   };


} // namespace windows



