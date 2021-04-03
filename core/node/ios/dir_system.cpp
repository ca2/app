#include "framework.h"
#include "_ios.h"


namespace ios
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

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace ios



