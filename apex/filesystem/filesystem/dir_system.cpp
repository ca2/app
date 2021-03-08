#include "framework.h"
#include "apex/platform/app_core.h"


dir_system::dir_system()
{

   m_pathInstall = ::dir::install();

}


dir_system::~dir_system()
{

}


::e_status dir_system::initialize(::layered * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }


   return true;

}


::e_status dir_system::init_system()
{

   if (!update_module_path())
   {

      return ::error_failed;

   }

   auto psystem = ::apex::get_system();

   #if defined(__APPLE__) || (defined(DEBUG)) || defined(ANDROID) || defined(_UWP)
   if (::dir::is(psystem->side_get_matter_path("app/_matter/main")))
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

   m_pfilewatcher.create();

   ::dir::mk(::dir::bookmark());

   //if (!update_module_path())
   //{

   //   return false;

   //}

   //if (m_pziputil == nullptr)
   //{

   //   m_pziputil = new ::zip::util();

   //}

   string strRelative = ::dir::app_relative();

   m_pathDefaultAppData = ::dir::home() / "application";

   string strAppFolder;

   //if (::apex::get_system()->m_plibrary)
   //{

   //   if (::apex::get_system()->m_plibrary->get_ca2_library())
   //   {

   //      strAppFolder = ::apex::get_system()->m_plibrary->get_ca2_library()->m_strFolder;

   //      if (strAppFolder.is_empty())
   //      {

   //         strAppFolder = ::apex::get_system()->m_plibrary->get_ca2_library()->m_strName;

   //      }

   //   }

   //}

   //if (strAppFolder.is_empty())
   //{

      strAppFolder = _002Underscore(psystem->m_strAppId);

   //}

   m_pathDefaultAppData /= strAppFolder;

   //m_strCa2DefaultAppData /= ::apex::get_system()->get_system_platform();

   //m_strCa2DefaultAppData /= ::apex::get_system()->get_system_configuration();

   ::file::path pathAppData;

   if (::apex::get_system()->has_property("app_folder"))
   {

      pathAppData = ::apex::get_system()->payload("app_folder");

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

   auto & context = Context;

   auto psystem = ::apex::get_system();

   auto pfile = psystem->m_pfilesystem;

   auto pathModule = pfile->m_pathModule;

   ::file::path pathModuleFolder = pathModule.folder();

   m_pathModule = pathModuleFolder;

   auto pathCa2Module = pfile->m_pathCa2Module;

   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();

   m_pathCa2Module = pathCa2ModuleFolder;

   return true;

}
