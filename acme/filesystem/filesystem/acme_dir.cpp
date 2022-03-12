// Create on 2021-03-20 23:59 <3ThomasBS_
#include "framework.h"
#include "acme/operating_system.h"
#include "acme_dir.h"
#include "acme_file.h"
#include "acme_path.h"


CLASS_DECL_ACME bool is_like_url_protocol(const char * psz);


acme_dir::acme_dir()
{

}


acme_dir::~acme_dir()
{


}


void acme_dir::initialize(::object * pobject)
{

   ::matter::initialize(pobject);

   m_pathInstallFolder = default_install();

   m_pathModuleFolder = dir_ca2_module();

}


::file::path acme_dir::app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

}


::file::path acme_dir::app_app_admin(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

}


::file::path acme_dir::app_app_nest(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

}


::file::path acme_dir::app_app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

   return stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

}


::file::path acme_dir::vcredist(string strPlatform, string strConfiguration)
{

   return stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

}


::file::path acme_dir::install_log(string strPlatform, string strConfiguration)
{

   return install() / ("install-" + strPlatform + ".log");

}



//
//::file::path acme_dir::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


::file::path acme_dir::appdata()
{

   return ca2roaming() / "appdata" / app_relative();

}


::file::path acme_dir::public_system()
{

   return public_root() / "system";

}


::file::path acme_dir::system()
{

   return ca2roaming() / "system";

}


::file::path acme_dir::config()
{

   return ca2roaming() / "config";

}


::file::path acme_dir::local()
{

   return ca2roaming() / "local";

}


::file::path acme_dir::sensitive()
{

#ifdef WINDOWS

   return "C:\\sensitive\\sensitive";

#else

   return "/sensitive/sensitive";

#endif

}







string acme_dir::system_short_name()
{

#ifdef _UWP

   return "metro";

#else

   ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

   return m_pacmefile->as_string(pathSystemShortName).trimmed();

#endif

}


::file::path acme_dir::relative(::file::path path)
{

   path.replace_with("", ":");

   ::str::ends_eat_ci(path, ".exe");

   return path;

}

#ifdef _UWP


::file::path acme_dir::app_relative()
{

   return "";

}


#else


::file::path acme_dir::app_relative()
{

   ::file::path path = m_psystem->m_pacmefile->module();

   path = file_path_folder(path);

   return path;

}


#endif



::file::path acme_dir::inplace_install(string strAppId, string strPlatform, string strConfiguration)
{

#ifdef WINDOWS_DESKTOP

   ::file::path path;

   string strFolder;

   strsize iFind = strAppId.find('/');

   if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
   {

      path = program_files_x86();

   }
   else
   {
      path = program_files_x86();


      path = program_files();

   }

   if (iFind < 0)
   {

      path /= strAppId;

   }
   else
   {

      path /= strAppId.Left(iFind);

      path /= strAppId.Mid(iFind + 1);

   }

   return path;

#elif defined(ANDROID)

   return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

#else

   return m_psystem->m_pacmefile->module() - 4;

#endif


}


::file::path acme_dir::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
{

#ifdef WINDOWS_DESKTOP

   ::file::path path;

   string strFolder;

   strsize iFind = strAppId.find('/');

   path = ca2roaming();

   path /= "_matter";

   return path;

#elif defined(ANDROID)

   return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

#else

   return m_psystem->m_pacmefile->module() - 4;

#endif

}


::file::path acme_dir::install()
{

   if (m_pathInstallFolder == nullptr || m_pathInstallFolder.is_empty())
   {

      return default_install();

   }

   return m_pathInstallFolder;

}


::file::path acme_dir::default_install()
{

#ifdef ANDROID

   return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

#elif defined(__APPLE__)

   return m_psystem->m_pacmefile->module()-3;

#elif defined(_UWP)

   return "";

#elif defined(FREEBSD)

   return m_psystem->m_pacmefile->module() - 2;

#else

   return m_psystem->m_pacmefile->module() - 4;

#endif

}


::file::path acme_dir::beforeca2()
{

   return ::file_path_folder(install());

}


#ifdef WINDOWS_DESKTOP


#include <Shlobj.h>


::file::path acme_dir::program_files_x86()
{

   wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

   wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

   wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

   if (wcslen(wstrModuleFilePath) == 0)
   {

      SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

   }

   wstrModuleFilePath.trim_right(L"\\/");

   wcscpy(wstrModuleFolder, wstrModuleFilePath);

   return string(wstrModuleFolder);

}


::file::path acme_dir::program_files()
{

   wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

   wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

   wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

   if (wcslen(wstrModuleFilePath) == 0)
   {

      SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

   }

   wstrModuleFilePath.trim_right(L"\\/");

   wstrModuleFolder = wstrModuleFilePath;

   return string(wstrModuleFolder);



}


#else


::file::path acme_dir::program_files_x86()
{

   ::file::path path("/opt/ca2");

   return path;

}


::file::path acme_dir::program_files()
{

   ::file::path path("/opt/ca2");

   return path;

}


#endif


::file::path acme_dir::stage(string strAppId, string strPlatform, string strConfiguration)
{

   return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / time_binary_platform(strPlatform) / strConfiguration;

}


#ifdef LINUX


::file::path acme_dir::home()
{

   return getenv("HOME");

}


#else


::file::path acme_dir::home()
{

   return "";

}


#endif


