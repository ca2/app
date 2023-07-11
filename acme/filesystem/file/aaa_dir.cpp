#include "framework.h"
#include "acme/operating_system.h"


#if defined(WINDOWS_DESKTOP)
#include <Shlobj.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(LINUX)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(UNIVERSAL_WINDOWS)
#include "acme/operating_system/universal_windows/file_winrt.h"
#endif




void TranslateLastError()
{

   if(errno == EEXIST)
   {

      set_last_status(error_already_exists);

   }
   else
   {

      set_last_status(::success);

   }

}


#ifdef WINDOWS

bool windows_file_find_is_dots(WIN32_FIND_DATAW & data);

#endif


#if defined(UNIVERSAL_WINDOWS)

#pragma push_macro("acmesystem()")

#undef acmesystem()

using namespace ::winrt::Windowsacmesystem();

#pragma pop_macro("acmesystem()")

#endif


namespace dir
{


      string name(const ::file::path & path1)
      {
         const ::scoped_string & scopedstr = path1 + strlen(path1) - 1;
         while(psz >= path1)
         {
            if(*psz != '\\' && *psz != '/' && *psz != ':')
               break;
            psz--;
         }
         while(psz >= path1)
         {
            if(*psz == '\\' || *psz == '/' || *psz == ':')
               break;
            psz--;
         }
         if(psz >= path1) // strChar == "\\" || strChar == "/"
         {
            const ::ansi_character * pszEnd = psz;
            /*while(psz >= path1)
             {
             if(*psz != '\\' && *psz != '/' && *psz != ':')
             break;
             psz--;
             }*/
            return string(path1, pszEnd - path1 + 1);
         }
         else
         {
            return "";
         }
      }
   


//   ::file::path ca2_module()
//   {
//
//   #if defined(ANDROID)
//
//      return acmepath()->app_module().folder();
//
//   #elif defined(UNIVERSAL_WINDOWS)
//
//      wstring wstrModuleFilePath;
//
//      auto pwszModuleFilePath = wstrModuleFilePath.get_buffer(MAX_PATH * 8);
//
//      if (!GetModuleFileNameW(nullptr, pwszModuleFilePath, MAX_PATH * 8))
//      {
//         
//         return "";
//         
//      }
//
//      wstrModuleFilePath.release_buffer();
//
//      LPWSTR pszModuleFileName;
//
//      wstring wstrModuleFolder;
//
//      auto pwszModuleFolder = wstrModuleFolder.get_buffer(MAX_PATH * 8);
//
//      if (!GetFullPathNameW(wstrModuleFilePath, MAX_PATH * 8, pwszModuleFolder, &pszModuleFileName))
//      {
//
//         return "";
//         
//      }
//
//      wstrModuleFolder.release_buffer();
//
//      wstrModuleFolder.case_insensitive_ends_eat("\\");
//      wstrModuleFolder.case_insensitive_ends_eat("/");
//      wstrModuleFolder.case_insensitive_ends_eat("\\");
//      wstrModuleFolder.case_insensitive_ends_eat("/");
//
//      return string(wstrModuleFolder);
//
//
//   #elif defined(WINDOWS)
//
//
//      wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);
//
//
//      wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
//
//
//      HMODULE hmodule = ::GetModuleHandleA("acme.dll");
//
//      if(hmodule == nullptr)
//         hmodule = ::GetModuleHandleA("spalib.dll");
//
//      if(hmodule == nullptr)
//      {
//
//         cotaskp(PWSTR) pwstr;
//
//         HRESULT hr = SHGetKnownFolderPath(
//                      FOLDERID_ProgramFilesX86,
//                      KF_FLAG_DEFAULT,
//                      nullptr,
//                      &pwstr);
//
//         wcscpy(wstrModuleFilePath, pwstr);
//
//
//         //if(wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '\\'
//
//         //      || wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '/')
//
//         //{
//         //   wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] = '\0';
//
//         //}
//         wcscat(wstrModuleFilePath, L"\\ca2\\");
//
//   #ifdef X86
//         wcscat(wstrModuleFilePath,L"stage\\x86\\");
//
//   #else
//         wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");
//
//   #endif
//
//         wcscpy(wstrModuleFolder, wstrModuleFilePath);
//
//         wstrModuleFilePath.release_buffer();
//
//         return string(wstrModuleFolder);
//
//
//      }
//
//      if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (::u32)wstrModuleFilePath.length()))
//      {
//
//         return "";
//
//      }
//
//      wstrModuleFilePath.release_buffer();
//
//      LPWSTR pszModuleFileName;
//
//      if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
//      {
//
//         return "";
//
//      }
//
//      wstrModuleFolder.release_buffer();
//
//      if(wstrModuleFolder.has_char())
//      {
//
//         wstrModuleFolder.trim_right(L"\\/");
//
//      }
//
//      return wstrModuleFolder;
//
//   #elif defined(__APPLE__)
//
//      string str;
//
//      {
//
////         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
////
////         if(str.has_char())
////         {
////            str = ::file::path(str).folder();
////            goto found;
////
////         }
////
////
////         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
////
////         if(str.has_char())
////         {
////            str = ::file::path(str).folder();
////            goto found;
////
////         }
//
//         str = get_exe_path();
//
//
//         if(str.has_char())
//         {
//            str = ::file::path(str).folder();
//            goto found;
//         }
//
//
//      }
//   found:
//      ;
//
//      return str;
//
//   #else
//
//      string strModuleFolder;
//
//      auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);
//
//      void * handle = dlopen("libacme.so", RTLD_NOW);
//
//      if(handle == nullptr)
//      {
//
//         strcpy(wstrModuleFolder, "/ca2/");
//
//      }
//      else
//      {
//
//         link_map * plm;
//
//         dlinfo(handle, RTLD_DI_LINKMAP, &plm);
//
//         strcpy(wstrModuleFolder, plm->l_name);
//
//         dlclose(handle);
//
//         strcpy(wstrModuleFolder, ::file_path_folder(wstrModuleFolder));
//
//      }
//
//      return string(wstrModuleFolder);
//
//
//
//   #endif
//
//
//   }


