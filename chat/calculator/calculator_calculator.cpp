#include "framework.h"


namespace calculator
{


   calculator::calculator(::object * pobject) :
      ::object(pobject),
      ::acme::department(pobject)
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





