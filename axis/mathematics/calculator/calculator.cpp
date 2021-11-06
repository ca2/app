#include "framework.h"


namespace calculator
{


   calculator::calculator()
   {
   
   }


   calculator::~calculator()
   {

   }


   ::e_status calculator::initialize(::object * pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace calculator