   ::file::path base_module()
   {

   #if defined(UNIVERSAL_WINDOWS)

      return "";

   #elif defined(WINDOWS)

      wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);

      wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);

      HMODULE hmodule = ::GetModuleHandleA("acme.dll");

      if (hmodule == nullptr)
      {

         hmodule = ::GetModuleHandleA("spalib.dll");

      }

      if (hmodule == nullptr)
      {

         wcscpy(wstrModuleFilePath,_wgetenv(L"PROGRAMFILES(X86)"));


         if(wstrModuleFilePath.empty())
         {

            SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

         }

         wstrModuleFilePath.trim_right(L"\\/");

         wcscat(wstrModuleFilePath, L"\\ca2\\");

   #ifdef X86

         wcscat(wstrModuleFilePath,L"stage\\x86\\");

   #else
         wide_concatenate(wstrModuleFilePath,L"stage\\x64\\");

   #endif

         wcscpy(wstrModuleFolder, wstrModuleFilePath);

         return string(wstrModuleFolder);

      }

      if(!GetModuleFileNameW(hmodule,wstrModuleFilePath, (::u32) wstrModuleFilePath.length()))
      {

         return "";

      }

      LPWSTR pszModuleFileName;

      if (!GetFullPathNameW(wstrModuleFilePath, (::u32) wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
      {

         return "";

      }

      wstrModuleFolder.release_buffer();

      wstrModuleFolder.trim_right(L"\\/");

      return wstrModuleFolder;

   #else

      string strModuleFolder;

      auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);

      throw ::exception(todo);

      return wstrModuleFolder;

   #endif

   }


// bool eat_end_level(string & str, i32 iLevelCount, const char * pSeparator)
// {

//    strsize iLast = str.length() - 1;

//    if(iLast < 0)
//       return iLevelCount <= 0;

//    while(str[iLast] == '/' || str[iLast] == '\\')
//       iLast--;

//    for(i32 i = 0; i < iLevelCount; i++)
//    {

//       strsize iFind1 = str.rear_find('/', iLast);

//       strsize iFind2 = str.rear_find('\\', iLast);

//       auto pFind = maximum(iFind1, iFind2);

//       if(iFind >= iLast)
//          return false;

//       if(::is_null(pFind))
//          return false;

//       iLast = iFind;

//       while(str[iLast] == '/' || str[iLast] == '\\')
//          iLast--;

//    }

//    str = str.substr(0, iLast + 1);

//    return true;

