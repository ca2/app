// Create on 2021-03-20 23:59 <3ThomasBS_
#include "../../../acid/framework.h"
#include "../../../acid/filesystem/filesystem/ace_directory.h"
#include "../../../acid/filesystem/filesystem/ace_file.h"
#include "../../../acid/filesystem/filesystem/ace_path.h"
//#include "path_array.h"
#include "../../../acid/filesystem/filesystem/listing.h"
#include "../../../acid/exception/interface_only.h"
#include "../../../acid/operating_system/process.h"
#include "../../../acid/platform/application.h"
#include "../../../acid/platform/node.h"
#include "../../../acid/platform/system.h"
#include "../../../acid/parallelization/synchronous_lock.h"


CLASS_DECL_ACID bool is_like_url_protocol(const ::scoped_string & scopedstr);


cdirectory::cdirectory()
{

}


ace_directory::~ace_directory()
{


}


void ace_directory::initialize(::particle * pparticle)
{

   ::particle::initialize(pparticle);

   m_pathInstallFolder = default_install();

   m_pathFolder = get_current();


//   m_pathModuleFolder = dir_ca2_module();

}


::file::path ace_directory::app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

}


::file::path ace_directory::app_app_admin(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

}


::file::path ace_directory::app_app_nest(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

}


::file::path ace_directory::app_app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

}


::file::path ace_directory::vcredist(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

}


::file::path ace_directory::install_log(string strPlatform, string strConfiguration)
{

   return install() / ("install-" + strPlatform + ".log");

}



//
//::file::path ace_directory::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


::file::path ace_directory::appdata()
{

   return roaming() / appid();

}


::file::path ace_directory::public_system()
{

   return public_root() / "system";

}


::file::path ace_directory::system()
{

   return ca2roaming() / "system";

}


::file::path ace_directory::config()
{

   return ca2roaming() / "config";

}


::file::path ace_directory::local()
{

   return ca2roaming() / "local";

}


::file::path ace_directory::sensitive()
{

#ifdef WINDOWS

   return "C:\\sensitive\\sensitive";

#else

   return "/sensitive/sensitive";

#endif

}







string ace_directory::system_short_name()
{

#ifdef UNIVERSAL_WINDOWS

   return "metro";

#else

   ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

   return m_pacefile->as_string(pathSystemShortName).trimmed();

#endif

}


::file::path ace_directory::relative(::file::path path)
{

   path.replace_with("", ":");

   path.case_insensitive_ends(".exe");

   return path;

}


::string ace_directory::appid()
{

   return application()->m_strAppId;

}


::file::path ace_directory::inplace_install(string strAppId, string strPlatform, string strConfiguration)
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

   return acefile()->module() - 4;

#endif


}


::file::path ace_directory::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
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

   return acefile()->module() - 4;

#endif

}


::file::path ace_directory::install()
{

   if (m_pathInstallFolder.is_empty())
   {

      return default_install();

   }

   return m_pathInstallFolder;

}


::file::path ace_directory::default_install()
{

#ifdef ANDROID

   return "./";

#elif defined(__APPLE__)

   return acefile()->module()-3;

#elif defined(UNIVERSAL_WINDOWS)

   return "";

#elif defined(FREEBSD) || defined(OPENBSD)

   return acefile()->module() - 2;

#else

   return acefile()->module() - 4;

#endif

}


::file::path ace_directory::beforeca2()
{

   return ::file_path_folder(install());

}



::file::path ace_directory::stage(string strAppId, string strPlatform, string strConfiguration)
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
//::file::path ace_directory::home()
//{
//
//   return getenv("HOME");
//
//}
//
//
//#else
//

::file::path ace_directory::home()
{

   throw interface_only();

   return "";

}


::file::path ace_directory::icloud_container2(const char * psz_iCloudContainerIdentifier)
{
   
   ::string str_iCloudContainerIdentifier;
   
   str_iCloudContainerIdentifier = acepath()->icloud_container_identifier(psz_iCloudContainerIdentifier);
   
   ::file::path pathContainer;
   
   pathContainer = ("icloud://" + str_iCloudContainerIdentifier);
   
   return pathContainer;
   
}


::file::path ace_directory::icloud_container2_final(const char * psz_iCloudContainerIdentifier)
{
   
   throw ::interface_only();
   
   return {};
   
}


::file::path ace_directory::icloud_container_documents(const char * psz_iCloudContainerIdentifier)
{

   return icloud_container2(psz_iCloudContainerIdentifier) / "Documents";
   
}


bool ace_directory::is_icloud_container(const ::file::path & path, const char * pszContentIdentifier)
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


bool ace_directory::has_icloud_container(const char * pszContentIdentifier)
{
   
   return false;
   
}



//
//#endif


//#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//

::file::path ace_directory::bookmark()
{

   return localconfig() / "bookmark";

}


void ace_directory::set_path_install_folder(const string & strPath)
{

   m_pathInstallFolder = strPath;

}


::file::path ace_directory::sys_temp()
{

   return appdata() / "time";

}


::file::path ace_directory::temp()
{

   return sys_temp();

}


::string ace_directory::dir_root()
{

   return "";

}


//::file::path ace_directory::home()
//{
//
//   return "";
//
//}


::file::path ace_directory::program_data()
{

   return "";

}


::file::path ace_directory::ca2appdata()
{

   return ca2roaming() / "appdata";

}



::file::path ace_directory::public_root()
{

   return program_data() / "ca2";

}

::file::path ace_directory::ca2roaming()
{

   return roaming() / "ca2";

}


::file::path ace_directory::localconfig()
{

   return ca2roaming() / "localconfig";

}


