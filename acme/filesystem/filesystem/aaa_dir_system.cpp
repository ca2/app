#include "framework.h"
#include "directory_system.h"
#include "file_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/parallelization/happening.h"
#include "acme/prototype/string/_string.h"
#include "acme/filesystem/watcher/watcher.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"


directory_system::directory_system()
{

   m_pathUpload = "C:\\upload";

}


directory_system::~directory_system()
{

}


void directory_system::initialize(::particle * pparticle)
{

   /*auto estatus = */ ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //auto psystem = system();

   //m_pathModule = psystem->m_pdirectorysystem->module();

   //return true;

}


void directory_system::init_system()
{

//   if (!update_module_path())
//   {
//
//      return ::error_failed;
//
//   }
//
   m_pathInstall = directory_system()->install();

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

   auto pdirectorysystem = directory_system();

#if defined(__APPLE__) || (defined(_DEBUG)) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)

   if ( pdirectorysystem->is(application()->side_get_matter_path("app/_matter/main")))
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

   //__øconstruct(m_pfilewatcher);

   pdirectorysystem->create(directory_system()->bookmark());

   //if (!update_module_path())
   //{

   //   return false;

   //}

   //if (m_pziputil == nullptr)
   //{

   //   m_pziputil = __allocate ::zip::util();

   //}

   ::string strAppId = directory_system()->appid();
   
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

   if (pathAppData.has_character())
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

   return directory_system()->home() / "application";

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

