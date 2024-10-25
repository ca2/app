// Create on 2021-03-20 23:59 <3ThomasBS_
#include "framework.h"
#include "directory_system.h"
#include "file_system.h"
#include "path_system.h"
//#include "path_array.h"
#include "listing.h"
#include "acme/exception/interface_only.h"
#include "acme/operating_system/process.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/parallelization/synchronous_lock.h"


//CLASS_DECL_ACME bool is_like_url_protocol(const ::scoped_string & scopedstr);


directory_system::directory_system()
{

   m_pathUpload = "C:\\upload";

}


directory_system::~directory_system()
{


}


void directory_system::initialize(::particle * pparticle)
{

   ::particle::initialize(pparticle);

   m_pathInstallFolder = default_install();

   m_pathFolder = get_current();


//   m_pathModuleFolder = dir_ca2_module();

}


::file::path directory_system::app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

}


::file::path directory_system::app_app_admin(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

}


::file::path directory_system::app_app_nest(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

}


::file::path directory_system::app_app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

}


::file::path directory_system::vcredist(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

}


::file::path directory_system::install_log(string strPlatform, string strConfiguration)
{

   return install() / ("install-" + strPlatform + ".log");

}



//
//::file::path directory_system::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


::file::path directory_system::appdata()
{

   return roaming() / appid();

}


//::file::path directory_system::user_config()
//{
//
//   return public_root() / "system";
//
//}
//
//
::file::path directory_system::user()
{

   return ca2roaming() / "user";

}


::file::path directory_system::config()
{

   return ca2roaming() / "config";

}


::file::path directory_system::local()
{

   return ca2roaming() / "local";

}


::file::path directory_system::sensitive()
{

#ifdef WINDOWS

   return "C:\\sensitive\\sensitive";

#else

   return "/sensitive/sensitive";

#endif

}







string directory_system::system_short_name()
{

#ifdef UNIVERSAL_WINDOWS

   return "metro";

#else

   ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

   return m_pacmefile->as_string(pathSystemShortName).trimmed();

#endif

}


::file::path directory_system::relative(::file::path path)
{

   path.replace_with("", ":");

   path.case_insensitive_ends(".exe");

   return path;

}


::string directory_system::appid()
{

   return application()->m_strAppId;

}


::file::path directory_system::inplace_install(string strAppId, string strPlatform, string strConfiguration)
{

#ifdef WINDOWS_DESKTOP

   ::file::path path;

   string strFolder;

   auto pFind = strAppId.find('/');

   if (strPlatform.case_insensitive_order("win32") == 0 || strPlatform.case_insensitive_order("x86") == 0)
   {

      path = program_files_x86();

   }
   else
   {
      path = program_files_x86();


      path = program_files();

   }

   if (::is_null(pFind))
   {

      path /= strAppId;

   }
   else
   {

      path /= strAppId(0, pFind);

      path /= strAppId(pFind + 1);

   }

   return path;

#elif defined(ANDROID)

   return "./";

#else

   return file_system()->module() - 4;

#endif


}


::file::path directory_system::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
{

#ifdef WINDOWS_DESKTOP

   ::file::path path;

   string strFolder;

   auto pFind = strAppId.find('/');

   path = ca2roaming();

   path /= "_matter";

   return path;

#elif defined(ANDROID)

   return         "./";

#else

   return file_system()->module() - 4;

#endif

}


::file::path directory_system::install()
{

   if (m_pathInstallFolder.is_empty())
   {

      return default_install();

   }

   return m_pathInstallFolder;

}


::file::path directory_system::default_install()
{

#ifdef ANDROID

   return "./";

#elif defined(__APPLE__)

   return file_system()->module()-3;

#elif defined(UNIVERSAL_WINDOWS)

   return "";

#elif defined(FREEBSD) || defined(OPENBSD)

   return file_system()->module() - 2;

#else

   return file_system()->module() - 4;

#endif

}


::file::path directory_system::beforeca2()
{

   return ::file_path_folder(install());

}



::file::path directory_system::stage(string strAppId, string strPlatform, string strConfiguration)
{

   return 
      inplace_install(
         strAppId,
         strPlatform,
         strConfiguration) 
      / "time" / node()->time_binary_platform(strPlatform) / strConfiguration;

}


//#ifdef LINUX
//
//
//::file::path directory_system::home()
//{
//
//   return getenv("HOME");
//
//}
//
//
//#else
//

