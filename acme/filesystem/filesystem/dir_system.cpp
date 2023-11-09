#include "framework.h"
#include "dir_system.h"
#include "file_system.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/parallelization/event.h"
#include "acme/primitive/string/_string.h"
#include "acme/filesystem/watcher/watcher.h"
#include "acme/platform/application.h"
#include "acme/platform/context.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"


dir_system::dir_system()
{

   m_pathUpload = "C:\\upload";

}


dir_system::~dir_system()
{

}


void dir_system::initialize(::particle * pparticle)
{

   /*auto estatus = */ ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //auto psystem = acmesystem();

   //m_pathModule = psystem->m_pacmedirectory->module();

   //return true;

}


void dir_system::init_system()
{

//   if (!update_module_path())
//   {
//
//      return ::error_failed;
//
//   }
//
   m_pathInstall = acmedirectory()->install();

   //auto psystem = acmesystem()->m_papexsystem;

   //auto pfile = psystem->m_pfilesystem;

   //auto pathModule = pfile->m_pathModule;

   //::file::path pathModuleFolder = pathModule.folder();

//   m_pathModule = pathModuleFolder;

   //m_pathModule = acmeapplication()->get_module_folder();

//   auto pathCa2Module = pfile->m_pathCa2Module;
//
//   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();
//
//   m_pathCa2Module = pathCa2ModuleFolder;

   //auto psystem = acmesystem()->m_papexsystem;

   auto pacmedirectory = acmedirectory();

   #if defined(__APPLE__) || (defined(DEBUG)) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)

   if ( pacmedirectory->is(acmesystem()->side_get_matter_path("app/_matter/main")))
   {

      m_pathLocalAppMatterFolder = acmesystem()->side_get_matter_path("");

      m_pathLocalAppMatterCacheFolder = acmesystem()->local_get_matter_cache_path();

   }
   else
#endif
   {

      m_pathLocalAppMatterFolder = acmesystem()->local_get_matter_path();

      m_pathLocalAppMatterCacheFolder = acmesystem()->local_get_matter_cache_path();

   }

   __construct(m_pfilewatcher);

   pacmedirectory->create(acmedirectory()->bookmark());

   //if (!update_module_path())
   //{

   //   return false;

   //}

   //if (m_pziputil == nullptr)
   //{

   //   m_pziputil = memory_new ::zip::util();

   //}

   ::string strAppId = acmedirectory()->appid();
   
   information() << "dir_system::init_system strAppId : " << strAppId;

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

      //strAppFolder = _002Underscore(acmeapplication()->m_strAppId);

   //}

   m_pathDefaultAppData /= strAppFolder;

   //m_strCa2DefaultAppData /= psystem->get_system_platform();

   //m_strCa2DefaultAppData /= psystem->get_system_configuration();

   ::file::path pathAppData;

   //auto psystem = acmesystem()->m_papexsystem;

   if (acmesystem()->has_property("app_folder"))
   {

      //pathAppData = psystem->payload("app_folder");

      pathAppData = acmesystem()->payload("app_folder");

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


::file::path dir_system::compute_default_app_data_path()
{

   return acmedirectory()->home() / "application";

}



//bool dir_system::update_module_path()
//{
//
//   //auto & context = Context;
//
//   auto psystem = acmesystem()->m_papexsystem;
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


//::file::path dir_system::application_installer_folder(const ::file::path& pathExe, string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
//{
//
//   return "";
//
//}


//::file::path dir_system::get_application_path(string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
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

