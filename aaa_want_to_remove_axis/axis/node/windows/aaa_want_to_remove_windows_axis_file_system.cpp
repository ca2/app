#include "framework.h"
//#include "windows_file_system.h"

//
//namespace windows
//{
//
//
//   namespace axis
//   {
//
//
//      file_system::file_system(::object * pobject):
//         ::object(pobject),
//         ::file::system(pobject),
//         ::windows::file_system(pobject),
//         ::file::axis::system(pobject)
//      {
//
//      }
//
//
//      file_system::~file_system()
//      {
//
//      }
//
//
//      bool file_system::FullPath(string &str,const char * pszFileIn)
//
//      {
//
//         //if(::aura::file_system::FullPath(str, pszFileIn))
//
//         // return true;
//
//         if(::str::begins_ci(pszFileIn,"http://"))
//
//         {
//
//            str = pszFileIn;
//
//
//            return true;
//
//         }
//         else if(::str::begins_ci(pszFileIn,"https://"))
//
//         {
//
//            str = pszFileIn;
//
//
//            return true;
//
//         }
//         wstring wstrFileIn;
//         wstrFileIn = ::str::international::utf8_to_unicode(pszFileIn);
//
//         wstring wstrFileOut;
//         bool b = vfxFullPath(wstrFileOut.get_string_buffer(MAX_PATH * 8),wstrFileIn) != FALSE;
//         wstrFileOut.release_string_buffer();
//         if(b)
//         {
//            ::str::international::unicode_to_utf8(str,wstrFileOut);
//         }
//         return b;
//      }
//
//      bool file_system::FullPath(wstring & wstrFullPath,const wstring & wstrPath)
//      {
//
//         /*      if(::aura::file_system::FullPath(wstrFullPath, wstrPath))
//         return true;*/
//
//         if(::str::begins_ci(wstrPath,L"http://"))
//         {
//            wstrFullPath = wstrPath;
//            return true;
//         }
//         else if(::str::begins_ci(wstrPath,L"https://"))
//         {
//            wstrFullPath = wstrPath;
//            return true;
//         }
//
//         return vfxFullPath(wstrFullPath,wstrPath) != FALSE;
//
//      }
//
//
//      UINT file_system::GetFileName(const char * pszPathName,string & str)
//
//      {
//         i32 nMax = MAX_PATH * 8;
//         wstring wstrPathName;
//         wstrPathName = ::str::international::utf8_to_unicode(pszPathName);
//
//         wstring wstrTitle;
//         UINT user = vfxGetFileName(wstrPathName,wstrTitle.alloc(nMax),nMax);
//         str = ::str::international::unicode_to_utf8(wstrTitle);
//         return user;
//      }
//
//      void file_system::GetModuleShortFileName(HINSTANCE hInst,string & strShortName)
//      {
//         vfxGetModuleShortFileName(hInst,strShortName);
//      }
//
//      var file_system::length(const string & strPath,::aura::application * papp)
//      {
//
//         var varRet;
//
//         varRet = ::file::system::length(strPath,papp);
//
//         if(!varRet.is_null())
//            return varRet;
//
//
//#ifdef WINDOWS
//
//         WIN32_FILE_ATTRIBUTE_DATA data;
//
//         if(!GetFileAttributesExW(::str::international::utf8_to_unicode(strPath),GetFileExInfoStandard,&data))
//         {
//            varRet.set_type(::type_null);
//         }
//         else
//         {
//            varRet = (u32) data.nFileSizeLow;
//         }
//
//#else
//
//         struct stat stat;
//
//         if(::stat(strPath, &stat)  == -1)
//         {
//            varRet.set_type(::type_null);
//         }
//         else
//         {
//            varRet = stat.st_size;
//         }
//
//#endif
//
//         return varRet;
//
//      }
//
//
//      file_result file_system::get_file(::object * pobject, const var & varFile, UINT nOpenFlags)
//      {
//
//         auto pfile = ::file::axis::system::get_file(pobject, varFile, nOpenFlags);
//
//         if(pfile)
//         {
//
//            return pfile;
//
//         }
//
//         pfile = ::windows::file_system::get_file(pobject, varFile, nOpenFlags);
//
//         if(pfile)
//         {
//
//            return pfile;
//
//         }
//
//         return pfile;
//
//      }
//
//
//   } // namespace axis
//
//
//} // namespace windows
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
