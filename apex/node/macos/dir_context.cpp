#include "framework.h"
#include "apex/os/_.h"
#include "apex/os/_os.h"
//#include "apex/xml/_.h"
#include "acme/id.h"

#include "_.h"

char * ns_user_local_desktop_folder();
char * ns_user_local_documents_folder();
char * ns_user_local_downloads_folder();
char * ns_user_local_music_folder();
char * ns_user_local_image_folder();
char * ns_user_local_video_folder();


namespace macos
{


   dir_context::dir_context()
   {


   }


   dir_context::~dir_context()
   {
   
   
   }


   ::e_status dir_context::initialize(::object * pobject)
   {
      
      auto estatus = ::dir_context::initialize(pobject);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      estatus = __refer(m_pdirsystem, ::apex::get_system()->m_pdirsystem);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      estatus = __refer(m_pfilesystem, ::apex::get_system()->m_pfilesystem);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;
      
   }


   ::e_status dir_context::init_system()
   {
      
      auto estatus = ::dir_context::init_system();
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      ::file::path pathHome;

      pathHome = ::file::path(getenv("HOME"));

      ::file::path str;

      if(pathHome.is_empty())
      {

         pathHome = "~/Library";

         pathHome /= ".default_user";

         str =  pathHome / "ca2";

      }
      else
      {

         str =  pathHome / "Library" / "ca2";

      }

      string strRelative;

      strRelative = ::dir::install();

      m_pdirsystem->m_strCommonAppData = str / strRelative / "commonappdata";

//      xml::document doc;
//
//      string strPath = ::dir::appdata() / "configuration\\directory.xml";
//
//      string strDocument = pcontext->m_papexcontext->file().as_string(strPath);
//
//      if(doc.load(strDocument))
//      {
//
//         if(doc.root()->get_name() == "directory_configuration")
//         {
//
//            m_pdirsystem->m_strTimeFolder = doc.root()->get_child_value("time");
//
//            m_pdirsystem->m_strNetSeedFolder = doc.root()->get_child_value("netseed");
//
//         }
//
//      }

      if(m_pdirsystem->m_strTimeFolder.is_empty())
      {
         
         m_pdirsystem->m_strTimeFolder = ::file::path(getenv("HOME")) /"Library" / "ca2"/"time";
         
      }

      if(m_pdirsystem->m_strNetSeedFolder.is_empty())
      {
         
         m_pdirsystem->m_strNetSeedFolder = ::dir::install() / "net";
         
      }

      ::dir::mk(m_pdirsystem->m_strTimeFolder);

      if(!::dir::is(m_pdirsystem->m_strTimeFolder))
      {
         
         return false;
         
      }

      ::file::path strTime;

      strTime = m_pdirsystem->m_strTimeFolder;

      strTime /= "time";

      ::dir::mk(strTime);

      if(!::dir::is(strTime))
      {
         
         return false;
         
      }

      str = "/usr/bin";

      m_pdirsystem->m_strPrograms = str;

      str = "/usr/share/";

      m_pdirsystem->m_strCommonPrograms = str;
      
      return estatus;

   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("File ::apex::get_system()");

      return listing;

   }


