#include "framework.h"
#include "apex/platform/app_core.h"
#include "acme/filesystem/filesystem/acme_dir.h"


dir_system::dir_system()
{

}


dir_system::~dir_system()
{

}


::e_status dir_system::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   m_pathInstall = m_psystem->m_pacmedir->install();

   return true;

}


::e_status dir_system::init_system()
{

   if (!update_module_path())
   {

      return ::error_failed;

   }

   auto psystem = get_system()->m_papexsystem;

   auto pacmedir = psystem->m_pacmedir;

   #if defined(__APPLE__) || (defined(DEBUG)) || defined(ANDROID) || defined(_UWP)

   if ( pacmedir->is(psystem->side_get_matter_path("app/_matter/main")))
   {

      m_pathLocalAppMatterFolder = psystem->side_get_matter_path("");

      m_pathLocalAppMatterCacheFolder = psystem->local_get_matter_cache_path();

   }
   else
#endif
   {

      m_pathLocalAppMatterFolder = psystem->local_get_matter_path();

      m_pathLocalAppMatterCacheFolder = psystem->local_get_matter_cache_path();

   }

   m_pfilewatcher.create(this);

   pacmedir->create(m_psystem->m_pacmedir->bookmark());

   //if (!update_module_path())
   //{

   //   return false;

   //}

   //if (m_pziputil == nullptr)
   //{

   //   m_pziputil = new ::zip::util();

   //}

   string strRelative = m_psystem->m_pacmedir->app_relative();

   m_pathDefaultAppData = m_psystem->m_pacmedir->home() / "application";

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

      strAppFolder = _002Underscore(psystem->m_strAppId);

   //}

   m_pathDefaultAppData /= strAppFolder;

   //m_strCa2DefaultAppData /= psystem->get_system_platform();

   //m_strCa2DefaultAppData /= psystem->get_system_configuration();

   ::file::path pathAppData;

   //auto psystem = get_system()->m_papexsystem;

   if (psystem->has_property("app_folder"))
   {

      //pathAppData = psystem->payload("app_folder");

      pathAppData = psystem->payload("app_folder");

   }

   if (pathAppData.has_char())
   {

      m_pathAppData = pathAppData;

   }
   else
   {

      m_pathAppData = m_pathDefaultAppData;
   }



   return ::success;

}


bool dir_system::update_module_path()
{

   //auto & context = Context;

   auto psystem = get_system()->m_papexsystem;

   auto pfile = psystem->m_pfilesystem;

   auto pathModule = pfile->m_pathModule;

   ::file::path pathModuleFolder = pathModule.folder();

   m_pathModule = pathModuleFolder;

   auto pathCa2Module = pfile->m_pathCa2Module;

   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();

   m_pathCa2Module = pathCa2ModuleFolder;

   return true;

}


//::string dir_system::dir_root()
//{
//
//   return "";
//
//}


//
//::file::path dir_system::get_memory_map_base_folder_path() const
//{
//
//   return "";
//
//}
//
//
//::file::path dir_system::home()
//{
//
//
//   return "";
//
//}
//


//
//
//::file::path dir_system::program_data()
//{
//
//   return "";
//
//}
//
//
//::file::path dir_system::roaming()
//{
//
//
//   return "";
//
//
//}


//::file::path dir_system::application_installer_folder(const ::file::path& pathExe, string strAppId, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
//{
//
//   return "";
//
//}


//::file::path dir_system::get_application_path(string strAppId, const char* pszPlatform, const char* pszConfiguration)
//{
//
//   return "";
//
//}


// ::file::path dir_system::get_last_run_application_path_file(string strAppId)
// {

//    return "";

// }


// ::file::path dir_system::get_last_run_application_path(string strAppId)
// {

//    return "";

// }