// }
//
//
//   string ca2_module_dup()
//   {
//
//      static string * s_pstrCalc = nullptr;
//
//      if(s_pstrCalc != nullptr)
//      {
//
//         return *s_pstrCalc;
//
//      }
//
//      string str;
//
//   #ifdef WINDOWS_DESKTOP
//
//      wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
//
//      GetModuleFileNameW(::GetModuleHandleA("acme.dll"), wstrModuleFilePath, MAX_PATH + 1);
//
//      str = (const unichar *) wstrModuleFilePath;
//
//   #elif defined(LINUX)
//
//      void * handle = dlopen("libacme.so", RTLD_NOW);
//
//      if(handle == nullptr)
//         return "";
//
//      link_map * plm;
//
//      dlinfo(handle, RTLD_DI_LINKMAP, &plm);
//
//      string strCa2ModuleFolder = plm->l_name;
//
//      dlclose(handle);
//
//      str = strCa2ModuleFolder;
//
//   #elif defined(UNIVERSAL_WINDOWS)
//
//      str = "";
//
//   #elif defined(__APPLE__)
//
//      {
//
//         str = get_exe_path();
//
//         if(str.has_char())
//         {
//
//            goto found;
//
//         }
//
//         str = ::dir::pathfind(::file::path(str).folder(), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
//
//         if(str.has_char())
//         {
//
//            goto found;
//
//         }
//
//         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
//
//         if(str.has_char())
//         {
//
//            goto found;
//
//         }
//
//         str = get_exe_path();
//
//         if(str.has_char())
//         {
//
//            goto found;
//
//         }
//
//         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
//
//         if(str.has_char())
//         {
//
//            goto found;
//
//         }
//
//      }
//
//   found:
//      ;
//
//   #endif
//
//      s_pstrCalc = memory_new string(str);
//
//      return *s_pstrCalc;
//
//
//   }



   bool mk(const ::file::path & path)
   {

      //if (::file::system_dir::g_pthis == nullptr)
      //{

         return _mk(path);

      //}

      //return ::file::system_dir::g_pthis->mk(path, ::get_context_system());

   }


#ifndef WINDOWS_DESKTOP


   bool _mk(const ::file::path & path)
   {

      if (is(path))
      {

         return true;

      }

      string strName;

      ::file::path pathDir;

      strsize iLastPos;

   #ifdef UNIVERSAL_WINDOWS

      {

         string strPath = path;

         string strPrefix;

         winrt_folder(strPath, strPrefix);

         pathDir = strPrefix;

         iLastPos = strPrefix.length();

      }

   #else

      iLastPos = -1;

   #endif

      ::file::path_array stra;

      path.ascendants_path(stra);

      index i = stra.get_upper_bound();

      for (; i >= 0; i--)
      {

         string strDir = stra[i];

         if (is(strDir))
         {

            break;

         }

      }

      if (i < 0)
      {

         return true;

      }

      for(; i < stra.get_count(); i++)
      {

         string strDir = stra[i];

         if (::dir::mkdir(strDir))
         {

         }
         else
         {

            auto estatus = ::get_last_status();

            if (estatus == ::error_already_exists)
            {

               try
               {

                  file_delete(strDir);

               }
               catch (...)
               {

               }

               string str = stra[i];

               str.trim_right("\\/");

               try
               {

                  file_delete(str);

               }
               catch (...)
               {

               }

               if (::dir::mkdir(stra[i]))
               {

                  continue;

               }
               else
               {

                  estatus = ::get_last_status();

               }

            }

   #ifdef WINDOWS_DESKTOP

            char * pszError;

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *)&pszError, 8, nullptr);

            //information("         auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create CreateDirectoryW last error(%d)=%s", dwError, pszError);

            ::LocalFree(pszError);

            //m_isdirmap.set(stra[i], false);

   #endif

            return false;

         }

      }

      return true;

   }


