#include "framework.h"


namespace calculator
{


   calculator::calculator(::layered * pobjectContext) :
      ::object(pobject),
      ::apex::department(pobject)
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





