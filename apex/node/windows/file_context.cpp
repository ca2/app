#include "framework.h"
#include "apex/operating_system.h"


namespace windows
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }


   ::e_status file_context::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __refer(m_pfilesystem, System.m_pfilesystem);

      __refer(m_pdirsystem, System.m_pdirsystem);

      return ::success;

   }


   ::e_status file_context::init_system()
   {

      auto estatus = m_pfilesystem->update_module_path();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   bool file_context::FullPath(string & str, const char * pszFileIn)

   {

      //if(::apex::file_context::FullPath(str, pszFileIn))

      // return true;

      if (::str::begins_ci(pszFileIn, "http://"))

      {

         str = pszFileIn;


         return true;

      }
      else if (::str::begins_ci(pszFileIn, "https://"))

      {

         str = pszFileIn;


         return true;

      }
      wstring wstrFileIn;
      wstrFileIn = ::str::international::utf8_to_unicode(pszFileIn);

      wstring wstrFileOut;
      bool b = vfxFullPath(wstrFileOut.get_string_buffer(MAX_PATH * 8), wstrFileIn) != false;
      if (b)
      {
         ::str::international::unicode_to_utf8(str, wstrFileOut);
      }
      return b;
   }

   bool file_context::FullPath(wstring & wstrFullPath, const wstring & wstrPath)
   {

      /*      if(::apex::file_context::FullPath(wstrFullPath, wstrPath))
      return true;*/

      if (::str::begins_ci(wstrPath, L"http://"))
      {
         wstrFullPath = wstrPath;
         return true;
      }
      else if (::str::begins_ci(wstrPath, L"https://"))
      {
         wstrFullPath = wstrPath;
         return true;
      }

      return vfxFullPath(wstrFullPath, wstrPath) != false;

   }


   ::u32 file_context::GetFileName(const char * pszPathName, string & str)

   {
      i32 nMax = MAX_PATH * 8;
      wstring wstrPathName;
      wstrPathName = ::str::international::utf8_to_unicode(pszPathName);

      wstring wstrTitle;
      ::u32 user = vfxGetFileName(wstrPathName, wstrTitle.get_string_buffer(nMax), nMax);
      str = ::str::international::unicode_to_utf8(wstrTitle);
      return user;
   }

   void file_context::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
   {
      vfxGetModuleShortFileName(hInst, strShortName);
   }

   ::payload file_context::length(const ::file::path & path)
   {

      ::payload varRet;

      //varRet = ::file_context::length(path);

      //if (!varRet.is_null())
      //   return varRet;


#ifdef WINDOWS

      WIN32_FILE_ATTRIBUTE_DATA data;

      if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = (u32)data.nFileSizeLow;
      }

#else

      struct stat stat;

      if (::stat(strPath, &stat) == -1)
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = stat.st_size;
      }

#endif

      return varRet;

   }


   ::payload file_context::length(const ::file::path & path, ::payload * pvarQuery)
   {

      // TODO: I don't remember what pvarQuery is used for, in the time of reimplementation
      // of this function. Maybe you should consider it in some case(s).

      return length(path);

   }


   ::status::result file_context::move(const ::file::path & pszNew, const ::file::path & psz)
   {


#ifdef WINDOWS_DESKTOP

      if (!::MoveFileW(
         ::str::international::utf8_to_unicode(psz),
         ::str::international::utf8_to_unicode(pszNew)))
      {

         DWORD dwError = ::GetLastError();

         if (dwError == ERROR_ALREADY_EXISTS)
         {

            if (::CopyFileW(
               ::str::international::utf8_to_unicode(psz),
               ::str::international::utf8_to_unicode(pszNew),
               false))
            {

               if (!::DeleteFileW(::str::international::utf8_to_unicode(psz)))
               {

                  dwError = ::GetLastError();

                  string strError;

                  strError.Format("Failed to delete the file to move \"%s\" error=%d", psz, dwError);

                  TRACE("%s", strError);

               }

               return ::success;

            }

            dwError = ::GetLastError();

         }

         string strError;

         strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);

         __throw(io_exception(::error_io, strError));

      }

#elif defined(_UWP)

      ::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);

      if (file == nullptr)
      {

         //output_debug_string("test");

         __throw(::exception::exception("file::file_context::move Could not move file, could not open source file"));

      }

      string strDirOld = psz.folder();
      string strDirNew = pszNew.folder();
      string strNameOld = psz.name();
      string strNameNew = pszNew.name();

      if (strDirOld == strDirNew)
      {
         if (strNameOld == strNameNew)
         {
            return ::success;
         }
         else
         {
            ::wait(file->RenameAsync(strNameNew));
         }
      }
      else
      {
         ::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
         if (strNameOld == strNameNew)
         {
            ::wait(file->MoveAsync(folder));
         }
         else
         {
            ::wait(file->MoveAsync(folder, strNameNew));
         }
      }


