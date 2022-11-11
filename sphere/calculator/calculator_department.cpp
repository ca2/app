#include "framework.h"


namespace calculator
{

   department::department(::particle * pparticle) :
      ::acme::department(pparticle)
   {
   }

   department::~department()
   {
   }


   bool department::init_instance()
   {

      if (!::acme::department::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



