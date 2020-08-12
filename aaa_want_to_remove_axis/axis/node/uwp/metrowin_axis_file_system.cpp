#include "framework.h"
#include "metrowin.h"


namespace metrowin
{


   namespace axis
   {


      file_system::file_system(::object * pobject):
         ::object(pobject),
         ::file::system(pobject),
         ::metrowin::file_system(pobject),
         ::file::axis::system(pobject)
      {

      }


      file_system::~file_system()
      {

      }

      //bool file_system::FullPath(string &str,const char * pszFileIn)

      //{
      //   /*      if(::file::system::FullPath(str, pszFileIn))

      //   return true;*/
      //   if(::str::begins_ci(pszFileIn,"http://"))

      //   {
      //      str = pszFileIn;

      //      return true;
      //   }
      //   else if(::str::begins_ci(pszFileIn,"https://"))

      //   {
      //      str = pszFileIn;

      //      return true;
      //   }
      //   wstring wstrFileIn;
      //   wstrFileIn = ::str::international::utf8_to_unicode(pszFileIn);

      //   wstring wstrFileOut;
      //   //      bool b = vfxFullPath(wstrFileOut.alloc(MAX_PATH * 8), wstrFileIn) != FALSE;
      //   /*      if(b)
      //   {
      //   ::str::international::unicode_to_utf8(str, wstrFileOut);
      //   }
      //   return b;*/

      //   return false;
      //}

      //bool file_system::FullPath(wstring & wstrFullPath,const wstring & wstrPath)
      //{

      //   //if(::file::system::FullPath(wstrFullPath, wstrPath))
      //   // return true;

      //   if(::str::begins_ci(wstrPath,L"http://"))
      //   {
      //      wstrFullPath = wstrPath;
      //      return true;
      //   }
      //   else if(::str::begins_ci(wstrPath,L"https://"))
      //   {
      //      wstrFullPath = wstrPath;
      //      return true;
      //   }

      //   //return vfxFullPath(wstrFullPath, wstrPath) != FALSE;
      //   return false;

      //}


      //UINT file_system::GetFileName(const char * pszPathName,string & str)

      //{
      //   int nMax = MAX_PATH * 8;
      //   wstring wstrPathName;
      //   wstrPathName = ::str::international::utf8_to_unicode(pszPathName);

      //   wstring wstrTitle;
      //   //UINT user = vfxGetFileName(wstrPathName, wstrTitle.alloc(nMax), nMax);
      //   str = ::str::international::unicode_to_utf8(wstrTitle);
      //   //return user;
      //   return 0;
      //}

      //void file_system::GetModuleShortFileName(HINSTANCE hInst,string & strShortName)
      //{
      //   //vfxGetModuleShortFileName(hInst, strShortName);
      //}


      var file_system::length(const ::file::path & path, ::aura::application * papp)
      {

         return ::file::axis::system::length(path, papp);

      }


      //{

      //   var varRet;

      //   WIN32_FILE_ATTRIBUTE_DATA data;

      //   if(!GetFileAttributesExW(::str::international::utf8_to_unicode(pszPath),GetFileExInfoStandard,&data))
      //   {
      //      varRet.set_type(::type_null);
      //   }
      //   else
      //   {
      //      varRet = (u32)data.nFileSizeLow;
      //   }


      //   return varRet;

      //}


      file_result file_system::get_file(::object * pobject, var varFile, UINT nOpenFlags)
      {

         auto pfile = ::file::axis::system::get_file(papp, varFile,nOpenFlags, eflag);

         if(pfile.is_set())
         {

            return pfile;

         }


         pfile = ::metrowin::file_system::get_file(papp, varFile, nOpenFlags, eflag);

         return pfile;

      }


   } //    namespace axis


} // namespace metrowin







