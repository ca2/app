#include "framework.h"


namespace calculator
{


   calculator::calculator(::object * pobject) :
      ::object(pobject),
      ::aura::department(pobject)
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





