#include "framework.h"


namespace calculator
{


   calculator::calculator(::particle * pparticle) :
      ::object(pparticle),
      ::acme::department(pparticle)
   {
   
   }


   calculator::~calculator()
   {

   }


   bool calculator::initialize()
   {

      return true;

   }


} // namespace calculator