::file::path directory_system::home()
{

   throw interface_only();

   return "";

}


::file::path directory_system::icloud_container2(const char * psz_iCloudContainerIdentifier)
{
   
   ::string str_iCloudContainerIdentifier;
   
   str_iCloudContainerIdentifier = path_system()->icloud_container_identifier(psz_iCloudContainerIdentifier);
   
   ::file::path pathContainer;
   
   pathContainer = ("icloud://" + str_iCloudContainerIdentifier);
   
   return pathContainer;
   
}


::file::path directory_system::icloud_container2_final(const char * psz_iCloudContainerIdentifier)
{
   
   throw ::interface_only();
   
   return {};
   
}


::file::path directory_system::icloud_container_documents(const char * psz_iCloudContainerIdentifier)
{

   return icloud_container2(psz_iCloudContainerIdentifier) / "Documents";
   
}


bool directory_system::is_icloud_container(const ::file::path & path, const char * pszContentIdentifier)
{
   
   ::file::path pathFolder;
   
   pathFolder = icloud_container2(pszContentIdentifier);
   
   if(path.folder() == pathFolder ||
      path.folder().begins(::string(pathFolder) + "/"))
   {
      
      return true;
      
   }
      
   return false;
   
}


bool directory_system::has_icloud_container(const char * pszContentIdentifier)
{
   
   return false;
   
}



//
//#endif


//#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//

::file::path directory_system::bookmark()
{

   return localconfig() / "bookmark";

}


void directory_system::set_path_install_folder(const string & strPath)
{

   m_pathInstallFolder = strPath;

}


::file::path directory_system::sys_temp()
{

   return appdata() / "time";

}


::file::path directory_system::temp()
{

   return sys_temp();

}


::string directory_system::dir_root()
{

   return "";

}


//::file::path directory_system::home()
//{
//
//   return "";
//
//}


::file::path directory_system::program_data()
{

   return "";

}


::file::path directory_system::application_home()
{

   return home() / "application";

}


::file::path directory_system::application_home(const ::scoped_string & scopedstrAppId)
{

   return application_home() / scopedstrAppId;

}


::file::path directory_system::ca2appdata()
{

   return ca2roaming() / "appdata";

}



::file::path directory_system::public_root()
{

   return program_data() / "ca2";

}

::file::path directory_system::ca2roaming()
{

   return roaming() / "ca2";

}


::file::path directory_system::localconfig()
{

   return ca2roaming() / "localconfig";

}


::file::path directory_system::module()
{

   //if(m_pathModuleFolder.is_empty())
   //{

   //   auto pnode = node();

   //   auto pathModule = pnode->module_path_source();

   //   m_pathModuleFolder = pathModule.folder();

   //}

   //return m_pathModuleFolder;

   auto papplication = application();

   return papplication->get_module_folder();

}

//
//::file::path directory_system::base_module()
//{
//
//   return "";
//
//}
//

//::file::path directory_system::ca2_module()
//{
//
//   return "";
//
//}
//
::file::path directory_system::archive()
{

   return "";

}



::file::path directory_system::tool()
{

   return "";

}


::file::path directory_system::roaming()
{

   return "";

}



::file::path directory_system::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
{

   ::file::path_array patha;

   patha.add_tokens(pszEnv, ":", false);

   string strCandidate;

   for (i32 i = 0; i < patha.get_count(); i++)
   {

      strCandidate = patha[i] / pszTopic;

      //if (file()->exists(strCandidate))
      if (m_pacmefile->exists(strCandidate))
      {
         
         return strCandidate;

      }

   }

   return "";

}


::file::path directory_system::program_files_x86()
{

   return {};

}



::file::path directory_system::program_files()
{

   return {};

}

::file::path directory_system::get_memory_map_base_folder_path()
{

   return "";

}


//string directory_system::system_short_name()
//{
//
//   return "";
//
//}


::file::path directory_system::machine_event_file_path()
{

   return appdata() / "machine/event/machine_event.bin";

}


::file::path directory_system::user_appdata_local()
{

   return "";

}


//::file::path directory_system::tool()
//{
//
//   return archive() / "tool-windows";
//
//}


//bool directory_system::_is(const ::file::path & path1)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}


//::file::path directory_system::base_module()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


//void directory_system::create(const ::file::path & path)
//{
//
//   return _create(path);
//
//}


