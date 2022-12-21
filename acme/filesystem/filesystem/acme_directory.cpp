// Create on 2021-03-20 23:59 <3ThomasBS_
#include "framework.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "acme_path.h"
//#include "path_array.h"
#include "listing.h"
#include "acme/exception/interface_only.h"
#include "acme/operating_system/process.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/parallelization/synchronous_lock.h"


CLASS_DECL_ACME bool is_like_url_protocol(const ::scoped_string & scopedstr);


acme_directory::acme_directory()
{

}


acme_directory::~acme_directory()
{


}


void acme_directory::initialize(::particle * pparticle)
{

   ::particle::initialize(pparticle);

   m_pathInstallFolder = default_install();

//   m_pathModuleFolder = dir_ca2_module();

}


::file::path acme_directory::app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

}


::file::path acme_directory::app_app_admin(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

}


::file::path acme_directory::app_app_nest(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

}


::file::path acme_directory::app_app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

}


::file::path acme_directory::vcredist(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

}


::file::path acme_directory::install_log(string strPlatform, string strConfiguration)
{

   return install() / ("install-" + strPlatform + ".log");

}



//
//::file::path acme_directory::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


::file::path acme_directory::appdata()
{

   return ca2roaming() / "appdata" / app_relative();

}


::file::path acme_directory::public_system()
{

   return public_root() / "system";

}


::file::path acme_directory::system()
{

   return ca2roaming() / "system";

}


::file::path acme_directory::config()
{

   return ca2roaming() / "config";

}


::file::path acme_directory::local()
{

   return ca2roaming() / "local";

}


::file::path acme_directory::sensitive()
{

#ifdef WINDOWS

   return "C:\\sensitive\\sensitive";

#else

   return "/sensitive/sensitive";

#endif

}







string acme_directory::system_short_name()
{

#ifdef _UWP

   return "metro";

#else

   ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

   return m_pacmefile->as_string(pathSystemShortName).trimmed();

#endif

}


::file::path acme_directory::relative(::file::path path)
{

   path.replace_with("", ":");

   path.case_insensitive_ends(".exe");

   return path;

}

#ifdef _UWP


::file::path acme_directory::app_relative()
{

   return "";

}


#else


::file::path acme_directory::app_relative()
{

   ::file::path path = acmefile()->module();

   path.find_replace(":", "");

   path = file_path_folder(path);

   return path;

}


#endif


::file::path acme_directory::inplace_install(string strAppId, string strPlatform, string strConfiguration)
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

   return acmefile()->module() - 4;

#endif


}


::file::path acme_directory::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
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

   return acmefile()->module() - 4;

#endif

}


::file::path acme_directory::install()
{

   if (m_pathInstallFolder.is_empty())
   {

      return default_install();

   }

   return m_pathInstallFolder;

}


::file::path acme_directory::default_install()
{

#ifdef ANDROID

   return "./";

#elif defined(__APPLE__)

   return acmefile()->module()-3;

#elif defined(_UWP)

   return "";

#elif defined(FREEBSD)

   return acmefile()->module() - 2;

#else

   return acmefile()->module() - 4;

#endif

}


::file::path acme_directory::beforeca2()
{

   return ::file_path_folder(install());

}



::file::path acme_directory::stage(string strAppId, string strPlatform, string strConfiguration)
{

   return 
      inplace_install(
         strAppId,
         strPlatform,
         strConfiguration) 
      / "time" / acmenode()->time_binary_platform(strPlatform) / strConfiguration;

}


#ifdef LINUX


::file::path acme_directory::home()
{

   return getenv("HOME");

}


#else


::file::path acme_directory::home()
{

   return "";

}


#endif


//#if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//

::file::path acme_directory::bookmark()
{

   return localconfig() / "bookmark";

}


void acme_directory::set_path_install_folder(const string & strPath)
{

   m_pathInstallFolder = strPath;

}


::file::path acme_directory::sys_temp()
{

   return appdata() / "time";

}


::string acme_directory::dir_root()
{

   return "";

}


//::file::path acme_directory::home()
//{
//
//   return "";
//
//}


::file::path acme_directory::program_data()
{

   return "";

}


::file::path acme_directory::ca2appdata()
{

   return ca2roaming() / "appdata";

}



::file::path acme_directory::public_root()
{

   return program_data() / "ca2";

}

::file::path acme_directory::ca2roaming()
{

   return roaming() / "ca2";

}


::file::path acme_directory::localconfig()
{

   return ca2roaming() / "localconfig";

}


