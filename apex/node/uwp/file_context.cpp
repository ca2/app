#include "framework.h"
#include "_.h"
#include "_uwp.h"



namespace universal_windows
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }

   bool file_context::FullPath(string& str, const char* pszFileIn)

   {
      /*      if(::file::system::FullPath(str, pszFileIn))

      return true;*/
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
      //      bool b = vfxFullPath(wstrFileOut.alloc(MAX_PATH * 8), wstrFileIn) != false;
      /*      if(b)
      {
      ::str::international::unicode_to_utf8(str, wstrFileOut);
      }
      return b;*/

      return false;
   }

   bool file_context::FullPath(wstring& wstrFullPath, const wstring& wstrPath)
   {

      //if(::file::system::FullPath(wstrFullPath, wstrPath))
      // return true;

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

      //return vfxFullPath(wstrFullPath, wstrPath) != false;
      return false;

   }


   ::u32 file_context::GetFileName(const char* pszPathName, string& str)

   {
      int nMax = MAX_PATH * 8;
      wstring wstrPathName;
      wstrPathName = ::str::international::utf8_to_unicode(pszPathName);

      wstring wstrTitle;
      //::u32 user = vfxGetFileName(wstrPathName, wstrTitle.alloc(nMax), nMax);
      str = ::str::international::unicode_to_utf8(wstrTitle);
      //return user;
      return 0;
   }

   void file_context::GetModuleShortFileName(HINSTANCE hInst, string& strShortName)
   {
      //vfxGetModuleShortFileName(hInst, strShortName);
   }


   ::payload file_context::length(const ::file::path& path)
   {

      ::payload varRet;

      WIN32_FILE_ATTRIBUTE_DATA data;

      if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
      {

         varRet.set_type(::e_type_null);

      }
      else
      {

         varRet = (u32)data.nFileSizeLow;

      }

      return varRet;

   }


   file_transport file_context::get_file(const ::payload& payloadFile, const ::file::e_open & eopen)
   {

      file_pointer spfile;

      ::file::path path = payloadFile.get_file_path();

      string strPrefix;

      auto folder = winrt_folder1(path, strPrefix);

      if (folder != nullptr)
      {

         auto pbuffer = __new(::universal_windows::native_buffer);

         //::extended::status ::extended::status = spfile->open(folder, strPath,nOpenFlags);

         auto result = pbuffer->open(folder, path, eopen);

         spfile = pbuffer;

         if (result.succeeded())
         {

            return spfile;

         }

      }

      spfile = ::file_context::get_file(payloadFile, eopen);

      return spfile;

   }


} // namespace universal_windows