void directory_system::create(const ::file::path & pathParam)
{

   //if (is_like_url_protocol(pathParam))
   //{

   //   return;

   //}
   //
   if(file_system()->exists(pathParam))
   {
      
      file_system()->erase(pathParam);
      
   }

   if (is(pathParam))
   {

      return;

   }

   ::file::path path(pathParam);

   string strName;

   ::file::path pathDir;

   strsize iLastPo = -1;

   ::file::path_array patha;

   ascendants_path(path, patha);

   ::collection::index i = patha.get_upper_bound();

   for (; i >= 0; i--)
   {

      string strDir = patha[i];

      if (is(strDir))
      {

         i++;

         break;

      }

   }

   if (i < 0)
   {

      return;

   }

   for (; i < patha.get_count(); i++)
   {

      string strDir = patha[i];

      _create2(strDir);

   }

}


void directory_system::_create2(const ::file::path & pathParam)
{

   //if (is(pathParam))
   //{

   //   return;

   //}

   auto bExists = m_pacmefile->exists(pathParam);

   if(bExists)
   {

      m_pacmefile->erase(pathParam);

   }

   _create4(pathParam);

}


//void directory_system::_create_directory(const ::file::path & pathParam)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}

   
::file::e_type directory_system::file_type(const ::file::path & path)
{

   if(path.is_empty())
   {

      return ::file::e_type_existent_folder;

   }

   auto etype = _file_type(path);

   return etype;

}

//string name(string path);


//void directory_system::enumrls(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//void directory_system::rls_dir(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//   //return "";
//
//}
//
//
//void directory_system::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void directory_system::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}


bool directory_system::enumerate(::file::listing & listing)
{

   return ::file::enumerator::enumerate(listing);

}


bool directory_system::defer_enumerate_media_library(::file::listing& listing)
{

   _synchronous_lock sl(m_pmutexMediaLibrary);

   for (auto& pair : m_medialibraryitemmap)
   {

      auto emedialibrary = pair.m_element1;

      string strProtocol = ::media_library::media_library_protocol(emedialibrary);

      if (listing.m_pathUser == strProtocol)
      {

         auto& libraryitema = pair.m_element2;

         if (libraryitema.has_element())
         {

            if (!listing.on_start_enumerating(this))
            {

               return false;

            }

            for (auto& plibraryitem : libraryitema)
            {

               ::file::path path;

               path = plibraryitem->get_path();

               path.set_file_path();

               listing.defer_add(path);

               string strTitle = plibraryitem->get_title();

               listing.m_straTitle.add(strTitle);

            }

            return true;

         }

      }

   }

   return false;

}


bool directory_system::defer_enumerate_protocol(::file::listing& listing)
{
   
   return node()->defer_enumerate_protocol(listing);
   
}


::media_library::item* directory_system::media_library_item(const ::file::path& path)
{

   _synchronous_lock sl(m_pmutexMediaLibrary);

   string strId(path);

   for (auto& pair : m_medialibraryitemmap)
   {

      auto emedialibrary = pair.m_element1;

      string strProtocol = ::media_library::media_library_protocol(emedialibrary);

      if (strId.case_insensitive_begins_eat(strProtocol))
      {

         auto& libraryitema = pair.m_element2;

         if (libraryitema.has_element())
         {

            for (auto& plibraryitem : libraryitema)
            {

               if (strId == plibraryitem->get_id())
               {

                  return plibraryitem;

               }

            }

         }

         return nullptr;

      }

   }

   return nullptr;

}


bool directory_system::defer_process_media_library_path(::file::path& path)
{

   auto plibraryitem = media_library_item(path);

   if(::is_set(plibraryitem) && plibraryitem->get_full_path().has_char())
   {

      path = plibraryitem->get_full_path();

      return true;

   }

   return false;

}


bool directory_system::defer_media_library_representative_file_name(::file::path & path)
{

   auto plibraryitem = media_library_item(path);

   if (::is_set(plibraryitem) && plibraryitem->get_mime_type().has_char())
   {

      string strMimeType = plibraryitem->get_mime_type();

      strMimeType.make_lower();

      if (strMimeType.case_insensitive_begins_eat("audio/"))
      {

         if (strMimeType == "mpeg")
         {

            path = "file.mp3";

            return true;

         }

      }

   }

   return false;

}



bool directory_system::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
{

   return ::file::enumerator::list(stra, scopedstr, eflag);

}