//#if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//

::file::path acme_dir::bookmark()
{

   return localconfig() / "bookmark";

}


void acme_dir::set_path_install_folder(const string & strPath)
{

   m_pathInstallFolder = strPath;

}


::file::path acme_dir::sys_temp()
{

   return appdata() / "time";

}


::string acme_dir::dir_root()
{

   return "";

}


//::file::path acme_dir::home()
//{
//
//   return "";
//
//}


::file::path acme_dir::program_data()
{

   return "";

}


::file::path acme_dir::ca2appdata()
{

   return ca2roaming() / "appdata";

}



::file::path acme_dir::public_root()
{

   return program_data() / "ca2";

}

::file::path acme_dir::ca2roaming()
{

   return roaming() / "ca2";

}


::file::path acme_dir::localconfig()
{

   return ca2roaming() / "localconfig";

}


::file::path acme_dir::module()
{

   if(m_pathModuleFolder.is_empty())
   {

      auto pnode = m_psystem->node();

      auto pathModule = pnode->module_path_source();

      m_pathModuleFolder = pathModule.folder();

   }

   return m_pathModuleFolder;

}

//
//::file::path acme_dir::base_module()
//{
//
//   return "";
//
//}
//

//::file::path acme_dir::ca2_module()
//{
//
//   return "";
//
//}
//
::file::path acme_dir::archive()
{

   return "";

}



::file::path acme_dir::tool()
{

   return "";

}


::file::path acme_dir::roaming()
{

   return "";

}



::file::path acme_dir::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
{

   ::file::path_array patha;

   patha.add_tokens(pszEnv, ":", false);

   string strCandidate;

   for (i32 i = 0; i < patha.get_count(); i++)
   {

      strCandidate = patha[i] / pszTopic;

      //if (m_pcontext->m_papexcontext->file().exists(strCandidate))
      if (m_pacmefile->exists(strCandidate))
      {
         
         return strCandidate;

      }

   }

   return "";

}


::file::path acme_dir::get_memory_map_base_folder_path()
{

   return "";

}


//string acme_dir::system_short_name()
//{
//
//   return "";
//
//}


::file::path acme_dir::machine_event_file_path()
{

   return appdata() / "machine/event/machine_event.bin";

}


::file::path acme_dir::user_appdata_local()
{

   return "";

}


//::file::path acme_dir::tool()
//{
//
//   return archive() / "tool-windows";
//
//}


//bool acme_dir::_is(const char * path1)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}


//::file::path acme_dir::base_module()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}


//void acme_dir::create(const char * path)
//{
//
//   return _create(path);
//
//}


void acme_dir::create(const char * pathParam)
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

   path.ascendants_path(patha);

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


void acme_dir::_create2(const char * pathParam)
{

   if (is(pathParam))
   {

      return;

   }

   auto bExists = m_pacmefile->exists(pathParam);

   if(bExists)
   {

      m_pacmefile->erase(pathParam);

   }

   __create(pathParam);

}


//void acme_dir::_create_directory(const char * pathParam)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}

   
bool acme_dir::is(const char * path)
{

   if(::is_null(path))
   {

      throw ::exception(error_null_pointer);

   }

   if(*path == '\0')
   {

      throw ::exception(error_bad_argument);

   }

   bool bDir;

   if (_is(bDir, path))
   {

      return bDir;

   }

   return false;

}

//string name(string path);


void acme_dir::rls(::file::path_array & stra, const char * psz)
{

   throw ::interface_only();

}


void acme_dir::rls_dir(::file::path_array & stra, const char * psz)
{

   throw ::interface_only();

   //return "";

}


void acme_dir::ls(::file::path_array & stra, const char * psz)
{

   throw ::interface_only();

}


void acme_dir::ls_dir(::file::path_array & stra, const char * psz)
{

   throw ::interface_only();

}


void acme_dir::ls_file(::file::path_array & stra, const char * psz)
{

   throw ::interface_only();

}


//         ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);


         //::file::path archive();


int acme_dir::make_path(const char * psz)
{

   throw ::interface_only();

   return -1;

}


//   };


//} // namespace posix




      /*namespace dir
      {*/


      //string name(const char * pszPath);
      //bool mk(const ::string & strPath);
      //bool _mk(const  char * path); // makes a directory path (all intermediates too)
      //bool is(const char * path);
      //bool _is(const char * path);
      //bool mk(const  char * path); // makes a directory path (all intermediates too)
      //bool mkdir(const  char * path); // only creates if parent dir already exists
      //void ls(::file::path_array & patha, const char * path);
      //void ls_dir(::file::path_array & patha, const char * path);
      //void ls_file(::file::path_array & patha, const char * path);
      //void rls(::file::path_array & patha, const char * path);
      //void rls_dir(::file::path_array & patha, const char * path);


//::file::path acme_dir::module_folder()
//{
//
//   throw ::interface_only();
//
//   return "";
//
//}

//virtual::file::path base_module();


//} // namespace dir


bool acme_dir::_is(bool & bDir, const char * path)
{

   bDir = ::is_directory(path);

   return true;

}


void acme_dir::__create(const char * path)
{

   ::create_directory(path);

   /*auto estatus =*/ 

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void acme_dir::erase(const char* path)
{

   ::erase_directory(path);

}


string acme_dir::get_current()
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_dir::change_current(const char * psz)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_dir::change_to_home()
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



