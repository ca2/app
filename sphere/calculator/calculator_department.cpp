#include "framework.h"


namespace calculator
{

   department::department(::particle * pparticle) :
      ::platform::department(pparticle)
   {
   }

   department::~department()
   {
   }


   bool department::init_instance()
   {

      if (!::platform::department::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



