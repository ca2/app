#include "framework.h"
////#include "apex/xml/_.h"
#include "acme/constant/id.h"


namespace universal_windows
{


   dir_context::dir_context()
   {

   }


   dir_context::~dir_context()
   {

   }


   void dir_context::initialize(::particle * pparticle)
   {

      auto estatus = ::dir_context::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      __refer(m_pdirsystem, ::apexacmesystem()->m_pdirsystem);

      __refer(m_pfilesystem, ::apexacmesystem()->m_pfilesystem);

      return estatus;

   }


   void dir_context::init_system()
   {

      auto estatus = ::dir_context::init_system();

      if (!estatus)
      {

         return estatus;

      }

      //return estatus;

      string strCa2Module = ca2module();

      m_pdirsystem->m_strCa2 = strCa2Module;

      //#if !defined(CUBE) && !defined(ANDROID)
      //
      //      m_strCa2 -= 2;
      //
      //#endif


      //auto pdocument = create_xml_document();

      //pdocument->load(pcontext->m_papexcontext->file()->as_string(appdata() / "configuration\\directory.xml"));

      //if (pdocument->root() && pdocument->root()->get_name() == "directory_configuration")
      //{

      //   m_pdirsystem->m_strTimeFolder = pdocument->root()->get_child_value("time");

      //   m_pdirsystem->m_strNetSeedFolder = pdocument->root()->get_child_value("netseed");

      //}

      if (m_pdirsystem->m_strTimeFolder.is_empty())
      {

         m_pdirsystem->m_strTimeFolder = appdata() / "time";

      }

      if (m_pdirsystem->m_strNetSeedFolder.is_empty())
      {

         m_pdirsystem->m_strNetSeedFolder = install() / "net";

      }

      mk(m_pdirsystem->m_strTimeFolder);

      if (!is(m_pdirsystem->m_strTimeFolder))
      {

         return false;

      }

      mk(m_pdirsystem->m_strTimeFolder / "time");

      m_pdirsystem->m_pathHome =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->ca2roaming() / "home";

      //nodeos_set_home(m_pdirsystem->m_pathHome);

      //nodeos_set_temp(m_pdirsystem->m_strTimeFolder / "time");

      return true;

   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.add("image://");
      listing.last().m_iDir = 1;
      listing.add("music://");
      listing.last().m_iDir = 1;
      listing.add("video://");

      listing.last().m_iDir = 1;

      listing.m_straTitle.add("Picture");
      listing.m_straTitle.add("Music");
      listing.m_straTitle.add("Video");

      return listing;

   }





