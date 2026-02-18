#include "framework.h"
//#include "acme/xml/_.h"


namespace universal_windows
{


   directory_system::directory_system()
   {

   }

   
   directory_system::~directory_system()
   {

   }


   void directory_system::initialize(::particle * pparticle)
   {

      auto estatus = ::directory_system::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      if (!update_module_path())
      {

         return ::error_failed;

      }

      //string strCa2Module = ca2module();

      //m_strCa2 = strCa2Module;

      //auto pdocument = create_xml_document();

      //pdocument->load(file()->as_string(appdata() / "configuration\\directory.xml"));

      //if (pdocument->get_root()->get_name() == "directory_configuration")
      //{

      //   m_strTimeFolder = pdocument->get_root()->get_child_value("time");

      //   m_strNetSeedFolder = pdocument->get_root()->get_child_value("netseed");

      //}
      //if (m_strTimeFolder.is_empty())
      //{

      //   m_strTimeFolder = appdata() / "time";

      //}

      //if (m_strNetSeedFolder.is_empty())
      //   m_strNetSeedFolder = install() / "net";

      //mk(m_strTimeFolder, get_app());

      //if (!is(m_strTimeFolder, get_app()))
      //   return false;

      //mk(m_strTimeFolder / "time", get_app());

      //m_pathHome = ::directory_system::ca2roaming() / "home";

      //nodeos_set_home(m_pathHome);

      //nodeos_set_temp(m_strTimeFolder / "time");

      return estatus;

   }




   //::file::path directory_system::trash_that_is_not_trash(const ::file::path& psz)
   //{

   //   if (scopedstr == nullptr)
   //      return "";

   //   if (scopedstr[1] == ':')
   //   {

   //      string strDir = psz.folder();

   //      string str;
   //      str = strDir.left(2);
   //      str += "\\trash_that_is_not_trash\\";
   //      string strFormat;
   //      ::earth::time time;
   //      time = ::earth::time::now();
   //      strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
   //      str += strFormat;
   //      if (strDir.m_pszData[2] == '\\')
   //      {
   //         str += strDir.substr(3);
   //      }
   //      else
   //      {
   //         str += strDir.substr(2);
   //      }
   //      return str;
   //   }

   //   return "";
   //}


   //::file::path directory_system::appdata()
   //{

   //   return ::file::path(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

   //}


   //::file::path directory_system::usersystemappdata(::particle * pparticle, const ::scoped_string & scopedstrPrefix)
   //{

   //   __UNREFERENCED_PARAMETER(pparticle);

   //   return appdata() / strPrefix;

   //}


   //::file::path directory_system::userdata(::particle * pparticle)
   //{

   //   return userfolder(pparticle) / "data";

   //}


   //::file::path directory_system::userfolder(::particle * pparticle)
   //{

   //   string str = appdata();

   //   string strUserFolderShift;

   //   if(App(pparticle).has_property("user_folder_relative_path"))
   //   {
   //      strUserFolderShift = App(pparticle).m_varTopicQuery["user_folder_relative_path"].get_string();
   //   }

   //   return str / "ca2" / strUserFolderShift;

   //}


   //::file::path directory_system::default_os_user_path_prefix(::particle * pparticle)
   //{

   //   __UNREFERENCED_PARAMETER(pparticle);

   //   return "CurrentUser";

   //}


   //::file::path directory_system::default_userappdata(::particle * pparticle,const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin)
   //{

   //   return default_userfolder(pparticle,lpcszPrefix,lpcszLogin) / "appdata";

   //}


   //::file::path directory_system::default_userdata(::particle * pparticle,const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin)
   //{

   //   return default_userfolder(pparticle,lpcszPrefix,lpcszLogin) / "data";

   //}


   //::file::path directory_system::default_userfolder(::particle * pparticle,const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin)
   //{

   //   return userfolder(pparticle) / strPrefix / strLogin;

   //}


   //::file::path directory_system::userquicklaunch(::particle * pparticle)
   //{

   //   throw ::exception(todo);

   //}


   //::file::path directory_system::userprograms(::particle * pparticle)
   //{

   //   throw ::exception(todo);

   //}


   //::file::path directory_system::commonprograms()
   //{

   //   throw ::exception(todo);

   //}


   //bool directory_system::is_inside_time(const ::file::path& pszPath)
   //{

   //   return is_inside(time(), pszPath, pparticle);

   //}


   //bool directory_system::is_inside(const ::file::path& pszDir, const ::file::path& strPath)
   //{

   //   return case_insensitive_string_begins(scopedstrDir, strPath);

   //}


   //bool directory_system::has_subdir(::particle * pparticle, const ::file::path& pszDir)
   //{

   //   return ::file::system_dir::has_subdir(pparticle, pszDir);

   //}


   //::file::path directory_system::commonappdata()
   //{

   //   return ::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path / "commonappdata";

   //}

   bool directory_system::update_module_path()
   {
      
      m_pathModule = ::path::module();

      m_pathCa2Module = ::dir::ca2_module();

      return true;

   }


   //::file::path directory_system::document()
   //{

   //   return "document://";

   //}


   //::file::path directory_system::music()
   //{

   //   return "music://";

   //}


   //::file::path directory_system::video()
   //{

   //   return "video://";

   //}


   //::file::path directory_system::image::image_pointer()
   //{

   //   return "image://";

   //}



} // namespace universal_windows




