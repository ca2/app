#include "framework.h"
#include "_linux.h"


namespace linux
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   void file_system::initialize(::particle * pparticle)
   {

      auto estatus = ::file_system::initialize(pparticle);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void file_system::init_system()
   {

      if(!update_module_path())
      {

         return ::error_failed;

      }

      return ::success;

   }


   void file_system::update_module_path()
   {

      auto estatus = ::file_system::update_module_path();

      if(!estatus)
      {

         return estatus;

      }

      ::file::path pathAppModule = acmepath()->app_module();

      m_pathModule = pathAppModule;

      ::file::path pathCa2AppModule = ::path::module();

      m_pathCa2Module = pathCa2AppModule;

      return estatus;

   }


} // namespace linux



