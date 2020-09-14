#include "framework.h"



namespace calculator
{


   calculator::calculator()
   {
   
   }


   calculator::~calculator()
   {

   }


   ::estatus calculator::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace calculator





