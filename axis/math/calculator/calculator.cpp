#include "framework.h"



namespace calculator
{


   calculator::calculator()
   {
   
   }


   calculator::~calculator()
   {

   }


   ::e_status calculator::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace calculator