   ::file::listing & dir_context::ls(::file::listing & listing)
   {

      if(listing.m_bRecursive)
      {


         index iStart = listing.get_size();


         {

            ___scoped_restore(listing.m_pathUser);

            ___scoped_restore(listing.m_pathFinal);

            ___scoped_restore(listing.m_eextract);

            if(::dir_context::ls(listing))
            {

               listing = error_failed;

               return listing;

            }

            ::file::listing dira;

            ls_dir(dira, listing.m_pathFinal);

            for(i32 i = 0; i < dira.get_count(); i++)
            {

               ::file::path dir_context = dira[i];

               if(dir_context == listing.m_pathFinal)
                  continue;

               listing.m_pathFinal = dir_context;

               if(listing.m_eextract != e_extract_all)
               {

                  listing.m_eextract = e_extract_none;

               }

               get_app()->dir()->ls(listing);

            }

         }

         ::file::path_array stra;

         ::dir::ls(stra, listing.m_pathFinal);

         for(int i = 0; i < stra.get_count(); i++)
         {

            ::file::path strPath = stra[i];

            string strName = strPath.name();

            if(!matches_wildcard_criteria(listing.m_straPattern,strName))
               continue;

            bool bDir = is(strPath);

            if((listing.m_bFile && !bDir) || (listing.m_bDir && bDir))
            {

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathUser.get_length() + 1;

         }

      }
      else
      {

         if(::dir_context::ls(listing).succeeded())
         {

            return listing;

         }

         ::file::path_array stra;

         ::dir::ls(stra,listing.m_pathFinal);

         for(int i = 0; i < stra.get_count(); i++)
         {

            ::file::path strPath = stra[i];

            string strName = strPath.name();

            if(!matches_wildcard_criteria(listing.m_straPattern,strName))
               continue;

            bool bDir = strPath.m_iDir < 0 ? is(strPath) : strPath.m_iDir != 0;

            if((listing.m_bFile && !bDir) || (listing.m_bDir && bDir))
            {

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

      }

      return listing;

   }


   bool dir_context::is_impl(const ::file::path & lpcszPath)
   {

      if(lpcszPath.case_insensitive_order("image://") == 0)
         return true;
      if (lpcszPath.case_insensitive_order("music://") == 0)
         return true;
      if (lpcszPath.case_insensitive_order("video://") == 0)
         return true;

      bool bIsDir;

     string strPath(lpcszPath);

      if(strPath.get_length() >= MAX_PATH)
      {
         if(string_begins(strPath,"\\\\"))
         {
            strPath = "\\\\?\\UNC" + strPath.Mid(1);
         }
         else
         {
            strPath = "\\\\?\\" + strPath;
         }
      }

      /*
      u32 dwAttrib;
      dwAttrib = windows_get_file_attributes(utf8_to_unicode(strPath));
      /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
      dwAttrib = GetFileAttributes(lpcszPath);
      }*/

      //bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      bIsDir = ::dir::_is(strPath);

      return bIsDir;

   }


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

      if(task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
      {

         return true;

      }

      strsize iFind = ::str().case_insensitive_find(".zip:",str);

      string strPath(str.c_str(), iLast + 1);

      if(strPath.get_length() >= MAX_PATH)
      {
         if(string_begins(strPath,"\\\\"))
         {
            //::str().begin(strPath,"\\\\?\\UNC");
         }
         else
         {
            //::str().begin(strPath,"\\\\?\\");
         }
      }

      bool bIsDir = ::dir_context::is(strPath);

      return bIsDir;

   }


   ::file::path dir_context::warehouse()
   {
      return dir()->ca2module();
   }

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
      return stage()/ "basis";
   }

   ::file::path dir_context::netseed()
   {
      return m_pdirsystem->m_strNetSeedFolder;
   }

   // stage in ccwarehouse spalib
   ::file::path dir_context::install()
   {

      return m_pdirsystem->m_strCa2;

   }


   ::file::path dir_context::time_square(const ::string & strPrefix, const ::string & strSuffix)
   {

      __UNREFERENCED_PARAMETER(strPrefix);
      __UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }

   ::file::path dir_context::time_square()
   {
      return time() / "time";
   }


   ::file::path dir_context::time_log()
   {
      return appdata() / "log";
   }


   bool dir_context::mk(const ::file::path & path)
   {

      if(is(pcsz))
         return true;

      ::file::path_array stra;

      pcsz.ascendants_path(stra);

      int i = stra.get_upper_bound();

      for (; i >= 0; i--)
      {

         ::file::path pathDir = stra[i];

         if(is(pathDir))
         {

            break;

         }

      }

      if (i < 0)
      {

         return true;

      }

      for(; i < stra.get_size(); i++)
      {

         ::file::path pathDir = stra[i];

         if (!::dir::mkdir(pathDir))
         {

            u32 dwError = ::GetLastError();

            if (dwError == ERROR_ALREADY_EXISTS)
            {

               string str;

               str = "\\\\?\\" + pathDir;

               str.trim_right("\\/");

               try
               {

                  pcontext->m_papexcontext->file()->del(str);

               }
               catch (...)
               {

               }

               str = stra[i];

               str.trim_right("\\/");

               try
               {

                  pcontext->m_papexcontext->file()->del(str);

               }
               catch (...)
               {

               }

               if (::dir::mkdir(stra[i]))
               {

//                  m_isdirmap.set(stra[i], true, 0);

                  goto try1;

               }
               else
               {

                  dwError = ::GetLastError();

               }

               string strError = get_last_error_message(dwError);

               FORMATTED_TRACE("dir_context::mk CreateDirectoryW last error(%d)=%s", dwError, strError);

               //m_isdirmap.set(stra[i], false, 0);

               return false;

            }
            else
            {

               //m_isdirmap.set(stra[i], true, 0);

            }

         }
         else
         {

            //m_isdirmap.set(stra[i],true,0);

         }

try1:;


      }

      return true;

   }


   bool dir_context::rm(const ::file::path & psz,bool bRecursive)
   {

      if(bRecursive)
      {

         ::file::listing straPath;

         ls(straPath, psz);

         for(int i = 0; i < straPath.get_count(); i++)
         {

            if(is(straPath[i]))
            {

               rm(psz / straPath[i].name(),true);

            }
            else
            {

               ::DeleteFileW(utf8_to_unicode(straPath[i]));

            }

         }

      }

      return RemoveDirectoryW(utf8_to_unicode(psz)) != false;

   }





   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
   {

      if(psz == nullptr)
         return "";

      if(psz[1] == ':')
      {

         string strDir = psz.folder();

         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::earth::time time;
         time = ::earth::time::now();
         strFormat.format("%04d-%02d-%02d %02d-%02d-%02d\\",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
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


   ::file::path dir_context::appdata()
   {

      return ::file::path(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path->Begin());

   }


   //::file::path dir_context::usersystemappdata(const ::string & strPrefix)
   //{

   //   __UNREFERENCED_PARAMETER(pparticle);

   //   return appdata() / strPrefix;

   //}


   //::file::path dir_context::userdata()
   //{

   //   return userfolder(pparticle) / "data";

   //}


   //::file::path dir_context::userfolder()
   //{

   //   string str = appdata();

   //   string strUserFolderShift;

   //   if(App(pparticle).has_property("user_folder_relative_path"))
   //   {
   //      strUserFolderShift = App(pparticle).m_varTopicQuery["user_folder_relative_path"].get_string();
   //   }

   //   return str / "ca2" / strUserFolderShift;

   //}


   //::file::path dir_context::default_os_user_path_prefix()
   //{

   //   __UNREFERENCED_PARAMETER(pparticle);

   //   return "CurrentUser";

   //}


   //::file::path dir_context::default_userappdata(const string & lpcszPrefix,const string & lpcszLogin)
   //{

   //   return default_userfolder(pparticle,lpcszPrefix,lpcszLogin) / "appdata";

   //}


   //::file::path dir_context::default_userdata(const string & lpcszPrefix,const string & lpcszLogin)
   //{

   //   return default_userfolder(pparticle,lpcszPrefix,lpcszLogin) / "data";

   //}


   //::file::path dir_context::default_userfolder(const ::string & strPrefix,const ::string & strLogin)
   //{

   //   return userfolder(pparticle) / strPrefix / strLogin;

   //}


   ::file::path dir_context::userquicklaunch()
   {

      throw ::exception(todo);

   }


   ::file::path dir_context::userprograms()
   {

      throw ::exception(todo);

   }


   ::file::path dir_context::commonprograms()
   {

      throw ::exception(todo);

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(),pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pszDir,const ::file::path & strPath)
   {

      return string_begins_ci(pszDir,strPath);

   }


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {

      return ::dir_context::has_subdir(pszDir);

   }


   ::file::path dir_context::commonappdata()
   {

      return ::file::path(string(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path->Begin()))/ "commonappdata";

   }

   //bool dir_context::update_module_path()
   //{

   //   m_pathModule = ::path::module();

   //   m_pathCa2Module = ::dir_context::ca2_module();

   //   return true;

   //}


   ::file::path dir_context::document()
   {

      return "document://";

   }


   ::file::path dir_context::music()
   {

      return "music://";

   }


   ::file::path dir_context::video()
   {

      return "video://";

   }


   ::file::path dir_context::image()
   {

      return "image://";

   }



} // namespace universal_windows















