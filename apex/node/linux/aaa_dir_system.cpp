#include "framework.h"
#include "_linux.h"
#undef USE_MISC

#include <dlfcn.h>
#include <link.h>


namespace linux
{


   dir_system::dir_system()
   {

   }


   dir_system::~dir_system()
   {

   }


   ::e_status dir_system::initialize(::object * pobject)
   {

      auto estatus = ::dir_system::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      void * handle = dlopen("libapex.so", RTLD_NOW);

      if(handle == nullptr)
      {

         m_pathCa2Module = m_pathModule;

      }
      else
      {

         link_map * plm;

         dlinfo(handle, RTLD_DI_LINKMAP, &plm);

         m_pathCa2Module = plm->l_name;

         if(m_pathCa2Module.is_empty() || m_pathCa2Module[0] != '/')
         {

            m_pathCa2Module = m_pathModule;

         }

         dlclose(handle);

      }

      m_pathHome = getenv("HOME");

      return estatus;

    }


} // namespace linux