//void directory_system::enumerate(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void directory_system::ls_file(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//         ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);


         //::file::path archive();


int directory_system::make_path(const ::scoped_string & scopedstr)
{

   throw ::interface_only();

   return -1;

}


//   };


//} // namespace posix




      /*namespace dir
      {*/


      //string name(const ::file::path & path);
      //bool mk(const ::string & strPath);
      //bool _mk(const  char * path); // makes a directory path (all intermediates too)
      //bool is(const ::file::path & path);
      //bool _is(const ::file::path & path);
      //bool mk(const  char * path); // makes a directory path (all intermediates too)
      //bool mkdir(const  char * path); // only creates if parent dir already exists
      //void ls(::file::path_array & patha, const ::file::path & path);
      //void ls_dir(::file::path_array & patha, const ::file::path & path);
      //void ls_file(::file::path_array & patha, const ::file::path & path);
      //void rls(::file::path_array & patha, const ::file::path & path);
      //void rls_dir(::file::path_array & patha, const ::file::path & path);


//::file::path directory_system::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}

//virtual::file::path base_module();


//} // namespace dir


::file::e_type directory_system::_file_type(const ::file::path & path)
{

   auto pathFinal = path_system()->safe_get_real_path(path);

   auto etype = ::safe_file_type(pathFinal);

   return etype;

}


