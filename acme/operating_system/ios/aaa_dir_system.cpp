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


   void dir_system::initialize(::particle * pparticle)
   {

      auto estatus = ::dir_system::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace ios