   ::file::listing & dir_context::ls(::file::listing & listing)
   {

      if(listing.m_bRecursive)
      {

         index iStart = listing.get_size();

         {

            __restore(listing.m_pathUser);

            __restore(listing.m_pathFinal);

            __restore(listing.m_eextract);

            if(::dir_context::ls(listing))
            {

               listing = ::error_failed;

               return listing;

            }

            ::file::listing dira;

            get_application()->dir().ls_dir(dira, listing.m_pathFinal);

            for(i32 i = 0; i < dira.get_count(); i++)
            {

               ::file::path dir_context = dira[i];

               if(dir_context == listing.m_pathFinal)
                  continue;

               listing.m_pathUser.Empty();
               listing.m_pathFinal = dir_context;

               if(listing.m_eextract != extract_all)
               {

                  listing.m_eextract = extract_none;

               }

               get_application()->dir().ls(listing);

            }

         }

         ::file::patha  straPath;

         ::dir::ls(straPath, listing.m_pathFinal);

//            file_find file_find;

         //          bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;

         for(auto & strPath : straPath)
         {

            bool bDir = is(strPath);

            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
            {

               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
                  continue;

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {

         if(::dir_context::ls(listing).succeeded())
         {

            return listing;

         }

         ::file::patha  straPath;

         ::dir::ls(straPath, listing.m_pathFinal);

         // file_find file_find;

         // bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != false;

         for(auto & strPath : straPath)
         {

            bool bDir = is(strPath);

            if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
            {

               if(!bDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
                  continue;

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

      }

      return listing;

   }


   bool dir_context::is(const ::file::path & pathParam)
   {

      ::file::path path;

      path = get_context()->defer_process_path(pathParam);

      if(::dir_context::is(path))
      {

         return true;

      }

      return ::dir::_is(path);

   }


//   bool dir_context::is(const string & strPath)
//   {
//
//      if(::file::system_dir::is(strPath, papp))
//         return true;
//
//      bool bIsDir;
//
//      ::u32 dwLastError;
//
//      if(m_isdirmap.lookup(strPath, bIsDir, dwLastError))
//      {
//
//         if(!bIsDir)
//         {
//
//            set_last_error(dwLastError);
//
//         }
//
//         return bIsDir;
//
//      }
//
//
//      wstring wstrPath;
//
//      //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
//      //wstrPath.alloc(iLen + 32);
//      wstrPath = ::str::international::utf8_to_unicode(strPath);
//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, L"\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }
//
//      bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));
//
//      m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());
//
//      return bIsDir;
//   }


   bool dir_context::name_is(const ::file::path & str)
   {
      //output_debug_string(str);
      strsize iLast = str.get_length() - 1;
      while(iLast >= 0)
      {
         if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            break;
         iLast--;
      }
      while(iLast >= 0)
      {
         if(str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
            break;
         iLast--;
      }
      if(iLast >= 0)
      {
         while(iLast >= 0)
         {
            if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            {
               iLast++;
               break;
            }
            iLast--;
         }
      }
      else
      {
         return true; // assume empty string is root_ones directory
      }


      bool bIsDir;

      ::u32 dwLastError;

      if(::thread_is_set(id_thread_zip_is_dir) && iLast >= 3  && !ansi_count_compare_ci(&((const char *) str)[iLast - 3], ".zip", 4))
      {
         //m_isdirmap.set(str.Left(iLast + 1), true, 0);
         return true;
      }

      wstring wstrPath;

      //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);

      //wstrPath.alloc(iLen + 32);

      wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);

      //output_debug_string(wstrPath);

//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, unitext("\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }

      bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));

      //m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? //0 : ::get_last_error());

      return bIsDir;
   }


   bool dir_context::mk(const ::file::path & pcsz)
   {

      if(is(pcsz))
      {

         return true;

      }

      ::file::patha stra;

      pcsz.ascendants_path(stra);

      for(i32 i = 0; i < stra.get_size(); i++)
      {

         if(!is(stra[i]))
         {

            if(!::dir::mkdir(stra[i]))
            {

               ::u32 dwError = ::get_last_error();

               if(dwError == ERROR_ALREADY_EXISTS)
               {

                  string str;
                  str = stra[i];
                  str.trim_right("\\/");
                  try
                  {

                     pcontext->m_papexcontext->file().del(str);

                  }
                  catch(...)
                  {

                  }

                  str = stra[i];

                  str.trim_right("\\/");

                  try
                  {

                     pcontext->m_papexcontext->file().del(str);

                  }
                  catch(...)
                  {

                  }

                  //if(::CreateDirectory(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), nullptr))

                  if(::dir::mkdir(stra[i]))
                  {

                     //m_isdirmap.set(stra[i], true, 0);

                     goto try1;

                  }
                  else
                  {

                     dwError = ::get_last_error();

                  }

               }

//               char * pszError;
////               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *) &pszError, 8, nullptr);
//                              FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *) &pszError, 8, nullptr);
//
//               //TRACE("dir_context::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
//               // xxx               ::LocalFree(pszError);
//               //m_isdirmap.set(stra[i], false);
            }
            else
            {
               //m_isdirmap.set(stra[i], true, 0);
            }
try1:

            if(!is(stra[i]))
            {

               return false;

            }

         }

      }

      return true;

   }


//   bool dir_context::rm(::object * const ::file::path & psz, bool bRecursive)
//   {
//      if(bRecursive)
//      {
//         string_array straPath;
//         string_array straTitle;
//         ls(papp, psz, &straPath, &straTitle);
//         for(i32 i = 0; i < straPath.get_count(); i++)
//         {
//            if(is(straPath[i], papp))
//            {
//               rm(papp, path(psz, straTitle[i]), true);
//            }
//            else
//            {
//               ::unlink(straPath[i]);
//            }
//         }
//      }
//      return ::rmdir(psz) != false;
//   }
//
//
//   string dir_context::name(const char * path1)
//   {
//      const char * psz = path1 + strlen(path1) - 1;
//      while(psz >= path1)
//      {
//         if(*psz != '\\' && *psz != '/' && *psz != ':')
//            break;
//         psz--;
//      }
//      while(psz >= path1)
//      {
//         if(*psz == '\\' || *psz == '/' || *psz == ':')
//            break;
//         psz--;
//      }
//      if(psz >= path1) // strChar == "\\" || strChar == "/"
//      {
//         const char * pszEnd = psz;
//         /*while(psz >= path1)
//          {
//          if(*psz != '\\' && *psz != '/' && *psz != ':')
//          break;
//          psz--;
//          }*/
//         return string(path1, pszEnd - path1 + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//   string dir_context::name(const string & str)
//   {
//
//      strsize iLast = str.get_length() - 1;
//
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//            break;
//         iLast--;
//      }
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//            break;
//         iLast--;
//      }
//      if(iLast >= 0)
//      {
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               break;
//            iLast--;
//         }
//         return str.Left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//
//   class ::file::path & dir_context::path()
//   {
//      return m_path;
//   }



   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
   {
      if(psz == nullptr)
         return "";

      if(psz[1] == ':')
      {
         string strDir = name(psz);
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::datetime::time time;
         time = ::datetime::time::get_current_time();
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if(strDir[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";
   }




//   string dir_context::usersystemappdata(::object * const char * lpcszPrefix, const char * pcsz, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      return path(appdata(lpcszPrefix), pcsz, lpcsz2);
//   }
//
//   string dir_context::appdata(::object * const char * pcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "appdata"), pcsz, lpcsz2);
//   }
//
//   string dir_context::userdata(::object * const char * pcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "data"), pcsz, lpcsz2);
//   }

//   ::file::path dir_context::userfolder(::object * pobject)
//   {
//
//      return App(papp).dir_context().userfolder();
//
//   }


//   ::file::path dir_context::default_os_user_path_prefix(::object * pobject)
//   {
//
//      return ::getlogin();
//
//   }


//   string dir_context::default_userappdata(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
//   }
//
//   string dir_context::default_userdata(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "data"), pszRelativePath);
//   }
//
//   string dir_context::default_userfolder(::object * const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//
//      return userfolder(papp, pszRelativePath);
//
//      /*      UNREFERENCED_PARAMETER(pobject);
//       string str;
//       SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_APPDATA,
//       false);
//       return path(path(str, "ca2\\user", lpcszPrefix), lpcszLogin, pszRelativePath);*/
//   }
//
//   string dir_context::userquicklaunch(::object * const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      string str;
//      /*SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_APPDATA,
//       false);*/
//      str = path(getenv("HOME"), "Microsoft\\Internet Explorer\\Quick Launch");
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   string dir_context::userprograms(::object * const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(pobject);
//      string str;
//      /*      SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_PROGRAMS,
//       false);*/
//
//      str = "/usr/bin";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }
//
//   string dir_context::commonprograms(const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      string str;
//      /*      SHGetSpecialFolderPath(
//       nullptr,
//       str,
//       CSIDL_COMMON_PROGRAMS,
//       false);*/
//      str = "/usr/share/";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   bool dir_context::is_inside_time(const char * pszPath)
//   {
//      return is_inside(time(), pszPath, papp);
//   }
//
//   bool dir_context::is_inside(const char * pszDir, const char * pszPath)
//   {
//      return ::str::begins_ci(pszDir, pszPath);
//   }
//


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {

      ::file::listing stra;

      get_application()->dir().ls_dir(stra, pszDir);

      return stra.has_elements();

   }





//    bool dir_context::is(const ::file::path & lpcszPath)
//    {
//
//        if(::file::system_dir::is(lpcszPath, papp))
//            return true;
//
//        string strPath(lpcszPath);
//
//        if(strPath.get_length() >= MAX_PATH)
//        {
//
//            if(::str::begins(strPath,astr.DoubleBackSlash))
//            {
//
//                strPath = "\\\\?\\UNC" + strPath.Mid(1);
//
//            }
//            else
//            {
//
//                strPath = "\\\\?\\" + strPath;
//
//            }
//
//        }
//
//        ::u32 dwAttrib;
//
//        dwAttrib = windows_get_file_attributes(::str::international::utf8_to_unicode(strPath));
//
//        bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//
//        m_isdirmap.set(lpcszPath, bIsDir, bIsDir ? 0 : ::get_last_error());
//
//        return bIsDir;
//
//    }


   //bool dir_context::is(const ::file::path & strPath)
   //{
   //
   //   if(::file::system_dir::is(strPath, papp))
   //      return true;

   //   bool bIsDir;

   //   u32 uiLastError;

   //   if(m_isdirmap.lookup(strPath, bIsDir, uiLastError))
   //   {
   //      if(!bIsDir)
   //      {
   //         ::set_last_error(uiLastError);
   //      }
   //      return bIsDir;
   //   }

   //   wstring wstrPath;
   //
   //   //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
   //   //wstrPath.alloc(iLen + 32);
   //   wstrPath = ::str::international::utf8_to_unicode(strPath);
   //   if(wstrPath.get_length() >= MAX_PATH)
   //   {
   //      if(::str::begins(wstrPath, L"\\\\"))
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\UNC");
   //      }
   //      else
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\");
   //      }
   //   }
   //   ::u32 dwAttrib;
   //   dwAttrib = windows_get_file_attributes(wstrPath);
   //   /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
   //   {
   //      dwAttrib = GetFileAttributes(strPath);
   //   }*/
   //
   //   bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
   //
   //   m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());

   //   return bIsDir;
   //}

//    bool dir_context::name_is(const ::file::path & str)
//    {
//        //output_debug_string(str);
//        strsize iLast = str.get_length() - 1;
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                break;
//            iLast--;
//        }
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//                break;
//            iLast--;
//        }
//        if(iLast >= 0)
//        {
//            while(iLast >= 0)
//            {
//                if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                {
//                    iLast++;
//                    break;
//                }
//                iLast--;
//            }
//        }
//        else
//        {
//            return true; // assume empty string is root_ones directory
//        }
//
//
//        bool bIsDir;
//
//
//        u32 uiLastError;
//
//        if(m_isdirmap.lookup(str, bIsDir, uiLastError, (i32) iLast))
//        {
//            if(!bIsDir)
//            {
//                ::set_last_error(uiLastError);
//            }
//            return bIsDir;
//        }
//
//
//        if(::get_task() != nullptr && ::get_task()->m_bZipIsDir && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
//        {
//            m_isdirmap.set(str.Left(iLast + 1), true, 0);
//            return true;
//        }
//
//
//
//
//        wstring wstrPath;
//
//        //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);
//
//        //wstrPath.alloc(iLen + 32);
//
//        wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);
//
//        //output_debug_string(wstrPath);
//
//        if(wstrPath.get_length() >= MAX_PATH)
//        {
//            if(::str::begins(wstrPath, L"\\\\"))
//            {
//                ::str::begin(wstrPath, L"\\\\?\\UNC");
//            }
//            else
//            {
//                ::str::begin(wstrPath, L"\\\\?\\");
//            }
//        }
//        ::u32 dwAttrib;
//        dwAttrib = windows_get_file_attributes(wstrPath);
//        /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
//         {
//         dwAttrib = GetFileAttributes(strPath);
//         }*/
//
//        bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//
//        m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::get_last_error());
//
//        return bIsDir;
//    }


   ::file::path dir_context::time()
   {
      return m_pdirsystem->m_strTimeFolder;
   }

   ::file::path dir_context::stage()
   {
      return install() / "stage";
   }

   ::file::path dir_context::stageapp()
   {
      return stage() / "basis";
   }

   ::file::path dir_context::netseed()
   {
      return m_pdirsystem->m_strNetSeedFolder;
   }

   // stage in ca2os spalib
   ::file::path dir_context::install()
   {

      single_lock synchronouslock(mutex(), true);

      return m_pdirsystem->m_pathCa2;

   }


   ::file::path dir_context::module()
   {

      return m_pdirsystem->m_pathModule;

   }


   ::file::path dir_context::ca2module()
   {

      return m_pdirsystem->m_pathCa2Module;

   }


   ::file::path dir_context::time_square(const string & strPrefix,const string & strSuffix)
   {

      UNREFERENCED_PARAMETER(strPrefix);
      UNREFERENCED_PARAMETER(strSuffix);
      
      return time() / "time";

   }


   ::file::path dir_context::time_log()
   {

      return appdata() / "log";

   }


   bool dir_context::rm(const ::file::path & psz, bool bRecursive)
   {

      if(bRecursive)
      {

         ::file::listing patha;

         get_application()->dir().ls(patha, psz);

         for(auto & path : patha)
         {

            if(is(path))
            {

               rm(psz / path.name(), true);

            }
            else
            {

               ::unlink(path);

            }

         }

      }

      return ::rmdir(psz) == 0;

   }


   //::file::path dir_context::name(const ::file::path & path1)
   //{
   //   const char * psz = path1 + strlen(path1) - 1;
   //   while(psz >= path1)
   //   {
   //      if(*psz != '\\' && *psz != '/' && *psz != ':')
   //         break;
   //      psz--;
   //   }
   //   while(psz >= path1)
   //   {
   //      if(*psz == '\\' || *psz == '/' || *psz == ':')
   //         break;
   //      psz--;
   //   }
   //   if(psz >= path1) // strChar == "\\" || strChar == "/"
   //   {
   //      const char * pszEnd = psz;
   //      /*while(psz >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }*/
   //      return string(path1, pszEnd - path1 + 1);
   //   }
   //   else
   //   {
   //      return "";
   //   }
   //}

   ::file::path dir_context::name(const ::file::path & str)
   {

      strsize iLast = str.get_length() - 1;

      while(iLast >= 0)
      {
         if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            break;
         iLast--;
      }
      while(iLast >= 0)
      {
         if(str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
            break;
         iLast--;
      }
      if(iLast >= 0)
      {
         while(iLast >= 0)
         {
            if(str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
               break;
            iLast--;
         }
         return str.Left(iLast + 1);
      }
      else
      {
         return "";
      }
   }


   //class ::file::file_path & dir_context::path()
   //{
   //   return m_path;
   //}

   /*!
    * Print a known folder.
    */
//    ::file::path get_known_folder(REFKNOWNFOLDERID kfid)
//    {
//        ::file::path str;
//        PWSTR pszPath = nullptr;
//        HANDLE hToken = nullptr;
//        ::OpenProcessToken(::GetCurrentProcess(),TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE,&hToken);
//        HRESULT hr = SHGetKnownFolderPath(kfid,0,hToken,&pszPath);
//        if(SUCCEEDED(hr))
//        {
//            str = pszPath;
//            // The calling application is responsible for calling CoTaskMemFree
//            // to free this resource after use.
//            CoTaskMemFree(pszPath);
//        }
//        else
//        {
//        }
//        return str;
//    }




//    ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
//    {
//        if(psz.is_empty())
//            return "";
//
//        if(psz[1] == ':')
//        {
//            string strDir = name(psz);
//            string str;
//            str = strDir.Left(2);
//            str += "\\trash_that_is_not_trash\\";
//            string strFormat;
//            ::datetime::time time;
//            time = ::datetime::time::get_current_time();
//            strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//            str += strFormat;
//            if(strDir.m_pszData[2] == '\\')
//            {
//                str += strDir.Mid(3);
//            }
//            else
//            {
//                str += strDir.Mid(2);
//            }
//            return str;
//        }
//
//        return "";
//    }

   ::file::path dir_context::appdata()
   {
      
      return ::dir::appdata();

   }


   ::file::path dir_context::commonappdata_root()
   {

      return m_pdirsystem->m_strCommonAppData;

   }
   ::file::path dir_context::commonappdata()
   {

      return m_pdirsystem->m_strCommonAppData;

   }


//    ::file::path dir_context::usersystemappdata(::object * pobject,const char * lpcszPrefix)
//    {
//        UNREFERENCED_PARAMETER(pobject);
//        return appdata() / lpcszPrefix;
//    }
//
//    ::file::path dir_context::appdata(::object * pobject)
//    {
//        return userfolder(pobject) / "appdata";
//    }
//
//    ::file::path dir_context::userdata(::object * pobject)
//    {
//        return userfolder(pobject) / "data";
//    }

//    ::file::path dir_context::userfolder(::object * pobject)
//    {
//
//
//
//    }
//
//    ::file::path dir_context::default_os_user_path_prefix(::object * pobject)
//    {
//        UNREFERENCED_PARAMETER(pobject);
//        unichar buf[MAX_PATH];
//        ULONG ulSize = sizeof(buf) / sizeof(unichar);
//        if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
//        {
//            if(!::GetUserNameW(buf, &ulSize))
//            {
//                __memset(buf, 0, sizeof(buf));
//            }
//        }
//        return ::str::international::unicode_to_utf8(buf);
//    }

//    ::file::path dir_context::default_userappdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//        return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata" ;
//    }
//
//    ::file::path dir_context::default_userdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//        return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
//    }
//
//    ::file::path dir_context::default_userfolder(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin)
//    {
//
//        return userfolder(pobject);
//
//    }

   ::file::path dir_context::userquicklaunch()
   {

      return m_pdirsystem->m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path dir_context::userprograms()
   {

      return m_pdirsystem->m_strPrograms;

   }


   ::file::path dir_context::commonprograms()
   {

      return m_pdirsystem->m_strCommonPrograms;

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return ::str::begins_ci(pszDir, pszPath);

   }


//    bool dir_context::has_subdir(::object * const ::file::path & pszDir)
//    {
//
//        file_find file_find;
//
//        bool bWorking;
//
//        bWorking = file_find.FindFile(pszDir / "*.*");
//
//        while(bWorking)
//        {
//
//            bWorking = file_find.FindNextFileA();
//
//            if(file_find.IsDirectory() && !file_find.IsDots())
//            {
//
//                return true;
//
//            }
//
//        }
//
//        return false;
//
//    }

   //bool file::GetStatus(const char * lpszFileName,::file::file_status& rStatus)
   //{
   //   // attempt to fully qualify path first
   //   wstring wstrFullName;
   //   wstring wstrFileName;
   //   wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
   //   if(!vfxFullPath(wstrFullName,wstrFileName))
   //   {
   //      rStatus.m_strFullName.Empty();
   //      return false;
   //   }
   //   ::str::international::unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

   //   WIN32_FIND_DATA findFileData;
   //   HANDLE hFind = FindFirstFile((char *)lpszFileName,&findFileData);
   //   if(hFind == INVALID_HANDLE_VALUE)
   //      return false;
   //   VERIFY(FindClose(hFind));

   //   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //   rStatus.m_attribute = (byte)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //   // get just the low ::u32 of the file size_i32
   //   ASSERT(findFileData.nFileSizeHigh == 0);
   //   rStatus.m_size = (::i32)findFileData.nFileSizeLow;

   //   // convert times as appropriate
   //   rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
   //   rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
   //   rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);

   //   if(rStatus.m_ctime.get_time() == 0)
   //      rStatus.m_ctime = rStatus.m_mtime;

   //   if(rStatus.m_atime.get_time() == 0)
   //      rStatus.m_atime = rStatus.m_mtime;

   //   return true;
   //}


   ::file::path dir_context::home()
   {

      return ::dir_context::home();

   }


   ::file::path dir_context::desktop()
   {

      return ::str::from_strdup(ns_user_local_desktop_folder());


   }


   ::file::path dir_context::document()
   {

      return ::str::from_strdup(ns_user_local_documents_folder());


   }

   ::file::path dir_context::download()
   {

      return ::str::from_strdup(ns_user_local_downloads_folder());

   }


   ::file::path dir_context::music()
   {

      return ::str::from_strdup(ns_user_local_music_folder());

   }


   ::file::path dir_context::video()
   {

      return ::str::from_strdup(ns_user_local_video_folder());

   }


   ::file::path dir_context::image()
   {

      return ::str::from_strdup(ns_user_local_image_folder());

   }


} // namespace macos



