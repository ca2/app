#include "framework.h"
#include "_linux.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace linux
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::e_status file_system::initialize(::object * pobject)
   {

      auto estatus = ::file_system::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status file_system::init_system()
   {

      if(!update_module_path())
      {

         return ::error_failed;

      }

      return ::success;

   }


   ::e_status file_system::update_module_path()
   {

      auto estatus = ::file_system::update_module_path();

      if(!estatus)
      {

         return estatus;

      }

      ::file::path pathAppModule = m_psystem->m_pacmepath->app_module();

      m_pathModule = pathAppModule;

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      ::file::path pathCa2AppModule =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->module();

      m_pathCa2Module = pathCa2AppModule;

      return estatus;

   }


} // namespace linux



