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


   ::e_status dir_system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::dir_system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      m_pathHome = System->m_pathCacheDirectory / "home";

      return estatus;

   }




} // namespace android