#else
      if (::rename(psz, pszNew) != 0)
      {
         i32 err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         __throw(::exception::exception(strError));
      }
#endif

      return ::success;

   }


   ::status::result file_context::del(const ::file::path & psz)
   {


#ifdef WINDOWS_DESKTOP

      HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz),
         GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
         FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, nullptr);

      if (h == INVALID_HANDLE_VALUE)
      {

         DWORD dwError = ::GetLastError();

         if (dwError == 2) // the file does not exist, so delete "failed"
         {

            return ::success;

         }

         string strError;

         strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);

         return ::error_failed;

      }
      else
      {
         ::FlushFileBuffers(h);
         ::CloseHandle(h);
      }

      /*      if(!::DeleteFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz)))
      {
      u32 dwError = ::get_last_error();
      if(dwError == 2) // the file does not exist, so delete "failed"
      return;
      string strError;
      strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
      __throw(io_exception(strError));
      }*/


#else

      if (unlink(psz) != 0)
      {
         i32 err = errno;
         if (err != ENOENT) // already does not exist - consider removal successful - does not issue an exception
         {
            string strError;
            strError.Format("Failed to delete file error=%d", err);
            __throw(::exception::exception(strError));
         }
      }
#endif

      return ::success;

   }


   bool file_context::is_read_only(const ::file::path & psz)
   {

#ifdef WINDOWS_DESKTOP

      u32 dwAttrib = windows_get_file_attributes(psz);

      if (dwAttrib & FILE_ATTRIBUTE_READONLY)
      {

         return true;

      }

      return false;

#elif defined(_UWP)

      __throw(todo());

#else

      struct stat st;

      if (stat(psz, &st) != 0)
         return true;

      return !(st.st_mode & S_IWUSR);

#endif

   }


   rp(::file::file) file_context::resource_get_file(const ::file::path & path)
   {

#ifdef WINDOWS_DESKTOP

      auto pfile = create_memory_file();

      int iId = atoi(path);

      string strExtension = path.final_extension();

      strExtension.make_upper();
      const char * psz = strExtension;
      if (strExtension == "HTML")
      {

         psz = (const char *)RT_HTML;

      }

      if (read_resource_as_memory(*pfile->get_primitive_memory(), (HINSTANCE) System.m_hinstance, iId, psz))
      {

         return pfile;

      }

#else

      throw_todo();

#endif

      return nullptr;

   }


   bool file_context::get_last_write_time(FILETIME * pfiletime, const string & strFilename)
   {

      WIN32_FILE_ATTRIBUTE_DATA data;

      __zero(data);

      if (!GetFileAttributesExW(wstring(strFilename), GetFileExInfoStandard, &data))
      {

         return false;

      }

      *pfiletime = data.ftLastWriteTime;

      return true;

   }




   bool file_context::get_status(const ::file::path & path, ::file::file_status & rStatus)
   {

      // attempt to fully qualify path first
      wstring wstrFullName;
      wstring wstrFileName;
      wstrFileName = ::str::international::utf8_to_unicode(path);
      if (!vfxFullPath(wstrFullName, wstrFileName))
      {
         rStatus.m_strFullName.Empty();
         return false;
      }
      ::str::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);

      WIN32_FIND_DATAW findFileData;
      HANDLE hFind = FindFirstFileW((LPWSTR)(const widechar *)wstrFullName, &findFileData);
      if (hFind == INVALID_HANDLE_VALUE)
         return false;
      VERIFY(FindClose(hFind));

      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      rStatus.m_attribute = (byte)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

      // get just the low ::u32 of the file size_i32
      ASSERT(findFileData.nFileSizeHigh == 0);
      rStatus.m_size = (::i32)findFileData.nFileSizeLow;

      // convert times as appropriate
      rStatus.m_ctime = __time(findFileData.ftCreationTime);
      rStatus.m_atime = __time(findFileData.ftLastAccessTime);
      rStatus.m_mtime = __time(findFileData.ftLastWriteTime);

      if (rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;

      if (rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;

      return true;

   }

   //void file_context::set_status(const ::file::path & path,const ::file::file_status& status)
   //{

   //   wstring pszFileName(path);

   //   ::u32 wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME pCreationTime = nullptr;

   //   LPFILETIME pLastAccessTime = nullptr;

   //   LPFILETIME pLastWriteTime = nullptr;


   //   if((wAttr = windows_get_file_attributes((LPWSTR)(const widechar *)pszFileName)) == (::u32)-1L)

   //      file_exception::throw_os_error((::i32)GetLastError());

   //   if((::u32)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributesW((LPWSTR)(const widechar *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::apex::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      pLastWriteTime = &lastWriteTime;


   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         pLastAccessTime = &lastAccessTime;

   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_ctime,&creationTime);
   //         pCreationTime = &creationTime;

   //      }

   //      HANDLE hFile = ::CreateFileW((LPWSTR)(const widechar *)pszFileName,GENERIC_READ | GENERIC_WRITE,

   //         FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         nullptr);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,pCreationTime,lpLastAccessTime,lpLastWriteTime))

   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::throw_os_error((::i32)::GetLastError());
   //   }

   //   if((::u32)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }
   //}


   //void file::SetStatus(const char * pszFileName,const ::file::file_status& status)

   //{
   //   ::u32 wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME pCreationTime = nullptr;

   //   LPFILETIME pLastAccessTime = nullptr;

   //   LPFILETIME pLastWriteTime = nullptr;


   //   if((wAttr = GetFileAttributes((char *)pszFileName)) == (::u32)-1L)

   //      file_exception::throw_os_error((::i32)GetLastError());

   //   if((::u32)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::apex::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      pLastWriteTime = &lastWriteTime;


   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         pLastAccessTime = &lastAccessTime;

   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_ctime,&creationTime);
   //         pCreationTime = &creationTime;

   //      }

   //      HANDLE hFile = ::CreateFile(pszFileName,GENERIC_READ | GENERIC_WRITE,

   //         FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         nullptr);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,pCreationTime,lpLastAccessTime,lpLastWriteTime))

   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::throw_os_error((::i32)::GetLastError());
   //   }

   //   if((::u32)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }
   //}

   ::status::result file_context::set_status(const ::file::path & path, const ::file::file_status & status)
   {

      wstring pszFileName(path);


      ::u32 wAttr;
      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME pCreationTime = nullptr;

      LPFILETIME pLastAccessTime = nullptr;

      LPFILETIME pLastWriteTime = nullptr;


      if ((wAttr = windows_get_file_attributes(path)) == (::u32)INVALID_FILE_ATTRIBUTES)
      {

         ::file::throw_os_error(::GetLastError());

      }

      if ((::u32)status.m_attribute != wAttr && (wAttr & FILE_ATTRIBUTE_READONLY))
      {
         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         if (!SetFileAttributesW((LPWSTR)(const widechar *)pszFileName, (::u32)status.m_attribute))
         {

            ::file::throw_os_error(::GetLastError());

         }

      }

      // last modification time
      if (status.m_mtime.get_time() != 0)
      {
         
         lastWriteTime = __FILETIME(status.m_mtime);

         pLastWriteTime = &lastWriteTime;

         // last access time
         if (status.m_atime.get_time() != 0)
         {

            lastAccessTime = __FILETIME(status.m_atime);

            pLastAccessTime = &lastAccessTime;

         }

         // create time
         if (status.m_ctime.get_time() != 0)
         {

            creationTime = __FILETIME(status.m_ctime);

            pCreationTime = &creationTime;

         }

         HANDLE hFile = ::CreateFileW((LPWSTR)(const widechar *)pszFileName, GENERIC_READ | GENERIC_WRITE,

            FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
            nullptr);

         if (hFile == INVALID_HANDLE_VALUE)
         {

            return ::os_error_to_status(::GetLastError());

         }

         if (!SetFileTime((HANDLE)hFile, pCreationTime, pLastAccessTime, pLastWriteTime))
         {

            return ::os_error_to_status(::GetLastError());

         }

         if (!::CloseHandle(hFile))
         {

            return ::os_error_to_status(::GetLastError());

         }

      }

      if ((::u32)status.m_attribute != wAttr && !(wAttr & FILE_ATTRIBUTE_READONLY))
      {

         if (!SetFileAttributesW((LPWSTR)(const widechar *)pszFileName, (::u32)status.m_attribute))
         {

            return ::os_error_to_status(::GetLastError());

         }

      }

      return ::success;

   }


   ::e_status file_context::update_module_path()
   {

      auto estatus = ::file_context::update_module_path();

      if(!estatus)
   {
      
      return estatus;
      
   }

      return estatus;

   }


   file_result file_context::get_file(const ::payload & varFile, const ::file::e_open & eopenFlags)
   {

      return ::file_context::get_file(varFile, eopenFlags);

   }


   ::file::path file_context::dropbox_info_json()
   {

      ::file::path pathJson;

      pathJson = user_appdata_local() / "Dropbox/info.json";

      return pathJson;

   }


} // namespace windows


