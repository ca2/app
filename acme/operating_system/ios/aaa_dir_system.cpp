#include "framework.h"
#include "_ios.h"


namespace ios
{


   directory_system::directory_system()
   {


   }


   directory_system::~directory_system()
   {


   }


   void directory_system::initialize(::particle * pparticle)
   {

      auto estatus = ::directory_system::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace ios