::file::path acme_directory::module()
{

   //if(m_pathModuleFolder.is_empty())
   //{

   //   auto pnode = acmenode();

   //   auto pathModule = pnode->module_path_source();

   //   m_pathModuleFolder = pathModule.folder();

   //}

   //return m_pathModuleFolder;

   auto pacmeapplication = acmeapplication();

   return pacmeapplication->get_module_folder();

}

//
//::file::path acme_directory::base_module()
//{
//
//   return "";
//
//}
//

//::file::path acme_directory::ca2_module()
//{
//
//   return "";
//
//}
//
::file::path acme_directory::archive()
{

   return "";

}



::file::path acme_directory::tool()
{

   return "";

}


::file::path acme_directory::roaming()
{

   return "";

}



::file::path acme_directory::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
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


::file::path acme_directory::program_files_x86()
{

   return {};

}



::file::path acme_directory::program_files()
{

   return {};

}

::file::path acme_directory::get_memory_map_base_folder_path()
{

   return "";

}


//string acme_directory::system_short_name()
//{
//
//   return "";
//
//}


::file::path acme_directory::machine_event_file_path()
{

   return appdata() / "machine/event/machine_event.bin";

}


::file::path acme_directory::user_appdata_local()
{

   return "";

}


//::file::path acme_directory::tool()
//{
//
//   return archive() / "tool-windows";
//
//}


//bool acme_directory::_is(const ::file::path & path1)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}


//::file::path acme_directory::base_module()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


//void acme_directory::create(const ::file::path & path)
//{
//
//   return _create(path);
//
//}


void acme_directory::create(const ::file::path & pathParam)
{

   if (is_like_url_protocol(pathParam))
   {

      return;

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

   index i = patha.get_upper_bound();

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


void acme_directory::_create2(const ::file::path & pathParam)
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

   __create(pathParam);

}


//void acme_directory::_create_directory(const ::file::path & pathParam)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}

   
bool acme_directory::is(const ::file::path & path)
{

   if(path.is_empty())
   {

      throw ::exception(error_null_pointer);

   }

   bool bDir;

   if (_is(bDir, path))
   {

      return bDir;

   }

   return false;

}

//string name(string path);


//void acme_directory::enumrls(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//void acme_directory::rls_dir(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//   //return "";
//
//}
//
//
//void acme_directory::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void acme_directory::enumerate(::file::listing & listing, const ::scoped_string & scopedstr, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   throw ::interface_only();
//
//}


bool acme_directory::enumerate(::file::listing & listing)
{

   return ::file::enumerator::enumerate(listing);

}


bool acme_directory::defer_enumerate_media_library(::file::listing& listing)
{

   synchronous_lock sl(m_pmutexMediaLibrary);

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

               path.m_iDir = 0;

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


::media_library::item* acme_directory::media_library_item(const ::file::path& path)
{

   synchronous_lock sl(m_pmutexMediaLibrary);

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


bool acme_directory::defer_process_media_library_path(::file::path& path)
{

   auto plibraryitem = media_library_item(path);

   if(::is_set(plibraryitem) && plibraryitem->get_full_path().has_char())
   {

      path = plibraryitem->get_full_path();

      return true;

   }

   return false;

}


bool acme_directory::defer_media_library_representative_file_name(::file::path & path)
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



bool acme_directory::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
{

   return ::file::enumerator::list(stra, scopedstr, eflag);

}


//void acme_directory::enumerate(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//
//
//void acme_directory::ls_file(::file::path_array & stra, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//}
//

//         ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);


         //::file::path archive();


int acme_directory::make_path(const ::scoped_string & scopedstr)
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


//::file::path acme_directory::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}

//virtual::file::path base_module();


//} // namespace dir


bool acme_directory::_is(bool & bDir, const ::file::path & path)
{

   auto pathFinal = m_pacmepath->_final(path);

   bDir = ::is_directory(pathFinal);

   return true;

}


void acme_directory::__create(const ::file::path & path)
{

   ::create_directory(path);

   /*auto estatus =*/ 

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void acme_directory::erase(const ::file::path & path)
{

   ::erase_directory(path);

}


string acme_directory::get_current()
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_directory::change_current(const ::scoped_string & scopedstr)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_directory::change_to_home()
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


void acme_directory::add_media_library_item(::media_library::item* pmedialibraryitem)
{

   synchronous_lock lock(m_pmutexMediaLibrary);

   auto emedialibrary = pmedialibraryitem->media_library_type();

   auto& a = m_medialibraryitemmap[emedialibrary];

   a.add(pmedialibraryitem);

}


