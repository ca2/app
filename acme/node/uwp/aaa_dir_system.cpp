#include "framework.h"
#include "acme/xml/_.h"


namespace universal_windows
{


   dir_system::dir_system()
   {

   }

   
   dir_system::~dir_system()
   {

   }


   ::e_status dir_system::initialize(::matter * pobject)
   {

      auto estatus = ::dir_system::initialize(pobject);

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

      //pdocument->load(pcontext->m_papexcontext->file().as_string(appdata() / "configuration\\directory.xml"));

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

      //mk(m_strTimeFolder, get_application());

      //if (!is(m_strTimeFolder, get_application()))
      //   return false;

      //mk(m_strTimeFolder / "time", get_application());

      //m_pathHome = ::dir_system::ca2roaming() / "home";

      //nodeos_set_home(m_pathHome);

      //nodeos_set_temp(m_strTimeFolder / "time");

      return estatus;

   }




   //::file::path dir_system::trash_that_is_not_trash(const ::file::path& psz)
   //{

   //   if (psz == nullptr)
   //      return "";

   //   if (psz[1] == ':')
   //   {

   //      string strDir = psz.folder();

   //      string str;
   //      str = strDir.Left(2);
   //      str += "\\trash_that_is_not_trash\\";
   //      string strFormat;
   //      ::datetime::time time;
   //      time = ::datetime::time::get_current_time();
   //      strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
   //      str += strFormat;
   //      if (strDir.m_pszData[2] == '\\')
   //      {
   //         str += strDir.Mid(3);
   //      }
   //      else
   //      {
   //         str += strDir.Mid(2);
   //      }
   //      return str;
   //   }

   //   return "";
   //}


   //::file::path dir_system::appdata()
   //{

   //   return ::file::path(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

   //}


   //::file::path dir_system::usersystemappdata(::matter * pobject, const ::string & strPrefix)
   //{

   //   __UNREFERENCED_PARAMETER(pobject);

   //   return appdata() / strPrefix;

   //}


   //::file::path dir_system::userdata(::matter * pobject)
   //{

   //   return userfolder(pobject) / "data";

   //}


   //::file::path dir_system::userfolder(::matter * pobject)
   //{

   //   string str = appdata();

   //   string strUserFolderShift;

   //   if(App(pobject).has_property("user_folder_relative_path"))
   //   {
   //      strUserFolderShift = App(pobject).m_varTopicQuery["user_folder_relative_path"].get_string();
   //   }

   //   return str / "ca2" / strUserFolderShift;

   //}


   //::file::path dir_system::default_os_user_path_prefix(::matter * pobject)
   //{

   //   __UNREFERENCED_PARAMETER(pobject);

   //   return "CurrentUser";

   //}


   //::file::path dir_system::default_userappdata(::matter * pobject,const string & lpcszPrefix,const string & lpcszLogin)
   //{

   //   return default_userfolder(pobject,lpcszPrefix,lpcszLogin) / "appdata";

   //}


   //::file::path dir_system::default_userdata(::matter * pobject,const string & lpcszPrefix,const string & lpcszLogin)
   //{

   //   return default_userfolder(pobject,lpcszPrefix,lpcszLogin) / "data";

   //}


   //::file::path dir_system::default_userfolder(::matter * pobject,const ::string & strPrefix,const ::string & strLogin)
   //{

   //   return userfolder(pobject) / strPrefix / strLogin;

   //}


   //::file::path dir_system::userquicklaunch(::matter* pobject)
   //{

   //   __throw(todo);

   //}


   //::file::path dir_system::userprograms(::matter* pobject)
   //{

   //   __throw(todo);

   //}


   //::file::path dir_system::commonprograms()
   //{

   //   __throw(todo);

   //}


   //bool dir_system::is_inside_time(const ::file::path& pszPath)
   //{

   //   return is_inside(time(), pszPath, pobject);

   //}


   //bool dir_system::is_inside(const ::file::path& pszDir, const ::file::path& strPath)
   //{

   //   return ::str::begins_ci(pszDir, strPath);

   //}


   //bool dir_system::has_subdir(::matter* pobject, const ::file::path& pszDir)
   //{

   //   return ::file::system_dir::has_subdir(pobject, pszDir);

   //}


   //::file::path dir_system::commonappdata()
   //{

   //   return ::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path / "commonappdata";

   //}

   bool dir_system::update_module_path()
   {
      
      m_pathModule = ::path::module();

      m_pathCa2Module = ::dir::ca2_module();

      return true;

   }


   //::file::path dir_system::document()
   //{

   //   return "document://";

   //}


   //::file::path dir_system::music()
   //{

   //   return "music://";

   //}


   //::file::path dir_system::video()
   //{

   //   return "video://";

   //}


   //::file::path dir_system::image_pointer()
   //{

   //   return "image://";

   //}



} // namespace universal_windows