#endif


   bool mkdir(const ::file::path & path)
   {

      if (is(path))
      {

         return true;

      }

      if (acmefile()->exists(path))
      {

         if (!file_delete(path))
         {

            set_last_status(error_already_exists);

            return false;

         }

      }

   #ifdef WINDOWS

      wstring wstr;

      if (is_absolute_path(path))
      {

         wstr = "\\\\?\\" + path;

      }
      else
      {

         wstr = path;

      }

      if (!::CreateDirectoryW(wstr, nullptr))
      {

         return false;

      }

   #else

      if (::mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
      {

         TranslateLastError();

         return false;

      }

      set_last_status(success);

   #endif

      return true;

   }



   ::file::path module()
   {

   #ifdef WINDOWS

      wstring path(get_buffer, MAX_PATH * 8);

      if(!GetModuleFileNameW(nullptr, path, (::u32) path.size()))
      {

         return "";

      }
      else
      {

         return name(string(path));

      }

   #else

      return "/acme/stage";

   #endif

   }


   bool is(const ::file::path & path)
   {

      //if (::file::system_dir::g_pthis == nullptr)
      //{

         return _is(path);

      //}

      //return ::file::system_dir::g_pthis->is(path, ::get_context_system());

   }



   string name(string path)
   {

      if(path.is_empty())
      {

         return path;

      }

      strsize iFirstColon = path.find(':');

      strsize iFirstSlash = -1;

      strsize iSecondSlash = -1;

      if (iFirstColon > 0)
      {

         iFirstSlash = path.find('/');

         if (iFirstSlash == iFirstColon + 1)
         {

            iSecondSlash = path.find('/', iFirstSlash + 1);

            if (iSecondSlash == iFirstSlash + 1 && path.get_length() == iSecondSlash + 1)
            {

               return "";

            }

         }

      }

      strsize iEnd = -1;

      if(path.last_char() == '/' || path.last_char() == '\\')
      {

         iEnd = -2;

      }

      strsize iPos1 = path.rear_find('/',iEnd);

      strsize iPos2 = path.rear_find('\\',iEnd);

      strsize iPos = maximum(maximum(iPos1, iPos2), 0);

      if (iPos == iSecondSlash)
      {

         path.truncate(iPos + 1);

      }
      else
      {

         path.truncate(iPos);

      }

      return path;

   }


   void rls(::file::path_array & stra, const file::path & psz)
   {
      ::count start = stra.get_count();
      ls(stra, psz);
      ::count end = stra.get_count();
      for(::index i = start; i < end; i++)
      {
         if(is(stra[i]))
         {
            rls(stra, stra[i]);
         }
      }

   }


   void rls_dir(::file::path_array & stra,const ::file::path & psz)
   {

      ::count start = stra.get_count();

      ls_dir(stra, psz);

      ::count end = stra.get_count();

      for(::index i = start; i < end; i++)
      {

         ::file::path path = stra[i];

         rls_dir(stra, path);

      }

   }


   void ls(::file::path_array & stra,const ::file::path & psz)
   {

   #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      DIR * dirp = opendir(psz);

      if(dirp == nullptr)
         return;

      dirent * dp;
      ::file::path path;
      while ((dp = readdir(dirp)) != nullptr)
      {

         if(strcmp(dp->d_name, "..") == 0)
            continue;
         else if(strcmp(dp->d_name, ".") == 0)
            continue;
         path = psz / dp->d_name;
         path.m_iDir = dp->d_type & DT_DIR ? 1 : 0;
         path.m_iSize = -1;
         stra.add(path);

         //information("flood for you: dir::ls ----> " + path);

      }

      closedir(dirp);

   #elif defined(UNIVERSAL_WINDOWS)

      ::winrt::Windows::Storage::StorageFolder ^ folder = nullptr;

      string strPrefix;

      string str = psz;

      try
      {

         if(string(psz).case_insensitive_order("image://") == 0)
         {

            strPrefix = "image://";

            try
            {

               folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }
         else if (string(psz).case_insensitive_order("music://") == 0)
         {

            strPrefix = "music://";

            try
            {

               folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }
         else if (string(psz).case_insensitive_order("video://") == 0)
         {

            strPrefix = "video://";

            try
            {

               folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }
         else if (string(psz).case_insensitive_order("document://") == 0)
         {

            strPrefix = "document://";

            try
            {

               folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }
         else
         {

            if (str.case_insensitive_begins_eat("image://"))
            {

               strPrefix = "image://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }

            if(str.case_insensitive_begins_eat("music://"))
            {

               strPrefix = "music://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }

            if (str.case_insensitive_begins_eat("video://"))
            {

               strPrefix = "video://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }

            if (str.case_insensitive_begins_eat("document://"))
            {

               strPrefix = "document://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }

            if (strPrefix.has_char())
            {

               string_array stra;

               stra.explode("/", str);

               string str;

               while (stra.get_count() > 0)
               {

                  str = stra[0];

                  if (str.has_char())
                  {

                     folder = wait(folder->GetFolderAsync(str));

                     strPrefix += str + "/";

                  }

                  stra.erase_at(0);

               }

            }
            else
            {

               folder = ::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(str).get();

               strPrefix = str + "/";

            }

         }

      }
      catch (...)
      {

         return;

      }

      if (folder == nullptr)
      {

         return;

      }

      string strPath = string(begin(folder->Path));

      auto a = folder->GetItemsAsync().get();

      for(u32 u = 0; u < a->Size; u++)
      {

         string strPath = string(begin(a->GetAt(u)->Path));

         ::file::path path(strPath);

         string str = path;

         path.m_iDir = a->GetAt(u)->IsOfType( ::winrt::Windows::Storage::StorageItemTypes::Folder) ? 1 :0;

         stra.add(path);

      }


   #else

      WIN32_FIND_DATAW FindFileData;

      HANDLE hFind;

      hFind = FindFirstFileW(wstring(psz / "*"), &FindFileData);

      if (hFind == INVALID_HANDLE_VALUE)
         return;

      while(true)
      {

         if(!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES))
            stra.add(::file::path(FindFileData.cFileName));

         //if (stra.has_elements() && stra.last() == "teste")
         //{
         //   information("teste");
         //}

         if(!FindNextFileW(hFind, &FindFileData))
            break;

      }

      FindClose(hFind);

   #endif


   }


   void ls_dir(::file::path_array & stra,const ::file::path & psz)
   {

   #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      DIR * dirp = opendir(psz);

      if(dirp == nullptr)
         return;

      dirent * dp;

      while ((dp = readdir(dirp)) != nullptr)
      {
         if(dp->d_name[0] == '.')
         {
            if(dp->d_name[1] == '\0')
               continue;
            if(dp->d_name[1] == '.')
            {
               if(dp->d_name[2] == '\0')
                  continue;
            }
         }
         ::file::path strPath = psz /  dp->d_name;
         if(is(strPath))
         {
            stra.add(strPath);
         }

      }

      closedir(dirp);

   #elif defined(UNIVERSAL_WINDOWS)

      ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

      ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

      for(u32 u = 0; u < a->Size; u++)
      {
         stra.add(begin(a->GetAt(u)->Path));
      }


   #else

      WIN32_FIND_DATAW FindFileData;

      HANDLE hFind;

      hFind = FindFirstFileW(wstring(psz), &FindFileData);

      if (hFind == INVALID_HANDLE_VALUE)
         return;

      while(true)
      {

         if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
         {

            stra.add(::file::path(FindFileData.cFileName));

         }

         stra.add(::file::path(FindFileData.cFileName));

         if(!FindNextFileW(hFind, &FindFileData))
            break;

      }

      FindClose(hFind);

   #endif


   }


   void ls_file(::file::path_array & stra,const ::file::path & psz)
   {

   #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      DIR * dirp = opendir(psz);

      if(dirp == nullptr)
         return;

      dirent * dp;

      while ((dp = readdir(dirp)) != nullptr)
      {
         if(dp->d_name[0] == '.')
         {
            if(dp->d_name[1] == '\0')
               continue;
            if(dp->d_name[1] == '.')
            {
               if(dp->d_name[2] == '\0')
                  continue;
            }
         }
         ::file::path strPath = psz /  dp->d_name;
         if(!is(strPath))
         {
            stra.add(strPath);
         }

      }

      closedir(dirp);

   #elif defined(UNIVERSAL_WINDOWS)

      ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

      ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

      for(u32 u = 0; u < a->Size; u++)
      {
         stra.add(begin(a->GetAt(u)->Path));
      }


   #else

      WIN32_FIND_DATAW FindFileData;

      HANDLE hFind;

      hFind = FindFirstFileW(wstring(psz), &FindFileData);

      if (hFind == INVALID_HANDLE_VALUE)
         return;

      while(true)
      {

         if(!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
         {
         }
         else
         {
            stra.add(::file::path(FindFileData.cFileName));
         }


         stra.add(::file::path(FindFileData.cFileName));

         if(!FindNextFileW(hFind, &FindFileData))
            break;

      }

      FindClose(hFind);

   #endif


   }


   ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode)
   {

      string_array stra;

      stra.add_tokens(pszEnv, ":");

      string strCandidate;

      for(i32 i = 0; i < stra.get_count(); i++)
      {

         if(stra[i].is_empty())
            continue;

         strCandidate = ::file::path(stra[i]) / pszTopic;

         if(acmefile()->exists(strCandidate))
         {
            return strCandidate;
         }

      }

      return "";

   }



   ::file::path archive()
   {

   #ifdef WINDOWS

       ::file::path pathArchive = getenv("__archive");

       return pathArchive;

   #else

      return "/archive";

   #endif

   }




 
} // namespace dir


extern "C" int make_path(const ::scoped_string & scopedstr)
{

   return          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(psz) != false;

}



