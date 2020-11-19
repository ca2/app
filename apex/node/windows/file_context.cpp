#include "framework.h"
#include "apex/os/_os.h"
#include "apex/node/_node.h"
#include "acme/os/windows_common/_file_c.h"
#include "acme/os/windows_common/file.h"


namespace windows
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }


   ::estatus file_context::initialize(::layered * pobjectContext)
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


   ::estatus file_context::init_system()
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
      bool b = vfxFullPath(wstrFileOut.get_string_buffer(MAX_PATH * 8), wstrFileIn) != FALSE;
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

      return vfxFullPath(wstrFullPath, wstrPath) != FALSE;

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

   var file_context::length(const ::file::path & path)
   {

      var varRet;

      varRet = ::file_context::length(path);

      if (!varRet.is_null())
         return varRet;


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


   bool file_context::get_last_write_time(FILETIME * pfiletime, const string & strFilename)
   {

      WIN32_FILE_ATTRIBUTE_DATA data;

      ·zero(data);

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
         return FALSE;
      }
      ::str::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);

      WIN32_FIND_DATAW findFileData;
      HANDLE hFind = FindFirstFileW((LPWSTR)(const widechar *)wstrFullName, &findFileData);
      if (hFind == INVALID_HANDLE_VALUE)
         return FALSE;
      VERIFY(FindClose(hFind));

      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      rStatus.m_attribute = (byte)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

      // get just the low ::u32 of the file size
      ASSERT(findFileData.nFileSizeHigh == 0);
      rStatus.m_size = (::i32)findFileData.nFileSizeLow;

      // convert times as appropriate
      rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
      rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
      rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);

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


   ::estatus file_context::update_module_path()
   {

      auto estatus = ::file_context::update_module_path();

      if(!estatus)
   {
      
      return estatus;
      
   }

      return estatus;

   }


   file_result file_context::get_file(const var & varFile, const efileopen & eopenFlags)
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


