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


   void dir_system::initialize(::object * pobject)
   {

      auto estatus = ::dir_system::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      return estatus;

   }




} // namespace android



