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

      return estatus;

   }




} // namespace android