::file::path ace_directory::module()
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
//::file::path ace_directory::base_module()
//{
//
//   return "";
//
//}
//

//::file::path ace_directory::ca2_module()
//{
//
//   return "";
//
//}
//
::file::path ace_directory::archive()
{

   return "";

}



::file::path ace_directory::tool()
{

   return "";

}


::file::path ace_directory::roaming()
{

   return "";

}



::file::path ace_directory::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
{

   ::file::path_array patha;

   patha.add_tokens(pszEnv, ":", false);

   string strCandidate;

   for (i32 i = 0; i < patha.get_count(); i++)
   {

      strCandidate = patha[i] / pszTopic;

      //if (file()->exists(strCandidate))
      if (m_pacefile->exists(strCandidate))
      {
         
         return strCandidate;

      }

   }

   return "";

}


::file::path ace_directory::program_files_x86()
{

   return {};

}



::file::path ace_directory::program_files()
{

   return {};

}

::file::path ace_directory::get_memory_map_base_folder_path()
{

   return "";

}


//string ace_directory::system_short_name()
//{
//
//   return "";
//
//}


::file::path ace_directory::machine_event_file_path()
{

   return appdata() / "machine/event/machine_event.bin";

}


::file::path ace_directory::user_appdata_local()
{

   return "";

}


//::file::path ace_directory::tool()
//{
//
//   return archive() / "tool-windows";
//
//}


//bool ace_directory::_is(const ::file::path & path1)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}


//::file::path ace_directory::base_module()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


//void ace_directory::create(const ::file::path & path)
//{
//
//   return _create(path);
//
//}


void ace_directory::create(const ::file::path & pathParam)
{

   if (is_like_url_protocol(pathParam))
   {

      return;

   }
   
   if(acefile()->exists(pathParam))
   {
      
      acefile()->erase(pathParam);
      
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


void ace_directory::_create2(const ::file::path & pathParam)
{

   //if (is(pathParam))
   //{

   //   return;

   //}

   auto bExists = m_pacefile->exists(pathParam);

   if(bExists)
   {

      m_pacefile->erase(pathParam);

   }

   _create4(pathParam);

}


//void ace_directory::_create_directory(const ::file::path & pathParam)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}

   
::file::e_type ace_directory::file_type(const ::file::path & path)
{

   if(path.is_empty())
   {

      return ::file::e_type_existent_folder;

   }

   auto etype = _file_type(path);

   return etype;

}

//string name(string path);


//void ace_directory::enumrls(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//void ace_directory::rls_dir(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//   //return "";
//
//}
//
//
//void ace_directory::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void ace_directory::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}


bool ace_directory::enumerate(::file::listing & listing)
{

   return ::file::enumerator::enumerate(listing);

}


bool ace_directory::defer_enumerate_media_library(::file::listing& listing)
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


bool ace_directory::defer_enumerate_protocol(::file::listing& listing)
{
   
   return node()->defer_enumerate_protocol(listing);
   
}


::media_library::item* ace_directory::media_library_item(const ::file::path& path)
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


bool ace_directory::defer_process_media_library_path(::file::path& path)
{

   auto plibraryitem = media_library_item(path);

   if(::is_set(plibraryitem) && plibraryitem->get_full_path().has_char())
   {

      path = plibraryitem->get_full_path();

      return true;

   }

   return false;

}


bool ace_directory::defer_media_library_representative_file_name(::file::path & path)
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



bool ace_directory::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
{

   return ::file::enumerator::list(stra, scopedstr, eflag);

}


//void ace_directory::enumerate(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void ace_directory::ls_file(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//         ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);


         //::file::path archive();


int ace_directory::make_path(const ::scoped_string & scopedstr)
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


//::file::path ace_directory::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}

//virtual::file::path base_module();


//} // namespace dir


::file::e_type ace_directory::_file_type(const ::file::path & path)
{

   auto pathFinal = acepath()->safe_get_real_path(path);

   auto etype = ::safe_file_type(pathFinal);

   return etype;

}


void ace_directory::_create4(const ::file::path & path)
{

   ::create_directory(path);

   /*auto estatus =*/ 

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void ace_directory::erase(const ::file::path & path)
{

   ::erase_directory(path);

}


void ace_directory::erase_recursively(const ::file::path &path)
{
   
   

}


string_to_string ace_directory::map_content(const ::file::path & path)
{

   ::string_to_string stringmap;

   ::file::listing listing;

   listing.set_file_listing(path);

   enumerate(listing);

   for(auto & path : listing)
   {

      stringmap[path] = acefile()->safe_get_string(path);

   }

   return ::transfer(stringmap);

}


string_array ace_directory::enumerate_content(const ::file::path &path)
{

   ::string_array stra;

   ::file::listing listing;

   listing.set_file_listing(path);

   enumerate(listing);

   for(auto & path : listing)
   {

      stra.add(acefile()->safe_get_string(path));

   }

   return ::transfer(stra);

}


::file::path ace_directory::get_current()
{

   throw ::interface_only();

   //throw ::interface_only();

}


void ace_directory::change_current(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void ace_directory::change_to_home()
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


void ace_directory::add_media_library_item(::media_library::item* pmedialibraryitem)
{

   _synchronous_lock lock(m_pmutexMediaLibrary);

   auto emedialibrary = pmedialibraryitem->media_library_type();

   auto& a = m_medialibraryitemmap[emedialibrary];

   a.add(pmedialibraryitem);

}


::file::path ace_directory::windows()
{

   return {};

}


::file::path ace_directory::system_drive()
{

   return {};

}


bool ace_directory::is_accessible(const ::file::path & path)
{

   return true;

}



