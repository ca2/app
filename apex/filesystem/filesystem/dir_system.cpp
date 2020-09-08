#include "framework.h"
#include "aura/platform/app_core.h"


dir_system::dir_system()
{

   m_pathInstall = ::dir::install();

}


dir_system::~dir_system()
{

}


::estatus dir_system::initialize(::object * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }


   return true;

}


::estatus dir_system::init_system()
{

   if (!update_module_path())
   {

      return ::error_failed;

   }


   #if defined(__APPLE__) || (defined(LINUX) && defined(DEBUG)) || defined(ANDROID) || defined(_UWP)
   if (::dir::is(System.side_get_matter_path("app/_matter/main")))
   {

      m_pathLocalAppMatterFolder = System.side_get_matter_path("");

      m_pathLocalAppMatterCacheFolder = System.local_get_matter_cache_path();

   }
   else
#endif
   {

      m_pathLocalAppMatterFolder = System.local_get_matter_path();

      m_pathLocalAppMatterCacheFolder = System.local_get_matter_cache_path();

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

   //if (System.m_plibrary)
   //{

   //   if (System.m_plibrary->get_ca2_library())
   //   {

   //      strAppFolder = System.m_plibrary->get_ca2_library()->m_strFolder;

   //      if (strAppFolder.is_empty())
   //      {

   //         strAppFolder = System.m_plibrary->get_ca2_library()->m_strName;

   //      }

   //   }

   //}

   //if (strAppFolder.is_empty())
   //{

      strAppFolder = _002Underscore(System.m_strAppId);

   //}

   m_pathDefaultAppData /= strAppFolder;

   //m_strCa2DefaultAppData /= System.get_system_platform();

   //m_strCa2DefaultAppData /= System.get_system_configuration();

   ::file::path pathAppData;

   if (System.has_property("app_folder"))
   {

      pathAppData = System.value("app_folder");

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

   auto pfile = System.m_pfilesystem;

   auto pathModule = pfile->m_pathModule;

   ::file::path pathModuleFolder = pathModule.folder();

   m_pathModule = pathModuleFolder;

   auto pathCa2Module = pfile->m_pathCa2Module;

   ::file::path pathCa2ModuleFolder = pathCa2Module.folder();

   m_pathCa2Module = pathCa2ModuleFolder;

   return true;

}
