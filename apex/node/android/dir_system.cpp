#include "framework.h"
#include "_android.h"


namespace android
{


   dir_system::dir_system()
   {

   }


   dir_system::~dir_system()
   {

   }


   ::e_status dir_system::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::dir_system::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      m_pathHome = ::apex::get_system()->m_pathCacheDirectory / "home";

      return estatus;

   }




} // namespace android



