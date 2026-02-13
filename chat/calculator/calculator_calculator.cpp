#include "framework.h"


namespace calculator
{


   calculator::calculator(::particle * pparticle) :
      ::object(pparticle),
      ::platform::department(pparticle)
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





