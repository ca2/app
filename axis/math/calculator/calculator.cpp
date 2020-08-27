#include "framework.h"
#include "calculator.h"


namespace calculator
{


   calculator::calculator()
   {
   
   }


   calculator::~calculator()
   {

   }


   ::estatus calculator::initialize(::object * pobjectContext)
   {

      auto estatus = ::aura::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace calculator





