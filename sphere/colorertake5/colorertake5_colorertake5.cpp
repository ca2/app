#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


   colorertake5::colorertake5(::object * pobject) :
      object(pobject),
      ::acme::department(pobject)
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




