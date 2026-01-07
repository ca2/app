#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


   colorertake5::colorertake5(::particle * pparticle) :
      object(pparticle),
      ::platform::department(pparticle)
   {

   }


   colorertake5::~colorertake5()
   {

   }


   bool colorertake5::initialize()
   {

      return true;

   }


} //namespace colorertake5