void directory_system::_create4(const ::file::path & path)
{

   ::create_directory(path);

   /*auto estatus =*/ 

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void directory_system::erase(const ::file::path & path)
{

   ::erase_directory(path);

}


void directory_system::erase_recursively(const ::file::path &path)
{
   
   

}


string_to_string directory_system::map_content(const ::file::path & path)
{

   ::string_to_string stringmap;

   ::file::listing listing;

   listing.set_file_listing(path);

   enumerate(listing);

   for(auto & path : listing)
   {

      stringmap[path] = file_system()->safe_get_string(path);

   }

   return ::transfer(stringmap);

}


string_array directory_system::enumerate_content(const ::file::path &path)
{

   ::string_array stra;

   ::file::listing listing;

   listing.set_file_listing(path);

   enumerate(listing);

   for(auto & path : listing)
   {

      stra.add(file_system()->safe_get_string(path));

   }

   return ::transfer(stra);

}


::file::path directory_system::get_current()
{

   throw ::interface_only();

   //throw ::interface_only();

}


void directory_system::change_current(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void directory_system::change_to_home()
{

   ::file::path pathHome = home();

   //auto estatus = change_current(pathHome);

   change_current(pathHome);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void directory_system::add_media_library_item(::media_library::item* pmedialibraryitem)
{

   _synchronous_lock lock(m_pmutexMediaLibrary);

   auto emedialibrary = pmedialibraryitem->media_library_type();

   auto& a = m_medialibraryitemmap[emedialibrary];

   a.add(pmedialibraryitem);

}


::file::path directory_system::windows()
{

   throw ::interface_only();

   return {};

}


::file::path directory_system::system_drive()
{

   throw ::interface_only();

   return {};

}


::file::path directory_system::fonts()
{

   throw ::interface_only();

   return {};

}


::file::path directory_system::___fonts()
{

   throw ::interface_only();

   return {};

}



bool directory_system::is_accessible(const ::file::path & path)
{

   return true;

}


bool directory_system::contains_files(const ::file::path& path, const ::string_array& straName, int iMinimumSize)
{

   for (auto& strName : straName)
   {

      auto pathFile = path / strName;

      if (!file_system()->exists(pathFile))
      {

         return false;

      }

      if (iMinimumSize > 0)
      {

         if (file_system()->get_size(pathFile) < iMinimumSize)
         {

            return false;

         }

      }

   }

   return true;

}





//
//directory_system::directory_system()
//{
//
//   m_pathUpload = "C:\\upload";
//
//}
//
//
//directory_system::~directory_system()
//{
//
//}

//
//void directory_system::initialize(::particle * pparticle)
//{
//
//   /*auto estatus = */ ::object::initialize(pparticle);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //auto psystem = system();
//
//   //m_pathModule = psystem->m_pacmedirectory->module();
//
//   //return true;
//
//}


void directory_system::init_system()
{

//   if (!update_module_path())
//   {
//
//      return ::error_failed;
//
//   }
//
   m_pathInstall = this->install();

   //auto psystem = system();

   //auto pfile = psystem->m_pfilesystem;

   //auto pathModule = pfile->m_pathModule;

   //::file::path pathModuleFolder = pathModule.folder();

//   m_pathModule = pathModuleFolder;

   //m_pathModule = application()->get_module_folder();

//   auto pathCa2Module = pfile->m_pathCa2Module;
//
//   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();
//
//   m_pathCa2Module = pathCa2ModuleFolder;

   //auto psystem = system();

   auto pacmedirectory = this;

#if defined(__APPLE__) || (defined(DEBUG)) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)

   if ( pacmedirectory->is(application()->side_get_matter_path("app/_matter/main")))
   {

      m_pathLocalAppMatterFolder = application()->side_get_matter_path("");

      m_pathLocalAppMatterCacheFolder = system()->local_get_matter_cache_path();

   }
   else
#endif
   {

      m_pathLocalAppMatterFolder = system()->local_get_matter_path();

      m_pathLocalAppMatterCacheFolder = system()->local_get_matter_cache_path();

   }

   //__construct(m_pfilewatcher);

   pacmedirectory->create(this->bookmark());

   //if (!update_module_path())
   //{

   //   return false;

   //}

   //if (m_pziputil == nullptr)
   //{

   //   m_pziputil = __allocate ::zip::util();

   //}

   ::string strAppId = this->appid();

   information() << "directory_system::init_system strAppId : " << strAppId;

   m_pathDefaultAppData = compute_default_app_data_path();

   string strAppFolder;

   //if (psystem->m_plibrary)
   //{

   //   if (psystem->m_plibrary->get_ca2_library())
   //   {

   //      strAppFolder = psystem->m_plibrary->get_ca2_library()->m_strFolder;

   //      if (strAppFolder.is_empty())
   //      {

   //         strAppFolder = psystem->m_plibrary->get_ca2_library()->m_strName;

   //      }

   //   }

   //}

   //if (strAppFolder.is_empty())
   //{

      //strAppFolder = _002Underscore(application()->m_strAppId);

   //}

   m_pathDefaultAppData /= strAppFolder;

   //m_strCa2DefaultAppData /= psystem->get_system_platform();

   //m_strCa2DefaultAppData /= psystem->get_system_configuration();

   ::file::path pathAppData;

   //auto psystem = system();

   if (system()->has_property("app_folder"))
   {

      //pathAppData = psystem->payload("app_folder");

      pathAppData = system()->payload("app_folder");

   }

   if (pathAppData.has_char())
   {

      m_pathAppData = pathAppData;

   }
   else
   {

      m_pathAppData = m_pathDefaultAppData;

   }

   information() << "m_pathAppData : " << m_pathAppData;

}


void directory_system::term_system()
{

   //m_pfilewatcher.release();

}


void directory_system::finalize()
{

   ::object::finalize();

}


::file::path directory_system::compute_default_app_data_path()
{

   return this->home() / "application";

}


//bool directory_system::update_module_path()
//{
//
//   //auto & context = Context;
//
//   auto psystem = system();
//
//   auto pfile = psystem->m_pfilesystem;
//
//   auto pathModule = pfile->m_pathModule;
//
//   ::file::path pathModuleFolder = pathModule.folder();
//
//   m_pathModule = pathModuleFolder;
//
//   auto pathCa2Module = pfile->m_pathCa2Module;
//
//   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();
//
//   m_pathCa2Module = pathCa2ModuleFolder;
//
//   return true;
//
//}


//::string directory_system::dir_root()
//{
//
//   return "";
//
//}


//
//::file::path directory_system::get_memory_map_base_folder_path() const
//{
//
//   return "";
//
//}
//
//
//::file::path directory_system::home()
//{
//
//
//   return "";
//
//}
//


//
//
//::file::path directory_system::program_data()
//{
//
//   return "";
//
//}
//
//
//::file::path directory_system::roaming()
//{
//
//
//   return "";
//
//
//}


//::file::path directory_system::application_installer_folder(const ::file::path& pathExe, string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
//{
//
//   return "";
//
//}


//::file::path directory_system::get_application_path(string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
//{
//
//   return "";
//
//}


// ::file::path directory_system::get_last_run_application_path_file(string strAppId)
// {

//    return "";

// }


// ::file::path directory_system::get_last_run_application_path(string strAppId)
// {

//    return "";

// }

